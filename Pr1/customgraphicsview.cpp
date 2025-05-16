#include "customgraphicsview.h"

#include <QWheelEvent>
#include <QTimer>

CustomGraphicsView::CustomGraphicsView(QWidget *parent)
    : QGraphicsView(parent), scene(new QGraphicsScene(this)), pixmapItem(nullptr), initialScale(0.0)
{
    setScene(scene);
    setDragMode(QGraphicsView::ScrollHandDrag); // 드래그로 스크롤 가능
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse); // 마우스 포인터 기준 확대/축소
    setBackgroundBrush(Qt::white); // 기본 배경 흰색
}

// 이미지를 불러와서 뷰에 띄우는 함수
void CustomGraphicsView::setImage(const QPixmap &pixmap)
{
    scene->clear(); // 기존 이미지 삭제
    pixmapItem = scene->addPixmap(pixmap); // 새로운 이미지 추가
    scene->setSceneRect(pixmap.rect()); // 이미지 기준으로 씬 사이즈 맞춤

    fitInView(pixmapItem, Qt::KeepAspectRatio); // 화면 맞추기 (임시 조정)

    QTimer::singleShot(0, this, [this]() { // Qt 이벤트 루프 한 번 돌린 후
        fitInView(pixmapItem, Qt::KeepAspectRatio);  // 한 번 더 (최종 조정)
        initialScale = transform().m11(); // 정확한 초기 스케일 저장
        setTransform(QTransform().scale(initialScale, initialScale)); // 정확히 맞추기
    });
}

// 휠로 확대/축소하는 함수
void CustomGraphicsView::wheelEvent(QWheelEvent *event)
{
    if (!pixmapItem)
        return;

    double factor;
    if (event->angleDelta().y() > 0)
        factor = 1.1; // 휠 위로 -> 확대
    else
        factor = 0.9; // 휠 아래로 -> 축소

    double currentScale = transform().m11();
    double newScale = currentScale * factor;

    // 최소한 초기 화면 스케일(initialScale)보다 작아지지 않게 제한
    if (newScale < initialScale)
        newScale = initialScale;

    if (newScale > 5.0) // 최대 5배 확대 제한
        newScale = 5.0;

    // 새 transform 적용
    QTransform t;
    t.scale(newScale, newScale);
    setTransform(t);

    event->accept();
}

// 창 사이즈 바뀔 때 자동으로 맞추는 함수
void CustomGraphicsView::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);

    if (pixmapItem && transform().m11() == initialScale)
    {
        fitInView(pixmapItem, Qt::KeepAspectRatio);
    }
}

QPixmap CustomGraphicsView::getPixmap() const
{
    if(pixmapItem)
        return pixmapItem->pixmap();
    return QPixmap(); // 비어있는 경우
}
