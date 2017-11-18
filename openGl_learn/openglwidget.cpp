#include "openglwidget.h"

GLfloat lightAmbient[4] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat lightDiffuse[4] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat lightPosition[4] = { 0.0, 0.0, 2.0, 1.0 };

OpenglWidget::OpenglWidget(QWidget *parent)
    :QGLWidget(parent)
{
    initWidget();
    initializeGL();

    xRot = yRot = zRot = 0.0;
    zoom = -5.0;
    xSpeed = ySpeed = 0.0;

    filter = 0;

    light = false;
    blend = false;

    //===========
    tilt = 90.0;
    spin = 0.0;
    loop = 0;

    twinkle = false;

    startTimer( 5 );
}

void OpenglWidget::initializeGL()
{
    //纹理
   loadGLTextures();
   glEnable( GL_TEXTURE_2D );


   glShadeModel(GL_SMOOTH);
   glClearColor(0.0,0.0,0.0,0.0);
   glClearDepth(1.0);
   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LEQUAL);
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

   //灯光
   glLightfv( GL_LIGHT1, GL_AMBIENT, lightAmbient );
   glLightfv( GL_LIGHT1, GL_DIFFUSE, lightDiffuse );
   glLightfv( GL_LIGHT1, GL_POSITION, lightPosition );

   glEnable( GL_LIGHT1 );

//   glColor4f( 1.0, 1.0, 1.0, 0.5 );
   //混合---融合----透明
   glBlendFunc( GL_SRC_ALPHA, GL_ONE );
   glEnable( GL_BLEND );

   //

}

void OpenglWidget::initWidget()
{
    setGeometry( 400, 200, 640, 480 );
    setWindowTitle(tr("opengl demo"));
}

void OpenglWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(  0.0,  0.0, zoom );

//    glTranslatef( 0,  0.0, -6.0 );

    draw3DCorDSystem();

    drawStars();

//    drawTriangularObj();
    draw3DCubeTextureObj();
    xRot += xSpeed;
    yRot += ySpeed;
}




