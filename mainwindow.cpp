
#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace cv;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // mainwindow initialization
    ui->setupUi(this);
    this->setWindowTitle("Stereo Video Edit System");
    this->setWindowIcon(QIcon(tr(":/image/3D_128.png")));
    ui->leftImgLabel->setAlignment(Qt::AlignCenter);
    ui->rightImgLabel->setAlignment(Qt::AlignCenter);

    stereoAnalysis = new CStereoAnalysis;

    // opened video initalization
    currentFrame = -1;

   // this is for saving data in a siimple way
    f.setFileName("./result/parameters.txt");
    if (!f.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Append))
    {
        qDebug() << "open parameters file error";
    }

    // signals and slots
    connect(ui->actionOpen,SIGNAL(triggered()), this, SLOT(openFile()));
    connect(ui->prevToolButton, SIGNAL(clicked()), this, SLOT(prevButtonClicked()));
    connect(ui->nextToolButton, SIGNAL(clicked()), this, SLOT(splitVideo()));
    connect(ui->baseline, SIGNAL(editingFinished()),this, SLOT(parametersEditFinished()));
    connect(ui->dolly, SIGNAL(editingFinished()),this, SLOT(parametersEditFinished()));
    connect(ui->arch, SIGNAL(editingFinished()),this, SLOT(parametersEditFinished()));
    connect(ui->fov, SIGNAL(editingFinished()),this, SLOT(parametersEditFinished()));
    connect(ui->translation, SIGNAL(editingFinished()),this, SLOT(parametersEditFinished()));
}

MainWindow::~MainWindow()
{
    if (capture.isOpened())
        capture.release();        // release the video resource

    if (f.isOpen())
        f.close();               // close the file

    delete ui;
}


void MainWindow::openFile()
{
    fileName = QFileDialog::getOpenFileName(this, "open a video file", "f:", "Video files(*.mp4 *.rmvb *.avi)");

    capture.open(fileName.toStdString());

    totalFrameNum = (int)capture.get(CV_CAP_PROP_FRAME_COUNT);
    ui->progressBar->setRange(0, totalFrameNum - 1);

    qDebug() << totalFrameNum;

    splitVideo();

}

void MainWindow::prevButtonClicked()
{
    if (currentFrame <= 0)
        return;

    currentFrame -= 2;      // a bug exits here
    capture.set(CV_CAP_PROP_POS_FRAMES, currentFrame);  // set previous frame as current frame

    splitVideo();
}

void MainWindow::saveButtonClicked()
{
    QString strFrameOrder = QString::number(currentFrame);

    // imwrite("./result/" + strFrameOrder.toStdString() + ".png", rightImg);  // save the image

    QTextStream out(&f);
    out << currentFrame << " " << ui->baseline->text() << " " <<
           ui->dolly->text() << " " << ui->arch->text() << " " <<
           ui->fov->text() << " " << ui->translation << endl;
    out.flush();
}


void MainWindow::nextButtonClicked()
{
    splitVideo();
}

void MainWindow::parametersEditFinished()
{
    // get parameters from label
    // convert to double
    double baseline = ui->baseline->text().toDouble();
    double dolly = ui->dolly->text().toDouble();
    double arch = ui->arch->text().toDouble();
    double fov = ui->fov->text().toDouble();
    double translation = ui->translation->text().toDouble();

   // stereoAnalysis->setParameters(baseline, dolly, arch, fov, translation);   // for scene analysis

    qDebug() << baseline << " " << dolly << " " << arch << " "  << fov << " " << translation;    // for debugging
}


void MainWindow::splitVideo()                  // split video to frames and show on the label
{
    currentFrame++;

    ui->progressBar->setValue(currentFrame);  // set current pragress

    Mat frame;
    capture >> frame;

    if (frame.empty())
        return;

    leftImg = MatToQimage(frame);                // convert Mat to QImage for displaying

    int height = ui->leftImgLabel->height();
    int width = ui->leftImgLabel->width();

    qDebug() <<height << " " << width;          // for debugging

    leftImg = leftImg.scaled(width, height, Qt::KeepAspectRatio);    // resize the image to adopt the label

    ui->leftImgLabel->setPixmap(QPixmap::fromImage(leftImg));
    ui->rightImgLabel->setPixmap(QPixmap::fromImage(leftImg));
}


void MainWindow::setParameters(double dbBaseline, double dbDolly,
                               double dbArch, double dbFov, double dbTranslation)
{
    ui->baseline->setText(QString::number(dbBaseline, 'g', 4));
    ui->dolly->setText(QString::number(dbDolly, 'g', 4));
    ui->arch->setText(QString::number(dbArch, 'g', 4));
    ui->fov->setText(QString::number(dbFov, 'g', 4));
    ui->translation->setText(QString::number(dbTranslation, 'g', 4));
}


QImage MainWindow::MatToQimage(Mat &mat)
{
    // 8-bits unsigned, NO. OF CHANNELS=1
    if(mat.type()==CV_8UC1)
    {
        // Set the color table (used to translate colour indexes to qRgb values)
        QVector<QRgb> colorTable;
        for (int i=0; i<256; i++)
            colorTable.push_back(qRgb(i,i,i));
        // Copy input Mat
        const uchar *qImageBuffer = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage img(qImageBuffer, mat.cols, mat.rows, mat.step, QImage::Format_Indexed8);
        img.setColorTable(colorTable);
        return img;
    }
    // 8-bits unsigned, NO. OF CHANNELS=3
    if(mat.type()==CV_8UC3)
    {
        // Copy input Mat
        const uchar *qImageBuffer = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage img(qImageBuffer, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        return img.rgbSwapped();
    }
    else
    {
        qDebug() << "ERROR: Mat could not be converted to QImage.";
        return QImage();
    }
}
