#ifndef OFFSCREENRENDERER_H
#define OFFSCREENRENDERER_H

#include <glew.h>
#include <QOffscreenSurface>
#include <QOpenGLContext>
#include <QImage>
#include <QThread>


class OffscreenRenderer : public QThread
{

    public:
        OffscreenRenderer();
        OffscreenRenderer(QOffscreenSurface * s);
        ~OffscreenRenderer();
        void initView();
        void initBuffers();
        void draw();

        void run();
        void stop();

    private:
        uchar * pixels;
        QImage * qi;
        GLuint fbo, rbo, depth_rbo;
        GLsizei image_width;
        GLsizei image_height;
        QOffscreenSurface * surface;
        QOpenGLContext * context;
//        QOpenGLContext * contextaux;
        bool doRendering;
        bool isInitalized;
};

#endif // OFFSCREENRENDERER_H