void OpenglWidget::draw3DCorDSystem()
{

    // 设置画笔颜色（RGB：此处为红色）
    // 绘制x、y、z轴线段

    //void glutWireCone(GLdouble radius, GLdouble height, GLint slices, GLint stacks);
    //radius 圆锥体基底的半径，height 圆锥体的高度，stacks条纬线，slice条经线


    glLineWidth(3.0);
    //x轴
    glBegin(GL_LINES);
    glColor3f(1.0f,0.0f,0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(2.0, 0.0f, 0.0f);
    glEnd();

    glPushMatrix();
    glTranslatef(2.0, 0.0f, 0.0f);
    glRotatef(90.0f,0.0f,1.0f,0.0f);
    glutWireCone(0.027,0.09,10,10);
    glPopMatrix();

    //y轴
    glBegin(GL_LINES);
     glColor3f(0.0f,1.0f,0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0, 2.0f, 0.0f);
    glEnd();

    glPushMatrix();
    glTranslatef(0.0, 2.0f, 0.0f);
    glRotatef(270.0f,1.0f,0.0f,0.0f);
    glutWireCone(0.027,0.09,10,10);
    glPopMatrix();

    //z轴
    glBegin(GL_LINES);
     glColor3f(0.0f,0.0f,2.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0, 0.0f, 1.0f);
    glEnd();

    glPushMatrix();
    glTranslatef(0.0, 0.0f, 2.0f);
    glRotatef(90.0f,0.0f,0.0f,1.0f);
    glutWireCone(0.027,0.09,10,10);
    glPopMatrix();
}

void OpenglWidget::drawCubeObj()
{
    glBegin( GL_QUADS );

    glColor4f(1, 0, 0,0.4);
    glVertex3f(-1,1,1);
    glVertex3f(-1,1,-1);
    glVertex3f(-1,-1,-1);
    glVertex3f(-1,-1,1);

    glColor4f(0, 0, 1,1);
    glVertex3f(-1,1,-1);
    glVertex3f(-1,-1,-1);
    glVertex3f(1,-1,-1);
    glVertex3f(1,1,-1);

    glColor4f(0, 1, 0,0.6);
    glVertex3f(1,1,-1);
    glVertex3f(1,-1,-1);
    glVertex3f(1,-1,1);
    glVertex3f(1,1,1);

    glColor4f(0, 0, 1,0.3);
    glVertex3f(1,-1,1);
    glVertex3f(1,1,1);
    glVertex3f(-1,1,1);
    glVertex3f(-1,-1,1);

    glColor4f(0, 1, 0,0.2);
    glVertex3f(-1,1,1);
    glVertex3f(1,1,1);
    glVertex3f(1,1,-1);
    glVertex3f(-1,1,-1);

    glColor4f(0, 0, 1,0.8);
    glVertex3f(-1,-1,1);
    glVertex3f(-1,-1,-1);
    glVertex3f(1,-1,-1);
    glVertex3f(1,-1,1);

    glEnd();
}

void OpenglWidget::drawTriangularObj()
{
    glRotatef( xRot,  1.0,  0.0,  0.0 );
    glRotatef( yRot,  0.0,  1.0,  0.0 );
    glBegin( GL_TRIANGLES );

    glColor4f( 1.0, 0.0, 0.0,1 );
    glVertex3f(  0.0,  1.0,  0.0 );
    glColor3f( 0.0, 0.0, 1.0 );
    glVertex3f( -1.0, -1.0, -1.0 );
    glColor3f( 0.0, 1.0, 0.0 );
    glVertex3f( -1.0, -1.0,  1.0 );

    glColor4f( 1.0, 0.0, 0.0,1);
    glVertex3f(  0.0,  1.0,  0.0 );
    glColor3f( 0.0, 0.0, 1.0 );
    glVertex3f(  1.0, -1.0,  1.0 );
    glColor3f( 0.0, 1.0, 0.0 );
    glVertex3f(  1.0, -1.0, -1.0 );

    glColor4f( 1.0, 0.0, 0.0,1 );
    glVertex3f(  0.0,  1.0,  0.0 );
    glColor3f( 0.0, 1.0, 0.0 );
    glVertex3f( -1.0, -1.0,  1.0 );
    glColor3f( 0.0, 0.0, 1.0 );
    glVertex3f(  1.0, -1.0,  1.0 );


    glColor4f( 1.0, 0.0, 0.0,1 );
    glVertex3f(  0.0,  1.0,  0.0 );
    glColor3f( 0.0, 1.0, 0.0 );
    glVertex3f(  1.0, -1.0, -1.0 );
    glColor3f( 0.0, 0.0, 1.0 );
    glVertex3f( -1.0, -1.0, -1.0 );

    glEnd();
}

void OpenglWidget::draw3DCubeTextureObj()
{

    glRotatef( xRot,  1.0,  0.0,  0.0 );
    glRotatef( yRot,  0.0,  1.0,  0.0 );
    glBindTexture( GL_TEXTURE_2D, texture[filter] );

    glBegin( GL_QUADS );
      glNormal3f( 0.0, 0.0, 1.0 );
      glTexCoord2f( 0.0, 0.0 ); glVertex3f( -1.0, -1.0,  1.0 );
      glTexCoord2f( 1.0, 0.0 ); glVertex3f(  1.0, -1.0,  1.0 );
      glTexCoord2f( 1.0, 1.0 ); glVertex3f(  1.0,  1.0,  1.0 );
      glTexCoord2f( 0.0, 1.0 ); glVertex3f( -1.0,  1.0,  1.0 );

      glNormal3f( 0.0, 0.0, -1.0 );
      glTexCoord2f( 1.0, 0.0 ); glVertex3f( -1.0, -1.0, -1.0 );
      glTexCoord2f( 1.0, 1.0 ); glVertex3f( -1.0,  1.0, -1.0 );
      glTexCoord2f( 0.0, 1.0 ); glVertex3f(  1.0,  1.0, -1.0 );
      glTexCoord2f( 0.0, 0.0 ); glVertex3f(  1.0, -1.0, -1.0 );

      glNormal3f( 0.0, 1.0, 0.0 );
      glTexCoord2f( 0.0, 1.0 ); glVertex3f( -1.0,  1.0, -1.0 );
      glTexCoord2f( 0.0, 0.0 ); glVertex3f( -1.0,  1.0,  1.0 );
      glTexCoord2f( 1.0, 0.0 ); glVertex3f(  1.0,  1.0,  1.0 );
      glTexCoord2f( 1.0, 1.0 ); glVertex3f(  1.0,  1.0, -1.0 );

      glNormal3f( 0.0, -1.0, 0.0 );
      glTexCoord2f( 1.0, 1.0 ); glVertex3f( -1.0, -1.0, -1.0 );
      glTexCoord2f( 0.0, 1.0 ); glVertex3f(  1.0, -1.0, -1.0 );
      glTexCoord2f( 0.0, 0.0 ); glVertex3f(  1.0, -1.0,  1.0 );
      glTexCoord2f( 1.0, 0.0 ); glVertex3f( -1.0, -1.0,  1.0 );

      glNormal3f( 1.0, 0.0, 0.0 );
      glTexCoord2f( 1.0, 0.0 ); glVertex3f(  1.0, -1.0, -1.0 );
      glTexCoord2f( 1.0, 1.0 ); glVertex3f(  1.0,  1.0, -1.0 );
      glTexCoord2f( 0.0, 1.0 ); glVertex3f(  1.0,  1.0,  1.0 );
      glTexCoord2f( 0.0, 0.0 ); glVertex3f(  1.0, -1.0,  1.0 );

      glNormal3f( -1.0, 0.0, 0.0 );
      glTexCoord2f( 0.0, 0.0 ); glVertex3f( -1.0, -1.0, -1.0 );
      glTexCoord2f( 1.0, 0.0 ); glVertex3f( -1.0, -1.0,  1.0 );
      glTexCoord2f( 1.0, 1.0 ); glVertex3f( -1.0,  1.0,  1.0 );
      glTexCoord2f( 0.0, 1.0 ); glVertex3f( -1.0,  1.0, -1.0 );
    glEnd();


}

void OpenglWidget::loadGLTextures()
{
    QImage tex, buf,tex_star,buf_star;
    if ( !buf.load( "D:/tgl/document/opengl/lesson08/lesson08/data/Glass.bmp" ) )
    {


      qWarning( "Could not read image file, using single-color instead." );

      QImage dummy(3, 3, QImage::Format_Indexed8);
//      QRgb value;
//      value = qRgb(122, 163, 39); // 0xff7aa327
//      QImage dummy( 128, 128, 32 );
      dummy.fill( Qt::green);
      buf = dummy;
    }
    tex = QGLWidget::convertToGLFormat( buf );

    //====================
    if (!buf_star.load( "D:/tgl/document/opengl/lesson09/lesson09/data/Star.bmp" ) )
    {
      qWarning( "Could not read image file, using single-color instead." );

      QImage dummy(3, 3, QImage::Format_Indexed8);
//      QRgb value;
//      value = qRgb(122, 163, 39); // 0xff7aa327
//      QImage dummy( 128, 128, 32 );
      dummy.fill( Qt::green);
      buf_star = dummy;
    }
    tex_star = QGLWidget::convertToGLFormat( buf_star );


    glGenTextures( 1, &texture_star[0] );
    glBindTexture( GL_TEXTURE_2D, texture_star[0] );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexImage2D( GL_TEXTURE_2D, 0, 3, tex_star.width(), tex_star.height(), 0,
        GL_RGBA, GL_UNSIGNED_BYTE, tex_star.bits() );

    glGenTextures( 3, &texture[0] );

    glBindTexture( GL_TEXTURE_2D, texture[0] );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexImage2D( GL_TEXTURE_2D, 0, 3, tex.width(), tex.height(), 0,
        GL_RGBA, GL_UNSIGNED_BYTE, tex.bits() );

    glBindTexture( GL_TEXTURE_2D, texture[1] );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexImage2D( GL_TEXTURE_2D, 0, 3, tex.width(), tex.height(), 0,
        GL_RGBA, GL_UNSIGNED_BYTE, tex.bits() );

    glBindTexture( GL_TEXTURE_2D, texture[2] );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST );
    gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGB, tex.width(), tex.height(),
                       GL_RGBA, GL_UNSIGNED_BYTE, tex.bits() );
}

