#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDesktopServices>
#include <QFileDialog>
#include <QPainter>
#include <QMessageBox>
#include "character.h"
#include "constants.h"
#include "functions.h"
#include "itemedit.h"
#include "variables.h"
#include "xml.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->ui->setupUi(this);

    this->ui->redHeartLineEdit->setValidator(this->_healthValidator);
    this->ui->soulHeartLineEdit->setValidator(this->_healthValidator);
    this->ui->blackHeartLineEdit->setValidator(this->_healthValidator);

    this->ui->coinLineEdit->setValidator(this->_consumableValidator);
    this->ui->bombLineEdit->setValidator(this->_consumableValidator);
    this->ui->keyLineEdit->setValidator(this->_consumableValidator);

    this->ui->pathTextEdit->setText(this->_defaultPath);

    this->ui->cardComboBox->view()->setMinimumWidth(constants::COMBOBOX_VIEW_MIN_WIDTH);
    this->ui->trinketComboBox->view()->setMinimumWidth(constants::COMBOBOX_VIEW_MIN_WIDTH);

    this->ui->notepadButton->setIcon(QIcon(":/Resources/Buttons/NotepadButton.png"));
    this->ui->compassButton->setIcon(QIcon(":/Resources/Buttons/CompassButton.png"));
    this->ui->randomCostumeButton->setIcon(QIcon(":/Resources/Buttons/DiceButton.png"));

#if defined(Q_OS_MAC)
    //Needed to set the fonts on these for whatever reason
    this->ui->redHeartLineEdit->setFont(this->_font);
    this->ui->soulHeartLineEdit->setFont(this->_font);
    this->ui->blackHeartLineEdit->setFont(this->_font);
    this->ui->coinLineEdit->setFont(this->_font);
    this->ui->bombLineEdit->setFont(this->_font);
    this->ui->keyLineEdit->setFont(this->_font);
    this->ui->sortCheckBox->setFont(this->_font);
    this->ui->pillCheckBox->setFont(this->_font);
    this->ui->cardCheckBox->setFont(this->_font);
    this->ui->trinketCheckBox->setFont(this->_font);
#endif

    QApplication::setWindowIcon(QIcon(":Resources/Icons/PurpleKey.ico"));
    QApplication::setFont(this->_font);
    QWidget::setFixedSize(this->size());

    setWindowTitle(constants::TITLE + " " + constants::VERSION);

    QPixmap result(this->size());

    result.fill(Qt::transparent);
    {
        const auto getPixmap = [](QString filename) -> QPixmap {
            return QPixmap(":/Resources/Background/" + filename + ".png");
        };
        QPainter painter(&result);
        painter.drawPixmap(0, 0, getPixmap("Background"));
        painter.drawPixmap(0, 0, getPixmap("BackgroundOverlay"));
        painter.drawPixmap(224, 10, getPixmap("WhoAmI"));
        painter.drawPixmap(453, 135, getPixmap("MyStuff"));
    }

    result = result.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, result);
    this->setPalette(palette);

    SetUpHealthAndConsumableLabels();
    GenerateCharacterComboBox();
    GenerateComboBoxes();

    //Generating ComboBoxes resets the spacebar item to 0
    //Workaround to set it to Isaac's spacebar item.
    for(int i = 0; i < this->ui->spacebarComboBox->count(); ++i)
        if(ui->spacebarComboBox->itemText(i) == "The D6")
            this->ui->spacebarComboBox->setCurrentIndex(i);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete this->_healthValidator;
    delete this->_consumableValidator;
}

void MainWindow::SetUpHealthAndConsumableLabels()
{
    this->_draw.PixmapToLabel(this->ui->redHeartImageLabel, ":/Resources/Health/RedHeartFull.png");
    this->_draw.PixmapToLabel(this->ui->soulHeartImageLabel, ":/Resources/Health/SoulHeartFull.png");
    this->_draw.PixmapToLabel(this->ui->blackHeartImageLabel, ":/Resources/Health/BlackHeartFull.png");

    this->_draw.PixmapToLabel(this->ui->coinImageLabel, ":/Resources/Consumables/Coin.png");
    this->_draw.PixmapToLabel(this->ui->bombImageLabel, ":/Resources/Consumables/Bomb.png");
    this->_draw.PixmapToLabel(this->ui->keyImageLabel, ":/Resources/Consumables/Key.png");
}

