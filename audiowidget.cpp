#include "audiowidget.h"
#include <qpainter.h>
AudioWidget::AudioWidget(QWidget *parent) :QWidget(parent)
{

}
void AudioWidget::paintEvent(QPaintEvent * e)
{
    QPainter painter(this);
    painter.fillRect(0,0,571,171,Qt::red);
    painter.drawLine(0,85,571,85);
}
