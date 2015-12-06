#include "xml.h"

#include "functions.h"
#include "variables.h"
#include <sstream>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

XML::XML(QString filename) :
    _filename(filename) { }

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
        QMessageBox(QMessageBox::Warning, "Information", "players.xml doesn't exist or has already been purged.").exec();
        return;
    }

    file.remove();

    QMessageBox message(QMessageBox::Information, "Success!", "players.xml purged.");
    message.exec();
}

void XML::WriteXML()
{
    if(!QDir(_filename + "/resources").exists())
    {
        QMessageBox(QMessageBox::Critical, "Error", QString("%1 is not found!").arg(_filename)).exec();
        return;
    }

    QFile file(_filename + "/resources/players.xml");
    if(file.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&file);
        if(afterbirthEnabled)
            stream << "<players bigportraitroot=\"gfx/ui/stage/\" nameimageroot=\"gfx/ui/boss/\" portraitroot=\"gfx/ui/boss/\" root=\"gfx/characters/costumes/\">\r\n";
        else
            stream << "<players root=\"resources/gfx/characters/costumes/\" portraitroot=\"resources/gfx/ui/boss/\" bigportraitroot=\"resources/gfx/ui/stage/\">\r\n";

        for(int i = 0; i < constants::REBIRTH_CHARACTER_COUNT; ++i)
            stream << GetPlayerLine(characterMap.at(static_cast<Characters>(i)));
        if(afterbirthEnabled) for(int i = 0; i < constants::AFTERBIRTH_CHARACTER_COUNT; ++i)
            stream << GetPlayerLine(characterMap.at(static_cast<Characters>(constants::REBIRTH_CHARACTER_COUNT + i)));
        stream << "</players>\r\n";
    }

    file.close();

    QMessageBox message(QMessageBox::Information, "Success!", "players.xml updated.");
    message.exec();
}

void XML::ReadXML()
{
    //pass
}

QString XML::GetPlayerLine(const Character &player)
{
    QString line = QString("\t<player ");
    AppendToLine(line, "id", player.ID);
    AppendToLine(line, "name", player.Name);
    if(afterbirthEnabled) AppendToLine(line, "nameimage", player.NameImage);
    AppendToLine(line, "skin", player.SkinFile);
    if(player.Costume != 0) AppendToLine(line, "costume", player.Costume);
    if(player.RedHearts != 0) AppendToLine(line, "hp", player.RedHearts);
    if(player.SoulHearts != 0) AppendToLine(line, "armor", player.SoulHearts);
    if(player.BlackHearts != 0) AppendToLine(line, "black", player.BlackHearts);
    if(player.Coins != 0) AppendToLine(line, "coins", player.Coins);
    if(player.Bombs != 0) AppendToLine(line, "bombs", player.Bombs);
    if(player.Keys != 0) AppendToLine(line, "keys", player.Keys);
    QString itemString = GetItemString(player);
    if(itemString != "") AppendToLine(line, "items", itemString);
    if(player.Pill != 0) AppendToLine(line, "pill", player.Pill);
    if(player.Card != 0) AppendToLine(line, "card", player.Card);
    if(player.Trinket != 0) AppendToLine(line, "trinket", player.Trinket);
    if(afterbirthEnabled) AppendToLine(line, "canShoot", player.CanShoot);
    if(player.ID == 9) //Eden
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
    if(player.Spacebar != 0) itemIDs.push_back(player.Spacebar);
    std::sort(itemIDs.begin(), itemIDs.end());

    QStringList itemStringList;
    for(const auto& itemID : itemIDs)
        itemStringList.push_back(QString::number(itemID));
    return itemStringList.join(",");
}
