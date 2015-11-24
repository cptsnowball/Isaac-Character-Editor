#ifndef VARIABLES
#define VARIABLES

#include "character.h"
#include "constants.h"
#include <array>
#include <map>

bool afterbirthEnabled = true;

Character _isaac(0, "Isaac", "PlayerName_01_Isaac.png", "Character_001_Isaac.png", "PlayerPortrait_01_Isaac.png", "PlayerPortraitBig_01_Isaac.png",
                 -1, 0, 6, 0, 0, 0, 1, 0, 0, 0, 0, 105, true, QStringList {});
Character _maggy(1, "Magdalene", "PlayerName_02_Magdalene.png", "Character_002_Magdalene.png", "PlayerPortrait_02_Magdalene.png", "PlayerPortraitBig_02_Magdalene.png",
                -1, 7, 8, 0, 0, 0, 0, 0, 0, 0, 0, 45, true, QStringList {});
Character _cain(2, "Cain", "PlayerName_03_Cain.png", "Character_003_Cain.png", "PlayerPortrait_03_Cain.png", "PlayerPortraitBig_03_Cain.png",
                -1, 8, 4, 0, 0, 0, 0, 1, 0, 0, 19, 0, true, QStringList {"Lucky Foot"});
Character _judas(3, "Judas", "PlayerName_04_Judas.png", "Character_004_Judas.png", "PlayerPortrait_04_Judas.png", "PlayerPortraitBig_04_Judas.png",
                 -1, 9, 2, 0, 0, 3, 0, 0, 0, 0, 0, 34, true, QStringList {});
Character _blueBaby(4, "???", "PlayerName_06_BlueBaby.png", "Character_006_Bluebaby.png", "PlayerPortrait_06_BlueBaby.png", "PlayerPortraitBig_06_Bluebaby.png",
                    2, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 36, true, QStringList {});
Character _eve(5, "Eve", "PlayerName_05_Eve.png", "Character_005_Eve.png", "PlayerPortrait_05_Eve.png", "PlayerPortraitBig_05_Eve.png",
               -1, 10, 4, 0, 0, 0, 0, 0, 0, 0, 0, 126, true, QStringList {"Dead Bird", "Whore of Babylon"});
Character _samson(6, "Samson", "PlayerName_07_Samson.png", "Character_007_Samson.png", "PlayerPortrait_07_Samson.png", "PlayerPortraitBig_07_Samson.png",
                  -1, 13, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, true, QStringList {"Bloody Lust"});
Character _azazel(7, "Azazel", "PlayerName_08_Azazel.png", "Character_008_Azazel.png", "PlayerPortrait_08_Azazel.png", "PlayerPortraitBig_08_Azazel.png",
                  1, 11, 0, 0, 6, 0, 0, 0, 0, 1, 0, 0, true, QStringList {});
Character _lazarus(8, "Lazarus", "PlayerName_10_Lazarus.png", "Character_009_Lazarus.png", "PlayerPortrait_09_Lazarus.png", "PlayerPortraitBig_09_Lazarus.png",
                   -1, 32, 6, 0, 0, 0, 0, 0, 1, 0, 0, 0, true, QStringList {});
Character _eden(9,  "Eden", "PlayerName_09_Eden.png", "Character_009_Eden.png", "PlayerPortrait_09_Eden.png", "PlayerPortraitBig_09_Eden.png",
                -1, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, true, QStringList {});
Character _theLost(10, "The Lost", "PlayerName_12_TheLost.png", "Character_012_TheLost.png", "PlayerPortrait_12_TheLost.png", "PlayerPortraitBig_12_TheLost.png",
                   0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 284, true, QStringList {"Holy Mantle"});
Character _lazarus2(11, "Lazarus II", "PlayerName_10_Lazarus.png", "Character_010_Lazarus2.png", "PlayerPortrait_10_Lazarus2.png", "PlayerPortraitBig_10_Lazarus2.png",
                    -1, 33, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, true, QStringList {"Anemic"});
Character _blackJudas(12, "Black Judas", "PlayerName_04_Judas.png", "Character_013_BlackJudas.png", "PlayerPortrait_BlackJudas.png", "PlayerPortraitBig_BlackJudas.png",
                      1, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, true, QStringList {});
Character _lilith(13, "Lilith", "PlayerName_13_Lilith.png", "Character_014_Lilith.png", "PlayerPortrait_13_Lilith.png", "PlayerPortraitBig_Lilith.png",
                  1, 34, 2, 0, 4, 0, 0, 0, 0, 0, 0, 357, false, QStringList {"Cambion Conception"});
Character _theKeeper(14, "The Keeper", "PlayerName_14_TheKeeper.png", "Character_015_Keeper.png", "PlayerPortrait_14_Keeper.png", "PlayerPortraitBig_Keeper.png",
                     -1, 0, 4, 0, 0, 1, 1, 0, 0, 0, 83, 349, true, QStringList {});

std::array<Character, constants::TOTAL_CHARACTER_COUNT> characterList {
    _isaac, _maggy, _cain, _judas, _blueBaby, _eve, _samson, _azazel, _lazarus, _eden, _theLost, _lazarus2, _blackJudas, _lilith, _theKeeper
};

std::map<Characters, Character> characterMap {
    {Characters::Isaac, _isaac},
    {Characters::Maggy, _maggy},
    {Characters::Cain, _cain},
    {Characters::Judas, _judas},
    {Characters::BlueBaby, _blueBaby},
    {Characters::Eve, _eve},
    {Characters::Samson, _samson},
    {Characters::Azazel, _azazel},
    {Characters::Lazarus, _lazarus},
    {Characters::Eden, _eden},
    {Characters::TheLost, _theLost},
    {Characters::Lazarus2, _lazarus2},
    {Characters::BlackJudas, _blackJudas},
    {Characters::Lilith, _lilith},
    {Characters::TheKeeper, _theKeeper}
};

#endif // VARIABLES

