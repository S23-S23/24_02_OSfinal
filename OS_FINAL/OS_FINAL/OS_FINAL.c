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

// ������ ����ü
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

// ���Ḯ��Ʈ
typedef struct Node {
	Fighter fighter;
	struct Node* next;
} Node;

Node* head = NULL;
//extern Node* head;

// �Լ� ����
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
	printf("\n\n���������� Ÿ��Ǭ(����: Eurofighter Typhoon)�� 1983�⿡ ������ ���������� ���ҽþ��� ���� ����ǰ� ���۵�, �ſ� ��ø�� �ֹ߿����� �ٸ��� ������-�ﰢ��(canard-delta wing) 4.5���� �������Դϴ�.\n");
	printf("����� Ư¡: �ֹ� ����: �� ���� Eurojet EJ200 �ͺ��� ������ �����Ͽ� ���� �߷°� �⵿���� �����մϴ�.\n");
	printf("���ڽ� ���: ���̴� �ݻ� ����(RCS)�� ���̱� ���� ���谡 ����Ǿ� ������, ������ ���ڽ� ������� �ƴմϴ�.\n");
	printf("������ �ö���-����-���̾� �ý���: ���� ���� �ý����� ������ȭ�Ǿ� ���� �������� ���̰� �������� �δ��� �ٿ��ݴϴ�.\n");
	printf("�ٸ��� ����: ����� ����, ������ ����, ���� �� �پ��� �ӹ��� ������ �� �ֽ��ϴ�.\n");
	printf("����� �̻���: AIM-120 AMRAAM, IRIS-T, MBDA Meteor, ������ ����: AGM-65 Maverick, Storm Shadow, Paveway �ø���, �����: Mauser BK-27 27mm �����\n");
}

void F_14(Fighter f) {
	printf("Name: %s\nMax Speed: %.1f\nRadar Range: %.2f\nFlares: %d\nMissiles: %d\nBullets: %d\nGeneration: %.1f\nEngine: %s\nCountry: %s\nRole: %s\n",
		f.name, f.max_speed, f.radar_range, f.num_flares, f.num_missiles, f.num_bullets,
		f.generation, f.engine_model, f.country_of_origin, f.role);
	printf("\n\nF-14 ������� �̱��� Grumman Aerospace���� ������ ������ ������ �������Դϴ�. �� ������ 1970��뿡 ó�� ���ߵǾ� �̱� �ر��� �ر� �������� �ַ� ������� ���Ǿ����ϴ�.\n");
	printf("������ F-14�� �ֿ� Ư¡�Դϴ�. : \n");
	printf("���� �� Ư¡: F-14�� ū �������� ���� ���� ������ ������ �ֽ��ϴ�. �� ������ �⵿���� ���� �������� ���̴� �� �⿩�߽��ϴ�.�⺻������ ������� �Բ� �ٸ��� �ӹ��� ������ �� �ֵ��� ����Ǿ�����, ���� ���� �ɷ��� �������ϴ�.\n");
	printf("���� �ý��� : F-14�� AIM-54 �ʴн� �߰Ÿ� ����-���� �̻����� �� ����� ����߽��ϴ�. �̴� ���� ��Ÿ��� ������ Ÿ�ݷ��� �ڶ��մϴ�.\n");
	printf("��� �� ����: F-14�� �̱� �ر��� �̶� ���� �ر����� Ȱ��Ǿ�����, �ַ� ��Ӱ� ���� �⵿���� �䱸�ϴ� �ӹ��� ����߽��ϴ�. Ư��, 1980����� �̶�-�̶�ũ ���￡�� �̶� ������ F-14�� ����Ͽ� �������� �����߽��ϴ�.\n");
	printf("�� �� �ļ� ����: F-14�� 2006�⿡ �� �ر����� �������� ���Ͽ�����, �ļ� �������� F/A-18 ȣ���̳� F/A-18E/F ���� ȣ���� ���ԵǾ����ϴ�.\n");
}

