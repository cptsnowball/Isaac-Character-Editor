#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <map>
#include <stdexcept>

template<typename Key, typename Value>
Key GetKeyFromValue(const std::map<Key, Value> &map, Value valueToFind) {
    for (const auto& keyValuePair : map)
    {
        if(keyValuePair.second == valueToFind) return keyValuePair.first;
        else continue;
    }
    //If a key wasn't found, throw an exception.
    //Should never happen if the maps are properly defined.
    throw std::invalid_argument("Value does not have a key!");
}

#endif // FUNCTIONS_H
