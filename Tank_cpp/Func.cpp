#include "Func.h"
#include "Data.h"
#include <Windows.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#pragma comment(lib,"winmm.lib")

//ϵͳ����
void SetCursorState(bool b)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);	//��ȡ����̨�����Ϣ
	CursorInfo.bVisible = b;					//��ʾ/���ؿ���̨���
	SetConsoleCursorInfo(handle, &CursorInfo);	//���ÿ���̨���״̬
}
void setColor(int ForeColor, int BackGroundColor)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);					 //��ȡ��ǰ���ھ��
	SetConsoleTextAttribute(handle, ForeColor + BackGroundColor * 0x10);//������ɫ
}
void GotoxyAndPrint(unsigned x, unsigned y, const char* str)
{
	COORD cur;
	cur.X = x * 2;
	cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);
	printf(str);
}

//��Ϸ���
void GameInit()
{
	//���õ�ͼ
	for (int x = 0; x < MAP_X / 2; x++)
	{
		for (int y = 0; y < MAP_Y; y++)
		{
			//��ͼ�߽�
			if (x == 0 || x == MAP_X / 2 - 1 || x == MAP_X_WALL / 2 ||	//������
				y == 0 || y == MAP_Y - 1 ||							//�����
				(x > MAP_X_WALL / 2 && y == MAP_Y / 2))				//������Ϣ����Ϸ��Ϣ�ָ���
			{
				g_MAP[x][y] = ��ͼ�߽�;
			}
			if (x >= MAP_X_WALL / 4 - 2 && x <= MAP_X_WALL / 4 + 3 && y >= MAP_Y - 2 - 3 && y <= MAP_Y - 2)
			{
				if (x >= MAP_X_WALL / 4 && x <= MAP_X_WALL / 4 + 1 && y >= MAP_Y - 2 - 1 && y <= MAP_Y - 2)
					g_MAP[x][y] = �Ҽ�Ȫˮ;
				else
					g_MAP[x][y] = �����ϰ�;
			}
		}
	}

	SetCursorState(false);				//���ع��
	system("title Tank");				//���ñ���
	srand((unsigned int)time(0));		//��ʼ�����������

	//���ű�������(�Ȳ��ţ�����
	mciSendString("open conf/BGM.mp3 alias bgm", NULL, 0, NULL);//���ļ�
	mciSendString("play bgm repeat", NULL, 0, NULL);			  // ѭ������
}
char* ShowGameFile()
{
	//����ָ��Ŀ¼����׺���ļ�������������
	char* gameFiles[10] = { nullptr };
	long Handle;
	struct _finddata_t FileInfo;
	int count = 0;
	if ((Handle = _findfirst("conf/game/*.i", &FileInfo)) == -1L)
		printf("Not Found\n");
	else
	{
		gameFiles[count] = (char*)malloc(20);
		strcpy_s(gameFiles[count], 20, FileInfo.name);
		//g_Maps[count] = FileInfo.name;
		count++;
		while (_findnext(Handle, &FileInfo) == 0)
		{
			gameFiles[count] = (char*)malloc(20);
			strcpy_s(gameFiles[count], 20, FileInfo.name);
			//g_Maps[count] = FileInfo.name;
			count++;
		}
		_findclose(Handle);
	}
	//��ʾ�浵�ļ�
	system("cls");
	GotoxyAndPrint(MAP_X / 4 - 5, MAP_Y / 2 - 8, "��ѡ��浵");
	int i = 0;								//ѭ��������for�ⶨ��
	for (; i < count; i++)
	{
		GotoxyAndPrint(MAP_X / 4 - 5, MAP_Y / 2 - 6 + i, "");
		printf("%d.%s", i + 1, gameFiles[i]);
	}
	//ѡ��
	GotoxyAndPrint(MAP_X / 4 - 5, MAP_Y / 2 - 6 + i, "������ѡ��-> ");
	SetCursorState(true);
	int input = _getch() - '0';				//��֤0-9����ASCII
	SetCursorState(false);
	char* _file = (char*)malloc(15);
	strcpy_s(_file, 15, gameFiles[input - 1]);//����ʼ��1�����±�ʼ��0	
	return _file;
}
void GameOver(PTANK penemytank)
{
	//����̹����
	int eneTankCount = GetLiveEnemyAmount(penemytank);
	//�ر������ļ�
	mciSendString("close bgm", NULL, 0, NULL);	//close�رն���stopֹͣ
	//��ʾ��Ϣ
	setColor(12, 0);
	GotoxyAndPrint(MAP_X_WALL / 4 - 2, MAP_Y / 2 - 7, "GAME OVER! ");
	if (eneTankCount == 0)
		GotoxyAndPrint(MAP_X_WALL / 4 - 2, MAP_Y / 2 - 5, "A Winner!");
	else
		GotoxyAndPrint(MAP_X_WALL / 4 - 2, MAP_Y / 2 - 5, "A Loser!");
	GotoxyAndPrint(MAP_X_WALL / 4 - 2, MAP_Y / 2 - 3, "");
	printf("Scores: %d", ENEMY_TANK_AMOUNT - eneTankCount);
	setColor(7, 0);
}
int  SelectMenu(int size, int* pindex)
{
	int input = _getch();			//�޻��Խ���
	switch (input)
	{
	case _UP:
		if (*pindex > 0)
			* pindex -= 1;
		break;
	case _DOWN:
		if (*pindex < size - 1)//���һ��
			* pindex += 1;
		break;
	case ENTER:
		return ENTER;
		break;
	default:
		break;
	}
	return 0;
}
void SaveGame(PTANK ptank, PTANK penemytank)
{
	//��ʾ��Ϣ
	system("cls");
	setColor(12, 0);
	GotoxyAndPrint(MAP_X / 2 - 12, 12, "������浵����");
	GotoxyAndPrint(MAP_X / 2 - 12, 14, "");
	//�����ļ���
	char str[15];
	char* filename = (char*)malloc(40);
	SetCursorState(true);
	scanf_s("%s", str, 15);
	SetCursorState(false);
	setColor(7, 0);
	sprintf_s(filename, 40, "%s%s%s", "conf/game/", str, ".i");
	//���ļ�
	FILE* pFile = NULL;
	errno_t err = fopen_s(&pFile, filename, "wb");
	//д��ȫ�ֱ���
	fwrite(&g_isRunning, sizeof(int), 1, pFile);		//��Ϸ����״̬
	fwrite(&g_levelEneTank, sizeof(int), 1, pFile);	//д���Ѷȣ����Ƶз�̹���ٶ�
	fwrite(&g_levelEneBul, sizeof(int), 1, pFile);	//д���Ѷȣ����Ƶз��ӵ��ٶ�
	//д���ϰ�
	for (int x = 0; x < MAP_X_WALL; x++)
	{
		for (int y = 0; y < MAP_Y; y++)
		{
			fwrite(&g_MAP[x][y], sizeof(int), 1, pFile);
		}
	}
	//д���ҷ�̹��
	fwrite(&ptank->core, sizeof(COORD), 1, pFile);//���Ľڵ�
	for (int i = 0; i < 5; i++)
		fwrite(&ptank->body[i], sizeof(COORD), 1, pFile);//�����ڵ�
	fwrite(&ptank->dir, sizeof(int), 1, pFile);//����
	fwrite(&ptank->blood, sizeof(int), 1, pFile);//Ѫ��
	fwrite(&ptank->isAlive, sizeof(bool), 1, pFile);//�Ƿ���
	fwrite(&ptank->who, sizeof(int), 1, pFile);//���
	//д���ҷ��ӵ�
	fwrite(&ptank->bullet.core, sizeof(COORD), 1, pFile);//����
	fwrite(&ptank->bullet.dir, sizeof(int), 1, pFile);//����
	fwrite(&ptank->bullet.state, sizeof(int), 1, pFile);//״̬
	//д��з�
	for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
	{
		//д��з�̹��
		fwrite(&penemytank[i].core, sizeof(COORD), 1, pFile);//���Ľڵ�
		for (int i = 0; i < 5; i++)
			fwrite(&penemytank[i].body[i], sizeof(COORD), 1, pFile);//�����ڵ�
		fwrite(&penemytank[i].dir, sizeof(int), 1, pFile);//����
		fwrite(&penemytank[i].blood, sizeof(int), 1, pFile);//Ѫ��
		fwrite(&penemytank[i].isAlive, sizeof(bool), 1, pFile);//�Ƿ���
		fwrite(&penemytank[i].who, sizeof(int), 1, pFile);//���
		//д��з��ӵ�
		fwrite(&penemytank[i].bullet.core, sizeof(COORD), 1, pFile);//����
		fwrite(&penemytank[i].bullet.dir, sizeof(int), 1, pFile);//����
		fwrite(&penemytank[i].bullet.state, sizeof(int), 1, pFile);//״̬
	}
	fclose(pFile);
}
void LoadGame(PTANK ptank, PTANK penemytank, char* str)
{
	char* filename = (char*)malloc(40);
	sprintf_s(filename, 40, "%s%s", "conf/game/", str);
	FILE* pFile = NULL;
	errno_t err = fopen_s(&pFile, filename, "rb");
	//��ȡȫ�ֱ���
	fread(&g_isRunning, sizeof(int), 1, pFile);		//��Ϸ����״̬
	fread(&g_levelEneTank, sizeof(int), 1, pFile);	//��ȡ�Ѷȣ����Ƶз�̹���ٶ�
	fread(&g_levelEneBul, sizeof(int), 1, pFile);	//��ȡ�Ѷȣ����Ƶз��ӵ��ٶ�
	//��ȡ�ϰ�
	for (int x = 0; x < MAP_X_WALL; x++)
	{
		for (int y = 0; y < MAP_Y; y++)
		{
			fread(&g_MAP[x][y], sizeof(int), 1, pFile);
		}
	}
	//��ȡ�ҷ�̹��
	fread(&ptank->core, sizeof(COORD), 1, pFile);//���Ľڵ�
	for (int i = 0; i < 5; i++)
		fread(&ptank->body[i], sizeof(COORD), 1, pFile);//�����ڵ�
	fread(&ptank->dir, sizeof(int), 1, pFile);//����
	fread(&ptank->blood, sizeof(int), 1, pFile);//Ѫ��
	fread(&ptank->isAlive, sizeof(bool), 1, pFile);//�Ƿ���
	fread(&ptank->who, sizeof(int), 1, pFile);//���
	//��ȡ�ҷ��ӵ�
	fread(&ptank->bullet.core, sizeof(COORD), 1, pFile);//����
	fread(&ptank->bullet.dir, sizeof(int), 1, pFile);//����
	fread(&ptank->bullet.state, sizeof(int), 1, pFile);//״̬
	//��ȡ�з�
	for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
	{
		//��ȡ�з�̹��
		fread(&penemytank[i].core, sizeof(COORD), 1, pFile);//���Ľڵ�
		for (int i = 0; i < 5; i++)
			fread(&penemytank[i].body[i], sizeof(COORD), 1, pFile);//�����ڵ�
		fread(&penemytank[i].dir, sizeof(int), 1, pFile);//����
		fread(&penemytank[i].blood, sizeof(int), 1, pFile);//Ѫ��
		fread(&penemytank[i].isAlive, sizeof(bool), 1, pFile);//�Ƿ���
		fread(&penemytank[i].who, sizeof(int), 1, pFile);//���
		//��ȡ�з��ӵ�
		fread(&penemytank[i].bullet.core, sizeof(COORD), 1, pFile);//����
		fread(&penemytank[i].bullet.dir, sizeof(int), 1, pFile);//����
		fread(&penemytank[i].bullet.state, sizeof(int), 1, pFile);//״̬
	}
	fclose(pFile);
}

