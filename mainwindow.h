#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString receStr;
    QString datatosend = "AAA";

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void resizeEvent(QResizeEvent * event);


    void connection();
    void dataReceive();
    void disconnected();

private:
    Ui::MainWindow *ui;
    QString filename;
    QTcpServer *newserver;
    QTcpSocket *newsocket;

};

#endif // MAINWINDOW_H