void F_16(Fighter f) {
	printf("Name: %s\nMax Speed: %.1f\nRadar Range: %.2f\nFlares: %d\nMissiles: %d\nBullets: %d\nGeneration: %.1f\nEngine: %s\nCountry: %s\nRole: %s\n",
		f.name, f.max_speed, f.radar_range, f.num_flares, f.num_missiles, f.num_bullets,
		f.generation, f.engine_model, f.country_of_origin, f.role);
	printf("\n\nF-16 ������ ����(F-16 Fighting Falcon)�� �̱��� ������ �ٸ��� �������, ���������� �θ� ���ǰ� �ִ� �����Դϴ�.\n");

	printf("���� ���:1970��� �� �� ������ �䱸�� ���� �淮 ������� ���ߵǾ���, ���� ������ 1974��, ���� ������ 1978�⿡ �̷�������ϴ�.\n");
	printf("����� Ư¡ : ������ �ö���-����-���̾� �ý���: ���ڽ� ���� ���� �ý����� �����Ͽ� �پ �⵿���� �������� �����մϴ�.���� ĳ����: �þ� Ȯ���� ���� ū ���� ĳ���Ǹ� ����Ͽ� �������� �þ߸� �ش�ȭ�߽��ϴ�. \n");
	printf("����: ����� �̻���: AIM-9 ���̵���δ�, AIM-120 AMRAAM, ������ ����: AGM-65 �Ź���, GBU-12 Paveway II,�����: M61 ���� 20mm �����");
}

void F_18(Fighter f) {
	printf("Name: %s\nMax Speed: %.1f\nRadar Range: %.2f\nFlares: %d\nMissiles: %d\nBullets: %d\nGeneration: %.1f\nEngine: %s\nCountry: %s\nRole: %s\n",
		f.name, f.max_speed, f.radar_range, f.num_flares, f.num_missiles, f.num_bullets,
		f.generation, f.engine_model, f.country_of_origin, f.role);
	printf("F/A-18 ȣ��(F/A-18 Hornet)�� 1970��� �� �� �ر��� �غ����� �䱸�� ���� �̱��� ������ �ٸ��� �������Դϴ�.\n");
	printf("����� Ư¡: �� ���� ���ʷ� �Ϸ�Ʈ�� F404 �ͺ��� ������ �����ϰ� �ֽ��ϴ� (�ֹ� ����)\n");
	printf("4. ����: ����� �̻���: AIM-7 ���зο�, AIM-120 AMRAAM, AIM-9 ���̵���δ� ��, ������ ����: AGM-84 ��Ǭ, AGM-88 HARM, �پ��� ������ ���� ��ź ��, �����: M61 ���� 20mm �����\n");
	printf("   ������ ����: AGM-84 ��Ǭ, AGM-88 HARM, �پ��� ������ ���� ��ź ��\n");
}

void F_35(Fighter f) {
	printf("Name: %s\nMax Speed: %.1f\nRadar Range: %.2f\nFlares: %d\nMissiles: %d\nBullets: %d\nGeneration: %.1f\nEngine: %s\nCountry: %s\nRole: %s\n",
		f.name, f.max_speed, f.radar_range, f.num_flares, f.num_missiles, f.num_bullets,
		f.generation, f.engine_model, f.country_of_origin, f.role);

	printf("\n\nF-35�� �̱��� Lockheed Martin�簡 ������ �ٸ��� ���ڽ� �������Դϴ�.\nF-35�� ������ ���� Ư¡�� ������ �ֽ��ϴ�: \n");
	printf("�ٸ�����: F-35�� ������, ������, �ػ����� ������ �پ��� �ӹ��� ������ �� �ִ� �ٸ��� �������Դϴ�. ����-����, ����-���� �̻����� ����Ͽ� �پ��� �ӹ��� ������ �� �ֽ��ϴ�.\n");
	printf("���ڽ� ���: F-35�� ���ڽ� ����� ���߾� ���̴� ������ ��ư� �ϸ�, ���� ����ý����� ���� �� �ֵ��� ����Ǿ����ϴ�.\n");
	printf("�ٱ��� ����: �̱��� ����Ͽ� ����, ȣ��, �״�����, ��Ż���� �� �ټ��� ������ �����Ͽ� ���߿� �⿩�ϰ� ������, ���� ���󿡼� ��� ��ȹ�� �ֽ��ϴ�.\n");
	printf("�������� ���: ���� ����, ��Ʈ��ũ �߽� ���� �ɷ��� ��ȭ�Ͽ� ������ �ǽð����� �����ϰ� �ٸ� �÷����� �����Ͽ� �ӹ��� ������ �� �ֽ��ϴ�.\n");
}

