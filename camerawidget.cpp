#include "camerawidget.h"


CameraWidget::CameraWidget(QWidget *parent) :QCameraViewfinder(parent){
	camera = new QCamera(this);
	camera->setViewfinder(this);
    recorder = new QMediaRecorder(camera);
	imageCapture = new QCameraImageCapture(camera);

	QVideoEncoderSettings videoSettings;
	videoSettings.setResolution(640, 480);
	videoSettings.setQuality(QMultimedia::VeryHighQuality);
	videoSettings.setFrameRate(30.0);

    QAudioEncoderSettings audioSettings;
    qDebug()<<"sup:"<<recorder->supportedAudioCodecs();
    audioSettings.setCodec("aac");
    audioSettings.setQuality(QMultimedia::HighQuality);

    recorder->setAudioSettings(audioSettings);
    recorder->setVideoSettings(videoSettings);
    recorder->setContainerFormat("mp4");

    camera->setCaptureMode(QCamera::CaptureVideo);
    camera->start();
}
void CameraWidget::startRecord()
{
    if(!fileName.isEmpty()){
        recorder->setOutputLocation(QUrl::fromLocalFile(fileName));
        recorder->record();
    }
}

void CameraWidget::stopRecord()
{
    recorder->stop();
}

void CameraWidget::setVideoName(QString s)
{
	fileName = s;
}