void MainWindow::ReplaceComboBoxItems(QComboBox* comboBox, QStringList items)
{
    //Replaces the items in the ComboBox with the provided ones and keeps the previously
    //selected value selected if possible, else it selects "None".
    QString previousSelection = comboBox->currentText();

    comboBox->clear();
    comboBox->addItems(items);

    for(int i = 0; i < comboBox->count(); ++i)
        if(previousSelection == comboBox->itemText(i))
            comboBox->setCurrentIndex(i);
}

void MainWindow::GenerateComboBoxes()
{
    //Character ComboBox is excluded because it's only supposed to be called
    //when a character's name is changed and Afterbirth is enabled/disabled.

    GenerateSpacebarComboBox();
    GenerateCardComboBox();
    GenerateTrinketComboBox();
}

void MainWindow::GenerateCharacterComboBox()
{
    QStringList characterNames;
    for(int i = 0; i < constants::REBIRTH_CHARACTER_COUNT; ++i)
        characterNames.append(characterMap.at(static_cast<Characters>(i)).Name);
    if(afterbirthEnabled) for(int i = 0; i < constants::AFTERBIRTH_CHARACTER_COUNT; ++i)
        characterNames.append(characterMap.at(static_cast<Characters>(constants::REBIRTH_CHARACTER_COUNT + i)).Name);

    int previousIndex = this->ui->characterComboBox->currentIndex();
    this->ui->characterComboBox->clear();
    this->ui->characterComboBox->addItems(characterNames);
    if(previousIndex > 0 && previousIndex < this->ui->characterComboBox->count())
        this->ui->characterComboBox->setCurrentIndex(previousIndex);
}

void MainWindow::GenerateSpacebarComboBox()
{
    QStringList spacebarList {
        "None", //0
        "The Bible",
        "The Book of Belial",
        "The Necronomicon",
        "The Poop",
        "Mr. Boom",
        "Tammy's Head",
        "Mom's Bra",
        "Kamikaze",
        "Mom's Pad",
        "Bob's Rotten Head", //10
        "Teleport",
        "Yum Heart",
        "Doctor's Remote",
        "Shoop Da Woop",
        "Lemon Mishap",
        "Book of Shadows",
        "Anarchist's Cookbook",
        "The Hourglass",
        "My Little Unicorn",
        "Book of Revelations", //20
        "The Nail",
        "We Need To Go Deeper",
        "Deck of Cards",
        "Monstro's Tooth",
        "The Gamekid",
        "The Book of Sin",
        "Mom's Bottle of Pills",
        "The D6",
        "Pinking Shears",
        "The Bean", //30
        "Monster Manual",
        "Dead Sea Scrolls",
        "Razor Blade",
        "Forget Me Now",
        "A Pony",
        "Guppy's Paw",
        "IV Bag",
        "Best Friend",
        "Remote Detonator",
        "Guppy's Head", //40
        "Prayer Card",
        "Notched Axe",
        "Crystal Ball",
        "Crack The Sky",
        "The Candle",
        "D20",
        "Spider Butt",
        "Dad's Key",
        "Portable Slot",
        "White Pony", //50
        "Blood Rights",
        "Telepathy For Dummies",
        "How To Jump",
        "D100",
        "D4",
        "D10",
        "Blank Card",
        "Book of Secrets",
        "Box of Spiders",
        "Red Candle", //60
        "The Jar",
        "Flush!",
        "The Satanic Bible",
        "Head of Krampus",
        "Butter Bean",
        "Magic Fingers",
        "Converter",
        "Pandora's Box",
        "Unicorn Stump",
        "Isaac's Tears", //70
        "Undefined",
        "Scissors",
        "Breath of Life",
        "Boomerang"
    };

    if(afterbirthEnabled)
    {
        spacebarList.append(QStringList {
            "Diplopia",
            "Placebo",
            "Wooden Nickel",
            "Mega Bean",
            "Glass Cannon",
            "Box of Friends",
            "Friendly Ball",
            "Tear Detonator",
            "D12",
            "Ventricide Razor",
            "D8",
            "Teleport 2.0",
            "Kidney Bean",
            "Glowing Hour Glass",
            "Mine Crafter",
            "Jar of Flies",
            "D7",
            "Mom's Box",
            "Mega Blast"
        });
    }

    if(sortAlphabetically)
    {
        //Removes and inserts "None" so it's always the first, regardless of sorting.
        spacebarList.removeAt(0);
        spacebarList.sort();
        spacebarList.insert(0, "None");
    }

    ReplaceComboBoxItems(this->ui->spacebarComboBox, spacebarList);
    /*
    QString previousSelection = this->ui->spacebarComboBox->currentText();

    this->ui->spacebarComboBox->clear();
    this->ui->spacebarComboBox->addItems(spacebarList);

    for(int i = 0; i < this->ui->spacebarComboBox->count(); ++i)
        if(previousSelection == this->ui->spacebarComboBox->itemText(i))
            this->ui->spacebarComboBox->setCurrentIndex(i);*/
}

