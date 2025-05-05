#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QPixmap>
#include <QScreen>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //커스텀 이미지 라벨 생성
    imageLabel = new ImageLabel(this);

    //스크롤 영역 설정
    container = new QWidget(this);
    QVBoxLayout *containerLayout = new QVBoxLayout(container);
    containerLayout->addStretch();  // 위 여백
    containerLayout->addWidget(imageLabel, 0, Qt::AlignCenter);  // 이미지 가운데 정렬
    containerLayout->addStretch();  // 아래 여백

    //ScrollArea에 container 삽입
    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(container);

    //전체 레이아웃에 scrollArea 추가
    ui->verticalLayout->insertWidget(0, scrollArea);  // 버튼보다 위에 붙이기

    //시그널-슬롯 연결
    connect(ui->loadButton, &QPushButton::clicked, this, &MainWindow::loadImage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadImage()
{
    QString fileName = QFileDialog::getOpenFileName(
        this, //부모 위젯 지정, 여기선 MainWindow 객체
        "이미지 선택", //대화 상자에 표시될 제목
        "", //파일을 열 때 기본으로 보여줄 경로(기본값)
        "Image Files (*.png *.jpg *.bmp)" //필터. 사용자가 선택할 수 있는 파일 형식을 제한
    );

    if (!fileName.isEmpty()) {
        QPixmap pixmap(fileName);  //원본 이미지 로드

        //창 크기 조절
        QSize screenSize = QGuiApplication::primaryScreen()->availableGeometry().size();
        screenSize.setHeight(screenSize.height() - 100);  // 작업표시줄 여유

        QSize imageSize = pixmap.size();  //원본 이미지 크기 기준
        int newWidth, newHeight;

        if (imageSize.width() <= screenSize.width() && imageSize.height() <= screenSize.height()) {
            newWidth = imageSize.width();
            newHeight = imageSize.height();
        } else {
            newWidth = screenSize.width();
            newHeight = screenSize.height();
        }

        this->resize(newWidth, newHeight);  //setImage() 전에 크기 조정

        //원본 이미지 넘김
        imageLabel->setImage(pixmap);
    }

    // if(!fileName.isEmpty()) Pr1 방식
    // {
    //     QPixmap pixmap(fileName); //pixmap: Qt에서 이미지를 표현하는 클래스

    //     QSize screenSize = QGuiApplication::primaryScreen()->availableGeometry().size(); //현재 화면의 크기
    //     screenSize.setHeight(screenSize.height()-100); //작업 표시줄을 뺀 화면 사이즈

    //     QSize imageSize = pixmap.size();
    //     if(imageSize.width() > screenSize.width() || imageSize.height() > screenSize.height()) //현재 이미지의 크기가 화면의 크기보다 크다면
    //     {
    //         imageSize.scale(screenSize, Qt::KeepAspectRatio); //이미지 사이즈 변수를 화면 사이즈에 원본의 비율을 유지한 크기로 리사이즈
    //         pixmap = pixmap.scaled(imageSize, Qt::KeepAspectRatio, Qt::SmoothTransformation); //실제 이미지를 이미지 사이즈 변수만큼 리사이즈
    //     }

    //     ui->label->setPixmap(pixmap);
    //     ui->label->resize(pixmap.size());
    //     this->adjustSize();  // 자동으로 창 크기와 버튼 위치까지 맞춰짐
    // }
}
