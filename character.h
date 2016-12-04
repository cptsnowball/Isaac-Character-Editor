#pragma once

#include <QString>
#include <QStringList>

enum class Characters : int {
    Isaac = 0, Maggy, Cain, Judas, BlueBaby, Eve, Samson, Azazel, Lazarus, Eden, TheLost, Lazarus2, BlackJudas, Lilith, TheKeeper, Apollyon
};

class Character
{
public:
    Character();
    Character(int, QString, QString, QString, QString, QString, int, int, int, int, int, int, int, int, int, int, int, int, bool, QStringList = {});
    int ID;
    QString Name, NameImage, SkinFile;
    QString Portrait, BigPortrait;
    int SkinColor, Costume;
    int RedHearts, SoulHearts, BlackHearts;
    int Coins, Bombs, Keys;
    int Pill, Card, Trinket;
    int Spacebar;
    bool CanShoot;
    QStringList Items;
};
