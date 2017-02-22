#include "myogui.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyoGui w;
    w.show();
    return a.exec();
}
