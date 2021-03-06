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

import QtQuick 2.2
import Sailfish.Silica 1.0

Item {
    width: parent.width
    height: header.height

    property alias text: header.text
    property alias icon: icon.source

    Image {
        id: icon
        anchors { left: parent.left }
        width: Theme.iconSizeSmall; height: Theme.iconSizeSmall
    }

    Label {
        id: header
        anchors { right: parent.right }
        width: parent.width - icon.width - Theme.paddingMedium
        horizontalAlignment: Text.AlignRight
        font.pixelSize: Theme.fontSizeSmall
        color: Theme.highlightColor
    }
}

