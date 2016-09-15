#include "nameimages.h"

#include "character.h"
#include "constants.h"
#include "variables.h"

#include <QFontDatabase>
#include <QImage>
#include <QPainter>
#include <QMessageBox>

NameImages::NameImages()
{
    QFontDatabase db;
    int id = db.addApplicationFont(":/Resources/Fonts/IsaacHandwritten.ttf");
    _isaacFont = db.applicationFontFamilies(id).first();
}

QImage NameImages::GenerateVsBossImage(const QString &name)
{
    QImage image(_vsBossWidth, _vsBossHeight, QImage::Format_ARGB32);
    image.fill(Qt::transparent);

    QPainter painter(&image);

    bool fontFits = false;
    int currentPixelSize = _vsBossPixelSize;

    while(!fontFits && currentPixelSize >= 12)
    {
        _isaacFont.setPixelSize(currentPixelSize);
        if (QFontMetrics(_isaacFont).width(name) > _vsBossWidth - 24) currentPixelSize -= 2;
        else fontFits = true;
    }

    QPen pen;
    pen.setColor(_vsBossColor);

    painter.setFont(_isaacFont);
    painter.setPen(pen);
    painter.drawText(image.rect(), Qt::AlignCenter | Qt::AlignVCenter, name);

    return image;
}

QImage NameImages::GenerateCharSelectImage(const QString &name)
{
    QImage image(_characterSelectWidth, _characterSelectHeight, QImage::Format_ARGB32);
    image.fill(Qt::transparent);

    QPainter painter(&image);

    bool fontFits = false;
    int currentPixelSize = _characterSelectPixelSize;

    while(!fontFits && currentPixelSize >= 12)
    {
        _isaacFont.setPixelSize(currentPixelSize);
        if (QFontMetrics(_isaacFont).width(name) > _characterSelectWidth) currentPixelSize -= 2;
        else fontFits = true;
    }

    QPen pen;
    pen.setColor(_characterSelectColor);

    painter.setFont(_isaacFont);
    painter.setPen(pen);

    painter.drawText(image.rect(), Qt::AlignCenter | Qt::AlignBottom, name);

    return image;
}

QImage NameImages::GenerateRebirthCharMenu()
{
    QImage startingImage(":/Resources/UI/DefaultCharacterMenuRebirth.png");
    QPainter painter(&startingImage);
    painter.setCompositionMode(QPainter::CompositionMode::CompositionMode_Source);
    for(int i = 0; i < constants::RebirthCharacterCount; ++i)
    {
        auto character = static_cast<Characters>(i);
        if (defaultNames.at(character) == characterMap.at(character).Name) continue;
        else if (character == Characters::BlackJudas || character == Characters::Lazarus2) continue;
        else
        {
            auto characterRect = QRect(charSelectMenuOffsets.at(character).x(), charSelectMenuOffsets.at(character).y(),
                                    _characterSelectWidth, _characterSelectHeight);
            painter.fillRect(characterRect, Qt::transparent);
            painter.drawImage(charSelectMenuOffsets.at(character), GenerateCharSelectImage(characterMap.at(character).Name));
        }
    }
    return startingImage;
}

QImage NameImages::GenerateAfterbirthCharMenu()
{
    QImage startingImage(":/Resources/UI/DefaultCharacterMenuAfterbirth.png");
    QPainter painter(&startingImage);
    painter.setCompositionMode(QPainter::CompositionMode::CompositionMode_Source);
    for(int i = 0; i < constants::TotalCharacterCount; ++i)
    {
        auto character = static_cast<Characters>(i);
        if (defaultNames.at(character) == characterMap.at(character).Name) continue;
        else if (character == Characters::BlackJudas || character == Characters::Lazarus2) continue;
        else
        {
            auto characterRect = QRect(charSelectMenuOffsets.at(character).x(), charSelectMenuOffsets.at(character).y(),
                                    _characterSelectWidth, _characterSelectHeight);
            painter.fillRect(characterRect, Qt::transparent);
            painter.drawImage(charSelectMenuOffsets.at(character), GenerateCharSelectImage(characterMap.at(character).Name));
        }
    }
    return startingImage;
}
