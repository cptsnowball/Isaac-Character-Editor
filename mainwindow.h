#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QIntValidator>
#include <QPointer>
#include <array>
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
    void SetUpHealthAndConsumableLabels();
    void GenerateCharacterComboBox();
    void GenerateCardComboBox();
    void GenerateTrinketComboBox();
    std::array<QLabel*, 12> SetUpHeartLabels();
public slots:
    void SetCurrentCharacter(int characterToSet);
    void SetRedHearts(QString value);
    void SetSoulHearts(QString value);
    void SetBlackHearts(QString value);
    void SetCoins(QString value);
    void SetBombs(QString value);
    void SetKeys(QString value);
    void SetCard(int cardIndex);
    void PillCheckBoxChanged(int checkState);
    void CardCheckBoxChanged(int checkState);
    void TrinketCheckBoxChanged(int checkState);
    void AfterbirthCheckBoxChanged(int checkState);
private:
    Ui::MainWindow* ui;
    Characters _currentCharacter = Characters::Isaac;
    Draw _draw;
    const QFont _font = QFont("Segoe UI", 9);
    QIntValidator* _healthValidator = new QIntValidator(0, 24, this);
    QIntValidator* _consumableValidator = new QIntValidator(0, 99, this);
    std::array<QLabel*, 12> _heartLabels = SetUpHeartLabels();
};

#endif // MAINWINDOW_H
