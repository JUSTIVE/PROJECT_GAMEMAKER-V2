//******************************************
#define COL                   GetStdHandle(STD_OUTPUT_HANDLE)        // �ܼ�â�� �ڵ����� �ޱ�
#define BLACK                SetConsoleTextAttribute(COL, 0x0000);        // ������
#define DARK_BLUE         SetConsoleTextAttribute(COL, 0x0001);        // �Ķ���
#define GREEN                SetConsoleTextAttribute(COL, 0x0002);        // ���
#define BLUE_GREEN        SetConsoleTextAttribute(COL, 0x0003);        // û���
#define BLOOD               SetConsoleTextAttribute(COL, 0x0004);        // �˺�����
#define PURPLE               SetConsoleTextAttribute(COL, 0x0005);        // �����
#define GOLD                 SetConsoleTextAttribute(COL, 0x0006);        // �ݻ�
#define ORIGINAL            SetConsoleTextAttribute(COL, 0x0007);        // ���� ȸ�� (ORIGINAL CONSOLE COLOR)
#define GRAY                 SetConsoleTextAttribute(COL, 0x0008);        // ȸ��
#define BLUE                  SetConsoleTextAttribute(COL, 0x0009);        // �Ķ���
#define HIGH_GREEN       SetConsoleTextAttribute(COL, 0x000a);        // ���λ�
#define SKY_BLUE           SetConsoleTextAttribute(COL, 0x000b);        // �ϴû�
#define RED                   SetConsoleTextAttribute(COL, 0x000c);        // ������
#define PLUM                SetConsoleTextAttribute(COL, 0x000d);        // ���ֻ�
#define YELLOW             SetConsoleTextAttribute(COL, 0x000e);        // �����
#define WHITE                SetConsoleTextAttribute(COL, 0x000f);        // ���
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