
#define _CRT_SECURE_NO_WARNINGS//<- scanf_s �Ⱦ��� ���� ��ó���⿡ ��
//+++++++++++++++++++++++++++++++++++++++++
//Ű��
#define BSP 0x8
#define ENTER 0xd
#define ESC 0x1b
#define UP 0x48
#define DOWN 0x50
#define LEFT 0x4b
#define RIGHT 0x4d
//*****************************************
//���
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<conio.h>
//��getch()�� ����ϱ� ����!
#if defined(_MSC_VER)
#ifndef _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_DEPRECATE (1)
#endif
#pragma warning(disable : 4996)
#endif
//******************************************
//�Լ�����
int game_dev_pj_selling(int game_point, char * pj_name);
void recruited(int called_num);
void loading();
void start();
int game_dev_pj_naming();
void game_dev_pj_cruit(char* pj_name, int pj_name_leng);
int game_dev_pj_running(char * pj_name, int * you_will_work, int cruit_chk_counted);
void cruit_upgrade_confirm(int what_num_you_choosed);
void game_end_phase();
void payday(int year,int month);
void leveling();
//******************************************
//��������
int stamina_regen_chk[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };//�ſ� ü����� üũ
int pay_chked[21] = { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };//�ų� ����üũ
int total_money=300;
int company_lv = 1; 
int paused_time=0;
int game_name_log_count = -1;//�Ʒ� ������ ��ġ�� �����ϴ� ����
char game_name_log[100][80] = { "\0" };//��� ������ �̸��� ����
int able_cruit_num = 1;//menu���� ��밡���ο� 
char blank[3] = ("\0");//ȭ��ǥ �̵��� ������ġ�� ä��
char company_name[80];//ȸ���̸� �Է¹޴°�
int ex_key;//�߰�Ű �νĿ�
unsigned char key = 0;//�߰�Ű ���� �� ���� �Է¿�
int money = 300;//ȸ���� �ں�
char upper[3] = ("��");//���� ���޴����� ��µǴ� ȭ��ǥ
char selector[3] = ("->");//���� ���ý� ��µǴ� ȭ��ǥ
char system_message[30] = { "                    " };//��� ������ �����ϴ� ���ڿ�
char system_message_init[30] = { "                    " };//�� ���� �ʱ�ȭ
int this_is_random_number_for_stats;//������ ������ +-a�� ������ ����
int worker_count = 1;//ȸ���� ������
int year;//� �Ⱓ
int month;
//******************************************
//��������
char err_not_choosed[40] = { "��� �Ѹ� �̻� �����Ͻʽÿ�" };
char err_not_enough_money[40] = { "�ܾ��� �����մϴ�" };
char err_not_enough_hire[40] = { "���̻� ����� �� �����ϴ�" };
char err_not_enough_stamina[40] = { "ü���� �����մϴ�." };
char err_selected_again[40] = { "�ߺ��� �����Դϴ�" };
//******************************************
//�ý��� �޼���
char alert_tooltip_arrow_and_enter[40] = { "������ ����Ű�� ����" };
char alert_payment_served[40] = { "�����鿡�� �޿��� ���޵Ǿ����ϴ�" };
char alert_company_lv_up[40] = { "ȸ���� ������ ����Ͽ����ϴ�!" };
//******************************************
//����db
/*		int enabler[13];
char worker_name[13][9];
//status
int programming[13];
int graphic[13];
int sound[13];

int stamina[13];
int upgrading_cost[13];
char upgrade_message[13][17];
//status_upgrade_delta
int programming_upgrade_delta[13];
int graphic_upgrade_delta[13];
int sound_upgrade_delta[13];

int stamina_minus_delta[13];
int stamina_regen_delta_per_min_const[13];
//status_upgrade_count
//���׷��̵� ����� status+=(upgrade_delta+randomwidth)
int upgrade_count[13];
*/
//******************************************

int worker_num[13] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
int enabler[13] = { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
char worker_name[13][9] = { { " ���� " }, { " ������ " }, { "��ī�ݶ�" }, { "�ﰢ���" }, { " �ƿǿ� " }, { "������A " }, { " ������ " }, { " �Ｚ�� " }, { "�׸�����" }, { "�Ŀ��ڴ�" }, { " ȫ��ȣ " }, { "�����콺" } };
//status
int programming[13] = { 35, 10, 45, 60, 8, 76, 1, 90, 1, 150, 2, 50 };
int graphic[13] = { 20, 60, 1, 25, 8, 82, 1, 80, 100, 1, 2, 50 };
int sound[13] = { 40, 100, 80, 30, 8, 46, 1, 70, 25, 1, 2, 50 };

int stamina[13] = { 100, 100, 100, 100, 5, 100, 100, 100, 100, 100, 100, 100 };
int upgrading_cost[13] = { 50, 50, 100, 150, 100, 200, 10, 500, 100, 100, 2, 250 };
int recruit_cost[13] = { 100, 300, 500, 700, 900, 1600, 1500, 1000, 150, 100, 2, 500 };
int payment[13] = { 100, 150, 500, 350, 450, 400, 1000, 1500, 150, 100, 2, 500 };
char upgrade_message[13][21] = { { "   ��������?  " }, { "�������ƿ亣���缼��" }, { "��ô� ���ô°� �Ƴ�" }, { "���������� �ܵ�700��" }, { "�ƿǿǿǿǿǿǿǿǿ�" }, { "���õ� ���ϵ� �߱�.." }, { "  ������ ��������?  " }, { "���з����з����з�? " }, { " �׸��Ƿ��� �ö���! " }, { " ���õ� ����� �ڵ�!" }, { "      ��������      " }, { "���ۺ��ۺ��ۺ��ۺ���" } };
//status_upgrade_delta
int programming_upgrade_delta[13] = { 3, 1, 3, 0, 4, 1, 4, 8, 1, 10, 2, 15 };
int graphic_upgrade_delta[13] = { 3, 4, 3, 0, 4, 1, 5, 8, 10, 1, 2, 15 };
int sound_upgrade_delta[13] = { 3, 5, 3, 0, 7, 1, 3, 8, 5, 1, 2, 15 };

int stamina_minus_delta[13] = { 15, 10, 18, 8, 15, 40, 10, 30, 19, 25, 2, 50 };
int stamina_regen_delta_per_min_const[13] = { 5, 3, 7, 6, 9, 8, 10, 15, 9, 9, 2, 15 };//�̰� ����ü ����???������??
double payment_delta_per_upgrade[13] = { 1.05, 1.05, 1.01,  1.1,  1.15,  1.15, 1.01,1.3,1.3,1};//���� �λ��� %�� �մϴ�.�������������������������������� ������ ¥��������..*�� ȫ��ȣ�� ������ �׻� 2�Դϴ�
//status_upgrade_count
//���׷��̵� ����� status+=(upgrade_delta+randomwidth)
int upgrade_count[13] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };//ī��Ʈ�� �ʿ���� ������? 
int company_level_requirement[12] = { 1000, 5000, 10000, 20000, 40000, 80000, 160000,320000,640000,1280000,2560000,5120000 };
//******************************************
//******************************************
//******************************************
//******************************************
//�ʸ��� ����Ʈ
int your_taked_worker_num[13] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };//taken[13]�� ���������� �� ��� pj_cruit���� if(key==0xd) ����case:DOWN ���� �߻��ϴ� ������ ó���ϱ� ���� taken�� �Ȱ��� �迭�� ����Ѵ�. �� your_taked_worker_num[13]�� ����� printf�� ������ ���δ�
int your_taked_worker_num_count = 0;
char list_of_cruit[13][9] = { "        ", "        ", "        ", "        ", "        ", "        ", "        ", "        ", "        ", "        ", "        ", "        " };//�ʸ��� ��������Ʈ.�̰� �� �� �־�����???�� worker_name[taken[recruited_num]]���� ó���� �� ���� �ʾ�����?
int your_stamina[13] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };//�ڽ��� ���� �������� ���¹̳�.�̰� �� �� �־�����???�� stamina[taken[recruited_num]]���� ó���� �� ���� �ʾ�����?
int your_upgrade_cost[13] = { 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00 };
//******************************************
void your_db_refresher()
{
	//�����ͺ��̽� ����ȭ.
	//�� �κ��� �ٷ� �� �׸��� '�ʸ��� ����Ʈ'�� db�� ����ȭ��Ű�� ���� ��������� ���Ŀ� ���������� �����ع������ν� ���ǹ��� �Լ��� �Ǿ���.
}
//******************************************
int digiter(int a)//������ �ڸ����� ����ϴ� �Լ�. �ַ� \b �� ��¿� ����
{
	int i;
	int digit = 1;

	if (a == 0)
	{
		return 1;
	}
	else if (a > 0)
	{
		for (i = 1; i < 1000000000; i = i * 10)
		{
			if ((i <= a) && (a < i * 10))
			{

				break;
			}
			digit++;
		}
		return digit;
	}
	else
	{
		a = 0 - a;
		for (i = 1; i < 1000000000; i = i * 10)
		{
			if ((i <= a) && (a < i * 10))
			{

				break;
			}
			digit++;
		}
		return digit+1;
	}
}
void alignment(int a)//digiter�� �̿����� ����\b����Լ�
{
	int i;
	for (i = 0; i < a; i++)
	{
		printf("\b");
	}
}
int arr_counter(int* input, int limits_end, int limits_down)//������ ����(int * input)�迭�� ��(limits_end) ���� ���� ��(limits_down) �̻��� ���� ���� �Լ�.
{
	int i, counter = 0;
	for (i = 0; i < limits_end; i++)
	{
		if (input[i]>limits_down)
		{
			counter++;
		}
	}
	return counter;
}

int status_upgrade_random_width()
{
	int re;
	srand(time(NULL));
	re = rand() % 10;
	re -= 4;
	return re;
}

