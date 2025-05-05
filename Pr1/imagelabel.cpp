#include "imagelabel.h"

ImageLabel::ImageLabel(QWidget *parent)
    : QLabel{parent}
{}

void ImageLabel::setImage(const QPixmap &pixmap) //이미지를 받아서 내부에 저장하고, 초기 배율로 표시
{
    originalPixmap = pixmap;

    //화면 크기 가져오기
    QSize screenSize = QGuiApplication::primaryScreen()->availableGeometry().size();
    screenSize.setHeight(screenSize.height() - 100);

    //이미지 크기 기준 배율 계산
    QSize imageSize = originalPixmap.size();
    double wRatio = static_cast<double>(screenSize.width()) / imageSize.width();
    double hRatio = static_cast<double>(screenSize.height()) / imageSize.height();

    scaleFactor = std::min(wRatio, hRatio);

    //너무 확대되지 않도록 제한
    if (scaleFactor > 1.0)
        scaleFactor = 1.0;

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
    if(event->angleDelta().y()>0) //휠을 위로 돌리면
        scaleFactor *= 1.1;
    else //휠을 아래로 돌리면
        scaleFactor *= 0.9;

    if (scaleFactor < 0.2) //최대/최소 비율 제한
        scaleFactor = 0.2;
    else if (scaleFactor > 5.0)
        scaleFactor = 5.0;

    updateDisplay();
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
