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

    this->resize(1700, 900); // 창 크기 기본 설정

    // 왼쪽/오른쪽 이미지 뷰 생성 (CustomGraphicsView 사용)
    leftView = new CustomGraphicsView(this);
    rightView = new CustomGraphicsView(this);

    // 보기 좋게 적당한 크기 확보
    leftView->setMinimumSize(800, 800);
    rightView->setMinimumSize(800, 800);

    // 스플리터로 좌우 나눔
    splitter = new QSplitter(Qt::Horizontal, this);
    splitter->addWidget(leftView);
    splitter->addWidget(rightView);
    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 1);

    // 스플리터를 감쌀 컨테이너
    container = new QWidget(this);
    QVBoxLayout* containerLayout = new QVBoxLayout(container);
    containerLayout->addWidget(splitter);

    // 왼쪽/오른쪽 버튼 생성
    loadLeftButton = new QPushButton("왼쪽 이미지 불러오기", this);
    loadRightButton = new QPushButton("오른쪽 이미지 불러오기", this);

    connect(loadLeftButton, &QPushButton::clicked, this, &MainWindow::loadLeftImage);
    connect(loadRightButton, &QPushButton::clicked, this, &MainWindow::loadRightImage);

    // 버튼들을 가로로 배치
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(loadLeftButton);
    buttonLayout->addStretch();
    buttonLayout->addWidget(loadRightButton);

    // 전체 메인 레이아웃
    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addWidget(container);
    mainLayout->addLayout(buttonLayout);

    // 이 레이아웃을 중앙 위젯으로 설정
    QWidget* centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    // 공간 분배 (SplitView 크게, 버튼 작게)
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