void OpenglWidget::drawStars()
{
    glBindTexture( GL_TEXTURE_2D, texture_star[0] );

    for ( loop = 0; loop < num; loop++ )
    {
      glLoadIdentity();
      glTranslatef( 0.0, 0.0, zoom );
      glRotatef( tilt, 1.0, 0.0, 0.0 );
      glRotatef( star[loop].angle, 0.0, 1.0, 0.0 );
      glTranslatef( star[loop].dist, 0.0, 0.0 );
      glRotatef( -star[loop].angle, 0.0, 1.0, 0.0 );
      glRotatef( -tilt, 1.0, 0.0, 0.0 );

      if ( twinkle )
      {
        glColor4ub( star[(num-loop)-1].r,
           star[(num-loop)-1].g,
           star[(num-loop)-1].b, 255 );
        glBegin( GL_QUADS );
          glTexCoord2f( 0.0, 0.0 ); glVertex3f( -1.0, -1.0, 0.0 );
          glTexCoord2f( 1.0, 0.0 ); glVertex3f( 1.0, -1.0, 0.0 );
          glTexCoord2f( 1.0, 1.0 ); glVertex3f( 1.0, 1.0, 0.0 );
          glTexCoord2f( 0.0, 1.0 ); glVertex3f( -1.0, 1.0, 0.0 );
        glEnd();
      }

      glRotatef( spin, 0.0, 0.0, 1.0 );
      glColor4ub( star[loop].r, star[loop].g, star[loop].b, 255 );
      glBegin( GL_QUADS );
        glTexCoord2f( 0.0, 0.0 ); glVertex3f( -1.0, -1.0, 0.0 );
        glTexCoord2f( 1.0, 0.0 ); glVertex3f( 1.0, -1.0, 0.0 );
        glTexCoord2f( 1.0, 1.0 ); glVertex3f( 1.0, 1.0, 0.0 );
        glTexCoord2f( 0.0, 1.0 ); glVertex3f( -1.0, 1.0, 0.0 );
      glEnd();

      spin += 0.01;
      star[loop].angle += float(loop)/num;
      star[loop].dist -= 0.01;

      if ( star[loop].dist < 0.0 )
      {
        star[loop].dist += 5.0;
        star[loop].r = rand() % 256;
        star[loop].g = rand() % 256;
        star[loop].b = rand() % 256;
      }
    }
}

