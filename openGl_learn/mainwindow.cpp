#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
 //   pGLWidget = new OpenglWidget();
//    pGLWidget->paintGL();
  //  pGLWidget->updateOverlayGL();

    ui->MyOpenGLWidget->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
