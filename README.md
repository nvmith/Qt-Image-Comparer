# 📂 Qt 기반 이미지 비교 프로그램
C++17과 Qt Creator를 기반으로 한 **이미지 비교 데스크탑 애플리케이션** 개발 프로젝트입니다.

---

## 프로젝트 개요

- **개발 기간**: 4주 (Pr1~Pr4 단계별 개발)
- **개발 환경**: C++ / Qt Creator / QMake
- **핵심 기술**: Qt GUI 프로그래밍, 이미지 처리, 사용자 인터랙션

---

## 프로젝트 커리큘럼

### 🟩 Pr1 — 이미지 로더 UI 구축 (✅ 완료)

**목표**: Qt 기본 위젯을 사용하여 이미지를 불러오는 간단한 뷰어 개발

- `QPushButton`, `QLabel`, `QFileDialog` 활용
- `QVBoxLayout`으로 중앙 정렬
- 이미지 크기에 따라 창 자동 조정
- 해상도 초과 시 자동 축소 기능

---

### 🟨 Pr2 — 이미지 뷰어 기능 확장 (✅ 완료)

**목표**: 마우스 휠로 이미지 확대/축소 가능한 스크롤 뷰어 구성

- `ImageLabel` 커스텀 클래스 (QLabel 상속)
- `scaleFactor`를 통한 확대/축소 비율 관리
- `QScrollArea` 기반 스크롤 기능 구현
- 중앙 정렬 (`QVBoxLayout + AlignCenter`) 적용
- 초기 해상도 기준 자동 배율 설정

---

### 🟦 Pr3 — 다중 이미지 비교 UI 구성 (✅ 완료)

**목표**: 두 장의 이미지를 나란히 띄워 비교할 수 있는 UI 구성

- 기존 `ImageLabel + QScrollArea` 구조 제거
- `CustomGraphicsView` 기반 구조로 전면 개편
- `QSplitter` 기반 좌우 정사각형 배치 구성
- 이미지별 독립 확대/축소/스크롤 기능 제공
- 마우스 휠 기반 부드러운 확대/축소 지원
- 초기 배율 이하 축소 제한, 드래그 이동 가능
- 좌우 이미지 불러오기 버튼 하단 배치

---

### 🟥 Pr4 — 이미지 비교 및 시각화 (✅ 완료)

**목표**: 두 이미지의 픽셀 단위 차이를 계산하고 시각적으로 강조

- `QImage::pixelColor()`를 통한 픽셀 비교 구현
- 이미지 크기 다를 경우 큰 쪽 기준 패딩 자동 맞춤
- 사용자 지정 색상으로 차이 표시 (`QColorDialog`)
- 결과는 팝업창으로 표시되며, 차이 비율(%) 포함

---

## 주요 기술 스택

- C++17
- Qt6 / Qt Creator
- QWidget 기반 GUI 프로그래밍
- GitHub 브랜치별 기능 분리 개발

---

## 실행 방법

```bash
git clone https://github.com/nvmith/QTProject.git
cd QTProject
# Qt Creator로 열고 빌드 후 실행
