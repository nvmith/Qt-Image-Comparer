# 📂 Qt 기반 이미지 비교 프로그램
C++과 Qt Creator를 기반으로 한 **이미지 비교 데스크탑 애플리케이션** 개발 프로젝트입니다.

---

## ✅ 목표

- Qt 기반 GUI 프로그래밍 실습
- 이미지 처리 및 사용자 인터랙션 구현
- 단계별 기능 개발로 실무 흐름 익히기

---

## 🔧 개발 환경

- 언어: C++ / Qt6 (QMake)
- IDE: Qt Creator

---

## 🧠 개발 의도 및 철학

사용자 중심의 데스크탑 앱 개발 과정을 체험하기 위해 본 프로젝트를 기획했습니다.  
기능 단위로 구분된 주차별 커리큘럼을 구성하고, **점진적으로 복잡한 구조를 다뤄보는 것**을 목적으로 합니다.

단순한 뷰어 기능을 넘어서, **사용자 입력, 비교 알고리즘, 시각화 표현**까지 포함된 구조로 완성도를 높였습니다.


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

- C++
- Qt6 / Qt Creator
- QWidget 기반 GUI 프로그래밍
- GitHub 브랜치별 기능 분리 개발

---

## 실행 화면

| 초기 실행 화면 | 이미지 로딩 후 |
|:--:|:--:|
| <img width="1280" alt="Image" src="https://github.com/user-attachments/assets/67cd6ba9-582e-43e7-8ea0-d479d425f99a" /> | <img width="1280" alt="Image" src="https://github.com/user-attachments/assets/283a62f4-fd10-49d8-ac88-1cb01f49dabc" /> |

| 색상 선택 다이얼로그 | 비교 결과 팝업 |
|:--:|:--:|
| <img width="1280" alt="Image" src="https://github.com/user-attachments/assets/ac116472-556f-43fa-a095-0b0f9008b0af" /> | <img width="602" alt="Image" src="https://github.com/user-attachments/assets/655a658d-277f-4c5f-b075-f38935c45ba5" /> |

---

> 사용자는 좌/우 이미지를 선택한 뒤  
> `"비교 시작"` 버튼을 클릭하여 두 이미지 간 차이를 시각적으로 확인할 수 있습니다.  
>  
> 비교 색상은 사용자가 직접 선택할 수 있으며,  
> 차이 결과는 팝업창으로 표시되며 차이 비율도 함께 출력합니다.

---

## 실행 방법

```bash
git clone https://github.com/nvmith/QTProject.git
cd QTProject
# Qt Creator로 열고 빌드 후 실행