//��ӡ���
void DrawLogo()
{
	GotoxyAndPrint(MAP_X / 4 - 9, MAP_Y / 2 - 15, "MMP\"\"MM\"\"YMM                      `7MM      ");
	GotoxyAndPrint(MAP_X / 4 - 9, MAP_Y / 2 - 14, "P'   MM   `7                        MM      ");
	GotoxyAndPrint(MAP_X / 4 - 9, MAP_Y / 2 - 13, "     MM       ,6\"Yb.  `7MMpMMMb.    MM, MP'");
	GotoxyAndPrint(MAP_X / 4 - 9, MAP_Y / 2 - 12, "     MM      8)   MM    MM    MM    MM ;Y   ");
	GotoxyAndPrint(MAP_X / 4 - 9, MAP_Y / 2 - 11, "     MM       ,pm9MM    MM    MM    MM;Mm   ");
	GotoxyAndPrint(MAP_X / 4 - 9, MAP_Y / 2 - 10, "     MM      8M   MM    MM    MM    MM `Mb. ");
	GotoxyAndPrint(MAP_X / 4 - 9, MAP_Y / 2 - 9, "   .JMML.    `Moo9^Yo..JMML  JMML..JMML. YA.");
}
void DrawBarr()
{
	for (int x = 0; x < MAP_X_WALL; x++)
	{
		for (int y = 0; y < MAP_Y; y++)
		{
			if (g_MAP[x][y] == ʯ���ϰ�) GotoxyAndPrint(x, y, "��");
			if (g_MAP[x][y] == �����ϰ�) GotoxyAndPrint(x, y, "��");
		}
	}
}
void DrawBorder()
{
	system("cls");						//��ҳ������
	for (int x = 0; x < MAP_X; x++)
	{
		for (int y = 0; y < MAP_Y; y++)
		{
			if (g_MAP[x][y] == ��ͼ�߽�)
			{
				GotoxyAndPrint(x, y, "��");
			}
			if (g_MAP[x][y] == �Ҽ�Ȫˮ)
			{
				setColor(12, 0);
				GotoxyAndPrint(x, y, "��");
				setColor(7, 0);
			}
		}
	}
}
void DrawGameHelp()
{
	setColor(12, 0);
	GotoxyAndPrint(MAP_X / 2 - 10, 18, "����˵��");
	GotoxyAndPrint(MAP_X / 2 - 11, 20, "W: ��  S: ��");
	GotoxyAndPrint(MAP_X / 2 - 11, 22, "A: ��  D: ��");
	GotoxyAndPrint(MAP_X / 2 - 11, 24, "Q:  ��ͣ��Ϸ");
	GotoxyAndPrint(MAP_X / 2 - 11, 26, "�ո�: ����");
	setColor(7, 0);
}
void DrawTank(PTANK ptank, int who)
{
	if (ptank->isAlive == false) return;
	if (who == �ҷ�̹��)
	{
		setColor(10, 0);
		GotoxyAndPrint(ptank->core.X, ptank->core.Y, "��");//���ĵ�
		for (int i = 0; i < 5; i++)//������
		{
			GotoxyAndPrint(ptank->body[i].X, ptank->body[i].Y, "��");
		}
		setColor(7, 0);
	}
	else if (who == �з�̹��)
	{
		setColor(11, 0);//����ɫ
		if (ptank->blood == 2)
		{
			GotoxyAndPrint(ptank->core.X, ptank->core.Y, "��");//���ĵ�
			for (int i = 0; i < 5; i++)//������
				GotoxyAndPrint(ptank->body[i].X, ptank->body[i].Y, "��");//���ĵ�
		}
		else if (ptank->blood == 1)
		{
			GotoxyAndPrint(ptank->core.X, ptank->core.Y, "��");//���ĵ�
			for (int i = 0; i < 5; i++)//������
				GotoxyAndPrint(ptank->body[i].X, ptank->body[i].Y, "��");
		}
		setColor(7, 0);
	}
}
void DrawBullet(PBULLET pbullet, PTANK ptank)
{
	//�����߽磬���ɱ߽����ɫ��ʵ���ӵ���ʧ��Ч��
	if (pbullet->core.X <= 0 ||
		pbullet->core.X >= MAP_X_WALL / 2 ||
		pbullet->core.Y <= 0 ||
		pbullet->core.Y >= MAP_Y - 1)
	{
		setColor(7, 0);
	}
	else
	{
		if (ptank->who == �ҷ�̹��)
			setColor(10, 0);
		else if (ptank->who == �з�̹��)
			setColor(11, 0);
	}
	//�����ϰ������ӵ���Ϊ�ո�ʵ���ӵ���ʧ
	if (g_MAP[pbullet->core.X][pbullet->core.Y] == �����ϰ�)
	{
		GotoxyAndPrint(pbullet->core.X, pbullet->core.Y, "  ");
	}
	//����ʯ���ϰ����ʵ���ӵ���ʧ��Ч��
	else if (g_MAP[pbullet->core.X][pbullet->core.Y] == ʯ���ϰ�)
	{
		setColor(7, 0);
	}
	//����Ȫˮ�����ӵ���������ɫ����״��ʵ���ӵ���ʧ
	else if (g_MAP[pbullet->core.X][pbullet->core.Y] == �Ҽ�Ȫˮ)
	{
		setColor(12, 0);
		GotoxyAndPrint(pbullet->core.X, pbullet->core.Y, "��");
	}
	//һ���˶�״̬
	else
	{
		GotoxyAndPrint(pbullet->core.X, pbullet->core.Y, "��");
	}
	setColor(7, 0);
}
void DrawGameInfo(PTANK ptank, PTANK penemytank)
{
	//����̹����
	int eneTankCount = GetLiveEnemyAmount(penemytank);
	//��ǰ�Ѷ�
	char level[10];
	if (g_levelEneTank == 300) strcpy_s(level, 10, "��\0");
	else if (g_levelEneTank == 200) strcpy_s(level, 10, "һ��\0");
	else if (g_levelEneTank == 100)strcpy_s(level, 10, "����\0");
	//����or��ͣ״̬
	setColor(12, 0);
	GotoxyAndPrint(MAP_X / 2 - 14, 1, "RUNNING");
	GotoxyAndPrint(MAP_X / 2 - 14, 2, "Q: ��ͣ��Ϸ");
	setColor(7, 0);
	//��Ϸ��Ϣ��ӡ
	setColor(12, 0);
	GotoxyAndPrint(MAP_X / 2 - 11, 5, "");
	printf("��ǰ����: %d", ptank->blood);
	GotoxyAndPrint(MAP_X / 2 - 11, 7, "");
	printf("��ǰ����: %d", ENEMY_TANK_AMOUNT - eneTankCount);
	GotoxyAndPrint(MAP_X / 2 - 11, 9, "");
	printf("��̹����: %d", eneTankCount);
	GotoxyAndPrint(MAP_X / 2 - 11, 11, "");
	printf("��ǰ�Ѷ�: %s", level);
	setColor(7, 0);
}
void DrawMenu(const char** menu, int size, int index)
{
	system("cls");
	DrawLogo();
	//��ʾ��Ϣ
	for (int i = 0; i < size; i++)//�˵�����
	{
		if (i == index)
		{
			setColor(12, 0);
			GotoxyAndPrint(MAP_X / 4 - 5, MAP_Y / 2 - 6 + 2 * i, menu[i]);
			setColor(7, 0);
		}
		else
			GotoxyAndPrint(MAP_X / 4 - 5, MAP_Y / 2 - 6 + 2 * i, menu[i]);
	}
}

