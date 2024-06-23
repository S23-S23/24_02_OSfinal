#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>      
#include<conio.h>        
#include<Windows.h>   
#include<time.h>        
#include<stdlib.h>     
#include<stdbool.h>
#include <string.h>
#include <mmsystem.h>

#pragma comment(lib,"winmm.lib")

// 전투기 구조체
typedef struct {
	char name[50];
	float max_speed;
	float radar_range;
	int num_flares;
	int num_missiles;
	int num_bullets;
	float generation;
	char engine_model[50];
	char country_of_origin[50];
	char role[50];
} Fighter;

// 연결리스트
typedef struct Node {
	Fighter fighter;
	struct Node* next;
} Node;

Node* head = NULL;
//extern Node* head;

// 함수 선언
Node* createNode(Fighter fighter);
void addFighter(Node** head, Fighter fighter);
void printAllFighters(Node* head);
Node* searchFighter(Node* head, const char* search_term);
void sortFighters(Node** head, int criteria);
void swap(Node* a, Node* b);
void managingFighters();
void search();
void managingList();
void userAddFighter();
void goodSpace() { printf("                                                                 "); }
void goodEnter() { printf("\n\n\n\n"); }
void Typhoon(Fighter f);
void F_14(Fighter f);
void F_16(Fighter f);
void F_18(Fighter f);
void F_35(Fighter f);
void Su_27(Fighter f);
void DarkStar(Fighter f);

void dogFight();

void mainMenu() {
	goodEnter(); goodEnter(); goodSpace();
	printf("AirForce Listing\n");
	goodEnter(); goodSpace();
	printf("Select the menu\n");
	goodEnter(); goodSpace();
	printf("1. Managing Fighters\n");
	goodSpace(); printf("2. DogFight\n");
}
void managingList() {
	system("cls");
	goodEnter(); goodEnter(); goodSpace();
	printf("Managing Fighters\n");
	goodEnter(); goodSpace();
	printf("Select the menu\n");
	goodEnter(); goodSpace();
	printf("1. Add Fighters\n");
	goodSpace(); printf("2. Print Fighters\n");
}

void search() {
	char search_term[50];
	printf("Enter the fighter name: ");
	if (fgets(search_term, sizeof(search_term), stdin) != NULL) {
		search_term[strcspn(search_term, "\n")] = 0;
	}
	else {
		printf("Error reading input\n");
		return;
	}

	Node* found = searchFighter(head, search_term);
	if (found != NULL) {
		printf("\nFighter with name %s found:\n", search_term);
		Fighter f = found->fighter;
		if (strcmp(search_term, "F-14") == 0) {
			F_14(f);
		}
		else if (strcmp(search_term, "F-35") == 0) {
			F_35(f);
		}
		else if (strcmp(search_term, "Eurofighter Typhoon") == 0) {
			Typhoon(f);
		}
		else if (strcmp(search_term, "F-16") == 0) {
			F_16(f);
		}
		else if (strcmp(search_term, "F-18") == 0) {
			F_18(f);
		}
		else if (strcmp(search_term, "Su-27") == 0) {
			Su_27(f);
		}
		else if (strcmp(search_term, "DarkStar") == 0) {
			DarkStar(f);
		}
		else {
			printf("Name: %s\nMax Speed: %.1f\nRadar Range: %.2f\nFlares: %d\nMissiles: %d\nBullets: %d\nGeneration: %.1f\nEngine: %s\nCountry: %s\nRole: %s\n",
				f.name, f.max_speed, f.radar_range, f.num_flares, f.num_missiles, f.num_bullets,
				f.generation, f.engine_model, f.country_of_origin, f.role);
		}
	}
	else {
		printf("\nFighter with name %s not found.\n", search_term);
	}
}

void mFprint() {
	system("cls");

	goodEnter();
	printf("                        The fighters currently registered are as follows :\n");
	goodEnter();
	printAllFighters(head);
	goodEnter();
	printf(" Select your henceforth:\n");
	printf(" 0. refresh\n 1. add Fighter\n 2. search Fighter\n\n");
	printf(" Q. sort by name            W. Sort by speed            E. Sort by generation\n\n");
}

void managingFighters() {
	system("cls");

	goodEnter();
	printf("                        The fighters currently registered are as follows :\n");
	goodEnter();
	printAllFighters(head);
	goodEnter();
	printf(" Select your henceforth:\n");
	printf(" 0. refresh\n 1. add Fighter\n 2. search Fighter\n\n");
	printf(" Q. sort by name            W. Sort by speed            E. Sort by generation\n\n");

	bool mFmenu = 1;
	while (mFmenu)
	{
		char mFmenu_select;
		scanf(" %c", &mFmenu_select);

		while (getchar() != '\n');

		switch (mFmenu_select) {
		case '0':
			mFprint();
			break;
		case '1':
			userAddFighter();
			mFprint();
			break;
		case '2':
			search();
			break;
		case 'Q':
		case 'q':
			sortFighters(&head, 1); // Sort by name
			mFprint();
			break;
		case 'W':
		case 'w':
			sortFighters(&head, 2); // Sort by speed
			mFprint();
			break;
		case 'E':
		case 'e':
			sortFighters(&head, 3); // Sort by generation
			mFprint();
			break;
		case ';':
			mFmenu = 0;
			break;
		default:
			printf("Invalid selection. Please try again.\n");
			break;
		}
	}
}

