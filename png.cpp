#include "png.h"

#include "constants.h"
#include "variables.h"

#include <QDir>
#include <QFile>
#include <QMessageBox>

PNG::PNG(const QString &filename) :
    _filename(filename) {

    //If filename ends with /resources, remove it.
    if(QDir(_filename).dirName() == "resources") {
        QDir dir = QDir(_filename);
        dir.cdUp();
        _filename = dir.absolutePath();
    }
}

void PNG::SavePNGs()
{
    if(!nameImagesEnabled) return;

    if (game == Game::AfterbirthPlus && !QDir(_filename).exists())
    {
        QMessageBox(QMessageBox::Critical, "Error", QString("%1 is not found!").arg(_filename)).exec();
    }
    else if(game != Game::AfterbirthPlus && !QDir(_filename + "/resources").exists())
    {
        QMessageBox(QMessageBox::Critical, "Error", QString("%1 is not found!").arg(_filename)).exec();
        return;
    }

    QString abPlusFilename = _filename + "/Isaac Character Editor";

    CreateDirIfDoesntExist((game == Game::AfterbirthPlus ? abPlusFilename : _filename) + "/resources/gfx/ui/boss");
    CreateDirIfDoesntExist((game == Game::AfterbirthPlus ? abPlusFilename : _filename) + "/resources/gfx/ui/main menu");

    switch (game)
    {
        case Game::Rebirth:
            for (int i = 0; i < constants::RebirthCharacterCount; ++i) {
                SaveVsBossImage(static_cast<Characters>(i));
            }
            break;
        case Game::Afterbirth:
            for (int i = 0; i < constants::AfterbirthCharacterCount; ++i) {
                SaveVsBossImage(static_cast<Characters>(i));
            }
            break;
        case Game::AfterbirthPlus:
            for (int i = 0; i < constants::AfterbirthPlusCharacterCount; ++i) {
                SaveVsBossImage(static_cast<Characters>(i));
            }
            break;
        case Game::Antibirth:
            for (int i = 0; i < constants::RebirthCharacterCount; ++i) {
                SaveVsBossImage(static_cast<Characters>(i));
            }
            for (int i = constants::RebirthCharacterCount; i < constants::AntibirthCharacterCount; ++i) {
                SaveVsBossImage(static_cast<Characters>(i + constants::AntibirthOffset));
            }
            break;
    }

    auto charSelectMenu = (game == Game::AfterbirthPlus) ?
                _nameImages.GenerateAfterbirthPlusCharMenu() : (game == Game::Afterbirth) ?
                    _nameImages.GenerateAfterbirthCharMenu() : _nameImages.GenerateRebirthCharMenu();

    SaveCharSelectMenu(charSelectMenu);
}

void PNG::DeletePNGs()
{
    //XML::DeleteXMLs already ganked it.
    if (game == Game::AfterbirthPlus) return;

    for(int i = 0; i < constants::UniqueCharacterCount; ++i)
    {
        QFile imageFile(_filename + "/resources/gfx/ui/boss/" + characterMap.at(static_cast<Characters>(i)).NameImage);
        if (imageFile.exists()) imageFile.remove();
    }
}

void PNG::CreateDirIfDoesntExist(const QString &dirname)
{
    if(!QDir(dirname).exists()) QDir().mkpath(dirname);
}

void PNG::SaveVsBossImage(Characters character)
{
    if (game == Game::AfterbirthPlus)
    {
        CreateDirIfDoesntExist(_filename + "/Isaac Character Editor/resources/");
    }

    QString abPlusFilename = _filename + "/Isaac Character Editor";

    if (character == Characters::BlackJudas || character == Characters::Lazarus2) return;
    auto image = _nameImages.GenerateVsBossImage(characterMap.at(character).Name);

    QFile imageFile((game == Game::AfterbirthPlus ? abPlusFilename : _filename) + "/resources/gfx/ui/boss/" + characterMap.at(character).NameImage);

    if (imageFile.exists()) imageFile.remove();

    if (defaultNames.at(character) == characterMap.at(character).Name) return;

    image.save((game == Game::AfterbirthPlus ? abPlusFilename : _filename) + "/resources/gfx/ui/boss/" + characterMap.at(character).NameImage);
}

void PNG::SaveCharSelectMenu(const QImage &image)
{
    QString abPlusFilename = _filename + "/Isaac Character Editor";
    QFile imageFile((game == Game::AfterbirthPlus ? abPlusFilename : _filename) + "/resources/gfx/ui/main menu/charactermenu.png");
    if(imageFile.exists()) imageFile.remove();
    image.save((game == Game::AfterbirthPlus ? abPlusFilename : _filename) + "/resources/gfx/ui/main menu/charactermenu.png");
}