void Su_27(Fighter f) {
	printf("Name: %s\nMax Speed: %.1f\nRadar Range: %.2f\nFlares: %d\nMissiles: %d\nBullets: %d\nGeneration: %.1f\nEngine: %s\nCountry: %s\nRole: %s\n",
		f.name, f.max_speed, f.radar_range, f.num_flares, f.num_missiles, f.num_bullets,
		f.generation, f.engine_model, f.country_of_origin, f.role);
	printf("\n\n Su-27 �÷�Ŀ(Su - 27 Flanker)��1970��� �� �ҷ��� �װ� ������ ��ȭ�ϱ� ���� ���ߵ� �ٸ��� �������Դϴ�.\n");
	printf("����� Ư¡ : �ֹ� ����: �� ���� ����ī ��-31 �ͺ��� ������ �����ϰ� �ֽ��ϴ�.\n");
	printf("              ��⵿��: �پ �⵿���� �����ϴ� ĵ��(Canard)�� �ö���-����-���̾� �ý����� Ư¡�Դϴ�.\n");
	printf("���� : ����� �̻���: R-27, R-73, R-77 ��, ������ ����: Kh-31, Kh-59, �پ��� ���� ��ź �� ���� ��, �����: GSh-30-1 30mm �����\n");
}

void DarkStar(Fighter f) {
	printf("Name: %s\nMax Speed: %.1f\nRole: %s\n",
		f.name, f.max_speed, f.role);
	printf("��ȭ [ž��: �Ź���]���� �����ϴ� ��ũ��Ÿ(Darkstar)�� ������ �������� (���� 10) �װ����Դϴ�.\n");
	printf("�������� ���� �װ����� SR-71 ������� SR-72�� ������ ��Ҹ� �ݿ��ϰ� �ֽ��ϴ�.\n");
}

////////////////////////////////////////////////////////������ ������ ��///////////////////////////////////////////////////////

////////////////////////////////////////////////��������Ʈ ����///////////////////////////////////////////////////////////////

#define BLACK 0 //���� ����
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
///////////////////////////////////////// �̵�
#define SPECIAL1 0XE0
#define SPECIAL2 0x00
#define SPACE 0x20
#define UP 0x48
#define DOWN 0x50
#define LEFT 0x4b
#define RIGHT 0x4d
int Delay = 10;
int frame_count = 0; //�ӵ� ������
int p1_frame_sync = 1; //�÷��̾� �̵��ӵ� (�ݺ��)
int player_speed = 1;

#define WIDTH 140
#define HEIGHT 43

#define UX 75  //���� ������ x��ǥ
#define UY 40  //���� ������ y��ǥ

int called = 0;

int oldx = UX, oldy = UY; // �÷��̾��� old ��ǥ
int newx = UX, newy = UY; //�÷��̾��� new ��ǥ
int keep_moving = 1;  //1:����̵�
////////////////////////////////////// �Ѿ�

int MAXBULLET = 6;
//#define MAXBULLET 6//�÷��̾��� �ִ� �Ѿ� ��
#define TRUE 1
#define FALSE 0

struct Bullet {
	int exist;
	int x, y;
} *Bullet;


#define MAXMISSILE 1 //�÷��̾��� �ִ� �̻��� ��
int MissileUse = 7; //�̻��� �ʸ��� ����
int Missile_frame_sync = 30;  //�̻��� �ӵ�����
struct {
	int exist;
	int x, y;
}Missile[MAXMISSILE];

////////////////////////////////////// ����
#define MAXENEMY 2
struct {
	int exist;
	int x, y;
	int number;
	int move;
	int type;
}Enemy[MAXENEMY];
char* Enemyunit[] = { "<=��=>","<=��=>","<=Y=>" };

///////////////////////////////////// �� �Ѿ�

#define MAXENEMYMISSILE 2 // �� �ִ� �̻��� ��
int enemymissileuse = 2; //�� �̻��� �ʸ��� ����
int enemymissile_frame_sync = 70;  //�� �̻��� �ӵ�����
int enemy_frame_sync = 1; //���� �ӵ�
struct {
	int exist;
	int x, y;
}EnemyMissile[MAXENEMYMISSILE];