void defaultFighters() {
	// Adding example fighters
	Fighter f1 = { "F-14", 2485.0, 313.964, 4, 6, 256, 4, "General Electric F110", "USA", "Multirole" };
	Fighter f2 = { "F-35", 1975.0, 201.168, 8, 8, 480, 5, "Pratt & Whitney F119", "USA", "Air Superiority" };
	Fighter f3 = { "Su-27", 2500.0, 305.775, 6, 10, 500, 4, "Saturn AL-31F", "Russia", "Air Superiority" };
	Fighter f4 = { "Eurofighter Typhoon", 2495.0, 289.681, 6, 8, 400, 4.5, "Eurojet EJ200", "Europe", "Multirole" };
	Fighter f5 = { "F-16", 2414.0, 193.121, 4, 6, 400, 4, "General Electric F110", "USA", "Multirole" };
	Fighter f6 = { "F-18", 1915.0, 241.401, 4, 8, 450, 4, "General Electric F404", "USA", "Multirole" };
	Fighter f7 = { "DarkStar", 12348.0, 241.401, 8, 10, 1000, 100, "Turbojet&Ramjet", "USA", "high-speed reconnaissance" };

	addFighter(&head, f1);
	addFighter(&head, f2);
	addFighter(&head, f3);
	addFighter(&head, f4);
	addFighter(&head, f5);
	addFighter(&head, f6);
	addFighter(&head, f7);
}

int main() {
	system("mode con:cols=150 lines=50");
	system("color f0");
	defaultFighters();
	mainMenu();

	bool bmain = true;
	while (bmain == true)
	{
		int main_select = 0;
		scanf("%d", &main_select);
		switch (main_select)
		{
		case 1:
			managingFighters();
			break;
		case 2:
			dogFight();
			break;
		case 3:
			bmain = false;
		default:
			break;
		}
	}

	int criteria = 1; // Sorting by max speed
	sortFighters(&head, criteria);
	printf("\nFighters sorted by max speed:\n");
	printAllFighters(head);
	return 0;
}

Node* createNode(Fighter fighter) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->fighter = fighter;
	newNode->next = NULL;
	return newNode;
}

void addFighter(Node** head, Fighter fighter) {
	Node* newNode = createNode(fighter);
	newNode->next = *head;
	*head = newNode;
}

void printAllFighters(Node* head) {
	printf(" %-25s %-20s %-20s %-10s %-10s %-10s %-20s %-25s\n",
		"Name", "Max Speed[km/h]", "Radar Range[km]", "Flares", "Missiles", "Bullets", "Generation[th]", "Role");
	printf("==============================================================================================================================================\n");
	Node* current = head;
	while (current != NULL) {
		Fighter f = current->fighter;
		printf(" %-25s %-20.1f %-20.2f %-10d %-10d %-10d %-20.1f %-25s\n",
			f.name, f.max_speed, f.radar_range, f.num_flares, f.num_missiles, f.num_bullets,
			f.generation, f.role);
		current = current->next;
	}
}

Node* searchFighter(Node* head, const char* search_term) {
	Node* current = head;
	while (current != NULL) {
		if (strcmp(current->fighter.name, search_term) == 0) {
			return current;
		}
		current = current->next;
	}
	return NULL;
}

void sortFighters(Node** head, int criteria) {
	if (*head == NULL) return;

	Node* current;
	Node* nextNode;
	int swapped;

	do {
		swapped = 0;
		current = *head;

		while (current->next != NULL) {
			nextNode = current->next;

			int compare = 0;
			switch (criteria) {
			case 1: // Name
				compare = strcmp(current->fighter.name, nextNode->fighter.name) > 0;
				break;
			case 2: // Max Speed
				compare = current->fighter.max_speed < nextNode->fighter.max_speed;
				break;
			case 3: // Generation
				compare = current->fighter.generation < nextNode->fighter.generation;
				break;
			}

			if (compare) {
				swap(current, nextNode);
				swapped = 1;
			}
			current = current->next;
		}
	} while (swapped);
}


void swap(Node* a, Node* b) {
	Fighter temp = a->fighter;
	a->fighter = b->fighter;
	b->fighter = temp;
}

