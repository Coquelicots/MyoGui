#include "glwidget.h"
#include <qpainter.h>
#include <QTimer>

GLWidget::GLWidget(QWidget *parent) :QWidget(parent), signalToPlay(40){
    connectMyo();
	timer = new QTimer(this);
	//connect(timer, SIGNAL(timeout()), this, SLOT(emgDataRefresh()));
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));
	fileExist = false;
    fileToRecord = new QFile("default.txt");
    textStream = new QTextStream(fileToRecord);
    isPaint = false;
    mode = true;
    index = 0;
    timeGap = 20;
}

void GLWidget::timerStart()
{
    if (fileExist){
        if(mode){
            timer->start();
        }else{
            timer->start(timeGap);
        }
    }
}

void GLWidget::timerStop()
{
	signal defaultSig;
	for (int x = 0; x < 40; x++) {
		signalToPlay[x] = defaultSig;
	}
	update();
	timer->stop();
	index = 0;
}

void GLWidget::timerPause()
{
	timer->stop();
}

void GLWidget::connectMyo()
{
	sensor.connectOnThread();
}

void GLWidget::openRecordFile(QString fileName)
{
	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;
	fileExist = true;
	QTextStream in(&file);
	while (!in.atEnd()) {
		QString line = in.readLine();
		QStringList list = line.split(' ');
		signal data;
        if(list.size()==9){
            for (int i = 0; i < 8; i++) {
                data.ch[i] = list.at(i).toInt();
            }
            signalRawData.push_back(data);
        }
    }
    file.close();
}
void GLWidget::setPosition(int t){
    if(signalRawData.size()>0){
        index = t/timeGap;
        if(index >= signalRawData.size()){
            index = signalRawData.size()-1;
        }
        emgDataRefresh();
        update();
    }
}
void GLWidget::setGap(qint64 t){
    timeGap = t/signalRawData.size();
}
void GLWidget::setRecordFile(QString fileName){
    fileExist = false;
    if(fileToRecord->isOpen())
        fileToRecord->close();
    delete textStream;
    delete fileToRecord;
    fileToRecord = new QFile(fileName);
    if(fileToRecord->open(QIODevice::ReadWrite)){
        fileExist = true;
        textStream = new QTextStream(fileToRecord);
    }
}
void GLWidget::emgDataRefresh()
{
    for (int x = 0,y = 39; x < 40; x++,y--) {
        for (int i = 0; i < 8; i++) {
            if((index-x)<0)
                signalToPlay[y].ch[i] = 0;
            else
                signalToPlay[y].ch[i] = signalRawData[index-x].ch[i] * 0.5;
        }
    }
	index++;
	if (index == signalRawData.size()) {
		timerPause();
		index = 0;
	}
}
void GLWidget::setMode(bool s){
    mode = s;
}
void GLWidget::paint(bool s){
    isPaint = s;
}
void GLWidget::paintEvent(QPaintEvent * e)
{
    if(isPaint){
        if(mode){
            paintLiveSignal();
        }else{
            emgDataRefresh();
            paintRecord();
        }
    }
}

void GLWidget::paintRecord()
{	
	int channelwidgetwidth = 570;
	int channelwidgetheigh = 255 / 3;
	int margin = 5;
	QPainterPath path;
	QPainter painter(this);
	for (int i = 0; i < 8; i++) {
		painter.fillRect(0, channelwidgetheigh*i+ margin*i, channelwidgetwidth, channelwidgetheigh, Qt::green);
		painter.setPen(Qt::yellow);
		painter.drawLine(0, channelwidgetheigh*i + margin*i + channelwidgetheigh*0.5, channelwidgetwidth, channelwidgetheigh*i + margin*i + channelwidgetheigh*0.5);
		path.moveTo(0, channelwidgetheigh*i + margin*i+ channelwidgetheigh*0.5);
		painter.setPen(Qt::black);
        for (int j = 0; j < 40; j++) {
			path.lineTo(j * 15, -(signalToPlay[j].ch[i])/3 + channelwidgetheigh*i + margin*i + channelwidgetheigh*0.5);
		}
		painter.drawPath(path);
	}
}

void GLWidget::paintLiveSignal()
{
	
	sensor.refreshEmg();
	array<int8_t, 8> datas;
	datas = sensor.getEmg();

	signal data;
	for (int i = 0; i < 8; i++) {
        if(fileToRecord->isOpen()){
            (*textStream)<<(int)datas[i]<<" ";
        }
		data.ch[i] = -(int)datas[i]*0.5;
	}
    if(fileToRecord->isOpen()){
        (*textStream)<<endl;
    }
	signalToPlay[39] = data;
	for (int x = 0; x < 39; x++) {
		signalToPlay[x] = signalToPlay[x + 1];
	}

	int channelwidgetwidth = 570;
	int channelwidgetheigh = 255 / 3;
	int margin = 5;
	QPainterPath path;
	QPainter painter(this);
	for (int i = 0; i < 8; i++) {
		painter.fillRect(0, channelwidgetheigh*i + margin*i, channelwidgetwidth, channelwidgetheigh, Qt::green);
		painter.setPen(Qt::yellow);
		painter.drawLine(0, channelwidgetheigh*i + margin*i + channelwidgetheigh*0.5, channelwidgetwidth, channelwidgetheigh*i + margin*i + channelwidgetheigh*0.5);
		path.moveTo(0, channelwidgetheigh*i + margin*i + channelwidgetheigh*0.5);
		painter.setPen(Qt::black);
		for (int j = 0; j < 40; j++) {
			path.lineTo(j * 15, -(signalToPlay[j].ch[i]) / 3 + channelwidgetheigh*i + margin*i + channelwidgetheigh*0.5);
		}
		painter.drawPath(path);
    }
}
