#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QtOpenGL>
#include <GL/gl.h>
#include <qgl.h>
#include <QGLWidget>
#include <GL/glu.h>
#include <windows.h>
#include <glut/glut.h>
#include <QImage>


#pragma comment(lib,"glut32.lib");
const GLuint num = 50;


typedef struct
{
  int r, g, b;
  GLfloat dist;
  GLfloat angle;
}stars;

class OpenglWidget : public QGLWidget
{
public:
    OpenglWidget(QWidget* parent =0);

protected:
    void initializeGL();
    void initWidget();
    virtual void paintGL();
    void resizeGL(int width,int height);

    void keyPressEvent(QKeyEvent *e);

private:
    void draw3DCorDSystem();  //3维坐标系
    void drawCubeObj();        //立方体
    void drawTriangularObj();  //四面体

    void draw3DCubeTextureObj();//带纹理的立方体

    void loadGLTextures();

    void drawStars();

  void timerEvent( QTimerEvent * );
//    void drawCubeCoordinates();
//    void GLGrid(coordpoint& pt1, coordpoint& pt2,int num);
//    void GLDrawSpaceAxes();

private:
    GLfloat m_rotateRectangle;
    GLfloat m_rotateTriangle;

    GLfloat xRot, yRot, zRot;
    GLfloat zoom;
    GLfloat xSpeed, ySpeed;
    GLuint texture[3];
    GLuint filter;

    bool light;
    bool blend;

    GLfloat tilt;
    GLfloat spin;

    GLuint loop;
    GLuint texture_star[1];

    bool twinkle;

    stars star[num];


};

#endif // OPENGLWIDGET_H
