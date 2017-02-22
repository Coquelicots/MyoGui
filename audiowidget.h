#ifndef AUDIOWIDGET_H
#define AUDIOWIDGET_H

#include <QWidget>

class AudioWidget : public QWidget
{
    Q_OBJECT
public:
    AudioWidget(QWidget *parent = Q_NULLPTR);
private:
    void paintEvent(QPaintEvent *e);
};

#endif // AUDIOWIDGET_H
