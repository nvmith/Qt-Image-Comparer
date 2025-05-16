#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSplitter>
#include <QPushButton>
#include <QLabel>

#include "customgraphicsview.h" // 이제 직접 확대/축소/스크롤이 가능한 뷰

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
    void loadLeftImage();  // 왼쪽 이미지를 불러오는 함수
    void loadRightImage(); // 오른쪽 이미지를 불러오는 함수
    void compareImage(); // 이미지 비교 함수
    QImage paddedImage(const QImage& src, const QSize& targetSize, const QColor& fillColor = Qt::black);

private:
    Ui::MainWindow *ui;

    CustomGraphicsView* leftView;  // 왼쪽 이미지를 보여줄 뷰
    CustomGraphicsView* rightView; // 오른쪽 이미지를 보여줄 뷰

    QPushButton* loadLeftButton;   // 왼쪽 이미지 불러오기 버튼
    QPushButton* loadRightButton;  // 오른쪽 이미지 불러오기 버튼
    QPushButton* compareButton; // 비교 버튼

    QSplitter* splitter;  // 두 뷰를 나누는 스플리터
    QWidget* container;   // 스플리터를 감싸는 컨테이너
};

#endif // MAINWINDOW_H
