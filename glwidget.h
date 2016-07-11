#ifndef RENDER_H
#define RENDER_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QMatrix4x4>


#include <QPainter>
#include <QFont>


QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    GLWidget(QWidget *parent = 0);
    ~GLWidget();

    QSize minimumSizeHint() const Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;

    void setData(double *drawData);

    bool updateGraph;

    void mousePressEvent( QMouseEvent* ev );


public slots:
    void cleanup();

signals:
    void mousePressed( const QPoint& );

protected:
    void initializeGL() Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;
    void resizeGL(int width, int height) Q_DECL_OVERRIDE;

private:

    void setupVertexAttribs();

    QOpenGLShaderProgram *m_program;


    int _position;
    int _color;

    // For ortho transforms
     int m_projMatrixLoc;

     // For mesh drawing
     GLfloat *mesh_vertices;
     GLfloat *mesh_colors;


     // For signal drawing
     GLfloat *signal_vertices;
     GLfloat *signal_colors;


};

#endif // RENDER_H

