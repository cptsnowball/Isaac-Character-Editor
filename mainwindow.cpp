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
    ui->characterComboBox->setFont(this->_font);
    ui->healthLabel->setFont(this->_font);
    ui->consumablesLabel->setFont(this->_font);

    ui->redHeartLineEdit->setFont(this->_font);
    ui->soulHeartLineEdit->setFont(this->_font);
    ui->blackHeartLineEdit->setFont(this->_font);

    ui->coinLineEdit->setFont(this->_font);
    ui->bombLineEdit->setFont(this->_font);
    ui->keyLineEdit->setFont(this->_font);

    ui->redHeartLineEdit->setValidator(this->_healthValidator);
    ui->soulHeartLineEdit->setValidator(this->_healthValidator);
    ui->blackHeartLineEdit->setValidator(this->_healthValidator);

    ui->coinLineEdit->setValidator(this->_consumableValidator);
    ui->bombLineEdit->setValidator(this->_consumableValidator);
    ui->keyLineEdit->setValidator(this->_consumableValidator);

    QApplication::setWindowIcon(QIcon(":Resources/Icons/PurpleKey.ico"));
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
    for(int i = 0; i < constants::AFTERBIRTH_CHARACTER_COUNT; ++i)
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
}
