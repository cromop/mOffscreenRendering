#include "OGLWidget.h"
#include <QOpenGLContext>
#include <QTimer>
#include <iostream>
#include <cstdlib>


OGLWidget::OGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    timer = new QTimer();
    connect (timer, SIGNAL(timeout()), this, SLOT(repaint()));
}

OGLWidget::~OGLWidget()
{
    // stop and wait for rendering loop to terminate
    renderer->stop();
    renderer->wait();

    timer->stop();

    delete timer;
    delete renderer;
    delete csurface;
}

void OGLWidget::initializeGL()
{
    // glewInit has to be called after the opengl rendering context creation
    glewExperimental = GL_TRUE;

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
      // Problem: glewInit failed, something is seriously wrong.
      std::cerr << "Error: " << glewGetErrorString(err);
    }

    // the QOffscreenSurface needs to be created on the GUI thread
    csurface = new QOffscreenSurface();
    csurface->setFormat(context()->format());
    csurface->create();

//    renderer = new CollisionDetection(csurface, this->context());
    renderer = new OffscreenRenderer(csurface);

    doneCurrent();

    renderer->start();
    timer->start(500);
}

void OGLWidget::resizeGL(int w, int h)
{
    double aspect;
    vwidth = w;
    vheight = h;

    glViewport(0, 0, w, h);

    glLoadIdentity();

    if(h == 0)
        h = 1;
    aspect = 1.0 * w / h;
    if (aspect<0.0001)
        aspect=1.0;
    if(aspect <= 1)
        glFrustum(-0.0005, 0.0005, -0.0005/aspect, 0.0005/aspect, 0.001, 1000.0);
    else
        glFrustum(-0.0005*aspect, 0.0005*aspect, -0.0005, 0.0005, 0.001, 1000.0);
}

void OGLWidget::paintGL()
{
    glClearColor(0.35f, 0.35f, 0.35f, 1.0f);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_TRIANGLES);
        glVertex3f( -5.0f, 5.0f, -15.0f);
        glVertex3f( 5.0f, -5.0f, -15.0f);
        glVertex3f( 5.0f, 5.0f, -15.0f);
    glEnd();
}
