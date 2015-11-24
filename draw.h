#ifndef DRAW_H
#define DRAW_H

#include "character.h"
#include <QLabel>

class Draw : public QObject
{
    Q_OBJECT

public:
    Draw();
    ~Draw();
    void Character(QLabel*, int);
private:
};

#endif // DRAW_H
