#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "opencv2/video/video.hpp"
#include "opencv.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "stereoview.h"
#include "stereoanalysis.h"

#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <QDoubleSpinBox>
#include <QFile>

using namespace cv;

namespace Ui {
class MainWindow;
class CStereoView;
class CStereoAnalysis;
}



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void initMenu();
    void setParameters(double dbBaseline, double dbDolly,
                      double dbArch, double dbFov, double dbTranslation);



    QImage MatToQimage(Mat &mat);

private slots:
    void openFile();
    void prevButtonClicked();
    void nextButtonClicked();
    void saveButtonClicked();

    void parametersEditFinished();

    void splitVideo();

private:
    Ui::MainWindow *ui;

    CStereoAnalysis *stereoAnalysis;

    VideoCapture capture;
    QFile f;
    QString fileName;
    QImage leftImg;
    QImage rightImg;

    QString baseline;
    QString dolly;
    QString fov;
    QString arch;
    QString translation;

    bool isAuto;

    int currentFrame;
    int totalFrameNum;

};

#endif // MAINWINDOW_H