//̹�����
void CleanTankTail(COORD oldCore, PCOORD oldBody)
{
	GotoxyAndPrint(oldCore.X, oldCore.Y, "  ");//���ĵ�
	for (int i = 0; i < 5; i++)//������
	{
		GotoxyAndPrint(oldBody[i].X, oldBody[i].Y, "  ");
	}
}
void SetTankShape(PTANK ptank)
{
	if (ptank->isAlive == false) return;
	if (ptank->dir == UP)
	{
		ptank->body[0] = { ptank->core.X, ptank->core.Y - 1 };
		ptank->body[1] = { ptank->core.X - 1, ptank->core.Y };
		ptank->body[2] = { ptank->core.X + 1, ptank->core.Y };
		ptank->body[3] = { ptank->core.X - 1, ptank->core.Y + 1 };
		ptank->body[4] = { ptank->core.X + 1, ptank->core.Y + 1 };
	}
	else if (ptank->dir == DOWN)
	{
		ptank->body[0] = { ptank->core.X, ptank->core.Y + 1 };
		ptank->body[1] = { ptank->core.X - 1, ptank->core.Y };
		ptank->body[2] = { ptank->core.X + 1, ptank->core.Y };
		ptank->body[3] = { ptank->core.X - 1, ptank->core.Y - 1 };
		ptank->body[4] = { ptank->core.X + 1, ptank->core.Y - 1 };
	}
	else if (ptank->dir == LEFT)
	{
		ptank->body[0] = { ptank->core.X - 1, ptank->core.Y };
		ptank->body[1] = { ptank->core.X , ptank->core.Y + 1 };
		ptank->body[2] = { ptank->core.X , ptank->core.Y - 1 };
		ptank->body[3] = { ptank->core.X + 1, ptank->core.Y + 1 };
		ptank->body[4] = { ptank->core.X + 1, ptank->core.Y - 1 };
	}
	else if (ptank->dir == RIGHT)
	{
		ptank->body[0] = { ptank->core.X + 1, ptank->core.Y };
		ptank->body[1] = { ptank->core.X , ptank->core.Y + 1 };
		ptank->body[2] = { ptank->core.X , ptank->core.Y - 1 };
		ptank->body[3] = { ptank->core.X - 1, ptank->core.Y + 1 };
		ptank->body[4] = { ptank->core.X - 1, ptank->core.Y - 1 };
	}
}
int GetLiveEnemyAmount(PTANK penemytank)
{
	int count = 0;
	for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
	{
		if (penemytank[i].isAlive == true)
			count++;
	}
	return count;
}
void ManipulateMyTank(PTANK ptank, int who, PTANK penemytank)
{
	if (ptank->isAlive == false) return;
	if (who == �ҷ�̹��)
	{
		char ch = 0;
		if (_kbhit())				//���������� 
		{
			ch = _getch();			//�޻��Խ�������
			switch (ch)
			{
			case 'w':
				if (!IsMyTankMeetOther(ptank, UP, penemytank))
					ptank->core.Y--;
				ptank->dir = UP;
				break;
			case 's':
				if (!IsMyTankMeetOther(ptank, DOWN, penemytank))
					ptank->core.Y++;
				ptank->dir = DOWN;
				break;
			case 'a':
				if (!IsMyTankMeetOther(ptank, LEFT, penemytank))
					ptank->core.X--;
				ptank->dir = LEFT;
				break;
			case 'd':
				if (!IsMyTankMeetOther(ptank, RIGHT, penemytank))
					ptank->core.X++;
				ptank->dir = RIGHT;
				break;
			case ' ':
				if (ptank->bullet.state != �Ѹ�ֵ)
					ptank->bullet.state = δ��ֵ;//�Ѹ�ֵ������ʱ���ٿ��𣬲��ɸ�ֵΪ1��Ӧ����ʧΪ0ʱ����������Ч
				break;
			case 'q':
			{
				//��ͣ���ָ�
				mciSendString("pause bgm", NULL, 0, NULL);	//��ͣbgm
				setColor(12, 0);
				GotoxyAndPrint(MAP_X / 2 - 14, 1, "       ");//�Ȱѽϳ���running���
				GotoxyAndPrint(MAP_X / 2 - 14, 1, "PAUSE");
				GotoxyAndPrint(MAP_X / 2 - 14, 2, "1. �ص���Ϸ");
				GotoxyAndPrint(MAP_X / 2 - 14, 3, "2. �˳���Ϸ");
				char tmp;
				do
				{
					tmp = _getch();	//��������������ͣ��Ϸ
				} while (!(tmp == '1' || tmp == '2' || tmp == '3'));//ֻ������123�ſ�
				switch (tmp)
				{
				case '1'://�ָ���Ϸ
				{
					mciSendString("resume bgm", NULL, 0, NULL);//�ָ�bgm
					GotoxyAndPrint(MAP_X / 2 - 14, 1, "RUNNING");
					GotoxyAndPrint(MAP_X / 2 - 14, 2, "Q: ��ͣ��Ϸ");
					GotoxyAndPrint(MAP_X / 2 - 14, 3, "           ");
					GotoxyAndPrint(MAP_X / 2 - 14, 4, "           ");
					break;
				}
				case '2'://�˳���Ϸ
				{
					GotoxyAndPrint(MAP_X / 2 - 14, 1, "������˳�?");
					GotoxyAndPrint(MAP_X / 2 - 14, 2, "1. �����˳�");
					GotoxyAndPrint(MAP_X / 2 - 14, 3, "2. ֱ���˳�");
					char op = _getch();
					if (op == '1')		//�����˳�
					{
						SaveGame(ptank, penemytank);
						GameOver(penemytank);
						g_isRunning = false;
						break;
					}
					else if (op == '2')	//ֱ���˳�
					{
						GameOver(penemytank);
						g_isRunning = false;
						break;
					}
				}
				default:
					break;
				}
				break;
			}
			default:
				break;
			}
		}
	}
	SetTankShape(ptank);//ÿ���ƶ���Ҫ����������̬
}
void ManipulateEneTank(PTANK ptank, int who, PTANK pmytank, PTANK penemytank)
{
	if (ptank->isAlive == false) return;
	if (who == �з�̹��)
	{
		switch (rand() % 5)
		{
		case UP:
			if (!IsEneTankMeetOther(ptank, UP, pmytank, penemytank))
				ptank->core.Y--;
			ptank->dir = UP;
			break;
		case DOWN:
			if (!IsEneTankMeetOther(ptank, DOWN, pmytank, penemytank))
				ptank->core.Y++;
			ptank->dir = DOWN;
			break;
		case LEFT:
			if (!IsEneTankMeetOther(ptank, LEFT, pmytank, penemytank))
				ptank->core.X--;
			ptank->dir = LEFT;
			break;
		case RIGHT:
			if (!IsEneTankMeetOther(ptank, RIGHT, pmytank, penemytank))
				ptank->core.X++;
			ptank->dir = RIGHT;
			break;
		case 4:
			if (ptank->bullet.state != �Ѹ�ֵ)
				ptank->bullet.state = δ��ֵ;
			break;
		default:
			break;
		}
	}
	SetTankShape(ptank);//ÿ���ƶ���Ҫ����������̬
}
bool IsMyTankMeetOther(PTANK ptank, int dir, PTANK penemytank)
{
	switch (dir)
	{
	case UP:
		//�Ƿ�ײ�߽�
		if (ptank->core.Y <= 2)
		{
			return true;
		}
		//�Ƿ�ײ�ϰ���
		if ((g_MAP[ptank->core.X][ptank->core.Y - 2] == �����ϰ� ||
			g_MAP[ptank->core.X - 1][ptank->core.Y - 2] == �����ϰ� ||
			g_MAP[ptank->core.X + 1][ptank->core.Y - 2] == �����ϰ�) ||
			(g_MAP[ptank->core.X][ptank->core.Y - 2] == ʯ���ϰ� ||
				g_MAP[ptank->core.X - 1][ptank->core.Y - 2] == ʯ���ϰ� ||
				g_MAP[ptank->core.X + 1][ptank->core.Y - 2] == ʯ���ϰ�))
		{
			return true;
		}
		//�Ƿ�ײ�з�̹��
		for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
		{
			if (penemytank[i].isAlive == false) continue;
			if (
				((ptank->core.X == penemytank[i].core.X) && (ptank->core.Y - penemytank[i].core.Y == 3)) ||
				((ptank->core.X == penemytank[i].core.X - 1) && (ptank->core.Y - penemytank[i].core.Y == 3)) ||
				((ptank->core.X == penemytank[i].core.X - 2) && (ptank->core.Y - penemytank[i].core.Y == 3)) ||
				((ptank->core.X == penemytank[i].core.X + 1) && (ptank->core.Y - penemytank[i].core.Y == 3)) ||
				((ptank->core.X == penemytank[i].core.X + 2) && (ptank->core.Y - penemytank[i].core.Y == 3))
				)//Ҫ==3,����<=��ֻ���ڰ��ŵ�ʱ��ɱ��������С�ڣ���û���ŵ�̹1��������ȴС��2����2����
			{
				return true;
			}
		}
		break;
	case DOWN:
		//�Ƿ�ײ�߽�
		if (ptank->core.Y >= MAP_Y - 3)
		{
			return true;
		}
		//�Ƿ�ײ�ϰ���
		if ((g_MAP[ptank->core.X][ptank->core.Y + 2] == �����ϰ� ||
			g_MAP[ptank->core.X - 1][ptank->core.Y + 2] == �����ϰ� ||
			g_MAP[ptank->core.X + 1][ptank->core.Y + 2] == �����ϰ�) ||
			(g_MAP[ptank->core.X][ptank->core.Y + 2] == ʯ���ϰ� ||
				g_MAP[ptank->core.X - 1][ptank->core.Y + 2] == ʯ���ϰ� ||
				g_MAP[ptank->core.X + 1][ptank->core.Y + 2] == ʯ���ϰ�))
		{
			return true;
		}
		//�Ƿ������Ҽ�Ȫˮ
		if (g_MAP[ptank->core.X][ptank->core.Y] == �Ҽ�Ȫˮ)
		{
			return true;
		}
		//�Ƿ�ײ�з�̹��
		for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
		{
			if (penemytank[i].isAlive == false) continue;
			if (
				((ptank->core.X == penemytank[i].core.X) && (penemytank[i].core.Y - ptank->core.Y == 3)) ||
				((ptank->core.X == penemytank[i].core.X - 1) && (penemytank[i].core.Y - ptank->core.Y == 3)) ||
				((ptank->core.X == penemytank[i].core.X - 2) && (penemytank[i].core.Y - ptank->core.Y == 3)) ||
				((ptank->core.X == penemytank[i].core.X + 1) && (penemytank[i].core.Y - ptank->core.Y == 3)) ||
				((ptank->core.X == penemytank[i].core.X + 2) && (penemytank[i].core.Y - ptank->core.Y == 3))
				)
			{
				return true;
			}
		}
		break;
	case LEFT:
		//�Ƿ�ײ�߽�
		if (ptank->core.X <= 2)
		{
			return true;
		}
		//�Ƿ�ײ�ϰ���
		if ((g_MAP[ptank->core.X - 2][ptank->core.Y] == �����ϰ� ||
			g_MAP[ptank->core.X - 2][ptank->core.Y - 1] == �����ϰ� ||
			g_MAP[ptank->core.X - 2][ptank->core.Y + 1] == �����ϰ�) ||
			(g_MAP[ptank->core.X - 2][ptank->core.Y] == ʯ���ϰ� ||
				g_MAP[ptank->core.X - 2][ptank->core.Y - 1] == ʯ���ϰ� ||
				g_MAP[ptank->core.X - 2][ptank->core.Y + 1] == ʯ���ϰ�))
		{
			return true;
		}
		//�Ƿ������Ҽ�Ȫˮ
		if (g_MAP[ptank->core.X][ptank->core.Y] == �Ҽ�Ȫˮ)
		{
			return true;
		}
		//�Ƿ�ײ�з�̹��
		for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
		{
			if (penemytank[i].isAlive == false) continue;
			if (
				((ptank->core.Y == penemytank[i].core.Y) && (ptank->core.X - penemytank[i].core.X == 3)) ||
				((ptank->core.Y == penemytank[i].core.Y - 1) && (ptank->core.X - penemytank[i].core.X == 3)) ||
				((ptank->core.Y == penemytank[i].core.Y - 2) && (ptank->core.X - penemytank[i].core.X == 3)) ||
				((ptank->core.Y == penemytank[i].core.Y + 1) && (ptank->core.X - penemytank[i].core.X == 3)) ||
				((ptank->core.Y == penemytank[i].core.Y + 2) && (ptank->core.X - penemytank[i].core.X == 3))
				)
			{
				return true;
			}
		}
		break;
	case RIGHT:
		//�Ƿ�ײ�߽�
		if (ptank->core.X >= MAP_X_WALL / 2 - 2)
		{
			return true;
		}
		//�Ƿ�ײ�ϰ���
		if ((g_MAP[ptank->core.X + 2][ptank->core.Y] == �����ϰ� ||
			g_MAP[ptank->core.X + 2][ptank->core.Y - 1] == �����ϰ� ||
			g_MAP[ptank->core.X + 2][ptank->core.Y + 1] == �����ϰ�) ||
			(g_MAP[ptank->core.X + 2][ptank->core.Y] == ʯ���ϰ� ||
				g_MAP[ptank->core.X + 2][ptank->core.Y - 1] == ʯ���ϰ� ||
				g_MAP[ptank->core.X + 2][ptank->core.Y + 1] == ʯ���ϰ�))
		{
			return true;
		}
		//�Ƿ������Ҽ�Ȫˮ
		if (g_MAP[ptank->core.X][ptank->core.Y] == �Ҽ�Ȫˮ)
		{
			return true;
		}
		//�Ƿ�ײ�з�̹��
		for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
		{
			if (penemytank[i].isAlive == false) continue;
			if (
				((ptank->core.Y == penemytank[i].core.Y) && (penemytank[i].core.X - ptank->core.X == 3)) ||
				((ptank->core.Y == penemytank[i].core.Y - 1) && (penemytank[i].core.X - ptank->core.X == 3)) ||
				((ptank->core.Y == penemytank[i].core.Y - 2) && (penemytank[i].core.X - ptank->core.X == 3)) ||
				((ptank->core.Y == penemytank[i].core.Y + 1) && (penemytank[i].core.X - ptank->core.X == 3)) ||
				((ptank->core.Y == penemytank[i].core.Y + 2) && (penemytank[i].core.X - ptank->core.X == 3))
				)
			{
				return true;
			}
		}
		break;
	default:
		break;
	}
	return false;
}
bool IsEneTankMeetOther(PTANK ptank, int dir, PTANK pmytank, PTANK penemytank)
{
	switch (dir)
	{
	case UP:
		//�Ƿ�ײ�߽�
		if (ptank->core.Y <= 2)
		{
			return true;
		}
		//�Ƿ�ײ�ϰ���
		if ((g_MAP[ptank->core.X][ptank->core.Y - 2] == �����ϰ� ||
			g_MAP[ptank->core.X - 1][ptank->core.Y - 2] == �����ϰ� ||
			g_MAP[ptank->core.X + 1][ptank->core.Y - 2] == �����ϰ�) ||
			(g_MAP[ptank->core.X][ptank->core.Y - 2] == ʯ���ϰ� ||
				g_MAP[ptank->core.X - 1][ptank->core.Y - 2] == ʯ���ϰ� ||
				g_MAP[ptank->core.X + 1][ptank->core.Y - 2] == ʯ���ϰ�))
		{
			return true;
		}
		//�Ƿ�ײ�ҷ�̹��
		if (
			((ptank->core.X == pmytank->core.X - 0) && (ptank->core.Y - pmytank->core.Y == 3)) ||
			((ptank->core.X == pmytank->core.X - 1) && (ptank->core.Y - pmytank->core.Y == 3)) ||
			((ptank->core.X == pmytank->core.X - 2) && (ptank->core.Y - pmytank->core.Y == 3)) ||
			((ptank->core.X == pmytank->core.X + 1) && (ptank->core.Y - pmytank->core.Y == 3)) ||
			((ptank->core.X == pmytank->core.X + 2) && (ptank->core.Y - pmytank->core.Y == 3))
			)//Ҫ==3,����<=��ֻ���ڰ��ŵ�ʱ��ɱ��������С�ڣ���û���ŵ�̹1��������ȴС��2����2����
		{
			return true;
		}
		//�Ƿ�ײ�����з�̹��
		for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
		{
			if (ptank->core.X == penemytank[i].core.X && ptank->core.Y == penemytank[i].core.Y)//�ų��Լ�
				continue;
			if (
				((ptank->core.X == penemytank[i].core.X) && (ptank->core.Y - penemytank[i].core.Y == 3)) ||
				((ptank->core.X == penemytank[i].core.X - 1) && (ptank->core.Y - penemytank[i].core.Y == 3)) ||
				((ptank->core.X == penemytank[i].core.X - 2) && (ptank->core.Y - penemytank[i].core.Y == 3)) ||
				((ptank->core.X == penemytank[i].core.X + 1) && (ptank->core.Y - penemytank[i].core.Y == 3)) ||
				((ptank->core.X == penemytank[i].core.X + 2) && (ptank->core.Y - penemytank[i].core.Y == 3))
				)//Ҫ==3,����<=��ֻ���ڰ��ŵ�ʱ��ɱ��������С�ڣ���û���ŵ�̹1��������ȴС��2����2����
			{
				return true;
			}
		}
		break;
	case DOWN:
		//�Ƿ�ײ�߽�
		if (ptank->core.Y >= MAP_Y - 3)
		{
			return true;
		}
		//�Ƿ�ײ�ϰ���
		if ((g_MAP[ptank->core.X][ptank->core.Y + 2] == �����ϰ� ||
			g_MAP[ptank->core.X - 1][ptank->core.Y + 2] == �����ϰ� ||
			g_MAP[ptank->core.X + 1][ptank->core.Y + 2] == �����ϰ�) ||
			(g_MAP[ptank->core.X][ptank->core.Y + 2] == ʯ���ϰ� ||
				g_MAP[ptank->core.X - 1][ptank->core.Y + 2] == ʯ���ϰ� ||
				g_MAP[ptank->core.X + 1][ptank->core.Y + 2] == ʯ���ϰ�))
		{
			return true;
		}
		//�Ƿ������Ҽ�Ȫˮ
		if (g_MAP[ptank->core.X][ptank->core.Y] == �Ҽ�Ȫˮ)
		{
			return true;
		}
		//�Ƿ�ײ�ҷ�̹��
		if (
			((ptank->core.X == pmytank->core.X - 0) && (pmytank->core.Y - ptank->core.Y == 3)) ||
			((ptank->core.X == pmytank->core.X - 1) && (pmytank->core.Y - ptank->core.Y == 3)) ||
			((ptank->core.X == pmytank->core.X - 2) && (pmytank->core.Y - ptank->core.Y == 3)) ||
			((ptank->core.X == pmytank->core.X + 1) && (pmytank->core.Y - ptank->core.Y == 3)) ||
			((ptank->core.X == pmytank->core.X + 2) && (pmytank->core.Y - ptank->core.Y == 3))
			)
		{
			return true;
		}
		//�Ƿ�ײ�����з�̹��
		for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
		{
			if (ptank->core.X == penemytank[i].core.X && ptank->core.Y == penemytank[i].core.Y)//�ų��Լ�
				continue;
			if (
				((ptank->core.X == penemytank[i].core.X) && (penemytank[i].core.Y - ptank->core.Y == 3)) ||
				((ptank->core.X == penemytank[i].core.X - 1) && (penemytank[i].core.Y - ptank->core.Y == 3)) ||
				((ptank->core.X == penemytank[i].core.X - 2) && (penemytank[i].core.Y - ptank->core.Y == 3)) ||
				((ptank->core.X == penemytank[i].core.X + 1) && (penemytank[i].core.Y - ptank->core.Y == 3)) ||
				((ptank->core.X == penemytank[i].core.X + 2) && (penemytank[i].core.Y - ptank->core.Y == 3))
				)
			{
				return true;
			}
		}
		break;
	case LEFT:
		//�Ƿ�ײ�߽�
		if (ptank->core.X <= 2)
		{
			return true;
		}
		//�Ƿ�ײ�ϰ���
		if ((g_MAP[ptank->core.X - 2][ptank->core.Y] == �����ϰ� ||
			g_MAP[ptank->core.X - 2][ptank->core.Y - 1] == �����ϰ� ||
			g_MAP[ptank->core.X - 2][ptank->core.Y + 1] == �����ϰ�) ||
			(g_MAP[ptank->core.X - 2][ptank->core.Y] == ʯ���ϰ� ||
				g_MAP[ptank->core.X - 2][ptank->core.Y - 1] == ʯ���ϰ� ||
				g_MAP[ptank->core.X - 2][ptank->core.Y + 1] == ʯ���ϰ�))
		{
			return true;
		}
		//�Ƿ������Ҽ�Ȫˮ
		if (g_MAP[ptank->core.X][ptank->core.Y] == �Ҽ�Ȫˮ)
		{
			return true;
		}
		//�Ƿ�ײ�ҷ�̹��
		if (
			((ptank->core.Y == pmytank->core.Y - 0) && (ptank->core.X - pmytank->core.X == 3)) ||
			((ptank->core.Y == pmytank->core.Y - 1) && (ptank->core.X - pmytank->core.X == 3)) ||
			((ptank->core.Y == pmytank->core.Y - 2) && (ptank->core.X - pmytank->core.X == 3)) ||
			((ptank->core.Y == pmytank->core.Y + 1) && (ptank->core.X - pmytank->core.X == 3)) ||
			((ptank->core.Y == pmytank->core.Y + 2) && (ptank->core.X - pmytank->core.X == 3))
			)
		{
			return true;
		}
		//�Ƿ�ײ�����з�̹��
		for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
		{
			if (ptank->core.X == penemytank[i].core.X && ptank->core.Y == penemytank[i].core.Y)//�ų��Լ�
				continue;
			if (
				((ptank->core.Y == penemytank[i].core.Y) && (ptank->core.X - penemytank[i].core.X == 3)) ||
				((ptank->core.Y == penemytank[i].core.Y - 1) && (ptank->core.X - penemytank[i].core.X == 3)) ||
				((ptank->core.Y == penemytank[i].core.Y - 2) && (ptank->core.X - penemytank[i].core.X == 3)) ||
				((ptank->core.Y == penemytank[i].core.Y + 1) && (ptank->core.X - penemytank[i].core.X == 3)) ||
				((ptank->core.Y == penemytank[i].core.Y + 2) && (ptank->core.X - penemytank[i].core.X == 3))
				)
			{
				return true;
			}
		}
		break;
	case RIGHT:
		//�Ƿ�ײ�߽�
		if (ptank->core.X >= MAP_X_WALL / 2 - 2)
		{
			return true;
		}
		//�Ƿ�ײ�ϰ���
		if ((g_MAP[ptank->core.X + 2][ptank->core.Y] == �����ϰ� ||
			g_MAP[ptank->core.X + 2][ptank->core.Y - 1] == �����ϰ� ||
			g_MAP[ptank->core.X + 2][ptank->core.Y + 1] == �����ϰ�) ||
			(g_MAP[ptank->core.X + 2][ptank->core.Y] == ʯ���ϰ� ||
				g_MAP[ptank->core.X + 2][ptank->core.Y - 1] == ʯ���ϰ� ||
				g_MAP[ptank->core.X + 2][ptank->core.Y + 1] == ʯ���ϰ�))
		{
			return true;
		}
		//�Ƿ������Ҽ�Ȫˮ
		if (g_MAP[ptank->core.X][ptank->core.Y] == �Ҽ�Ȫˮ)
		{
			return true;
		}
		//�Ƿ�ײ�ҷ�̹��
		if (
			((ptank->core.Y == pmytank->core.Y - 0) && (pmytank->core.X - ptank->core.X == 3)) ||
			((ptank->core.Y == pmytank->core.Y - 1) && (pmytank->core.X - ptank->core.X == 3)) ||
			((ptank->core.Y == pmytank->core.Y - 2) && (pmytank->core.X - ptank->core.X == 3)) ||
			((ptank->core.Y == pmytank->core.Y + 1) && (pmytank->core.X - ptank->core.X == 3)) ||
			((ptank->core.Y == pmytank->core.Y + 2) && (pmytank->core.X - ptank->core.X == 3))
			)
		{
			return true;
		}
		//�Ƿ�ײ�����з�̹��
		for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
		{
			if (ptank->core.X == penemytank[i].core.X && ptank->core.Y == penemytank[i].core.Y)//�ų��Լ�
				continue;
			if (
				((ptank->core.Y == penemytank[i].core.Y) && (penemytank[i].core.X - ptank->core.X == 3)) ||
				((ptank->core.Y == penemytank[i].core.Y - 1) && (penemytank[i].core.X - ptank->core.X == 3)) ||
				((ptank->core.Y == penemytank[i].core.Y - 2) && (penemytank[i].core.X - ptank->core.X == 3)) ||
				((ptank->core.Y == penemytank[i].core.Y + 1) && (penemytank[i].core.X - ptank->core.X == 3)) ||
				((ptank->core.Y == penemytank[i].core.Y + 2) && (penemytank[i].core.X - ptank->core.X == 3))
				)
			{
				return true;
			}
		}
		break;
	default:
		break;
	}
	return false;
}

