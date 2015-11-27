#ifndef VARIABLES_H
#define VARIABLES_H

#include "character.h"
#include "constants.h"
#include <array>
#include <map>

extern bool afterbirthEnabled;

extern Character _isaac;
extern Character _maggy;
extern Character _cain;
extern Character _judas;
extern Character _blueBaby;
extern Character _eve;
extern Character _samson;
extern Character _azazel;
extern Character _lazarus;
extern Character _eden;
extern Character _theLost;
extern Character _lazarus2;
extern Character _blackJudas;
extern Character _lilith;
extern Character _theKeeper;

extern std::array<Character, constants::TOTAL_CHARACTER_COUNT> characterList;
extern std::map<Characters, Character> characterMap;
extern std::map<QString, int> trinketMap;

#endif // VARIABLES

