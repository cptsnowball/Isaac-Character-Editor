#pragma once

#include <ctime>
#include <random>
#include <type_traits>
#include <QComboBox>

template<class IntType>
struct Random
{
    static_assert(std::is_integral<IntType>::value, "Random<IntType>: type must be integral.");
public:
    Random(std::time_t seed = std::time(nullptr))
    {
        this->_mt.seed(seed);
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



