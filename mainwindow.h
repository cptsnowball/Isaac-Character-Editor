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
    void GenerateComboBoxes();
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
    void SetTrinket(QString value);
    void PillCheckBoxChanged(int checkState);
    void CardCheckBoxChanged(int checkState);
    void TrinketCheckBoxChanged(int checkState);
    void SortCheckBoxChanged(int checkState);
    void AfterbirthCheckBoxChanged(int checkState);
    void RestoreDefaultPath();
private:
    Ui::MainWindow* ui;
    Characters _currentCharacter = Characters::Isaac;
    Draw _draw;
    const QFont _font = QFont("Segoe UI", 9);
    QString _isaacPath = _defaultPath;
    QIntValidator* _healthValidator = new QIntValidator(0, 24, this);
    QIntValidator* _consumableValidator = new QIntValidator(0, 99, this);
    std::array<QLabel*, 12> _heartLabels = SetUpHeartLabels();

    //Ugly
#if defined(Q_OS_WIN)
    const QString _defaultPath = "C:/Program Files (x86)/Steam/SteamApps/common/The Binding of Isaac Rebirth";
#elif defined(Q_OS_MAC)
    //not sure yet
    const QString _defaultPath = "/Library/Application Support/Steam/SteamApps/common/the binding of isaac/The Binding Of Isaac.app/Content/Resources/resources/";
#elif defined(Q_OS_LINUX)
    //not sure yet either
    const QString _defaultPath = "";
#else
#error Platform not supported
    const QString _defaultPath = QString::null;
#endif
};

#endif // MAINWINDOW_H
