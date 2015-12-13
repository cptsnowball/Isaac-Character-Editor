#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <algorithm>
#include <iterator>
#include <map>
#include <stdexcept>
#include <vector>
#include <QStringList>
#include "input.h"
#include "variables.h"

template<typename Key, typename Value>
Key GetKeyFromValue(const std::map<Key, Value> &map, const Value &valueToFind) {
    for (const auto& keyValuePair : map)
    {
        if(keyValuePair.second == valueToFind) return keyValuePair.first;
        else continue;
    }
    //If a key wasn't found, throw an exception.
    //Should never happen if the maps are properly defined.
    throw std::invalid_argument("Value does not have a key!");
}

template<typename T>
inline bool SortedVectorContains(const std::vector<T> &vector, const T &value)
{
    //Returns true if the vector contains the value and false otherwise.
    //Vector has to be sorted for it to work, use VectorContains otherwise.
    return std::binary_search(vector.begin(), vector.end(), value);
}

template<typename T>
inline bool VectorContains(const std::vector<T> &vector, const T &value)
{
    //Returns true if the vector contains the value and false otherwise.
    return std::find(vector.begin(), vector.end(), value) != vector.end();
}

template<typename T>
inline void RemoveValueFromVector(std::vector<T> &vector, const T value)
{
    vector.erase(std::remove(vector.begin(), vector.end(), value), vector.end());
}

std::vector<int> GetItemIDsFromItemList(QStringList itemList);
QStringList GetItemNamesFromItemList(QStringList itemList, bool sideEffects = true);
QStringList SimplifyItemString(QStringList itemList);
void ReplaceComboBoxItems(QComboBox* comboBox, QStringList items);
void FindAndSetValueInComboBox(QComboBox* comboBox, QString value);

#endif // FUNCTIONS_H
