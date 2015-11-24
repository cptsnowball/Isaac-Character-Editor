#ifndef DRAW_H
#define DRAW_H

#include "character.h"
#include <QLabel>
#include <array>

class Draw : public QObject
{
    Q_OBJECT

public:
    Draw();
    ~Draw();
    void PixmapToLabel(QLabel*, const QString&);
    void Character(QLabel*, Characters);
    void Health(std::array<QLabel*, 12>, int, int, int, bool);
private:
};

#endif // DRAW_H