void OpenglWidget::timerEvent(QTimerEvent *)
{
    updateGL();
}

void OpenglWidget::resizeGL(int width, int height)
{
    if(0 == height)
    {
         height = 1;
    }

       glViewport(0, 0, (GLint)width, (GLint)height);

       glMatrixMode(GL_PROJECTION);

       glLoadIdentity();

     //  gluPerspective(45.0, (GLfloat)width/(GLfloat)height, 0.1, 100.0);

       GLdouble aspectRatio = (GLfloat)width/(GLfloat)height;
       GLdouble zNear = 0.1;
       GLdouble zFar = 100.0;

       GLdouble rFov = 45.0 * 3.14159265 / 180.0;
        glFrustum( -zNear * tan( rFov / 2.0 ) * aspectRatio,
                  zNear * tan( rFov / 2.0 ) * aspectRatio,
                  -zNear * tan( rFov / 2.0 ),
                  zNear * tan( rFov / 2.0 ),
                  zNear, zFar );

       glMatrixMode(GL_MODELVIEW);

       glLoadIdentity();
}

void OpenglWidget::keyPressEvent(QKeyEvent *e)
{
    switch ( e->key() )
    {
    case Qt::Key_L:
      light = !light;
      if ( !light )
      {
        glDisable( GL_LIGHTING );
      }
      else
      {
        glEnable( GL_LIGHTING );
      }
      updateGL();
      break;
    case Qt::Key_B:
      blend = !blend;
      if ( blend )
      {
        glEnable( GL_BLEND );
        glDisable( GL_DEPTH_TEST );
      }
      else
      {
        glDisable( GL_BLEND );
        glEnable( GL_DEPTH_TEST );
      }
      updateGL();
      break;
    case Qt::Key_F:
      filter += 1;
      if ( filter > 2 )
      {
        filter = 0;
      }
      updateGL();
      break;
    case Qt::Key_Z:
      zoom -= 0.2;
      updateGL();
      break;
    case Qt::Key_M:
      zoom += 0.2;
      updateGL();
      break;
    case Qt::Key_Up:
      xSpeed -= 0.01;
      updateGL();
      break;
    case Qt::Key_Down:
      xSpeed += 0.01;
      updateGL();
      break;
    case Qt::Key_Right:
      ySpeed += 0.01;
      updateGL();
      break;
    case Qt::Key_Left:
      ySpeed -= 0.01;
      updateGL();
      break;

    case Qt::Key_T:
      twinkle = !twinkle;
      updateGL();
      break;

    case Qt::Key_Escape:
      close();
    }
}


