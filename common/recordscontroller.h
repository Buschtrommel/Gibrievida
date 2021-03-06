/*
    Gibrievida - An activity tracker
    Copyright (C) 2016-2019 Hüssenbergnetz/Matthias Fehring
    https://github.com/Huessenbergnetz/Gibrievida

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef RECORDSCONTROLLER_H
#define RECORDSCONTROLLER_H

#include <QObject>
#include <QDateTime>
#include <QSoundEffect>
#include <QMediaPlayer>
#include "basecontroller.h"

class QTimer;
class QProximitySensor;
class QAccelerometer;
class QRotationSensor;
class QOrientationSensor;
class QMediaPlayer;

namespace Gibrievida {

class Record;
class Activity;
class Category;
class Configuration;
class DistanceMeasurement;

/*!
 * \brief Controller class to manage Record objects.
 *
 * This controller is used to manage single Record object like preparing new records, update active and finished records
 * as well as delete records.
 *
 * The workflow to create new records should be prepare(), add(), finish(). Active records can be canceled via cancel() method.
 */
class RecordsController : public BaseController
{
    Q_OBJECT
    Q_PROPERTY(Gibrievida::Record *current READ current WRITE setCurrent NOTIFY currentChanged)
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible)
    Q_PROPERTY(Gibrievida::DistanceMeasurement *distanceMeasurement READ distanceMeasurement NOTIFY distanceMeasurementChanged)
public:
    explicit RecordsController(Configuration *config, QObject *parent = nullptr);
    ~RecordsController();

    Q_INVOKABLE void prepare();
    Q_INVOKABLE void cancel();
    Q_INVOKABLE int add(Gibrievida::Activity *activity, const QString &note = QString(), int finishOnCovering = 0);
    Q_INVOKABLE void update(Gibrievida::Record *r, int oldActivityId);
    Q_INVOKABLE void remove(Gibrievida::Record *r);
    Q_INVOKABLE void removeByActivity(Gibrievida::Activity *a);
    Q_INVOKABLE void removeByCategory(Gibrievida::Category *c);
    Q_INVOKABLE void removeAll();

    Record *current() const;
    bool isVisible() const;
    DistanceMeasurement *distanceMeasurement() const;

    void setVisible(bool visible);

    Q_INVOKABLE void increaseRepetitions();
    Q_INVOKABLE void decreaseRepetitions();

public slots:
    void finish();

signals:
    /*!
     * \brief Emitted if a Record has been finished successfully and it's data has been written to database.
     */
    void finished(Record *record);
    /*!
     * \brief Emitted if a Record has been updated successfully in the database.
     */
    void updated(Record *record, int oldActivityId);
    /*!
     * \brief Emitted if a Record has been removed successfully from the database.
     */
    void removed(int databaseId, int activity, int category);
    /*!
     * \brief Emitted if a set of records has been removed successfully from the database.
     */
    void removedByActivity(int activity, int category);
    /*!
     * \brief Emitted if a set of records has been removed successfully from the database.
     */
    void removedByCategory(int category);
    /*!
     * \brief Emitted if all records have been removed successfully from the database.
     */
    void removedAll();

    void currentChanged(Record *current);
    void distanceMeasurementChanged(DistanceMeasurement *distanceMeasurement);

private slots:
    void updateDuration();
    void updateRepetitionClickSound(int clickSound);
    void proximityUpdate();
    void detectUpDownTop();
    void detectUpDownFace();
    void detectFinishOnCovering();
    void soundPlayerStatusChanged(QMediaPlayer::MediaStatus status);
    void updateMaxSpeed(qreal speed);
    void initialPositionAvailable(bool available);
    void positionSignalLost();

private:
    Q_DISABLE_COPY(RecordsController)

    void setCurrent(Record *nCurrent);
    void setDistanceMeasurement(DistanceMeasurement *nDistanceMeasurement);

    void init();
    void startStopTimer();
    void setSensor();
    void removeSensor();
    void playSound(const QString &soundFile);

    Record *m_current;
    bool m_visible;
    int m_finishOnCovering;
    DistanceMeasurement *m_distanceMeasurement;

    QTimer *m_timer;
    QTimer *m_sensorTimer;
    QTimer *m_finishOnCoveringTimer;
    Configuration *m_config;

    QSoundEffect m_repetitionClickSound;
    QProximitySensor *m_proximitySensor;
    QAccelerometer *m_accelSensor;
    QRotationSensor *m_rotationSensor;
    QOrientationSensor *m_orientationSensor;
    QMediaPlayer *m_soundPlayer;
};

}

#endif // RECORDSCONTROLLER_H
