import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1

Rectangle {
    id: main
    color: "darkgray"

    property string title;
    property color textColor: "white"
    property Item threeD
    default property list<QtObject> properties

    property list<Item> controls
    property list<MenuChoice> menuChoices

    Item {
        id: titleRow
        anchors.top:parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: 30

        Label {
            anchors.centerIn: parent
            text: title
            font.bold: true
        }
    }

    Component {
        id: bool_control
        Item {
            property Item prev
            anchors.top: prev.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 10
            anchors.rightMargin: 10
            implicitHeight: 40

            property QtObject prop
            property QtObject target

            function reset() {
                bool_check.checked = target.value
            }
            Row {
                anchors.fill: parent
                spacing: 5

                Label {
                    id: bool_control_label
                    height: parent.height
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignRight
                    width: parent.width - bool_check.implicitWidth - 5
                    text: prop.name
                    color: textColor
                    font.bold: true
                }
                Switch {
                    id: bool_check
                    width: implicitWidth
                    checked: target.value

                    onCheckedChanged: {
                        target.value = checked
                    }
                }
            }
        }
    }

    Component {
        id: menu_choice
        Rectangle {
            property Item prev
            anchors.top: prev.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 10
            anchors.rightMargin: 10
            implicitHeight: 30

            property QtObject prop
            property QtObject target

            color: target.value ? "lightgray" : "transparent"

            function reset() {
                menu_label.color = target.value ? "green" : textColor
            }
            Label {
                id: menu_label
                anchors.fill: parent
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                text: prop.name
                color: target.value ? "green" : textColor
                font.bold: true

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        for(var i=0; i<menuChoices.length; i++)
                            menuChoices[i].value = (menuChoices[i] === target)
                    }
                }
            }
        }
    }

    Component {
        id: float_control
        Item {
            property Item prev
            anchors.top: prev.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 10
            anchors.rightMargin: 10
            implicitHeight: 40

            property QtObject prop
            property alias from: float_slider.from
            property alias to: float_slider.to
            property QtObject target

            function reset() {
                float_slider.value = target.value
            }
            Row {
                anchors.fill: parent
                spacing: 10

                Label {
                    height: parent.height
                    verticalAlignment: Text.AlignVCenter
                    width: 60
                    text: prop.name
                    font.bold: true
                    color: textColor
                }
                Slider {
                    id: float_slider
                    width: parent.width - 70
                    from: from
                    to: to
                    value: target.value

                    onValueChanged: {
                        target.value = value
                        threeD.update()
                    }
                    handle: Rectangle {
                        x: float_slider.leftPadding + float_slider.visualPosition * (float_slider.availableWidth - width)
                        y: float_slider.topPadding + float_slider.availableHeight / 2 - height / 2
                        implicitWidth: 30
                        implicitHeight: 30
                        radius: 15
                        color: float_slider.pressed ? "#f0f0f0" : "#f6f6f6"
                        border.color: "#bdbebf"

                        Label {
                            anchors.centerIn: parent
                            text: float_slider.value.toFixed(2)
                        }
                    }
                }
            }
        }
    }

    function reset()
    {
        for(var index=0; index < properties.length; index++) {
            properties[index].reset()
        }
        for(var index=0; index < controls.length; index++) {
            controls[index].reset()
        }
    }

    Component.onCompleted: {
        var height = 10 + titleRow.height
        var prev = titleRow

        for(var index=0; index < properties.length; index++) {
            var prop = properties[index]
            if(prop.type === "float") {
                prev = float_control.createObject(main, {"anchors.top": prev.bottom,
                                                      prop: prop, from: prop.from, to: prop.to, target: prop})
                controls.push(prev)
            }
            else if(prop.type === "bool") {
                prev = bool_control.createObject(main, {"anchors.top": prev.bottom, prop: prop, target: prop})
                controls.push(prev)
            }
            else if(prop.type === "menuchoice") {
                prev = menu_choice.createObject(main, {"anchors.top": prev.bottom, prop: prop, target: prop})
                menuChoices.push(prop)
            }
            height += prev.implicitHeight
        }
        main.height = height
    }
}