void MainWindow::GenerateCardComboBox()
{
    QStringList cardList {
        "None", //0
        "O - The Fool", //1
        "I - The Magician", //2
        "II - The High Priestess", //3
        "III - The Empress", //4
        "IV - The Emperor", //5
        "V - The Hierophant", //6
        "VI - The Lovers", //7
        "VII - The Chariot", //8
        "VIII - Justice", //9
        "IX - The Hermit", //10
        "X - Wheel of Fortune", //11
        "XI - Strength", //12
        "XII - The Hanged Man", //13
        "XIII - Death", //14
        "XIV - Temperance", //15
        "XV - The Devil", //16
        "XVI - The Tower", //17
        "XVII - The Stars", //18
        "XVIII - The Moon", //19
        "XIX - The Sun", //20
        "XX - Judgement", //21
        "XXI - The World", //22
        "2 of Clubs", //23
        "2 of Diamonds", //24
        "2 of Spades", //25
        "2 of Hearts", //26
        "Joker", //27
        "Rune of Hagalaz", //28
        "Rune of Jera", //29
        "Rune of Ehwaz", //30
        "Rune of Dagaz", //31
        "Rune of Ansuz", //32
        "Rune of Perthro", //33
        "Rune of Berkano", //34
        "Rune of Algiz", //35
        "Chaos Card", //37
        "Credit Card", //38
        "Rules Card", //39
        "A Card Against Humanity", //40
        "Suicide King" //41
    };

    if(afterbirthEnabled)
    {
        //Blank Rune is ID 36 in Afterbirth, moving the other Rebirth cards' IDs up by one
        cardList.insert(36, "Blank Rune"); //36
        cardList.append(QStringList {
            "Get Out of Jail Free Card", //42
            "? Card", //43
            "Dice Shard", //44
            "Emergency Contact" //45
        });
    }

    ReplaceComboBoxItems(this->ui->cardComboBox, cardList);
}

