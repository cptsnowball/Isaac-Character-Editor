#include "itemedit.h"

ItemEdit::ItemEdit(QWidget* parent) : QTextEdit(parent)
{

}

void ItemEdit::keyPressEvent(QKeyEvent* event)
{
    if(event->key() == Qt::Key_Return)
    {
        //Will be used as a shortkey to set items button
    }
    else QTextEdit::keyPressEvent(event);
}
