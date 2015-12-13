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

QStringList GetItemNamesFromItemList(QStringList itemList, bool sideEffects)
{
    //Loops through all possible inputs and returns a vector containing their correct item names.
    //Also sets the spacebar combo box if a spacebar item was found.
    itemList = SimplifyItemString(itemList);
    QStringList itemNames;
    for(const auto& item : itemList)
    {
        if(item == "vaporwave" && sideEffects)
        {
            //Invert the value and draw background accordingly.
            vaporwaveAesthetics = !vaporwaveAesthetics;
            mainWindowPtr->DrawBackground(vaporwaveAesthetics);
            continue;
        }

        for(auto& possibleInput : possibleInputs)
        {
            //If user input is an item ID set it and move to next item.
            if(QString::number(possibleInput.ID) == item)
            {
                if(!afterbirthEnabled && possibleInput.Afterbirth) continue;
                else itemNames.push_back(possibleInput.Name);
                continue;
            }

            //Else loop through possible ways of spelling an item.
            for(auto& userInput : possibleInput.UserInputsList)
            {
                if(userInput == item)
                {
                    if(!afterbirthEnabled && possibleInput.Afterbirth) continue;
                    else if(possibleInput.Spacebar && sideEffects)
                        FindAndSetValueInComboBox(spacebarComboBoxPtr, possibleInput.Name);
                    else itemNames.push_back(possibleInput.Name);
                }
            }
        }
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
        for(const auto &string : stringsToRemove)
            if(item.startsWith(string + " ")) item.remove(string);
        item.remove(' ');
        simplifiedItemList.push_back(item);
    }
    return simplifiedItemList;
}

void ReplaceComboBoxItems(QComboBox* comboBox, QStringList items)
{
    //Replaces the items in the ComboBox with the provided ones and keeps the previously
    //selected value selected if possible, else it selects "None".
    QString previousSelection = comboBox->currentText();

    comboBox->clear();
    comboBox->addItems(items);

    for(int i = 0; i < comboBox->count(); ++i)
        if(previousSelection == comboBox->itemText(i))
            comboBox->setCurrentIndex(i);
}

void FindAndSetValueInComboBox(QComboBox* comboBox, QString value)
{
    //int is used instead of size_t because count() returns a const int.
    for(int i = 0; i < comboBox->count(); ++i)
        if(value == spacebarComboBoxPtr->itemText(i))
            comboBox->setCurrentIndex(i);
}
