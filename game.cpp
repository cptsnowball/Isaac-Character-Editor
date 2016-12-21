#include "game.h"

QString StringFromGame(Game game)
{
    switch (game)
    {
        case Game::Rebirth:
            return "rebirth";
        case Game::Afterbirth:
            return "afterbirth";
        case Game::AfterbirthPlus:
            return "afterbirth+";
        case Game::Antibirth:
            return "antibirth";
        default:
            return "rebirth";
    }
}

Game GameFromString(QString string)
{
    if (string == "rebirth") return Game::Rebirth;
    else if (string == "afterbirth") return Game::Afterbirth;
    else if (string == "afterbirth+") return Game::AfterbirthPlus;
    else if (string == "antibirth") return Game::Antibirth;
    else return Game::Rebirth;
}