//�ӵ����
void MoveBullet(PBULLET pbullet)
{
	switch (pbullet->dir)
	{
	case UP:
		pbullet->core.Y--;
		break;
	case DOWN:
		pbullet->core.Y++;
		break;
	case LEFT:
		pbullet->core.X--;
		break;
	case RIGHT:
		pbullet->core.X++;
		break;
	default:
		break;
	}
}
void CleanBullet(COORD oldBulCore)
{
	GotoxyAndPrint(oldBulCore.X, oldBulCore.Y, "  ");
	//printf("  ");
}
void IsMyBulMeetOther(PBULLET pbullet, PTANK penemytank, PTANK ptank)
{
	//���߽�
	if (pbullet->core.X <= 0 ||
		pbullet->core.X >= MAP_X_WALL / 2 ||
		pbullet->core.Y <= 0 ||
		pbullet->core.Y >= MAP_Y - 1)
	{
		pbullet->state = ������;
	}
	//�������ϰ�
	if (g_MAP[pbullet->core.X][pbullet->core.Y] == �����ϰ�)
	{
		pbullet->state = ������;
		g_MAP[pbullet->core.X][pbullet->core.Y] = �յ�;
	}
	//��ʯ���ϰ�
	if (g_MAP[pbullet->core.X][pbullet->core.Y] == ʯ���ϰ�)
	{
		pbullet->state = ������;
	}
	//��Ȫˮ
	if (g_MAP[pbullet->core.X][pbullet->core.Y] == �Ҽ�Ȫˮ)
	{
		pbullet->state = ������;
	}
	//���з�̹��
	for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
	{
		if (penemytank[i].isAlive == false) continue;
		switch (pbullet->dir)
		{
		case UP:
			if (
				(pbullet->core.X == penemytank[i].core.X) && (pbullet->core.Y - penemytank[i].core.Y == 0) ||
				(pbullet->core.X == penemytank[i].body[0].X) && (pbullet->core.Y - penemytank[i].body[0].Y == 0) ||
				(pbullet->core.X == penemytank[i].body[1].X) && (pbullet->core.Y - penemytank[i].body[1].Y == 0) ||
				(pbullet->core.X == penemytank[i].body[2].X) && (pbullet->core.Y - penemytank[i].body[2].Y == 0) ||
				(pbullet->core.X == penemytank[i].body[3].X) && (pbullet->core.Y - penemytank[i].body[3].Y == 0) ||
				(pbullet->core.X == penemytank[i].body[4].X) && (pbullet->core.Y - penemytank[i].body[4].Y == 0)
				)
			{
				PlaySound(TEXT("conf/duang.wav"), NULL, SND_FILENAME | SND_ASYNC);//������Ч
				pbullet->state = ������;
				penemytank[i].blood--;
				if (penemytank[i].blood == 0)//��Ѫ��Ϊ0������
					penemytank[i].isAlive = false;
				if (!penemytank[i].isAlive && (ENEMY_TANK_AMOUNT - GetLiveEnemyAmount(penemytank)) % 3 == 0)//ÿ������������ֵ+1
					(ptank->blood)++;//Ҫ��!penemytank[i].isAlive��Ҫ���򵽶������ĵ�̹Ҳ����
			}
			break;
		case DOWN:
			if (
				(pbullet->core.X == penemytank[i].core.X) && (pbullet->core.Y - penemytank[i].core.Y == 0) ||
				(pbullet->core.X == penemytank[i].body[0].X) && (pbullet->core.Y - penemytank[i].body[0].Y == 0) ||
				(pbullet->core.X == penemytank[i].body[1].X) && (pbullet->core.Y - penemytank[i].body[1].Y == 0) ||
				(pbullet->core.X == penemytank[i].body[2].X) && (pbullet->core.Y - penemytank[i].body[2].Y == 0) ||
				(pbullet->core.X == penemytank[i].body[3].X) && (pbullet->core.Y - penemytank[i].body[3].Y == 0) ||
				(pbullet->core.X == penemytank[i].body[4].X) && (pbullet->core.Y - penemytank[i].body[4].Y == 0)
				)
			{
				PlaySound(TEXT("conf/duang.wav"), NULL, SND_FILENAME | SND_ASYNC);//������Ч
				pbullet->state = ������;
				penemytank[i].blood--;
				if (penemytank[i].blood == 0)//��Ѫ��Ϊ0������
					penemytank[i].isAlive = false;
				if (!penemytank[i].isAlive && (ENEMY_TANK_AMOUNT - GetLiveEnemyAmount(penemytank)) % 3 == 0)//ÿ������������ֵ+1
					(ptank->blood)++;
			}
			break;
		case LEFT:
			if (
				(pbullet->core.X == penemytank[i].core.X) && (pbullet->core.Y - penemytank[i].core.Y == 0) ||
				(pbullet->core.X == penemytank[i].body[0].X) && (pbullet->core.Y - penemytank[i].body[0].Y == 0) ||
				(pbullet->core.X == penemytank[i].body[1].X) && (pbullet->core.Y - penemytank[i].body[1].Y == 0) ||
				(pbullet->core.X == penemytank[i].body[2].X) && (pbullet->core.Y - penemytank[i].body[2].Y == 0) ||
				(pbullet->core.X == penemytank[i].body[3].X) && (pbullet->core.Y - penemytank[i].body[3].Y == 0) ||
				(pbullet->core.X == penemytank[i].body[4].X) && (pbullet->core.Y - penemytank[i].body[4].Y == 0)
				)
			{
				PlaySound(TEXT("conf/duang.wav"), NULL, SND_FILENAME | SND_ASYNC);//������Ч
				pbullet->state = ������;
				penemytank[i].blood--;
				if (penemytank[i].blood == 0)//��Ѫ��Ϊ0������
					penemytank[i].isAlive = false;
				if (!penemytank[i].isAlive && (ENEMY_TANK_AMOUNT - GetLiveEnemyAmount(penemytank)) % 3 == 0)//ÿ������������ֵ+1
					(ptank->blood)++;
			}
			break;
		case RIGHT:
			if (
				(pbullet->core.X == penemytank[i].core.X) && (pbullet->core.Y - penemytank[i].core.Y == 0) ||
				(pbullet->core.X == penemytank[i].body[0].X) && (pbullet->core.Y - penemytank[i].body[0].Y == 0) ||
				(pbullet->core.X == penemytank[i].body[1].X) && (pbullet->core.Y - penemytank[i].body[1].Y == 0) ||
				(pbullet->core.X == penemytank[i].body[2].X) && (pbullet->core.Y - penemytank[i].body[2].Y == 0) ||
				(pbullet->core.X == penemytank[i].body[3].X) && (pbullet->core.Y - penemytank[i].body[3].Y == 0) ||
				(pbullet->core.X == penemytank[i].body[4].X) && (pbullet->core.Y - penemytank[i].body[4].Y == 0)
				)
			{
				PlaySound(TEXT("conf/duang.wav"), NULL, SND_FILENAME | SND_ASYNC);//������Ч
				pbullet->state = ������;
				penemytank[i].blood--;
				if (penemytank[i].blood == 0)//��Ѫ��Ϊ0������
					penemytank[i].isAlive = false;
				if (!penemytank[i].isAlive && (ENEMY_TANK_AMOUNT - GetLiveEnemyAmount(penemytank)) % 3 == 0)//ÿ������������ֵ+1
					(ptank->blood)++;
			}
			break;
		default:
			break;
		}
	}
}
void IsEneBulMeetOther(PBULLET pbullet, PTANK penemytank, PTANK ptank)
{
	//���߽�
	if (pbullet->core.X <= 0 ||
		pbullet->core.X >= MAP_X_WALL / 2 ||
		pbullet->core.Y <= 0 ||
		pbullet->core.Y >= MAP_Y - 1)
	{
		pbullet->state = ������;
	}
	//�������ϰ�
	if (g_MAP[pbullet->core.X][pbullet->core.Y] == �����ϰ�)
	{
		pbullet->state = ������;
		g_MAP[pbullet->core.X][pbullet->core.Y] = �յ�;
	}
	//��ʯ���ϰ�
	if (g_MAP[pbullet->core.X][pbullet->core.Y] == ʯ���ϰ�)
	{
		pbullet->state = ������;
	}
	//��Ȫˮ
	if (g_MAP[pbullet->core.X][pbullet->core.Y] == �Ҽ�Ȫˮ)
	{
		pbullet->state = ������;
		ptank->blood = 0;//Ȫˮ�򵽣��ҷ�̹�˵���ȥ��
	}
	//�����ҷ�̹��
	switch (pbullet->dir)
	{
	case UP:
		if (
			(pbullet->core.X == ptank->core.X) && (pbullet->core.Y - ptank->core.Y == 0) ||
			(pbullet->core.X == ptank->body[0].X) && (pbullet->core.Y - ptank->body[0].Y == 0) ||
			(pbullet->core.X == ptank->body[1].X) && (pbullet->core.Y - ptank->body[1].Y == 0) ||
			(pbullet->core.X == ptank->body[2].X) && (pbullet->core.Y - ptank->body[2].Y == 0) ||
			(pbullet->core.X == ptank->body[3].X) && (pbullet->core.Y - ptank->body[3].Y == 0) ||
			(pbullet->core.X == ptank->body[4].X) && (pbullet->core.Y - ptank->body[4].Y == 0)
			)
		{
			PlaySound(TEXT("conf/duang.wav"), NULL, SND_FILENAME | SND_ASYNC);//������Ч
			pbullet->state = ������;
			(ptank->blood)--;
			if (ptank->blood == 0)//�����Ѫ��Ϊ0
				ptank->isAlive = false;//����Ϊ����
		}
		break;
	case DOWN:
		if (
			(pbullet->core.X == ptank->core.X) && (pbullet->core.Y - ptank->core.Y == 0) ||
			(pbullet->core.X == ptank->body[0].X) && (pbullet->core.Y - ptank->body[0].Y == 0) ||
			(pbullet->core.X == ptank->body[1].X) && (pbullet->core.Y - ptank->body[1].Y == 0) ||
			(pbullet->core.X == ptank->body[2].X) && (pbullet->core.Y - ptank->body[2].Y == 0) ||
			(pbullet->core.X == ptank->body[3].X) && (pbullet->core.Y - ptank->body[3].Y == 0) ||
			(pbullet->core.X == ptank->body[4].X) && (pbullet->core.Y - ptank->body[4].Y == 0)
			)
		{
			PlaySound(TEXT("conf/duang.wav"), NULL, SND_FILENAME | SND_ASYNC);//������Ч
			pbullet->state = ������;
			(ptank->blood)--;
			if (ptank->blood == 0)//�����Ѫ��Ϊ0
				ptank->isAlive = false;//����Ϊ����
		}
		break;
	case LEFT:
		if (
			(pbullet->core.X == ptank->core.X) && (pbullet->core.Y - ptank->core.Y == 0) ||
			(pbullet->core.X == ptank->body[0].X) && (pbullet->core.Y - ptank->body[0].Y == 0) ||
			(pbullet->core.X == ptank->body[1].X) && (pbullet->core.Y - ptank->body[1].Y == 0) ||
			(pbullet->core.X == ptank->body[2].X) && (pbullet->core.Y - ptank->body[2].Y == 0) ||
			(pbullet->core.X == ptank->body[3].X) && (pbullet->core.Y - ptank->body[3].Y == 0) ||
			(pbullet->core.X == ptank->body[4].X) && (pbullet->core.Y - ptank->body[4].Y == 0)
			)
		{
			PlaySound(TEXT("conf/duang.wav"), NULL, SND_FILENAME | SND_ASYNC);//������Ч
			pbullet->state = ������;
			(ptank->blood)--;
			if (ptank->blood == 0)//�����Ѫ��Ϊ0
				ptank->isAlive = false;//����Ϊ����
		}
		break;
	case RIGHT:
		if (
			(pbullet->core.X == ptank->core.X) && (pbullet->core.Y - ptank->core.Y == 0) ||
			(pbullet->core.X == ptank->body[0].X) && (pbullet->core.Y - ptank->body[0].Y == 0) ||
			(pbullet->core.X == ptank->body[1].X) && (pbullet->core.Y - ptank->body[1].Y == 0) ||
			(pbullet->core.X == ptank->body[2].X) && (pbullet->core.Y - ptank->body[2].Y == 0) ||
			(pbullet->core.X == ptank->body[3].X) && (pbullet->core.Y - ptank->body[3].Y == 0) ||
			(pbullet->core.X == ptank->body[4].X) && (pbullet->core.Y - ptank->body[4].Y == 0)
			)
		{
			PlaySound(TEXT("conf/duang.wav"), NULL, SND_FILENAME | SND_ASYNC);//������Ч
			pbullet->state = ������;
			(ptank->blood)--;
			if (ptank->blood == 0)//�����Ѫ��Ϊ0
				ptank->isAlive = false;//����Ϊ����
		}
		break;
	default:
		break;
	}
	//�������з�̹��
	for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
	{
		if (penemytank[i].isAlive == false) continue;
		switch (pbullet->dir)
		{
		case UP:
			if (
				(pbullet->core.X == penemytank[i].core.X) && (pbullet->core.Y - penemytank[i].core.Y == 0) ||
				(pbullet->core.X == penemytank[i].body[0].X) && (pbullet->core.Y - penemytank[i].body[0].Y == 0) ||
				(pbullet->core.X == penemytank[i].body[1].X) && (pbullet->core.Y - penemytank[i].body[1].Y == 0) ||
				(pbullet->core.X == penemytank[i].body[2].X) && (pbullet->core.Y - penemytank[i].body[2].Y == 0) ||
				(pbullet->core.X == penemytank[i].body[3].X) && (pbullet->core.Y - penemytank[i].body[3].Y == 0) ||
				(pbullet->core.X == penemytank[i].body[4].X) && (pbullet->core.Y - penemytank[i].body[4].Y == 0)
				)
			{
				pbullet->state = ������;
			}
			break;
		case DOWN:
			if (
				(pbullet->core.X == penemytank[i].core.X) && (pbullet->core.Y - penemytank[i].core.Y == 0) ||
				(pbullet->core.X == penemytank[i].body[0].X) && (pbullet->core.Y - penemytank[i].body[0].Y == 0) ||
				(pbullet->core.X == penemytank[i].body[1].X) && (pbullet->core.Y - penemytank[i].body[1].Y == 0) ||
				(pbullet->core.X == penemytank[i].body[2].X) && (pbullet->core.Y - penemytank[i].body[2].Y == 0) ||
				(pbullet->core.X == penemytank[i].body[3].X) && (pbullet->core.Y - penemytank[i].body[3].Y == 0) ||
				(pbullet->core.X == penemytank[i].body[4].X) && (pbullet->core.Y - penemytank[i].body[4].Y == 0)
				)
			{
				pbullet->state = ������;
			}
			break;
		case LEFT:
			if (
				(pbullet->core.X == penemytank[i].core.X) && (pbullet->core.Y - penemytank[i].core.Y == 0) ||
				(pbullet->core.X == penemytank[i].body[0].X) && (pbullet->core.Y - penemytank[i].body[0].Y == 0) ||
				(pbullet->core.X == penemytank[i].body[1].X) && (pbullet->core.Y - penemytank[i].body[1].Y == 0) ||
				(pbullet->core.X == penemytank[i].body[2].X) && (pbullet->core.Y - penemytank[i].body[2].Y == 0) ||
				(pbullet->core.X == penemytank[i].body[3].X) && (pbullet->core.Y - penemytank[i].body[3].Y == 0) ||
				(pbullet->core.X == penemytank[i].body[4].X) && (pbullet->core.Y - penemytank[i].body[4].Y == 0)
				)
			{
				pbullet->state = ������;
			}
			break;
		case RIGHT:
			if (
				(pbullet->core.X == penemytank[i].core.X) && (pbullet->core.Y - penemytank[i].core.Y == 0) ||
				(pbullet->core.X == penemytank[i].body[0].X) && (pbullet->core.Y - penemytank[i].body[0].Y == 0) ||
				(pbullet->core.X == penemytank[i].body[1].X) && (pbullet->core.Y - penemytank[i].body[1].Y == 0) ||
				(pbullet->core.X == penemytank[i].body[2].X) && (pbullet->core.Y - penemytank[i].body[2].Y == 0) ||
				(pbullet->core.X == penemytank[i].body[3].X) && (pbullet->core.Y - penemytank[i].body[3].Y == 0) ||
				(pbullet->core.X == penemytank[i].body[4].X) && (pbullet->core.Y - penemytank[i].body[4].Y == 0)
				)
			{
				pbullet->state = ������;
			}
			break;
		default:
			break;
		}
	}
}

