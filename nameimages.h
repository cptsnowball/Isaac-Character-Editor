#pragma once

#include <functional>
#include <QColor>
#include <QFont>
#include <QImage>

class NameImages
{
public:
    NameImages();
    QImage GenerateVsBossImage(const QString &name);
    QImage GenerateCharSelectImage(const QString &name);
    QImage GenerateRebirthCharMenu();
    QImage GenerateAfterbirthCharMenu();
private:
    QFont _isaacFont;

    const QColor _vsBossColor = QColor(199, 178, 153);
    const int _vsBossWidth = 192;
    const int _vsBossHeight = 64;
    const int _vsBossPixelSize = 64;

    const QColor _characterSelectColor = QColor(55, 43, 45);
    const int _characterSelectWidth = 80;
    const int _characterSelectHeight = 32;
    const int _characterSelectPixelSize = 28;
};


