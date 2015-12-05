#include "functions.h"
#include <QMessageBox>

std::vector<int> GetItemIDsFromItemList(QStringList itemList)
{
    //Loops through all possible inputs and returns a vector containing matched item IDs
    itemList = SimplifyItemString(itemList);
    std::vector<int> itemIDs;
    for(const auto& item : itemList)
        for(auto& possibleInput : possibleInputs)
            for(auto& userInput : possibleInput.UserInputsList)
                if(userInput == item)
                {
                    if(!afterbirthEnabled && possibleInput.Afterbirth) continue;
                    else itemIDs.push_back(possibleInput.ID);
                }

    return itemIDs;
}

QStringList GetItemNamesFromItemList(QStringList itemList)
{
    //Loops through all possible inputs and returns a vector containing their correct item names.
    itemList = SimplifyItemString(itemList);
    QStringList itemNames;
    for(const auto& item : itemList)
        for(auto& possibleInput : possibleInputs)
            for(auto& userInput : possibleInput.UserInputsList)
                if(userInput == item)
                {
                    if(!afterbirthEnabled && possibleInput.Afterbirth) continue;
                    else itemNames.push_back(possibleInput.Name);
                }

    return itemNames;
}

QStringList SimplifyItemString(QStringList itemList)
{
    //Couldn't get a regex working properly, this works flawlessly.
    const QString charsToRemove("#'-._!?");
    const QStringList stringsToRemove { "the", "moms", "a" };

    //Loop through items and simplify their strings.
    QStringList simplifiedItemList;
    for(auto& item : itemList)
    {
        item = item.toLower();
        for(const auto &character : charsToRemove) item.remove(character);
        for(const auto &string : stringsToRemove) item.remove(string + " ");
        item.remove(' ');
        simplifiedItemList.push_back(item);
    }
    return simplifiedItemList;
}
