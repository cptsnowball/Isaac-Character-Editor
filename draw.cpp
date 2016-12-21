#include "draw.h"

#include "functions.h"
#include "variables.h"

#include <QBitmap>
#include <QLabel>
#include <QMessageBox>
#include <QPixmap>

Draw::Draw() { }

Draw::~Draw() { }

void Draw::PixmapToLabel(QLabel* label, const QString &filename)
{
    QPixmap pixmap(filename);
    label->setPixmap(pixmap);
    label->setMask(pixmap.mask());
    label->show();
}

void Draw::Character(QLabel* characterImageLabel, Characters characterToDraw)
{
    QString character;

    switch(characterToDraw)
    {
    case Characters::Isaac:
        character = ":/Resources/Characters/Isaac.png";
        break;
    case Characters::Maggy:
        character = ":/Resources/Characters/Maggy.png";
        break;
    case Characters::Cain:
        character = ":/Resources/Characters/Cain.png";
        break;
    case Characters::Judas:
        character = ":/Resources/Characters/Judas.png";
        break;
    case Characters::BlueBaby:
        character = ":/Resources/Characters/BlueBaby.png";
        break;
    case Characters::Eve:
        character = ":/Resources/Characters/Eve.png";
        break;
    case Characters::Samson:
        character = ":/Resources/Characters/Samson.png";
        break;
    case Characters::Azazel:
        character = ":/Resources/Characters/Azazel.png";
        break;
    case Characters::Lazarus:
        character = ":/Resources/Characters/Lazarus.png";
        break;
    case Characters::Eden:
        character = ":/Resources/Characters/Eden.png";
        break;
    case Characters::TheLost:
        character = ":/Resources/Characters/TheLost.png";
        break;
    case Characters::Lazarus2:
        character = ":/Resources/Characters/Lazarus2.png";
        break;
    case Characters::BlackJudas:
        character = ":/Resources/Characters/BlackJudas.png";
        break;
    case Characters::Lilith:
        character = ":/Resources/Characters/Lilith.png";
        break;
    case Characters::TheKeeper:
        character = ":/Resources/Characters/TheKeeper.png";
        break;
    case Characters::Apollyon:
        character = ":/Resources/Characters/Isaac.png";
        break;
    case Characters::Bethany:
        character = ":/Resources/Characters/Bethany.png";
        break;
    case Characters::Jacob:
        character = ":/Resources/Characters/Jacob.png";
        break;
    case Characters::Esau:
        character = ":/Resources/Characters/Esau.png";
        break;
    default:
        character = ":/Resources/Characters/Isaac.png";
        break;
    }

    PixmapToLabel(characterImageLabel, character);
}

void Draw::Health(std::array<QLabel*, 12> heartLabels, int redHearts, int soulHearts, int blackHearts, bool isKeeper)
{
    for(int i = 0; i < 12; ++i) heartLabels.at(i)->clear();

    if(isKeeper)
    {
        int drawnHealth = 0;
        for(int i = 0; i < 12; ++i)
        {
            if(drawnHealth >= 4) break;

            if(redHearts > 1)
            {
                PixmapToLabel(heartLabels.at(i), ":/Resources/Health/CoinHeartFull.png");
                redHearts -= 2;
                drawnHealth += 2;
            }
            else if(redHearts == 1)
            {
                PixmapToLabel(heartLabels.at(i), ":/Resources/Health/CoinHeartHalf.png");
                redHearts -= 1;
                drawnHealth += 1;
            }
            else if(soulHearts > 1 && drawnHealth < 3)
            {
                PixmapToLabel(heartLabels.at(i), ":/Resources/Health/SoulHeartFull.png");
                soulHearts -= 2;
                drawnHealth += 2;
            }
            else if((soulHearts == 1 || soulHearts > 1) && drawnHealth >= 3)
            {
                PixmapToLabel(heartLabels.at(i), ":/Resources/Health/SoulHeartHalf.png");
                soulHearts -= 1;
                drawnHealth += 1;
            }
            else if(blackHearts > 1 && drawnHealth < 3)
            {
                PixmapToLabel(heartLabels.at(i), ":/Resources/Health/BlackHeartFull.png");
                blackHearts -= 2;
                drawnHealth += 2;
            }
            else if((blackHearts == 1 || blackHearts > 1) && drawnHealth >= 3)
            {
                PixmapToLabel(heartLabels.at(i), ":/Resources/Health/BlackHeartHalf.png");
                blackHearts -= 1;
                drawnHealth += 1;
            }
        }
        return;
    }

    for(int i = 0; i < 12; ++i)
    {
        if(redHearts > 1)
        {
            PixmapToLabel(heartLabels.at(i), ":/Resources/Health/RedHeartFull.png");
            redHearts -= 2;
        }
        else if(redHearts == 1)
        {
            PixmapToLabel(heartLabels.at(i), ":/Resources/Health/RedHeartHalf.png");
            redHearts -= 1;
        }
        else if(soulHearts > 1)
        {
            PixmapToLabel(heartLabels.at(i), ":/Resources/Health/SoulHeartFull.png");
            soulHearts -= 2;
        }
        else if(soulHearts == 1)
        {
            PixmapToLabel(heartLabels.at(i), ":/Resources/Health/SoulHeartHalf.png");
            soulHearts -= 1;
        }
        else if(blackHearts > 1)
        {
            PixmapToLabel(heartLabels.at(i), ":/Resources/Health/BlackHeartFull.png");
            blackHearts -= 2;
        }
        else if(blackHearts == 1)
        {
            PixmapToLabel(heartLabels.at(i), ":/Resources/Health/BlackHeartHalf.png");
            blackHearts -= 1;
        }
    }
}

