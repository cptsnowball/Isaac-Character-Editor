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
    int isaacID = db.addApplicationFont(":/Resources/Fonts/IsaacHandwritten.ttf"),
        godmodeID = db.addApplicationFont(":/Resources/Fonts/Godmode.ttf");
    _isaacFont = db.applicationFontFamilies(isaacID).first();
    _godmodeFont = db.applicationFontFamilies(godmodeID).first();
}

QImage NameImages::GenericImageGenerator(const QString &name, int width, int height,
                                         int pixelSize, QFont font, QColor color)
{
    QImage image(width, height, QImage::Format_ARGB32);
    image.fill(Qt::transparent);

    QPainter painter(&image);

    bool fontFits = false;

    while(!fontFits && pixelSize >= 12)
    {
        font.setPixelSize(pixelSize);
        if (QFontMetrics(font).width(name) > width - 24) pixelSize -= 2;
        else fontFits = true;
    }

    QPen pen;
    pen.setColor(color);

    painter.setFont(font);
    painter.setPen(pen);
    painter.drawText(image.rect(), Qt::AlignCenter | Qt::AlignVCenter, name);

    return image;
}

QImage NameImages::GenerateVsBossImage(const QString &name)
{
    return GenericImageGenerator(name, _vsBossWidth, _vsBossHeight, _vsBossPixelSize,
                                 (godmodeEnabled ? _godmodeFont : _isaacFont), _vsBossColor);
}

QImage NameImages::GenerateCharSelectImage(const QString &name)
{
    return GenericImageGenerator(name, _characterSelectWidth, _characterSelectHeight, _characterSelectPixelSize,
                                 (godmodeEnabled ? _godmodeFont : _isaacFont), _characterSelectColor);
}

//ugh
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
    for(int i = 0; i < constants::AfterbirthCharacterCount; ++i)
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

QImage NameImages::GenerateAfterbirthPlusCharMenu()
{
    QImage startingImage(":/Resources/UI/DefaultCharacterMenuAfterbirthPlus.png");
    QPainter painter(&startingImage);
    painter.setCompositionMode(QPainter::CompositionMode::CompositionMode_Source);
    for(int i = 0; i < constants::AfterbirthCharacterCount; ++i)
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
