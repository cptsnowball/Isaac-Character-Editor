#pragma once

#include "mainwindow.h"

#include <QObject>
#include <QKeyEvent>
#include <QTextEdit>

class ItemEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit ItemEdit(QWidget* parent = nullptr);
    void keyPressEvent(QKeyEvent* event);
    void ProcessItems();
};
