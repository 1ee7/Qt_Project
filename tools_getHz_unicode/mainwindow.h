#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QByteArray>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_create_clicked();

private:
    Ui::MainWindow *ui;

    QString str_Hz;
    unsigned short m_nHzSize;
    QString str_Unicode;
};

#endif // MAINWINDOW_H