void userAddFighter() {
	Fighter newFighter;

	printf("Enter fighter name: ");
	fgets(newFighter.name, sizeof(newFighter.name), stdin);
	newFighter.name[strcspn(newFighter.name, "\n")] = 0;

	printf("Enter max speed: ");
	scanf("%f", &newFighter.max_speed);

	printf("Enter radar range: ");
	scanf("%f", &newFighter.radar_range);

	printf("Enter number of flares: ");
	scanf("%d", &newFighter.num_flares);

	printf("Enter number of missiles: ");
	scanf("%d", &newFighter.num_missiles);

	printf("Enter number of bullets: ");
	scanf("%d", &newFighter.num_bullets);

	printf("Enter generation [th]: ");
	scanf("%f", &newFighter.generation);

	while (getchar() != '\n');

	printf("Enter engine model: ");
	fgets(newFighter.engine_model, sizeof(newFighter.engine_model), stdin);
	newFighter.engine_model[strcspn(newFighter.engine_model, "\n")] = 0; // Remove newline character

	printf("Enter country of origin: ");
	fgets(newFighter.country_of_origin, sizeof(newFighter.country_of_origin), stdin);
	newFighter.country_of_origin[strcspn(newFighter.country_of_origin, "\n")] = 0; // Remove newline character

	printf("Enter role: ");
	fgets(newFighter.role, sizeof(newFighter.role), stdin);
	newFighter.role[strcspn(newFighter.role, "\n")] = 0; // Remove newline character

	addFighter(&head, newFighter);

	printf("Addition complete!\n");
	return;
}
void Typhoon(Fighter f) {
	printf("Name: %s\nMax Speed: %.1f\nRadar Range: %.2f\nFlares: %d\nMissiles: %d\nBullets: %d\nGeneration: %.1f\nEngine: %s\nCountry: %s\nRole: %s\n",
		f.name, f.max_speed, f.radar_range, f.num_flares, f.num_missiles, f.num_bullets,
		f.generation, f.engine_model, f.country_of_origin, f.role);
	printf("\n\n유로파이터 타이푼(영어: Eurofighter Typhoon)은 1983년에 발족한 유럽국들의 컨소시엄에 의해 설계되고 제작된, 매우 민첩한 쌍발엔진의 다목적 선미익-삼각익(canard-delta wing) 4.5세대 전투기입니다.\n");
	printf("기술적 특징: 쌍발 엔진: 두 개의 Eurojet EJ200 터보팬 엔진을 장착하여 높은 추력과 기동성을 제공합니다.\n");
	printf("스텔스 기술: 레이더 반사 면적(RCS)을 줄이기 위한 설계가 적용되어 있지만, 완전한 스텔스 전투기는 아닙니다.\n");
	printf("디지털 플라이-바이-와이어 시스템: 비행 제어 시스템이 디지털화되어 조종 안정성을 높이고 조종사의 부담을 줄여줍니다.\n");
	printf("다목적 역할: 공대공 전투, 공대지 공격, 정찰 등 다양한 임무를 수행할 수 있습니다.\n");
	printf("공대공 미사일: AIM-120 AMRAAM, IRIS-T, MBDA Meteor, 공대지 무기: AGM-65 Maverick, Storm Shadow, Paveway 시리즈, 기관포: Mauser BK-27 27mm 기관포\n");
}

void F_14(Fighter f) {
	printf("Name: %s\nMax Speed: %.1f\nRadar Range: %.2f\nFlares: %d\nMissiles: %d\nBullets: %d\nGeneration: %.1f\nEngine: %s\nCountry: %s\nRole: %s\n",
		f.name, f.max_speed, f.radar_range, f.num_flares, f.num_missiles, f.num_bullets,
		f.generation, f.engine_model, f.country_of_origin, f.role);
	printf("\n\nF-14 전투기는 미국의 Grumman Aerospace에서 개발한 고성능의 공중전 전투기입니다. 이 비행기는 1970년대에 처음 개발되어 미국 해군과 해군 함정에서 주력 전투기로 사용되었습니다.\n");
	printf("다음은 F-14의 주요 특징입니다. : \n");
	printf("설계 및 특징: F-14는 큰 날개폭과 이중 엔진 구조를 가지고 있습니다. 이 날개는 기동성과 비행 안정성을 높이는 데 기여했습니다.기본적으로 전투기와 함께 다목적 임무를 수행할 수 있도록 설계되었으며, 고도의 전투 능력을 가졌습니다.\n");
	printf("무기 시스템 : F-14은 AIM-54 필닉스 중거리 공중-공중 미사일을 주 무기로 사용했습니다. 이는 고도의 사거리와 강력한 타격력을 자랑합니다.\n");
	printf("운용 및 역사: F-14은 미국 해군과 이란 제국 해군에서 활용되었으며, 주로 고속과 높은 기동성을 요구하는 임무를 담당했습니다. 특히, 1980년대의 이란-이라크 전쟁에서 이란 공군이 F-14를 사용하여 전투력을 발휘했습니다.\n");
	printf("퇴역 및 후속 기종: F-14은 2006년에 미 해군에서 정식으로 퇴역하였으며, 후속 기종으로 F/A-18 호넷이나 F/A-18E/F 수퍼 호넷이 도입되었습니다.\n");
}

void F_16(Fighter f) {
	printf("Name: %s\nMax Speed: %.1f\nRadar Range: %.2f\nFlares: %d\nMissiles: %d\nBullets: %d\nGeneration: %.1f\nEngine: %s\nCountry: %s\nRole: %s\n",
		f.name, f.max_speed, f.radar_range, f.num_flares, f.num_missiles, f.num_bullets,
		f.generation, f.engine_model, f.country_of_origin, f.role);
	printf("\n\nF-16 파이팅 팰컨(F-16 Fighting Falcon)은 미국이 개발한 다목적 전투기로, 세계적으로 널리 사용되고 있는 기종입니다.\n");

	printf("개발 배경:1970년대 초 미 공군의 요구에 따라 경량 전투기로 개발되었고, 최초 비행은 1974년, 정식 도입은 1978년에 이루어졌습니다.\n");
	printf("기술적 특징 : 디지털 플라이-바이-와이어 시스템: 전자식 비행 제어 시스템을 도입하여 뛰어난 기동성과 안정성을 제공합니다.버블 캐노피: 시야 확보를 위해 큰 투명 캐노피를 사용하여 조종사의 시야를 극대화했습니다. \n");
	printf("무장: 공대공 미사일: AIM-9 사이드와인더, AIM-120 AMRAAM, 공대지 무기: AGM-65 매버릭, GBU-12 Paveway II,기관포: M61 벌컨 20mm 기관포");
}

