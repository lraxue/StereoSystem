#include "pglwidget.h"
#include <math.h>

#define PI 3.1415926536f

PGLWidget::PGLWidget(QWidget *parent):QOpenGLWidget(parent)
                     ///* = 0 */, const QGLWidget *shareEidget /* = 0 */, Qt::WindowFlags flags /* = 0 */):QGLWidget(parent, shareEidget, flags)
{
    short angle = 18;
    for (short i = 0; i < 5; ++i)
    {
        Point[i][0] = cos(angle * PI / 180);
        Point[i][1] = sin(angle * PI / 180);
        Point[i][2] = 0.0;

        angle += 72;
    }
}

PGLWidget::~PGLWidget()
{

}


void PGLWidget::initializeGL()
{
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClearDepth(1.0);

    glEnable(GL_DEPTH_TEST);

    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, Point);
}

void PGLWidget::resizeGL(int w, int h)
{

    qDebug() << w << " " << h;
    glViewport(0, 0, (GLint)w, (GLint)h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 1, 1000.0);
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

}

void PGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    glTranslatef(-1.5, 0.0, -6.0);

    glBegin(GL_TRIANGLES);
      glVertex3f(0.0, 1.0, 0.0);
      glVertex3f(-1.0, -1.0, 0.0);
      glVertex3f(1.0, -1.0, 0.0);
    glEnd();

    glTranslatef(3.0, 0.0, 0.0);

    glBegin(GL_LINE_LOOP);
       glArrayElement(1);
       glArrayElement(4);
       glArrayElement(2);
       glArrayElement(0);
       glArrayElement(3);
    glEnd();
}


void PGLWidget::reshow(int width, int height)
{
    resizeGL(width, height);
}


void PGLWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (windowState() & Qt::WindowFullScreen)
        showNormal();
    else
        showFullScreen();
}

void PGLWidget::closeEvent(QCloseEvent *event)
{
    QMessageBox box;
    box.setWindowTitle("Close");
    //box.setIcon(QMessageBox::warning);
    box.setText("Are you sure to close the window?");
    box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    if (QMessageBox::No == box.exec())
    {
        event->ignore();
        return;
    }

    close();
    //PGLWidget::closeEvent(event);
}