void Draw::Spacebar(QLabel* spacebarImageLabel, int spacebarID)
{
    PixmapToLabel(spacebarImageLabel, QString(":/Resources/Spacebar/Spacebar_%1.png").arg(spacebarID));
}

void Draw::Charge(QLabel* chargeLabel, int spacebarID)
{
    const std::vector<int> charge1IDs = { 36, 38, 111, 127, 145, 164, 285, 289, 298, 294, 338, 349, 352, 383, 427, 1029, 1051, 1082 };
    const std::vector<int> charge2IDs = { 37, 44, 56, 66, 107, 171, 175, 192, 288, 421, 422, 1004, 1031, 1067, 1078};
    const std::vector<int> charge3IDs = {
                    34, 39, 41, 42, 47, 49, 58, 65, 86, 123, 136, 147, 351, 382, 386, 437,
                    1003, 1012, 1013, 1027, 1052, 1056
                };
    const std::vector<int> charge4IDs = { 45, 97, 124, 160, 286, 348, 357, 406, 419, 439, 1025, 1086};
    const std::vector<int> charge6IDs = {
                    33, 35, 77, 78, 83, 84, 85, 93, 102, 105, 130, 146, 158, 166, 181, 283, 284, 287,
                    291, 292, 293, 323, 324, 325, 326, 1015, 1032, 1072, 1089
                };
    const std::vector<int> charge12IDs = {441};

    if(VectorContains(charge1IDs, spacebarID)) PixmapToLabel(chargeLabel, ":/Resources/Charge/Charge1.png");
    else if(VectorContains(charge2IDs, spacebarID)) PixmapToLabel(chargeLabel, ":/Resources/Charge/Charge2.png");
    else if(VectorContains(charge3IDs, spacebarID)) PixmapToLabel(chargeLabel, ":/Resources/Charge/Charge3.png");
    else if(VectorContains(charge4IDs, spacebarID)) PixmapToLabel(chargeLabel, ":/Resources/Charge/Charge4.png");
    else if(VectorContains(charge6IDs, spacebarID)) PixmapToLabel(chargeLabel, ":/Resources/Charge/Charge6.png");
    else if(VectorContains(charge12IDs, spacebarID)) PixmapToLabel(chargeLabel, ":/Resources/Charge/Charge12.png");
    else chargeLabel->clear();
}

void Draw::Pill(QLabel* cardImageLabel)
{
    int pills = (game == Game::Afterbirth || game == Game::AfterbirthPlus) ? constants::TotalPillCount : constants::RebirthPillCount;
    QString pillToDraw = QString(":/Resources/Cards/Pill%1.png").arg(this->_rng.RandomInt(pills));
    PixmapToLabel(cardImageLabel, pillToDraw);
    this->DrawnPill = pillToDraw.toInt();
}

