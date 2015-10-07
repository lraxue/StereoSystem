#ifndef PGLWIDGET
#define PGLWIDGET

#include <QOpenGLWidget>
//#include <QtOpenGL/QtOpenGL>
//#include <QtGui/QOpenGLFunctions>
//#include "qgl.h"
//#include <QGL>
#include <glut.h>
#include <QCloseEvent>
#include <QMessageBox>
#include <QtOpenGL>

class PGLWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
     PGLWidget(QWidget *parent = 0);  //, const QGLWidget *shareEidget = 0, Qt::WindowFlags falgs = 0);
    ~PGLWidget();

protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();

    virtual void mouseDoubleClickEvent(QMouseEvent *event);
    virtual void closeEvent(QCloseEvent *event);

public:
     void reshow(int width, int height);

private:
    GLfloat Point[5][3];
};
#endif // PGLWIDGET

