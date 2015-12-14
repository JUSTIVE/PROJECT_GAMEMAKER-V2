//******************************************
#define COL                   GetStdHandle(STD_OUTPUT_HANDLE)        // 콘솔창의 핸들정보 받기
#define BLACK                SetConsoleTextAttribute(COL, 0x0000);        // 검정색
#define DARK_BLUE         SetConsoleTextAttribute(COL, 0x0001);        // 파란색
#define GREEN                SetConsoleTextAttribute(COL, 0x0002);        // 녹색
#define BLUE_GREEN        SetConsoleTextAttribute(COL, 0x0003);        // 청녹색
#define BLOOD               SetConsoleTextAttribute(COL, 0x0004);        // 검붉은색
#define PURPLE               SetConsoleTextAttribute(COL, 0x0005);        // 보라색
#define GOLD                 SetConsoleTextAttribute(COL, 0x0006);        // 금색
#define ORIGINAL            SetConsoleTextAttribute(COL, 0x0007);        // 밝은 회색 (ORIGINAL CONSOLE COLOR)
#define GRAY                 SetConsoleTextAttribute(COL, 0x0008);        // 회색
#define BLUE                  SetConsoleTextAttribute(COL, 0x0009);        // 파란색
#define HIGH_GREEN       SetConsoleTextAttribute(COL, 0x000a);        // 연두색
#define SKY_BLUE           SetConsoleTextAttribute(COL, 0x000b);        // 하늘색
#define RED                   SetConsoleTextAttribute(COL, 0x000c);        // 빨간색
#define PLUM                SetConsoleTextAttribute(COL, 0x000d);        // 자주색
#define YELLOW             SetConsoleTextAttribute(COL, 0x000e);        // 노란색
#define WHITE                SetConsoleTextAttribute(COL, 0x000f);        // 흰색
//******************************************
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<conio.h>
void loading();
void start();
void slide_up_animation();
void slide_down_animation();
void tutorial();
void intro_animation();