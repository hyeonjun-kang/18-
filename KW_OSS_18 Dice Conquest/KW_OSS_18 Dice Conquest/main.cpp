#include<iostream>
#include<Windows.h>
#include<conio.h>
#include <ctime>
#include <random>

using namespace std;

#define INIT_POS 1
//Ű���� �Է� ���� �� �Էµ� Ű���带 ��ȯ�ϴ� �Լ�.
int GetKeyDown()
{
	if (_kbhit() != 0)
	{
		return _getch();
	}
	return 0;
}
//-----------------------------------------
//�ܼ� ������ Ư�� ��ġ�� Ŀ���� �̵��ϴ� �Լ�.
void GotoXY(int x, int y)
{
	COORD pos;
	pos.X = 2 * x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void title() {
	GotoXY(3, 2);
	printf("     _ _                                                  _  \n");
	GotoXY(3, 3);
	printf("  __| (_) ___ ___    ___ ___  _ __   __ _ _   _  ___  ___| |_ \n");
	GotoXY(3, 4);
	printf(" / _` | |/ __/ _ |  / __/ _ || '_ | / _` | | | |/ _ |/ __| __|\n");
	GotoXY(3, 5);
	printf("| (_| | | (_|  __/ | (_| (_) | | | | (_| | |_| |  __/|__ | |_ \n");
	GotoXY(3, 6);
	printf(" |__,_|_||___|___|  |___|___/|_| |_||__, ||__,_||___||___/|__|\n");
	GotoXY(3, 7);
	printf("                                       |_|                   \n ");

	GotoXY(10, 13);
	printf("�� press any key to game start ��");
	GotoXY(10, 15);
	printf("��   press 'q' to game exit    ��");
	int key = _getch();
	if (key == 'q' || key == 'Q') {
		system("cls");
		exit(1);
	}
	system("cls");
}
//�ܼ� â ũ��� ������ �����ϴ� �Լ�.
void SetConsoleView()
{
	system("mode con:cols=80 lines=20");
	system("title Dice Conquest");
}


//-----------------------------------------
//2���� �迭�� �̷���� ��
const int originMap[6][6] = { {1, 1, 2, 2, 3, 3},
								{4, 4, 5, 5, 6, 6},
								{8, 8, 9, 9, 10, 10},
								{12, 12, 15, 15, 16, 16},
								{18, 18, 20, 20, 24, 24},
								{25, 25, 30, 30, 36, 36} };
void text_remove() {
	GotoXY(0, 15);
	for (int i = 0; i < 120; i++) { printf("  "); }
}
//������ ����ü
struct Pos
{
	int x;
	int y;
};

//Ű���� �Է��� ������ ���� enum
enum KEYBOARD
{
	IS_ARROW = 224,
	UP = 72,
	LEFT = 75,
	RIGHT = 77,
	DOWN = 80,
	SPACE = 32,
};

//������ �����س��� enum
enum COLOR
{
	GREEN = 10,
	MINT,
	RED,
	PINK,
	YELLOW,
	WHITE,
};
int* getindex(int num) {
	int *arr = new int[2];
	switch (num) {
	case 1:
		arr[0] = 0; arr[1] = 0; break;
	case 2:
		arr[0] = 0; arr[1] = 2; break;
	case 3:
		arr[0] = 0; arr[1] = 4; break;
	case 4:
		arr[0] = 1; arr[1] = 0; break;
	case 5:
		arr[0] = 1; arr[1] = 2; break;
	case 6:
		arr[0] = 1; arr[1] = 4; break;
	case 8:
		arr[0] = 2; arr[1] = 0; break;
	case 9:
		arr[0] = 2; arr[1] = 2; break;
	case 10:
		arr[0] = 2; arr[1] = 4; break;
	case 12:
		arr[0] = 3; arr[1] = 0; break;
	case 15:
		arr[0] = 3; arr[1] = 2; break;
	case 16:
		arr[0] = 3; arr[1] = 4; break;
	case 18:
		arr[0] = 4; arr[1] = 0; break;
	case 20:
		arr[0] = 4; arr[1] = 2; break;
	case 24:
		arr[0] = 4; arr[1] = 4; break;
	case 25:
		arr[0] = 5; arr[1] = 0; break;
	case 30:
		arr[0] = 5; arr[1] = 2; break;
	case 36:
		arr[0] = 5; arr[1] = 4; break;
	}
	return arr;
}
namespace P {
	class player {
	public:
		player() {
			order = 0;
			many_ground = 0;
			opponent_color = 0;
			my_color = 0;
		}

		int get_order() { return order; }
		int get_many_ground() { return many_ground; }
		int get_opponent_color() { return opponent_color; }
		int get_my_color() { return my_color; }
		void set_order(int num) { order = num; }
		void set_many_ground(int many) { many_ground = many; }
		void set_opponent_color(int color) { opponent_color = color; }
		void set_my_color(int color) { my_color = color; }

	private:
		int opponent_color;
		int order;
		int many_ground;
		int my_color;
	};
	void player_order(player *p1, player *p2);
	bool player_win(player p1, player p2);
	void player_order(player *p1, player *p2)
	{
		printf("������ �����ϱ� ���� ������ ���ϰڽ��ϴ�.\n");
		printf("�ֻ����� ������ ���� ���� ���� �÷��̾ ���� ���� �����ϰ� �˴ϴ�.\n");
		while (1) {
			printf("player1(GREEN), �ƹ�Ű�� ���� �ֻ��� ������\n");
			_getch();
			int dice1 = rand() % 6 + 1;
			printf("player1(GREEN) dice : %d\n", dice1);

			printf("player2(RED), �ƹ�Ű�� ���� �ֻ��� ������\n");
			_getch();
			int dice2 = rand() % 6 + 1;
			printf("player2(RED) dice : %d\n", dice2);
			if (dice1 == dice2) {
				printf("�� �ֻ����� ���� ����, �ٽ� ������ ���� ���ϱ�!\n");
				continue;
			}
			else if (dice1 > dice2) {
				p1->set_order(1);
				p2->set_order(2);
				printf("player1(GREEN) ù��°!,player2(RED) �ι�°!\n");
				break;
			}
			else {
				p1->set_order(2);
				p2->set_order(1);
				printf("player2(RED) ù��°!,player1(GREEN) �ι�°!\n");
				break;
			}
		}
		printf(" �ƹ�Ű�� ������ ���� ����\n");
		_getch();
		system("cls");

	}
};




//���� �Ŵ��� Ŭ����
class GameManager
{
private:
	Pos player;				//�÷��̾� Ŀ�� ��ġ.
	int spaceCount;			//������ Ƚ��.
	int player1Count;		//player1 ���� ����
	int player2Count;		//plyaer2 ���� ����
	int colorMap[6][6];//�� ���� ���� �Լ�,p1�� GREEN p2�� RED
	bool turn;//���� ���������� ���� ����, TRUE�� P1, FALSE �� P2
public:
	void StartGame()
	{
		P::player a1;
		a1.set_opponent_color(RED);
		a1.set_my_color(GREEN);
		P::player a2;
		a2.set_opponent_color(GREEN);
		a2.set_my_color(RED);
		P::player_order(&a1, &a2);
		Init();		//���� �ʱ�ȭ
		DrawBack();	//��� �׸���
		DrawMain();
		score(&a1, &a2);

		while (true)//���� ������ ���� �Լ� �ֱ�
		{
			while (1) {//order 1 pase
				P::player* this_turn = NULL;
				P::player* oppo = NULL;
				if (a1.get_order() == 1) {
					GotoXY(5, 15);
					printf("player 1(GREEN)�� �� ����!");
					this_turn = &a1;
					oppo = &a2;
				}
				else if (a2.get_order() == 1) {
					GotoXY(5, 15);
					printf("player 2(RED)�� �� ����!");
					this_turn = &a2;
					oppo = &a1;
				}
				GotoXY(5, 16);
				printf("�ƹ�Ű�� ���� �ֻ��� ������");
				_getch();
				text_remove();
				int dice1 = rand() % 6 + 1; int dice2 = rand() % 6 + 1;
				GotoXY(5, 15);
				printf("�ֻ��� ���: %d, %d", dice1, dice2);
				GotoXY(5, 16);
				printf("%d�� ���� ������ �� �ֽ��ϴ�!", dice1*dice2);
				GotoXY(5, 17);
				printf("�ƹ�Ű�� ���� �����ϱ�");
				_getch();
				text_remove();
				int *num = getindex(dice1 * dice2);
				if (colorMap[*num][*(num + 1)] == 0 || colorMap[*num][*(num + 1)] == this_turn->get_opponent_color()) {
					if (colorMap[*num][*(num + 1)] == this_turn->get_opponent_color()) {
						GotoXY(5, 15);
						printf("��� �� %d�� ���� �����Ͽ����ϴ�!", dice1 * dice2);
						colorMap[*num][*(num + 1)] = this_turn->get_my_color();
						this_turn->set_many_ground(this_turn->get_many_ground() + 1);
						oppo->set_many_ground(oppo->get_many_ground() - 1);
						GotoXY(5, 16);
						printf("��� ���� �����Ͽ����Ƿ�, �ѹ� �� �ֻ����� ���� ��ȸ�� ������ϴ�!");
						GotoXY(5, 17);
						printf("�ƹ�Ű�� ���� �����ϱ�");
						_getch();
						text_remove();
						delete num;
						DrawMain();
						score(&a1, &a2);
						Sleep(100);
						if ((a1.get_many_ground() + a2.get_many_ground()) == 36) {
							DrawGameClear(&a1, &a2);
							break;
						}
						continue;
					}
					else {
						GotoXY(5, 15);
						printf("�� �� %d�� ���� �����Ͽ����ϴ�!", dice1 * dice2);
						GotoXY(5, 16);
						printf("�ƹ�Ű�� ���� �����ϱ�");
						colorMap[*num][*(num + 1)] = this_turn->get_my_color();
						this_turn->set_many_ground(this_turn->get_many_ground() + 1);
						_getch();
					}
				}
				else if (colorMap[*num][*(num + 1) + 1] == 0 || colorMap[*num][*(num + 1) + 1] == this_turn->get_opponent_color()) {
					if (colorMap[*num][*(num + 1) + 1] == this_turn->get_opponent_color()) {
						GotoXY(5, 15);
						printf("��� �� %d�� ���� �����Ͽ����ϴ�!", dice1 * dice2);
						colorMap[*num][*(num + 1) + 1] = this_turn->get_my_color();
						this_turn->set_many_ground(this_turn->get_many_ground() + 1);
						oppo->set_many_ground(oppo->get_many_ground() - 1);
						GotoXY(5, 16);
						printf("��� ���� �����Ͽ����Ƿ�, �ѹ� �� �ֻ����� ���� ��ȸ�� ������ϴ�!");
						GotoXY(5, 17);
						printf("�ƹ�Ű�� ���� �����ϱ�"); _getch();
						text_remove();
						delete num;
						DrawMain();
						score(&a1, &a2);
						Sleep(100);
						if ((a1.get_many_ground() + a2.get_many_ground()) == 36) {
							DrawGameClear(&a1, &a2);
							break;
						}
						continue;
					}
					else {
						GotoXY(5, 15);
						printf("�� �� %d�� ���� �����Ͽ����ϴ�!", dice1 * dice2);
						GotoXY(5, 16);
						printf("�ƹ�Ű�� ���� �����ϱ�");
						_getch();
						colorMap[*num][*(num + 1) + 1] = this_turn->get_my_color();
						this_turn->set_many_ground(this_turn->get_many_ground() + 1);
					}
				}
				else {
					GotoXY(5, 15);
					printf("������ %d��° ���� �����ϴ�..", dice1 * dice2);
					GotoXY(5, 16);
					printf("�ƹ�Ű�� ���� �����ϱ�"); _getch();
				}
				text_remove();
				delete num;
				break;
			}
			DrawMain();
			score(&a1, &a2);
			Sleep(100);
			if ((a1.get_many_ground() + a2.get_many_ground()) == 36) {
				DrawGameClear(&a1, &a2);
				break;
			}
			while (1) {//order 2 pase
				P::player* this_turn = NULL;
				P::player* oppo = NULL;
				if (a1.get_order() == 2) {
					GotoXY(5, 15);
					printf("player 1(GREEN)�� �� ����!");
					this_turn = &a1;
					oppo = &a2;
				}
				else if (a2.get_order() == 2) {
					GotoXY(5, 15);
					printf("player 2(RED)�� �� ����!");
					this_turn = &a2;
					oppo = &a1;
				}
				GotoXY(5, 16);
				printf("�ƹ�Ű�� ���� �ֻ��� ������");
				_getch();
				text_remove();
				int dice1 = rand() % 6 + 1; int dice2 = rand() % 6 + 1;
				GotoXY(5, 15);
				printf("�ֻ��� ���: %d, %d", dice1, dice2);
				GotoXY(5, 16);
				printf("%d�� ���� ������ �� �ֽ��ϴ�!", dice1 * dice2);
				GotoXY(5, 17);
				printf("�ƹ�Ű�� ���� �����ϱ�");
				_getch();
				text_remove();
				int* num = getindex(dice1 * dice2);
				if (colorMap[*num][*(num + 1)] == 0 || colorMap[*num][*(num + 1)] == this_turn->get_opponent_color()) {
					if (colorMap[*num][*(num + 1)] == this_turn->get_opponent_color()) {
						GotoXY(5, 15);
						printf("��� �� %d�� ���� �����Ͽ����ϴ�!", dice1 * dice2);
						colorMap[*num][*(num + 1)] = this_turn->get_my_color();
						this_turn->set_many_ground(this_turn->get_many_ground() + 1);
						oppo->set_many_ground(oppo->get_many_ground() - 1);
						GotoXY(5, 16);
						printf("��� ���� �����Ͽ����Ƿ�, �ѹ� �� �ֻ����� ���� ��ȸ�� ������ϴ�!");
						GotoXY(5, 17);
						printf("�ƹ�Ű�� ���� �����ϱ�");
						_getch();
						text_remove();
						delete num;
						DrawMain();
						score(&a1, &a2);
						Sleep(100);
						if ((a1.get_many_ground() + a2.get_many_ground()) == 36) {
							DrawGameClear(&a1, &a2);
							break;
						}
						continue;
					}
					else {
						GotoXY(5, 15);
						printf("�� �� %d�� ���� �����Ͽ����ϴ�!", dice1 * dice2);
						colorMap[*num][*(num + 1)] = this_turn->get_my_color();
						this_turn->set_many_ground(this_turn->get_many_ground() + 1);
						GotoXY(5, 16);
						printf("�ƹ�Ű�� ���� �����ϱ�");
						_getch();
					}
				}
				else if (colorMap[*num][*(num + 1) + 1] == 0 || colorMap[*num][*(num + 1) + 1] == this_turn->get_opponent_color()) {
					if (colorMap[*num][*(num + 1) + 1] == this_turn->get_opponent_color()) {
						GotoXY(5, 15);
						printf("��� �� %d�� ���� �����Ͽ����ϴ�!", dice1 * dice2);
						colorMap[*num][*(num + 1) + 1] = this_turn->get_my_color();
						this_turn->set_many_ground(this_turn->get_many_ground() + 1);
						oppo->set_many_ground(oppo->get_many_ground() - 1);
						GotoXY(5, 16);
						printf("��� ���� �����Ͽ����Ƿ�, �ѹ� �� �ֻ����� ���� ��ȸ�� ������ϴ�!");
						GotoXY(5, 17);
						printf("�ƹ�Ű�� ���� �����ϱ�"); _getch();
						text_remove();
						delete num;
						DrawMain();
						score(&a1, &a2);
						Sleep(100);
						if ((a1.get_many_ground() + a2.get_many_ground()) == 36) {
							DrawGameClear(&a1, &a2);
							break;
						}
						continue;
					}
					else {
						GotoXY(5, 15);
						printf("�� �� %d�� ���� �����Ͽ����ϴ�!", dice1 * dice2);
						GotoXY(5, 16);
						printf("�ƹ�Ű�� ���� �����ϱ�"); _getch();
						colorMap[*num][*(num + 1) + 1] = this_turn->get_my_color();
						this_turn->set_many_ground(this_turn->get_many_ground() + 1);
					}
				}
				else {
					GotoXY(5, 15);
					printf("������ %d��° ���� �����ϴ�..", dice1 * dice2);
					GotoXY(5, 16);
					printf("�ƹ�Ű�� ���� �����ϱ�"); _getch();
				}
				text_remove();
				delete num;
				break;
			}
			//draw
			DrawMain();
			score(&a1, &a2);
			Sleep(100);
			if ((a1.get_many_ground() + a2.get_many_ground()) == 36) {
				DrawGameClear(&a1, &a2);
				break;
			}
		}
	}

	//�� �ʱ�ȭ
	void Init()
	{
		player.x = 0;
		player.y = 0;
		spaceCount = 0;
		player1Count = 0;
		player2Count = 0;
		for (int i = 0; i < 6; i++) {
			for (int k = 0; k < 6; k++) {
				colorMap[i][k] = 0;
			}
		}
		turn = true;

	}
	void score(P::player * p1, P::player* p2) {//�� �÷��̾� ���� �� ���� ��� �Լ�
		GotoXY(25, 6);
		printf("��    %02d     ��     %02d    ��", p1->get_many_ground(), p2->get_many_ground());
	}


	//Ŀ���� ��ġ �̵�
	void MovePos()
	{
		GotoXY(INIT_POS + (player.x * 4), INIT_POS + (player.y * 2) + 1);
		printf("  ");

		//Ű���� �Է��� �޾Ƽ�, �ش� ��ġ�� �̵��� �����ش�.
		switch (_getch())
		{
		case KEYBOARD::LEFT:
			--player.x;
			if (player.x <= 0)
			{
				player.x = 0;
			}
			break;
		case KEYBOARD::RIGHT:
			++player.x;
			if (player.x >= 5)
			{
				player.x = 5;
			}
			break;
		case KEYBOARD::UP:
			--player.y;
			if (player.y <= 0)
			{
				player.y = 0;
			}
			break;
		case KEYBOARD::DOWN:
			++player.y;
			if (player.y >= 5)
			{
				player.y = 5;
			}
			break;
		}
	}

	void DrawMain()
	{
		//map draw
		SetTextColor(WHITE);
		int d = 0;
		int c;
		for (int y = 0; y < 6; ++y)
		{
			GotoXY(INIT_POS, INIT_POS + (2 * y));
			for (int x = 0; x < 6; ++x)
			{
				c = colorMap[y][x];
				if (c == GREEN) { SetTextColor(GREEN); }//color�ʿ� ���� �� ĥ�ϱ�
				else if (c == RED) { SetTextColor(RED); }
				else { SetTextColor(WHITE); }
				d = originMap[y][x];
				printf("[%02d]    ", d);
				SetTextColor(WHITE);
			}
		}
		SetTextColor(WHITE);


		GotoXY(25, 1);
		printf("Press Any Key");
	}

	void DrawBack()
	{
		SetTextColor(WHITE);
		GotoXY(25, 5);
		cout << "���player1����player2���";
		GotoXY(25, 7);
		cout << "��           ��           ��";
		GotoXY(25, 8);
		cout << "���������������";
		GotoXY(25, 10);
		cout << "Kwang Woon Univ";
		GotoXY(25, 11);
		cout << "OSS ";
		SetTextColor(PINK);
		cout << "team 18";
		SetTextColor(WHITE);
		GotoXY(0, 14);
		for (int i = 0; i < 40; i++) { cout << "��"; }
		GotoXY(0, 18);
		for (int i = 0; i < 40; i++) { cout << "��"; }
	}

	void DrawGameClear(P::player * p1, P::player * p2)
	{
		system("cls");
		if (p1->get_many_ground() > p2->get_many_ground()) {
			SetTextColor(YELLOW);
			GotoXY(3, 5);
			cout << "=========================";
			GotoXY(3, 6);
			cout << "===== Player 1 win! =====";
			GotoXY(3, 7);
			cout << "=========================";
			SetTextColor(WHITE);
		}
		else if (p1->get_many_ground() < p2->get_many_ground()) {
			SetTextColor(YELLOW);
			GotoXY(3, 5);
			cout << "=========================";
			GotoXY(3, 6);
			cout << "===== Player 2 win! =====";
			GotoXY(3, 7);
			cout << "=========================";
			SetTextColor(WHITE);
		}
		else {
			SetTextColor(YELLOW);
			GotoXY(3, 5);
			cout << "=========================";
			GotoXY(3, 6);
			cout << "========= draw! =========";
			GotoXY(3, 7);
			cout << "=========================";
			SetTextColor(WHITE);
		}
	}

	void SetTextColor(int color)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	}
};

//�����Լ�
int main(void)
{
	srand(time(NULL));
	SetConsoleView();
	title();
	GameManager* pGameMgr = new GameManager();
	pGameMgr->StartGame();
	delete(pGameMgr);
	return 0;
}