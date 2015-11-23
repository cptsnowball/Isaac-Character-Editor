#include "draw.h"

#include "character.h"
#include <QBitmap>
#include <QLabel>
#include <QPixmap>

Draw::Draw() { }

Draw::~Draw() { }

void Draw::Character(QLabel **characterImageLabel, int selectedIndex)
{
    QPixmap character;
    Characters characterToDraw = static_cast<Characters>(selectedIndex);

    switch(characterToDraw)
    {
    case Characters::Isaac:
        character = QPixmap(":/Resources/Characters/Isaac.png");
        break;
    case Characters::Maggy:
        character = QPixmap(":/Resources/Characters/Maggy.png");
        break;
    case Characters::Cain:
        character = QPixmap(":/Resources/Characters/Cain.png");
        break;
    case Characters::Judas:
        character = QPixmap(":/Resources/Characters/Judas.png");
        break;
    case Characters::BlueBaby:
        character = QPixmap(":/Resources/Characters/BlueBaby.png");
        break;
    case Characters::Eve:
        character = QPixmap(":/Resources/Characters/Eve.png");
        break;
    case Characters::Samson:
        character = QPixmap(":/Resources/Characters/Samson.png");
        break;
    case Characters::Azazel:
        character = QPixmap(":/Resources/Characters/Azazel.png");
        break;
    case Characters::Lazarus:
        character = QPixmap(":/Resources/Characters/Lazarus.png");
        break;
    case Characters::Eden:
        character = QPixmap(":/Resources/Characters/Eden.png");
        break;
    case Characters::TheLost:
        character = QPixmap(":/Resources/Characters/TheLost.png");
        break;
    case Characters::Lazarus2:
        character = QPixmap(":/Resources/Characters/Lazarus2.png");
        break;
    case Characters::BlackJudas:
        character = QPixmap(":/Resources/Characters/BlackJudas.png");
        break;
    case Characters::Lilith:
        character = QPixmap(":/Resources/Characters/Lilith.png");
        break;
    case Characters::TheKeeper:
        character = QPixmap(":/Resources/Characters/TheKeeper.png");
        break;
    default:
        character = QPixmap(":/Resources/Characters/Isaac.png");
        break;
    }

    characterImageLabel[0]->setPixmap(character);
    characterImageLabel[0]->setMask(character.mask());
    characterImageLabel[0]->show();
}
