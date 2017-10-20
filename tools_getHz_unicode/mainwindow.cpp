#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qdebug.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("汉字Unicode转化器");
    ui->plainTextEdit_getHz->setPlainText("请输入中文");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_create_clicked()
{
    str_Hz = ui->plainTextEdit_getHz->toPlainText();

    unsigned char c_tmp[3];
    bool btmp=false;

    m_nHzSize = str_Hz.size();
    str_Unicode.clear();
    QString str_tmp;
    QByteArray byteArrray_tmp;
     byteArrray_tmp = str_Hz.toLocal8Bit();

      char *code = byteArrray_tmp.data();

      unsigned int len = byteArrray_tmp.size();

       while(len>0)
       {
           if((*code)&0x80)
           {
               c_tmp[0] = (unsigned char )(*code)&0xff;
               c_tmp[1] = (unsigned char )(*(code+1))&0xff;
               c_tmp[2] = (unsigned char )(*(code+2))&0xff;

               str_tmp.sprintf("0x%x%x%x",c_tmp[0],c_tmp[1],c_tmp[2]);

               qDebug()<<"data is "<<str_tmp;

               code += 3;
               len -= 3;

             ui->statusBar->showMessage("正在生成....");
           }
           else
           {
               ui->statusBar->showMessage("警告：输入内容中---含有非汉字内容！！");

               btmp = true;
               code += 1;
               len -= 1;

                break;
           }

          str_Unicode.append(str_tmp);
          str_Unicode.append(",");
       }

       ui->plainTextEdit_putUnicode->setPlainText(str_Unicode);

       ui->statusBar->showMessage("  完成.");
       if(btmp)
       {
            ui->statusBar->showMessage("完成. 警告：输入内容中---含有非汉字内容！！");
       }


}

