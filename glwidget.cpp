/****************************************************************************
**
** Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "glwidget.h"

#include <QMouseEvent>
#include <QOpenGLShaderProgram>
#include <QCoreApplication>

#include <math.h>


GLWidget::GLWidget(QWidget *parent)
    :  QOpenGLWidget(parent),
     m_program(0)
{

    /*
     * Design scope mesh
    */

    int ind = 0;
    int starty = -10;
    int startx = 0;



    mesh_vertices = new GLfloat[64*3];
    mesh_colors = new GLfloat[64*3];

     for (int i=0;i<11;i++)
    {
        mesh_vertices[ind++] = 0.0f;
        mesh_vertices[ind++] = starty;
        mesh_vertices[ind++] = 0.0f;

        mesh_vertices[ind++] = 2000.0f;
        mesh_vertices[ind++] = starty;
        mesh_vertices[ind++] = 0.0f;

        starty+=2;
    }

    for (int i=0;i<21;i++)
    {
        mesh_vertices[ind++] = startx;
        mesh_vertices[ind++] = 10.0;
        mesh_vertices[ind++] = 0.0f;

        mesh_vertices[ind++] = startx;
        mesh_vertices[ind++] = -10;
        mesh_vertices[ind++] = 0.0f;

        startx+=100;

    }


     for (int i=0;i<64;i++)
     {
         mesh_colors[i*3+0] = 0.1;
         mesh_colors[i*3+1] = 0.2;
         mesh_colors[i*3+2] = 0.05;

     }



     signal_vertices = new GLfloat[3*2000];
     signal_colors = new GLfloat[3*2000];

     ind = 0;


     for (int i=0;i<2000;i++)
     {
         signal_vertices[ind++] = i/1.0;
         signal_vertices[ind++] = 0.0;
         signal_vertices[ind++] = 0.0;

     }


     /*
      *    x, y, z
     */


/*
     ind = 0;
     for (int i=0;i<20000;i++)
     {
         signal_vertices[ind++] = i/1.0;
         signal_vertices[ind++] = 8.0*sin(signal_vertices[ind-1]*2.0*3.14/180.0/30);
         signal_vertices[ind++] = 0.0f;

     }
*/

     /*
      * signal color is red
    */

     ind = 0;


     for (int i=0;i<2000;i++)
     {
         signal_colors[ind++] = 0.8;
         signal_colors[ind++] = 0.05;
         signal_colors[ind++] = 0.05;

     }


     updateGraph = false;





}

GLWidget::~GLWidget()
{

   cleanup();


   delete [] mesh_vertices;
   delete [] mesh_colors;


   delete [] signal_vertices;
   delete [] signal_colors;
}

QSize GLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize GLWidget::sizeHint() const
{
    return QSize(200, 200);
}


void GLWidget::cleanup()
{
    makeCurrent();

    delete m_program;
    m_program = 0;


    doneCurrent();
}


#if defined(WIN32) && !defined(UNIX)
/* Do windows stuff */

const char *shader_vertex_source="\n\
        attribute vec2 position; //the position of the point\n\
        attribute vec3 color;  //the color of the point\n\
        \n\
        varying vec3 vColor;\n\
        uniform mat4 projection;\n\
        void main(void) { //pre-built function\n\
        gl_Position =   projection*vec4(position, 0., 1.0); //0. is the z, and 2 is w\n\
        vColor=color;\n\
        }";


const char *shader_fragment_source="\n\
        #ifdef GL_ES\n\
            precision mediump float;\n\
        #endif\n\
        \n\
        \n\
        \n\
        varying vec3 vColor;\n\
        void main(void) {\n\
        gl_FragColor = vec4(vColor, .1);\n\
        }";
#else

// Burası Ubuntu üzerinde beglabone black için derleme yapmak üzere ayrıldı. SGX ile NVIDA GPU direktifleri uyusmuyor
const char *shader_vertex_source="\n\
        precision mediump float;\n\
        attribute vec3 color;  //the color of the point\n\
        attribute vec2 position; //the position of the point\n\
        uniform mat4 projection;\n\
        \n\
        varying vec3 vColor;\n\
        void main(void) { //pre-built function\n\
            gl_Position = projection*vec4(position, 0., 1.); //0. is the z, and 1 is w\n\
             vColor=color;\n\
        }";


