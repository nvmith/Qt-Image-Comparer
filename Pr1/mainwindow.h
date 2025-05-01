#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void loadImage(); //슬롯 함수 선언
    //슬롯 함수: 특정 이벤트가 발생했을 때 실행될 함수
    //시그널: 이벤트를 발생시키는 주체

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
