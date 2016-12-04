#include "input.h"

#include <QFile>
#include <QMessageBox>
#include <QXmlStreamReader>

std::vector<Input> Input::getPossibleUserInputs()
{
    std::vector<Input> inputs;

    QFile file(":/inputs.xml");
    if (file.open(QIODevice::ReadOnly))
    {
        QXmlStreamReader xml;
        xml.setDevice(&file);

        while (!xml.atEnd()) {
            xml.readNext();
            if (xml.isStartElement()) {
                if (xml.name() == "input") {
                    Input input;
                    for (const QXmlStreamAttribute &attribute : xml.attributes()) {
                        if (attribute.name().toString() == "userinput")
                            input.UserInputsList = attribute.value().toString().split(',');
                        else if (attribute.name().toString() == "name")
                            input.Name = attribute.value().toString();
                        else if (attribute.name().toString() == "id")
                            input.ID = attribute.value().toInt();
                        else if (attribute.name().toString() == "spacebar")
                            input.Spacebar = attribute.value().toString() == "true" ? true : false;
                        else if (attribute.name().toString() == "afterbirth")
                            input.WhichGame = attribute.value().toString() == "true" ? Game::Afterbirth : Game::Rebirth;
                        else if (attribute.name().toString() == "afterbirthplus")
                            input.WhichGame = attribute.value().toString() == "true" ? Game::AfterbirthPlus : Game::Rebirth;
                    }
                    inputs.push_back(input);
                }
            }
        }
    }

    return inputs;
}

// Unusued in release code.
void Input::ShowInput()
{
    QMessageBox msg;
    msg.setText(QString("userinput: %1\nname: %2, id: %3, afterbirth: %4")
                .arg(this->UserInputsList.join(", "),
                     this->Name,
                     QString::number(this->ID),
                     this->WhichGame == Game::Afterbirth ? "true" : "false"));
    msg.exec();
}