void MainWindow::GenerateTrinketComboBox()
{
    QStringList trinketList {
        "None", //0
        "Swallowed Penny",
        "Petrified Poop",
        "AAA Battery",
        "Broken Remote",
        "Purple Heart",
        "Broken Magnet",
        "Rosary Bead",
        "Cartridge",
        "Pulse Worm",
        "Wiggle Worm", //10
        "Ring Worm",
        "Flat Worm",
        "Store Credit",
        "Callus",
        "Lucky Rock",
        "Mom's Toenail",
        "Black Lipstick",
        "Bible Tract",
        "Paper Clip",
        "Monkey's Paw", //20
        "Mysterious Paper",
        "Daemon's Tail",
        "Missing Poster",
        "Butt Penny",
        "Mysterious Candy",
        "Hook Worm",
        "Whip Worm",
        "Broken Ankh",
        "Fish Head",
        "Pinky Eye", //30
        "Push Pin",
        "Liberty Cap",
        "Umbilical Cord",
        "Child's Heart",
        "Curved Horn",
        "Rusted Key",
        "Goat Hoof",
        "Mom's Pearl",
        "Cancer",
        "Red Patch", //40
        "Match Stick",
        "Lucky Toe",
        "Cursed Skull",
        "Safety Cap",
        "Ace of Spades",
        "Isaac's Fork",
        //"Polaroid",
        "A Missing Page",
        "Bloody Penny",
        "Burnt Penny", //50
        "Flat Penny",
        "Counterfeit Coin",
        "Tick",
        "Isaac's Head",
        "Maggy's Faith",
        "Judas' Tongue",
        "\?\?\?'s Soul", //escapes a trigraph
        "Samson's Lock",
        "Cain's Eye",
        "Eve's Bird Foot", //60
        "The Left Hand"
    };

    if(afterbirthEnabled)
    {
        trinketList.append(QStringList {
            "Shiny Rock",
            "Safety Scissors",
            "Rainbow Worm",
            "Tape Worm",
            "Lazy Worm",
            "Cracked Dice",
            "Super Magnet",
            "Faded Polaroid",
            "Louse",
            "Bob's Bladder",
            "Watch Battery",
            "Blasting Cap",
            "Stud Finder",
            "Error",
            "Poker Chip",
            "Blister",
            "Second Hand",
            "Endless Nameless",
            "Black Feather",
            "Blind Rage",
            "Golden Horse Shoe",
            "Store Key",
            "Rib of Greed",
            "Karma",
            "Lil Larva",
            "Mom's Locket",
            "NO!",
            "Child Leash",
            "Brown Cap"
        });
    }

    if(sortAlphabetically)
    {
        //Removes and inserts "None" so it's always the first, regardless of sorting.
        trinketList.removeAt(0);
        trinketList.sort();
        trinketList.insert(0, "None");
    }

    ReplaceComboBoxItems(this->ui->trinketComboBox, trinketList);
}

std::array<QLabel*, 12> MainWindow::SetUpHeartLabels()
{
    std::array<QLabel*, 12> heartLabels;
    int x = 62, y = 14;
    for(int i = 0; i < 12; ++i)
    {
        QLabel* tempHeartLabel = new QLabel(this);
        tempHeartLabel->setGeometry(x, y, constants::HEART_LABEL_SIZE, constants::HEART_LABEL_SIZE);
        x += constants::HEART_LABEL_SIZE;
        if(i == 5)
        {
            y += constants::HEART_LABEL_SIZE;
            x = 62;
        }
        heartLabels.at(i) = tempHeartLabel;
    }
    return heartLabels;
}

void MainWindow::SetCurrentCharacter(int characterToSet)
{
    //Happens when the ComboBox is cleared.
    if(characterToSet == -1) return;

    currentCharacter = static_cast<Characters>(characterToSet);
    Character character = characterMap.at(currentCharacter);
    this->_draw.Character(this->ui->characterImageLabel, currentCharacter);
    this->_draw.Health(this->_heartLabels, character.RedHearts, character.SoulHearts, character.BlackHearts,
                       currentCharacter == Characters::TheKeeper);

    if(character.Pill == 1) this->_draw.Pill(this->ui->cardImageLabel);
    else if(character.Card > 0) this->_draw.Card(this->ui->cardImageLabel, character.Card);

    this->ui->redHeartLineEdit->setText(QString::number(character.RedHearts));
    this->ui->soulHeartLineEdit->setText(QString::number(character.SoulHearts));
    this->ui->blackHeartLineEdit->setText(QString::number(character.BlackHearts));

    this->ui->coinLineEdit->setText(QString::number(character.Coins));
    this->ui->bombLineEdit->setText(QString::number(character.Bombs));
    this->ui->keyLineEdit->setText(QString::number(character.Keys));

    this->ui->pillCheckBox->setChecked(character.Pill == 1);
    this->ui->cardCheckBox->setChecked(character.Card > 0);
    this->ui->cardComboBox->setCurrentIndex(character.Card);

    //If character holds a trinket, get the trinkets name and loop through the ComboBox.
    //Once an index with the same name is found, set it.
    //This is used to make it work with both alphabetical sorting and not.
    if(character.Trinket > 0)
    {
        this->ui->trinketCheckBox->setChecked(true);
        QString trinket = GetKeyFromValue(trinketMap, character.Trinket);

        for(int i = 0; i < this->ui->trinketComboBox->count(); ++i)
            if(ui->trinketComboBox->itemText(i) == trinket)
                this->ui->trinketComboBox->setCurrentIndex(i);
    }
    else this->ui->trinketCheckBox->setChecked(false);

    //Almost the same thing, except this time with a spacebar item.
    if(character.Spacebar > 0)
    {
        QString spacebar = GetKeyFromValue(spacebarMap, character.Spacebar);

        for(int i = 0; i < this->ui->spacebarComboBox->count(); ++i)
            if(ui->spacebarComboBox->itemText(i) == spacebar)
                this->ui->spacebarComboBox->setCurrentIndex(i);
    }
    else this->ui->spacebarComboBox->setCurrentIndex(0);

    this->SetItems();
    this->ui->canShootCheckBox->setChecked(character.CanShoot);
}

