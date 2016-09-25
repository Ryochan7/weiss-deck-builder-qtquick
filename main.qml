import QtQuick 2.3
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4

import com.mycompany.qmlcomponents 1.0

ApplicationWindow {
    id: mainWindow

    visible: true
    width: 1024
    height: 700

    title: qsTr("Weiss Schwarz Deck Builder")

    property QtObject pelican

    function comeOnPelican(card)
    {
        pelican = card
    }

    function clearSearchFields()
    {
        cardIdSearchText.text = ""
        cardNameSearchText.text = ""
        cardColorSearchCombo.currentIndex = -1
        cardTypeSearchCombo.currentIndex = -1
        cardTriggerSearchCombo.currentIndex = -1
        cardPowerSearchText.text = ""
        cardCostSearchText.text = ""
        cardSoulSearchCombo.currentIndex = -1
        cardLevelSearchCombo.currentIndex = -1
        cardTraitSearchText.text = ""
        cardAbilitySearchText.text = ""
    }

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            /*MenuItem {
                text: qsTr("&Open")
                onTriggered: console.log("Open action triggered");
            }
            */

            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    ColumnLayout {
        id: searchFieldsColumn

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.topMargin: 10
        anchors.bottomMargin: 10
        anchors.leftMargin: 20
        anchors.rightMargin: 20

        RowLayout {
            Layout.fillWidth: true
            spacing: 10

            Label {
                text: "Card ID"
            }

            TextField {
                id: cardIdSearchText
                Layout.fillWidth: true
            }

            Label {
                text: "Card Name"
            }

            TextField {
                id: cardNameSearchText
                Layout.fillWidth: true
            }

            Label {
                text: "Color"
            }

            ComboBox {
                id: cardColorSearchCombo
                model: [" ", "Red", "Blue", "Yellow", "Green"]
                Layout.preferredWidth: 100
            }

            Label {
                text: "Type"
            }

            ComboBox {
                id: cardTypeSearchCombo
                model: [" ", "Climax", "Character", "Event"]
                Layout.preferredWidth: 100
            }

            Button {
                text: "Submit"

                onClicked: {
                    collectionView.selection.clear();
                    pelican = null;
                    collectionModel.searchDatabase({"cardid": cardIdSearchText.text,
                                                    "name": cardNameSearchText.text,
                                                    "color": cardColorSearchCombo.currentText,
                                                    "type": cardTypeSearchCombo.currentText,
                                                    "trigger": cardTriggerSearchCombo.currentText,
                                                    "power": cardPowerSearchText.text,
                                                    "cost": cardCostSearchText.text,
                                                    "soul": cardSoulSearchCombo.currentText,
                                                    "level": cardLevelSearchCombo.currentText,
                                                    "trait": cardTraitSearchText.text,
                                                    "ability": cardAbilitySearchText.text});
                }
            }
        }

        RowLayout {
            Layout.fillWidth: true

            Label {
                text: "Trigger"
            }

            ComboBox {
                id: cardTriggerSearchCombo
                model: [" ", "None", "Soul+1", "Soul+2", "Return", "Shot",
                    "Comeback", "Treasure", "Pool", "Draw"]
                Layout.preferredWidth: 100
            }

            Label {
                text: "Power"
            }

            TextField {
                id: cardPowerSearchText
                Layout.fillWidth: true
            }

            Label {
                text: "Cost"
            }

            TextField {
                id: cardCostSearchText
                Layout.fillWidth: true
            }

            Label {
                text: "Soul"
            }

            ComboBox {
                id: cardSoulSearchCombo
                model: [" ", "1", "2", "3"]
            }

            Label {
                text: "Level"
            }

            ComboBox {
                id: cardLevelSearchCombo
                model: [" ", "0", "1", "2", "3"]
            }

            Label {
                text: "Trait"
            }

            TextField {
                id: cardTraitSearchText
                Layout.fillWidth: true
            }

            Button {
                text: "Clear All"

                onClicked: {
                    clearSearchFields();
                    pelican = null;
                    collectionView.selection.clear();
                    collectionModel.searchDatabase({});
                }
            }
        }

        RowLayout {
            Layout.fillWidth: true

            Label {
                text: "Ability"
            }

            TextField {
                id: cardAbilitySearchText
                Layout.fillWidth: true
            }
        }
    }

    RowLayout {
        id: mainRow
        anchors.top: searchFieldsColumn.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 20

        spacing: 0

        ColumnLayout {
            id: columnLayout1
            Layout.alignment: Qt.AlignTop
            spacing: 10
            Layout.fillWidth: false
            Layout.preferredWidth: 400;

            RowLayout {
                id: rowLayout1

                spacing: 10

                Rectangle {
                    id: imageContainer
                    Layout.preferredWidth: 75
                    Layout.preferredHeight: 150
                    Layout.alignment: Qt.AlignTop

                    Image {
                        width: parent.width
                        height: parent.height

                        source: {
                            var result = "cardBack-s.jpg";
                            if (pelican)
                            {
                                var temp = pelican.getImageFilePath();
                                if (temp !== "")
                                {
                                    result = "file:/" + temp;
                                }
                            }

                            return result;
                        }

                        fillMode: Image.Stretch
                    }
                }

                ColumnLayout {
                    spacing: 10

                    RowLayout {

                        TextField {
                            id: cardNameText

                            text: pelican ? pelican.name : ""
                            placeholderText: "Name"
                            readOnly: true

                            Layout.fillWidth: true
                        }
                    }

                    RowLayout {

                        TextField {
                            id: cardIdText

                            text: pelican ? pelican.cid : ""
                            placeholderText: "ID"
                            readOnly: true

                            //Layout.fillWidth: true

                        }

                        TextField {
                            id: cardTypeText

                            text: pelican ? pelican.getTypeString() : ""
                            placeholderText: "Type"
                            readOnly: true
                            font.capitalization: Font.Capitalize

                            //Layout.fillWidth: true

                        }

                        TextField {
                            id: cardTriggerText

                            text: pelican && pelican.trigger !== WeissCard.NoneTrigger ? "Trigger: " + pelican.getTriggerString() : ""
                            placeholderText: "Trigger"
                            readOnly: true
                            font.capitalization: Font.Capitalize

                            //Layout.fillWidth: true

                        }
                    }

                    RowLayout {
                        TextField {
                            id: cardLevelText

                            text: pelican ? "L: " + pelican.level : ""
                            placeholderText: "Level"
                            readOnly: true

                            //Layout.fillWidth: true
                            Layout.preferredWidth: 50

                        }

                        TextField {
                            id: cardCostText

                            text: pelican ? "C: " + pelican.cost : ""
                            placeholderText: "Cost"
                            readOnly: true

                            //Layout.fillWidth: true
                            Layout.preferredWidth: 50

                        }

                        TextField {
                            id: cardPowerText

                            text: pelican ? "P: " + pelican.power : ""
                            placeholderText: "Power"
                            readOnly: true

                            //Layout.fillWidth: true

                        }

                        TextField {
                            id: cardSoulText

                            text: pelican ? "S: " + pelican.soul : ""
                            placeholderText: "Soul"
                            readOnly: true

                            //Layout.fillWidth: true

                        }
                    }

                    TextArea {
                        id: cardDescriptionText

                        //text: "Description"
                        text: {
                            var temp = "";
                            if (pelican)
                            {
                                if (pelican.trait !== "" || pelican.traitEn !== "")
                                {
                                    var temparray = [];

                                    temp += pelican.trait ? pelican.trait + " " : "";
                                    temp += pelican.traitEn ? pelican.traitEn : "";

                                }

                                if (pelican.trait2 !== "" || pelican.trait2En !== "")
                                {
                                    if (temp.length > 0)
                                    {
                                        temp += " | ";
                                    }

                                    temp += pelican.trait2 ? pelican.trait2 + " " : "";
                                    temp += pelican.trait2En ? pelican.trait2En : "";
                                }

                                if (temp.length > 0)
                                {
                                    temp += "\n\n";
                                }

                                temp += pelican.description ? pelican.description + "\n" : "";
                                temp += pelican.descriptionEn ? pelican.descriptionEn : "";

                                if (pelican.flavor !== "" || pelican.flavorEn !== "")
                                {
                                    temp += "\nFlavor Text: \n"
                                    temp += pelican && pelican.flavor ? pelican.flavor + " " : "";
                                    temp += pelican && pelican.flavorEn ? pelican.flavorEn : "";
                                }
                            }

                            return temp;
                        }

                        readOnly: true
                        style: TextAreaStyle {
                            backgroundColor: pelican ? pelican.getColorString().toLowerCase() : "#ffffff"
                        }

                        Layout.fillWidth: true

                    }
                }
            }

            Rectangle {
                color: "white"
                Layout.fillWidth: true
                height: 20

                Text {
                    x: 10
                    width: parent.width - 20
                    text: qsTr("Special thanks to <a href=\"http://www.littleakiba.com/\">littleakiba</a> for most of the translations.")
                    onLinkActivated: Qt.openUrlExternally(link)
                }
            }

            Row {
                Layout.alignment: Qt.AlignHCenter
                spacing: 6

                Button {
                    text: "New"

                    onClicked: {
                        clearSearchFields();
                        pelican = null;
                        collectionView.selection.clear();
                        deckModel.clear();
                        collectionModel.searchDatabase({});
                    }
                }

                Button {
                    text: "Save"

                    onClicked: {
                    }
                }

                Button {
                    text: "Load"

                    onClicked: {
                    }
                }

                Button {
                    text: "Exit"

                    onClicked: {
                        Qt.quit();
                    }
                }
            }
        }

        ColumnLayout {
            spacing: 10
            Layout.fillWidth: true
            //Layout.preferredWidth: parent.width * 0.5;
            Layout.alignment: Qt.AlignTop
            Layout.leftMargin: 40

            GroupBox {
                checkable: false
                checked: false
                title: "Search Results"

                Layout.fillWidth: true
                Layout.preferredWidth: 300

                ColumnLayout {
                    width: parent.width

                    spacing: 10

                    Label {
                        text: "Result count: " + collectionModel.resultCount;
                    }

                    TableView {
                        id: collectionView

                        Layout.fillWidth: true
                        Layout.preferredHeight: 200

                        model: collectionModel

                        TableViewColumn {
                            title: "ID"
                            role: "id"
                        }

                        TableViewColumn {
                            title: "Name"
                            role: "name"
                        }

                        TableViewColumn {
                            title: "Color"
                            role: "color"
                        }

                        TableViewColumn {
                            title: "Type"
                            role: "type"
                        }

                        TableViewColumn {
                            title: "Level"
                            role: "level"
                        }

                        TableViewColumn {
                            title: "Cost"
                            role: "cost"
                        }

                        TableViewColumn {
                            title: "Soul"
                            role: "soul"
                        }

                        TableViewColumn {
                            title: "Power"
                            role: "power"
                        }

                        onDoubleClicked: {
                            deckModel.addCard(collectionView.model.get(collectionView.currentRow), 1);
                        }

                        onCurrentRowChanged: {
                            pelican = model.get(collectionView.currentRow);
                        }

                        /*Keys.onPressed: {
                            if (event.key == Qt.Key_Return) {
                                event.accepted = true;
                            }
                        }
                        */

                        Keys.onReturnPressed: {
                            if (collectionView.currentRow > -1)
                            {
                                deckModel.addCard(collectionView.model.get(collectionView.currentRow), 1);
                            }
                        }
                    }

                    Row {
                        //Layout.fillWidth: true
                        Layout.alignment: Qt.AlignHCenter
                        spacing: 6

                        Button {
                            text: "+1"
                            width: 60

                            onClicked: {
                                deckModel.addCard(collectionView.model.get(collectionView.currentRow), 1);
                            }
                        }

                        Button {
                            text: "+4"
                            width: 60

                            onClicked: {
                                deckModel.addCard(collectionView.model.get(collectionView.currentRow), 4);
                            }
                        }

                        Button {
                            text: "-1"
                            width: 60

                            onClicked: {
                                deckModel.removeCard(collectionView.model.get(collectionView.currentRow), 1);
                            }
                        }

                        Button {
                            text: "-4"
                            width: 60

                            onClicked: {
                                deckModel.removeCard(collectionView.model.get(collectionView.currentRow), 4);
                            }
                        }
                    }
                }
            }
        }
    }

    GroupBox {
        id: deckGroupBox
        anchors.top: mainRow.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right

        anchors.leftMargin: 20
        anchors.rightMargin: 20
        anchors.topMargin: 20
        anchors.bottomMargin: 20

        title: "Deck List"

        RowLayout {
            id: rowLayout2
            anchors.fill: parent
            anchors.topMargin: 10

            spacing: 10

            Column {
                id: firstLabelsColumn
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignVCenter
                Layout.preferredWidth: 150
                //width: 150
                //anchors.left: parent.left
                //anchors.leftMargin: 0
                //anchors.top: parent.top

                Label {
                    property int value: realDeck.cardCount;
                    text: "Card count: " + value
                }

                Label {
                    property int value: realDeck.climaxCount;
                    text: "Climax: " + value
                    color: "red"
                }

                Label {
                    property int value: realDeck.level0Count;
                    text: "Level 0: " + value
                    color: "red"
                }

                Label {
                    property int value: realDeck.level1Count;
                    text: "Level 1: " + value
                    color: "red"
                }

                Label {
                    property int value: realDeck.level2Count;
                    text: "Level 2: " + value
                    color: "red"
                }

                Label {
                    property int value: realDeck.level3Count;
                    text: "Level 3: " + value
                    color: "red"
                }

                Label {
                    property int value: realDeck.soulTriggerCount;
                    text: "Soul Triggers: " + value
                }
            }

            Column {
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignVCenter
                Layout.preferredWidth: 75
                //anchors.right: parent.right
                //anchors.rightMargin: 0
                //anchors.left: firstLabelsColumn.right
                //anchors.leftMargin: 10
                //width: 150

                Label {
                    property int value: realDeck.eventCount;
                    text: "Event: " + value
                }

                Label {
                    property int value: realDeck.yellowCount;
                    text: "Yellow: " + value
                }

                Label {
                    property int value: realDeck.greenCount;
                    text: "Green: " + value
                }

                Label {
                    property int value: realDeck.redCount;
                    text: "Red: " + value
                }

                Label {
                    property int value: realDeck.blueCount;
                    text: "Blue: " + value
                }

                Item {
                    //color: "white"
                    height: 20
                    width: 1
                }

                Button {
                    text: "Clear Deck"

                    onClicked: {
                        console.log("[CLEAR DECK] Captain")
                        deckModel.clear();
                    }
                }
            }

            TableView {
                id: tabletable
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.leftMargin: 20

                model: deckModel

                TableViewColumn {
                    title: "#"
                    role: "quantity"
                }

                TableViewColumn {
                    title: "ID"
                    role: "id"
                }

                TableViewColumn {
                    title: "Name"
                    role: "name"
                }

                TableViewColumn {
                    title: "Color"
                    role: "color"
                }

                TableViewColumn {
                    title: "Type"
                    role: "type"
                }

                TableViewColumn {
                    title: "L"
                    role: "level"
                }

                TableViewColumn {
                    title: "C"
                    role: "cost"
                }

                TableViewColumn {
                    title: "Trigger"
                    role: "trigger"
                }

                TableViewColumn {
                    title: "S"
                    role: "soul"
                }

                TableViewColumn {
                    title: "Power"
                    role: "power"
                }

                onCurrentRowChanged: {
                    pelican = deckModel.get(tabletable.currentRow);
                }

                onDoubleClicked: {
                    deckModel.removeCard(deckModel.get(tabletable.currentRow), 1);
                }
            }
        }
    }
}
