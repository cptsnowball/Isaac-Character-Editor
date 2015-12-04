#include "functions.h"
#include "itemedit.h"
#include "input.h"
#include "variables.h"

ItemEdit::ItemEdit(QWidget* parent) : QTextEdit(parent)
{

}

void ItemEdit::keyPressEvent(QKeyEvent* event)
{
    if(event->key() == Qt::Key_Return)
    {
        this->ProcessItems();
    }
    else QTextEdit::keyPressEvent(event);
}

void ItemEdit::ProcessItems()
{
    QStringList itemList = this->toPlainText().split(',');
    itemList = SimplifyItemString(itemList);

    //Get the proper item names
    QStringList items = GetItemNamesFromItemList(itemList);

    //Set the current character items
    Character* character = &characterMap.at(currentCharacter);
    character->Items = items;

    //Set the plain text according to the found items and their proper names.
    this->setPlainText(items.join(", "));
    QTextCursor cursor(this->textCursor());
    cursor.movePosition(QTextCursor::End);
    this->setTextCursor(cursor);
}
