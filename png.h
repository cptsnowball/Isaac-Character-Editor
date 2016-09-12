#pragma once

#include "character.h"
#include "nameimages.h"

#include <QString>

class PNG
{
public:
    explicit PNG(const QString &filename);
    void SavePNGs();
    void DeletePNGs();
private:
    NameImages _nameImages;
    QString _filename;
    void CreateDirIfDoesntExist(const QString &dirname);
    void SaveVsBossImage(Characters character);
    void SaveCharSelectMenu(const QImage &image);
};
