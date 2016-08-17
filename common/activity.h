#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <QObject>

namespace Gibrievida {

class Category;

/*!
 * \brief The Activity class.
 */
class Activity : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int databaseId READ databaseId NOTIFY databaseIdChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(int minRepeats READ minRepeats WRITE setMinRepeats NOTIFY minRepeatsChanged)
    Q_PROPERTY(int maxRepeats READ maxRepeats WRITE setMaxRepeats NOTIFY maxRepeatsChanged)
    Q_PROPERTY(bool useRepeats READ useRepeats NOTIFY useRepeatsChanged)
    Q_PROPERTY(bool useDistance READ useDistance WRITE setUseDistance NOTIFY useDistanceChanged)
    Q_PROPERTY(int records READ records NOTIFY recordsChanged)
    Q_PROPERTY(Gibrievida::Category *category READ category NOTIFY categoryChanged)
public:
    explicit Activity(QObject *parent = nullptr);
    explicit Activity(int databaseId, const QString &name, int minRepeats, int maxRepeats, bool useDistance, int records, QObject *parent = nullptr);
    ~Activity();

    int databaseId() const;
    QString name() const;
    int minRepeats() const;
    int maxRepeats() const;
    bool useRepeats() const;
    bool useDistance() const;
    int records() const;
    Category *category() const;

    void setDatabaseId(int nDatabaseId);
    void setName(const QString &nName);
    void setMinRepeats(int nMinRepeats);
    void setMaxRepeats(int nMaxRepeats);
    void setUseRepeats(bool nUseRepeats);
    void setUseDistance(bool nUseDistance);
    void setRecords(int nRecords);
    void setCategory(Category *nCategory);

    Q_INVOKABLE bool isValid() const;


signals:
    void databaseIdChanged(int databaseId);
    void nameChanged(const QString &name);
    void minRepeatsChanged(int minRepeats);
    void maxRepeatsChanged(int maxRepeats);
    void useRepeatsChanged(bool useRepeats);
    void useDistanceChanged(bool useDistance);
    void recordsChanged(int records);
    void categoryChanged(Category *category);

private:
    Q_DISABLE_COPY(Activity)
    int m_databaseId;
    QString m_name;
    int m_minRepeats;
    int m_maxRepeats;
    bool m_useRepeats;
    bool m_useDistance;
    int m_records;
    Category *m_category;

};

}

#endif // ACTIVITY_H
