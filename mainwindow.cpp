#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>
#include <QMessageBox>
#include "character.h"
#include "constants.h"
#include "functions.h"
#include "variables.h"
#include "xml.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _draw()
{
    this->ui->setupUi(this);

    this->ui->redHeartLineEdit->setValidator(this->_healthValidator);
    this->ui->soulHeartLineEdit->setValidator(this->_healthValidator);
    this->ui->blackHeartLineEdit->setValidator(this->_healthValidator);

    this->ui->coinLineEdit->setValidator(this->_consumableValidator);
    this->ui->bombLineEdit->setValidator(this->_consumableValidator);
    this->ui->keyLineEdit->setValidator(this->_consumableValidator);

    this->ui->pathTextEdit->setText(this->_defaultPath);

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

void MainWindow::GenerateComboBoxes()
{
    //Character ComboBox is excluded because it's only supposed to be called
    //when a character's name is changed and Afterbirth is enabled/disabled.

    GenerateCardComboBox();
    GenerateTrinketComboBox();
    //GenerateSpacebarComboBox();
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

    this->ui->cardComboBox->clear();
    this->ui->cardComboBox->addItems(cardList);
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

    this->ui->trinketComboBox->clear();
    this->ui->trinketComboBox->addItems(trinketList);
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
    if(characterToSet == -1) return;

    this->_currentCharacter = static_cast<Characters>(characterToSet);
    Character character = characterMap.at(this->_currentCharacter);
    this->_draw.Character(this->ui->characterImageLabel, this->_currentCharacter);
    this->_draw.Health(this->_heartLabels, character.RedHearts, character.SoulHearts, character.BlackHearts,
                       _currentCharacter == Characters::TheKeeper);

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
    //Once an index with the same name is find, set it.
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
}

void MainWindow::SetRedHearts(QString value)
{
    Character* character = &characterMap.at(this->_currentCharacter);
    character->RedHearts = value.toInt();
    this->_draw.Health(this->_heartLabels, character->RedHearts, character->SoulHearts, character->BlackHearts,
                       _currentCharacter == Characters::TheKeeper);
}

void MainWindow::SetSoulHearts(QString value)
{
    Character* character = &characterMap.at(this->_currentCharacter);
    character->SoulHearts = value.toInt();
    this->_draw.Health(this->_heartLabels, character->RedHearts, character->SoulHearts, character->BlackHearts,
                       _currentCharacter == Characters::TheKeeper);
}

void MainWindow::SetBlackHearts(QString value)
{
    Character* character = &characterMap.at(this->_currentCharacter);
    character->BlackHearts = value.toInt();
    this->_draw.Health(this->_heartLabels, character->RedHearts, character->SoulHearts, character->BlackHearts,
                       _currentCharacter == Characters::TheKeeper);
}

void MainWindow::SetCoins(QString value)
{
    Character* character = &characterMap.at(this->_currentCharacter);
    character->Coins = value.toInt();
}

void MainWindow::SetBombs(QString value)
{
    Character* character = &characterMap.at(this->_currentCharacter);
    character->Bombs = value.toInt();
}

void MainWindow::SetKeys(QString value)
{
    Character* character = &characterMap.at(this->_currentCharacter);
    character->Keys = value.toInt();
}

void MainWindow::SetCard(int cardIndex)
{
    Character* character = &characterMap.at(this->_currentCharacter);
    character->Card = cardIndex;
    this->_draw.Card(this->ui->cardImageLabel, cardIndex);
}

void MainWindow::SetTrinket(QString value)
{
    Character* character = &characterMap.at(this->_currentCharacter);
    int trinket = trinketMap[value];
    character->Trinket = trinket;
    this->_draw.Trinket(this->ui->trinketImageLabel, trinket);
}

void MainWindow::PillCheckBoxChanged(int checkState)
{
    Character* character = &characterMap.at(this->_currentCharacter);
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
    else if(checkState == Qt::Unchecked) afterbirthEnabled = false;
    GenerateCharacterComboBox();
    GenerateComboBoxes();
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

void MainWindow::PurgeButtonClicked()
{
    XML(this->_isaacPath).DeleteXML();
}

void MainWindow::ReadButtonClicked()
{
    //pass
}

void MainWindow::ExportButtonClicked()
{
    XML(this->_isaacPath).WriteXML();
}
