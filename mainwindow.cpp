#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>
#include "character.h"
#include "constants.h"
#include "variables.h"

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
    GenerateCardComboBox();
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

void MainWindow::GenerateCharacterComboBox()
{
    QStringList characterNames;
    for(int i = 0; i < constants::REBIRTH_CHARACTER_COUNT; ++i)
        characterNames.append(characterList.at(i).Name);
    if(afterbirthEnabled) for(int i = 0; i < constants::AFTERBIRTH_CHARACTER_COUNT; ++i)
        characterNames.append(characterList.at(constants::REBIRTH_CHARACTER_COUNT + i).Name);

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

void MainWindow::AfterbirthCheckBoxChanged(int checkState)
{
    if(checkState == Qt::Checked) afterbirthEnabled = true;
    else if(checkState == Qt::Unchecked) afterbirthEnabled = false;
    GenerateCharacterComboBox();
    GenerateCardComboBox();
}
