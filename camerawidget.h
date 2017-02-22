#pragma once
#include "videowidget.h"
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QVBoxLayout>
#include <QMediaRecorder>
class CameraWidget : public QCameraViewfinder {
	Q_OBJECT
public:
	CameraWidget(QWidget *parent = Q_NULLPTR);
	void startRecord();
	void stopRecord();
	void setVideoName(QString s);
private:
	QCamera *camera;
	QCameraImageCapture *imageCapture;
	QMediaRecorder *recorder;
	QString fileName;
};