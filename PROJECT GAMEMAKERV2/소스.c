
#define _CRT_SECURE_NO_WARNINGS//<- scanf_s 안쓰기 위해 전처리기에 씀
//+++++++++++++++++++++++++++++++++++++++++
//키값
#define BSP 0x8
#define ENTER 0xd
#define ESC 0x1b
#define UP 0x48
#define DOWN 0x50
#define LEFT 0x4b
#define RIGHT 0x4d
//*****************************************
//헤더
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<conio.h>
//↓getch()를 사용하기 위해!
#if defined(_MSC_VER)
#ifndef _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_DEPRECATE (1)
#endif
#pragma warning(disable : 4996)
#endif
//******************************************
//함수선언
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
//전역변수
int stamina_regen_chk[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };//매월 체력재생 체크
int pay_chked[21] = { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };//매년 연봉체크
int total_money=300;
int company_lv = 1; 
int paused_time=0;
int game_name_log_count = -1;//아래 변수의 위치를 제어하는 변수
char game_name_log[100][80] = { "\0" };//모든 게임의 이름을 저장
int able_cruit_num = 1;//menu에서 고용가능인원 
char blank[3] = ("\0");//화살표 이동시 이전위치에 채움
char company_name[80];//회사이름 입력받는곳
int ex_key;//추가키 인식용
unsigned char key = 0;//추가키 구별 및 엔터 입력용
int money = 300;//회사의 자본
char upper[3] = ("↑");//직원 고용메뉴에서 출력되는 화살표
char selector[3] = ("->");//직원 선택시 출력되는 화살표
char system_message[30] = { "                    " };//경고나 툴팁을 설명하는 문자열
char system_message_init[30] = { "                    " };//위 변수 초기화
int this_is_random_number_for_stats;//교육시 스택의 +-a를 결정할 변수
int worker_count = 1;//회사의 직원수
int year;//운영 기간
int month;
//******************************************
//에러모음
char err_not_choosed[40] = { "적어도 한명 이상 선택하십시오" };
char err_not_enough_money[40] = { "잔액이 부족합니다" };
char err_not_enough_hire[40] = { "더이상 고용할 수 없습니다" };
char err_not_enough_stamina[40] = { "체력이 부족합니다." };
char err_selected_again[40] = { "중복된 선택입니다" };
//******************************************
//시스템 메세지
char alert_tooltip_arrow_and_enter[40] = { "조작은 방향키와 엔터" };
char alert_payment_served[40] = { "직원들에게 급여가 지급되었습니다" };
char alert_company_lv_up[40] = { "회사의 레벨이 상승하였습니다!" };
//******************************************
//직원db
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
//업그레이드 방식은 status+=(upgrade_delta+randomwidth)
int upgrade_count[13];
*/
//******************************************

int worker_num[13] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
int enabler[13] = { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
char worker_name[13][9] = { { " 고래밥 " }, { " 폰팔이 " }, { "코카콜라" }, { "삼각김밥" }, { " 아옳옳 " }, { "직장인A " }, { " 마슬랜 " }, { " 삼성맨 " }, { "그림쟁이" }, { "파워코더" }, { " 홍진호 " }, { "에퀴녹스" } };
//status
int programming[13] = { 35, 10, 45, 60, 8, 76, 1, 90, 1, 150, 2, 50 };
int graphic[13] = { 20, 60, 1, 25, 8, 82, 1, 80, 100, 1, 2, 50 };
int sound[13] = { 40, 100, 80, 30, 8, 46, 1, 70, 25, 1, 2, 50 };

int stamina[13] = { 100, 100, 100, 100, 5, 100, 100, 100, 100, 100, 100, 100 };
int upgrading_cost[13] = { 50, 50, 100, 150, 100, 200, 10, 500, 100, 100, 2, 250 };
int recruit_cost[13] = { 100, 300, 500, 700, 900, 1600, 1500, 1000, 150, 100, 2, 500 };
int payment[13] = { 100, 150, 500, 350, 450, 400, 1000, 1500, 150, 100, 2, 500 };
char upgrade_message[13][21] = { { "   고래고래고래밥?  " }, { "베가좋아요베가사세요" }, { "펩시는 마시는거 아냐" }, { "편의점에서 단돈700원" }, { "아옳옳옳옳옳옳옳옳옳" }, { "오늘도 내일도 야근.." }, { "  피탕탕 피탕피탕?  " }, { "공밀레공밀레공밀레? " }, { " 그림실력이 올랐다! " }, { " 오늘도 밤새서 코딩!" }, { "      콩콩콩콩      " }, { "빙글빙글빙글빙글빙글" } };
//status_upgrade_delta
int programming_upgrade_delta[13] = { 3, 1, 3, 0, 4, 1, 4, 8, 1, 10, 2, 15 };
int graphic_upgrade_delta[13] = { 3, 4, 3, 0, 4, 1, 5, 8, 10, 1, 2, 15 };
int sound_upgrade_delta[13] = { 3, 5, 3, 0, 7, 1, 3, 8, 5, 1, 2, 15 };

int stamina_minus_delta[13] = { 15, 10, 18, 8, 15, 40, 10, 30, 19, 25, 2, 50 };
int stamina_regen_delta_per_min_const[13] = { 5, 3, 7, 6, 9, 8, 10, 15, 9, 9, 2, 15 };//이건 도대체 뭘까???리젠율??
double payment_delta_per_upgrade[13] = { 1.05, 1.05, 1.01,  1.1,  1.15,  1.15, 1.01,1.3,1.3,1};//월급 인상은 %로 합니다.ㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋ물론 정수로 짜르지마는..*즉 홍진호의 월급은 항상 2입니다
//status_upgrade_count
//업그레이드 방식은 status+=(upgrade_delta+randomwidth)
int upgrade_count[13] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };//카운트는 필요없지 않을까? 
int company_level_requirement[12] = { 1000, 5000, 10000, 20000, 40000, 80000, 160000,320000,640000,1280000,2560000,5120000 };
//******************************************
//******************************************
//******************************************
//******************************************
//너만의 리스트
int your_taked_worker_num[13] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };//taken[13]이 전역변수로 갈 경우 pj_cruit에서 if(key==0xd) 이후case:DOWN 에서 발생하는 오류를 처리하기 위해 taken과 똑같은 배열을 사용한다. 이 your_taked_worker_num[13]은 어로지 printf의 참조에 쓰인다
int your_taked_worker_num_count = 0;
char list_of_cruit[13][9] = { "        ", "        ", "        ", "        ", "        ", "        ", "        ", "        ", "        ", "        ", "        ", "        " };//너만의 직원리스트.이걸 난 왜 넣었을까???걍 worker_name[taken[recruited_num]]으로 처리할 수 있지 않았을까?
int your_stamina[13] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };//자신이 가진 직원들의 스태미나.이걸 난 왜 넣었을까???걍 stamina[taken[recruited_num]]으로 처리할 수 있지 않았을까?
int your_upgrade_cost[13] = { 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00 };
//******************************************
void your_db_refresher()
{
	//데이터베이스 동기화.
	//이 부분은 바로 윗 항목인 '너만의 리스트'를 db와 동기화시키기 위해 만들었으나 추후에 전역변수로 설정해버림으로써 무의미한 함수가 되었다.
}
//******************************************
int digiter(int a)//정수의 자리수를 계산하는 함수. 주로 \b 의 출력에 쓰임
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
void alignment(int a)//digiter를 이용하지 않음\b출력함수
{
	int i;
	for (i = 0; i < a; i++)
	{
		printf("\b");
	}
}
int arr_counter(int* input, int limits_end, int limits_down)//정수형 변수(int * input)배열의 끝(limits_end) 까지 일정 값(limits_down) 이상의 값을 세는 함수.
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

