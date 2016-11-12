#pragma once

#include "character.h"
#include "constants.h"
#include "input.h"
#include "mainwindow.h"
#include "png.h"

#include <array>
#include <map>
#include <vector>
#include <QComboBox>

extern bool afterbirthEnabled;
extern bool godmodeEnabled;
extern bool nameImagesEnabled;
extern bool sortAlphabetically;
extern bool vaporwaveAesthetics;

extern Characters currentCharacter;

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

extern std::array<Character, constants::TotalCharacterCount> characterList;
extern std::map<Characters, Character> characterMap;
extern std::map<QString, int> spacebarMap;
extern std::map<QString, int> trinketMap;
extern std::map<Characters, QString> defaultNames;
extern std::map<Characters, QPoint> charSelectMenuOffsets;

extern std::vector<Input> possibleInputs;

//Needed to set the selected spacebar item outside of the MainWindow class.
//Probably a terrible work around.
extern QComboBox* spacebarComboBoxPtr;

//Needed to access from Draw::Familiar()
extern QComboBox* trinketComboBoxPtr;

//Used to access DrawBackground() outside of MainWindow.
extern MainWindow* mainWindowPtr;
