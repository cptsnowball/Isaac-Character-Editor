#ifndef ITEMEDIT_H
#define ITEMEDIT_H

#include <QObject>
#include <QTextEdit>

class ItemEdit : public QTextEdit
{
    Q_OBJECT
public:
    void keyPressEvent(QKeyEvent* event);
};

#endif // ITEMEDIT_H
