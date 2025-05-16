#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->resize(1600, 900); // 창 크기 기본 설정

    // 왼쪽/오른쪽 이미지 뷰 생성 (CustomGraphicsView 사용)
    leftView = new CustomGraphicsView(this);
    rightView = new CustomGraphicsView(this);

    // 화면 최소 크기 설정
    leftView->setMinimumSize(800, 800);
    rightView->setMinimumSize(800, 800);

    // 스플리터로 좌우 나눔
    splitter = new QSplitter(Qt::Horizontal, this);
    splitter->addWidget(leftView);
    splitter->addWidget(rightView);
    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 1);

    // 스플리터를 감쌀 컨테이너 -> 바로 mainLayout에 붙여도되나 향후 여백 추가나 정렬 조정을 더 쉽게 하기 위해 중간 컨테이너로 한 번 감쌈
    container = new QWidget(this);
    QVBoxLayout* containerLayout = new QVBoxLayout(container);
    containerLayout->addWidget(splitter);

    // 왼쪽/오른쪽 버튼 생성
    loadLeftButton = new QPushButton("왼쪽 이미지 불러오기", this);
    loadRightButton = new QPushButton("오른쪽 이미지 불러오기", this);
    compareButton = new QPushButton("비교 시작", this);

    connect(loadLeftButton, &QPushButton::clicked, this, &MainWindow::loadLeftImage);
    connect(loadRightButton, &QPushButton::clicked, this, &MainWindow::loadRightImage);
    connect(compareButton, &QPushButton::clicked, this, &MainWindow::compareImage);

    // 버튼들 가로 배치
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(loadLeftButton);
    buttonLayout->addWidget(compareButton);
    buttonLayout->addWidget(loadRightButton);
    //buttonLayout->addStretch(); // 가운데를 비워서 왼쪽/오른쪽 버튼이 양 끝에 정렬되도록 함

    // 전체 메인 레이아웃
    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addWidget(container);
    mainLayout->addLayout(buttonLayout);

    // 이 레이아웃을 중앙 위젯으로 설정
    QWidget* centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    // 공간 분배 -> 뷰어 영역이 전체 높이의 90%, 버튼은 10% 차지하게 설정
    mainLayout->setStretch(0, 9);
    mainLayout->setStretch(1, 1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 왼쪽 이미지 불러오는 함수
void MainWindow::loadLeftImage()
{
    QString fileName = QFileDialog::getOpenFileName(this, "왼쪽 이미지 선택", "", "Image Files (*.png *.jpg *.bmp)");
    if (!fileName.isEmpty())
    {
        QPixmap pixmap(fileName);
        leftView->setImage(pixmap); // 뷰에 이미지 넘기기
    }
}

// 오른쪽 이미지 불러오는 함수
void MainWindow::loadRightImage()
{
    QString fileName = QFileDialog::getOpenFileName(this, "오른쪽 이미지 선택", "", "Image Files (*.png *.jpg *.bmp)");
    if (!fileName.isEmpty())
    {
        QPixmap pixmap(fileName);
        rightView->setImage(pixmap);
    }
}

// 이미지 비교 함수
void MainWindow::compareImage()
{
    // 이미지가 비어있으면 아무 것도 하지 않음
    if (leftView->getPixmap().isNull() || rightView->getPixmap().isNull())
        return;

    QColor diffColor = QColorDialog::getColor(Qt::red, this, "차이 색상 선택"); // 사용자가 직접 차이 색상 선택

    if (!diffColor.isValid()) { // 색을 선택하지 않으면 return
        return;
    }

    QImage imgA = leftView->getPixmap().toImage();
    QImage imgB = rightView->getPixmap().toImage();

    QSize targetSize = imgA.size().expandedTo(imgB.size()); // 각각의 가로/세로 중 더 큰 값

    QImage paddedA = paddedImage(imgA, targetSize);
    QImage paddedB = paddedImage(imgB, targetSize);

    int diffCount = 0;
    int totalPixels = targetSize.width() * targetSize.height();

    // 결과 이미지: 원본 크기, 흰색 배경
    QImage diffImage(targetSize, QImage::Format_ARGB32);
    diffImage.fill(Qt::white);

    for (int y = 0; y < targetSize.height(); ++y) {
        for (int x = 0; x < targetSize.width(); ++x) {
            QColor colorA = paddedA.pixelColor(x, y);
            QColor colorB = paddedB.pixelColor(x, y);

            if (colorA != colorB) {
                diffImage.setPixelColor(x, y, diffColor); // 차이가 나는 픽셀은 빨간색으로 표시
                diffCount++;
            } else {
                // 같은 픽셀은 원래 색상 그대로
                diffImage.setPixelColor(x, y, colorA);
            }
        }
    }

    // 새로운 QPixmap으로 결과 생성
    QPixmap resultPixmap = QPixmap::fromImage(diffImage);

    double diffRatio = (double)diffCount / totalPixels * 100.0; // 차이 비율 계산
    QString diffText = QString("차이 비율: %1%").arg(QString::number(diffRatio, 'f', 2)); // 차이 난 픽셀의 비율을 소수점 2자리로 문자열 포맷팅

    // 비교 결과 이미지를 새로운 CustomGraphicsView에 표시하고 팝업창으로 띄움
    CustomGraphicsView* resultView = new CustomGraphicsView();
    resultView->setImage(resultPixmap);

    // 차이 비율 라벨
    QLabel* diffLabel = new QLabel(diffText);
    diffLabel->setAlignment(Qt::AlignCenter);
    diffLabel->setStyleSheet("font-size: 20px; padding: 10px;");

    QWidget* resultWindow = new QWidget();
    resultWindow->setWindowTitle("비교 결과");
    QVBoxLayout* layout = new QVBoxLayout(resultWindow);
    layout->addWidget(resultView);
    layout->addWidget(diffLabel);

    resultWindow->resize(800, 850);
    resultWindow->show();
}

// 원본 이미지를 중앙에 배치하고, 주변 여백을 지정된 색으로 채운 새 이미지 반환
QImage MainWindow::paddedImage(const QImage& src, const QSize& targetSize, const QColor& fillColor)
{
    QImage padded(targetSize, QImage::Format_ARGB32);
    padded.fill(fillColor);

    QPainter painter(&padded);
    QPoint offset(
        (targetSize.width() - src.width()) / 2,
        (targetSize.height() - src.height()) / 2
        );
    painter.drawImage(offset, src);

    return padded;
}
