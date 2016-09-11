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

    if(!QDir(_filename + "/resources").exists())
    {
        QMessageBox(QMessageBox::Critical, "Error", QString("%1 is not found!").arg(_filename)).exec();
        return;
    }

    if(!QDir(_filename + "/resources/gfx/ui/boss").exists())
    {
        QDir().mkpath(_filename + "/resources/gfx/ui/boss");
    }

    for(int i = 0; i < constants::RebirthCharacterCount; ++i)
    {
        SaveVsBossImage(static_cast<Characters>(i));
    }
    if(afterbirthEnabled) for(int i = 0; i < constants::AfterbirthCharacterCount; ++i)
    {
        SaveVsBossImage(static_cast<Characters>(i));
    }
}

void PNG::DeletePNGs()
{

}

void PNG::SaveVsBossImage(Characters character)
{
    if (character == Characters::BlackJudas || character == Characters::Lazarus2) return;
    if (defaultNames.at(character) == characterMap.at(character).Name) return;

    auto image = _nameImages.GenerateVsBossImage(characterMap.at(character).Name);
    image.save(_filename + "/resources/gfx/ui/boss/" + characterMap.at(character).NameImage);
}
