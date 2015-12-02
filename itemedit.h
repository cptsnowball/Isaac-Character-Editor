#ifndef ITEMEDIT_H
#define ITEMEDIT_H

#include <QObject>
#include <QKeyEvent>
#include <QTextEdit>

class ItemEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit ItemEdit(QWidget* parent = 0);
    void keyPressEvent(QKeyEvent* event);
};

#endif // ITEMEDIT_H
