#ifndef COLLISIONDETECTION_H
#define COLLISIONDETECTION_H

#include <glew.h>
#include <QOffscreenSurface>
#include <QOpenGLContext>
#include <QImage>
#include <QThread>


class CollisionDetection : public QThread
{

    public:
        CollisionDetection();
        CollisionDetection(QOffscreenSurface * s);
        ~CollisionDetection();
        void initView();
        void initBuffers();
        void draw();

        void run();

    private:
        uchar * pixels;
        QImage * qi;
        GLuint fbo, rbo, depth_rbo;
        GLsizei image_width;
        GLsizei image_height;
        QOffscreenSurface * surface;
        QOpenGLContext * context;
        QOpenGLContext * contextaux;
        bool doRendering;
        bool isInitalized;
};

#endif // COLLISIONDETECTION_H
