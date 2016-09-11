#include "nameimages.h"

#include <QFontDatabase>
#include <QImage>
#include <QPainter>

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
    int currentPixelSize = _startingPixelSize;

    while(!fontFits && currentPixelSize >= 12)
    {
        _isaacFont.setPixelSize(currentPixelSize);
        if (QFontMetrics(_isaacFont).width(name) > 192) currentPixelSize -= 12;
        else fontFits = true;
    }

    QPen pen;
    pen.setColor(_vsBossColor);

    painter.setFont(_isaacFont);
    painter.setPen(pen);

    painter.drawText(image.rect(), Qt::AlignCenter | Qt::AlignVCenter, name);

    return image;
}