void slide_up_animation()//화면이 위로 올라가는 듯한 애니메이션. 여기서 배운 점은 sleep()과 system("cls")로 화면을 갱신하는데엔 최소딜레이가 존재한단 것이다. 
{
	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■			                                                              ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(10);
	system("cls");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■			                                                              ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(10);
	system("cls");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■			                                                              ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(10);
	system("cls");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■			                                                              ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(10);
	system("cls");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■			                                                              ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(10);
	system("cls");
	printf("■                                                                        ■\n");
	printf("■			                                                              ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(10);
	system("cls");
	printf("■			                                                              ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(10);
	system("cls");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(10);
	system("cls");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(10);
	system("cls");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(10);
	system("cls");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(10);
	system("cls");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(10);
	system("cls");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(10);
	system("cls");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(10);
	system("cls");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(10);
	system("cls");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(10);
	system("cls");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(10);
	system("cls");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(10);
	system("cls");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(10);
	system("cls");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(10);
	system("cls");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(10);
	system("cls");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(10);
	system("cls");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(10);
	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(10);

}
void slide_down_animation()
{
	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(10);
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(10);
	system("cls");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(10);
	system("cls");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(10);
	system("cls");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(10);
	system("cls");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(10);
	system("cls");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(10);
	system("cls");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(10);
	system("cls");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(10);
	system("cls");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(10);
	system("cls");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(10);
	system("cls");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(10);
	system("cls");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(10);
	system("cls");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(10);
	system("cls");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(10);
	system("cls");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(10);
	system("cls");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(10);
	system("cls");
	printf("■			                                                              ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(10);
	//17
	//22
	system("cls");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■			                                                              ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(10);
	system("cls");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■			                                                              ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(10);
}

void loading()//화면에서 문자가 빙글빙글 돌면서 로딩이 되는 듯한 애니메이션.
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
void start()//인트로. 글자가 하나씩 쓰여지는 듯한 애니메이션
{
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                                                         ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                                                         ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                                                         ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |  __                                                         ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                                                         ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |  __                                                         ■\n");
	printf("■        | | |_ |                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                                                         ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |  __                                                         ■\n");
	printf("■        | | |_ |                                                        ■\n");
	printf("■        | |__| |                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                                                         ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |  __                                                         ■\n");
	printf("■        | | |_ |                                                        ■\n");
	printf("■        | |__| |                                                        ■\n");
	printf("■         #_____|                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                                                         ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |  __                                                         ■\n");
	printf("■        | | |_ |/                                                       ■\n");
	printf("■        | |__| |                                                        ■\n");
	printf("■         #_____|#                                                       ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                                                         ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |  __  _                                                      ■\n");
	printf("■        | | |_ |/                                                       ■\n");
	printf("■        | |__| | (                                                      ■\n");
	printf("■         #_____|#_                                                      ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                                                         ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |  __  __                                                     ■\n");
	printf("■        | | |_ |/ _                                                     ■\n");
	printf("■        | |__| | (_                                                     ■\n");
	printf("■         #_____|#__                                                     ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                                                         ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |  __  __                                                     ■\n");
	printf("■        | | |_ |/ _`                                                    ■\n");
	printf("■        | |__| | (_|                                                    ■\n");
	printf("■         #_____|#__,                                                    ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                                                         ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |  __  __ _                                                   ■\n");
	printf("■        | | |_ |/ _`                                                    ■\n");
	printf("■        | |__| | (_|                                                    ■\n");
	printf("■         #_____|#__,_                                                   ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                                                         ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |  __  __ _                                                   ■\n");
	printf("■        | | |_ |/ _` |                                                  ■\n");
	printf("■        | |__| | (_| |                                                  ■\n");
	printf("■         #_____|#__,_|                                                  ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                                                         ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |  __  __ _                                                   ■\n");
	printf("■        | | |_ |/ _` |                                                  ■\n");
	printf("■        | |__| | (_| |                                                  ■\n");
	printf("■         #_____|#__,_|_| |_| |_|                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                                                         ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |  __  __ _                                                   ■\n");
	printf("■        | | |_ |/ _` |                                                  ■\n");
	printf("■        | |__| | (_| | | | | | |                                        ■\n");
	printf("■         #_____|#__,_|_| |_| |_|                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                                                         ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |  __  __ _                                                   ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ #                                         ■\n");
	printf("■        | |__| | (_| | | | | | |                                        ■\n");
	printf("■         #_____|#__,_|_| |_| |_|                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                                                         ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |  __  __ _ _ __ ___                                          ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ #                                         ■\n");
	printf("■        | |__| | (_| | | | | | |                                        ■\n");
	printf("■         #_____|#__,_|_| |_| |_|                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                 ____                                    ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |  __  __ _ _ __ ___                                          ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ #                                         ■\n");
	printf("■        | |__| | (_| | | | | | |                                        ■\n");
	printf("■         #_____|#__,_|_| |_| |_|                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                 ____                                    ■\n");
	printf("■         / ____|               |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___                                          ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ #                                         ■\n");
	printf("■        | |__| | (_| | | | | | |                                        ■\n");
	printf("■         #_____|#__,_|_| |_| |_|                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                 ____                                    ■\n");
	printf("■         / ____|               |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ #                                         ■\n");
	printf("■        | |__| | (_| | | | | | |                                        ■\n");
	printf("■         #_____|#__,_|_| |_| |_|                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                 ____                                    ■\n");
	printf("■         / ____|               |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ # |__ <                                   ■\n");
	printf("■        | |__| | (_| | | | | | |                                        ■\n");
	printf("■         #_____|#__,_|_| |_| |_|                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                 ____                                    ■\n");
	printf("■         / ____|               |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ # |__ <                                   ■\n");
	printf("■        | |__| | (_| | | | | | |___) |                                  ■\n");
	printf("■         #_____|#__,_|_| |_| |_|                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                 ____                                    ■\n");
	printf("■         / ____|               |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ # |__ <                                   ■\n");
	printf("■        | |__| | (_| | | | | | |___) |                                  ■\n");
	printf("■         #_____|#__,_|_| |_| |_|____/                                   ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                 ____                                    ■\n");
	printf("■         / ____|               |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ # |__ <                                   ■\n");
	printf("■        | |__| | (_| | | | | | |___) |                                  ■\n");
	printf("■         #_____|#__,_|_| |_| |_|____/                                   ■\n");
	printf("■                                                                        ■\n");
	printf("■        |                                                               ■\n");
	printf("■        |                                                               ■\n");
	printf("■        |                                                               ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                 ____                                    ■\n");
	printf("■         / ____|               |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ # |__ <                                   ■\n");
	printf("■        | |__| | (_| | | | | | |___) |                                  ■\n");
	printf("■         #_____|#__,_|_| |_| |_|____/                                   ■\n");
	printf("■         /                                                              ■\n");
	printf("■        |                                                               ■\n");
	printf("■        |                                                               ■\n");
	printf("■        |                                                               ■\n");
	printf("■         #                                                              ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                 ____                                    ■\n");
	printf("■         / ____|               |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ # |__ <                                   ■\n");
	printf("■        | |__| | (_| | | | | | |___) |                                  ■\n");
	printf("■         #_____|#__,_|_| |_| |_|____/                                   ■\n");
	printf("■         /                                                              ■\n");
	printf("■        | |                                                             ■\n");
	printf("■        | |                                                             ■\n");
	printf("■        | |                                                             ■\n");
	printf("■         #_                                                             ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                 ____                                    ■\n");
	printf("■         / ____|               |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ # |__ <                                   ■\n");
	printf("■        | |__| | (_| | | | | | |___) |                                  ■\n");
	printf("■         #_____|#__,_|_| |_| |_|____/                                   ■\n");
	printf("■         / _                                                            ■\n");
	printf("■        | |                                                             ■\n");
	printf("■        | |                                                             ■\n");
	printf("■        | |_                                                            ■\n");
	printf("■         #__                                                            ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                 ____                                    ■\n");
	printf("■         / ____|               |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ # |__ <                                   ■\n");
	printf("■        | |__| | (_| | | | | | |___) |                                  ■\n");
	printf("■         #_____|#__,_|_| |_| |_|____/                                   ■\n");
	printf("■         / __                                                           ■\n");
	printf("■        | |                                                             ■\n");
	printf("■        | |                                                             ■\n");
	printf("■        | |__                                                           ■\n");
	printf("■         #___                                                           ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                 ____                                    ■\n");
	printf("■         / ____|               |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ # |__ <                                   ■\n");
	printf("■        | |__| | (_| | | | | | |___) |                                  ■\n");
	printf("■         #_____|#__,_|_| |_| |_|____/                                   ■\n");
	printf("■         / ___                                                          ■\n");
	printf("■        | |                                                             ■\n");
	printf("■        | |                                                             ■\n");
	printf("■        | |___                                                          ■\n");
	printf("■         #____                                                          ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                 ____                                    ■\n");
	printf("■         / ____|               |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ # |__ <                                   ■\n");
	printf("■        | |__| | (_| | | | | | |___) |                                  ■\n");
	printf("■         #_____|#__,_|_| |_| |_|____/                                   ■\n");
	printf("■         / ____                                                         ■\n");
	printf("■        | |                                                             ■\n");
	printf("■        | |                                                             ■\n");
	printf("■        | |____                                                         ■\n");
	printf("■         #_____                                                         ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                 ____                                    ■\n");
	printf("■         / ____|               |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ # |__ <                                   ■\n");
	printf("■        | |__| | (_| | | | | | |___) |                                  ■\n");
	printf("■         #_____|#__,_|_| |_| |_|____/                                   ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |                                                             ■\n");
	printf("■        | |                                                             ■\n");
	printf("■        | |____                                                         ■\n");
	printf("■         #_____|                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                 ____                                    ■\n");
	printf("■         / ____|               |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ # |__ <                                   ■\n");
	printf("■        | |__| | (_| | | | | | |___) |                                  ■\n");
	printf("■         #_____|#__,_|_| |_| |_|____/                                   ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |                                                             ■\n");
	printf("■        | |         |                                                   ■\n");
	printf("■        | |____     |                                                   ■\n");
	printf("■         #_____|    |                                                   ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                 ____                                    ■\n");
	printf("■         / ____|               |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ # |__ <                                   ■\n");
	printf("■        | |__| | (_| | | | | | |___) |                                  ■\n");
	printf("■         #_____|#__,_|_| |_| |_|____/                                   ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |          _                                                  ■\n");
	printf("■        | |         |                                                   ■\n");
	printf("■        | |____     |                                                   ■\n");
	printf("■         #_____|    |_                                                  ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                 ____                                    ■\n");
	printf("■         / ____|               |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ # |__ <                                   ■\n");
	printf("■        | |__| | (_| | | | | | |___) |                                  ■\n");
	printf("■         #_____|#__,_|_| |_| |_|____/                                   ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |          _                                                  ■\n");
	printf("■        | |         | '                                                 ■\n");
	printf("■        | |____     | |                                                 ■\n");
	printf("■         #_____|    |_|                                                 ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                 ____                                    ■\n");
	printf("■         / ____|               |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ # |__ <                                   ■\n");
	printf("■        | |__| | (_| | | | | | |___) |                                  ■\n");
	printf("■         #_____|#__,_|_| |_| |_|____/                                   ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |          _ _                                                ■\n");
	printf("■        | |         | '_                                                ■\n");
	printf("■        | |____     | |                                                 ■\n");
	printf("■         #_____|    |_|                                                 ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                 ____                                    ■\n");
	printf("■         / ____|               |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ # |__ <                                   ■\n");
	printf("■        | |__| | (_| | | | | | |___) |                                  ■\n");
	printf("■         #_____|#__,_|_| |_| |_|____/                                   ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |          _ __                                               ■\n");
	printf("■        | |         | '_                                                ■\n");
	printf("■        | |____     | | |                                               ■\n");
	printf("■         #_____|    |_| |                                               ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                 ____                                    ■\n");
	printf("■         / ____|               |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ # |__ <                                   ■\n");
	printf("■        | |__| | (_| | | | | | |___) |                                  ■\n");
	printf("■         #_____|#__,_|_| |_| |_|____/                                   ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |          _ __                                               ■\n");
	printf("■        | |         | '_ `                                              ■\n");
	printf("■        | |____     | | |                                               ■\n");
	printf("■         #_____|    |_| |_                                              ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                 ____                                    ■\n");
	printf("■         / ____|               |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ # |__ <                                   ■\n");
	printf("■        | |__| | (_| | | | | | |___) |                                  ■\n");
	printf("■         #_____|#__,_|_| |_| |_|____/                                   ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |          _ __ _                                             ■\n");
	printf("■        | |         | '_ `                                              ■\n");
	printf("■        | |____     | | | |                                             ■\n");
	printf("■         #_____|    |_| |_|                                             ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                 ____                                    ■\n");
	printf("■         / ____|               |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ # |__ <                                   ■\n");
	printf("■        | |__| | (_| | | | | | |___) |                                  ■\n");
	printf("■         #_____|#__,_|_| |_| |_|____/                                   ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |          _ __ __                                            ■\n");
	printf("■        | |         | '_ ` _                                            ■\n");
	printf("■        | |____     | | | |                                             ■\n");
	printf("■         #_____|    |_| |_|                                             ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                 ____                                    ■\n");
	printf("■         / ____|               |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ # |__ <                                   ■\n");
	printf("■        | |__| | (_| | | | | | |___) |                                  ■\n");
	printf("■         #_____|#__,_|_| |_| |_|____/                                   ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |          _ __ ___                                           ■\n");
	printf("■        | |         | '_ ` _                                            ■\n");
	printf("■        | |____     | | | | |                                           ■\n");
	printf("■         #_____|    |_| |_| |                                           ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                 ____                                    ■\n");
	printf("■         / ____|               |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ # |__ <                                   ■\n");
	printf("■        | |__| | (_| | | | | | |___) |                                  ■\n");
	printf("■         #_____|#__,_|_| |_| |_|____/                                   ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |          _ __ ___                                           ■\n");
	printf("■        | |         | '_ ` _ #                                          ■\n");
	printf("■        | |____     | | | | | |                                         ■\n");
	printf("■         #_____|    |_| |_| |_|                                         ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                 ____                                    ■\n");
	printf("■         / ____|               |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ # |__ <                                   ■\n");
	printf("■        | |__| | (_| | | | | | |___) |                                  ■\n");
	printf("■         #_____|#__,_|_| |_| |_|____/                                   ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |          _ __ ___  _ __                                     ■\n");
	printf("■        | |         | '_ ` _ #|                                         ■\n");
	printf("■        | |____     | | | | | |                                         ■\n");
	printf("■         #_____|    |_| |_| |_|                                         ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                 ____                                    ■\n");
	printf("■         / ____|               |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ # |__ <                                   ■\n");
	printf("■        | |__| | (_| | | | | | |___) |                                  ■\n");
	printf("■         #_____|#__,_|_| |_| |_|____/                                   ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |          _ __ ___  _ __                                     ■\n");
	printf("■        | |         | '_ ` _ #| '_ #                                    ■\n");
	printf("■        | |____     | | | | | |                                         ■\n");
	printf("■         #_____|    |_| |_| |_|                                         ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                 ____                                    ■\n");
	printf("■         / ____|               |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ # |__ <                                   ■\n");
	printf("■        | |__| | (_| | | | | | |___) |                                  ■\n");
	printf("■         #_____|#__,_|_| |_| |_|____/                                   ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |          _ __ ___  _ __                                     ■\n");
	printf("■        | |         | '_ ` _ #| '_ #                                    ■\n");
	printf("■        | |____     | | | | | | |_) |                                   ■\n");
	printf("■         #_____|    |_| |_| |_|                                         ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                 ____                                    ■\n");
	printf("■         / ____|               |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ # |__ <                                   ■\n");
	printf("■        | |__| | (_| | | | | | |___) |                                  ■\n");
	printf("■         #_____|#__,_|_| |_| |_|____/                                   ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |          _ __ ___  _ __                                     ■\n");
	printf("■        | |         | '_ ` _ #| '_ #                                    ■\n");
	printf("■        | |____     | | | | | | |_) |                                   ■\n");
	printf("■         #_____|    |_| |_| |_| .__/                                    ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                 ____                                    ■\n");
	printf("■         / ____|               |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ # |__ <                                   ■\n");
	printf("■        | |__| | (_| | | | | | |___) |                                  ■\n");
	printf("■         #_____|#__,_|_| |_| |_|____/                                   ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |          _ __ ___  _ __                                     ■\n");
	printf("■        | |         | '_ ` _ #| '_ #                                    ■\n");
	printf("■        | |____     | | | | | | |_) |                                   ■\n");
	printf("■         #_____|    |_| |_| |_| .__/                                    ■\n");
	printf("■                              | |                                       ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                 ____                                    ■\n");
	printf("■         / ____|               |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ # |__ <                                   ■\n");
	printf("■        | |__| | (_| | | | | | |___) |                                  ■\n");
	printf("■         #_____|#__,_|_| |_| |_|____/                                   ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |          _ __ ___  _ __                                     ■\n");
	printf("■        | |         | '_ ` _ #| '_ #                                    ■\n");
	printf("■        | |____     | | | | | | |_) |                                   ■\n");
	printf("■         #_____|    |_| |_| |_| .__/                                    ■\n");
	printf("■                              | |                                       ■\n");
	printf("■                              |_|                                       ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                 ____                                    ■\n");
	printf("■         / ____|               |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ # |__ <                                   ■\n");
	printf("■        | |__| | (_| | | | | | |___) |                                  ■\n");
	printf("■         #_____|#__,_|_| |_| |_|____/                                   ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |          _ __ ___  _ __   _                                 ■\n");
	printf("■        | |         | '_ ` _ #| '_ # /                                  ■\n");
	printf("■        | |____     | | | | | | |_) |                                   ■\n");
	printf("■         #_____|    |_| |_| |_| .__/                                    ■\n");
	printf("■                              | |                                       ■\n");
	printf("■                              |_|                                       ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                 ____                                    ■\n");
	printf("■         / ____|               |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ # |__ <                                   ■\n");
	printf("■        | |__| | (_| | | | | | |___) |                                  ■\n");
	printf("■         #_____|#__,_|_| |_| |_|____/                                   ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |          _ __ ___  _ __   __                                ■\n");
	printf("■        | |         | '_ ` _ #| '_ # /                                  ■\n");
	printf("■        | |____     | | | | | | |_) |                                   ■\n");
	printf("■         #_____|    |_| |_| |_| .__/                                    ■\n");
	printf("■                              | |                                       ■\n");
	printf("■                              |_|                                       ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                 ____                                    ■\n");
	printf("■         / ____|               |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ # |__ <                                   ■\n");
	printf("■        | |__| | (_| | | | | | |___) |                                  ■\n");
	printf("■         #_____|#__,_|_| |_| |_|____/                                   ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |          _ __ ___  _ __   __                                ■\n");
	printf("■        | |         | '_ ` _ #| '_ # / _                                ■\n");
	printf("■        | |____     | | | | | | |_) | (                                 ■\n");
	printf("■         #_____|    |_| |_| |_| .__/ #                                  ■\n");
	printf("■                              | |                                       ■\n");
	printf("■                              |_|                                       ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                 ____                                    ■\n");
	printf("■         / ____|               |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ # |__ <                                   ■\n");
	printf("■        | |__| | (_| | | | | | |___) |                                  ■\n");
	printf("■         #_____|#__,_|_| |_| |_|____/                                   ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |          _ __ ___  _ __   __ _                              ■\n");
	printf("■        | |         | '_ ` _ #| '_ # / _`                               ■\n");
	printf("■        | |____     | | | | | | |_) | (_                                ■\n");
	printf("■         #_____|    |_| |_| |_| .__/ #_                                 ■\n");
	printf("■                              | |                                       ■\n");
	printf("■                              |_|                                       ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                 ____                                    ■\n");
	printf("■         / ____|               |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ # |__ <                                   ■\n");
	printf("■        | |__| | (_| | | | | | |___) |                                  ■\n");
	printf("■         #_____|#__,_|_| |_| |_|____/                                   ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |          _ __ ___  _ __   __ _                              ■\n");
	printf("■        | |         | '_ ` _ #| '_ # / _` |                             ■\n");
	printf("■        | |____     | | | | | | |_) | (_|                               ■\n");
	printf("■         #_____|    |_| |_| |_| .__/ #__                                ■\n");
	printf("■                              | |                                       ■\n");
	printf("■                              |_|                                       ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                 ____                                    ■\n");
	printf("■         / ____|               |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ # |__ <                                   ■\n");
	printf("■        | |__| | (_| | | | | | |___) |                                  ■\n");
	printf("■         #_____|#__,_|_| |_| |_|____/                                   ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |          _ __ ___  _ __   __ _                              ■\n");
	printf("■        | |         | '_ ` _ #| '_ # / _` |                             ■\n");
	printf("■        | |____     | | | | | | |_) | (_| |                             ■\n");
	printf("■         #_____|    |_| |_| |_| .__/ #__,                               ■\n");
	printf("■                              | |                                       ■\n");
	printf("■                              |_|                                       ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                 ____                                    ■\n");
	printf("■         / ____|               |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ # |__ <                                   ■\n");
	printf("■        | |__| | (_| | | | | | |___) |                                  ■\n");
	printf("■         #_____|#__,_|_| |_| |_|____/                                   ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |          _ __ ___  _ __   __ _                              ■\n");
	printf("■        | |         | '_ ` _ #| '_ # / _` |                             ■\n");
	printf("■        | |____     | | | | | | |_) | (_| |                             ■\n");
	printf("■         #_____|    |_| |_| |_| .__/ #__,_|                             ■\n");
	printf("■                              | |                                       ■\n");
	printf("■                              |_|                                       ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                 ____                                    ■\n");
	printf("■         / ____|               |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ # |__ <                                   ■\n");
	printf("■        | |__| | (_| | | | | | |___) |                                  ■\n");
	printf("■         #_____|#__,_|_| |_| |_|____/                                   ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |          _ __ ___  _ __   __ _ _                            ■\n");
	printf("■        | |         | '_ ` _ #| '_ # / _` |                             ■\n");
	printf("■        | |____     | | | | | | |_) | (_| |                             ■\n");
	printf("■         #_____|    |_| |_| |_| .__/ #__,_|_                            ■\n");
	printf("■                              | |                                       ■\n");
	printf("■                              |_|                                       ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                 ____                                    ■\n");
	printf("■         / ____|               |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ # |__ <                                   ■\n");
	printf("■        | |__| | (_| | | | | | |___) |                                  ■\n");
	printf("■         #_____|#__,_|_| |_| |_|____/                                   ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |          _ __ ___  _ __   __ _ _                            ■\n");
	printf("■        | |         | '_ ` _ #| '_ # / _` | '                           ■\n");
	printf("■        | |____     | | | | | | |_) | (_| | |                           ■\n");
	printf("■         #_____|    |_| |_| |_| .__/ #__,_|_|                           ■\n");
	printf("■                              | |                                       ■\n");
	printf("■                              |_|                                       ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                 ____                                    ■\n");
	printf("■         / ____|               |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ # |__ <                                   ■\n");
	printf("■        | |__| | (_| | | | | | |___) |                                  ■\n");
	printf("■         #_____|#__,_|_| |_| |_|____/                                   ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |          _ __ ___  _ __   __ _ _ _                          ■\n");
	printf("■        | |         | '_ ` _ #| '_ # / _` | '_                          ■\n");
	printf("■        | |____     | | | | | | |_) | (_| | |                           ■\n");
	printf("■         #_____|    |_| |_| |_| .__/ #__,_|_|                           ■\n");
	printf("■                              | |                                       ■\n");
	printf("■                              |_|                                       ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                 ____                                    ■\n");
	printf("■         / ____|               |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ # |__ <                                   ■\n");
	printf("■        | |__| | (_| | | | | | |___) |                                  ■\n");
	printf("■         #_____|#__,_|_| |_| |_|____/                                   ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |          _ __ ___  _ __   __ _ _ __                         ■\n");
	printf("■        | |         | '_ ` _ #| '_ # / _` | '_                          ■\n");
	printf("■        | |____     | | | | | | |_) | (_| | | |                         ■\n");
	printf("■         #_____|    |_| |_| |_| .__/ #__,_|_| |                         ■\n");
	printf("■                              | |                                       ■\n");
	printf("■                              |_|                                       ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                 ____                                    ■\n");
	printf("■         / ____|               |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ # |__ <                                   ■\n");
	printf("■        | |__| | (_| | | | | | |___) |                                  ■\n");
	printf("■         #_____|#__,_|_| |_| |_|____/                                   ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |          _ __ ___  _ __   __ _ _ __                         ■\n");
	printf("■        | |         | '_ ` _ #| '_ # / _` | '_ #                        ■\n");
	printf("■        | |____     | | | | | | |_) | (_| | | |                         ■\n");
	printf("■         #_____|    |_| |_| |_| .__/ #__,_|_| |_                        ■\n");
	printf("■                              | |                                       ■\n");
	printf("■                              |_|                                       ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                 ____                                    ■\n");
	printf("■         / ____|               |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ # |__ <                                   ■\n");
	printf("■        | |__| | (_| | | | | | |___) |                                  ■\n");
	printf("■         #_____|#__,_|_| |_| |_|____/                                   ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |          _ __ ___  _ __   __ _ _ __                         ■\n");
	printf("■        | |         | '_ ` _ #| '_ # / _` | '_ #                        ■\n");
	printf("■        | |____     | | | | | | |_) | (_| | | | |                       ■\n");
	printf("■         #_____|    |_| |_| |_| .__/ #__,_|_| |_|                       ■\n");
	printf("■                              | |                                       ■\n");
	printf("■                              |_|                                       ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                 ____                                    ■\n");
	printf("■         / ____|               |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ # |__ <                                   ■\n");
	printf("■        | |__| | (_| | | | | | |___) |                                  ■\n");
	printf("■         #_____|#__,_|_| |_| |_|____/                                   ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |          _ __ ___  _ __   __ _ _ __                         ■\n");
	printf("■        | |         | '_ ` _ #| '_ # / _` | '_ #|                       ■\n");
	printf("■        | |____     | | | | | | |_) | (_| | | | |                       ■\n");
	printf("■         #_____|    |_| |_| |_| .__/ #__,_|_| |_|                       ■\n");
	printf("■                              | |                                       ■\n");
	printf("■                              |_|                |___/                  ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                 ____                                    ■\n");
	printf("■         / ____|               |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ # |__ <                                   ■\n");
	printf("■        | |__| | (_| | | | | | |___) |                                  ■\n");
	printf("■         #_____|#__,_|_| |_| |_|____/                                   ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |          _ __ ___  _ __   __ _ _ __                         ■\n");
	printf("■        | |         | '_ ` _ #| '_ # / _` | '_ #|                       ■\n");
	printf("■        | |____     | | | | | | |_) | (_| | | | |                       ■\n");
	printf("■         #_____|    |_| |_| |_| .__/ #__,_|_| |_|                       ■\n");
	printf("■                              | |                 __/ |                 ■\n");
	printf("■                              |_|                |___/                  ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                 ____                                    ■\n");
	printf("■         / ____|               |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ # |__ <                                   ■\n");
	printf("■        | |__| | (_| | | | | | |___) |                                  ■\n");
	printf("■         #_____|#__,_|_| |_| |_|____/                                   ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |          _ __ ___  _ __   __ _ _ __                         ■\n");
	printf("■        | |         | '_ ` _ #| '_ # / _` | '_ #|                       ■\n");
	printf("■        | |____     | | | | | | |_) | (_| | | | |                       ■\n");
	printf("■         #_____|    |_| |_| |_| .__/ #__,_|_| |_|#__, |                 ■\n");
	printf("■                              | |                 __/ |                 ■\n");
	printf("■                              |_|                |___/                  ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                 ____                                    ■\n");
	printf("■         / ____|               |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ # |__ <                                   ■\n");
	printf("■        | |__| | (_| | | | | | |___) |                                  ■\n");
	printf("■         #_____|#__,_|_| |_| |_|____/                                   ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |          _ __ ___  _ __   __ _ _ __                         ■\n");
	printf("■        | |         | '_ ` _ #| '_ # / _` | '_ #|                       ■\n");
	printf("■        | |____     | | | | | | |_) | (_| | | | | |_| |                 ■\n");
	printf("■         #_____|    |_| |_| |_| .__/ #__,_|_| |_|#__, |                 ■\n");
	printf("■                              | |                 __/ |                 ■\n");
	printf("■                              |_|                |___/                  ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                 ____                                    ■\n");
	printf("■         / ____|               |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ # |__ <                                   ■\n");
	printf("■        | |__| | (_| | | | | | |___) |                                  ■\n");
	printf("■         #_____|#__,_|_| |_| |_|____/                                   ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |          _ __ ___  _ __   __ _ _ __                         ■\n");
	printf("■        | |         | '_ ` _ #| '_ # / _` | '_ #| | | |                 ■\n");
	printf("■        | |____     | | | | | | |_) | (_| | | | | |_| |                 ■\n");
	printf("■         #_____|    |_| |_| |_| .__/ #__,_|_| |_|#__, |                 ■\n");
	printf("■                              | |                 __/ |                 ■\n");
	printf("■                              |_|                |___/                  ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                 ____                                    ■\n");
	printf("■         / ____|               |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ # |__ <                                   ■\n");
	printf("■        | |__| | (_| | | | | | |___) |                                  ■\n");
	printf("■         #_____|#__,_|_| |_| |_|____/                                   ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |          _ __ ___  _ __   __ _ _ __  _   _                  ■\n");
	printf("■        | |         | '_ ` _ #| '_ # / _` | '_ #| | | |                 ■\n");
	printf("■        | |____     | | | | | | |_) | (_| | | | | |_| |                 ■\n");
	printf("■         #_____|    |_| |_| |_| .__/ #__,_|_| |_|#__, |                 ■\n");
	printf("■                              | |                 __/ |                 ■\n");
	printf("■                              |_|                |___/                  ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                 ____                                    ■\n");
	printf("■         / ____|               |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ # |__ <                                   ■\n");
	printf("■        | |__| | (_| | | | | | |___) |                                  ■\n");
	printf("■         #_____|#__,_|_| |_| |_|____/                                   ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |          _ __ ___  _ __   __ _ _ __  _   _                  ■\n");
	printf("■        | |      _  | '_ ` _ #| '_ # / _` | '_ #| | | |                 ■\n");
	printf("■        | |____ (_) | | | | | | |_) | (_| | | | | |_| |                 ■\n");
	printf("■         #_____|    |_| |_| |_| .__/ #__,_|_| |_|#__, |                 ■\n");
	printf("■                              | |                 __/ |                 ■\n");
	printf("■                              |_|                |___/                  ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(100);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                 ____                                    ■\n");
	printf("■         / ____|               |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ # |__ <                                   ■\n");
	printf("■        | |__| | (_| | | | | | |___) |                                  ■\n");
	printf("■         #_____|#__,_|_| |_| |_|____/                                   ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |          _ __ ___  _ __   __ _ _ __  _   _                  ■\n");
	printf("■        | |    / _ #| '_ ` _ #| '_ # / _` | '_ #| | | |                 ■\n");
	printf("■        | |___| (_) | | | | | | |_) | (_| | | | | |_| |                 ■\n");
	printf("■         #_____#   /|_| |_| |_| .__/ #__,_|_| |_|#__, |                 ■\n");
	printf("■                              | |                 __/ |                 ■\n");
	printf("■                              |_|                |___/                  ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(100);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                 ____                                    ■\n");
	printf("■         / ____|               |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ # |__ <                                   ■\n");
	printf("■        | |__| | (_| | | | | | |___) |                                  ■\n");
	printf("■         #_____|#__,_|_| |_| |_|____/                                   ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |     ___  _ __ ___  _ __   __ _ _ __  _   _                  ■\n");
	printf("■        | |    / _ #| '_ ` _ #| '_ # / _` | '_ #| | | |                 ■\n");
	printf("■        | |___| (_) | | | | | | |_) | (_| | | | | |_| |                 ■\n");
	printf("■         #_____#___/|_| |_| |_| .__/ #__,_|_| |_|#__, |                 ■\n");
	printf("■                              | |                 __/ |                 ■\n");
	printf("■                              |_|                |___/                  ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(100);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                 ____                                    ■\n");
	printf("■         / ____|               |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ # |__ <                                   ■\n");
	printf("■        | |__| | (_| | | | | | |___) |                                  ■\n");
	printf("■         #_____|#__,_|_| |_| |_|____/                                   ■\n");
	printf("■         / ____| |                                                      ■\n");
	printf("■        | |     ___  _ __ ___  _ __   __ _ _ __  _   _                  ■\n");
	printf("■        | |  _ / _ #| '_ ` _ #| '_ # / _` | '_ #| | | |                 ■\n");
	printf("■        | |___| (_) | | | | | | |_) | (_| | | | | |_| |                 ■\n");
	printf("■         #_____#___/|_| |_| |_| .__/ #__,_|_| |_|#__, |                 ■\n");
	printf("■                 |            | |                 __/ |                 ■\n");
	printf("■                              |_|                |___/                  ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                 ____                                    ■\n");
	printf("■         / ____|               |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ # |__ <                                   ■\n");
	printf("■        | |__| | (_| | | | | | |___) |                                  ■\n");
	printf("■         #_____|#__,_|_| |_| |_|____/                                   ■\n");
	printf("■         / ____| |                                                      ■\n");
	printf("■        | |     ___  _ __ ___  _ __   __ _ _ __  _   _                  ■\n");
	printf("■        | | __ / _ #| '_ ` _ #| '_ # / _` | '_ #| | | |                 ■\n");
	printf("■        | |___| (_) | | | | | | |_) | (_| | | | | |_| |                 ■\n");
	printf("■         #_____#___/|_| |_| |_| .__/ #__,_|_| |_|#__, |                 ■\n");
	printf("■                 |            | |                 __/ |                 ■\n");
	printf("■                 |            |_|                |___/                  ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                 ____                                    ■\n");
	printf("■         / ____|               |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ # |__ <                                   ■\n");
	printf("■        | |__| | (_| | | | | | |___) |                                  ■\n");
	printf("■         #_____|#__,_|_| |_| |_|____/                                   ■\n");
	printf("■         / ____| .                                                      ■\n");
	printf("■        | |     ___  _ __ ___  _ __   __ _ _ __  _   _                  ■\n");
	printf("■        | |__. / _ #| '_ ` _ #| '_ # / _` | '_ #| | | |                 ■\n");
	printf("■        | |___| (_) | | | | | | |_) | (_| | | | | |_| |                 ■\n");
	printf("■         #_____#___/|_| |_| |_| .__/ #__,_|_| |_|#__, |                 ■\n");
	printf("■                 .            | |                 __/ |                 ■\n");
	printf("■                 |            |_|                |___/                  ■\n");
	printf("■                 |                                                      ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                 ____                                    ■\n");
	printf("■         / ____| |             |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ # |__ <                                   ■\n");
	printf("■        | |__| | (_| | | | | | |___) |                                  ■\n");
	printf("■         #_____|#__,_|_| |_| |_|____/                                   ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |     ___  _ __ ___  _ __   __ _ _ __  _   _                  ■\n");
	printf("■        | |_.  / _ #| '_ ` _ #| '_ # / _` | '_ #| | | |                 ■\n");
	printf("■        | |___| (_) | | | | | | |_) | (_| | | | | |_| |                 ■\n");
	printf("■         #_____#___/|_| |_| |_| .__/ #__,_|_| |_|#__, |                 ■\n");
	printf("■                              | |                 __/ |                 ■\n");
	printf("■                 .            |_|                |___/                  ■\n");
	printf("■                 |                                                      ■\n");
	printf("■                 |                                                      ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____  |              ____                                    ■\n");
	printf("■         / ____| |             |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ # |__ <                                   ■\n");
	printf("■        | |__| | (_| | | | | | |___) |                                  ■\n");
	printf("■         #_____|#__,_|_| |_| |_|____/                                   ■\n");
	printf("■         / ____| .                                                      ■\n");
	printf("■        | |     ___  _ __ ___  _ __   __ _ _ __  _   _                  ■\n");
	printf("■        | |.  ./ _ #| '_ ` _ #| '_ # / _` | '_ #| | | |                 ■\n");
	printf("■        | |___| (_) | | | | | | |_) | (_| | | | | |_| |                 ■\n");
	printf("■         #_____#___/|_| |_| |_| .__/ #__,_|_| |_|#__, |                 ■\n");
	printf("■                 .            | |                 __/ |                 ■\n");
	printf("■                              |_|                |___/                  ■\n");
	printf("■                 .                                                      ■\n");
	printf("■                 |                                                      ■\n");
	printf("■                 |                                                      ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                 |                                                      ■\n");
	printf("■          _____  |              ____                                    ■\n");
	printf("■         / ____| .             |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ # |__ <                                   ■\n");
	printf("■        | |__| | (_| | | | | | |___) |                                  ■\n");
	printf("■         #_____|#__,_|_| |_| |_|____/                                   ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |     ___  _ __ ___  _ __   __ _ _ __  _   _                  ■\n");
	printf("■        | |  . / _ #| '_ ` _ #| '_ # / _` | '_ #| | | |                 ■\n");
	printf("■        | |___| (_) | | | | | | |_) | (_| | | | | |_| |                 ■\n");
	printf("■         #_____#___/|_| |_| |_| .__/ #__,_|_| |_|#__, |                 ■\n");
	printf("■                              | |                 __/ |                 ■\n");
	printf("■                 .            |_|                |___/                  ■\n");
	printf("■                                                                        ■\n");
	printf("■                 .                                                      ■\n");
	printf("■                 |                                                      ■\n");
	printf("■                 |                                                      ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                 |                                                      ■\n");
	printf("■                 |                                                      ■\n");
	printf("■          _____  .              ____                                    ■\n");
	printf("■         / ____|               |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ # |__ <                                   ■\n");
	printf("■        | |__| | (_| | | | | | |___) |                                  ■\n");
	printf("■         #_____|#__,_|_| |_| |_|____/                                   ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |     ___  _ __ ___  _ __   __ _ _ __  _   _                  ■\n");
	printf("■       _| | .  / _ #| '_ ` _ #| '_ # / _` | '_ #| | | |                 ■\n");
	printf("■        | |___| (_) | | | | | | |_) | (_| | | | | |_| |                 ■\n");
	printf("■         #_____#___/|_| |_| |_| .__/ #__,_|_| |_|#__, |                 ■\n");
	printf("■                              | |                 __/ |                 ■\n");
	printf("■                              |_|                |___/                  ■\n");
	printf("■                 .                                                      ■\n");
	printf("■                                                                        ■\n");
	printf("■                 .                                                      ■\n");
	printf("■                 |                                                      ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                 |                                                      ■\n");
	printf("■                 |                                                      ■\n");
	printf("■                 .                                                      ■\n");
	printf("■          _____                 ____                                    ■\n");
	printf("■         / ____| .             |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ # |__ <                                   ■\n");
	printf("■        | |__| | (_| | | | | | |___) |                                  ■\n");
	printf("■         #_____|#__,_|_| |_| |_|____/                                   ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |     ___  _ __ ___  _ __   __ _ _ __  _   _                  ■\n");
	printf("■      __| |.   / _ #| '_ ` _ #| '_ # / _` | '_ #| | | |                 ■\n");
	printf("■        | |___| (_) | | | | | | |_) | (_| | | | | |_| |                 ■\n");
	printf("■         #_____#___/|_| |_| |_| .__/ #__,_|_| |_|#__, |                 ■\n");
	printf("■                              | |                 __/ |                 ■\n");
	printf("■                              |_|                |___/                  ■\n");
	printf("■                                                                        ■\n");
	printf("■                 .                                                      ■\n");
	printf("■                                                                        ■\n");
	printf("■                 .                                                      ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                 |                                                      ■\n");
	printf("■                 |                                                      ■\n");
	printf("■                 .                                                      ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____  .              ____                                    ■\n");
	printf("■         / ____|               |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ # |__ <                                   ■\n");
	printf("■        | |__| | (_| | | | | | |___) |                                  ■\n");
	printf("■         #_____|#__,_|_| |_| |_|____/                                   ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |     ___  _ __ ___  _ __   __ _ _ __  _   _                  ■\n");
	printf("■     __.| |    / _ #| '_ ` _ #| '_ # / _` | '_ #| | | |                 ■\n");
	printf("■        | |___| (_) | | | | | | |_) | (_| | | | | |_| |                 ■\n");
	printf("■         #_____#___/|_| |_| |_| .__/ #__,_|_| |_|#__, |                 ■\n");
	printf("■                              | |                 __/ |                 ■\n");
	printf("■                              |_|                |___/                  ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                 .                                                      ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                  |                                                     ■\n");
	printf("■                  |                                                     ■\n");
	printf("■                  .                                                     ■\n");
	printf("■                                                                        ■\n");
	printf("■                  .                                                     ■\n");
	printf("■          _____                 ____                                    ■\n");
	printf("■         / ____|               |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ # |__ <                                   ■\n");
	printf("■        | |__| | (_| | | | | | |___) |                                  ■\n");
	printf("■         #_____|#__,_|_| |_| |_|____/                                   ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |     ___  _ __ ___  _ __   __ _ _ __  _   _                  ■\n");
	printf("■    __. | |    / _ #| '_ ` _ #| '_ # / _` | '_ #| | | |                 ■\n");
	printf("■        | |___| (_) | | | | | | |_) | (_| | | | | |_| |                 ■\n");
	printf("■         #_____#___/|_| |_| |_| .__/ #__,_|_| |_|#__, |                 ■\n");
	printf("■                              | |                 __/ |                 ■\n");
	printf("■                              |_|                |___/                  ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                 .                                                      ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                 |                                                      ■\n");
	printf("■                 .                                                      ■\n");
	printf("■                                                                        ■\n");
	printf("■                 .                                                      ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                 ____                                    ■\n");
	printf("■         / ____|               |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ # |__ <                                   ■\n");
	printf("■        | |__| | (_| | | | | | |___) |                                  ■\n");
	printf("■         #_____|#__,_|_| |_| |_|____/                                   ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |     ___  _ __ ___  _ __   __ _ _ __  _   _                  ■\n");
	printf("■   __.  | |    / _ #| '_ ` _ #| '_ # / _` | '_ #| | | |                 ■\n");
	printf("■        | |___| (_) | | | | | | |_) | (_| | | | | |_| |                 ■\n");
	printf("■         #_____#___/|_| |_| |_| .__/ #__,_|_| |_|#__, |                 ■\n");
	printf("■                              | |                 __/ |                 ■\n");
	printf("■                              |_|                |___/                  ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                 .                                                      ■\n");
	printf("■                                                                        ■\n");
	printf("■                 .                                                      ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                 ____                                    ■\n");
	printf("■         / ____|               |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ # |__ <                                   ■\n");
	printf("■        | |__| | (_| | | | | | |___) |                                  ■\n");
	printf("■         #_____|#__,_|_| |_| |_|____/                                   ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |     ___  _ __ ___  _ __   __ _ _ __  _   _                  ■\n");
	printf("■  __.  .| |    / _ #| '_ ` _ #| '_ # / _` | '_ #| | | |                 ■\n");
	printf("■        | |___| (_) | | | | | | |_) | (_| | | | | |_| |                 ■\n");
	printf("■         #_____#___/|_| |_| |_| .__/ #__,_|_| |_|#__, |                 ■\n");
	printf("■                              | |                 __/ |                 ■\n");
	printf("■                              |_|                |___/                  ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                 .                                                      ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                 ____                                    ■\n");
	printf("■         / ____|               |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ # |__ <                                   ■\n");
	printf("■        | |__| | (_| | | | | | |___) |                                  ■\n");
	printf("■         #_____|#__,_|_| |_| |_|____/                                   ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |     ___  _ __ ___  _ __   __ _ _ __  _   _                  ■\n");
	printf("■ __.  . | |    / _ #| '_ ` _ #| '_ # / _` | '_ #| | | |                 ■\n");
	printf("■        | |___| (_) | | | | | | |_) | (_| | | | | |_| |                 ■\n");
	printf("■         #_____#___/|_| |_| |_| .__/ #__,_|_| |_|#__, |                 ■\n");
	printf("■                              | |                 __/ |                 ■\n");
	printf("■                              |_|                |___/                  ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                 .                                                      ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                 ____                                    ■\n");
	printf("■         / ____|               |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ # |__ <                                   ■\n");
	printf("■        | |__| | (_| | | | | | |___) |                                  ■\n");
	printf("■         #_____|#__,_|_| |_| |_|____/                                   ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |     ___  _ __ ___  _ __   __ _ _ __  _   _                  ■\n");
	printf("■__.  .  | |    / _ #| '_ ` _ #| '_ # / _` | '_ #| | | |                 ■\n");
	printf("■        | |___| (_) | | | | | | |_) | (_| | | | | |_| |                 ■\n");
	printf("■         #_____#___/|_| |_| |_| .__/ #__,_|_| |_|#__, |                 ■\n");
	printf("■                              | |                 __/ |                 ■\n");
	printf("■                              |_|                |___/                  ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                 ____                                    ■\n");
	printf("■         / ____|               |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ # |__ <                                   ■\n");
	printf("■        | |__| | (_| | | | | | |___) |                                  ■\n");
	printf("■         #_____|#__,_|_| |_| |_|____/                                   ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |     ___  _ __ ___  _ __   __ _ _ __  _   _                  ■\n");
	printf("■_.  .   | |    / _ #| '_ ` _ #| '_ # / _` | '_ #| | | |                 ■\n");
	printf("■        | |___| (_) | | | | | | |_) | (_| | | | | |_| |                 ■\n");
	printf("■         #_____#___/|_| |_| |_| .__/ #__,_|_| |_|#__, |                 ■\n");
	printf("■                              | |                 __/ |                 ■\n");
	printf("■                              |_|                |___/                  ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                 ____                                    ■\n");
	printf("■         / ____|               |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ # |__ <                                   ■\n");
	printf("■        | |__| | (_| | | | | | |___) |                                  ■\n");
	printf("■         #_____|#__,_|_| |_| |_|____/                                   ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |     ___  _ __ ___  _ __   __ _ _ __  _   _                  ■\n");
	printf("■.  .    | |    / _ #| '_ ` _ #| '_ # / _` | '_ #| | | |                 ■\n");
	printf("■        | |___| (_) | | | | | | |_) | (_| | | | | |_| |                 ■\n");
	printf("■         #_____#___/|_| |_| |_| .__/ #__,_|_| |_|#__, |                 ■\n");
	printf("■                              | |                 __/ |                 ■\n");
	printf("■                              |_|                |___/                  ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                 ____                                    ■\n");
	printf("■         / ____|               |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ # |__ <                                   ■\n");
	printf("■        | |__| | (_| | | | | | |___) |                                  ■\n");
	printf("■         #_____|#__,_|_| |_| |_|____/                                   ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |     ___  _ __ ___  _ __   __ _ _ __  _   _                  ■\n");
	printf("■  .     | |    / _ #| '_ ` _ #| '_ # / _` | '_ #| | | |                 ■\n");
	printf("■        | |___| (_) | | | | | | |_) | (_| | | | | |_| |                 ■\n");
	printf("■         #_____#___/|_| |_| |_| .__/ #__,_|_| |_|#__, |                 ■\n");
	printf("■                              | |                 __/ |                 ■\n");
	printf("■                              |_|                |___/                  ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                 ____                                    ■\n");
	printf("■         / ____|               |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ # |__ <                                   ■\n");
	printf("■        | |__| | (_| | | | | | |___) |                                  ■\n");
	printf("■         #_____|#__,_|_| |_| |_|____/                                   ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |     ___  _ __ ___  _ __   __ _ _ __  _   _                  ■\n");
	printf("■ .      | |    / _ #| '_ ` _ #| '_ # / _` | '_ #| | | |                 ■\n");
	printf("■        | |___| (_) | | | | | | |_) | (_| | | | | |_| |                 ■\n");
	printf("■         #_____#___/|_| |_| |_| .__/ #__,_|_| |_|#__, |                 ■\n");
	printf("■                              | |                 __/ |                 ■\n");
	printf("■                              |_|                |___/                  ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                 ____                                    ■\n");
	printf("■         / ____|               |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ # |__ <                                   ■\n");
	printf("■        | |__| | (_| | | | | | |___) |                                  ■\n");
	printf("■         #_____|#__,_|_| |_| |_|____/                                   ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |     ___  _ __ ___  _ __   __ _ _ __  _   _                  ■\n");
	printf("■.       | |    / _ #| '_ ` _ #| '_ # / _` | '_ #| | | |                 ■\n");
	printf("■        | |___| (_) | | | | | | |_) | (_| | | | | |_| |                 ■\n");
	printf("■         #_____#___/|_| |_| |_| .__/ #__,_|_| |_|#__, |                 ■\n");
	printf("■                              | |                 __/ |                 ■\n");
	printf("■                              |_|                |___/                  ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	Sleep(25);	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■          _____                 ____                                    ■\n");
	printf("■         / ____|               |___ #                                   ■\n");
	printf("■        | |  __  __ _ _ __ ___   __) |                                  ■\n");
	printf("■        | | |_ |/ _` | '_ ` _ # |__ <                                   ■\n");
	printf("■        | |__| | (_| | | | | | |___) |                                  ■\n");
	printf("■         #_____|#__,_|_| |_| |_|____/                                   ■\n");
	printf("■         / ____|                                                        ■\n");
	printf("■        | |     ___  _ __ ___  _ __   __ _ _ __  _   _                  ■\n");
	printf("■        | |    / _ #| '_ ` _ #| '_ # / _` | '_ #| | | |                 ■\n");
	printf("■        | |___| (_) | | | | | | |_) | (_| | | | | |_| |                 ■\n");
	printf("■         #_____#___/|_| |_| |_| .__/ #__,_|_| |_|#__, |                 ■\n");
	printf("■                              | |                 __/ |                 ■\n");
	printf("■                              |_|                |___/                  ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	system("pause");
}


int game_dev_pj_naming()//게임 개발의 첫 부분이자 만들 게임의 이름을 정하는 함수
{
	int bspc = 0;
	unsigned char key;
	int ex_key = 1, i = 0, pj_name_leng, ex_bsp = 0, j = 0;

	char pj_name[80] = { '\0' };
	while (1)
	{

		system("cls");
		pj_name_leng = strlen(pj_name);
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                        프로젝트를 개발합니다.                          ■\n");
		printf("■                    개발할 게임의 이름을 적어주세요(영어)               ■\n");

		printf("■                                                                        ■\n");

		printf("■                     ->%s                                   ", pj_name);
		alignment(pj_name_leng);
		printf("              ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                         제발 영어로 적어주세요                         ■\n");
		printf("■        한글로 작성시 발생할 불이익에 대해서는 책임지지 않습니다        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");

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
void game_dev_pj_cruit(char* pj_name, int pj_name_leng)//게임 개발에 참여할 직원을 선택하는 함수.
{
	int you_will_work[13] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };//이건 최종적으로 일할 직원들의 번호를 가져옴.running에서 사용가능
	int taken[13] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };//목록으로 '가져와진' 직원의 번호.// ?!??!?!?!?!??!?
	char selected[16][3] = { "->", "\0", "\0", "\0", "\0", "\0", "\0", "\0", "\0", "\0", "\0", "\0", "\0", "\0", "\0", "\0" };//화살표 그래픽을 위한 
	char checked[13] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' };
	int i, j;
	int cruit_chk_counted = 0;//최종적으로 일할 직원의 수. running에서 사용가능
	int menu_num = 0;//메뉴 이동시 필요한 변수
	int able_to_work = 0;//직원 채택 목록을 채우기위해 쓰는 변수. 루프가 끝나면 아마 총 가용인원일것이다.
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
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■     %s의 개발을 시작합니다.                           ", pj_name);
		alignment(strlen(pj_name));
		printf("                   ■\n");
		printf("■                                                                        ■\n");
		printf("■  <SYSTEM>  %s                              ", system_message);
		alignment(strlen(system_message));
		printf("                              ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■     이 프로젝트에 참가할 직원을 선택하세요(최대 4명)                   ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■     %s%s%c\t%s%s%c\t%s%s%c\t%s%s%c\t  ■\n", selected[0], list_of_cruit[0], checked[0], selected[1], list_of_cruit[1], checked[1], selected[2], list_of_cruit[2], checked[2], selected[3], list_of_cruit[3], checked[3]);
		printf("■     체력:%d\t         %d\t           %d\t            %d\t          ■\n", stamina[taken[0]], stamina[taken[1]], stamina[taken[2]], stamina[taken[3]]);
		printf("■     %s%s%c\t%s%s%c\t%s%s%c\t%s%s%c\t  ■\n", selected[4], list_of_cruit[4], checked[4], selected[5], list_of_cruit[5], checked[5], selected[6], list_of_cruit[6], checked[6], selected[7], list_of_cruit[7], checked[7]);
		printf("■     체력:%d\t         %d\t           %d\t            %d\t          ■\n", stamina[taken[4]], stamina[taken[5]], stamina[taken[5]], stamina[taken[7]]);
		printf("■     %s%s%c\t%s%s%c\t%s%s%c\t%s%s%c\t  ■\n", selected[8], list_of_cruit[8], checked[8], selected[9], list_of_cruit[9], checked[9], selected[10], list_of_cruit[10], checked[10], selected[11], list_of_cruit[11], checked[11]);
		printf("■     체력:%d\t         %d\t           %d\t            %d\t          ■\n", stamina[taken[8]], stamina[taken[9]], stamina[taken[10]], stamina[taken[11]]);
		printf("■                                                                        ■\n");
		printf("■      %s 뒤로\t                                           %s 완료\t  ■\n", selected[12], selected[15]);
		printf("■                                                                        ■\n");
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");

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
					strcpy(system_message, system_message_init);//시스템메세지 초기화
					launch = 1;
					break;
				}
				else
				{
					strcpy(system_message, err_not_choosed);//고르지 않았다는 시스템 에러 메세지 출력
				}
			}

		}
		fflush(stdin);
		//4명 이상 고르지 못하게 하는 장치
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
int disaster()//이 disaster 함수는 어떠한 재난을 내릴지 결정하는 함수.확률이 희박할수록 더 심한 재난을 내림(시그마임.)사실 이거 10줄 이내로 줄일순 있지만 일단 쓰고 봅니다
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
int game_dev_pj_running(char * pj_name, int * you_will_work, int cruit_chk_counted)//실제 게임을 개발하는 과정을 담을 함수./(/회사명/일할 직원 '번호' 목록/일할 직원의 수)를 참조해온다.
{
	char gauge[11][21] = { { "□□□□□□□□□□" }, { "■□□□□□□□□□" }, { "■■□□□□□□□□" }, { "■■■□□□□□□□" }, { "■■■■□□□□□□" }, { "■■■■■□□□□□" }, { "■■■■■■□□□□" }, { "■■■■■■■□□□" }, { "■■■■■■■■□□" }, { "■■■■■■■■■□" }, { "■■■■■■■■■■" } };
	int i, j;
	int game_point = 0;
	int temp;
	double game_point_programming_const;
	int game_point_graphic_const;
	int game_point_sound_const;
	int process = 0;//이 프로세스 변수는 disaster에 영향을 받음
	int progress = 0;//progress 는 disaster에 영향을 받지 않음
	int disaster_code;
	int disaster_return;
	int when_disaster;
	double game_point_delta = 0;
	int disaster_num[13] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
	double disaster_effect[13] = { 0.3, 0.35, 0.40, 0.45, 0.5, 0.55, 0.60, 0.65, 0.7, 0.75, 0.80, 0.85, 0.9 };
	char disasters[14][31] = { { "세이브파일이 삭제되었습니다!!!" }, { "     지진이 발생했습니다!!    " }, { " 대규모 버그가 발생했습니다!! " }, { "경쟁사에서 대작출현! 의욕상실!" }, { "사무실에 전염병이 창궐합니다! " }, { "      정전이 발생했습니다!    " }, { "  직원이 야근을 도망쳤습니다! " }, { " 컴퓨터에 콜라를 쏟았습니다!  " }, { "과도한 야근으로 인해 의욕상실!" }, { " 디자인팀과 개발팀의 갈등고조 " }, { "          예비군 소집!        " }, { " 프로그램이 응답하지 않습니다 " }, { "         알수없는 오류!       " } };

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
	//for 문을 이용하여 frame_gauge 출력 ;
	//함수 disaster 을 참조하여 반복횟수를 퍼센트로 줄이되 전체순환횟수는 줄이지 않음.
	//disaster의 효과는 임의의 타이밍에 등장, 그러나 개발 초기에는 등장하지 않음, 아마 반복문을 제어하는 제어변수를 응용하면 될것같음.()
	for (progress = 0; progress < 100*cruit_chk_counted; progress++)
	{
		system("cls");
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                  완성률: %s                          ■\n", gauge[progress / (10*cruit_chk_counted)]);
		printf("■                                                                        ■\n");
		printf("■                             %s를 개발중입니다.              ", pj_name);
		alignment(strlen(pj_name));
		printf("             ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                       %s이(가) 개발중입니다!!                    ■\n", worker_name[you_will_work[progress / (100*cruit_chk_counted / cruit_chk_counted)]]);//이 논리 에러. 계속 예외 처리(integer divide by zero)에 관한 언급이 나온다.
		printf("■                                                                        ■\n");
		printf("■                     +    프로그래밍  :  %d              ", programming[you_will_work[progress / (100*cruit_chk_counted / cruit_chk_counted)]]);
		alignment(digiter(programming[you_will_work[(progress / (100*cruit_chk_counted / cruit_chk_counted))]]));
		printf("                 ■\n");
		printf("■                     +    그래픽      :  %d              ", graphic[you_will_work[progress / (100*cruit_chk_counted / cruit_chk_counted)]]);
		alignment(digiter(graphic[you_will_work[(progress / (100*cruit_chk_counted / cruit_chk_counted))]]));
		printf("                 ■\n");
		printf("■                     +    사운드      :  %d              ", sound[you_will_work[progress / (100*cruit_chk_counted / cruit_chk_counted)]]);
		alignment(digiter(sound[you_will_work[(progress / (100*cruit_chk_counted / cruit_chk_counted))]]));
		printf("                 ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                         게임의 완성도:  %d            ", game_point);
		alignment(digiter(game_point));
		printf("                   ■\n");
		printf("■                                                                        ■\n");
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(500);
		game_point_delta = ((programming[you_will_work[progress / (100*cruit_chk_counted / cruit_chk_counted)]] * game_point_programming_const) + (graphic[you_will_work[progress / (100*cruit_chk_counted / cruit_chk_counted)]] * game_point_graphic_const) + (sound[you_will_work[(progress / (100*cruit_chk_counted / cruit_chk_counted))]] * game_point_sound_const)) / 10;
		game_point += game_point_delta;

		if (disaster_code < 5)
		{
			if (progress == when_disaster)
			{
				system("cls");
				printf("%d\n", disaster_return);
				printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
				printf("■                                                                        ■\n");
				printf("■                                                                        ■\n");
				printf("■                                                                        ■\n");
				printf("■                                                                        ■\n");
				printf("■                                                                        ■\n");
				printf("■                                                                        ■\n");
				printf("■                                                                        ■\n");
				printf("■                                                                        ■\n");
				printf("■                                                                        ■\n");
				printf("■                                                                        ■\n");
				printf("■                             재해 발생!!                                ■\n");
				printf("■                                                                        ■\n");
				printf("■                    %s                       ", disasters[disaster_return]);
				alignment(strlen(disasters[disaster_return]));
				printf("  ■\n");
				printf("■                                                                        ■\n");
				printf("■             개발중인 게임의 완성도의 일부가 손실됩니다!                ■\n");
				printf("■                                                                        ■\n");
				printf("■                                                                        ■\n");
				printf("■                                                                        ■\n");
				printf("■                                                                        ■\n");
				printf("■                                                                        ■\n");
				printf("■                                                                        ■\n");
				printf("■                                                                        ■\n");
				printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
				game_point = (game_point*(disaster_effect[disaster_return] * 100)) / 100;
				Sleep(3000);
			}
		}

	}
	game_dev_pj_selling(game_point, pj_name);
	






	return 0;
}
int maxi(int champion,int challenger)//그래프에 참조할 최대값을 구하는 함수
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
	//그래프의 호출에는 3차원 배열이 사용됨.((x:좌표값)(y:좌표값)(z:개채값))
	//1.5초당 하나씩, 한달동안 총 45초, 칸은 6*30
	char graph[31][7][3] = { { { "  " }, { "  " }, { "  " }, { "  " }, { "  " }, { "  " } }, { { "  " }, { "  " }, { "  " }, { "  " }, { "  " }, { "  " } }, { { "  " }, { "  " }, { "  " }, { "  " }, { "  " }, { "  " } }, { { "  " }, { "  " }, { "  " }, { "  " }, { "  " }, { "  " } }, { { "  " }, { "  " }, { "  " }, { "  " }, { "  " }, { "  " } }, { { "  " }, { "  " }, { "  " }, { "  " }, { "  " }, { "  " } }, { { "  " }, { "  " }, { "  " }, { "  " }, { "  " }, { "  " } }, { { "  " }, { "  " }, { "  " }, { "  " }, { "  " }, { "  " } }, { { "  " }, { "  " }, { "  " }, { "  " }, { "  " }, { "  " } }, { { "  " }, { "  " }, { "  " }, { "  " }, { "  " }, { "  " } }, { { "  " }, { "  " }, { "  " }, { "  " }, { "  " }, { "  " } }, { { "  " }, { "  " }, { "  " }, { "  " }, { "  " }, { "  " } }, { { "  " }, { "  " }, { "  " }, { "  " }, { "  " }, { "  " } }, { { "  " }, { "  " }, { "  " }, { "  " }, { "  " }, { "  " } }, { { "  " }, { "  " }, { "  " }, { "  " }, { "  " }, { "  " } }, { { "  " }, { "  " }, { "  " }, { "  " }, { "  " }, { "  " } }, { { "  " }, { "  " }, { "  " }, { "  " }, { "  " }, { "  " } }, { { "  " }, { "  " }, { "  " }, { "  " }, { "  " }, { "  " } }, { { "  " }, { "  " }, { "  " }, { "  " }, { "  " }, { "  " } }, { { "  " }, { "  " }, { "  " }, { "  " }, { "  " }, { "  " } }, { { "  " }, { "  " }, { "  " }, { "  " }, { "  " }, { "  " } }, { { "  " }, { "  " }, { "  " }, { "  " }, { "  " }, { "  " } }, { { "  " }, { "  " }, { "  " }, { "  " }, { "  " }, { "  " } }, { { "  " }, { "  " }, { "  " }, { "  " }, { "  " }, { "  " } }, { { "  " }, { "  " }, { "  " }, { "  " }, { "  " }, { "  " } }, { { "  " }, { "  " }, { "  " }, { "  " }, { "  " }, { "  " } }, { { "  " }, { "  " }, { "  " }, { "  " }, { "  " }, { "  " } }, { { "  " }, { "  " }, { "  " }, { "  " }, { "  " }, { "  " } }, { { "  " }, { "  " }, { "  " }, { "  " }, { "  " }, { "  " } }, { { "  " }, { "  " }, { "  " }, { "  " }, { "  " }, { "  " } }, { { "  " }, { "  " }, { "  " }, { "  " }, { "  " }, { "  " } } };
	int relative_value[30];
	int i, j;
	int daily_value[30];
	char graph_on[3] = {"▒"};
	char graph_off[3] = { "  " };
	int maxo;//그래프상의 최대값
	double temp;
	double selled_count = (game_point / 10);
	double selled_count_delta=1;//delta값은 0.96~1.16
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
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");//81~100
		printf("■                                                                        ■\n");//65~80
		printf("■                                                                        ■\n");//49~64
		printf("■                                                                        ■\n");//33~48
		printf("■                                                                        ■\n");//17~32
		printf("■                                                                        ■\n");//~16
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                          %s를 판매중입니다.                ", pj_name);
		alignment(strlen(pj_name));
		printf("              ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■      %s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s      ■\n", graph[0][5], graph[1][5], graph[2][5], graph[3][5], graph[4][5], graph[5][5], graph[6][5], graph[7][5], graph[8][5], graph[9][5], graph[10][5], graph[11][5], graph[12][5], graph[13][5], graph[14][5], graph[15][5], graph[16][5], graph[17][5], graph[18][5], graph[19][5], graph[20][5], graph[21][5], graph[22][5], graph[23][5], graph[24][5], graph[25][5], graph[26][5], graph[27][5], graph[28][5], graph[29][5]);
		printf("■      %s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s      ■\n", graph[0][4], graph[1][4], graph[2][4], graph[3][4], graph[4][4], graph[5][4], graph[6][4], graph[7][4], graph[8][4], graph[9][4], graph[10][4], graph[11][4], graph[12][4], graph[13][4], graph[14][4], graph[15][4], graph[16][4], graph[17][4], graph[18][4], graph[19][4], graph[20][4], graph[21][4], graph[22][4], graph[23][4], graph[24][4], graph[25][4], graph[26][4], graph[27][4], graph[28][4], graph[29][4]);
		printf("■      %s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s      ■\n", graph[0][3], graph[1][3], graph[2][3], graph[3][3], graph[4][3], graph[5][3], graph[6][3], graph[7][3], graph[8][3], graph[9][3], graph[10][3], graph[11][3], graph[12][3], graph[13][3], graph[14][3], graph[15][3], graph[16][3], graph[17][3], graph[18][3], graph[19][3], graph[20][3], graph[21][3], graph[22][3], graph[23][3], graph[24][3], graph[25][3], graph[26][3], graph[27][3], graph[28][3], graph[29][3]);
		printf("■      %s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s      ■\n", graph[0][2], graph[1][2], graph[2][2], graph[3][2], graph[4][2], graph[5][2], graph[6][2], graph[7][2], graph[8][2], graph[9][2], graph[10][2], graph[11][2], graph[12][2], graph[13][2], graph[14][2], graph[15][2], graph[16][2], graph[17][2], graph[18][2], graph[19][2], graph[20][2], graph[21][2], graph[22][2], graph[23][2], graph[24][2], graph[25][2], graph[26][2], graph[27][2], graph[28][2], graph[29][2]);
		printf("■      %s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s      ■\n", graph[0][1], graph[1][1], graph[2][1], graph[3][1], graph[4][1], graph[5][1], graph[6][1], graph[7][1], graph[8][1], graph[9][1], graph[10][1], graph[11][1], graph[12][1], graph[13][1], graph[14][1], graph[15][1], graph[16][1], graph[17][1], graph[18][1], graph[19][1], graph[20][1], graph[21][1], graph[22][1], graph[23][1], graph[24][1], graph[25][1], graph[26][1], graph[27][1], graph[28][1], graph[29][1]);
		printf("■      %s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s      ■\n", graph[0][0], graph[1][0], graph[2][0], graph[3][0], graph[4][0], graph[5][0], graph[6][0], graph[7][0], graph[8][0], graph[9][0], graph[10][0], graph[11][0], graph[12][0], graph[13][0], graph[14][0], graph[15][0], graph[16][0], graph[17][0], graph[18][0], graph[19][0], graph[20][0], graph[21][0], graph[22][0], graph[23][0], graph[24][0], graph[25][0], graph[26][0], graph[27][0], graph[28][0], graph[29][0]);//가로 30개.하루에 한줄씩(한줄==1.5sec),250마다 한칸이 채워진다
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                           총 판매량: %d                     ", total_selled);
		alignment(digiter(total_selled));
		printf("             ■\n");
		printf("■                                                                        ■\n");
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
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
	//키워드:(그래프;시간 :(증가율:(delta로 처리?),(비 누적계)))
	//->변화량값을 조정하는것으로. 그래프는 주식에서의 연착륙 그래프를 모델로 한다.
	return 0;
}
int recruit()//직원 채용의 첫 페이즈로써 로딩하는 화면 이후 무작위 3개의 worker_num을 불러온다.*아직은 남은 인원이 2명 이하일때의 예외처리가 안되어 있지만, 이부분을 if 문으로 처리하면 될 듯 하다
{
		char choosing[5][3] = { { "↑" }, { "" }, { "" }, { "" } };
	int menu_num = 0;
	int recruit_chosen[3];
	int i, j;
	for (i = 0; i <= 5; i++)
	{

		system("cls");
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                        회사를 홍보중입니다....\t                  ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(100);
		system("cls");
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                        회사를 홍보중입니다.   \t                  ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(100);
		system("cls");
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                        회사를 홍보중입니다..  \t                  ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(100);
		system("cls");
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                        회사를 홍보중입니다... \t                  ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(100);
		system("cls");
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                        회사를 홍보중입니다....\t                  ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
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
				if (recruit_chosen[i] == recruit_chosen[j])//중복예외처리문구
				{
					i--;//중복되면 함더돌아
				}
			}
			else
			{
				i--;//해당구역의 enabler가 1이면 함더돌아...긍데 arr[]엨읔엨ㅇ엨
			}
		}
	}
	for (i = 0; i <= 2; i++)
	{
		system("cls");
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                    지원서류를 처리중입니다....\t                  ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(100);
		system("cls");
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                    지원서류를 처리중입니다.   \t                  ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(100);
		system("cls");
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                    지원서류를 처리중입니다..  \t                  ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(100);
		system("cls");
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                    지원서류를 처리중입니다... \t                  ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(100);
		system("cls");
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                    지원서류를 처리중입니다....\t                  ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(100);
	}

	while (1)
	{
		digiter(money);
		system("cls");
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		printf("■                                                                        ■\n");
		printf("■                   다음과 같은 인재들이 모였습니다!                     ■\n");
		printf("■                        누구를 채용하시겠습니까?                        ■\n");
		printf("■                                                                        ■\n");
		printf("■ 현재 자산: %d                             ", money);
		alignment(digiter(money));
		printf("                               ■\n");
		printf("■                                                                        ■\n");
		printf("■                 %s                    ", system_message);
		alignment(strlen(system_message));
		printf("                                   ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■ 이름:      %s\t            %s\t\t    %s\t  ■\n", worker_name[recruit_chosen[0]], worker_name[recruit_chosen[1]], worker_name[recruit_chosen[2]]);
		printf("■                                                                        ■\n");
		printf("■ 프로그래밍:    %d\t\t\t%d\t\t\t%d\t  ■\n", programming[recruit_chosen[0]], programming[recruit_chosen[1]], programming[recruit_chosen[2]]);
		printf("■                                                                        ■\n");
		printf("■ 그래픽:        %d\t\t\t%d\t\t\t%d\t  ■\n", graphic[recruit_chosen[0]], graphic[recruit_chosen[1]], graphic[recruit_chosen[2]]);
		printf("■                                                                        ■\n");
		printf("■ 사운드:        %d\t\t\t%d\t\t\t%d\t  ■\n", sound[recruit_chosen[0]], sound[recruit_chosen[1]], sound[recruit_chosen[2]]);
		printf("■                                                                        ■\n");
		printf("■ 비용:          %d\t\t\t%d\t\t\t%d\t  ■\n", recruit_cost[recruit_chosen[0]], recruit_cost[recruit_chosen[1]], recruit_cost[recruit_chosen[2]]);
		printf("■                                                                        ■\n");
		printf("■	   \t%s\t\t\t%s\t\t\t%s\t  ■\n", choosing[0], choosing[1], choosing[2]);
		printf("■                                                                        ■\n");
		printf("■                             %s돌아가기     \t                          ■\n", choosing[3]);
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
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
void recruited(int called_num)// 성공 이후의 애니메이션을 재생하는 함수.
{
	int i = 0;
	while (i<10)
	{
		system("cls");
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                         '     '     '                                  ■\n");
		printf("■                    '                     '                             ■\n");
		printf("■                                             '                          ■\n");
		printf("■                .                                                       ■\n");
		printf("■                   %s이(가) 채용되었습니다!.                      ■\n", worker_name[called_num]);
		printf("■                .                                                       ■\n");
		printf("■                                               .                        ■\n");
		printf("■	             .  \"%s\"                            ■\n", upgrade_message[called_num]);
		printf("■                                             .                          ■\n");
		printf("■                       .     .       .    .                             ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(100);
		system("cls");
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                         .     .     .                                  ■\n");
		printf("■                    .                     .                             ■\n");
		printf("■                                             .                          ■\n");
		printf("■                '                                                       ■\n");
		printf("■                   %s이(가) 채용되었습니다!'                      ■\n", worker_name[called_num]);
		printf("■                '                                                       ■\n");
		printf("■                                               '                        ■\n");
		printf("■	             '  \"%s\"                            ■\n", upgrade_message[called_num]);
		printf("■                                             '                          ■\n");
		printf("■                       '     '       '    '                             ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(100);
		i++;
	}
	enabler[called_num] = 1;
	worker_count++;
	able_cruit_num--;
}
void cruit_upgrade_select()//교육할 직원을 선택하는 창.
{
	int upgrade_confirmed=0;
	int what_num_you_choosed = -1;
	int taken[13] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };//목록으로 '가져와진' 직원의 번호(worker_num을 참조.).//아래의 반복문이 끝나면 내가 가지고 있는 직원들의 '번호'명.
	char selected[16][3] = { "->", "\0", "\0", "\0", "\0", "\0", "\0", "\0", "\0", "\0", "\0", "\0", "\0", "\0", "\0", "\0" };//화살표 그래픽을 위한 
	int i, j;
	int menu_num = 0;//메뉴 이동시 필요한 변수
	int able_to_work = 0;//직원 채택 목록을 채우기위해 쓰는 변수. 아래의 루프가 끝나면 아마 총 가용인원일것이다.
	
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
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■  <SYSTEM>  %s                              ", system_message);
		alignment(strlen(system_message));
		printf("                              ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                      교육시킬 직원을 선택해주세요                      ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■     %s%s  \t%s%s  \t%s%s  \t%s%s  \t  ■\n", selected[0], list_of_cruit[0], selected[1], list_of_cruit[1],  selected[2], list_of_cruit[2],  selected[3], list_of_cruit[3] );
		printf("■     비용:%d\t         %d\t           %d\t            %d\t          ■\n", upgrading_cost[taken[0]], upgrading_cost[taken[1]], upgrading_cost[taken[2]], upgrading_cost[taken[3]]);
		printf("■     %s%s  \t%s%s  \t%s%s  \t%s%s  \t  ■\n", selected[4], list_of_cruit[4], selected[5], list_of_cruit[5], selected[6], list_of_cruit[6], selected[7], list_of_cruit[7] );
		printf("■     비용:%d\t         %d\t           %d\t            %d\t          ■\n", upgrading_cost[taken[4]], upgrading_cost[taken[5]], upgrading_cost[taken[6]], upgrading_cost[taken[7]]);
		printf("■     %s%s  \t%s%s  \t%s%s  \t%s%s  \t  ■\n", selected[8], list_of_cruit[8], selected[9], list_of_cruit[9], selected[10], list_of_cruit[10],  selected[11], list_of_cruit[11]);
		printf("■     비용:%d\t         %d\t           %d\t            %d\t          ■\n", upgrading_cost[taken[8]], upgrading_cost[taken[9]], upgrading_cost[taken[10]], upgrading_cost[taken[11]]);
		printf("■                                                                        ■\n");
		printf("■      %s 뒤로\t                                                          ■\n", selected[12]);
		printf("■                                                                        ■\n");
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");

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
					strcpy(system_message, system_message_init);//시스템메세지 초기화
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
			printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
			printf("■                                                                        ■\n");
			printf("■                                                                        ■\n");
			printf("■                                                                        ■\n");
			printf("■                                                                        ■\n");
			printf("■                                                                        ■\n");
			printf("■                                                                        ■\n");
			printf("■                                                                        ■\n");
			printf("■                                                                        ■\n");
			printf("■                                                                        ■\n");
			printf("■                                                                        ■\n");
			printf("■                   %s의 교육에 실패했습니다!...                   ■\n", worker_name[what_num_you_choosed]);
			printf("■                                                                        ■\n");
			printf("■                                                                        ■\n");
			printf("■	                                                                      ■\n");
			printf("■                                                                        ■\n");
			printf("■                                                                        ■\n");
			printf("■                                                                        ■\n");
			printf("■                                                                        ■\n");
			printf("■                                                                        ■\n");
			printf("■                                                                        ■\n");
			printf("■                                                                        ■\n");
			printf("■                                                                        ■\n");
			printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
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
			printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
			printf("■                                                                        ■\n");
			printf("■                                                                        ■\n");
			printf("■                                                                        ■\n");
			printf("■                                                                        ■\n");
			printf("■                                                                        ■\n");
			printf("■                              .     .                                   ■\n");
			printf("■                        '                .                              ■\n");
			printf("■                     '                                                  ■\n");
			printf("■                  .                            .                        ■\n");
			printf("■                     %s이(가) 성장했습니다!  '                    ■\n", worker_name[what_num_you_choosed]);
			printf("■                                                                        ■\n");
			printf("■                  .                              .                      ■\n");
			printf("■	                  \"%s\"                          ■\n", upgrade_message[what_num_you_choosed]);
			printf("■                     .                       .                          ■\n");
			printf("■                           .      .      .                              ■\n");
			printf("■                                                                        ■\n");
			printf("■          프로그래밍:   %d        ->        %d            ", pg_temp, programming[what_num_you_choosed]);
			alignment(digiter(pg_temp) + digiter(programming[what_num_you_choosed]));
			printf("                  ■\n");
			printf("■                                                                        ■\n");
			printf("■              그래픽:   %d        ->        %d            ", gp_temp, graphic[what_num_you_choosed]);
			alignment(digiter(gp_temp)+digiter(graphic[what_num_you_choosed]));
			printf("                  ■\n");
			printf("■                                                                        ■\n");
			printf("■              사운드:   %d        ->        %d            ", sd_temp, sound[what_num_you_choosed]);
			alignment(digiter(sd_temp)+digiter(sound[what_num_you_choosed]));
			printf("                  ■\n");
			printf("■                                                                        ■\n");
			printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
			Sleep(300);
			;
			i++;
		}
		
	}
	
}

