#pragma once

#include <QColor>
#include <QFont>
#include <QImage>

class NameImages
{
public:
    NameImages();
    QImage GenerateVsBossImage(const QString &name);
private:
    QFont _isaacFont;

    const QColor _vsBossColor = QColor(199, 178, 153);
    const int _vsBossWidth = 192;
    const int _vsBossHeight = 64;

    const int _startingPixelSize = 64;
};


