#pragma once

#include "game.h"

#include <vector>
#include <QString>
#include <QStringList>

class Input
{
public:
    QStringList UserInputsList;
    QString Name;
    int ID;
    bool Spacebar = false;
    Game WhichGame = Game::Rebirth;
    static std::vector<Input> getPossibleUserInputs();
    void ShowInput();
private:
};