//////////////////////////////////
int heart = 5;
int remain = 2;
int choise;
////////////////�Լ� ���� ����
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
	gotoxy(30, 21); printf(" ��  ��  / ��  /   / |  | |  �� |   | |  | \n");
	gotoxy(30, 22); printf(" ��   ��/   ��/   /  |  | |   ��|   | |  | \n");
	gotoxy(30, 23); printf("  ��             /   |  | |   . `   | |  | \n");
	gotoxy(30, 24); printf("   ��    /��    /    |  | |   |��   | |__| \n");
	gotoxy(30, 25); printf("    ��__/  ��__/     |__| |___| ��__| (__) \n");
}

void printLose() {
	textcolor(MAGENTA2, WHITE);
	gotoxy(30, 20); printf(" __        ______        _______.   _______  __  \n");
	gotoxy(30, 21); printf("|  |      /  __  ��      /       | |   ____||  | \n");
	gotoxy(30, 22); printf("|  |     |  |  |  |    |   (----`  |  |__   |  | \n");
	gotoxy(30, 23); printf("|  |     |  |  |  |     ��  ��     |   __|  |  | \n");
	gotoxy(30, 24); printf("|  `----.|  `--'  | .----)   |     |  |____ |__| \n");
	gotoxy(30, 25); printf("|_______| ��______/  |_______/     |_______|(__) \n");
}

void printIntro() {
	gotoxy(30, 5); printf("���Ⱑ ���並 ħ���ؿԽ��ϴ�! ������ ���!!\n");
	gotoxy(30, 8); printf("1. Game start!\n");
	gotoxy(30, 9); printf("2. Game rule\n");
}

void gameRule() {
	printf("  �̵� : ȭ��ǥ\n");
	printf("  ������ �������� ������ ���� ���� �ȿ��� ������ �޽��ϴ�! (�÷���, �̻���, �Ѿ� ��, �ִ�ӵ�) \n");
	printf("  �¸� ���� : ���� ���������� �����մϴ�. (�Ѿ��� ���߽�Ű�ų� 7�ʿ� �ѹ� �� �����Ǵ� �̻��Ϸ� óġ�ϼ���.)\n");
	printf("  �й� ���� : Flare�� 0�� ���¿��� �̻��Ͽ� �ǰ� ���ϸ� �й��մϴ�.\n");
	printf("  ������ 2�ʸ��� ���� �ӵ��� �������� �ٰ����� 2���� �̻����� �����մϴ�. ");
}

void chooseFight() {
	gotoxy(50, 10);
	printf("Choose your Fight!\n");
	sortFighters(&head, 1);
	printAllFighters(head);
	printf("\n Select from above(0~6) \n");

	scanf("%d", &choise);
	switch (choise) //�ӵ� ��� �̻��� �Ѿ�
	{
	case 0:
		heart = 10;
		MissileUse = 3;
		MAXBULLET = 10;
		p1_frame_sync = 0;
	case 1: //���������� 
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
		printf("0������ 6�������� �����մϴ�.");
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
		gotoxy(0, 43); for (int i = 0; i < 149; i++) { textcolor(BLACK, WHITE); printf("��"); }
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
		Enemy[i].type = rand() % 3; // ���� ���� ����
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
		playerdraw(newx, newy); // ���ο� ��ġ���� �÷��̾� ǥ��
		oldx = newx; // ������ ��ġ�� ����Ѵ�.
		oldy = newy;
	}
}

void playerdraw(int x, int y) {
	textcolor(BLUE1, WHITE);
	gotoxy(x, y);
	printf("<=��=>");
}
void playererase(int x, int y) {
	gotoxy(x, y);
	printf("      ");
}

void DrawBullet(int i) {
	textcolor(BLUE1, WHITE);
	gotoxy(Bullet[i].x, Bullet[i].y); printf("��");
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
	direct = location == 0 ? 50 : 130; // ������ġ
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
	// �¸�
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
	printf("��");
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
	gotoxy(45, 48); printf(" ���� �� : %d", remain);
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
	printf("��");
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

			// ����
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

				// ���� �̻��� �浹
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