#include "activitiesmodel.h"
#include "activitiescontroller.h"
#include "categoriescontroller.h"
#include "category.h"
#include "activity.h"
#include <QSqlQuery>
#include <QSqlError>
#ifdef QT_DEBUG
#include <QtDebug>
#endif

using namespace Gibrievida;

/*!
 * \brief Constructs a new activities model.
 */
ActivitiesModel::ActivitiesModel(QObject *parent) : DBModel(parent)
{
    m_actsController = nullptr;
    m_catsController = nullptr;
    init();
}



/*!
 * \brief Destroys the model and all model data.
 */
ActivitiesModel::~ActivitiesModel()
{

}


/*!
 * \brief Reimplemented from QAbstractItemModel.
 */
QHash<int, QByteArray> ActivitiesModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractItemModel::roleNames();
    roles.insert(Item, QByteArrayLiteral("item"));
    return roles;
}



/*!
 * \brief Reimplemented from QAbstractItemModel.
 */
int ActivitiesModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_activities.count();
}


/*!
 * \brief Reimplemented from QAbstractListModel.
 */
QModelIndex ActivitiesModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent)) {
        return QModelIndex();
    }

    return createIndex(row, column);
}



/*!
 * \brief Reimplemented from QAbstractItemModel.
 */
QVariant ActivitiesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    if (index.row() > (m_activities.size()-1)) {
        return QVariant();
    }

    if (role == Item) {
        return QVariant::fromValue<Activity*>(m_activities.at(index.row()));
    } else {
        return QVariant();
    }
}



/*!
 * \brief Initializes the model data from the SQL database.
 */
void ActivitiesModel::init()
{
    setInOperation(true);

    clear();

    if (!connectDb()) {
        setInOperation(false);
        return;
    }

    QSqlQuery q(m_db);

    if (!q.exec(QStringLiteral("SELECT a.id, a.name, a.minrepeats, a.maxrepeats, a.distance, a.category, c.name as categoryname, c.color, (SELECT COUNT(id) FROM records WHERE activity = a.id) AS records, (SELECT COUNT(id) FROM activities WHERE category = a.category) AS catActs FROM activities a JOIN categories c ON c.id = a.category"))) {
        setInOperation(false);
        return;
    }

    QList<Activity*> t_activities;

    while (q.next()) {
        Activity *a = new Activity(q.value(0).toInt(), q.value(1).toString(), q.value(2).toInt(), q.value(3).toInt(), q.value(4).toBool(), q.value(8).toInt(), this);
        Category *c = new Category(q.value(5).toInt(), q.value(6).toString(), q.value(7).toString(), q.value(9).toInt(), a);
        a->setCategory(c);
        t_activities.append(a);
    }

    if (!t_activities.isEmpty()) {

        beginInsertRows(QModelIndex(), 0, t_activities.count()-1);

        m_activities = t_activities;

        endInsertRows();
    }

    setInOperation(false);
}



/*!
 * \brief Clears the model and removes all model data.
 */
void ActivitiesModel::clear()
{
    if (!m_activities.isEmpty()) {
        beginRemoveRows(QModelIndex(), 0, rowCount()-1);

        qDeleteAll(m_activities);
        m_activities.clear();

        endRemoveRows();
    }
}



/*!
 * \brief Adds a new Activity to the model.
 */
void ActivitiesModel::add(int databaseId, const QString &name, Category *c, int minRepeats, int maxRepeats, bool distance)
{
    Activity *a = new Activity(databaseId, name, minRepeats, maxRepeats, distance, 0, this);
    c->setParent(a);
    a->setCategory(c);

    beginInsertRows(QModelIndex(), rowCount(), rowCount());

    m_activities.append(a);

    endInsertRows();
}




/*!
 * \brief Removes the activity with \a databaseId.
 */
void ActivitiesModel::remove(int databaseId, int category)
{
    Q_UNUSED(category)

    int idx = find(databaseId);

    if (idx < 0) {
        return;
    }

    beginRemoveRows(QModelIndex(), idx, idx);

    delete m_activities.takeAt(idx);

    endRemoveRows();
}



/*!
 * \brief Removes all activites from the model.
 */
void ActivitiesModel::removeAll()
{
    clear();
}


/*!
 * \brief Reloads the model after a category has been removed.
 */
void ActivitiesModel::removeCategory(int category)
{
    Q_UNUSED(category)
    init();
}




/*!
 * \brief Updates the model items after a category has been updated.
 */
void ActivitiesModel::updateCategory(Category *c)
{
    if (m_activities.isEmpty()) {
        return;
    }

    if (!c) {
        return;
    }

    if (!c->isValid()) {
        return;
    }

    for (int i = 0; i < m_activities.size(); ++i) {
        Category *cat = m_activities.at(i)->category();
        if (cat->databaseId() == c->databaseId()) {
            cat->setName(c->name());
            cat->setColor(c->color());
        }
    }
}



/*!
 * \brief Returns the index of the model item identified by databaseId.
 *
 * If the item is not in the model, \a -1 will be returned.
 */
int ActivitiesModel::find(int databaseId)
{
    int idx = -1;

    if (m_activities.isEmpty()) {
        return idx;
    }

    for (int i = 0; i < m_activities.size(); ++i) {
        if (m_activities.at(i)->databaseId() == databaseId) {
            idx = i;
            break;
        }
    }

    return idx;
}



/*!
 * \brief Sets the activites controller.
 */
void ActivitiesModel::setActivitiesController(ActivitiesController *controller)
{
    if (controller != m_actsController) {
        if (m_actsController) {
            disconnect(m_actsController, &ActivitiesController::added, this, &ActivitiesModel::add);
            disconnect(m_actsController, &ActivitiesController::removed, this, &ActivitiesModel::remove);
            disconnect(m_actsController, &ActivitiesController::removedAll, this, &ActivitiesModel::removeAll);
        }
        m_actsController = controller;
        if (m_actsController) {
            connect(m_actsController, &ActivitiesController::added, this, &ActivitiesModel::add);
            connect(m_actsController, &ActivitiesController::removed, this, &ActivitiesModel::remove);
            connect(m_actsController, &ActivitiesController::removedAll, this, &ActivitiesModel::removeAll);
        }
    }
}


/*!
 * \brief Returns the currently set activities contoller.
 */
ActivitiesController *ActivitiesModel::getActivitiesController() const
{
    return m_actsController;
}



/*!
 * \brief Sets the categories controller.
 */
void ActivitiesModel::setCategoriesController(CategoriesController *controller)
{
    if (controller != m_catsController) {
        if (m_catsController) {
            disconnect(m_catsController, &CategoriesController::removed, this, &ActivitiesModel::removeCategory);
            disconnect(m_catsController, &CategoriesController::removedAll, this, &ActivitiesModel::removeAll);
            disconnect(m_catsController, &CategoriesController::updated, this, &ActivitiesModel::updateCategory);
        }
        m_catsController = controller;
        if (m_catsController) {
            connect(m_catsController, &CategoriesController::removed, this, &ActivitiesModel::removeCategory);
            connect(m_catsController, &CategoriesController::removedAll, this, &ActivitiesModel::removeAll);
            connect(m_catsController, &CategoriesController::updated, this, &ActivitiesModel::updateCategory);
        }
    }
}


/*!
 * \brief Returns the currently set categories controller.
 */
CategoriesController *ActivitiesModel::getCategoriesController() const
{
    return m_catsController;
}
