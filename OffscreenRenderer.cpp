#include "OffscreenRenderer.h"
#include <iostream>


OffscreenRenderer::OffscreenRenderer()
{
}

OffscreenRenderer::OffscreenRenderer(QOffscreenSurface * s)
{
    image_width = 512;
    image_height = 512;
    fbo = rbo = depth_rbo = 0;

    pixels = new uchar[image_width * image_height * 3];
    for(int i=0; i < (image_width * image_height * 3) ; i++ )
        pixels[i] = 0;

    surface = s;

    doRendering = true;
    isInitalized = false;
}

OffscreenRenderer::~OffscreenRenderer()
{
    delete pixels;
    delete qi;
    delete context;
}

void OffscreenRenderer::initView()
{
    glViewport(0, 0, image_width, image_height);

    double aspect;
//    if(vheight == 0)
//        vheight = 1;
    aspect = 1.0 * image_width / image_height;
    if (aspect<0.0001)
        aspect=1.0;
    if(aspect <= 1)
        glFrustum(-0.0005, 0.0005, -0.0005/aspect, 0.0005/aspect, 0.001, 1000.0);
    else
        glFrustum(-0.0005*aspect, 0.0005*aspect, -0.0005, 0.0005, 0.001, 1000.0);
}

void OffscreenRenderer::initBuffers()
{
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA, image_width, image_height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glGenRenderbuffers(1, &depth_rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, depth_rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, image_width, image_height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, rbo);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth_rbo);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void OffscreenRenderer::draw()
{
    glColor3f(0.0,1.0,0.0);

    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glDrawBuffer(GL_COLOR_ATTACHMENT0);

    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


//    float vertices2[] = {   -5.0f, 5.0f, -15.0f,
//                           5.0f, -5.0f, -15.0f,
//                           5.0f, 5.0f, -15.0f,
//                       };

//    glEnableClientState(GL_VERTEX_ARRAY);
//    glVertexPointer(3, GL_FLOAT, 0, vertices2);
//    glDrawArrays(GL_TRIANGLES, 0, 3);
//    glDisableClientState(GL_VERTEX_ARRAY);

    glBegin(GL_TRIANGLES);
        glVertex3f( -5.0f, 5.0f, -15.0f);
        glVertex3f( 5.0f, -5.0f, -15.0f);
        glVertex3f( 5.0f, 5.0f, -15.0f);
    glEnd();

    glReadBuffer(GL_COLOR_ATTACHMENT0);
    glReadPixels(0,0, image_width, image_height,
                 GLenum(GL_RGB), GLenum(GL_UNSIGNED_BYTE), pixels);

    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    qi = new QImage(pixels, image_width, image_height, QImage::Format_RGB888);

    if(qi->save("image.PNG", 0, -1))
        std::cerr << "Image saved" << std::endl;
    else
        std::cerr << "There was a problem saving the image" << std::endl;
}

void OffscreenRenderer::run()
{
    while(doRendering)
    {
        if(!isInitalized)
        {
            isInitalized = true;

            context = new QOpenGLContext();
            context->setFormat(surface->format());
            context->create();
            context->makeCurrent(surface);

            initBuffers();
            initView();
        }

        draw();
        sleep(1);
    }
}

void OffscreenRenderer::stop()
{
    doRendering = false;
}
