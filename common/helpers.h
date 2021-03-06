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

#ifndef HELPERS_H
#define HELPERS_H

#include <QObject>
#include <QLocale>

namespace Gibrievida {

class Configuration;

/*!
 * \brief Provides helper functions.
 */
class Helpers : public QObject
{
    Q_OBJECT
public:
    explicit Helpers(Configuration *config, const QLocale &locale = QLocale(), QObject *parent = nullptr);
    ~Helpers();

    Q_INVOKABLE QString createDurationString(uint duration);
    Q_INVOKABLE QString relativeTimeString(const QDateTime &time);
    Q_INVOKABLE QString toDistanceString(double distance);
    Q_INVOKABLE QString toSpeedString(float speed);
    Q_INVOKABLE double toMetres(double yards);
    Q_INVOKABLE double toYards(double metres);

private:
    Q_DISABLE_COPY(Helpers)
    Configuration *m_c;
    QLocale m_l;
};

}

#endif // HELPERS_H