void Draw::Card(QLabel* cardImageLabel, int cardIndex)
{
    QString rune = QString(":/Resources/Cards/Rune%1.png").arg(this->_rng.RandomInt(constants::RuneCount));
    if (cardIndex == 0) cardImageLabel->clear();
    else if (cardIndex > 40 && game == Game::Antibirth) PixmapToLabel(cardImageLabel, ":/Resources/Cards/Rune1x.png");
    else if (cardIndex > 0 && cardIndex <= 22) PixmapToLabel(cardImageLabel, ":/Resources/Cards/TarotCard.png");
    else if (cardIndex >= 23 && cardIndex <= 27) PixmapToLabel(cardImageLabel, ":/Resources/Cards/PlayingCard.png");
    else if (cardIndex >= 36 && cardIndex <= 43)
    {
        //Attention to detail added only by Antibirth
        if (game == Game::Antibirth)
        {
            if (cardIndex == 36) PixmapToLabel(cardImageLabel, ":/Resources/Cards/ChaosCard.png");
            else if (cardIndex == 37) PixmapToLabel(cardImageLabel, ":/Resources/Cards/CreditCard.png");
            else if (cardIndex == 39) PixmapToLabel(cardImageLabel, ":/Resources/Cards/CardAgainstHumanity.png");
        }
        else if ((game == Game::Afterbirth || game == Game::AfterbirthPlus) && cardIndex == 36) PixmapToLabel(cardImageLabel, rune);
        else PixmapToLabel(cardImageLabel, ":/Resources/Cards/PlayingCard.png");
    }
    else if (cardIndex >= 28 && cardIndex <= 35) PixmapToLabel(cardImageLabel, rune);
    else if (cardIndex == 44) PixmapToLabel(cardImageLabel, ":/Resources/Cards/DiceShard.png");
    else if (cardIndex == 45) PixmapToLabel(cardImageLabel, ":/Resources/Cards/EmergencyContact.png");
}

void Draw::Trinket(QLabel* trinketImageLabel, int trinketID)
{
    if(trinketID == 0) trinketImageLabel->clear();
    else PixmapToLabel(trinketImageLabel, QString(":/Resources/Trinkets/Trinket_%1.png").arg(QString::number(trinketID)));
}

void Draw::Familiar(QLabel* familiarImageLabel, std::vector<int> itemIDs) {
    const std::vector<int> possibleFamiliars {
        //Shooters
        8, 113, 88, 99, 100, 95, 67, 188, 163, 167, 174, 267, 269, 322, 275,
        //Spawners
        131, 94, 96, 98, 144, 266, 271, 278,
        //Orbitals
        128, 57, 112, 10, 172, 264, 274, 207, 73, 279,
        //Followers
        265, 270, 273, 276, 277, 280, 281, 319, 320,
        //Other
        11, 81, 178, 187,
        //Afterbirth
        360, 361, 362, 363, 364, 365, 372, 384, 385, 387, 388, 389, 390, 403, 404, 405,
        417, 426, 430, 431, 435, 436,
        //Sample for trinket familiars and Super Bum.
        997, 998, 999,
        //Antibirth
        1014, 1016, 1028, 1034, 1054, 1055, 1059, 1062, 1076, 1092
    };

    //Create a vector that contains the IDs for the available familiars.
    std::vector<int> familiars;
    for (const int itemID : itemIDs)
    {
        if (VectorContains(possibleFamiliars, itemID))
            familiars.push_back(itemID);
    }

    if (trinketComboBoxPtr->currentText() == "Isaac's Head") familiars.push_back(997);
    if (trinketComboBoxPtr->currentText() == "\?\?\?'s Soul") familiars.push_back(998);
    if (currentCharacter == Characters::Lilith) familiars.push_back(360);
    if (VectorContains(familiars, 144) && VectorContains(familiars, 278) && VectorContains(familiars, 388))
    {
        RemoveValueFromVector(familiars, 144);
        RemoveValueFromVector(familiars, 278);
        RemoveValueFromVector(familiars, 388);
        familiars.push_back(999);
    }

    if (familiars.empty())
    {
        familiarImageLabel->clear();
        return;
    }

    int familiarToDraw = familiars.at(this->_rng.RandomInt(0, familiars.size() - 1));
    if (familiarToDraw == 405)
        PixmapToLabel(familiarImageLabel, QString(":/Resources/Familiars/Familiar_%1_%2.png").arg(familiarToDraw, this->_rng.RandomInt(1, 4)));
    else PixmapToLabel(familiarImageLabel, QString(":/Resources/Familiars/Familiar_%1.png").arg(familiarToDraw));
}
