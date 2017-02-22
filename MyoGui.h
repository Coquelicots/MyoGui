#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MyoGui.h"

class MyoGui : public QMainWindow
{
    Q_OBJECT

public:
    MyoGui(QWidget *parent = Q_NULLPTR);

private:
    Ui::MyoGuiClass ui;
    bool mode;//true for record, false for play
    bool playing;
    QPushButton *startButton;
private slots:
    void playButtonHandler();
    void recordButtonHandler();
    void stopButtonHandler();
    void browseButtonHandler();
    void pauseButtonHandler();
    void sliderValueChanged();
    void setSliderValue();
    void setSliderMaximum();
    void modeButtonHandler();
};
