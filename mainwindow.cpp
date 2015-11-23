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

    QApplication::setWindowIcon(QIcon(":Resources/Icons/PurpleKey.ico"));

    setWindowTitle(constants::TITLE + " " + constants::VERSION);

    QPixmap background(":/Resources/Background/Background.png");
    QPixmap overlay(":/Resources/Background/BackgroundOverlay.png");
    QPixmap whoAmI(":/Resources/Background/WhoAmI.png");

    QPixmap result(background.size());

    result.fill(Qt::transparent);
    {
        QPainter painter(&result);
        painter.drawPixmap(0, 0, background);
        painter.drawPixmap(0, 0, overlay);
        painter.drawPixmap(224, 10, whoAmI);
    }

    result = result.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, result);
    this->setPalette(palette);

    GenerateCharacterComboBox();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::GenerateCharacterComboBox()
{
    QStringList characterNames;
    for(int i = 0; i < constants::REBIRTH_CHARACTER_COUNT; ++i)
        characterNames.append(characterList.at(i).Name);
    for(int i = 0; i < constants::AFTERBIRTH_CHARACTER_COUNT; ++i)
        characterNames.append(characterList.at(constants::REBIRTH_CHARACTER_COUNT + i).Name);
    ui->characterComboBox->addItems(characterNames);

    currentCharacter = Characters::Isaac;
}

void MainWindow::DrawCharacter(int characterToDraw)
{
    this->_draw.Character(&this->ui->characterImageLabel, characterToDraw);
}
