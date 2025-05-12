# 📂 Qt 기반 이미지 비교 프로그램
C++17과 Qt Creator를 기반으로 한 **이미지 비교 프로그램** 개발 프로젝트입니다.  

---

## 프로젝트 개요

- **개발 기간**: 4주 (Pr1~Pr4 단계별 개발)
- **개발 환경**: C++17 / Qt Creator / QMake
- **핵심 기술**: Qt GUI 프로그래밍, 이미지 처리, 사용자 인터랙션

---

## 프로젝트 커리큘럼

### 🟩 Pr1 — 이미지 로더 UI 구축 (✅ 완료)

**목표**: Qt 기본 위젯을 사용하여 이미지를 불러오는 간단한 뷰어 개발

- `QPushButton`, `QLabel`, `QFileDialog` 활용
- `QVBoxLayout`을 통한 중앙 정렬
- 이미지 크기에 따라 창 자동 조정
- 해상도 초과 시 자동 축소 기능

---

### 🟨 Pr2 — 이미지 뷰어 기능 확장 (✅ 완료)

**목표**: 마우스 휠로 이미지 확대/축소, 스크롤 가능 뷰어 구성

- `ImageLabel` 커스텀 클래스 (QLabel 상속)
- `scaleFactor`를 통한 확대/축소 비율 관리
- `QScrollArea`를 사용해 스크롤 가능한 뷰어 구성
- 중앙 정렬 (`QVBoxLayout + AlignCenter`) 적용
- 초기 해상도 기반 자동 배율 설정

---

### 🟦 Pr3 — 다중 이미지 비교 UI 구성 (⏳ 예정)

**목표**: 두 장의 이미지를 나란히 띄워 비교할 수 있는 인터페이스 구성

- `QSplitter` 또는 `QTabWidget` 기반 분할 레이아웃
- 이미지 A/B 선택 및 크기 동기화

---

### 🟥 Pr4 — 이미지 비교 및 시각화 (🎯 최종 목표)

**목표**: 두 이미지 간의 차이점 계산 및 시각적으로 강조 표시

- `QImage::pixelColor()`를 통한 픽셀 비교
- 차이점 강조 및 결과 이미지 저장
- 다양한 옵션 제공 및 UI 개선

---

## 주요 기술 스택

- C++17
- Qt5 / Qt Creator
- QWidget 기반 GUI 프로그래밍
- GitHub 브랜치별 기능 개발 관리

---

## 실행 방법

```bash
git clone https://github.com/nvmith/QTProject.git
cd QTProject
# Qt Creator로 열고 빌드 후 실행
