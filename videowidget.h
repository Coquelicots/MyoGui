#pragma once
#include "glwidget.h"
#include <QVideoWidget>
#include <QMediaPlayer>


class VideoWidget : public QVideoWidget {
	Q_OBJECT
public:
	VideoWidget(QWidget *parent = Q_NULLPTR);
	void playVideo();
	void pauseVideo();
	void setVideoPosition(int position);
	void stopVideo();
	void setVideo(QString videoName);
	QMediaPlayer player;
	qint64 duration;
private slots:
	void getDuration();
};