#ifndef CUSTOMGRAPHICSVIEW_H
#define CUSTOMGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QGraphicsPixmapItem>

// QGraphicsView를 상속, 확대/축소/스크롤을 자연스럽게 지원하는 이미지 뷰어

class CustomGraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    CustomGraphicsView(QWidget *parent = nullptr);

    void setImage(const QPixmap& pixmap); // 이미지를 뷰에 설정하는 함수
    QPixmap getPixmap() const;

protected:
    void wheelEvent(QWheelEvent *event) override; // 마우스 휠로 확대/축소
    void resizeEvent(QResizeEvent *event) override; // 창 리사이즈 대응

private:
    QGraphicsScene* scene;           // 이미지가 올라가는 씬
    QGraphicsPixmapItem* pixmapItem; // 실제 이미지를 담는 아이템
    double initialScale;             // 처음 fitInView 했을 때 스케일 저장
};

#endif // CUSTOMGRAPHICSVIEW_H
