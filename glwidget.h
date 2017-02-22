#pragma once

#include <QWidget>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QVector>
#include <QDebug>
#include <QVBoxLayout>
#include "MyoSensor.h"
class GLWidget : public QWidget {
	Q_OBJECT
public :
    struct signal {
        int ch[8] = {};
    };
	GLWidget(QWidget *parent = Q_NULLPTR);
	void timerStart();
	void timerStop();
	void timerPause();
	void connectMyo();
	void openRecordFile(QString fileName);
    void setRecordFile(QString fileName);
    void setMode(bool s);
    void paint(bool s);
    void setGap(qint64 t);
    void setPosition(int t);
private:
	void paintEvent(QPaintEvent *e);
	void paintRecord();
	void paintLiveSignal();
	int index = 0;
	MyoSensor sensor;
	QTimer *timer;
	QVector<signal> signalRawData;
	QVector<signal> signalToPlay;
	bool fileExist;
    bool isPaint;
    bool mode;//true for record,false for play
    int timeGap;
    QFile *fileToRecord;
    QTextStream *textStream;
private slots:
	void emgDataRefresh();
};
