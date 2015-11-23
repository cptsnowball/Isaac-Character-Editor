#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "draw.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void GenerateCharacterComboBox();
public slots:
    void DrawCharacter(int characterToDraw);
private:
    Ui::MainWindow *ui;
    Draw _draw;
    const QFont _font = QFont("Segoe UI");
};

#endif // MAINWINDOW_H
