#pragma once

#include "character.h"
#include "random.h"

#include <array>
#include <cstdint>
#include <vector>
#include <QLabel>

class Draw : public QObject
{
    Q_OBJECT

public:
    Draw();
    ~Draw();
    void PixmapToLabel(QLabel*, const QString&);
    void Character(QLabel*, Characters);
    void Health(std::array<QLabel*, 12>, int, int, int, bool);
    void Spacebar(QLabel*, int);
    void Charge(QLabel*, int);
    void Pill(QLabel*);
    void Card(QLabel*, QString);
    void Trinket(QLabel*, int);
    void Familiar(QLabel*, std::vector<int>);
    int DrawnPill = 0;
private:
    Random<std::uint32_t> _rng{};
};
