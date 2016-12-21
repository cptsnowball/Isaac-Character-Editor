#pragma once

#include <QString>

enum class Game {
    Rebirth,
    Afterbirth,
    AfterbirthPlus,
    Antibirth
};

QString StringFromGame(Game game);
Game GameFromString(QString string);