void slide_up_animation()//ȭ���� ���� �ö󰡴� ���� �ִϸ��̼�. ���⼭ ��� ���� sleep()�� system("cls")�� ȭ���� �����ϴµ��� �ּҵ����̰� �����Ѵ� ���̴�. 
{
	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��			                                                              ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(10);
	system("cls");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��			                                                              ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(10);
	system("cls");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��			                                                              ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(10);
	system("cls");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��			                                                              ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(10);
	system("cls");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��			                                                              ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(10);
	system("cls");
	printf("��                                                                        ��\n");
	printf("��			                                                              ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(10);
	system("cls");
	printf("��			                                                              ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(10);
	system("cls");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(10);
	system("cls");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(10);
	system("cls");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(10);
	system("cls");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(10);
	system("cls");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(10);
	system("cls");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(10);
	system("cls");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(10);
	system("cls");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(10);
	system("cls");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(10);
	system("cls");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(10);
	system("cls");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(10);
	system("cls");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(10);
	system("cls");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(10);
	system("cls");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(10);
	system("cls");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(10);
	system("cls");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(10);
	system("cls");
	printf("���������������������������������������\n");
	Sleep(10);

}
void slide_down_animation()
{
	system("cls");
	printf("���������������������������������������\n");
	Sleep(10);
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(10);
	system("cls");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(10);
	system("cls");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(10);
	system("cls");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(10);
	system("cls");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(10);
	system("cls");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(10);
	system("cls");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(10);
	system("cls");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(10);
	system("cls");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(10);
	system("cls");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(10);
	system("cls");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(10);
	system("cls");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(10);
	system("cls");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(10);
	system("cls");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(10);
	system("cls");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(10);
	system("cls");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(10);
	system("cls");
	printf("��			                                                              ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(10);
	//17
	//22
	system("cls");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��			                                                              ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(10);
	system("cls");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��			                                                              ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(10);
}

void loading()//ȭ�鿡�� ���ڰ� ���ۺ��� ���鼭 �ε��� �Ǵ� ���� �ִϸ��̼�.
{
	char a = '@', b = 'o', c = '.', d = '\0', e = '\0', f = '\0', g = '\0', h = '\0', temp;
	int end = 0, i;
	slide_up_animation();


	for (end = 0; end<50; end++)
	{
		printf("                                %c%c                                    \n", a, a);
		printf("                         %c%c %c%c%c%c%c%c %c%c                         \n", a, a, a, a, a, a, a, a, a, a);
		printf("                    %c%c  %c%c            %c%c  %c%c                    \n", h, h, a, a, a, a, b, b);
		printf("                 %c%c  %c                      %c  %c%c                 \n", h, h, h, b, b, b);
		printf("               %c%c%c                              %c%c%c               \n", h, h, h, b, b, b);
		printf("             %c%c                                      %c%c             \n", h, h, b, b);
		printf("           %c%c                                          %c%c           \n", h, h, b, b);
		printf("         %c%c                                              %c%c         \n", g, g, c, c);
		printf("        %c%c                                                %c%c        \n", g, g, c, c);
		printf("        %c%c                                                %c%c        \n", g, g, c, c);
		printf("       %c%c                   L O A D I N G                  %c%c       \n", g, g, c, c);
		printf("       %c%c                                                  %c%c       \n", g, g, c, c);
		printf("        %c%c                                                %c%c        \n", g, g, c, c);
		printf("        %c%c                                                %c%c        \n", g, g, c, c);
		printf("         %c%c                                              %c%c         \n", g, g, c, c);
		printf("           %c%c                                          %c%c           \n", f, f, d, d);
		printf("             %c%c                                      %c%c             \n", f, f, d, d);
		printf("               %c%c%c                              %c%c%c               \n", f, f, f, d, d, d);
		printf("                 %c%c  %c                      %c  %c%c                 \n", f, f, f, d, d, d);
		printf("                    %c%c  %c%c            %c%c  %c%c                    \n", f, f, e, e, e, e, d, d);
		printf("                         %c%c %c%c%c%c%c%c %c%c                         \n", e, e, e, e, e, e, e, e, e, e);
		printf("                                %c%c                                    \n", e, e);
		Sleep(30);	system("cls");
		temp = h; h = a; a = b; b = c; c = d; d = e; e = f; f = g; g = temp; end++;
	}
	slide_down_animation();
	fflush(stdin);
}
void start()//��Ʈ��. ���ڰ� �ϳ��� �������� ���� �ִϸ��̼�
{
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                                                         ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                                                         ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                                                         ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |  __                                                         ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                                                         ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |  __                                                         ��\n");
	printf("��        | | |_ |                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                                                         ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |  __                                                         ��\n");
	printf("��        | | |_ |                                                        ��\n");
	printf("��        | |__| |                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                                                         ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |  __                                                         ��\n");
	printf("��        | | |_ |                                                        ��\n");
	printf("��        | |__| |                                                        ��\n");
	printf("��         #_____|                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                                                         ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |  __                                                         ��\n");
	printf("��        | | |_ |/                                                       ��\n");
	printf("��        | |__| |                                                        ��\n");
	printf("��         #_____|#                                                       ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                                                         ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |  __  _                                                      ��\n");
	printf("��        | | |_ |/                                                       ��\n");
	printf("��        | |__| | (                                                      ��\n");
	printf("��         #_____|#_                                                      ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                                                         ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |  __  __                                                     ��\n");
	printf("��        | | |_ |/ _                                                     ��\n");
	printf("��        | |__| | (_                                                     ��\n");
	printf("��         #_____|#__                                                     ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                                                         ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |  __  __                                                     ��\n");
	printf("��        | | |_ |/ _`                                                    ��\n");
	printf("��        | |__| | (_|                                                    ��\n");
	printf("��         #_____|#__,                                                    ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                                                         ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |  __  __ _                                                   ��\n");
	printf("��        | | |_ |/ _`                                                    ��\n");
	printf("��        | |__| | (_|                                                    ��\n");
	printf("��         #_____|#__,_                                                   ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                                                         ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |  __  __ _                                                   ��\n");
	printf("��        | | |_ |/ _` |                                                  ��\n");
	printf("��        | |__| | (_| |                                                  ��\n");
	printf("��         #_____|#__,_|                                                  ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                                                         ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |  __  __ _                                                   ��\n");
	printf("��        | | |_ |/ _` |                                                  ��\n");
	printf("��        | |__| | (_| |                                                  ��\n");
	printf("��         #_____|#__,_|_| |_| |_|                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                                                         ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |  __  __ _                                                   ��\n");
	printf("��        | | |_ |/ _` |                                                  ��\n");
	printf("��        | |__| | (_| | | | | | |                                        ��\n");
	printf("��         #_____|#__,_|_| |_| |_|                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                                                         ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |  __  __ _                                                   ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ #                                         ��\n");
	printf("��        | |__| | (_| | | | | | |                                        ��\n");
	printf("��         #_____|#__,_|_| |_| |_|                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                                                         ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |  __  __ _ _ __ ___                                          ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ #                                         ��\n");
	printf("��        | |__| | (_| | | | | | |                                        ��\n");
	printf("��         #_____|#__,_|_| |_| |_|                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                 ____                                    ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |  __  __ _ _ __ ___                                          ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ #                                         ��\n");
	printf("��        | |__| | (_| | | | | | |                                        ��\n");
	printf("��         #_____|#__,_|_| |_| |_|                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                 ____                                    ��\n");
	printf("��         / ____|               |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___                                          ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ #                                         ��\n");
	printf("��        | |__| | (_| | | | | | |                                        ��\n");
	printf("��         #_____|#__,_|_| |_| |_|                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                 ____                                    ��\n");
	printf("��         / ____|               |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ #                                         ��\n");
	printf("��        | |__| | (_| | | | | | |                                        ��\n");
	printf("��         #_____|#__,_|_| |_| |_|                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                 ____                                    ��\n");
	printf("��         / ____|               |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ # |__ <                                   ��\n");
	printf("��        | |__| | (_| | | | | | |                                        ��\n");
	printf("��         #_____|#__,_|_| |_| |_|                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                 ____                                    ��\n");
	printf("��         / ____|               |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ # |__ <                                   ��\n");
	printf("��        | |__| | (_| | | | | | |___) |                                  ��\n");
	printf("��         #_____|#__,_|_| |_| |_|                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                 ____                                    ��\n");
	printf("��         / ____|               |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ # |__ <                                   ��\n");
	printf("��        | |__| | (_| | | | | | |___) |                                  ��\n");
	printf("��         #_____|#__,_|_| |_| |_|____/                                   ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                 ____                                    ��\n");
	printf("��         / ____|               |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ # |__ <                                   ��\n");
	printf("��        | |__| | (_| | | | | | |___) |                                  ��\n");
	printf("��         #_____|#__,_|_| |_| |_|____/                                   ��\n");
	printf("��                                                                        ��\n");
	printf("��        |                                                               ��\n");
	printf("��        |                                                               ��\n");
	printf("��        |                                                               ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                 ____                                    ��\n");
	printf("��         / ____|               |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ # |__ <                                   ��\n");
	printf("��        | |__| | (_| | | | | | |___) |                                  ��\n");
	printf("��         #_____|#__,_|_| |_| |_|____/                                   ��\n");
	printf("��         /                                                              ��\n");
	printf("��        |                                                               ��\n");
	printf("��        |                                                               ��\n");
	printf("��        |                                                               ��\n");
	printf("��         #                                                              ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                 ____                                    ��\n");
	printf("��         / ____|               |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ # |__ <                                   ��\n");
	printf("��        | |__| | (_| | | | | | |___) |                                  ��\n");
	printf("��         #_____|#__,_|_| |_| |_|____/                                   ��\n");
	printf("��         /                                                              ��\n");
	printf("��        | |                                                             ��\n");
	printf("��        | |                                                             ��\n");
	printf("��        | |                                                             ��\n");
	printf("��         #_                                                             ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                 ____                                    ��\n");
	printf("��         / ____|               |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ # |__ <                                   ��\n");
	printf("��        | |__| | (_| | | | | | |___) |                                  ��\n");
	printf("��         #_____|#__,_|_| |_| |_|____/                                   ��\n");
	printf("��         / _                                                            ��\n");
	printf("��        | |                                                             ��\n");
	printf("��        | |                                                             ��\n");
	printf("��        | |_                                                            ��\n");
	printf("��         #__                                                            ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                 ____                                    ��\n");
	printf("��         / ____|               |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ # |__ <                                   ��\n");
	printf("��        | |__| | (_| | | | | | |___) |                                  ��\n");
	printf("��         #_____|#__,_|_| |_| |_|____/                                   ��\n");
	printf("��         / __                                                           ��\n");
	printf("��        | |                                                             ��\n");
	printf("��        | |                                                             ��\n");
	printf("��        | |__                                                           ��\n");
	printf("��         #___                                                           ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                 ____                                    ��\n");
	printf("��         / ____|               |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ # |__ <                                   ��\n");
	printf("��        | |__| | (_| | | | | | |___) |                                  ��\n");
	printf("��         #_____|#__,_|_| |_| |_|____/                                   ��\n");
	printf("��         / ___                                                          ��\n");
	printf("��        | |                                                             ��\n");
	printf("��        | |                                                             ��\n");
	printf("��        | |___                                                          ��\n");
	printf("��         #____                                                          ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                 ____                                    ��\n");
	printf("��         / ____|               |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ # |__ <                                   ��\n");
	printf("��        | |__| | (_| | | | | | |___) |                                  ��\n");
	printf("��         #_____|#__,_|_| |_| |_|____/                                   ��\n");
	printf("��         / ____                                                         ��\n");
	printf("��        | |                                                             ��\n");
	printf("��        | |                                                             ��\n");
	printf("��        | |____                                                         ��\n");
	printf("��         #_____                                                         ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                 ____                                    ��\n");
	printf("��         / ____|               |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ # |__ <                                   ��\n");
	printf("��        | |__| | (_| | | | | | |___) |                                  ��\n");
	printf("��         #_____|#__,_|_| |_| |_|____/                                   ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |                                                             ��\n");
	printf("��        | |                                                             ��\n");
	printf("��        | |____                                                         ��\n");
	printf("��         #_____|                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                 ____                                    ��\n");
	printf("��         / ____|               |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ # |__ <                                   ��\n");
	printf("��        | |__| | (_| | | | | | |___) |                                  ��\n");
	printf("��         #_____|#__,_|_| |_| |_|____/                                   ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |                                                             ��\n");
	printf("��        | |         |                                                   ��\n");
	printf("��        | |____     |                                                   ��\n");
	printf("��         #_____|    |                                                   ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                 ____                                    ��\n");
	printf("��         / ____|               |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ # |__ <                                   ��\n");
	printf("��        | |__| | (_| | | | | | |___) |                                  ��\n");
	printf("��         #_____|#__,_|_| |_| |_|____/                                   ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |          _                                                  ��\n");
	printf("��        | |         |                                                   ��\n");
	printf("��        | |____     |                                                   ��\n");
	printf("��         #_____|    |_                                                  ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                 ____                                    ��\n");
	printf("��         / ____|               |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ # |__ <                                   ��\n");
	printf("��        | |__| | (_| | | | | | |___) |                                  ��\n");
	printf("��         #_____|#__,_|_| |_| |_|____/                                   ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |          _                                                  ��\n");
	printf("��        | |         | '                                                 ��\n");
	printf("��        | |____     | |                                                 ��\n");
	printf("��         #_____|    |_|                                                 ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                 ____                                    ��\n");
	printf("��         / ____|               |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ # |__ <                                   ��\n");
	printf("��        | |__| | (_| | | | | | |___) |                                  ��\n");
	printf("��         #_____|#__,_|_| |_| |_|____/                                   ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |          _ _                                                ��\n");
	printf("��        | |         | '_                                                ��\n");
	printf("��        | |____     | |                                                 ��\n");
	printf("��         #_____|    |_|                                                 ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                 ____                                    ��\n");
	printf("��         / ____|               |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ # |__ <                                   ��\n");
	printf("��        | |__| | (_| | | | | | |___) |                                  ��\n");
	printf("��         #_____|#__,_|_| |_| |_|____/                                   ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |          _ __                                               ��\n");
	printf("��        | |         | '_                                                ��\n");
	printf("��        | |____     | | |                                               ��\n");
	printf("��         #_____|    |_| |                                               ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                 ____                                    ��\n");
	printf("��         / ____|               |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ # |__ <                                   ��\n");
	printf("��        | |__| | (_| | | | | | |___) |                                  ��\n");
	printf("��         #_____|#__,_|_| |_| |_|____/                                   ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |          _ __                                               ��\n");
	printf("��        | |         | '_ `                                              ��\n");
	printf("��        | |____     | | |                                               ��\n");
	printf("��         #_____|    |_| |_                                              ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                 ____                                    ��\n");
	printf("��         / ____|               |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ # |__ <                                   ��\n");
	printf("��        | |__| | (_| | | | | | |___) |                                  ��\n");
	printf("��         #_____|#__,_|_| |_| |_|____/                                   ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |          _ __ _                                             ��\n");
	printf("��        | |         | '_ `                                              ��\n");
	printf("��        | |____     | | | |                                             ��\n");
	printf("��         #_____|    |_| |_|                                             ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                 ____                                    ��\n");
	printf("��         / ____|               |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ # |__ <                                   ��\n");
	printf("��        | |__| | (_| | | | | | |___) |                                  ��\n");
	printf("��         #_____|#__,_|_| |_| |_|____/                                   ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |          _ __ __                                            ��\n");
	printf("��        | |         | '_ ` _                                            ��\n");
	printf("��        | |____     | | | |                                             ��\n");
	printf("��         #_____|    |_| |_|                                             ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                 ____                                    ��\n");
	printf("��         / ____|               |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ # |__ <                                   ��\n");
	printf("��        | |__| | (_| | | | | | |___) |                                  ��\n");
	printf("��         #_____|#__,_|_| |_| |_|____/                                   ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |          _ __ ___                                           ��\n");
	printf("��        | |         | '_ ` _                                            ��\n");
	printf("��        | |____     | | | | |                                           ��\n");
	printf("��         #_____|    |_| |_| |                                           ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                 ____                                    ��\n");
	printf("��         / ____|               |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ # |__ <                                   ��\n");
	printf("��        | |__| | (_| | | | | | |___) |                                  ��\n");
	printf("��         #_____|#__,_|_| |_| |_|____/                                   ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |          _ __ ___                                           ��\n");
	printf("��        | |         | '_ ` _ #                                          ��\n");
	printf("��        | |____     | | | | | |                                         ��\n");
	printf("��         #_____|    |_| |_| |_|                                         ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                 ____                                    ��\n");
	printf("��         / ____|               |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ # |__ <                                   ��\n");
	printf("��        | |__| | (_| | | | | | |___) |                                  ��\n");
	printf("��         #_____|#__,_|_| |_| |_|____/                                   ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |          _ __ ___  _ __                                     ��\n");
	printf("��        | |         | '_ ` _ #|                                         ��\n");
	printf("��        | |____     | | | | | |                                         ��\n");
	printf("��         #_____|    |_| |_| |_|                                         ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                 ____                                    ��\n");
	printf("��         / ____|               |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ # |__ <                                   ��\n");
	printf("��        | |__| | (_| | | | | | |___) |                                  ��\n");
	printf("��         #_____|#__,_|_| |_| |_|____/                                   ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |          _ __ ___  _ __                                     ��\n");
	printf("��        | |         | '_ ` _ #| '_ #                                    ��\n");
	printf("��        | |____     | | | | | |                                         ��\n");
	printf("��         #_____|    |_| |_| |_|                                         ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                 ____                                    ��\n");
	printf("��         / ____|               |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ # |__ <                                   ��\n");
	printf("��        | |__| | (_| | | | | | |___) |                                  ��\n");
	printf("��         #_____|#__,_|_| |_| |_|____/                                   ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |          _ __ ___  _ __                                     ��\n");
	printf("��        | |         | '_ ` _ #| '_ #                                    ��\n");
	printf("��        | |____     | | | | | | |_) |                                   ��\n");
	printf("��         #_____|    |_| |_| |_|                                         ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                 ____                                    ��\n");
	printf("��         / ____|               |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ # |__ <                                   ��\n");
	printf("��        | |__| | (_| | | | | | |___) |                                  ��\n");
	printf("��         #_____|#__,_|_| |_| |_|____/                                   ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |          _ __ ___  _ __                                     ��\n");
	printf("��        | |         | '_ ` _ #| '_ #                                    ��\n");
	printf("��        | |____     | | | | | | |_) |                                   ��\n");
	printf("��         #_____|    |_| |_| |_| .__/                                    ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                 ____                                    ��\n");
	printf("��         / ____|               |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ # |__ <                                   ��\n");
	printf("��        | |__| | (_| | | | | | |___) |                                  ��\n");
	printf("��         #_____|#__,_|_| |_| |_|____/                                   ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |          _ __ ___  _ __                                     ��\n");
	printf("��        | |         | '_ ` _ #| '_ #                                    ��\n");
	printf("��        | |____     | | | | | | |_) |                                   ��\n");
	printf("��         #_____|    |_| |_| |_| .__/                                    ��\n");
	printf("��                              | |                                       ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                 ____                                    ��\n");
	printf("��         / ____|               |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ # |__ <                                   ��\n");
	printf("��        | |__| | (_| | | | | | |___) |                                  ��\n");
	printf("��         #_____|#__,_|_| |_| |_|____/                                   ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |          _ __ ___  _ __                                     ��\n");
	printf("��        | |         | '_ ` _ #| '_ #                                    ��\n");
	printf("��        | |____     | | | | | | |_) |                                   ��\n");
	printf("��         #_____|    |_| |_| |_| .__/                                    ��\n");
	printf("��                              | |                                       ��\n");
	printf("��                              |_|                                       ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                 ____                                    ��\n");
	printf("��         / ____|               |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ # |__ <                                   ��\n");
	printf("��        | |__| | (_| | | | | | |___) |                                  ��\n");
	printf("��         #_____|#__,_|_| |_| |_|____/                                   ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |          _ __ ___  _ __   _                                 ��\n");
	printf("��        | |         | '_ ` _ #| '_ # /                                  ��\n");
	printf("��        | |____     | | | | | | |_) |                                   ��\n");
	printf("��         #_____|    |_| |_| |_| .__/                                    ��\n");
	printf("��                              | |                                       ��\n");
	printf("��                              |_|                                       ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                 ____                                    ��\n");
	printf("��         / ____|               |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ # |__ <                                   ��\n");
	printf("��        | |__| | (_| | | | | | |___) |                                  ��\n");
	printf("��         #_____|#__,_|_| |_| |_|____/                                   ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |          _ __ ___  _ __   __                                ��\n");
	printf("��        | |         | '_ ` _ #| '_ # /                                  ��\n");
	printf("��        | |____     | | | | | | |_) |                                   ��\n");
	printf("��         #_____|    |_| |_| |_| .__/                                    ��\n");
	printf("��                              | |                                       ��\n");
	printf("��                              |_|                                       ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                 ____                                    ��\n");
	printf("��         / ____|               |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ # |__ <                                   ��\n");
	printf("��        | |__| | (_| | | | | | |___) |                                  ��\n");
	printf("��         #_____|#__,_|_| |_| |_|____/                                   ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |          _ __ ___  _ __   __                                ��\n");
	printf("��        | |         | '_ ` _ #| '_ # / _                                ��\n");
	printf("��        | |____     | | | | | | |_) | (                                 ��\n");
	printf("��         #_____|    |_| |_| |_| .__/ #                                  ��\n");
	printf("��                              | |                                       ��\n");
	printf("��                              |_|                                       ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                 ____                                    ��\n");
	printf("��         / ____|               |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ # |__ <                                   ��\n");
	printf("��        | |__| | (_| | | | | | |___) |                                  ��\n");
	printf("��         #_____|#__,_|_| |_| |_|____/                                   ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |          _ __ ___  _ __   __ _                              ��\n");
	printf("��        | |         | '_ ` _ #| '_ # / _`                               ��\n");
	printf("��        | |____     | | | | | | |_) | (_                                ��\n");
	printf("��         #_____|    |_| |_| |_| .__/ #_                                 ��\n");
	printf("��                              | |                                       ��\n");
	printf("��                              |_|                                       ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                 ____                                    ��\n");
	printf("��         / ____|               |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ # |__ <                                   ��\n");
	printf("��        | |__| | (_| | | | | | |___) |                                  ��\n");
	printf("��         #_____|#__,_|_| |_| |_|____/                                   ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |          _ __ ___  _ __   __ _                              ��\n");
	printf("��        | |         | '_ ` _ #| '_ # / _` |                             ��\n");
	printf("��        | |____     | | | | | | |_) | (_|                               ��\n");
	printf("��         #_____|    |_| |_| |_| .__/ #__                                ��\n");
	printf("��                              | |                                       ��\n");
	printf("��                              |_|                                       ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                 ____                                    ��\n");
	printf("��         / ____|               |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ # |__ <                                   ��\n");
	printf("��        | |__| | (_| | | | | | |___) |                                  ��\n");
	printf("��         #_____|#__,_|_| |_| |_|____/                                   ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |          _ __ ___  _ __   __ _                              ��\n");
	printf("��        | |         | '_ ` _ #| '_ # / _` |                             ��\n");
	printf("��        | |____     | | | | | | |_) | (_| |                             ��\n");
	printf("��         #_____|    |_| |_| |_| .__/ #__,                               ��\n");
	printf("��                              | |                                       ��\n");
	printf("��                              |_|                                       ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                 ____                                    ��\n");
	printf("��         / ____|               |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ # |__ <                                   ��\n");
	printf("��        | |__| | (_| | | | | | |___) |                                  ��\n");
	printf("��         #_____|#__,_|_| |_| |_|____/                                   ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |          _ __ ___  _ __   __ _                              ��\n");
	printf("��        | |         | '_ ` _ #| '_ # / _` |                             ��\n");
	printf("��        | |____     | | | | | | |_) | (_| |                             ��\n");
	printf("��         #_____|    |_| |_| |_| .__/ #__,_|                             ��\n");
	printf("��                              | |                                       ��\n");
	printf("��                              |_|                                       ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                 ____                                    ��\n");
	printf("��         / ____|               |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ # |__ <                                   ��\n");
	printf("��        | |__| | (_| | | | | | |___) |                                  ��\n");
	printf("��         #_____|#__,_|_| |_| |_|____/                                   ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |          _ __ ___  _ __   __ _ _                            ��\n");
	printf("��        | |         | '_ ` _ #| '_ # / _` |                             ��\n");
	printf("��        | |____     | | | | | | |_) | (_| |                             ��\n");
	printf("��         #_____|    |_| |_| |_| .__/ #__,_|_                            ��\n");
	printf("��                              | |                                       ��\n");
	printf("��                              |_|                                       ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                 ____                                    ��\n");
	printf("��         / ____|               |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ # |__ <                                   ��\n");
	printf("��        | |__| | (_| | | | | | |___) |                                  ��\n");
	printf("��         #_____|#__,_|_| |_| |_|____/                                   ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |          _ __ ___  _ __   __ _ _                            ��\n");
	printf("��        | |         | '_ ` _ #| '_ # / _` | '                           ��\n");
	printf("��        | |____     | | | | | | |_) | (_| | |                           ��\n");
	printf("��         #_____|    |_| |_| |_| .__/ #__,_|_|                           ��\n");
	printf("��                              | |                                       ��\n");
	printf("��                              |_|                                       ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                 ____                                    ��\n");
	printf("��         / ____|               |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ # |__ <                                   ��\n");
	printf("��        | |__| | (_| | | | | | |___) |                                  ��\n");
	printf("��         #_____|#__,_|_| |_| |_|____/                                   ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |          _ __ ___  _ __   __ _ _ _                          ��\n");
	printf("��        | |         | '_ ` _ #| '_ # / _` | '_                          ��\n");
	printf("��        | |____     | | | | | | |_) | (_| | |                           ��\n");
	printf("��         #_____|    |_| |_| |_| .__/ #__,_|_|                           ��\n");
	printf("��                              | |                                       ��\n");
	printf("��                              |_|                                       ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                 ____                                    ��\n");
	printf("��         / ____|               |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ # |__ <                                   ��\n");
	printf("��        | |__| | (_| | | | | | |___) |                                  ��\n");
	printf("��         #_____|#__,_|_| |_| |_|____/                                   ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |          _ __ ___  _ __   __ _ _ __                         ��\n");
	printf("��        | |         | '_ ` _ #| '_ # / _` | '_                          ��\n");
	printf("��        | |____     | | | | | | |_) | (_| | | |                         ��\n");
	printf("��         #_____|    |_| |_| |_| .__/ #__,_|_| |                         ��\n");
	printf("��                              | |                                       ��\n");
	printf("��                              |_|                                       ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                 ____                                    ��\n");
	printf("��         / ____|               |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ # |__ <                                   ��\n");
	printf("��        | |__| | (_| | | | | | |___) |                                  ��\n");
	printf("��         #_____|#__,_|_| |_| |_|____/                                   ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |          _ __ ___  _ __   __ _ _ __                         ��\n");
	printf("��        | |         | '_ ` _ #| '_ # / _` | '_ #                        ��\n");
	printf("��        | |____     | | | | | | |_) | (_| | | |                         ��\n");
	printf("��         #_____|    |_| |_| |_| .__/ #__,_|_| |_                        ��\n");
	printf("��                              | |                                       ��\n");
	printf("��                              |_|                                       ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                 ____                                    ��\n");
	printf("��         / ____|               |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ # |__ <                                   ��\n");
	printf("��        | |__| | (_| | | | | | |___) |                                  ��\n");
	printf("��         #_____|#__,_|_| |_| |_|____/                                   ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |          _ __ ___  _ __   __ _ _ __                         ��\n");
	printf("��        | |         | '_ ` _ #| '_ # / _` | '_ #                        ��\n");
	printf("��        | |____     | | | | | | |_) | (_| | | | |                       ��\n");
	printf("��         #_____|    |_| |_| |_| .__/ #__,_|_| |_|                       ��\n");
	printf("��                              | |                                       ��\n");
	printf("��                              |_|                                       ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                 ____                                    ��\n");
	printf("��         / ____|               |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ # |__ <                                   ��\n");
	printf("��        | |__| | (_| | | | | | |___) |                                  ��\n");
	printf("��         #_____|#__,_|_| |_| |_|____/                                   ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |          _ __ ___  _ __   __ _ _ __                         ��\n");
	printf("��        | |         | '_ ` _ #| '_ # / _` | '_ #|                       ��\n");
	printf("��        | |____     | | | | | | |_) | (_| | | | |                       ��\n");
	printf("��         #_____|    |_| |_| |_| .__/ #__,_|_| |_|                       ��\n");
	printf("��                              | |                                       ��\n");
	printf("��                              |_|                |___/                  ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                 ____                                    ��\n");
	printf("��         / ____|               |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ # |__ <                                   ��\n");
	printf("��        | |__| | (_| | | | | | |___) |                                  ��\n");
	printf("��         #_____|#__,_|_| |_| |_|____/                                   ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |          _ __ ___  _ __   __ _ _ __                         ��\n");
	printf("��        | |         | '_ ` _ #| '_ # / _` | '_ #|                       ��\n");
	printf("��        | |____     | | | | | | |_) | (_| | | | |                       ��\n");
	printf("��         #_____|    |_| |_| |_| .__/ #__,_|_| |_|                       ��\n");
	printf("��                              | |                 __/ |                 ��\n");
	printf("��                              |_|                |___/                  ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                 ____                                    ��\n");
	printf("��         / ____|               |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ # |__ <                                   ��\n");
	printf("��        | |__| | (_| | | | | | |___) |                                  ��\n");
	printf("��         #_____|#__,_|_| |_| |_|____/                                   ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |          _ __ ___  _ __   __ _ _ __                         ��\n");
	printf("��        | |         | '_ ` _ #| '_ # / _` | '_ #|                       ��\n");
	printf("��        | |____     | | | | | | |_) | (_| | | | |                       ��\n");
	printf("��         #_____|    |_| |_| |_| .__/ #__,_|_| |_|#__, |                 ��\n");
	printf("��                              | |                 __/ |                 ��\n");
	printf("��                              |_|                |___/                  ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                 ____                                    ��\n");
	printf("��         / ____|               |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ # |__ <                                   ��\n");
	printf("��        | |__| | (_| | | | | | |___) |                                  ��\n");
	printf("��         #_____|#__,_|_| |_| |_|____/                                   ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |          _ __ ___  _ __   __ _ _ __                         ��\n");
	printf("��        | |         | '_ ` _ #| '_ # / _` | '_ #|                       ��\n");
	printf("��        | |____     | | | | | | |_) | (_| | | | | |_| |                 ��\n");
	printf("��         #_____|    |_| |_| |_| .__/ #__,_|_| |_|#__, |                 ��\n");
	printf("��                              | |                 __/ |                 ��\n");
	printf("��                              |_|                |___/                  ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                 ____                                    ��\n");
	printf("��         / ____|               |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ # |__ <                                   ��\n");
	printf("��        | |__| | (_| | | | | | |___) |                                  ��\n");
	printf("��         #_____|#__,_|_| |_| |_|____/                                   ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |          _ __ ___  _ __   __ _ _ __                         ��\n");
	printf("��        | |         | '_ ` _ #| '_ # / _` | '_ #| | | |                 ��\n");
	printf("��        | |____     | | | | | | |_) | (_| | | | | |_| |                 ��\n");
	printf("��         #_____|    |_| |_| |_| .__/ #__,_|_| |_|#__, |                 ��\n");
	printf("��                              | |                 __/ |                 ��\n");
	printf("��                              |_|                |___/                  ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                 ____                                    ��\n");
	printf("��         / ____|               |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ # |__ <                                   ��\n");
	printf("��        | |__| | (_| | | | | | |___) |                                  ��\n");
	printf("��         #_____|#__,_|_| |_| |_|____/                                   ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |          _ __ ___  _ __   __ _ _ __  _   _                  ��\n");
	printf("��        | |         | '_ ` _ #| '_ # / _` | '_ #| | | |                 ��\n");
	printf("��        | |____     | | | | | | |_) | (_| | | | | |_| |                 ��\n");
	printf("��         #_____|    |_| |_| |_| .__/ #__,_|_| |_|#__, |                 ��\n");
	printf("��                              | |                 __/ |                 ��\n");
	printf("��                              |_|                |___/                  ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                 ____                                    ��\n");
	printf("��         / ____|               |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ # |__ <                                   ��\n");
	printf("��        | |__| | (_| | | | | | |___) |                                  ��\n");
	printf("��         #_____|#__,_|_| |_| |_|____/                                   ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |          _ __ ___  _ __   __ _ _ __  _   _                  ��\n");
	printf("��        | |      _  | '_ ` _ #| '_ # / _` | '_ #| | | |                 ��\n");
	printf("��        | |____ (_) | | | | | | |_) | (_| | | | | |_| |                 ��\n");
	printf("��         #_____|    |_| |_| |_| .__/ #__,_|_| |_|#__, |                 ��\n");
	printf("��                              | |                 __/ |                 ��\n");
	printf("��                              |_|                |___/                  ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(100);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                 ____                                    ��\n");
	printf("��         / ____|               |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ # |__ <                                   ��\n");
	printf("��        | |__| | (_| | | | | | |___) |                                  ��\n");
	printf("��         #_____|#__,_|_| |_| |_|____/                                   ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |          _ __ ___  _ __   __ _ _ __  _   _                  ��\n");
	printf("��        | |    / _ #| '_ ` _ #| '_ # / _` | '_ #| | | |                 ��\n");
	printf("��        | |___| (_) | | | | | | |_) | (_| | | | | |_| |                 ��\n");
	printf("��         #_____#   /|_| |_| |_| .__/ #__,_|_| |_|#__, |                 ��\n");
	printf("��                              | |                 __/ |                 ��\n");
	printf("��                              |_|                |___/                  ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(100);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                 ____                                    ��\n");
	printf("��         / ____|               |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ # |__ <                                   ��\n");
	printf("��        | |__| | (_| | | | | | |___) |                                  ��\n");
	printf("��         #_____|#__,_|_| |_| |_|____/                                   ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |     ___  _ __ ___  _ __   __ _ _ __  _   _                  ��\n");
	printf("��        | |    / _ #| '_ ` _ #| '_ # / _` | '_ #| | | |                 ��\n");
	printf("��        | |___| (_) | | | | | | |_) | (_| | | | | |_| |                 ��\n");
	printf("��         #_____#___/|_| |_| |_| .__/ #__,_|_| |_|#__, |                 ��\n");
	printf("��                              | |                 __/ |                 ��\n");
	printf("��                              |_|                |___/                  ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(100);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                 ____                                    ��\n");
	printf("��         / ____|               |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ # |__ <                                   ��\n");
	printf("��        | |__| | (_| | | | | | |___) |                                  ��\n");
	printf("��         #_____|#__,_|_| |_| |_|____/                                   ��\n");
	printf("��         / ____| |                                                      ��\n");
	printf("��        | |     ___  _ __ ___  _ __   __ _ _ __  _   _                  ��\n");
	printf("��        | |  _ / _ #| '_ ` _ #| '_ # / _` | '_ #| | | |                 ��\n");
	printf("��        | |___| (_) | | | | | | |_) | (_| | | | | |_| |                 ��\n");
	printf("��         #_____#___/|_| |_| |_| .__/ #__,_|_| |_|#__, |                 ��\n");
	printf("��                 |            | |                 __/ |                 ��\n");
	printf("��                              |_|                |___/                  ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                 ____                                    ��\n");
	printf("��         / ____|               |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ # |__ <                                   ��\n");
	printf("��        | |__| | (_| | | | | | |___) |                                  ��\n");
	printf("��         #_____|#__,_|_| |_| |_|____/                                   ��\n");
	printf("��         / ____| |                                                      ��\n");
	printf("��        | |     ___  _ __ ___  _ __   __ _ _ __  _   _                  ��\n");
	printf("��        | | __ / _ #| '_ ` _ #| '_ # / _` | '_ #| | | |                 ��\n");
	printf("��        | |___| (_) | | | | | | |_) | (_| | | | | |_| |                 ��\n");
	printf("��         #_____#___/|_| |_| |_| .__/ #__,_|_| |_|#__, |                 ��\n");
	printf("��                 |            | |                 __/ |                 ��\n");
	printf("��                 |            |_|                |___/                  ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                 ____                                    ��\n");
	printf("��         / ____|               |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ # |__ <                                   ��\n");
	printf("��        | |__| | (_| | | | | | |___) |                                  ��\n");
	printf("��         #_____|#__,_|_| |_| |_|____/                                   ��\n");
	printf("��         / ____| .                                                      ��\n");
	printf("��        | |     ___  _ __ ___  _ __   __ _ _ __  _   _                  ��\n");
	printf("��        | |__. / _ #| '_ ` _ #| '_ # / _` | '_ #| | | |                 ��\n");
	printf("��        | |___| (_) | | | | | | |_) | (_| | | | | |_| |                 ��\n");
	printf("��         #_____#___/|_| |_| |_| .__/ #__,_|_| |_|#__, |                 ��\n");
	printf("��                 .            | |                 __/ |                 ��\n");
	printf("��                 |            |_|                |___/                  ��\n");
	printf("��                 |                                                      ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                 ____                                    ��\n");
	printf("��         / ____| |             |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ # |__ <                                   ��\n");
	printf("��        | |__| | (_| | | | | | |___) |                                  ��\n");
	printf("��         #_____|#__,_|_| |_| |_|____/                                   ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |     ___  _ __ ___  _ __   __ _ _ __  _   _                  ��\n");
	printf("��        | |_.  / _ #| '_ ` _ #| '_ # / _` | '_ #| | | |                 ��\n");
	printf("��        | |___| (_) | | | | | | |_) | (_| | | | | |_| |                 ��\n");
	printf("��         #_____#___/|_| |_| |_| .__/ #__,_|_| |_|#__, |                 ��\n");
	printf("��                              | |                 __/ |                 ��\n");
	printf("��                 .            |_|                |___/                  ��\n");
	printf("��                 |                                                      ��\n");
	printf("��                 |                                                      ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____  |              ____                                    ��\n");
	printf("��         / ____| |             |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ # |__ <                                   ��\n");
	printf("��        | |__| | (_| | | | | | |___) |                                  ��\n");
	printf("��         #_____|#__,_|_| |_| |_|____/                                   ��\n");
	printf("��         / ____| .                                                      ��\n");
	printf("��        | |     ___  _ __ ___  _ __   __ _ _ __  _   _                  ��\n");
	printf("��        | |.  ./ _ #| '_ ` _ #| '_ # / _` | '_ #| | | |                 ��\n");
	printf("��        | |___| (_) | | | | | | |_) | (_| | | | | |_| |                 ��\n");
	printf("��         #_____#___/|_| |_| |_| .__/ #__,_|_| |_|#__, |                 ��\n");
	printf("��                 .            | |                 __/ |                 ��\n");
	printf("��                              |_|                |___/                  ��\n");
	printf("��                 .                                                      ��\n");
	printf("��                 |                                                      ��\n");
	printf("��                 |                                                      ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                 |                                                      ��\n");
	printf("��          _____  |              ____                                    ��\n");
	printf("��         / ____| .             |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ # |__ <                                   ��\n");
	printf("��        | |__| | (_| | | | | | |___) |                                  ��\n");
	printf("��         #_____|#__,_|_| |_| |_|____/                                   ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |     ___  _ __ ___  _ __   __ _ _ __  _   _                  ��\n");
	printf("��        | |  . / _ #| '_ ` _ #| '_ # / _` | '_ #| | | |                 ��\n");
	printf("��        | |___| (_) | | | | | | |_) | (_| | | | | |_| |                 ��\n");
	printf("��         #_____#___/|_| |_| |_| .__/ #__,_|_| |_|#__, |                 ��\n");
	printf("��                              | |                 __/ |                 ��\n");
	printf("��                 .            |_|                |___/                  ��\n");
	printf("��                                                                        ��\n");
	printf("��                 .                                                      ��\n");
	printf("��                 |                                                      ��\n");
	printf("��                 |                                                      ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                 |                                                      ��\n");
	printf("��                 |                                                      ��\n");
	printf("��          _____  .              ____                                    ��\n");
	printf("��         / ____|               |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ # |__ <                                   ��\n");
	printf("��        | |__| | (_| | | | | | |___) |                                  ��\n");
	printf("��         #_____|#__,_|_| |_| |_|____/                                   ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |     ___  _ __ ___  _ __   __ _ _ __  _   _                  ��\n");
	printf("��       _| | .  / _ #| '_ ` _ #| '_ # / _` | '_ #| | | |                 ��\n");
	printf("��        | |___| (_) | | | | | | |_) | (_| | | | | |_| |                 ��\n");
	printf("��         #_____#___/|_| |_| |_| .__/ #__,_|_| |_|#__, |                 ��\n");
	printf("��                              | |                 __/ |                 ��\n");
	printf("��                              |_|                |___/                  ��\n");
	printf("��                 .                                                      ��\n");
	printf("��                                                                        ��\n");
	printf("��                 .                                                      ��\n");
	printf("��                 |                                                      ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                 |                                                      ��\n");
	printf("��                 |                                                      ��\n");
	printf("��                 .                                                      ��\n");
	printf("��          _____                 ____                                    ��\n");
	printf("��         / ____| .             |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ # |__ <                                   ��\n");
	printf("��        | |__| | (_| | | | | | |___) |                                  ��\n");
	printf("��         #_____|#__,_|_| |_| |_|____/                                   ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |     ___  _ __ ___  _ __   __ _ _ __  _   _                  ��\n");
	printf("��      __| |.   / _ #| '_ ` _ #| '_ # / _` | '_ #| | | |                 ��\n");
	printf("��        | |___| (_) | | | | | | |_) | (_| | | | | |_| |                 ��\n");
	printf("��         #_____#___/|_| |_| |_| .__/ #__,_|_| |_|#__, |                 ��\n");
	printf("��                              | |                 __/ |                 ��\n");
	printf("��                              |_|                |___/                  ��\n");
	printf("��                                                                        ��\n");
	printf("��                 .                                                      ��\n");
	printf("��                                                                        ��\n");
	printf("��                 .                                                      ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                 |                                                      ��\n");
	printf("��                 |                                                      ��\n");
	printf("��                 .                                                      ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____  .              ____                                    ��\n");
	printf("��         / ____|               |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ # |__ <                                   ��\n");
	printf("��        | |__| | (_| | | | | | |___) |                                  ��\n");
	printf("��         #_____|#__,_|_| |_| |_|____/                                   ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |     ___  _ __ ___  _ __   __ _ _ __  _   _                  ��\n");
	printf("��     __.| |    / _ #| '_ ` _ #| '_ # / _` | '_ #| | | |                 ��\n");
	printf("��        | |___| (_) | | | | | | |_) | (_| | | | | |_| |                 ��\n");
	printf("��         #_____#___/|_| |_| |_| .__/ #__,_|_| |_|#__, |                 ��\n");
	printf("��                              | |                 __/ |                 ��\n");
	printf("��                              |_|                |___/                  ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                 .                                                      ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                  |                                                     ��\n");
	printf("��                  |                                                     ��\n");
	printf("��                  .                                                     ��\n");
	printf("��                                                                        ��\n");
	printf("��                  .                                                     ��\n");
	printf("��          _____                 ____                                    ��\n");
	printf("��         / ____|               |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ # |__ <                                   ��\n");
	printf("��        | |__| | (_| | | | | | |___) |                                  ��\n");
	printf("��         #_____|#__,_|_| |_| |_|____/                                   ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |     ___  _ __ ___  _ __   __ _ _ __  _   _                  ��\n");
	printf("��    __. | |    / _ #| '_ ` _ #| '_ # / _` | '_ #| | | |                 ��\n");
	printf("��        | |___| (_) | | | | | | |_) | (_| | | | | |_| |                 ��\n");
	printf("��         #_____#___/|_| |_| |_| .__/ #__,_|_| |_|#__, |                 ��\n");
	printf("��                              | |                 __/ |                 ��\n");
	printf("��                              |_|                |___/                  ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                 .                                                      ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                 |                                                      ��\n");
	printf("��                 .                                                      ��\n");
	printf("��                                                                        ��\n");
	printf("��                 .                                                      ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                 ____                                    ��\n");
	printf("��         / ____|               |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ # |__ <                                   ��\n");
	printf("��        | |__| | (_| | | | | | |___) |                                  ��\n");
	printf("��         #_____|#__,_|_| |_| |_|____/                                   ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |     ___  _ __ ___  _ __   __ _ _ __  _   _                  ��\n");
	printf("��   __.  | |    / _ #| '_ ` _ #| '_ # / _` | '_ #| | | |                 ��\n");
	printf("��        | |___| (_) | | | | | | |_) | (_| | | | | |_| |                 ��\n");
	printf("��         #_____#___/|_| |_| |_| .__/ #__,_|_| |_|#__, |                 ��\n");
	printf("��                              | |                 __/ |                 ��\n");
	printf("��                              |_|                |___/                  ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                 .                                                      ��\n");
	printf("��                                                                        ��\n");
	printf("��                 .                                                      ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                 ____                                    ��\n");
	printf("��         / ____|               |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ # |__ <                                   ��\n");
	printf("��        | |__| | (_| | | | | | |___) |                                  ��\n");
	printf("��         #_____|#__,_|_| |_| |_|____/                                   ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |     ___  _ __ ___  _ __   __ _ _ __  _   _                  ��\n");
	printf("��  __.  .| |    / _ #| '_ ` _ #| '_ # / _` | '_ #| | | |                 ��\n");
	printf("��        | |___| (_) | | | | | | |_) | (_| | | | | |_| |                 ��\n");
	printf("��         #_____#___/|_| |_| |_| .__/ #__,_|_| |_|#__, |                 ��\n");
	printf("��                              | |                 __/ |                 ��\n");
	printf("��                              |_|                |___/                  ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                 .                                                      ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                 ____                                    ��\n");
	printf("��         / ____|               |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ # |__ <                                   ��\n");
	printf("��        | |__| | (_| | | | | | |___) |                                  ��\n");
	printf("��         #_____|#__,_|_| |_| |_|____/                                   ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |     ___  _ __ ___  _ __   __ _ _ __  _   _                  ��\n");
	printf("�� __.  . | |    / _ #| '_ ` _ #| '_ # / _` | '_ #| | | |                 ��\n");
	printf("��        | |___| (_) | | | | | | |_) | (_| | | | | |_| |                 ��\n");
	printf("��         #_____#___/|_| |_| |_| .__/ #__,_|_| |_|#__, |                 ��\n");
	printf("��                              | |                 __/ |                 ��\n");
	printf("��                              |_|                |___/                  ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                 .                                                      ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                 ____                                    ��\n");
	printf("��         / ____|               |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ # |__ <                                   ��\n");
	printf("��        | |__| | (_| | | | | | |___) |                                  ��\n");
	printf("��         #_____|#__,_|_| |_| |_|____/                                   ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |     ___  _ __ ___  _ __   __ _ _ __  _   _                  ��\n");
	printf("��__.  .  | |    / _ #| '_ ` _ #| '_ # / _` | '_ #| | | |                 ��\n");
	printf("��        | |___| (_) | | | | | | |_) | (_| | | | | |_| |                 ��\n");
	printf("��         #_____#___/|_| |_| |_| .__/ #__,_|_| |_|#__, |                 ��\n");
	printf("��                              | |                 __/ |                 ��\n");
	printf("��                              |_|                |___/                  ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                 ____                                    ��\n");
	printf("��         / ____|               |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ # |__ <                                   ��\n");
	printf("��        | |__| | (_| | | | | | |___) |                                  ��\n");
	printf("��         #_____|#__,_|_| |_| |_|____/                                   ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |     ___  _ __ ___  _ __   __ _ _ __  _   _                  ��\n");
	printf("��_.  .   | |    / _ #| '_ ` _ #| '_ # / _` | '_ #| | | |                 ��\n");
	printf("��        | |___| (_) | | | | | | |_) | (_| | | | | |_| |                 ��\n");
	printf("��         #_____#___/|_| |_| |_| .__/ #__,_|_| |_|#__, |                 ��\n");
	printf("��                              | |                 __/ |                 ��\n");
	printf("��                              |_|                |___/                  ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                 ____                                    ��\n");
	printf("��         / ____|               |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ # |__ <                                   ��\n");
	printf("��        | |__| | (_| | | | | | |___) |                                  ��\n");
	printf("��         #_____|#__,_|_| |_| |_|____/                                   ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |     ___  _ __ ___  _ __   __ _ _ __  _   _                  ��\n");
	printf("��.  .    | |    / _ #| '_ ` _ #| '_ # / _` | '_ #| | | |                 ��\n");
	printf("��        | |___| (_) | | | | | | |_) | (_| | | | | |_| |                 ��\n");
	printf("��         #_____#___/|_| |_| |_| .__/ #__,_|_| |_|#__, |                 ��\n");
	printf("��                              | |                 __/ |                 ��\n");
	printf("��                              |_|                |___/                  ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                 ____                                    ��\n");
	printf("��         / ____|               |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ # |__ <                                   ��\n");
	printf("��        | |__| | (_| | | | | | |___) |                                  ��\n");
	printf("��         #_____|#__,_|_| |_| |_|____/                                   ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |     ___  _ __ ___  _ __   __ _ _ __  _   _                  ��\n");
	printf("��  .     | |    / _ #| '_ ` _ #| '_ # / _` | '_ #| | | |                 ��\n");
	printf("��        | |___| (_) | | | | | | |_) | (_| | | | | |_| |                 ��\n");
	printf("��         #_____#___/|_| |_| |_| .__/ #__,_|_| |_|#__, |                 ��\n");
	printf("��                              | |                 __/ |                 ��\n");
	printf("��                              |_|                |___/                  ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                 ____                                    ��\n");
	printf("��         / ____|               |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ # |__ <                                   ��\n");
	printf("��        | |__| | (_| | | | | | |___) |                                  ��\n");
	printf("��         #_____|#__,_|_| |_| |_|____/                                   ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |     ___  _ __ ___  _ __   __ _ _ __  _   _                  ��\n");
	printf("�� .      | |    / _ #| '_ ` _ #| '_ # / _` | '_ #| | | |                 ��\n");
	printf("��        | |___| (_) | | | | | | |_) | (_| | | | | |_| |                 ��\n");
	printf("��         #_____#___/|_| |_| |_| .__/ #__,_|_| |_|#__, |                 ��\n");
	printf("��                              | |                 __/ |                 ��\n");
	printf("��                              |_|                |___/                  ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                 ____                                    ��\n");
	printf("��         / ____|               |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ # |__ <                                   ��\n");
	printf("��        | |__| | (_| | | | | | |___) |                                  ��\n");
	printf("��         #_____|#__,_|_| |_| |_|____/                                   ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |     ___  _ __ ___  _ __   __ _ _ __  _   _                  ��\n");
	printf("��.       | |    / _ #| '_ ` _ #| '_ # / _` | '_ #| | | |                 ��\n");
	printf("��        | |___| (_) | | | | | | |_) | (_| | | | | |_| |                 ��\n");
	printf("��         #_____#___/|_| |_| |_| .__/ #__,_|_| |_|#__, |                 ��\n");
	printf("��                              | |                 __/ |                 ��\n");
	printf("��                              |_|                |___/                  ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(25);	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��          _____                 ____                                    ��\n");
	printf("��         / ____|               |___ #                                   ��\n");
	printf("��        | |  __  __ _ _ __ ___   __) |                                  ��\n");
	printf("��        | | |_ |/ _` | '_ ` _ # |__ <                                   ��\n");
	printf("��        | |__| | (_| | | | | | |___) |                                  ��\n");
	printf("��         #_____|#__,_|_| |_| |_|____/                                   ��\n");
	printf("��         / ____|                                                        ��\n");
	printf("��        | |     ___  _ __ ___  _ __   __ _ _ __  _   _                  ��\n");
	printf("��        | |    / _ #| '_ ` _ #| '_ # / _` | '_ #| | | |                 ��\n");
	printf("��        | |___| (_) | | | | | | |_) | (_| | | | | |_| |                 ��\n");
	printf("��         #_____#___/|_| |_| |_| .__/ #__,_|_| |_|#__, |                 ��\n");
	printf("��                              | |                 __/ |                 ��\n");
	printf("��                              |_|                |___/                  ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	system("pause");
}


int game_dev_pj_naming()//���� ������ ù �κ����� ���� ������ �̸��� ���ϴ� �Լ�
{
	int bspc = 0;
	unsigned char key;
	int ex_key = 1, i = 0, pj_name_leng, ex_bsp = 0, j = 0;

	char pj_name[80] = { '\0' };
	while (1)
	{

		system("cls");
		pj_name_leng = strlen(pj_name);
		printf("���������������������������������������\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                        ������Ʈ�� �����մϴ�.                          ��\n");
		printf("��                    ������ ������ �̸��� �����ּ���(����)               ��\n");

		printf("��                                                                        ��\n");

		printf("��                     ->%s                                   ", pj_name);
		alignment(pj_name_leng);
		printf("              ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                         ���� ����� �����ּ���                         ��\n");
		printf("��        �ѱ۷� �ۼ��� �߻��� �����Ϳ� ���ؼ��� å������ �ʽ��ϴ�        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("���������������������������������������\n");

		key = getch();
		if (key == 224)
		{
			ex_key = getch();
		}
		else if (key == ENTER)
		{
			break;
		}
		else if (key == BSP)
		{
			if (j<0)
			{
				j--;

			}
		}
		else
		{
			pj_name[j] = key;
		}
		j++;
	}

	game_dev_pj_cruit(pj_name, pj_name_leng);

	return 0;
}
void game_dev_pj_cruit(char* pj_name, int pj_name_leng)//���� ���߿� ������ ������ �����ϴ� �Լ�.
{
	int you_will_work[13] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };//�̰� ���������� ���� �������� ��ȣ�� ������.running���� ��밡��
	int taken[13] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };//������� '��������' ������ ��ȣ.// ?!??!?!?!?!??!?
	char selected[16][3] = { "->", "\0", "\0", "\0", "\0", "\0", "\0", "\0", "\0", "\0", "\0", "\0", "\0", "\0", "\0", "\0" };//ȭ��ǥ �׷����� ���� 
	char checked[13] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' };
	int i, j;
	int cruit_chk_counted = 0;//���������� ���� ������ ��. running���� ��밡��
	int menu_num = 0;//�޴� �̵��� �ʿ��� ����
	int able_to_work = 0;//���� ä�� ����� ä������� ���� ����. ������ ������ �Ƹ� �� �����ο��ϰ��̴�.
	int launch = 0;
	for (i = 0; i < 13; i++)
	{
		if (enabler[i] == 1)
		{
			strcpy(list_of_cruit[able_to_work], worker_name[i]);
			taken[able_to_work] = worker_num[i];
			your_stamina[able_to_work] = stamina[i];
			able_to_work++;
		}
		else
		{

		}
	}

	while (1)
	{
		system("cls");
		printf("���������������������������������������\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��     %s�� ������ �����մϴ�.                           ", pj_name);
		alignment(strlen(pj_name));
		printf("                   ��\n");
		printf("��                                                                        ��\n");
		printf("��  <SYSTEM>  %s                              ", system_message);
		alignment(strlen(system_message));
		printf("                              ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��     �� ������Ʈ�� ������ ������ �����ϼ���(�ִ� 4��)                   ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��     %s%s%c\t%s%s%c\t%s%s%c\t%s%s%c\t  ��\n", selected[0], list_of_cruit[0], checked[0], selected[1], list_of_cruit[1], checked[1], selected[2], list_of_cruit[2], checked[2], selected[3], list_of_cruit[3], checked[3]);
		printf("��     ü��:%d\t         %d\t           %d\t            %d\t          ��\n", stamina[taken[0]], stamina[taken[1]], stamina[taken[2]], stamina[taken[3]]);
		printf("��     %s%s%c\t%s%s%c\t%s%s%c\t%s%s%c\t  ��\n", selected[4], list_of_cruit[4], checked[4], selected[5], list_of_cruit[5], checked[5], selected[6], list_of_cruit[6], checked[6], selected[7], list_of_cruit[7], checked[7]);
		printf("��     ü��:%d\t         %d\t           %d\t            %d\t          ��\n", stamina[taken[4]], stamina[taken[5]], stamina[taken[5]], stamina[taken[7]]);
		printf("��     %s%s%c\t%s%s%c\t%s%s%c\t%s%s%c\t  ��\n", selected[8], list_of_cruit[8], checked[8], selected[9], list_of_cruit[9], checked[9], selected[10], list_of_cruit[10], checked[10], selected[11], list_of_cruit[11], checked[11]);
		printf("��     ü��:%d\t         %d\t           %d\t            %d\t          ��\n", stamina[taken[8]], stamina[taken[9]], stamina[taken[10]], stamina[taken[11]]);
		printf("��                                                                        ��\n");
		printf("��      %s �ڷ�\t                                           %s �Ϸ�\t  ��\n", selected[12], selected[15]);
		printf("��                                                                        ��\n");
		printf("���������������������������������������\n");

		key = getch();
		if (key == 224)
		{
			ex_key = getch();
			switch (ex_key)
			{
			case UP:
			{
				strcpy(system_message, system_message_init);
				strcpy(selected[menu_num], blank);
				if ((menu_num<12) || (menu_num == 15) || (menu_num == 12))
				{
					do
					{
						menu_num -= 4;
						if (menu_num<0)
						{
							menu_num += 16;
							if (menu_num == 13)
							{
								menu_num = 9;
							}
							else if (menu_num == 14)
							{
								menu_num = 10;
							}
						}
					} while (enabler[taken[menu_num]] == 0);
				}
				else
				{
					if (menu_num == 13)
					{
						menu_num = 1;
					}
					else if (menu_num == 14)
					{
						menu_num = 2;
					}
				}
				strcpy(selected[menu_num], selector);
				break;

			}
			case DOWN:
			{
				strcpy(system_message, system_message_init);
				strcpy(selected[menu_num], blank);
				if ((menu_num<12) || (menu_num == 15) || (menu_num == 12))
				{
					do
					{
						menu_num += 4;
						if (menu_num == 19)
							menu_num = 3;
						else if (menu_num == 16)
							menu_num = 0;
						if (menu_num == 13)
						{
							menu_num = 1;
						}
						else if (menu_num == 14)
						{
							menu_num = 2;
						}
					} while (enabler[taken[menu_num]] == 0);
				}
				else
				{

				}
				strcpy(selected[menu_num], selector);
				break;
			}
			case RIGHT:
			{
				strcpy(system_message, system_message_init);
				strcpy(selected[menu_num], blank);
				if ((menu_num<12) || (menu_num == 15) || (menu_num == 12))
				{
					do
					{
						menu_num++;
						menu_num = menu_num % 16;
						if (menu_num == 15)
						{
							menu_num = 0;
						}
						else if (menu_num == 13)
						{
							menu_num = 15;
						}
					} while (enabler[taken[menu_num]] == 0);
				}
				else
				{

				}
				strcpy(selected[menu_num], selector);
				break;
			}
			case LEFT:
			{
				strcpy(system_message, system_message_init);
				strcpy(selected[menu_num], blank);
				if ((menu_num<12) || (menu_num == 15) || (menu_num == 12))
				{
					do
					{
						menu_num--;
						menu_num = menu_num % 16;
						if (menu_num == 14)
						{
							menu_num = 12;
						}
						if (menu_num == -1)
						{
							menu_num += 16;
						}
					} while (enabler[taken[menu_num]] == 0);
				}
				strcpy(selected[menu_num], selector);
				break;
			}
			default:
				break;
			}
		}
		else if (key == 0xd)
		{
			if (menu_num < 12)
			{
				if (checked[menu_num]!='v')
				{
					if ((stamina[taken[menu_num]] - stamina_minus_delta[taken[menu_num]]) > 0)
					{
						if (enabler[taken[menu_num]] == 1)
						{
							you_will_work[cruit_chk_counted] = taken[menu_num];
							checked[menu_num] = 'v';
							cruit_chk_counted++;
						}
					}
					else
					{
						strcpy(system_message, err_not_enough_stamina);
					}
				}
				else
				{
					strcpy(system_message, err_selected_again);
				}
			}
			else if (menu_num == 12)
			{
				break;
			}
			else if (menu_num == 15)
			{
				if (cruit_chk_counted >= 1)
				{
					strcpy(system_message, system_message_init);//�ý��۸޼��� �ʱ�ȭ
					launch = 1;
					break;
				}
				else
				{
					strcpy(system_message, err_not_choosed);//���� �ʾҴٴ� �ý��� ���� �޼��� ���
				}
			}

		}
		fflush(stdin);
		//4�� �̻� ���� ���ϰ� �ϴ� ��ġ
		if (cruit_chk_counted == 4)
		{
			strcpy(selected[menu_num], blank);
			menu_num = 15;
			strcpy(selected[menu_num], selector);
		}

	}
	if (launch==1)
	{
		game_name_log_count++;
		strcpy(game_name_log[game_name_log_count], pj_name);
		for (i = 0; i < cruit_chk_counted; i++)
		{
			your_taked_worker_num[i] = taken[i];
		}
		your_taked_worker_num_count = arr_counter(your_taked_worker_num, 12, 0);
		game_dev_pj_running(pj_name, you_will_work, cruit_chk_counted);
	}
	


}
int disaster()//�� disaster �Լ��� ��� �糭�� ������ �����ϴ� �Լ�.Ȯ���� ����Ҽ��� �� ���� �糭�� ����(�ñ׸���.)��� �̰� 10�� �̳��� ���ϼ� ������ �ϴ� ���� ���ϴ�
{
	int a, b;
	srand(time(NULL));
	a = rand() % 100;
	a++;
	b = a;
	if (a<1)
	{
		b = 0;
	}
	else if ((a >= 1) || (a<3))
	{
		b = 1;
	}
	else if ((a >= 3) || (a<6))
	{
		b = 2;
	}
	else if ((a >= 6) || (a<10))
	{
		b = 3;
	}
	else if ((a >= 10) || (a<15))
	{
		b = 4;
	}
	else if ((a >= 15) || (a<21))
	{
		b = 5;
	}
	else if ((a >= 21) || (a<28))
	{
		b = 6;
	}
	else if ((a >= 28) || (a<36))
	{
		b = 7;
	}
	else if ((a >= 36) || (a<45))
	{
		b = 8;
	}
	else if ((a >= 45) || (a<55))
	{
		b = 9;
	}
	else if ((a >= 55) || (a<66))
	{
		b = 10;
	}
	else if ((a >= 66) || (a<78))
	{
		b = 11;
	}
	else
	{
		b = 12;
	}

	return b;
}
int game_dev_pj_running(char * pj_name, int * you_will_work, int cruit_chk_counted)//���� ������ �����ϴ� ������ ���� �Լ�./(/ȸ���/���� ���� '��ȣ' ���/���� ������ ��)�� �����ؿ´�.
{
	char gauge[11][21] = { { "�����������" }, { "�����������" }, { "�����������" }, { "�����������" }, { "�����������" }, { "�����������" }, { "�����������" }, { "�����������" }, { "�����������" }, { "�����������" }, { "�����������" } };
	int i, j;
	int game_point = 0;
	int temp;
	double game_point_programming_const;
	int game_point_graphic_const;
	int game_point_sound_const;
	int process = 0;//�� ���μ��� ������ disaster�� ������ ����
	int progress = 0;//progress �� disaster�� ������ ���� ����
	int disaster_code;
	int disaster_return;
	int when_disaster;
	double game_point_delta = 0;
	int disaster_num[13] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
	double disaster_effect[13] = { 0.3, 0.35, 0.40, 0.45, 0.5, 0.55, 0.60, 0.65, 0.7, 0.75, 0.80, 0.85, 0.9 };
	char disasters[14][31] = { { "���̺������� �����Ǿ����ϴ�!!!" }, { "     ������ �߻��߽��ϴ�!!    " }, { " ��Ը� ���װ� �߻��߽��ϴ�!! " }, { "����翡�� ��������! �ǿ���!" }, { "�繫�ǿ� �������� â���մϴ�! " }, { "      ������ �߻��߽��ϴ�!    " }, { "  ������ �߱��� �����ƽ��ϴ�! " }, { " ��ǻ�Ϳ� �ݶ� ��ҽ��ϴ�!  " }, { "������ �߱����� ���� �ǿ���!" }, { " ���������� �������� ������� " }, { "          ���� ����!        " }, { " ���α׷��� �������� �ʽ��ϴ� " }, { "         �˼����� ����!       " } };

	for (i = 0; i < cruit_chk_counted; i++)
	{
		stamina[you_will_work[i]] -= stamina_minus_delta[you_will_work[i]];
	}

	//
	srand(time(NULL));
	disaster_code = rand() % 100;
	if (disaster_code < 5)
	{
		disaster_return = disaster();
	}
	srand(time(NULL));
	when_disaster = rand() % 60;
	when_disaster += 20;
	srand(time(NULL));
	game_point_programming_const = ((rand() % 5) + 1);
	srand(time(NULL));
	game_point_graphic_const = ((rand() % 5) + 1);
	srand(time(NULL));
	game_point_sound_const = ((rand() % 5) + 1);
	//for ���� �̿��Ͽ� frame_gauge ��� ;
	//�Լ� disaster �� �����Ͽ� �ݺ�Ƚ���� �ۼ�Ʈ�� ���̵� ��ü��ȯȽ���� ������ ����.
	//disaster�� ȿ���� ������ Ÿ�ֿ̹� ����, �׷��� ���� �ʱ⿡�� �������� ����, �Ƹ� �ݺ����� �����ϴ� ������� �����ϸ� �ɰͰ���.()
	for (progress = 0; progress < 100*cruit_chk_counted; progress++)
	{
		system("cls");
		printf("���������������������������������������\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                  �ϼ���: %s                          ��\n", gauge[progress / (10*cruit_chk_counted)]);
		printf("��                                                                        ��\n");
		printf("��                             %s�� �������Դϴ�.              ", pj_name);
		alignment(strlen(pj_name));
		printf("             ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                       %s��(��) �������Դϴ�!!                    ��\n", worker_name[you_will_work[progress / (100*cruit_chk_counted / cruit_chk_counted)]]);//�� �� ����. ��� ���� ó��(integer divide by zero)�� ���� ����� ���´�.
		printf("��                                                                        ��\n");
		printf("��                     +    ���α׷���  :  %d              ", programming[you_will_work[progress / (100*cruit_chk_counted / cruit_chk_counted)]]);
		alignment(digiter(programming[you_will_work[(progress / (100*cruit_chk_counted / cruit_chk_counted))]]));
		printf("                 ��\n");
		printf("��                     +    �׷���      :  %d              ", graphic[you_will_work[progress / (100*cruit_chk_counted / cruit_chk_counted)]]);
		alignment(digiter(graphic[you_will_work[(progress / (100*cruit_chk_counted / cruit_chk_counted))]]));
		printf("                 ��\n");
		printf("��                     +    ����      :  %d              ", sound[you_will_work[progress / (100*cruit_chk_counted / cruit_chk_counted)]]);
		alignment(digiter(sound[you_will_work[(progress / (100*cruit_chk_counted / cruit_chk_counted))]]));
		printf("                 ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                         ������ �ϼ���:  %d            ", game_point);
		alignment(digiter(game_point));
		printf("                   ��\n");
		printf("��                                                                        ��\n");
		printf("���������������������������������������\n");
		Sleep(500);
		game_point_delta = ((programming[you_will_work[progress / (100*cruit_chk_counted / cruit_chk_counted)]] * game_point_programming_const) + (graphic[you_will_work[progress / (100*cruit_chk_counted / cruit_chk_counted)]] * game_point_graphic_const) + (sound[you_will_work[(progress / (100*cruit_chk_counted / cruit_chk_counted))]] * game_point_sound_const)) / 10;
		game_point += game_point_delta;

		if (disaster_code < 5)
		{
			if (progress == when_disaster)
			{
				system("cls");
				printf("%d\n", disaster_return);
				printf("���������������������������������������\n");
				printf("��                                                                        ��\n");
				printf("��                                                                        ��\n");
				printf("��                                                                        ��\n");
				printf("��                                                                        ��\n");
				printf("��                                                                        ��\n");
				printf("��                                                                        ��\n");
				printf("��                                                                        ��\n");
				printf("��                                                                        ��\n");
				printf("��                                                                        ��\n");
				printf("��                                                                        ��\n");
				printf("��                             ���� �߻�!!                                ��\n");
				printf("��                                                                        ��\n");
				printf("��                    %s                       ", disasters[disaster_return]);
				alignment(strlen(disasters[disaster_return]));
				printf("  ��\n");
				printf("��                                                                        ��\n");
				printf("��             �������� ������ �ϼ����� �Ϻΰ� �սǵ˴ϴ�!                ��\n");
				printf("��                                                                        ��\n");
				printf("��                                                                        ��\n");
				printf("��                                                                        ��\n");
				printf("��                                                                        ��\n");
				printf("��                                                                        ��\n");
				printf("��                                                                        ��\n");
				printf("��                                                                        ��\n");
				printf("���������������������������������������\n");
				game_point = (game_point*(disaster_effect[disaster_return] * 100)) / 100;
				Sleep(3000);
			}
		}

	}
	game_dev_pj_selling(game_point, pj_name);
	






	return 0;
}
int maxi(int champion,int challenger)//�׷����� ������ �ִ밪�� ���ϴ� �Լ�
{
	if (champion>challenger)
	{
		return champion;
	}
	else
	{
		return challenger;
	}
}
int game_dev_pj_selling(int game_point, char * pj_name)
{
	//�׷����� ȣ�⿡�� 3���� �迭�� ����.((x:��ǥ��)(y:��ǥ��)(z:��ä��))
	//1.5�ʴ� �ϳ���, �Ѵ޵��� �� 45��, ĭ�� 6*30
	char graph[31][7][3] = { { { "  " }, { "  " }, { "  " }, { "  " }, { "  " }, { "  " } }, { { "  " }, { "  " }, { "  " }, { "  " }, { "  " }, { "  " } }, { { "  " }, { "  " }, { "  " }, { "  " }, { "  " }, { "  " } }, { { "  " }, { "  " }, { "  " }, { "  " }, { "  " }, { "  " } }, { { "  " }, { "  " }, { "  " }, { "  " }, { "  " }, { "  " } }, { { "  " }, { "  " }, { "  " }, { "  " }, { "  " }, { "  " } }, { { "  " }, { "  " }, { "  " }, { "  " }, { "  " }, { "  " } }, { { "  " }, { "  " }, { "  " }, { "  " }, { "  " }, { "  " } }, { { "  " }, { "  " }, { "  " }, { "  " }, { "  " }, { "  " } }, { { "  " }, { "  " }, { "  " }, { "  " }, { "  " }, { "  " } }, { { "  " }, { "  " }, { "  " }, { "  " }, { "  " }, { "  " } }, { { "  " }, { "  " }, { "  " }, { "  " }, { "  " }, { "  " } }, { { "  " }, { "  " }, { "  " }, { "  " }, { "  " }, { "  " } }, { { "  " }, { "  " }, { "  " }, { "  " }, { "  " }, { "  " } }, { { "  " }, { "  " }, { "  " }, { "  " }, { "  " }, { "  " } }, { { "  " }, { "  " }, { "  " }, { "  " }, { "  " }, { "  " } }, { { "  " }, { "  " }, { "  " }, { "  " }, { "  " }, { "  " } }, { { "  " }, { "  " }, { "  " }, { "  " }, { "  " }, { "  " } }, { { "  " }, { "  " }, { "  " }, { "  " }, { "  " }, { "  " } }, { { "  " }, { "  " }, { "  " }, { "  " }, { "  " }, { "  " } }, { { "  " }, { "  " }, { "  " }, { "  " }, { "  " }, { "  " } }, { { "  " }, { "  " }, { "  " }, { "  " }, { "  " }, { "  " } }, { { "  " }, { "  " }, { "  " }, { "  " }, { "  " }, { "  " } }, { { "  " }, { "  " }, { "  " }, { "  " }, { "  " }, { "  " } }, { { "  " }, { "  " }, { "  " }, { "  " }, { "  " }, { "  " } }, { { "  " }, { "  " }, { "  " }, { "  " }, { "  " }, { "  " } }, { { "  " }, { "  " }, { "  " }, { "  " }, { "  " }, { "  " } }, { { "  " }, { "  " }, { "  " }, { "  " }, { "  " }, { "  " } }, { { "  " }, { "  " }, { "  " }, { "  " }, { "  " }, { "  " } }, { { "  " }, { "  " }, { "  " }, { "  " }, { "  " }, { "  " } }, { { "  " }, { "  " }, { "  " }, { "  " }, { "  " }, { "  " } } };
	int relative_value[30];
	int i, j;
	int daily_value[30];
	char graph_on[3] = {"��"};
	char graph_off[3] = { "  " };
	int maxo;//�׷������� �ִ밪
	double temp;
	double selled_count = (game_point / 10);
	double selled_count_delta=1;//delta���� 0.96~1.16
	int total_selled = selled_count;
	double negative_environment =1;

	loading();
	maxo = selled_count;
	for ( i = 0; i < 30; i++)
	{
		srand(time(NULL));
		selled_count_delta = (((rand() % 10)-5) / 100) + 1.1;
		negative_environment *= (1+(0.5*company_lv));
		daily_value[i] = selled_count;

		for (j = 0; j < i; j++)
		{
			temp = (daily_value[j] * 100) / maxo;
			if (temp > 81)
			{
				strcpy(graph[j][0], graph_on);
				strcpy(graph[j][1], graph_on);
				strcpy(graph[j][2], graph_on);
				strcpy(graph[j][3], graph_on);
				strcpy(graph[j][4], graph_on);
				strcpy(graph[j][5], graph_on);
			}
			else if (temp > 65)
			{
				strcpy(graph[j][0], graph_on);
				strcpy(graph[j][1], graph_on);
				strcpy(graph[j][2], graph_on);
				strcpy(graph[j][3], graph_on);
				strcpy(graph[j][4], graph_on);
				strcpy(graph[j][5], graph_off);
			}
			else if (temp > 49)
			{
				strcpy(graph[j][0], graph_on);
				strcpy(graph[j][1], graph_on);
				strcpy(graph[j][2], graph_on);
				strcpy(graph[j][3], graph_on);
				strcpy(graph[j][4], graph_off);
				strcpy(graph[j][5], graph_off);
			}
			else if (temp > 33)
			{
				strcpy(graph[j][0], graph_on);
				strcpy(graph[j][1], graph_on);
				strcpy(graph[j][2], graph_on);
				strcpy(graph[j][3], graph_off);
				strcpy(graph[j][4], graph_off);
				strcpy(graph[j][5], graph_off);
			}
			else if (temp > 17)
			{
				strcpy(graph[j][0], graph_on);
				strcpy(graph[j][1], graph_on);
				strcpy(graph[j][2], graph_off);
				strcpy(graph[j][3], graph_off);
				strcpy(graph[j][4], graph_off);
				strcpy(graph[j][5], graph_off);
			}
			else if (temp > 8)
			{
				strcpy(graph[j][0], graph_on);
				strcpy(graph[j][1], graph_off);
				strcpy(graph[j][2], graph_off);
				strcpy(graph[j][3], graph_off);
				strcpy(graph[j][4], graph_off);
				strcpy(graph[j][5], graph_off);
			}
			else
			{
				strcpy(graph[j][0], graph_off);
				strcpy(graph[j][1], graph_off);
				strcpy(graph[j][2], graph_off);
				strcpy(graph[j][3], graph_off);
				strcpy(graph[j][4], graph_off);
				strcpy(graph[j][5], graph_off);
			}
		}


		system("cls");
		printf("���������������������������������������\n");//81~100
		printf("��                                                                        ��\n");//65~80
		printf("��                                                                        ��\n");//49~64
		printf("��                                                                        ��\n");//33~48
		printf("��                                                                        ��\n");//17~32
		printf("��                                                                        ��\n");//~16
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                          %s�� �Ǹ����Դϴ�.                ", pj_name);
		alignment(strlen(pj_name));
		printf("              ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��      %s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s      ��\n", graph[0][5], graph[1][5], graph[2][5], graph[3][5], graph[4][5], graph[5][5], graph[6][5], graph[7][5], graph[8][5], graph[9][5], graph[10][5], graph[11][5], graph[12][5], graph[13][5], graph[14][5], graph[15][5], graph[16][5], graph[17][5], graph[18][5], graph[19][5], graph[20][5], graph[21][5], graph[22][5], graph[23][5], graph[24][5], graph[25][5], graph[26][5], graph[27][5], graph[28][5], graph[29][5]);
		printf("��      %s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s      ��\n", graph[0][4], graph[1][4], graph[2][4], graph[3][4], graph[4][4], graph[5][4], graph[6][4], graph[7][4], graph[8][4], graph[9][4], graph[10][4], graph[11][4], graph[12][4], graph[13][4], graph[14][4], graph[15][4], graph[16][4], graph[17][4], graph[18][4], graph[19][4], graph[20][4], graph[21][4], graph[22][4], graph[23][4], graph[24][4], graph[25][4], graph[26][4], graph[27][4], graph[28][4], graph[29][4]);
		printf("��      %s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s      ��\n", graph[0][3], graph[1][3], graph[2][3], graph[3][3], graph[4][3], graph[5][3], graph[6][3], graph[7][3], graph[8][3], graph[9][3], graph[10][3], graph[11][3], graph[12][3], graph[13][3], graph[14][3], graph[15][3], graph[16][3], graph[17][3], graph[18][3], graph[19][3], graph[20][3], graph[21][3], graph[22][3], graph[23][3], graph[24][3], graph[25][3], graph[26][3], graph[27][3], graph[28][3], graph[29][3]);
		printf("��      %s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s      ��\n", graph[0][2], graph[1][2], graph[2][2], graph[3][2], graph[4][2], graph[5][2], graph[6][2], graph[7][2], graph[8][2], graph[9][2], graph[10][2], graph[11][2], graph[12][2], graph[13][2], graph[14][2], graph[15][2], graph[16][2], graph[17][2], graph[18][2], graph[19][2], graph[20][2], graph[21][2], graph[22][2], graph[23][2], graph[24][2], graph[25][2], graph[26][2], graph[27][2], graph[28][2], graph[29][2]);
		printf("��      %s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s      ��\n", graph[0][1], graph[1][1], graph[2][1], graph[3][1], graph[4][1], graph[5][1], graph[6][1], graph[7][1], graph[8][1], graph[9][1], graph[10][1], graph[11][1], graph[12][1], graph[13][1], graph[14][1], graph[15][1], graph[16][1], graph[17][1], graph[18][1], graph[19][1], graph[20][1], graph[21][1], graph[22][1], graph[23][1], graph[24][1], graph[25][1], graph[26][1], graph[27][1], graph[28][1], graph[29][1]);
		printf("��      %s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s      ��\n", graph[0][0], graph[1][0], graph[2][0], graph[3][0], graph[4][0], graph[5][0], graph[6][0], graph[7][0], graph[8][0], graph[9][0], graph[10][0], graph[11][0], graph[12][0], graph[13][0], graph[14][0], graph[15][0], graph[16][0], graph[17][0], graph[18][0], graph[19][0], graph[20][0], graph[21][0], graph[22][0], graph[23][0], graph[24][0], graph[25][0], graph[26][0], graph[27][0], graph[28][0], graph[29][0]);//���� 30��.�Ϸ翡 ���پ�(����==1.5sec),250���� ��ĭ�� ä������
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                           �� �Ǹŷ�: %d                     ", total_selled);
		alignment(digiter(total_selled));
		printf("             ��\n");
		printf("��                                                                        ��\n");
		printf("���������������������������������������\n");
		selled_count *= selled_count_delta;
		selled_count -= negative_environment;
		daily_value[i] = selled_count;
		maxo = maxi(maxo, selled_count);

		


		Sleep(1500);
		total_selled += selled_count;
		if (selled_count < 0)
		{
			break;
		}
		
	}
	total_money += (total_selled / 100);
	money += (total_selled / 100);
	Sleep(4000);
	//Ű����:(�׷���;�ð� :(������:(delta�� ó��?),(�� ������)))
	//->��ȭ������ �����ϴ°�����. �׷����� �ֽĿ����� ������ �׷����� �𵨷� �Ѵ�.
	return 0;
}
int recruit()//���� ä���� ù ������ν� �ε��ϴ� ȭ�� ���� ������ 3���� worker_num�� �ҷ��´�.*������ ���� �ο��� 2�� �����϶��� ����ó���� �ȵǾ� ������, �̺κ��� if ������ ó���ϸ� �� �� �ϴ�
{
		char choosing[5][3] = { { "��" }, { "" }, { "" }, { "" } };
	int menu_num = 0;
	int recruit_chosen[3];
	int i, j;
	for (i = 0; i <= 5; i++)
	{

		system("cls");
		printf("���������������������������������������\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                        ȸ�縦 ȫ�����Դϴ�....\t                  ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("���������������������������������������\n");
		Sleep(100);
		system("cls");
		printf("���������������������������������������\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                        ȸ�縦 ȫ�����Դϴ�.   \t                  ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("���������������������������������������\n");
		Sleep(100);
		system("cls");
		printf("���������������������������������������\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                        ȸ�縦 ȫ�����Դϴ�..  \t                  ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("���������������������������������������\n");
		Sleep(100);
		system("cls");
		printf("���������������������������������������\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                        ȸ�縦 ȫ�����Դϴ�... \t                  ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("���������������������������������������\n");
		Sleep(100);
		system("cls");
		printf("���������������������������������������\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                        ȸ�縦 ȫ�����Դϴ�....\t                  ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("���������������������������������������\n");
		Sleep(100);
	}
	for (i = 0; i < 3; i++)
	{
		srand(time(NULL));
		recruit_chosen[i] = rand() % 12;
		for (j = i - 1; j >= 0; j--)
		{
			if (enabler[recruit_chosen[i]] == 0)
			{
				if (recruit_chosen[i] == recruit_chosen[j])//�ߺ�����ó������
				{
					i--;//�ߺ��Ǹ� �Դ�����
				}
			}
			else
			{
				i--;//�ش籸���� enabler�� 1�̸� �Դ�����...�൥ arr[]���Þ�����
			}
		}
	}
	for (i = 0; i <= 2; i++)
	{
		system("cls");
		printf("���������������������������������������\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                    ���������� ó�����Դϴ�....\t                  ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("���������������������������������������\n");
		Sleep(100);
		system("cls");
		printf("���������������������������������������\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                    ���������� ó�����Դϴ�.   \t                  ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("���������������������������������������\n");
		Sleep(100);
		system("cls");
		printf("���������������������������������������\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                    ���������� ó�����Դϴ�..  \t                  ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("���������������������������������������\n");
		Sleep(100);
		system("cls");
		printf("���������������������������������������\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                    ���������� ó�����Դϴ�... \t                  ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("���������������������������������������\n");
		Sleep(100);
		system("cls");
		printf("���������������������������������������\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                    ���������� ó�����Դϴ�....\t                  ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("���������������������������������������\n");
		Sleep(100);
	}

	while (1)
	{
		digiter(money);
		system("cls");
		printf("���������������������������������������\n");
		printf("��                                                                        ��\n");
		printf("��                   ������ ���� ������� �𿴽��ϴ�!                     ��\n");
		printf("��                        ������ ä���Ͻðڽ��ϱ�?                        ��\n");
		printf("��                                                                        ��\n");
		printf("�� ���� �ڻ�: %d                             ", money);
		alignment(digiter(money));
		printf("                               ��\n");
		printf("��                                                                        ��\n");
		printf("��                 %s                    ", system_message);
		alignment(strlen(system_message));
		printf("                                   ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("�� �̸�:      %s\t            %s\t\t    %s\t  ��\n", worker_name[recruit_chosen[0]], worker_name[recruit_chosen[1]], worker_name[recruit_chosen[2]]);
		printf("��                                                                        ��\n");
		printf("�� ���α׷���:    %d\t\t\t%d\t\t\t%d\t  ��\n", programming[recruit_chosen[0]], programming[recruit_chosen[1]], programming[recruit_chosen[2]]);
		printf("��                                                                        ��\n");
		printf("�� �׷���:        %d\t\t\t%d\t\t\t%d\t  ��\n", graphic[recruit_chosen[0]], graphic[recruit_chosen[1]], graphic[recruit_chosen[2]]);
		printf("��                                                                        ��\n");
		printf("�� ����:        %d\t\t\t%d\t\t\t%d\t  ��\n", sound[recruit_chosen[0]], sound[recruit_chosen[1]], sound[recruit_chosen[2]]);
		printf("��                                                                        ��\n");
		printf("�� ���:          %d\t\t\t%d\t\t\t%d\t  ��\n", recruit_cost[recruit_chosen[0]], recruit_cost[recruit_chosen[1]], recruit_cost[recruit_chosen[2]]);
		printf("��                                                                        ��\n");
		printf("��	   \t%s\t\t\t%s\t\t\t%s\t  ��\n", choosing[0], choosing[1], choosing[2]);
		printf("��                                                                        ��\n");
		printf("��                             %s���ư���     \t                          ��\n", choosing[3]);
		printf("���������������������������������������\n");
		key = getch();
		if (key == 224)
		{
			ex_key = getch();
			switch (ex_key)
			{
			case UP:
			{
				strcpy(choosing[menu_num], blank);
				menu_num = 1;
				strcpy(choosing[menu_num], upper);
				break;
			}
			case DOWN:
			{
				strcpy(choosing[menu_num], blank);
				menu_num = 3;
				strcpy(choosing[menu_num], selector);
				break;
			}
			case RIGHT:
			{
				strcpy(choosing[menu_num], blank);
				menu_num++;
				menu_num = menu_num % 4;
				if (menu_num<3)
				{
					strcpy(choosing[menu_num], upper);
				}
				else
				{
					strcpy(choosing[menu_num], selector);
				}
				break;
			}
			case LEFT:
			{
				strcpy(choosing[menu_num], blank);
				menu_num--;
				if (menu_num == -1)
				{
					menu_num += 4;
				}
				menu_num = menu_num % 4;
				if (menu_num<3)
				{
					strcpy(choosing[menu_num], upper);
				}
				else
				{
					strcpy(choosing[menu_num], selector);
				}
				break;
			}
			default:
				break;
			}
		}
		else if (key == 0xd)
		{
			if (menu_num<3)
			{
				if (money<recruit_cost[recruit_chosen[menu_num]])
				{
					strcpy(system_message, err_not_enough_money);
				}
				else
				{
					money -= recruit_cost[recruit_chosen[menu_num]];
					recruited(recruit_chosen[menu_num]);
					break;
				}
			}
			else
			{
				strcpy(system_message, system_message_init);
				break;
			}
		}
	}
	return 0;
}
void recruited(int called_num)// ���� ������ �ִϸ��̼��� ����ϴ� �Լ�.
{
	int i = 0;
	while (i<10)
	{
		system("cls");
		printf("���������������������������������������\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                         '     '     '                                  ��\n");
		printf("��                    '                     '                             ��\n");
		printf("��                                             '                          ��\n");
		printf("��                .                                                       ��\n");
		printf("��                   %s��(��) ä��Ǿ����ϴ�!.                      ��\n", worker_name[called_num]);
		printf("��                .                                                       ��\n");
		printf("��                                               .                        ��\n");
		printf("��	             .  \"%s\"                            ��\n", upgrade_message[called_num]);
		printf("��                                             .                          ��\n");
		printf("��                       .     .       .    .                             ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("���������������������������������������\n");
		Sleep(100);
		system("cls");
		printf("���������������������������������������\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                         .     .     .                                  ��\n");
		printf("��                    .                     .                             ��\n");
		printf("��                                             .                          ��\n");
		printf("��                '                                                       ��\n");
		printf("��                   %s��(��) ä��Ǿ����ϴ�!'                      ��\n", worker_name[called_num]);
		printf("��                '                                                       ��\n");
		printf("��                                               '                        ��\n");
		printf("��	             '  \"%s\"                            ��\n", upgrade_message[called_num]);
		printf("��                                             '                          ��\n");
		printf("��                       '     '       '    '                             ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("���������������������������������������\n");
		Sleep(100);
		i++;
	}
	enabler[called_num] = 1;
	worker_count++;
	able_cruit_num--;
}
void cruit_upgrade_select()//������ ������ �����ϴ� â.
{
	int upgrade_confirmed=0;
	int what_num_you_choosed = -1;
	int taken[13] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };//������� '��������' ������ ��ȣ(worker_num�� ����.).//�Ʒ��� �ݺ����� ������ ���� ������ �ִ� �������� '��ȣ'��.
	char selected[16][3] = { "->", "\0", "\0", "\0", "\0", "\0", "\0", "\0", "\0", "\0", "\0", "\0", "\0", "\0", "\0", "\0" };//ȭ��ǥ �׷����� ���� 
	int i, j;
	int menu_num = 0;//�޴� �̵��� �ʿ��� ����
	int able_to_work = 0;//���� ä�� ����� ä������� ���� ����. �Ʒ��� ������ ������ �Ƹ� �� �����ο��ϰ��̴�.
	
	for (i = 0; i < 13; i++)
	{
		if (enabler[i] == 1)
		{
			strcpy(list_of_cruit[able_to_work], worker_name[i]);
			taken[able_to_work] = worker_num[i];
			your_upgrade_cost[able_to_work] = upgrading_cost[i];
			able_to_work++;
		}
		else
		{

		}
	}

	while (1)
	{
		system("cls");
		printf("���������������������������������������\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��  <SYSTEM>  %s                              ", system_message);
		alignment(strlen(system_message));
		printf("                              ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                      ������ų ������ �������ּ���                      ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��     %s%s  \t%s%s  \t%s%s  \t%s%s  \t  ��\n", selected[0], list_of_cruit[0], selected[1], list_of_cruit[1],  selected[2], list_of_cruit[2],  selected[3], list_of_cruit[3] );
		printf("��     ���:%d\t         %d\t           %d\t            %d\t          ��\n", upgrading_cost[taken[0]], upgrading_cost[taken[1]], upgrading_cost[taken[2]], upgrading_cost[taken[3]]);
		printf("��     %s%s  \t%s%s  \t%s%s  \t%s%s  \t  ��\n", selected[4], list_of_cruit[4], selected[5], list_of_cruit[5], selected[6], list_of_cruit[6], selected[7], list_of_cruit[7] );
		printf("��     ���:%d\t         %d\t           %d\t            %d\t          ��\n", upgrading_cost[taken[4]], upgrading_cost[taken[5]], upgrading_cost[taken[6]], upgrading_cost[taken[7]]);
		printf("��     %s%s  \t%s%s  \t%s%s  \t%s%s  \t  ��\n", selected[8], list_of_cruit[8], selected[9], list_of_cruit[9], selected[10], list_of_cruit[10],  selected[11], list_of_cruit[11]);
		printf("��     ���:%d\t         %d\t           %d\t            %d\t          ��\n", upgrading_cost[taken[8]], upgrading_cost[taken[9]], upgrading_cost[taken[10]], upgrading_cost[taken[11]]);
		printf("��                                                                        ��\n");
		printf("��      %s �ڷ�\t                                                          ��\n", selected[12]);
		printf("��                                                                        ��\n");
		printf("���������������������������������������\n");

		key = getch();
		if (key == 224)
		{
			ex_key = getch();
			switch (ex_key)
			{
			case UP:
			{
				strcpy(selected[menu_num], blank);
				if ((menu_num<12)  || (menu_num == 12))
				{
					do
					{
						menu_num -= 4;
						if (menu_num<0)
						{
							menu_num += 13;
							if (menu_num == 13)
							{
								menu_num = 9;
							}
							else if (menu_num == 14)
							{
								menu_num = 10;
							}
						}
					} while (enabler[taken[menu_num]] == 0);
				}
				else
				{
					if (menu_num == 13)
					{
						menu_num = 1;
					}
					else if (menu_num == 14)
					{
						menu_num = 2;
					}
				}
				strcpy(selected[menu_num], selector);
				break;

			}
			case DOWN:
			{
				strcpy(selected[menu_num], blank);
				if ((menu_num<12) || (menu_num == 12))
				{
					do
					{
						menu_num += 4;
						if (menu_num == 15)
							menu_num = 3;
						else if (menu_num == 16)
							menu_num = 0;
						if (menu_num == 13)
						{
							menu_num = 1;
						}
						else if (menu_num == 14)
						{
							menu_num = 2;
						}
					} while (enabler[taken[menu_num]] == 0);
				}
				else
				{

				}
				strcpy(selected[menu_num], selector);
				break;
			}
			case RIGHT:
			{
				strcpy(selected[menu_num], blank);
				if ((menu_num<12) ||  (menu_num == 12))
				{
					do
					{
						menu_num++;
						menu_num = menu_num % 13;
						if (menu_num == 13)
						{
							menu_num = 0;
						}
					} while (enabler[taken[menu_num]] == 0);
				}
				else
				{

				}
				strcpy(selected[menu_num], selector);
				break;
			}
			case LEFT:
			{
				strcpy(selected[menu_num], blank);
				if ((menu_num<12) || (menu_num == 12))
				{
					do
					{
						menu_num--;
						menu_num = menu_num % 13;
						if (menu_num == -1)
						{
							menu_num += 13;
						}
					} while (enabler[taken[menu_num]] == 0);
				}
				strcpy(selected[menu_num], selector);
				break;
			}
			default:
				break;
			}
		}
		else if (key == 0xd)
		{
			if (menu_num<12)
			{
				if ((money - upgrading_cost[menu_num]) >= 0)
				{
					strcpy(system_message, system_message_init);//�ý��۸޼��� �ʱ�ȭ
					upgrade_confirmed = 1;
					what_num_you_choosed = taken[menu_num];
					break;
				}
				else
				{
					strcpy(system_message, err_not_enough_money);//
					continue;
				}
				
			}
			else if (menu_num == 12)
			{
				strcpy(system_message, system_message_init);
				break;
			}
		}
	
	}
	if (upgrade_confirmed==1)
	{
		cruit_upgrade_confirm(what_num_you_choosed);
	}
}

void cruit_upgrade_confirm(int what_num_you_choosed)
{
	int pg_temp = programming[what_num_you_choosed];
	int gp_temp = graphic[what_num_you_choosed];
	int sd_temp = sound[what_num_you_choosed];
	int unlucky;
	int i = 0;
	srand(time(NULL));
	unlucky = (rand() % 100)+1;
	money -= upgrading_cost[what_num_you_choosed];
	if (unlucky<10)
	{
		while (i<10)
		{
			system("cls");
			printf("���������������������������������������\n");
			printf("��                                                                        ��\n");
			printf("��                                                                        ��\n");
			printf("��                                                                        ��\n");
			printf("��                                                                        ��\n");
			printf("��                                                                        ��\n");
			printf("��                                                                        ��\n");
			printf("��                                                                        ��\n");
			printf("��                                                                        ��\n");
			printf("��                                                                        ��\n");
			printf("��                                                                        ��\n");
			printf("��                   %s�� ������ �����߽��ϴ�!...                   ��\n", worker_name[what_num_you_choosed]);
			printf("��                                                                        ��\n");
			printf("��                                                                        ��\n");
			printf("��	                                                                      ��\n");
			printf("��                                                                        ��\n");
			printf("��                                                                        ��\n");
			printf("��                                                                        ��\n");
			printf("��                                                                        ��\n");
			printf("��                                                                        ��\n");
			printf("��                                                                        ��\n");
			printf("��                                                                        ��\n");
			printf("��                                                                        ��\n");
			printf("���������������������������������������\n");
			Sleep(200);
			i++;
		}
	}
	else
	{
		programming[what_num_you_choosed] += (programming_upgrade_delta[what_num_you_choosed] + status_upgrade_random_width());
		graphic[what_num_you_choosed] += (graphic_upgrade_delta[what_num_you_choosed] + status_upgrade_random_width());
		sound[what_num_you_choosed] += (sound_upgrade_delta[what_num_you_choosed] + status_upgrade_random_width());
		payment[what_num_you_choosed] *= payment_delta_per_upgrade[what_num_you_choosed];
		while (i<10)
		{
			system("cls");
			printf("���������������������������������������\n");
			printf("��                                                                        ��\n");
			printf("��                                                                        ��\n");
			printf("��                                                                        ��\n");
			printf("��                                                                        ��\n");
			printf("��                                                                        ��\n");
			printf("��                              .     .                                   ��\n");
			printf("��                        '                .                              ��\n");
			printf("��                     '                                                  ��\n");
			printf("��                  .                            .                        ��\n");
			printf("��                     %s��(��) �����߽��ϴ�!  '                    ��\n", worker_name[what_num_you_choosed]);
			printf("��                                                                        ��\n");
			printf("��                  .                              .                      ��\n");
			printf("��	                  \"%s\"                          ��\n", upgrade_message[what_num_you_choosed]);
			printf("��                     .                       .                          ��\n");
			printf("��                           .      .      .                              ��\n");
			printf("��                                                                        ��\n");
			printf("��          ���α׷���:   %d        ->        %d            ", pg_temp, programming[what_num_you_choosed]);
			alignment(digiter(pg_temp) + digiter(programming[what_num_you_choosed]));
			printf("                  ��\n");
			printf("��                                                                        ��\n");
			printf("��              �׷���:   %d        ->        %d            ", gp_temp, graphic[what_num_you_choosed]);
			alignment(digiter(gp_temp)+digiter(graphic[what_num_you_choosed]));
			printf("                  ��\n");
			printf("��                                                                        ��\n");
			printf("��              ����:   %d        ->        %d            ", sd_temp, sound[what_num_you_choosed]);
			alignment(digiter(sd_temp)+digiter(sound[what_num_you_choosed]));
			printf("                  ��\n");
			printf("��                                                                        ��\n");
			printf("���������������������������������������\n");
			Sleep(300);
			;
			i++;
		}
		
	}
	
}

void pausing()//�޴�4���� ��Ƽ��Ƽ.
{
	int i;
	int pause_start=(clock()/CLOCKS_PER_SEC);
	int pause_end;
	
	while (1)
	{
		system("cls");
		printf("���������������������������������������\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                   - �� * �� * �� * �� * �� * �� -                      ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                      �ƹ� Ű�� ���� �����մϴ�                         ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("���������������������������������������\n");
		Sleep(100);
		key = getch();
		if (key > 0)
			break;
	}
	loading();
	pause_end = clock() / CLOCKS_PER_SEC;
	paused_time += (pause_end - pause_start);
}

void main()//���θ޴� ���.
{
	system("pause");
	int is_not_count, i, menu_num = 1, j, toy_num,year_temp,month_temp;
	slide_down_animation();
	start();
	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                     ����� ȸ���� �̸��� �����ּ���:                   ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	gets(company_name);
	fflush(stdin);
	system("pause");
	loading();
	is_not_count = clock() / CLOCKS_PER_SEC;
	//�Ʒ��� ����������
	while (10800 > ((clock() / CLOCKS_PER_SEC) - (is_not_count+paused_time)))//��ȹ������ 10��¥�� �����̾�����, �÷��̽ð� �� 3�ð����� ����.
	{
		
		system("cls");
		year = ((clock() / CLOCKS_PER_SEC) - (is_not_count + paused_time)) / 540;
		month = ((((clock() / CLOCKS_PER_SEC) - (is_not_count + paused_time) % 540) / 45)%12)+1;
		printf("���������������������������������������\n");
		printf("�� ȸ���: %s                               ", company_name);
		alignment(strlen(company_name));
		printf("                                ��\n");
		printf("�� �߰� ä�� ���� �ο�: %d                                                  ", able_cruit_num);
		alignment(digiter(able_cruit_num));
		printf("��\n");
		printf("�� ȸ�� ����: %d          ", company_lv);
		alignment(digiter(company_lv));
		printf("                                                  ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("��                                          ���ӡ�                        ��\n");
		printf("��                                         (������7                       ��\n");
		printf("��                                          ��    ~                       ��\n");
		printf("��                                           l��   ��                     ��\n");
		printf("��                                           ����f_,)��                   ��\n");
		printf("�� <SYSTEM>                                                               ��\n");
		printf("�� %s                                       ", system_message);alignment(strlen(system_message));printf("                                ��\n");
		printf("��                                                                        ��\n");
		printf("��                                                                        ��\n");
		printf("���������������������������������������\n");
		//}
		if (menu_num == 1)
		{
			printf("��                                    �� 1. ���� ����   �� 2. ���� ä��   ��\n");
			printf("��   ȸ�� �ں�:%d              ", money);
			alignment(digiter(money));
			printf("         ��****************��                ��\n");
			printf("��   ���� ��:  %d      ", worker_count);
			alignment(digiter(worker_count));
			printf("                 ��������������������\n");
			printf("��   � ����:%d��     %d����       ", year, month);
			alignment(digiter(year) + digiter(month));
			printf("     �� 3. ���� ����   �� 4. �Ͻ� ����   ��\n", year);
			printf("��                                    ��                ��                ��\n");
		}
		else if (menu_num == 2)
		{
			printf("��                                    �� 1. ���� ����   �� 2. ���� ä��   ��\n");
			printf("��   ȸ�� �ں�:%d              ", money);
			alignment(digiter(money));
			printf("         ��                ��****************��\n");
			printf("��   ���� ��:  %d      ", worker_count);
			alignment(digiter(worker_count));
			printf("                 ��������������������\n");
			printf("��   � ����:%d��     %d����       ", year, month);
			alignment(digiter(year) + digiter(month));
			printf("     �� 3. ���� ����   �� 4. �Ͻ� ����   ��\n", year);
			printf("��                                    ��                ��                ��\n");
		}
		else if (menu_num == 3)
		{
			printf("��                                    �� 1. ���� ����   �� 2. ���� ä��   ��\n");
			printf("��   ȸ�� �ں�:%d              ", money);
			alignment(digiter(money));
			printf("         ��                ��                ��\n");
			printf("��   ���� ��:  %d      ", worker_count);
			alignment(digiter(worker_count));
			printf("                 ��������������������\n");
			printf("��   � ����:%d��     %d����       ", year, month);
			alignment(digiter(year) + digiter(month));
			printf("     �� 3. ���� ����   �� 4. �Ͻ� ����   ��\n", year);
			printf("��                                    ��****************��                ��\n");
		}
		else if (menu_num == 0)
		{
			printf("��                                    �� 1. ���� ����   �� 2. ���� ä��   ��\n");
			printf("��   ȸ�� �ں�:%d              ", money);
			alignment(digiter(money));
			printf("         ��                ��                ��\n");
			printf("��   ���� ��:  %d      ", worker_count);
			alignment(digiter(worker_count));
			printf("                 ��������������������\n");
			printf("��   � ����:%d��     %d����       ", year, month);
			alignment(digiter(year) + digiter(month));
			printf("     �� 3. ���� ����   �� 4. �Ͻ� ����   ��\n", year);
			printf("��                                    ��                ��****************��\n");
		}
		printf("���������������������������������������\n");

		key = getch();
		if (key == 224)
		{
			ex_key = getch();
			switch (ex_key)
			{
			case UP:
			{
				//strcpy(system_message, system_message_init);
				menu_num -= 2;
				if (menu_num<0)
				{
					if (menu_num==-1)
					{
						menu_num = 3;
					}
					if (menu_num==-2)
					{
						menu_num = 2;
					}
				}
				menu_num = menu_num % 4;
				break;
			}
			case DOWN:
			{
				//strcpy(system_message, system_message_init);
				menu_num += 2;
				menu_num = menu_num % 4;
				break;
			}
			case RIGHT:
			{
				//strcpy(system_message, system_message_init);
				menu_num++;
				menu_num = menu_num % 4;
				break;
			}
			case LEFT:
			{
				//strcpy(system_message, system_message_init);
				if (menu_num == 0)
				{
					menu_num = 3;
				}
				else if (menu_num == 3)
				{
					menu_num = 2;
				}
				else if (menu_num == 2)
				{
					menu_num = 1;
				}
				else if (menu_num == 1)
				{
					menu_num = 0;
				}
				break;
			}
			default:
				break;
			}
		}
		else if (key == ENTER)
		{
			if (menu_num == 1)
			{
				loading();
				game_dev_pj_naming();
			}
			else if (menu_num == 2)
			{
				if (able_cruit_num == 0)
				{
					strcpy(system_message, err_not_enough_hire);
				}
				else
				{
					loading();
					recruit();
				}
			}
			else if (menu_num == 3)
			{
				loading();
				cruit_upgrade_select();
			}
			else if (menu_num==0)
			{
				pausing();
			}
			
		}
		strcpy(system_message, system_message_init);
		payday(year,month);
		leveling();
		
	}
	game_end_phase();
}


void payday(int year,int month)
{
	
	int i,j;
	int total_paying=0;
	if ((pay_chked[year])<1)
	{
		strcpy(system_message, alert_payment_served);
			for (j = 0; j < 12; j++)
			{
				if (enabler[j] == 1)
				{
					total_paying += payment[j];
					for (i = 0; i < 12; i++)//���¹̳� ���� üũ initialize
					{
						stamina_regen_chk[i] = 0;
					}
				}
			}
	}
	else
	{
	}
	//�Ʒ��� ���¹̳� ����
	for (i = 0; i < month; i++)//��
	{
		if (stamina_regen_chk[i]<1)
		{
			for (j = 0; j <12; i++)
			{
				if (enabler[j]==1)
				{
					stamina[j] += stamina_regen_delta_per_min_const[j];
				}
			}
			stamina_regen_chk[i] = 1;
		}
	}
	



	pay_chked[year] = 1;
	money -= total_paying;
}

void game_end_phase()
{
	system("cls");
	printf("���������������������������������������\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                   ������ �÷������ּż� �����մϴ�.                    ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                      �� ���� ��: %d                  ",worker_count);
	alignment(digiter(worker_count));
	printf("                    ��\n");
	printf("��                                                                        ��\n");
	printf("��                         �� �ڻ�: %d                  ",total_money);
	alignment(digiter(total_money));
	printf("                  ��\n");
	printf("��                                                                        ��\n");
	printf("��              �� ������ ������Ʈ: %d                  ", game_name_log_count+1);
	alignment(digiter(game_name_log_count + 1));
	printf("                  ��\n");
	printf("��                                                                        ��\n");
	printf("��                                                                        ��\n");
	printf("��                            �� ����: %d                  ",(worker_count*100)+(money*10)+((game_name_log_count+1)*150));
	alignment((digiter((worker_count * 100) + (money * 10) + ((game_name_log_count + 1) * 150))));
	printf("                               ��\n");
	printf("��                                                                        ��\n");
	printf("���������������������������������������\n");
	Sleep(3000);
}
void leveling()
{
	int i, j;
	int temp=company_lv;
	int temp_2;
	for (i =0; i <12; i++)
	{
		if ((total_money>company_level_requirement[i]) || (total_money<company_level_requirement[i+1]))
		{
			temp_2 = i;
			break;
		}
	}
	if (temp!=temp_2)
	{
		strcpy(system_message, alert_company_lv_up);
		able_cruit_num++;
	}


}
void intro_animation()
{

}