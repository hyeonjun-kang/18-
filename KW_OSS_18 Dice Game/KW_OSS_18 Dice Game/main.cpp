#include<iostream>
#include<Windows.h>
#include<conio.h>

using namespace std;

#define INIT_POS 1

//-----------------------------------------
//�ܼ� ������ Ư�� ��ġ�� Ŀ���� �̵��ϴ� �Լ�.
void GotoXY(int x, int y)
{
	COORD pos;
	pos.X = 2 * x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//�ܼ� â ũ��� ������ �����ϴ� �Լ�.
void SetConsoleView()
{
	system("mode con:cols=80 lines=20");
	system("title Dice Game");
}

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
//2���� �迭�� �̷���� ��
const int originMap[6][6] = { {1, 1, 2, 2, 3, 3},
								{4, 4, 5, 5, 6, 6},
								{8, 8, 9, 9, 10, 10},
								{12, 12, 15, 15, 16, 16},
								{18, 18, 20, 20, 24, 24},
								{25, 25, 30, 30, 36, 36} };

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

//���� �Ŵ��� Ŭ����
class GameManager
{
private:
	char questionMap[6][6];	//���߰� �ִ� ��.
	Pos player;				//�÷��̾� Ŀ�� ��ġ.
	Pos flipPos[2];			//������ ī�� ��ġ ����.
	int flipCount;			//������ ī�� ����.
	int spaceCount;			//������ Ƚ��.
	int matchedCardCount;	//���� ī�� ����.
public:
	void StartGame()
	{
		Init();		//���� �ʱ�ȭ
		DrawBack();	//��� �׸���

		//���� ���� ����
		int key = 0;
		while (true)
		{
			key = GetKeyDown();	//Ű �Է� �޴� �Լ�
			if (key == KEYBOARD::IS_ARROW)
			{
				//ȭ��ǥ��.
				MovePos();
			}
			if (key == KEYBOARD::SPACE)
			{
				//�����̽�
				FlipCard();
			}
			//draw
			DrawMain();
			Sleep(100);
			CheckCard();
		}
	}

	//�� �ʱ�ȭ
	void Init()
	{
		for (int y = 0; y < 6; ++y)
		{
			for (int x = 0; x < 6; ++x)
			{
				questionMap[y][x] = '?';	//����ǥ�� �� ����
			}
		}
		player.x = 0;
		player.y = 0;
		flipCount = 0;
		spaceCount = 0;
		matchedCardCount = 0;
	}

	//ī�� ������ �Լ�
	void FlipCard()
	{
		if (questionMap[player.y][player.x] != '?') return;
		if (flipCount > 2) return;
		flipPos[flipCount].x = player.x;
		flipPos[flipCount].y = player.y;
		questionMap[player.y][player.x] = originMap[player.y][player.x] + '0';
		++flipCount;
	}

	//Ŀ���� ��ġ �̵�
	void MovePos()
	{
		GotoXY(INIT_POS + (player.x * 3), INIT_POS + (player.y * 2) + 1);
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
		char c = '\0';
		for (int y = 0; y < 6; ++y)
		{
			GotoXY(INIT_POS, INIT_POS + (2 * y));
			for (int x = 0; x < 6; ++x)
			{
				c = questionMap[y][x];
				if (c != '?')
				{
					SetTextColor(GREEN);
				}
				printf("[%c]   ", c);
				SetTextColor(WHITE);
			}
		}

		//player draw
		GotoXY(INIT_POS + (player.x * 3), INIT_POS + (player.y * 2) + 1);
		printf(" ^");


		GotoXY(20, 1);
		printf("Press Space Bar");

		GotoXY(20, 3);
		printf("Count : %d", spaceCount);
	}

	void CheckCard()
	{
		if (flipCount == 2)
		{
			char c = '?';
			if (originMap[flipPos[0].y][flipPos[0].x] == originMap[flipPos[1].y][flipPos[1].x])
			{
				//������
				c = originMap[flipPos[0].y][flipPos[0].x] + '0';
				++matchedCardCount;
			}
			else
			{
				//�ٸ���.
				Sleep(500);
			}
			questionMap[flipPos[0].y][flipPos[0].x] = c;
			questionMap[flipPos[1].y][flipPos[1].x] = c;
			flipCount = 0;
			++spaceCount;

			if (matchedCardCount >= 18)
			{
				DrawGameClear();
				Sleep(2000);
				system("cls");
				Init();
				DrawBack();
			}
		}
	}

	void DrawBack()
	{
		SetTextColor(WHITE);
		GotoXY(20, 6);
		cout << "Kwang Woon Univ";
		GotoXY(20, 7);
		cout << "OSS ";
		SetTextColor(PINK);
		cout << "team 18";
		SetTextColor(WHITE);
	}

	void DrawGameClear()
	{
		SetTextColor(YELLOW);
		GotoXY(3, 5);
		cout << "=========================";
		GotoXY(3, 6);
		cout << "======= C L E A R =======";
		GotoXY(3, 7);
		cout << "=========================";
		SetTextColor(WHITE);
	}

	void SetTextColor(int color)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	}
};

//�����Լ�
int main(void)
{
	SetConsoleView();
	GameManager* pGameMgr = new GameManager();
	pGameMgr->StartGame();
	delete(pGameMgr);
	return 0;
}
