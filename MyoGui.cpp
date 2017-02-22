#include "MyoGui.h"
#include <QFileDialog>
MyoGui::MyoGui(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
        startButton = ui.startButton;
        connect(ui.startButton, SIGNAL(released()), this, SLOT (recordButtonHandler()));
        //QPushButton *playButton = ui.playButton;
        connect(ui.playButton,SIGNAL(released()),this, SLOT(playButtonHandler()));
	QPushButton *stopButton = ui.stopButton;
	connect(stopButton, SIGNAL(released()), this, SLOT(stopButtonHandler()));
        //QPushButton *browseButton = ui.browseButton;
        //connect(browseButton, SIGNAL(released()), this, SLOT(browseButtonHandler()));
	QPushButton *pauseButton = ui.pauseButton;
	connect(pauseButton, SIGNAL(released()), this, SLOT(pauseButtonHandler()));
        //QPushButton *modeButton = ui.modeButton;
        //connect(modeButton, SIGNAL(released()), this, SLOT(modeButtonHandler()));
	QSlider *progressSlider = ui.progressSlider;
	progressSlider->setMinimum(0);
	connect(progressSlider, SIGNAL(sliderMoved(int)), this, SLOT(sliderValueChanged()));
	connect(&ui.videowidget->player, SIGNAL(durationChanged(qint64)), this, SLOT(setSliderMaximum()));
	connect(&ui.videowidget->player, SIGNAL(positionChanged(qint64)), this, SLOT(setSliderValue()));
        mode = true;
        playing = false;
        ui.videowidget->hide();
}
void MyoGui::playButtonHandler(){
    mode = false;
    ui.glwidget->setMode(false);
    ui.videowidget->show();
    ui.camerawidget->hide();
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this,"Open Video","/Users", tr("Video Files (*.mp4)"));
    if(fileName!=NULL){
        ui.pauseButton->setText("Pause");
        playing = true;
        ui.videowidget->setVideo(fileName);
        fileName.replace(fileName.length()-4,4,".txt");
        ui.glwidget->openRecordFile(fileName);
        ui.glwidget->paint(true);
        ui.glwidget->timerStart();
        ui.videowidget->playVideo();
    }
}
void MyoGui::modeButtonHandler(){
    mode = !mode;
    if(mode){
        startButton->setText("Record");
        ui.videowidget->hide();
        ui.camerawidget->show();
        ui.glwidget->setMode(true);
    }
    else{
        startButton->setText("Play");
        ui.videowidget->show();
        ui.camerawidget->hide();
        ui.glwidget->setMode(false);
    }
}
void MyoGui::recordButtonHandler()
{
    mode = true;
    ui.glwidget->setMode(true);
    ui.videowidget->hide();
    ui.camerawidget->show();

    QString file;
    file = QFileDialog::getSaveFileName(this,"Open Record","/Users");
    if(file!=NULL){
        ui.glwidget->setRecordFile(file+".txt");
        ui.camerawidget->setVideoName(file+".mp4");
        ui.glwidget->paint(true);
        ui.glwidget->timerStart();
        ui.camerawidget->startRecord();
    }
}

void MyoGui::stopButtonHandler()
{
    ui.glwidget->paint(false);
    ui.glwidget->timerStop();
    if(!mode)
        ui.videowidget->stopVideo();
    else
        ui.camerawidget->stopRecord();
}

void MyoGui::browseButtonHandler()
{
    if(!mode){
        ui.glwidget->openRecordFile(
                QFileDialog::getOpenFileName(this,"Open Record","/Users", tr("Text Files (*.txt)"))
        );
        ui.videowidget->setVideo(
                QFileDialog::getOpenFileName(this,"Open Video","/Users", tr("Video Files (*.mp4)"))
        );
    }
    else{
        QString file;
        file = QFileDialog::getSaveFileName(this,"Open Record","/Users");
        ui.glwidget->setRecordFile(file+".txt");
        ui.camerawidget->setVideoName(file+".mp4");
    }
}

void MyoGui::pauseButtonHandler()
{
    if(mode){
        ui.glwidget->timerStop();
        ui.camerawidget->stopRecord();
    }else{
        if(playing){
            ui.pauseButton->setText("Resume");
            playing = false;
            ui.glwidget->timerPause();
            ui.videowidget->pauseVideo();
        }else{
            ui.pauseButton->setText("Pause");
            playing = true;
            ui.glwidget->timerStart();
            ui.videowidget->playVideo();
        }
    }
}

void MyoGui::sliderValueChanged()
{
    if(!mode&&ui.videowidget->player.isAvailable()){
	ui.videowidget->setVideoPosition(ui.progressSlider->value());
        ui.glwidget->setPosition((ui.progressSlider->value()));
    }
}

void MyoGui::setSliderValue()
{
	ui.progressSlider->setValue(ui.videowidget->player.position());
}

void MyoGui::setSliderMaximum()
{
	ui.progressSlider->setMaximum(ui.videowidget->player.duration());
        ui.glwidget->setGap((ui.videowidget->player.duration()));
}
