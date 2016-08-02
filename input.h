#pragma once

#include <QString>
#include <QStringList>
#include <vector>

class Input
{
public:
    QStringList UserInputsList;
    QString Name;
    int ID;
    bool Spacebar = false;
    bool Afterbirth = false;
    static std::vector<Input> getPossibleUserInputs();
    void ShowInput();
private:
};
