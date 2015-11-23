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
        character = QPixmap(":/Characters/Isaac.png");
        break;
    case Characters::Maggy:
        character = QPixmap(":/Characters/Maggy.png");
        break;
    case Characters::Cain:
        character = QPixmap(":/Characters/Cain.png");
        break;
    case Characters::Judas:
        character = QPixmap(":/Characters/Judas.png");
        break;
    case Characters::BlueBaby:
        character = QPixmap(":/Characters/BlueBaby.png");
        break;
    case Characters::Eve:
        character = QPixmap(":/Characters/Eve.png");
        break;
    case Characters::Samson:
        character = QPixmap(":/Characters/Samson.png");
        break;
    case Characters::Azazel:
        character = QPixmap(":/Characters/Azazel.png");
        break;
    case Characters::Lazarus:
        character = QPixmap(":/Characters/Lazarus.png");
        break;
    case Characters::Eden:
        character = QPixmap(":/Characters/Eden.png");
        break;
    case Characters::TheLost:
        character = QPixmap(":/Characters/TheLost.png");
        break;
    case Characters::Lazarus2:
        character = QPixmap(":/Characters/Lazarus2.png");
        break;
    case Characters::BlackJudas:
        character = QPixmap(":/Characters/BlackJudas.png");
        break;
    case Characters::Lilith:
        character = QPixmap(":/Characters/Lilith.png");
        break;
    case Characters::TheKeeper:
        character = QPixmap(":/Characters/TheKeeper.png");
        break;
    default:
        character = QPixmap(":/Characters/Isaac.png");
        break;
    }

    characterImageLabel[0]->setPixmap(character);
    characterImageLabel[0]->setMask(character.mask());
    characterImageLabel[0]->show();
}