#if 0
void OpenglWidget::drawCubeCoordinates()
{
        /*****网格绘制*****/

        /*****使用颜色混合来消除一些锯齿， 主要针对点和线

        以及不相互重叠的多边形的反锯齿。*****/

        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
        glEnable(GL_POINT_SMOOTH);                   //设置反走样
        glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);       //设置反走样
        glEnable(GL_LINE_SMOOTH);
        glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
        glEnable(GL_POLYGON_SMOOTH);
        glHint(GL_POLYGON_SMOOTH_HINT,GL_NICEST);

        //绘制立体坐标系
        GLUquadricObj *objCylinder =gluNewQuadric();
        glRotatef(-45,0.0,1.0,0.0);

        //确定坐标系原点
        glPushMatrix();
        glColor3f(1.0f,1.0f, 1.0f);
        glTranslatef(-5,0,-5);
        glutSolidSphere(0.2,20,20);
        //glutSolidTorus(0.2,1,10,10);圆环

        glPopMatrix();

        //画网格线

        coordpoint cpoint1 = {-5,0,-5};
        coordpoint cpoint2 = {5,0,5};
        glColor3f(0.9f,0.9f,0.9f);
        GLGrid(cpoint1,cpoint2,10);

        //画网格线

        glPushMatrix();
        {
            glRotatef(90,1.0,0.0,0.0);
            glTranslatef(0.0f,-5,-5);
            coordpoint cpoint3 ={-5,00,-5};
            coordpoint cpoint4 = {5,00,5};
            glColor3f(0.9f,0.9f,0.0f);
            GLGrid(cpoint3,cpoint4,10);


            //半透明绘制
            //glDepthMask(GL_FALSE);
            //glColor3f(0.3,0.3,0.0);
            //glTranslatef(0.0,5,0.0);
            //glutSolidSphere(2,20,20);
            //glDepthMask(GL_TRUE);
        }

        glPopMatrix();

        //画网格线
        glPushMatrix();
            glRotatef(90,0.0,0.0,1.0);
            glTranslatef(5,5,-0);
            coordpoint cpoint5 ={-5,0,-5};
            coordpoint cpoint6 = {5,0,5};
            glColor3f(0.0f,0.9f,0.0f);
            GLGrid(cpoint5,cpoint6,10);
        glPopMatrix();



        //画坐标轴

        glPushMatrix();
        {
            glColor3f(0.0f, 1,0.0f);
            glTranslatef(-5,0,-5);
            gluCylinder(objCylinder,0.05, 0.05, AXES_LEN, 10, 5);           //X
            glTranslatef(0,0,AXES_LEN);
            gluCylinder(objCylinder,0.2, 0.0, 0.5, 10, 5);                 //X
        }
        glPopMatrix();


        glPushMatrix();
        {
            glTranslatef(-5,0,-5);
            glTranslatef(0,0.2,AXES_LEN);
            glRotatef(90,0.0,1.0,0.0);
            GLPrint("X");                                               // Print GL Text ToThe Screen
        }
        glPopMatrix();



        //画坐标轴
        glPushMatrix();
        {
            glColor3f(1, 0,0.0f);
            glTranslatef(-5,0,-5);
            glRotatef(90,0.0,1.0,0.0);
            gluCylinder(objCylinder,0.05, 0.05, AXES_LEN, 10, 5);           //Y
            glTranslatef(0,0,AXES_LEN);
            gluCylinder(objCylinder,0.2, 0.0, 0.5, 10, 5);                 //Y
        }
        glPopMatrix();

        glPushMatrix();
        {
            glTranslatef(-5,0,-5);
            glRotatef(90,0.0,1.0,0.0);
            glTranslatef(0,0.2,AXES_LEN);
            glRotatef(90,0.0,1.0,0.0);
            GLPrint("Y");                                               // Print GL Text ToThe Screen
        }
        glPopMatrix();

        //画坐标轴
        glPushMatrix();
        {
            glColor3f(1, 1,0.0f);
            glTranslatef(-5,0,-5);
            glRotatef(-90,1.0,0.0,0.0);
            gluCylinder(objCylinder,0.05, 0.05, AXES_LEN, 10, 5);           //Z
            glTranslatef(0,0,AXES_LEN);
            gluCylinder(objCylinder,0.2, 0.0, 0.5, 10, 5);                 //Z
        }
        glPopMatrix();

        glPushMatrix();
        {
            glTranslatef(-5,0,-5);
            glRotatef(-90,1.0,0.0,0.0);
            glTranslatef(0.0,0.6,AXES_LEN);
            glRotatef(90,0.0,1.0,0.0);
            glRotatef(90,0.0,0.0,1.0);
            GLPrint("Z");                                               // Print GL Text ToThe Screen
        }
        glPopMatrix();


        /*****取消反锯齿*****/
        glDisable(GL_BLEND);
        glDisable(GL_LINE_SMOOTH);
        glDisable(GL_POINT_SMOOTH);
        glDisable(GL_POLYGON_SMOOTH);
}

