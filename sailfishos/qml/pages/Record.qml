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
import harbour.gibrievida 1.0
import "../common"

Page {
    id: singleRecordPage

    objectName: "SingleRecordPage"

    property Record record: null
    property bool comingFromList: false

    SilicaFlickable {
        PullDownMenu {
            MenuItem {
                visible: record && !record.active
                text: qsTr("Delete")
                onClicked: {
                    if (comingFromList) {
                        record.remove()
                        pageStack.pop()
                    } else {
                        remorse.execute(qsTr("Deleting"), function() {records.remove(record); pageStack.pop()})
                    }
                }
            }

            MenuItem {
                visible: record && !record.active
                text: qsTr("Edit")
                onClicked: pageStack.push(Qt.resolvedUrl("../dialogs/RecordDialog.qml"), {record: record})
            }

            MenuItem {
                visible: record && record.active
                //: pull down menu entry name
                text: qsTr("Cancel recording")
                //: remorse popup text
                onClicked: remorse.execute(qsTr("Cancel recording"), function() {records.cancel(); pageStack.pop()})
            }

            MenuItem {
                visible: record && record.active
                //: pull down menu entry name
                text: qsTr("Finish recording")
                onClicked: records.finish()
            }
        }

        id: singleRecordFlick
        anchors.fill: parent
        contentHeight: singleRecordCol.height + increaseRepArea.height

        VerticalScrollDecorator {
            flickable: singleRecordFlick
            page: singleRecordPage
        }

        Column {
            id: singleRecordCol
            anchors { left: parent.left; right: parent.right; leftMargin: Theme.horizontalPageMargin; rightMargin: Theme.horizontalPageMargin }
            spacing: Theme.paddingSmall

            PageHeader {
                id: pHeader
                page: singleRecordPage
                rightMargin: 0
                title: record ? record.activity.name : ""
            }

            IconSectionHeader {
                icon: "image://theme/icon-s-time"
                text: qsTr("Start time")
            }

            Text {
                id: startTimeText
                width: parent.width
                color: Theme.primaryColor
                font.pixelSize: Theme.fontSizeSmall
                text: record ? helpers.relativeTimeString(record.start) : ""
            }

            IconSectionHeader {
                icon: "image://theme/icon-s-duration"
                text: qsTr("Duration")
            }

            Text {
                id: durationText
                width: parent.width
                color: Theme.primaryColor
                font.pixelSize: Theme.fontSizeSmall
                text: record ? helpers.createDurationString(record.duration) : ""
            }

            IconSectionHeader {
                icon: "image://theme/icon-s-retweet"
                text: qsTr("Repetitions")
                visible: record ? record.activity.useRepeats : false
            }

            Text {
                width: parent.width
                color: Theme.primaryColor
                font.pixelSize: Theme.fontSizeSmall
                text: record ? record.repetitions : ""
                visible: record ? record.activity.useRepeats : false
            }

            IconSectionHeader {
                icon: "image://theme/icon-s-timer"
                text: qsTr("Time per repetition")
                visible: record && record.activity.useRepeats && !record.active
            }

            Text {
                width: parent.width
                color: Theme.primaryColor
                font.pixelSize: Theme.fontSizeSmall
                //: the s is the abbreviation for seconds
                text: record ? qsTr("%1s").arg(Number(record.tpr).toLocaleString(Qt.locale(), 'f', 3)) : ""
                visible: record && record.activity.useRepeats && !record.active
            }

            IconSectionHeader {
                icon: "image://theme/icon-s-task"
                text: qsTr("Distance")
                visible: record && record.activity.useDistance
            }

            Text {
                width: parent.width
                color: Theme.primaryColor
                font.pixelSize: Theme.fontSizeSmall
                text: record ? helpers.toDistanceString(record.distance) : ""
                visible: record && record.activity.useDistance
            }

            IconSectionHeader {
                icon: "image://theme/icon-s-alarm"
                text: qsTr("Average speed")
                visible: record && record.activity.useDistance && !record.active
            }

            Text {
                width: parent.width
                color: Theme.primaryColor
                font.pixelSize: Theme.fontSizeSmall
                text: record ? helpers.toSpeedString(record.avgSpeed) : ""
                visible: record && record.activity.useDistance && !record.active
            }

            IconSectionHeader {
                icon: "image://theme/icon-s-alarm"
                text: qsTr("Maximum speed")
                visible: record && record.activity.useDistance
            }

            Text {
                width: parent.width
                color: Theme.primaryColor
                font.pixelSize: Theme.fontSizeSmall
                text: record ? helpers.toSpeedString(record.maxSpeed) : ""
                visible: record && record.activity.useDistance
            }

            IconSectionHeader {
                icon: "image://theme/icon-s-edit"
                text: qsTr("Note")
                visible: record ? record.note != "" : false
            }

            Text {
                width: parent.width
                color: Theme.primaryColor
                font.pixelSize: Theme.fontSizeSmall
                text: record ? record.note : ""
                visible: record ? record.note != "" : false
            }

            IconSectionHeader {
                icon: "image://theme/icon-m-gps"
                text: qsTr("Satellites in use/view")
                visible: records.distanceMeasurement
            }

            Text {
                width: parent.width
                color: Theme.primaryColor
                font.pixelSize: Theme.fontSizeSmall
                text: records.distanceMeasurement ? records.distanceMeasurement.satellitesInUse + "/" + records.distanceMeasurement.satellitesInView : ""
                visible: records.distanceMeasurement
            }

            IconSectionHeader {
                icon: "image://theme/icon-s-timer"
                text: qsTr("Last position update")
                visible: records.distanceMeasurement
            }

            Text {
                width: parent.width
                color: records.distanceMeasurement && records.distanceMeasurement.lastUpdate >= 300 ? "#ff4d4d" : Theme.primaryColor
                font.pixelSize: Theme.fontSizeSmall
                visible: records.distanceMeasurement
                text: records.distanceMeasurement ? records.distanceMeasurement.lastUpdate < 0 ? qsTr("Never")
                                                  : records.distanceMeasurement.lastUpdate === 0
                                                    ? qsTr("Now")
                                                    : qsTr("%1 ago").arg(helpers.createDurationString(records.distanceMeasurement.lastUpdate))
                                                    : ""
            }

            IconSectionHeader {
                icon: "image://theme/icon-s-group-chat"
                text: qsTr("Position accuracy")
                visible: records.distanceMeasurement
            }

            Text {
                width: parent.width
                color: Theme.primaryColor
                font.pixelSize: Theme.fontSizeSmall
                text: records.distanceMeasurement ? helpers.toDistanceString(records.distanceMeasurement.accuracy) : ""
                visible: records.distanceMeasurement
            }
        }

        Item {
            id: satelliteConnection
            anchors { left: parent.left; right: parent.right; top: singleRecordCol.bottom }
            height: visible ? Theme.itemSizeHuge : 0
            visible: records.distanceMeasurement && !records.distanceMeasurement.initialPositionAvailable

            Label {
                anchors.centerIn: parent
                width: parent.width - (2 * Theme.horizontalPageMargin)
                text: records.distanceMeasurement ? qsTr("Waiting for initial position") : ""
                color: Theme.highlightColor
                font.pixelSize: Theme.fontSizeLarge
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                horizontalAlignment: Text.AlignHCenter
            }
        }

        BackgroundItem {
            id: increaseRepArea
            anchors { left: parent.left; right: parent.right; top: singleRecordCol.bottom }
            visible: record && record.active && record.activity.useRepeats
            contentHeight: increaseRepArea.height
            height: Screen.height - singleRecordCol.height - satelliteConnection.height

            onClicked: records.increaseRepetitions()

            Label {
                id: increaseRepLabel
                anchors.centerIn: parent
                width: parent.width - (2 * Theme.horizontalPageMargin)
                text: record && record.repetitions ? record.repetitions : qsTr("Click in this free space to add a repetition")
                font.pixelSize: record && record.repetitions ? (Theme.fontSizeExtraLarge * 5) : Theme.fontSizeLarge
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                color: increaseRepArea.highlighted ? Theme.highlightColor : Theme.primaryColor
                horizontalAlignment: Text.AlignHCenter
            }
        }

        RemorsePopup {
            id: remorse
        }
    }
}