const char *shader_fragment_source="\n\
       precision mediump float;\n\
        \n\
        \n\
        \n\
         varying vec3 vColor;\n\
        void main(void) {\n\
        gl_FragColor = vec4(vColor, .3);\n\
        }";

#endif



void GLWidget::initializeGL()
{
    // In this example the widget's corresponding top-level window can change
    // several times during the widget's lifetime. Whenever this happens, the
    // QOpenGLWidget's associated context is destroyed and a new one is created.
    // Therefore we have to be prepared to clean up the resources on the
    // aboutToBeDestroyed() signal, instead of the destructor. The emission of
    // the signal will be followed by an invocation of initializeGL() where we
    // can recreate all resources.


  connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &GLWidget::cleanup);

    initializeOpenGLFunctions();


    m_program = new QOpenGLShaderProgram;


     m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, shader_vertex_source);
     m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, shader_fragment_source);


  //  m_program->bindAttributeLocation("vertex", 0);
  //  m_program->bindAttributeLocation("normal", 1);
    m_program->link();

    m_program->bind();

        _position = m_program->attributeLocation("position");
        _color = m_program->attributeLocation("color");


        QMatrix4x4 projection;
        projection.ortho(-100, 2100, -11, 11, -1, 1);
        m_program->setUniformValue("projection", projection);


        // Store the vertex attribute bindings for the program.
        setupVertexAttribs();


      qDebug() << "Shader program log:" << m_program->log();


  m_program->release();


}

void GLWidget::setupVertexAttribs()
{

  QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();

  f->glDisable(GL_DEPTH_TEST);





 // f->glEnableVertexAttribArray(_position);
 // f->glEnableVertexAttribArray(_color);



}

void GLWidget::paintGL()
{


 //  qDebug("Update");
    // makeCurrent(); --> This is already called

  if (updateGraph) {








    // Set orthographic projection on the whole window


    QPainter painter;
      painter.begin(this);

      painter.beginNativePainting();


      m_program->bind();


    glClearColor(0.0, 0.4, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


      QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();



      // Load the vertex data
      f->glVertexAttribPointer(_position, 3, GL_FLOAT, GL_FALSE, 0, mesh_vertices);
      f->glEnableVertexAttribArray(_position);

      f->glVertexAttribPointer(_color, 3, GL_FLOAT, GL_FALSE, 0, mesh_colors);
      f->glEnableVertexAttribArray(_color);


      f->glDrawArrays(GL_LINES, 0, 64);

      f->glDisableVertexAttribArray(_position);

      f->glDisableVertexAttribArray(_color);


                 // Load the vertex data
              f->glVertexAttribPointer(_position, 3, GL_FLOAT, GL_FALSE, 0, signal_vertices);
              f->glEnableVertexAttribArray(_position);

              f->glVertexAttribPointer(_color, 3, GL_FLOAT, GL_FALSE, 0, signal_colors);
              f->glEnableVertexAttribArray(_color);


              f->glDrawArrays(GL_LINE_STRIP, 0, 2000);


              f->glDisableVertexAttribArray(_position);

              f->glDisableVertexAttribArray(_color);

              f->glFlush();






     m_program->release();

     painter.endNativePainting();


     int y_pos = (double)(this->height())*23.0/408.0-(this->width()/1.0)/(this->height()/1.0);

     int x_pos = (double)(this->width())*15.0/642.0;


     painter.drawText(x_pos, y_pos, "30");


     painter.end();





      updateGraph = false;

   //   doneCurrent(); --> This will be called automatically





}

}

void GLWidget::resizeGL(int w, int h)
{

 glViewport(0.0, 0.0, w, h);

}

void GLWidget::setData(double *drawData)
{

    int ind = 0;

    for (int i=0;i<2000;i++)
    {
        signal_vertices[ind++] = i/1.0;
        signal_vertices[ind++] = drawData[i]/1.0;
        signal_vertices[ind++] = 0.0;

    }
}

void GLWidget::mousePressEvent(QMouseEvent *ev)
{
    QString x = QString::number(ev->x());
    QString y = QString::number(ev->y());

    qDebug() << "X Pos: " << x << ", Y Pos: " << y;

    qDebug("Height: %d, Width: %d", this->height(), this->width());


}
