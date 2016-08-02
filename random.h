#pragma once

#include <random>
#include <QComboBox>

class Random
{
public:
    Random();
    int RandomInt(int);
    int RandomInt(int, int);
    void SetRandomComboBoxIndex(QComboBox*);
private:
    std::mt19937 _mt;
};
