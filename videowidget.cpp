#include "videowidget.h"

VideoWidget::VideoWidget(QWidget *parent) :QVideoWidget(parent) {
	player.setVideoOutput(this);
    //connect(&player, SIGNAL(durationChanged(qint64)), this, SLOT(getDuration()));
	duration = 0;
}

void VideoWidget::playVideo()
{
	player.play();
}

void VideoWidget::pauseVideo()
{
	player.pause();
}

void VideoWidget::setVideoPosition(int position)
{
	player.setPosition(position);
}

void VideoWidget::stopVideo()
{
	player.stop();
}

void VideoWidget::setVideo(QString videoName)
{
	player.setMedia(QUrl::fromLocalFile(videoName));
	
}

void VideoWidget::getDuration()
{
	duration = player.duration();
}
