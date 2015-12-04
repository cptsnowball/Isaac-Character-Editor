#include "character.h"

Character::Character(int setID, QString setName, QString setNameImage, QString setSkinFile,
                     QString setPortrait, QString setBigPortrait, int setSkinColor, int setCostume,
                     int setRedHearts, int setSoulHearts, int setBlackHearts, int setCoins,
                     int setBombs, int setKeys, int setPill, int setCard, int setTrinket,
                     int setSpacebar, bool setCanShoot, QStringList setItems) :
    ID(setID), Name(setName), NameImage(setNameImage), SkinFile(setSkinFile),
    Portrait(setPortrait),  BigPortrait(setBigPortrait), SkinColor(setSkinColor),
    Costume(setCostume), RedHearts(setRedHearts), SoulHearts(setSoulHearts),
    BlackHearts(setBlackHearts), Coins(setCoins), Bombs(setBombs), Keys(setKeys),
    Pill(setPill), Card(setCard), Trinket(setTrinket), Spacebar(setSpacebar),
    CanShoot(setCanShoot), Items(setItems)
{

}

Character::Character() {}
