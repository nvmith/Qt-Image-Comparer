#include "imagelabel.h"
#include <QScrollBar>

ImageLabel::ImageLabel(QWidget *parent)
    : QLabel{parent}
{
    setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
}

void ImageLabel::setImage(const QPixmap &pixmap) //이미지를 받아서 내부에 저장하고, 초기 배율로 표시
{
    originalPixmap = pixmap;

    scaleFactor = 1.0;

    // //화면 크기 가져오기
    // QSize screenSize = QGuiApplication::primaryScreen()->availableGeometry().size();
    // screenSize.setHeight(screenSize.height() - 100);

    // //이미지 크기 기준 배율 계산
    // QSize imageSize = originalPixmap.size();
    // double wRatio = static_cast<double>(screenSize.width()) / imageSize.width();
    // double hRatio = static_cast<double>(screenSize.height()) / imageSize.height();

    // scaleFactor = std::min(wRatio, hRatio);

    // //너무 확대되지 않도록 제한
    // if (scaleFactor > 1.0)
    //     scaleFactor = 1.0;

    updateDisplay();
}

void ImageLabel::updateDisplay()
{
    if(!originalPixmap.isNull())
    {
        QPixmap scaled = originalPixmap.scaled(
            originalPixmap.size() * scaleFactor,
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation
        );
        setPixmap(scaled);
        resize(scaled.size());
    }
}

void ImageLabel::wheelEvent(QWheelEvent *event)
{
    if(!scrollArea)
    {
        QLabel::wheelEvent(event);
        return;
    }

    QScrollBar* hBar = scrollArea->horizontalScrollBar();
    QScrollBar* vBar = scrollArea->verticalScrollBar();

    if (!hBar || !vBar) {
        QLabel::wheelEvent(event);
        return;
    }

    // 1. 확대 전: viewport 내 마우스 위치
    QPoint posInViewport = event->position().toPoint();

    // 2. 확대 전: 이미지 안에서 마우스가 가리키는 "픽셀 좌표"
    double relativeX = (hBar->value() + posInViewport.x()) / (double)width();
    double relativeY = (vBar->value() + posInViewport.y()) / (double)height();

    // 3. 확대/축소 실행
    if (event->angleDelta().y() > 0)
        scaleFactor *= 1.1;
    else
        scaleFactor *= 0.9;

    if (scaleFactor < 0.2)
        scaleFactor = 0.2;
    else if (scaleFactor > 5.0)
        scaleFactor = 5.0;

    updateDisplay();

    // 4. 확대 후: 새로운 스크롤 위치 계산
    int newHValue = int(relativeX * width()) - posInViewport.x();
    int newVValue = int(relativeY * height()) - posInViewport.y();

    // 5. 스크롤바 이동
    hBar->setValue(newHValue);
    vBar->setValue(newVValue);
}

double ImageLabel::getScaleFactor() const {
    return scaleFactor;
}

QSize ImageLabel::sizeHint() const {
    if (!originalPixmap.isNull()) {
        return originalPixmap.size() * scaleFactor;
    }
    return QLabel::sizeHint();
}

void ImageLabel::setScrollArea(QAbstractScrollArea* area)
{
    scrollArea = area;
}