//��ͼ���
char* ShowMapFile()
{
	//����ָ��Ŀ¼����׺���ļ�������������
	char* mapFiles[10] = { nullptr };
	long Handle;
	struct _finddata_t FileInfo;
	int count = 0;
	if ((Handle = _findfirst("conf/map/*.i", &FileInfo)) == -1L)
		printf("Not Found\n");
	else
	{
		mapFiles[count] = (char*)malloc(20);
		strcpy_s(mapFiles[count], 20, FileInfo.name);
		//g_Maps[count] = FileInfo.name;
		count++;
		while (_findnext(Handle, &FileInfo) == 0)
		{
			mapFiles[count] = (char*)malloc(20);
			strcpy_s(mapFiles[count], 20, FileInfo.name);
			//g_Maps[count] = FileInfo.name;
			count++;
		}
		_findclose(Handle);
	}
	//��ʾ��ͼ�ļ�
	system("cls");
	GotoxyAndPrint(MAP_X / 4 - 5, MAP_Y / 2 - 8, "��ѡ���ͼ");
	int i = 0;								//ѭ��������for�ⶨ��
	for (; i < count; i++)
	{
		GotoxyAndPrint(MAP_X / 4 - 5, MAP_Y / 2 - 6 + i, "");
		printf("%d.%s", i + 1, mapFiles[i]);
	}
	//ѡ��
	GotoxyAndPrint(MAP_X / 4 - 5, MAP_Y / 2 - 6 + i, "������ѡ��-> ");
	SetCursorState(true);
	int input = _getch() - '0';				//��֤0-9����ASCII
	SetCursorState(false);
	char* _file = (char*)malloc(15);
	strcpy_s(_file, 15, mapFiles[input - 1]);//����ʼ��1�����±�ʼ��0	
	return _file;
}
void SetDefaultMap()
{
	for (int x = 0; x < MAP_X_WALL; x++)
	{
		for (int y = 0; y < MAP_Y; y++)
		{
			if (
				(x > MAP_X_WALL / 4 - 9 && x < MAP_X_WALL / 4 - 5 && y > MAP_Y / 2 - 8 && y < MAP_Y / 2 - 4) ||
				(x < MAP_X_WALL / 4 + 9 && x > MAP_X_WALL / 4 + 5 && y > MAP_Y / 2 - 8 && y < MAP_Y / 2 - 4) ||
				(x > MAP_X_WALL / 4 - 9 && x < MAP_X_WALL / 4 - 5 && y < MAP_Y / 2 + 6 && y > MAP_Y / 2 + 2) ||
				(x < MAP_X_WALL / 4 + 9 && x > MAP_X_WALL / 4 + 5 && y < MAP_Y / 2 + 6 && y > MAP_Y / 2 + 2)
				)
			{
				g_MAP[x][y] = �����ϰ�;
			}
			if (
				(x > MAP_X_WALL / 4 - 9 && x < MAP_X_WALL / 4 - 5 && y > MAP_Y / 2 - 9 && y < MAP_Y / 2 - 7) ||
				(x < MAP_X_WALL / 4 + 9 && x > MAP_X_WALL / 4 + 5 && y > MAP_Y / 2 - 9 && y < MAP_Y / 2 - 7) ||
				(x > MAP_X_WALL / 4 - 9 && x < MAP_X_WALL / 4 - 5 && y < MAP_Y / 2 + 7 && y > MAP_Y / 2 + 5) ||
				(x < MAP_X_WALL / 4 + 9 && x > MAP_X_WALL / 4 + 5 && y < MAP_Y / 2 + 7 && y > MAP_Y / 2 + 5)
				)
			{
				g_MAP[x][y] = ʯ���ϰ�;
			}
		}
	}
}
void LoadMapFile(char* str)
{
	char* filename = (char*)malloc(40);
	sprintf_s(filename, 40, "%s%s", "conf/map/", str);
	FILE* pFile = NULL;
	errno_t err = fopen_s(&pFile, filename, "rb");
	for (int x = 0; x < MAP_X_WALL; x++)
	{
		for (int y = 0; y < MAP_Y; y++)
		{
			fread(&g_MAP[x][y], sizeof(int), 1, pFile);
		}
	}
	fclose(pFile);
}
void CustomizeMap(PTANK ptank, PTANK penemytank)
{
	DrawBorder();		//��ͼ�߽�
	//��ʾ��Ϣ
	setColor(12, 0);
	GotoxyAndPrint(MAP_X / 2 - 12, 2, "     �༭��ͼ");
	GotoxyAndPrint(MAP_X / 2 - 12, 4, "�����������������");
	GotoxyAndPrint(MAP_X / 2 - 12, 6, "���ֵ���������ʯ��");
	GotoxyAndPrint(MAP_X / 2 - 12, 8, "�Ҽ������������ϰ�");
	GotoxyAndPrint(MAP_X / 2 - 12, 10, "����˫�����˳��༭");
	setColor(7, 0);
	//����¼����
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD ir = {};
	DWORD dwCount = 0;
	SetConsoleMode(hInput, ENABLE_MOUSE_INPUT);
	//��������¼�����������Ļ
	while (true)
	{
		ReadConsoleInput(hInput, &ir, 1, &dwCount);
		if (ir.EventType == MOUSE_EVENT)
		{
			//������������ϰ�
			if (ir.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			{
				COORD pos = ir.Event.MouseEvent.dwMousePosition;//��ȡ������λ��
				//�������ҷ�̹�˴�����
				if (pos.X / 2 >= ptank->core.X - 1 &&
					pos.X / 2 <= ptank->core.X + 1 &&
					pos.Y >= ptank->core.Y - 1 &&
					pos.Y <= ptank->core.Y + 1)
					continue;
				//�������ҷ�̹�˻���
				int flag = 0;
				for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
				{
					if (pos.X / 2 >= penemytank[i].core.X - 1 &&
						pos.X / 2 <= penemytank[i].core.X + 1 &&
						pos.Y >= penemytank[i].core.Y - 1 &&
						pos.Y <= penemytank[i].core.Y + 1)
						flag = 1;
					//continue;//�������Ǵ�for
				}
				if (flag == 1) continue;
				//������Ȫˮ����
				if (pos.X / 2 >= MAP_X_WALL / 4 &&
					pos.X / 2 <= MAP_X_WALL / 4 + 1 &&
					pos.Y >= MAP_Y - 2 - 1 &&
					pos.Y <= MAP_Y - 2) continue;
				//�ɻ��ƴ������߽硢̹�ˡ�Ȫˮ��
				if (pos.X > 1 && pos.X < MAP_X_WALL && pos.Y >0 && pos.Y < MAP_Y - 1)
				{
					g_MAP[pos.X / 2][pos.Y] = �����ϰ�;
					GotoxyAndPrint(pos.X / 2, pos.Y, "��");
				}
			}
			//���ֻ���ʯ���ϰ�
			if (ir.Event.MouseEvent.dwButtonState == FROM_LEFT_2ND_BUTTON_PRESSED)
			{
				COORD pos = ir.Event.MouseEvent.dwMousePosition;//��ȡ������λ��
				//�������ҷ�̹�˴�����
				if (pos.X / 2 >= ptank->core.X - 1 &&
					pos.X / 2 <= ptank->core.X + 1 &&
					pos.Y >= ptank->core.Y - 1 &&
					pos.Y <= ptank->core.Y + 1)
					continue;
				//�������ҷ�̹�˻���
				int flag = 0;
				for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
				{
					if (pos.X / 2 >= penemytank[i].core.X - 1 &&
						pos.X / 2 <= penemytank[i].core.X + 1 &&
						pos.Y >= penemytank[i].core.Y - 1 &&
						pos.Y <= penemytank[i].core.Y + 1)
						flag = 1;
					//continue;//�������Ǵ�for
				}
				if (flag == 1) continue;
				//������Ȫˮ����
				if (pos.X / 2 >= MAP_X_WALL / 4 - 2 &&
					pos.X / 2 <= MAP_X_WALL / 4 + 3 &&
					pos.Y >= MAP_Y - 2 - 3 &&
					pos.Y <= MAP_Y - 2) continue;
				//�ɻ��ƴ������߽硢̹�ˡ�Ȫˮ��
				if (pos.X > 1 && pos.X < MAP_X_WALL && pos.Y >0 && pos.Y < MAP_Y - 1)
				{
					g_MAP[pos.X / 2][pos.Y] = ʯ���ϰ�;
					GotoxyAndPrint(pos.X / 2, pos.Y, "��");
				}
			}
			//�Ҽ�����
			if (ir.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
			{
				COORD pos = ir.Event.MouseEvent.dwMousePosition;
				if (pos.X > 1 && pos.X < MAP_X_WALL && pos.Y >0 && pos.Y < MAP_Y - 1)
				{
					g_MAP[pos.X / 2][pos.Y] = �յ�;
					GotoxyAndPrint(pos.X / 2, pos.Y, "  ");
				}
			}
			//˫���˳�
			if (ir.Event.MouseEvent.dwEventFlags == DOUBLE_CLICK)
			{
				COORD pos = ir.Event.MouseEvent.dwMousePosition;
				if (!(pos.X > 1 && pos.X < MAP_X_WALL && pos.Y >0 && pos.Y < MAP_Y - 1))
				{
					//��ͼ��˫�����˳�
					break;
				}
			}
		}
	}
	//��ʾ��Ϣ
	system("cls");
	setColor(12, 0);
	GotoxyAndPrint(MAP_X / 2 - 12, 12, "�������ͼ����:");
	GotoxyAndPrint(MAP_X - 24, 14, "");
	//�����ļ���
	char str[15];
	char* filename = (char*)malloc(40);
	SetCursorState(true);
	scanf_s("%s", str, 15);
	SetCursorState(false);
	setColor(7, 0);
	sprintf_s(filename, 40, "%s%s%s", "conf/map/", str, ".i");
	//����д���ļ�
	FILE* pFile = NULL;
	errno_t err = fopen_s(&pFile, filename, "wb");
	for (int x = 0; x < MAP_X_WALL; x++)
	{
		for (int y = 0; y < MAP_Y; y++)
		{
			fwrite(&g_MAP[x][y], sizeof(int), 1, pFile);
		}
	}
	fclose(pFile);
}