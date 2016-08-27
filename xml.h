#pragma once

#include "character.h"

#include <QString>

class XML
{
public:
    explicit XML(QString filename);
    void WriteXML();
    void DeleteXML();
    void ReadXML();
private:
    QString GetPlayerLine(const Character &player);
    QString GetItemString(const Character &player);
    QString GetSkinColorString(const Character &player);
    QString _filename;
    inline static void AppendToLine(QString &line, QString attribute, QString arg) {
        line.append(QString("%1=\"%2\" ").arg(attribute, arg));
    }
    inline static void AppendToLine(QString &line, QString attribute, int arg) {
        line.append(QString("%1=\"%2\" ").arg(attribute, QString::number(arg)));
    }
    inline static void AppendToLine(QString &line, QString attribute, bool arg) {
        if(arg == false) line.append(QString("%1=\"false\" ").arg(attribute));
    }
};
