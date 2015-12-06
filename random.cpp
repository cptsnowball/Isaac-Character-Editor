#include "random.h"
#include <ctime>

Random::Random()
{
    this->_mt.seed(time(0));
}

int Random::RandomInt(int max)
{
    std::uniform_int_distribution<int> distribution(1, max);
    return distribution(this->_mt);
}

int Random::RandomInt(int min, int max)
{
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(this->_mt);
}

void Random::SetRandomComboBoxIndex(QComboBox* comboBox)
{
    comboBox->setCurrentIndex(RandomInt(0, comboBox->count() - 1));
}