void MainWindow::SetRedHearts(QString value)
{
    Character* character = &characterMap.at(currentCharacter);
    character->RedHearts = value.toInt();
    this->_draw.Health(this->_heartLabels, character->RedHearts, character->SoulHearts, character->BlackHearts,
                       currentCharacter == Characters::TheKeeper);
}

void MainWindow::SetSoulHearts(QString value)
{
    Character* character = &characterMap.at(currentCharacter);
    character->SoulHearts = value.toInt();
    this->_draw.Health(this->_heartLabels, character->RedHearts, character->SoulHearts, character->BlackHearts,
                       currentCharacter == Characters::TheKeeper);
}

void MainWindow::SetBlackHearts(QString value)
{
    Character* character = &characterMap.at(currentCharacter);
    character->BlackHearts = value.toInt();
    this->_draw.Health(this->_heartLabels, character->RedHearts, character->SoulHearts, character->BlackHearts,
                       currentCharacter == Characters::TheKeeper);
}

void MainWindow::SetCoins(QString value)
{
    Character* character = &characterMap.at(currentCharacter);
    character->Coins = value.toInt();
}

void MainWindow::SetBombs(QString value)
{
    Character* character = &characterMap.at(currentCharacter);
    character->Bombs = value.toInt();
}

void MainWindow::SetKeys(QString value)
{
    Character* character = &characterMap.at(currentCharacter);
    character->Keys = value.toInt();
}

void MainWindow::SetItems()
{
    Character* character = &characterMap.at(currentCharacter);
    this->ui->itemTextEdit->setPlainText(character->Items.join(", "));
}

void MainWindow::SetSpacebar(QString value)
{
    Character* character = &characterMap.at(currentCharacter);
    int spacebar = spacebarMap[value];
    character->Spacebar = spacebar;
    this->_draw.Spacebar(this->ui->spacebarImageLabel, spacebar);
    this->_draw.Charge(this->ui->chargeImageLabel, spacebar);
}

void MainWindow::SetCard(int cardIndex)
{
    Character* character = &characterMap.at(currentCharacter);
    character->Card = cardIndex;
    this->_draw.Card(this->ui->cardImageLabel, cardIndex);
}

void MainWindow::SetTrinket(QString value)
{
    Character* character = &characterMap.at(currentCharacter);
    int trinket = trinketMap[value];
    character->Trinket = trinket;
    this->_draw.Trinket(this->ui->trinketImageLabel, trinket);
}

void MainWindow::SetTears(int checkState)
{
    Character* character = &characterMap.at(currentCharacter);
    if(checkState == Qt::Checked) character->CanShoot = true;
    else if(checkState == Qt::Unchecked) character->CanShoot = false;
}