void pausing()//메뉴4번의 액티비티.
{
	int i;
	int pause_start=(clock()/CLOCKS_PER_SEC);
	int pause_end;
	
	while (1)
	{
		system("cls");
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                   - ⓟ * ⓐ * ⓤ * ⓢ * ⓔ * ⓓ -                      ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                      아무 키나 눌러 해제합니다                         ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(100);
		key = getch();
		if (key > 0)
			break;
	}
	loading();
	pause_end = clock() / CLOCKS_PER_SEC;
	paused_time += (pause_end - pause_start);
}

void main()//메인메뉴 출력.
{
	system("pause");
	int is_not_count, i, menu_num = 1, j, toy_num,year_temp,month_temp;
	slide_down_animation();
	start();
	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                     당신의 회사의 이름을 정해주세요:                   ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	gets(company_name);
	fflush(stdin);
	system("pause");
	loading();
	is_not_count = clock() / CLOCKS_PER_SEC;
	//아래가 메인프레임
	while (10800 > ((clock() / CLOCKS_PER_SEC) - (is_not_count+paused_time)))//계획서에는 10분짜리 게임이었지만, 플레이시간 총 3시간으로 변경.
	{
		
		system("cls");
		year = ((clock() / CLOCKS_PER_SEC) - (is_not_count + paused_time)) / 540;
		month = ((((clock() / CLOCKS_PER_SEC) - (is_not_count + paused_time) % 540) / 45)%12)+1;
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		printf("■ 회사명: %s                               ", company_name);
		alignment(strlen(company_name));
		printf("                                ■\n");
		printf("■ 추가 채용 가능 인원: %d                                                  ", able_cruit_num);
		alignment(digiter(able_cruit_num));
		printf("■\n");
		printf("■ 회사 레벨: %d          ", company_lv);
		alignment(digiter(company_lv));
		printf("                                                  ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■                                          ／ㅣ、                        ■\n");
		printf("■                                         (˚、。7                       ■\n");
		printf("■                                          ＼    ~                       ■\n");
		printf("■                                           l、   ＼                     ■\n");
		printf("■                                           じしf_,)ノ                   ■\n");
		printf("■ <SYSTEM>                                                               ■\n");
		printf("■ %s                                       ", system_message);alignment(strlen(system_message));printf("                                ■\n");
		printf("■                                                                        ■\n");
		printf("■                                                                        ■\n");
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		//}
		if (menu_num == 1)
		{
			printf("■                                    ■ 1. 게임 개발   ■ 2. 직원 채용   ■\n");
			printf("■   회사 자본:%d              ", money);
			alignment(digiter(money));
			printf("         ■****************■                ■\n");
			printf("■   직원 수:  %d      ", worker_count);
			alignment(digiter(worker_count));
			printf("                 ■■■■■■■■■■■■■■■■■■■\n");
			printf("■   운영 연수:%d년     %d개월       ", year, month);
			alignment(digiter(year) + digiter(month));
			printf("     ■ 3. 직원 교육   ■ 4. 일시 정지   ■\n", year);
			printf("■                                    ■                ■                ■\n");
		}
		else if (menu_num == 2)
		{
			printf("■                                    ■ 1. 게임 개발   ■ 2. 직원 채용   ■\n");
			printf("■   회사 자본:%d              ", money);
			alignment(digiter(money));
			printf("         ■                ■****************■\n");
			printf("■   직원 수:  %d      ", worker_count);
			alignment(digiter(worker_count));
			printf("                 ■■■■■■■■■■■■■■■■■■■\n");
			printf("■   운영 연수:%d년     %d개월       ", year, month);
			alignment(digiter(year) + digiter(month));
			printf("     ■ 3. 직원 교육   ■ 4. 일시 정지   ■\n", year);
			printf("■                                    ■                ■                ■\n");
		}
		else if (menu_num == 3)
		{
			printf("■                                    ■ 1. 게임 개발   ■ 2. 직원 채용   ■\n");
			printf("■   회사 자본:%d              ", money);
			alignment(digiter(money));
			printf("         ■                ■                ■\n");
			printf("■   직원 수:  %d      ", worker_count);
			alignment(digiter(worker_count));
			printf("                 ■■■■■■■■■■■■■■■■■■■\n");
			printf("■   운영 연수:%d년     %d개월       ", year, month);
			alignment(digiter(year) + digiter(month));
			printf("     ■ 3. 직원 교육   ■ 4. 일시 정지   ■\n", year);
			printf("■                                    ■****************■                ■\n");
		}
		else if (menu_num == 0)
		{
			printf("■                                    ■ 1. 게임 개발   ■ 2. 직원 채용   ■\n");
			printf("■   회사 자본:%d              ", money);
			alignment(digiter(money));
			printf("         ■                ■                ■\n");
			printf("■   직원 수:  %d      ", worker_count);
			alignment(digiter(worker_count));
			printf("                 ■■■■■■■■■■■■■■■■■■■\n");
			printf("■   운영 연수:%d년     %d개월       ", year, month);
			alignment(digiter(year) + digiter(month));
			printf("     ■ 3. 직원 교육   ■ 4. 일시 정지   ■\n", year);
			printf("■                                    ■                ■****************■\n");
		}
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");

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
					for (i = 0; i < 12; i++)//스태미나 리젠 체크 initialize
					{
						stamina_regen_chk[i] = 0;
					}
				}
			}
	}
	else
	{
	}
	//아래는 스태미나 리젠
	for (i = 0; i < month; i++)//월
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
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                   끝까지 플레이해주셔서 감사합니다.                    ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                      총 직원 수: %d                  ",worker_count);
	alignment(digiter(worker_count));
	printf("                    ■\n");
	printf("■                                                                        ■\n");
	printf("■                         총 자산: %d                  ",total_money);
	alignment(digiter(total_money));
	printf("                  ■\n");
	printf("■                                                                        ■\n");
	printf("■              총 개발한 프로젝트: %d                  ", game_name_log_count+1);
	alignment(digiter(game_name_log_count + 1));
	printf("                  ■\n");
	printf("■                                                                        ■\n");
	printf("■                                                                        ■\n");
	printf("■                            총 점수: %d                  ",(worker_count*100)+(money*10)+((game_name_log_count+1)*150));
	alignment((digiter((worker_count * 100) + (money * 10) + ((game_name_log_count + 1) * 150))));
	printf("                               ■\n");
	printf("■                                                                        ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
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