void OpenglWidget::GLGrid(coordpoint &pt1, coordpoint &pt2, int num)
{
     const float _xLen = (pt2.x -pt1.x) / num;
     const float _yLen = (pt2.y - pt1.y) / num;
     const float _zLen = (pt2.z - pt1.z) / num;

     glLineWidth(1.0f);
     glLineStipple(1, 0x0303);//线条样式
     glBegin(GL_LINES);
     glEnable(GL_LINE_SMOOTH);
     //glColor3f(0.0f,0.0f, 1.0f); //白色线条

     int xi = 0;
     int yi = 0;
     int zi = 0;

     //绘制平行于X的直线
     for (zi = 0; zi <= num; zi++)
     {
         float z = _zLen * zi + pt1.z;
         for (yi = 0; yi <= num; yi++)
         {
            float y = _yLen * yi +pt1.y;
            glVertex3f(pt1.x, y, z);
            glVertex3f(pt2.x, y, z);
         }
     }

     //绘制平行于Y的直线
     for (zi = 0; zi <= num; zi++)
     {
         float z = _zLen * zi + pt1.z;
         for (xi = 0; xi <= num; xi++)
         {
            float x = _xLen * xi +pt1.x;
            glVertex3f(x, pt1.y, z);
            glVertex3f(x, pt2.y, z);
         }
     }

     //绘制平行于Z的直线
     for (yi = 0; yi <= num; yi++)
     {
         float y = _yLen * yi + pt1.y;
         for (xi = 0; xi <= num; xi++)
         {
            float x = _xLen * xi +pt1.x;
            glVertex3f(x, y, pt1.z);
            glVertex3f(x, y, pt2.z);
          }
      }
        glEnd();

}

void OpenglWidget::GLDrawSpaceAxes()
{
    GLUquadricObj *objCylinder =gluNewQuadric();
    glPushMatrix();
    {
        glColor3f(1.0f,1.0f, 1.0f);
        glutSolidSphere(0.25,6,6);
        glColor3f(0.0f,0.0f, 1.0f);
        gluCylinder(objCylinder,0.1, 0.1, AXES_LEN, 10, 5);         //Z
        glTranslatef(0,0,AXES_LEN);
        gluCylinder(objCylinder,0.3, 0.0, 0.6, 10, 5);                 //Z
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(0,0.5,AXES_LEN);
        glRotatef(90,0.0,1.0,0.0);
        GLPrint("Z");                                               // Print GL Text ToThe Screen
    }
    glPopMatrix();

    glPushMatrix();
    {
        glColor3f(0.0f,1.0f, 0.0f);
        glRotatef(-90,1.0,0.0,0.0);
        gluCylinder(objCylinder,0.1, 0.1, AXES_LEN, 10, 5);         //Y
        glTranslatef(0,0,AXES_LEN);
        gluCylinder(objCylinder,0.3, 0.0, 0.6, 10, 5);                 //Y
    }
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0.5,AXES_LEN,0);
    GLPrint("Y");                                               // Print GL Text ToThe Screen
    glPopMatrix();


    glPushMatrix();
    {
        glColor3f(1.0f,0.0f, 0.0f);
        glRotatef(90,0.0,1.0,0.0);
        gluCylinder(objCylinder,0.1, 0.1, AXES_LEN, 10, 5);         //X
        glTranslatef(0,0,AXES_LEN);
        gluCylinder(objCylinder,0.3, 0.0, 0.6, 10, 5);                 //X
    }
    glPopMatrix();


    glPushMatrix();
    glTranslatef(AXES_LEN,0.5,0);
    GLPrint("X");                                               // Print GL Text ToThe Screen
    glPopMatrix();


}
#endif
