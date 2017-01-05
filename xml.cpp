#include "xml.h"

#include "character.h"
#include "functions.h"
#include "variables.h"

#include <sstream>
#include <QDir>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QXmlStreamReader>

XML::XML(const QString &filename) :
    _filename(filename) {

    //If filename ends with /resources, remove it.
    if(QDir(_filename).dirName() == "resources") {
        QDir dir = QDir(_filename);
        dir.cdUp();
        _filename = dir.absolutePath();
    }
}

void XML::DeleteXML()
{
    if(!QDir(_filename + "/resources").exists())
    {
        QMessageBox(QMessageBox::Critical, "Error", QString("%1 is not found!").arg(_filename)).exec();
        return;
    }

    QFile file(_filename + "/resources/players.xml");
    if(!file.exists())
    {
        QMessageBox(QMessageBox::Warning, "Information", "players.xml doesn't exist or has already been deleted.").exec();
        return;
    }

    file.remove();

    QMessageBox message(QMessageBox::Information, "Success!", "players.xml deleted.");
    message.exec();
}

void XML::WriteXML()
{
    if (!QDir(_filename + "/resources").exists())
    {
        QMessageBox(QMessageBox::Critical, "Error", QString("%1 is not found!").arg(_filename)).exec();
        return;
    }

    QFile file(_filename + "/resources/players.xml");
    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&file);
        if (game == Game::Afterbirth || game == Game::AfterbirthPlus)
            stream << "<players bigportraitroot=\"gfx/ui/stage/\" nameimageroot=\"gfx/ui/boss/\" portraitroot=\"gfx/ui/boss/\" root=\"gfx/characters/costumes/\">\r\n";
        else
            stream << "<players root=\"resources/gfx/characters/costumes/\" portraitroot=\"resources/gfx/ui/boss/\" bigportraitroot=\"resources/gfx/ui/stage/\">\r\n";

        switch (game)
        {
            case Game::Rebirth:
                for (int i = 0; i < constants::RebirthCharacterCount; ++i)
                    stream << GetPlayerLine(characterMap.at(static_cast<Characters>(i)));
                break;
            case Game::Afterbirth:
                for (int i = 0; i < constants::AfterbirthCharacterCount; ++i)
                    stream << GetPlayerLine(characterMap.at(static_cast<Characters>(i)));
                break;
            case Game::AfterbirthPlus:
                for (int i = 0; i < constants::AfterbirthPlusCharacterCount; ++i)
                    stream << GetPlayerLine(characterMap.at(static_cast<Characters>(i)));
                break;
            case Game::Antibirth:
                for (int i = 0; i < constants::RebirthCharacterCount; ++i)
                    stream << GetPlayerLine(characterMap.at(static_cast<Characters>(i)));
                for (int i = constants::RebirthCharacterCount; i < constants::AntibirthCharacterCount; ++i)
                    stream << GetPlayerLine(characterMap.at(static_cast<Characters>(i + constants::AntibirthOffset)));
                break;
        }

        stream << "</players>\r\n";
    }

    file.close();

    QMessageBox message(QMessageBox::Information, "Success!", "players.xml updated.");
    message.exec();
}

void XML::ReadXML()
{
    if (!QDir(_filename + "/resources").exists())
    {
        QMessageBox(QMessageBox::Critical, "Error", QString("%1 is not found!").arg(_filename)).exec();
        return;
    }

    QFile file(_filename + "/resources/players.xml");
    if (!file.exists())
    {
        QMessageBox(QMessageBox::Warning, "Information", "players.xml doesn't exist.").exec();
        return;
    }

    if (file.open(QIODevice::ReadOnly))
    {
        QXmlStreamReader xml;
        xml.setDevice(&file);

        //Entire thing needs a rewrite, barely "works".
        int currentCharacterIndex = 0;

        while (!xml.atEnd()) {
            xml.readNext();
            if (xml.isStartElement()) {
                if (xml.name() == "player")
                {
                    //If theres more characters in the .xml than in the map (why), break.
                    if (currentCharacterIndex >= constants::UniqueCharacterCount) break;

                    for (const QXmlStreamAttribute &attribute : xml.attributes()) {
                        if (attribute.name().toString() == "name")
                            characterMap.at(static_cast<Characters>(currentCharacterIndex)).Name = attribute.value().toString();
                        else if (attribute.name().toString() == "skinColor")
                            characterMap.at(static_cast<Characters>(currentCharacterIndex)).SkinColor = attribute.value().toInt();
                        else if (attribute.name().toString() == "costume")
                            characterMap.at(static_cast<Characters>(currentCharacterIndex)).Costume = attribute.value().toInt();
                        else if (attribute.name().toString() == "hp")
                            characterMap.at(static_cast<Characters>(currentCharacterIndex)).RedHearts = attribute.value().toInt();
                        else if (attribute.name().toString() == "armor")
                            characterMap.at(static_cast<Characters>(currentCharacterIndex)).SoulHearts = attribute.value().toInt();
                        else if (attribute.name().toString() == "black")
                            characterMap.at(static_cast<Characters>(currentCharacterIndex)).BlackHearts = attribute.value().toInt();
                        else if (attribute.name().toString() == "coins")
                            characterMap.at(static_cast<Characters>(currentCharacterIndex)).Coins = attribute.value().toInt();
                        else if (attribute.name().toString() == "bombs")
                            characterMap.at(static_cast<Characters>(currentCharacterIndex)).Bombs = attribute.value().toInt();
                        else if (attribute.name().toString() == "keys")
                            characterMap.at(static_cast<Characters>(currentCharacterIndex)).Keys = attribute.value().toInt();
                        else if (attribute.name().toString() == "items")
                            characterMap.at(static_cast<Characters>(currentCharacterIndex)).Items = GetItemNamesFromItemList(attribute.value().toString().split(','), false);
                        else if (attribute.name().toString() == "pill")
                            characterMap.at(static_cast<Characters>(currentCharacterIndex)).Pill = attribute.value().toInt();
                        else if (attribute.name().toString() == "card")
                            characterMap.at(static_cast<Characters>(currentCharacterIndex)).Card = attribute.value().toInt();
                        else if (attribute.name().toString() == "trinket")
                            characterMap.at(static_cast<Characters>(currentCharacterIndex)).Trinket = attribute.value().toInt();
                        else if (attribute.name().toString() == "canShoot")
                            characterMap.at(static_cast<Characters>(currentCharacterIndex)).CanShoot = attribute.value() == "true" ? true : false;
                    }

                    //Move on to the next character in the map.
                    ++currentCharacterIndex;
                }
            }
        }

        mainWindowPtr->SetCurrentCharacter(static_cast<int>(currentCharacter));
    }
    file.close();

    QMessageBox message(QMessageBox::Information, "Success!", "players.xml read successful.");
    message.exec();
}

