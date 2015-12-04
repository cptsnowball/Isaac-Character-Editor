#ifndef ITEMEDIT_H
#define ITEMEDIT_H

#include "mainwindow.h"

#include <QObject>
#include <QKeyEvent>
#include <QTextEdit>

class ItemEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit ItemEdit(QWidget* parent = 0);
    void keyPressEvent(QKeyEvent* event);
    void ProcessItems();
};

#endif // ITEMEDIT_H