void F_18(Fighter f) {
	printf("Name: %s\nMax Speed: %.1f\nRadar Range: %.2f\nFlares: %d\nMissiles: %d\nBullets: %d\nGeneration: %.1f\nEngine: %s\nCountry: %s\nRole: %s\n",
		f.name, f.max_speed, f.radar_range, f.num_flares, f.num_missiles, f.num_bullets,
		f.generation, f.engine_model, f.country_of_origin, f.role);
	printf("F/A-18 호넷(F/A-18 Hornet)은 1970년대 말 미 해군과 해병대의 요구에 따라 미국이 개발한 다목적 전투기입니다.\n");
	printf("기술적 특징: 두 개의 제너럴 일렉트릭 F404 터보팬 엔진을 장착하고 있습니다 (쌍발 엔진)\n");
	printf("4. 무장: 공대공 미사일: AIM-7 스패로우, AIM-120 AMRAAM, AIM-9 사이드와인더 등, 공대지 무기: AGM-84 하푼, AGM-88 HARM, 다양한 레이저 유도 폭탄 등, 기관포: M61 벌컨 20mm 기관포\n");
	printf("   공대지 무기: AGM-84 하푼, AGM-88 HARM, 다양한 레이저 유도 폭탄 등\n");
}

void F_35(Fighter f) {
	printf("Name: %s\nMax Speed: %.1f\nRadar Range: %.2f\nFlares: %d\nMissiles: %d\nBullets: %d\nGeneration: %.1f\nEngine: %s\nCountry: %s\nRole: %s\n",
		f.name, f.max_speed, f.radar_range, f.num_flares, f.num_missiles, f.num_bullets,
		f.generation, f.engine_model, f.country_of_origin, f.role);

	printf("\n\nF-35은 미국의 Lockheed Martin사가 개발한 다목적 스텔스 전투기입니다.\nF-35는 다음과 같은 특징을 가지고 있습니다: \n");
	printf("다목적성: F-35은 공중전, 지상전, 해상전을 포함한 다양한 임무를 수행할 수 있는 다목적 전투기입니다. 공중-공중, 공중-지상 미사일을 사용하여 다양한 임무를 수행할 수 있습니다.\n");
	printf("스텔스 기능: F-35은 스텔스 기능을 갖추어 레이더 감지를 어렵게 하며, 적의 방공시스템을 피할 수 있도록 설계되었습니다.\n");
	printf("다국적 참여: 미국을 비롯하여 영국, 호주, 네덜란드, 이탈리아 등 다수의 국가가 참여하여 개발에 기여하고 있으며, 여러 나라에서 운용 계획이 있습니다.\n");
	printf("현대적인 기능: 센서 통합, 네트워크 중심 작전 능력을 강화하여 정보를 실시간으로 공유하고 다른 플랫폼과 협력하여 임무를 수행할 수 있습니다.\n");
}

void Su_27(Fighter f) {
	printf("Name: %s\nMax Speed: %.1f\nRadar Range: %.2f\nFlares: %d\nMissiles: %d\nBullets: %d\nGeneration: %.1f\nEngine: %s\nCountry: %s\nRole: %s\n",
		f.name, f.max_speed, f.radar_range, f.num_flares, f.num_missiles, f.num_bullets,
		f.generation, f.engine_model, f.country_of_origin, f.role);
	printf("\n\n Su-27 플랭커(Su - 27 Flanker)는1970년대 초 소련의 항공 전력을 강화하기 위해 개발된 다목적 전투기입니다.\n");
	printf("기술적 특징 : 쌍발 엔진: 두 개의 리율카 알-31 터보팬 엔진을 장착하고 있습니다.\n");
	printf("              고기동성: 뛰어난 기동성을 제공하는 캔드(Canard)와 플라이-바이-와이어 시스템이 특징입니다.\n");
	printf("무기 : 공대공 미사일: R-27, R-73, R-77 등, 공대지 무기: Kh-31, Kh-59, 다양한 유도 폭탄 및 로켓 등, 기관포: GSh-30-1 30mm 기관포\n");
}

void DarkStar(Fighter f) {
	printf("Name: %s\nMax Speed: %.1f\nRole: %s\n",
		f.name, f.max_speed, f.role);
	printf("영화 [탑건: 매버릭]에서 등장하는 다크스타(Darkstar)는 가상의 극초음속 (마하 10) 항공기입니다.\n");
	printf("디자인은 실제 항공기인 SR-71 블랙버드와 SR-72의 디자인 요소를 반영하고 있습니다.\n");
}

////////////////////////////////////////////////////////전투기 리스팅 끝///////////////////////////////////////////////////////

////////////////////////////////////////////////도그파이트 시작///////////////////////////////////////////////////////////////

