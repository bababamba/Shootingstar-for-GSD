# Shootingstar-for-GSD
## 1. 프로젝트 설명
본 프로젝트는 2021년 상명대학교 게임학과에서 개발한 게임이다.

본 프로젝트는 Game Software Design 수업을 위해 개발한 게임이다.

C++ 만을 사용해서 슈팅게임을 완성하는 것이 본 프로젝트의 목적이다.

게임에 필요한 리소스는 프로그래머 한태종이 직접 그렸다.

## 2. 프로젝트 인원
프로그래머 최정훈, 조대훈, 한태종 

## 3. 업무 분담
조대훈 : 보스 개발 및 다수의 패턴 개발

최정훈 : 소형 적 2체 및 중형 적 1체 개발, 적 클래스 구조 설계

한태종 : 소형 적 2체 및 중형 적 1체 개발, 플레이어 및 그래픽 시스템 개발

## 4. 프로젝트 환경
Visual Studio

C++

SDL(Simple Direct Layer)

Github

## 5. 프로젝트 구조
```
    ├─3rdparty
    │  ├─SDL2-2.24.0
    │  │  ├─cmake
    │  │  ├─docs
    │  │  ├─include
    │  │  └─lib
    │  │      ├─x64
    │  │      └─x86
    │  └─SDL2_image-2.6.2
    │      ├─cmake
    │      ├─include
    │      └─lib
    │          ├─x64
    │          │  └─optional
    │          └─x86
    │              └─optional
    ├─sho
    │  ├─image
    │  ├─rapidjson
    │  │  ├─error
    │  │  ├─internal
    │  │  └─msinttypes
    │  └─x64
    │      └─Debug
    │          └─sho.tlog
    └─x64
        └─Debug
```