QString XML::GetPlayerLine(const Character &player)
{
    QString line = QString("\t<player ");
    AppendToLine(line, "id", player.ID);
    AppendToLine(line, "name", player.Name);
    AppendToLine(line, "skinColor", player.SkinColor);
    if (game == Game::Afterbirth || game == Game::AfterbirthPlus) AppendToLine(line, "nameimage", player.NameImage);
    AppendToLine(line, "portrait", player.Portrait);
    AppendToLine(line, "bigportrait", player.BigPortrait);
    AppendToLine(line, "skin", (player.SkinFile.split('.')[0] + "%1.png").arg(GetSkinColorString(player)));
    if (player.Costume != 0) AppendToLine(line, "costume", player.Costume);
    if (player.RedHearts != 0) AppendToLine(line, "hp", player.RedHearts);
    if (player.SoulHearts != 0) AppendToLine(line, "armor", player.SoulHearts);
    if (player.BlackHearts != 0) AppendToLine(line, "black", player.BlackHearts);
    if (player.Coins != 0) AppendToLine(line, "coins", player.Coins);
    if (player.Bombs != 0) AppendToLine(line, "bombs", player.Bombs);
    if (player.Keys != 0) AppendToLine(line, "keys", player.Keys);
    QString itemString = GetItemString(player);
    if (itemString != "") AppendToLine(line, "items", itemString);
    if (player.Pill != 0) AppendToLine(line, "pill", player.Pill);
    if (player.Card != 0) AppendToLine(line, "card", player.Card);
    if (player.Trinket != 0) AppendToLine(line, "trinket", player.Trinket);
    if (game == Game::Afterbirth || game == Game::AfterbirthPlus) AppendToLine(line, "canShoot", player.CanShoot);
    if (player.ID == 9) //Eden
    {
        line.append(">\r\n");
        for(int i = 1; i <= 10; ++i)
            line.append(QString("\t\t<hair gfx=\"Character_009_EdenHair%1.png\" />\r\n").arg(QString::number(i)));
        line.append("\t</player>\r\n");
    }
    else line.append("/>\r\n");
    return line;
}

QString XML::GetItemString(const Character &player)
{
    std::vector<int> itemIDs = GetItemIDsFromItemList(player.Items);
    if (player.Spacebar != 0) itemIDs.push_back(player.Spacebar);
    std::sort(itemIDs.begin(), itemIDs.end());

    QStringList itemStringList;
    for(const auto& itemID : itemIDs)
        itemStringList.push_back(QString::number(itemID));
    return itemStringList.join(",");
}

QString XML::GetSkinColorString(const Character &player)
{
    std::vector<int> skinColorlessCharacterIDs = {
        _blueBaby.ID, _theLost.ID, _azazel.ID,
        _blackJudas.ID, _lilith.ID, _theKeeper.ID,
        _apollyon.ID
    };
    if (VectorContains(skinColorlessCharacterIDs, player.ID)) return "";
    else {
        switch(player.SkinColor)
        {
        case -1:
            return "";
        case 0:
            return "_white";
        case 1:
            return "_black";
        case 2:
            return "_blue";
        case 3:
            return "_red";
        case 4:
            return "_green";
        case 5:
            return "_grey";
        default:
            return "";

        }
    }
}