#define BLACK 0 //색깔 정의
#define BLUE1 1
#define GREEN1 2
#define CYAN1 3
#define RED1 4
#define MAGENTA1 5
#define YELLOW1 6
#define GRAY1 7
#define GRAY2 8
#define BLUE2 9
#define GREEN2 10
#define CYAN2 11
#define RED2 12
#define MAGENTA2 13
#define YELLOW2 14
#define WHITE 15 
///////////////////////////////////////// 이동
#define SPECIAL1 0XE0
#define SPECIAL2 0x00
#define SPACE 0x20
#define UP 0x48
#define DOWN 0x50
#define LEFT 0x4b
#define RIGHT 0x4d
int Delay = 10;
int frame_count = 0; //속도 조절용
int p1_frame_sync = 1; //플레이어 이동속도 (반비례)
int player_speed = 1;

#define WIDTH 140
#define HEIGHT 43

#define UX 75  //시작 유저의 x좌표
#define UY 40  //시작 유저의 y좌표

int called = 0;

int oldx = UX, oldy = UY; // 플레이어의 old 좌표
int newx = UX, newy = UY; //플레이어의 new 좌표
int keep_moving = 1;  //1:계속이동
////////////////////////////////////// 총알

int MAXBULLET = 6;
//#define MAXBULLET 6//플레이어의 최대 총알 수
#define TRUE 1
#define FALSE 0

struct Bullet {
	int exist;
	int x, y;
} *Bullet;


#define MAXMISSILE 1 //플레이어의 최대 미사일 수
int MissileUse = 7; //미사일 초마다 생성
int Missile_frame_sync = 30;  //미사일 속도조절
struct {
	int exist;
	int x, y;
}Missile[MAXMISSILE];

////////////////////////////////////// 적기
#define MAXENEMY 2
struct {
	int exist;
	int x, y;
	int number;
	int move;
	int type;
}Enemy[MAXENEMY];
char* Enemyunit[] = { "<=▼=>","<=♥=>","<=Y=>" };

///////////////////////////////////// 적 총알

#define MAXENEMYMISSILE 2 // 적 최대 미사일 수
int enemymissileuse = 2; //적 미사일 초마다 생성
int enemymissile_frame_sync = 70;  //적 미사일 속도조절
int enemy_frame_sync = 1; //적기 속도
struct {
	int exist;
	int x, y;
}EnemyMissile[MAXENEMYMISSILE];

//////////////////////////////////
int heart = 5;
int remain = 2;
int choise;
////////////////함수 정의 구간
void printDogFight();
void printIntro();
void gameRule();

void gamestart();
void init_game();
void playermove(unsigned char ch);
void playerdraw(int x, int y);
void playererase(int x, int y);

void DrawBullet(int i);
void EraseBullet(int i);
void bulletmove();

void showenemy();
void Enemymove();

void EnemyMissileMove();
void EnemyMissileshow();
void EnemyMissiledraw(int i);
void EnemyMissileerase(int i);

void Enemyfall();
void playerfall();
void info();
void setPlayerSpeed(int i);

void MissileDraw(int i);
void MissileErase(int i);
void MissileMove();
void MissileShow();
void chooseFight();
void cleanup_game();
/////////////////////////////


void textcolor(int fg_color, int bg_color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), fg_color | bg_color << 4);
}

