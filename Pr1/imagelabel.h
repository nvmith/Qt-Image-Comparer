#ifndef IMAGELABEL_H
#define IMAGELABEL_H

#include <QLabel>
#include <QWheelEvent>
#include <QAbstractScrollArea>

class ImageLabel : public QLabel
{
    Q_OBJECT
public:
    explicit ImageLabel(QWidget *parent = nullptr);
    void setImage(const QPixmap &pixmap);
    QSize sizeHint() const override;
    double getScaleFactor() const;
    void setScrollArea(QAbstractScrollArea* area);

protected:
    void wheelEvent(QWheelEvent *event) override;

private:
    QPixmap originalPixmap;   //원본 이미지 저장용
    double scaleFactor = 1.0; //확대/축소 비율
    void updateDisplay();
    QAbstractScrollArea* scrollArea = nullptr;

signals:
};

#endif // IMAGELABEL_H
