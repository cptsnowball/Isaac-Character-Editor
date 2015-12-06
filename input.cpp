#include "input.h"

#include <QFile>
#include <QXmlStreamReader>
#include <QMessageBox>

std::vector<Input> Input::getPossibleUserInputs()
{
    std::vector<Input> inputs;

    QFile file(":/inputs.xml");
    if(file.open(QIODevice::ReadOnly))
    {
        QXmlStreamReader xml;
        xml.setDevice(&file);

        while(!xml.atEnd()) {
            xml.readNext();
            if(xml.isStartElement()) {
                if(xml.name() == "input") {
                    Input input;
                    foreach(const QXmlStreamAttribute &attribute, xml.attributes()) {
                        if(attribute.name().toString() == "userinput")
                            input.UserInputsList = attribute.value().toString().split(',');
                        else if(attribute.name().toString() == "name")
                            input.Name = attribute.value().toString();
                        else if(attribute.name().toString() == "id")
                            input.ID = attribute.value().toInt();
                        else if(attribute.name().toString() == "spacebar")
                            input.Spacebar = attribute.value().toString() == "true" ? true : false;
                        else if(attribute.name().toString() == "afterbirth")
                            input.Afterbirth = attribute.value().toString() == "true" ? true : false;
                    }
                    inputs.push_back(input);
                }
            }
        }
    }

    return inputs;
}

void Input::ShowInput()
{
    QMessageBox msg;
    msg.setText(QString("userinput: %1\nname: %2, id: %3, afterbirth: %4")
                .arg(this->UserInputsList.join(", "),
                     this->Name,
                     QString::number(this->ID),
                     this->Afterbirth == true ? "true" : "false"));
    msg.exec();
}
