#pragma once

#include <QString>

enum class Game {
    Rebirth,
    Afterbirth,
    AfterbirthPlus
};

QString StringFromGame(Game game);
Game GameFromString(QString string);
