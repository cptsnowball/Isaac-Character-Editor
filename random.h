#pragma once

#include <ctime>
#include <random>
#include <type_traits>
#include <QComboBox>

template<class IntType, typename std::enable_if<std::is_integral<IntType>::value>::type* = nullptr>
struct Random
{
public:
    Random()
    {
        this->_mt.seed(std::time(nullptr));
    }

    IntType RandomInt(IntType max)
    {
        std::uniform_int_distribution<IntType> distribution(1, max);
        return distribution(this->_mt);
    }

    IntType RandomInt(IntType min, IntType max)
    {
        std::uniform_int_distribution<IntType> distribution(min, max);
        return distribution(this->_mt);
    }

    void SetRandomComboBoxIndex(QComboBox* comboBox)
    {
        comboBox->setCurrentIndex(RandomInt(0, comboBox->count() - 1));
    }
private:
    std::mt19937 _mt;
};



