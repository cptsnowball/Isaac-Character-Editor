#ifndef INPUT_H
#define INPUT_H

#include <QString>
#include <QStringList>
#include <vector>

class Input
{
public:
    QStringList UserInputsList;
    QString Name;
    int ID;
    bool Afterbirth = false;
    static std::vector<Input> getPossibleUserInputs();
    void ShowInput();
private:
};

#endif // INPUT_H