void removeCursor(void) {
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	cursorInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void gotoxy(int x, int y) {
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void dogFight() {
	system("mode con:cols=150 lines=50");
	srand(time(NULL));
	removeCursor();
	system("cls");
	system("color f0");
	printDogFight();
	system("cls");
	printIntro();

	bool smain = true;
	while (smain == true)
	{
		int smain_select = 0;
		scanf("%d", &smain_select);
		switch (smain_select)
		{
		case 1:
			system("cls");
			chooseFight();
			gamestart();
			break;
		case 2:
			gameRule();
			break;
		default:
			break;
		}
	}
	cleanup_game();
	return;
}

void printDogFight() {
	gotoxy(30, 20); printf(" ________    ______   _______   _______  __    _______  __    __  .___________. __  \n");
	gotoxy(30, 21); printf("I        | /  __   | /   _____||   ____||  | /  _____| |  |  |  | |           ||  | \n");
	gotoxy(30, 22); printf("I  .--.  | |  |  | | |  I  __  |  |__   |  | |  |  __  |  |__|  | `---|  |----`|  | \n");
	gotoxy(30, 23); printf("I  |  |  | |  |  | | |  I I_ | I  __|   |  | |  | |_ | |   __   |     |  |     |  | \n");
	gotoxy(30, 24); printf("I  '--'  | |  `--' | |  I__| | |  |     |  | |  |__| | |  |  |  |     |  |     |__| \n");
	gotoxy(30, 25); printf("I_______/    ______/  _______| |__|     |__| |_______| |__|  |__|     |__|     (__) \n");
	gotoxy(60, 40); system("pause");
}

void printWin() {
	textcolor(MAGENTA2, WHITE);
	gotoxy(30, 20); printf("  ____    __    ____  __  .___   __.   __  \n");
	gotoxy(30, 21); printf(" ↘  ↘  / ↘  /   / |  | |  ↘ |   | |  | \n");
	gotoxy(30, 22); printf(" ↘   ↘/   ↘/   /  |  | |   ↘|   | |  | \n");
	gotoxy(30, 23); printf("  ↘             /   |  | |   . `   | |  | \n");
	gotoxy(30, 24); printf("   ↘    /↘    /    |  | |   |↘   | |__| \n");
	gotoxy(30, 25); printf("    ↘__/  ↘__/     |__| |___| ↘__| (__) \n");
}

void printLose() {
	textcolor(MAGENTA2, WHITE);
	gotoxy(30, 20); printf(" __        ______        _______.   _______  __  \n");
	gotoxy(30, 21); printf("|  |      /  __  ↘      /       | |   ____||  | \n");
	gotoxy(30, 22); printf("|  |     |  |  |  |    |   (----`  |  |__   |  | \n");
	gotoxy(30, 23); printf("|  |     |  |  |  |     ↘  ↘     |   __|  |  | \n");
	gotoxy(30, 24); printf("|  `----.|  `--'  | .----)   |     |  |____ |__| \n");
	gotoxy(30, 25); printf("|_______| ↘______/  |_______/     |_______|(__) \n");
}

void printIntro() {
	gotoxy(30, 5); printf("적기가 영토를 침범해왔습니다! 전투기 출격!!\n");
	gotoxy(30, 8); printf("1. Game start!\n");
	gotoxy(30, 9); printf("2. Game rule\n");
}

void gameRule() {
	printf("  이동 : 화살표\n");
	printf("  선택한 전투기의 스탯이 실제 게임 안에서 영향을 받습니다! (플레어, 미사일, 총알 수, 최대속도) \n");
	printf("  승리 조건 : 적을 성공적으로 제압합니다. (총알을 명중시키거나 7초에 한번 씩 충전되는 미사일로 처치하세요.)\n");
	printf("  패배 조건 : Flare가 0인 상태에서 미사일에 피격 당하면 패배합니다.\n");
	printf("  적군은 2초마다 빠른 속도로 유저에게 다가가는 2개의 미사일을 생성합니다. ");
}

void chooseFight() {
	gotoxy(50, 10);
	printf("Choose your Fight!\n");
	sortFighters(&head, 1);
	printAllFighters(head);
	printf("\n Select from above(0~6) \n");

	scanf("%d", &choise);
	switch (choise) //속도 목숨 미사일 총알
	{
	case 0:
		heart = 10;
		MissileUse = 3;
		MAXBULLET = 10;
		p1_frame_sync = 0;
	case 1: //유로파이터 
		heart = 6;
		MissileUse = 6;
		MAXBULLET = 3;
		p1_frame_sync = 2;
		break;
	case 2: //F-14
		heart = 4;
		MissileUse = 8;
		MAXBULLET = 2;
		p1_frame_sync = 3;
		break;
	case 3: //F-16
		heart = 4;
		MissileUse = 8;
		MAXBULLET = 3;
		p1_frame_sync = 4;
		break;
	case 4: //F-18
		heart = 4;
		MAXBULLET = 4;
		p1_frame_sync = 6;
		MissileUse = 6;
		break;
	case 5: //F-35
		heart = 8;
		MAXBULLET = 5;
		p1_frame_sync = 5;
		MissileUse = 6;
		break;
	case 6: //Su-27
		heart = 6;
		MissileUse = 5;
		p1_frame_sync = 1;
		MAXBULLET = 6;
		break;
	default:
		printf("0번부터 6번까지만 가능합니다.");
		break;
	}
}

void gamestart() {
	PlaySound(TEXT("DangerZone.wav"), NULL, SND_ASYNC | SND_LOOP);
	unsigned char ch = 0;
	init_game();
	int i;
	int player_speed = 1;
	int frame_counter = 0;

	while (1) {
		info();
		if (frame_count % enemy_frame_sync == 0) {
			showenemy();
			Enemymove();
			EnemyMissileshow();
			EnemyMissileMove();
			MissileShow();
			MissileMove();
			Enemyfall();
			playerfall();
		}
		gotoxy(0, 43); for (int i = 0; i < 149; i++) { textcolor(BLACK, WHITE); printf("─"); }
		if (_kbhit() == 1) {
			ch = _getch();
			if (ch == SPECIAL1 || ch == SPECIAL2) {
				ch = _getch();
				switch (ch) {
				case UP: case DOWN: case LEFT: case RIGHT:
					playermove(ch);
					if (frame_count % p1_frame_sync == 0)   playermove(0);
					break;
				default:
					if (frame_count % p1_frame_sync == 0)	playermove(0);
				}
			}
		}
		if (ch == SPACE) {
			for (i = 0; i < MAXBULLET && Bullet[i].exist == TRUE; i++) {}
			if (i != MAXBULLET) {
				Bullet[i].x = newx + 1;
				Bullet[i].y = newy - 1;
				Bullet[i].exist = TRUE;
			}
		}
		bulletmove();
		Sleep(25);
		frame_count++;
	}
}

void init_game() {
	system("cls");
	removeCursor();
	// Initialize two enemies
	for (int i = 0; i < 2; i++) {
		Enemy[i].exist = TRUE;
		Enemy[i].x = (i == 0) ? 5 : 55; // Positions on left and right
		Enemy[i].y = 1 + rand() % 8;
		Enemy[i].move = (i == 0) ? 1 : -1; // Directions
		Enemy[i].type = rand() % 3; // 적기 외형 랜덤
	}
	Bullet = (struct Bullet*)malloc(MAXBULLET * sizeof(struct Bullet)); // Allocate memory for Bullet array

	if (Bullet == NULL) {
		printf("Memory allocation failed!\n");
		cleanup_game();
		exit(1);
	}
}

void cleanup_game() {
	free(Bullet);
}

void playermove(unsigned char ch) {
	int move_flag = 0;
	static unsigned char last_ch = 0;
	static int called = 0; //

	if (called == 0) {
		removeCursor();
		playerdraw(oldx, oldy);
		called = 1;
	}
	if (keep_moving && ch == 0)
		ch = last_ch;
	last_ch = ch;

	switch (ch) {
	case UP:
		if (oldy > 5)
			newy = oldy - 1;
		move_flag = 1;
		break;
	case DOWN:
		if (oldy < HEIGHT - 1)
			newy = oldy + 1;
		move_flag = 1;
		break;
	case LEFT:
		if (oldx > 25)
			newx = oldx - 1;
		move_flag = 1;
		break;
	case RIGHT:
		if (oldx < WIDTH - 25)
			newx = oldx + 1;
		move_flag = 1;
		break;
	}
	if (move_flag) {
		playererase(oldx, oldy);
		playerdraw(newx, newy); // 새로운 위치에서 플레이어 표시
		oldx = newx; // 마지막 위치를 기억한다.
		oldy = newy;
	}
}

void playerdraw(int x, int y) {
	textcolor(BLUE1, WHITE);
	gotoxy(x, y);
	printf("<=▲=>");
}
void playererase(int x, int y) {
	gotoxy(x, y);
	printf("      ");
}

void DrawBullet(int i) {
	textcolor(BLUE1, WHITE);
	gotoxy(Bullet[i].x, Bullet[i].y); printf("│");
}
void EraseBullet(int i) {
	gotoxy(Bullet[i].x, Bullet[i].y); printf("  ");
}

void bulletmove() {
	int i;
	for (i = 0; i < MAXBULLET; i++) {
		if (Bullet[i].exist == TRUE) {
			EraseBullet(i);
			if (Bullet[i].y == 0) {
				Bullet[i].exist = FALSE;
			}
			else {
				Bullet[i].y--;
				DrawBullet(i);
			}
		}
	}
}

void showenemy() {
	int i, location, direct, height;
	textcolor(RED1, WHITE);
	location = rand() % 2;
	direct = location == 0 ? 50 : 130; // 스폰위치
	height = 1 + rand() % 8;
	for (i = 0; i < MAXENEMY && Enemy[i].exist == TRUE; i++) {}
}

void Enemymove() {
	int enemies_alive = 0; // Counter for alive enemies

	for (int i = 0; i < MAXENEMY; i++) {
		if (Enemy[i].exist == TRUE) {
			enemies_alive++;
			// Erase the previous position
			gotoxy(Enemy[i].x, Enemy[i].y);
			printf("         "); // Clear the width of the enemy

			// Move enemy
			if (Enemy[i].x >= 135) {
				Enemy[i].move = -1; // Change direction to left
			}
			else if (Enemy[i].x <= 5) {
				Enemy[i].move = 1; // Change direction to right
			}

			Enemy[i].x += Enemy[i].move;

			// Randomly change y direction
			if (rand() % 2 == 0) {
				if (Enemy[i].y < 8) {
					Enemy[i].y++;
				}
			}
			else {
				if (Enemy[i].y > 1) {
					Enemy[i].y--;
				}
			}
			// Draw the enemy at the new position
			gotoxy(Enemy[i].x, Enemy[i].y);
			printf("%s", Enemyunit[Enemy[i].type]);
		}
	}
	// 승리
	if (enemies_alive == 0) {
		gotoxy(70, 25);
		printWin();
		gotoxy(0, 48);
		Sleep(1000);
		cleanup_game();
		exit(0);
	}
}


void EnemyMissileshow() {
	int j;
	int random = rand() % MAXENEMY;
	for (j = 0; j < MAXENEMYMISSILE && EnemyMissile[j].exist == TRUE; j++) {}
	if (j != MAXENEMYMISSILE && Enemy[random].exist == TRUE) {
		EnemyMissile[j].x = Enemy[random].x + 2;
		EnemyMissile[j].y = Enemy[random].y + 1;
		EnemyMissile[j].exist = TRUE;
	}
}

void EnemyMissiledraw(int i) {
	textcolor(RED2, WHITE);
	gotoxy(EnemyMissile[i].x, EnemyMissile[i].y);
	printf("●");
}
void EnemyMissileerase(int i) {
	gotoxy(EnemyMissile[i].x, EnemyMissile[i].y);
	printf("  ");
}

void EnemyMissileMove() {
	int random;
	random = 1;
	for (int i = 0; i < MAXENEMYMISSILE; i++) {
		if (EnemyMissile[i].exist == TRUE) {
			EnemyMissileerase(i);
			if (EnemyMissile[i].y > HEIGHT - 3) {
				EnemyMissile[i].exist = FALSE;
			}
			else {
				if (random) {
					if (EnemyMissile[i].x <= newx)
						EnemyMissile[i].x++;
					else
						EnemyMissile[i].x--;
				}
				EnemyMissile[i].y++;
				EnemyMissiledraw(i);
			}
		}
	}
}

void Enemyfall() {
	int i, j, count = 0;
	for (i = 0; i < MAXENEMY; i++) {
		if (Enemy[i].exist == FALSE || Enemy[i].type == -1)
			continue;
		for (j = 0; j < MAXBULLET; j++) {
			if (Bullet[j].exist == FALSE)
				continue;
			if (Enemy[i].y == Bullet[j].y && abs(Enemy[i].x - Bullet[j].x) <= 7) {
				gotoxy(Bullet[j].x, Bullet[j].y);
				printf("           ");
				Bullet[j].exist = FALSE;
				Enemy[i].exist = FALSE; // Mark the enemy as no longer existing
				remain--;
				break; // Break out of the inner loop to avoid multiple bullets hitting the same enemy
			}
		}
	}
}

void playerfall() {
	int i;
	for (i = 0; i < MAXENEMYMISSILE; i++) {
		if (EnemyMissile[i].exist == FALSE)
			continue;
		if (EnemyMissile[i].y == newy && abs(EnemyMissile[i].x - newx) <= 3) {
			EnemyMissile[i].exist = FALSE;
			gotoxy(EnemyMissile[i].x, EnemyMissile[i].y);
			printf("    ");
			heart--;
		}
	}
}

void info() {
	textcolor(BLACK, WHITE);
	gotoxy(45, 48); printf(" 남은 적 : %d", remain);
	gotoxy(15, 48); printf("Flare : ");
	if (heart == 9) {
		gotoxy(15, 48); printf("Flare : ");
		gotoxy(25, 48); printf("8");
	}
	else if (heart == 8) {
		gotoxy(15, 48); printf("Flare : ");
		gotoxy(25, 48); printf("7");
	}
	else if (heart == 7) {
		gotoxy(15, 48); printf("Flare : ");
		gotoxy(25, 48); printf("6");
	}
	else if (heart == 6) {
		gotoxy(15, 48); printf("Flare : ");
		gotoxy(25, 48); printf("5");
	}
	else if (heart == 5) {
		gotoxy(15, 48); printf("Flare : ");
		gotoxy(25, 48); printf("4");
	}
	else if (heart == 4) {
		gotoxy(15, 48); printf("Flare : ");
		gotoxy(25, 48); printf("3");
	}
	else if (heart == 3) {
		gotoxy(15, 48); printf("Flare : ");
		gotoxy(25, 48); printf("2");
	}
	else if (heart == 2) {
		gotoxy(15, 48); printf("Flare : ");
		gotoxy(25, 48); printf("1");
	}
	else if (heart == 1) {
		gotoxy(15, 48); textcolor(RED1, WHITE);  printf("Flare : ");
		gotoxy(25, 48); printf("0");
	}
	else if (heart == 0) {
		gotoxy(70, 25); textcolor(RED1, WHITE); printLose();
		gotoxy(0, 48);
		cleanup_game();
		Sleep(1000);
		exit(0);
	}
}

void setPlayerSpeed(int speed) {
	player_speed = speed;
}

void MissileDraw(int i) {
	textcolor(BLUE1, WHITE);
	gotoxy(Missile[i].x, Missile[i].y);
	printf("●");
}

void MissileErase(int i) {
	gotoxy(Missile[i].x, Missile[i].y);
	printf("  ");
}

void MissileMove() {
	for (int i = 0; i < MAXMISSILE; i++) {
		if (Missile[i].exist == TRUE) {
			MissileErase(i);

			int nearest_enemy = -1;
			int min_distance = 1000000;

			for (int j = 0; j < MAXENEMY; j++) {
				if (Enemy[j].exist == TRUE) {
					int distance = abs(Enemy[j].x - Missile[i].x) + abs(Enemy[j].y - Missile[i].y);
					if (distance < min_distance) {
						min_distance = distance;
						nearest_enemy = j;
					}
				}
			}

			// 유도
			if (nearest_enemy != -1) {
				if (Missile[i].x < Enemy[nearest_enemy].x) {
					Missile[i].x++;
				}
				else if (Missile[i].x > Enemy[nearest_enemy].x) {
					Missile[i].x--;
				}

				if (Missile[i].y < Enemy[nearest_enemy].y) {
					Missile[i].y++;
				}
				else if (Missile[i].y > Enemy[nearest_enemy].y) {
					Missile[i].y--;
				}

				// 유도 미사일 충돌
				if (Missile[i].x == Enemy[nearest_enemy].x && Missile[i].y == Enemy[nearest_enemy].y) {
					if (rand() % 5 == 0) { // 50% chance the enemy survives
						Enemy[nearest_enemy].exist = FALSE;
						gotoxy(Enemy[nearest_enemy].x, Enemy[nearest_enemy].y);
						printf("     "); // Clear enemy
						remain--;
					}
					Missile[i].exist = FALSE;
					gotoxy(Missile[i].x, Missile[i].y);
					printf(" "); // Clear missile
				}
				else {
					MissileDraw(i);
				}
			}
			else {
				Missile[i].exist = FALSE;
			}

			if (Missile[i].x < 0 || Missile[i].x >= WIDTH || Missile[i].y < 0 || Missile[i].y >= HEIGHT) {
				Missile[i].exist = FALSE;
				gotoxy(Missile[i].x, Missile[i].y);
				printf(" ");
			}
			else {
				MissileDraw(i);
			}
		}
	}
}



void MissileShow() {
	static int missile_timer = 0;
	missile_timer++;

	if (missile_timer >= MissileUse * 60) {
		missile_timer = 0;
		for (int i = 0; i < MAXMISSILE; i++) {
			if (Missile[i].exist == FALSE) {
				Missile[i].x = newx + 1;
				Missile[i].y = newy - 1;
				Missile[i].exist = TRUE;
				MissileDraw(i);
				break;
			}
		}
	}
}