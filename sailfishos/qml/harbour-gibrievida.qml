/*
    Gibrievida - An activity tracker
    Copyright (C) 2016 Buschtrommel/Matthias Fehring http://gibrievida.buschmann23.de

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

import QtQuick 2.2
import Sailfish.Silica 1.0
import harbour.gibrievida 1.0
import "pages"

ApplicationWindow
{
    id: gibrievida
    initialPage: Component { MainPage { } }
    cover: Qt.resolvedUrl("cover/CoverPage.qml")
    allowedOrientations: Orientation.Portrait
    _defaultPageOrientations: Orientation.Portrait

    function updateVisibility()
    {
        if (pageStack.currentPage.objectName === "MainPage" || (pageStack.currentPage.objectName === "SingleRecordPage" && pageStack.currentPage.record.active) || cover.status === Cover.Active) {
            records.visible = true
        } else {
            records.visible = false
        }
    }

    Connections {
        target: pageStack
        onCurrentPageChanged: updateVisibility()
    }
}


