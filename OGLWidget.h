#ifndef OGLWidget_H
#define OGLWidget_H

#include <glew.h>
#include <QOpenGLWidget>
#include <QOffscreenSurface>
#include <OffscreenRenderer.h>
#include <QTimer>

class OGLWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    OGLWidget(QWidget *parent = 0);
    ~OGLWidget();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

private:
    float vwidth;
    float vheight;
    CollisionDetection *collision;
    QOffscreenSurface *csurface;
    QOpenGLContext *ccontext;
    QTimer *timer;


};

#endif // OGLWidget_H
