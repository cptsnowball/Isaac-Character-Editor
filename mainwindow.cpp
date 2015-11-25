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
    ui->setupUi(this);

    ui->redHeartLineEdit->setValidator(this->_healthValidator);
    ui->soulHeartLineEdit->setValidator(this->_healthValidator);
    ui->blackHeartLineEdit->setValidator(this->_healthValidator);

    ui->coinLineEdit->setValidator(this->_consumableValidator);
    ui->bombLineEdit->setValidator(this->_consumableValidator);
    ui->keyLineEdit->setValidator(this->_consumableValidator);

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

    ui->characterComboBox->addItems(characterNames);
    this->_currentCharacter = Characters::Isaac;
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
    this->_currentCharacter = static_cast<Characters>(characterToSet);
    Character character = characterMap.at(this->_currentCharacter);
    this->_draw.Character(this->ui->characterImageLabel, this->_currentCharacter);
    this->_draw.Health(this->_heartLabels, character.RedHearts, character.SoulHearts, character.BlackHearts,
                       _currentCharacter == Characters::TheKeeper);

    this->ui->redHeartLineEdit->setText(QString::number(character.RedHearts));
    this->ui->soulHeartLineEdit->setText(QString::number(character.SoulHearts));
    this->ui->blackHeartLineEdit->setText(QString::number(character.BlackHearts));

    this->ui->coinLineEdit->setText(QString::number(character.Coins));
    this->ui->bombLineEdit->setText(QString::number(character.Bombs));
    this->ui->keyLineEdit->setText(QString::number(character.Keys));
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

void MainWindow::PillCheckBoxChanged(int checkState)
{
    if(checkState == Qt::Checked)
    {
        if(this->ui->cardCheckBox->isChecked())
            this->ui->cardCheckBox->setChecked(false);
        this->_draw.Card(this->ui->cardImageLabel, afterbirthEnabled, 1);
    }
    else if(checkState == Qt::Unchecked)
        this->_draw.Card(this->ui->cardImageLabel, afterbirthEnabled, 0);
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
    this->_draw.Card(this->ui->cardImageLabel, afterbirthEnabled, 0);
}