void MainWindow::PillCheckBoxChanged(int checkState)
{
    Character* character = &characterMap.at(currentCharacter);
    if(checkState == Qt::Checked)
    {
        if(this->ui->cardCheckBox->isChecked())
            this->ui->cardCheckBox->setChecked(false);
        character->Pill = 1;
        this->_draw.Pill(this->ui->cardImageLabel);
    }
    else if(checkState == Qt::Unchecked)
    {
        character->Pill = 0;
        this->ui->cardImageLabel->clear();
    }
}

void MainWindow::CardCheckBoxChanged(int checkState)
{
    if(checkState == Qt::Checked)
    {
        if(this->ui->pillCheckBox->isChecked())
            this->ui->pillCheckBox->setChecked(false);
        this->ui->cardComboBox->setEnabled(true);
    }
    else if(checkState == Qt::Unchecked)
    {
        this->ui->cardComboBox->setCurrentIndex(0);
        this->ui->cardComboBox->setEnabled(false);
    }
}

void MainWindow::TrinketCheckBoxChanged(int checkState)
{
    if(checkState == Qt::Checked)
        this->ui->trinketComboBox->setEnabled(true);
    else if(checkState == Qt::Unchecked)
    {
        this->ui->trinketComboBox->setCurrentIndex(0);
        this->ui->trinketComboBox->setEnabled(false);
    }
}

void MainWindow::SortCheckBoxChanged(int checkState)
{
    if(checkState == Qt::Checked) sortAlphabetically = true;
    else if(checkState == Qt::Unchecked) sortAlphabetically = false;
    GenerateComboBoxes();
}

void MainWindow::AfterbirthCheckBoxChanged(int checkState)
{
    if(checkState == Qt::Checked) afterbirthEnabled = true;
    else if(checkState == Qt::Unchecked)
    {
        afterbirthEnabled = false;
        //Enable tears for all Rebirth characters because canShoot is Afterbirth exclusive
        //Leave Afterbirth characters intact because they need Afterbirth enabled anyways.
        for(int i = 0; i < constants::REBIRTH_CHARACTER_COUNT; ++i)
            characterMap.at(static_cast<Characters>(i)).CanShoot = true;
    }
    GenerateCharacterComboBox();
    GenerateComboBoxes();
    this->ui->canShootCheckBox->setEnabled(afterbirthEnabled);
    this->ui->itemTextEdit->ProcessItems();
}

void MainWindow::PathTextEditChanged()
{
    this->_isaacPath = this->ui->pathTextEdit->toPlainText();
}

void MainWindow::RestoreDefaultPath()
{
    this->ui->pathTextEdit->setText(this->_defaultPath);
    QTextCursor cursor(this->ui->pathTextEdit->textCursor());
    cursor.movePosition(QTextCursor::End);
    this->ui->pathTextEdit->setTextCursor(cursor);
}

void MainWindow::CompassButtonClicked()
{
    //Sets the path text box to a directory selected by the user.
    QString dir = QFileDialog::getExistingDirectory(this,
        tr("Select your Isaac directory."),
        QDir::currentPath(),
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    this->ui->pathTextEdit->setPlainText(dir);

    QTextCursor cursor(this->ui->pathTextEdit->textCursor());
    cursor.movePosition(QTextCursor::End);
    this->ui->pathTextEdit->setTextCursor(cursor);
}

void MainWindow::NotepadButtonClicked()
{
    //Opens the file in a default text editor.
    if(QFile(this->_isaacPath + "/resources/players.xml").exists())
        QDesktopServices::openUrl(QUrl("file:///" + this->_isaacPath + "/resources/players.xml"));
    else QMessageBox(QMessageBox::Warning, "Information", "players.xml can't be opened.").exec();
}

void MainWindow::SetItemsButtonClicked()
{
    this->ui->itemTextEdit->ProcessItems();
}

void MainWindow::PurgeButtonClicked()
{
    XML(this->_isaacPath).DeleteXML();
}

void MainWindow::ReadButtonClicked()
{
    XML(this->_isaacPath).ReadXML();
}

void MainWindow::ExportButtonClicked()
{
    XML(this->_isaacPath).WriteXML();
}
