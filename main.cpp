#include "mainwindow.h"
#include <QApplication>

using namespace std;

Point2f point;
vector<Point2f> points[2];

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
