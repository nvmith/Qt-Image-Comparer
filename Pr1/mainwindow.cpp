#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>

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

    connect(loadLeftButton, &QPushButton::clicked, this, &MainWindow::loadLeftImage);
    connect(loadRightButton, &QPushButton::clicked, this, &MainWindow::loadRightImage);

    // 버튼들 가로 배치
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(loadLeftButton);
    buttonLayout->addStretch(); // 가운데를 비워서 왼쪽/오른쪽 버튼이 양 끝에 정렬되도록 함
    buttonLayout->addWidget(loadRightButton);

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
