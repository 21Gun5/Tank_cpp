#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Game.h"
#include "Func.h"
#include "Map.h"
#include "Tank.h"
#pragma comment(lib,"winmm.lib")

//��Ϸ���
void CGame::GameInit(CMap &map)
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
				map.m_nArrMap[x][y] = ��ͼ�߽�;
			}
			if (x >= MAP_X_WALL / 4 - 2 && x <= MAP_X_WALL / 4 + 3 && y >= MAP_Y - 2 - 3 && y <= MAP_Y - 2)
			{
				if (x >= MAP_X_WALL / 4 && x <= MAP_X_WALL / 4 + 1 && y >= MAP_Y - 2 - 1 && y <= MAP_Y - 2)
					map.m_nArrMap[x][y] = �Ҽ�Ȫˮ;
				else
					map.m_nArrMap[x][y] = �����ϰ�;
			}
		}
	}

	SetCursorState(false);				//���ع��
	system("title Tank");				//���ñ���
	srand((unsigned int)time(0));		//��ʼ�����������

	//���ű�������(�Ȳ��ţ�����
	//mciSendString("open conf/BGM.mp3 alias bgm", NULL, 0, NULL);//���ļ�
	//mciSendString("play bgm repeat", NULL, 0, NULL);			  // ѭ������
}

//char* ShowGameFile()
//{
//	//����ָ��Ŀ¼����׺���ļ�������������
//	char* gameFiles[10] = { nullptr };
//	long Handle;
//	struct _finddata_t FileInfo;
//	int count = 0;
//	if ((Handle = _findfirst("conf/game/*.i", &FileInfo)) == -1L)
//		printf("Not Found\n");
//	else
//	{
//		gameFiles[count] = (char*)malloc(20);
//		strcpy_s(gameFiles[count], 20, FileInfo.name);
//		//g_Maps[count] = FileInfo.name;
//		count++;
//		while (_findnext(Handle, &FileInfo) == 0)
//		{
//			gameFiles[count] = (char*)malloc(20);
//			strcpy_s(gameFiles[count], 20, FileInfo.name);
//			//g_Maps[count] = FileInfo.name;
//			count++;
//		}
//		_findclose(Handle);
//	}
//	//��ʾ�浵�ļ�
//	system("cls");
//	GotoxyAndPrint(MAP_X / 4 - 5, MAP_Y / 2 - 8, "��ѡ��浵");
//	int i = 0;								//ѭ��������for�ⶨ��
//	for (; i < count; i++)
//	{
//		GotoxyAndPrint(MAP_X / 4 - 5, MAP_Y / 2 - 6 + i, "");
//		printf("%d.%s", i + 1, gameFiles[i]);
//	}
//	//ѡ��
//	GotoxyAndPrint(MAP_X / 4 - 5, MAP_Y / 2 - 6 + i, "������ѡ��-> ");
//	SetCursorState(true);
//	int input = _getch() - '0';				//��֤0-9����ASCII
//	SetCursorState(false);
//	char* _file = (char*)malloc(15);
//	strcpy_s(_file, 15, gameFiles[input - 1]);//����ʼ��1�����±�ʼ��0	
//	return _file;
//}

void CGame::GameOver(CTank * penemytank)
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

//int  SelectMenu(int size, int* pindex)
//{
//	int input = _getch();			//�޻��Խ���
//	switch (input)
//	{
//	case _UP:
//		if (*pindex > 0)
//			* pindex -= 1;
//		break;
//	case _DOWN:
//		if (*pindex < size - 1)//���һ��
//			* pindex += 1;
//		break;
//	case ENTER:
//		return ENTER;
//		break;
//	default:
//		break;
//	}
//	return 0;
//}

//void SaveGame(PTANK ptank, PTANK penemytank)
//{
//	//��ʾ��Ϣ
//	system("cls");
//	setColor(12, 0);
//	GotoxyAndPrint(MAP_X / 2 - 12, 12, "������浵����");
//	GotoxyAndPrint(MAP_X / 2 - 12, 14, "");
//	//�����ļ���
//	char str[15];
//	char* filename = (char*)malloc(40);
//	SetCursorState(true);
//	scanf_s("%s", str, 15);
//	SetCursorState(false);
//	setColor(7, 0);
//	sprintf_s(filename, 40, "%s%s%s", "conf/game/", str, ".i");
//	//���ļ�
//	FILE* pFile = NULL;
//	errno_t err = fopen_s(&pFile, filename, "wb");
//	//д��ȫ�ֱ���
//	fwrite(&g_isRunning, sizeof(int), 1, pFile);		//��Ϸ����״̬
//	fwrite(&g_levelEneTank, sizeof(int), 1, pFile);	//д���Ѷȣ����Ƶз�̹���ٶ�
//	fwrite(&g_levelEneBul, sizeof(int), 1, pFile);	//д���Ѷȣ����Ƶз��ӵ��ٶ�
//	//д���ϰ�
//	for (int x = 0; x < MAP_X_WALL; x++)
//	{
//		for (int y = 0; y < MAP_Y; y++)
//		{
//			fwrite(&g_MAP[x][y], sizeof(int), 1, pFile);
//		}
//	}
//	//д���ҷ�̹��
//	fwrite(&ptank->core, sizeof(COORD), 1, pFile);//���Ľڵ�
//	for (int i = 0; i < 5; i++)
//		fwrite(&ptank->body[i], sizeof(COORD), 1, pFile);//�����ڵ�
//	fwrite(&ptank->dir, sizeof(int), 1, pFile);//����
//	fwrite(&ptank->blood, sizeof(int), 1, pFile);//Ѫ��
//	fwrite(&ptank->isAlive, sizeof(bool), 1, pFile);//�Ƿ���
//	fwrite(&ptank->who, sizeof(int), 1, pFile);//���
//	//д���ҷ��ӵ�
//	fwrite(&ptank->bullet.core, sizeof(COORD), 1, pFile);//����
//	fwrite(&ptank->bullet.dir, sizeof(int), 1, pFile);//����
//	fwrite(&ptank->bullet.state, sizeof(int), 1, pFile);//״̬
//	//д��з�
//	for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
//	{
//		//д��з�̹��
//		fwrite(&penemytank[i].core, sizeof(COORD), 1, pFile);//���Ľڵ�
//		for (int i = 0; i < 5; i++)
//			fwrite(&penemytank[i].body[i], sizeof(COORD), 1, pFile);//�����ڵ�
//		fwrite(&penemytank[i].dir, sizeof(int), 1, pFile);//����
//		fwrite(&penemytank[i].blood, sizeof(int), 1, pFile);//Ѫ��
//		fwrite(&penemytank[i].isAlive, sizeof(bool), 1, pFile);//�Ƿ���
//		fwrite(&penemytank[i].who, sizeof(int), 1, pFile);//���
//		//д��з��ӵ�
//		fwrite(&penemytank[i].bullet.core, sizeof(COORD), 1, pFile);//����
//		fwrite(&penemytank[i].bullet.dir, sizeof(int), 1, pFile);//����
//		fwrite(&penemytank[i].bullet.state, sizeof(int), 1, pFile);//״̬
//	}
//	fclose(pFile);
//}

//void LoadGame(PTANK ptank, PTANK penemytank, char* str)
//{
//	char* filename = (char*)malloc(40);
//	sprintf_s(filename, 40, "%s%s", "conf/game/", str);
//	FILE* pFile = NULL;
//	errno_t err = fopen_s(&pFile, filename, "rb");
//	//��ȡȫ�ֱ���
//	fread(&g_isRunning, sizeof(int), 1, pFile);		//��Ϸ����״̬
//	fread(&g_levelEneTank, sizeof(int), 1, pFile);	//��ȡ�Ѷȣ����Ƶз�̹���ٶ�
//	fread(&g_levelEneBul, sizeof(int), 1, pFile);	//��ȡ�Ѷȣ����Ƶз��ӵ��ٶ�
//	//��ȡ�ϰ�
//	for (int x = 0; x < MAP_X_WALL; x++)
//	{
//		for (int y = 0; y < MAP_Y; y++)
//		{
//			fread(&g_MAP[x][y], sizeof(int), 1, pFile);
//		}
//	}
//	//��ȡ�ҷ�̹��
//	fread(&ptank->core, sizeof(COORD), 1, pFile);//���Ľڵ�
//	for (int i = 0; i < 5; i++)
//		fread(&ptank->body[i], sizeof(COORD), 1, pFile);//�����ڵ�
//	fread(&ptank->dir, sizeof(int), 1, pFile);//����
//	fread(&ptank->blood, sizeof(int), 1, pFile);//Ѫ��
//	fread(&ptank->isAlive, sizeof(bool), 1, pFile);//�Ƿ���
//	fread(&ptank->who, sizeof(int), 1, pFile);//���
//	//��ȡ�ҷ��ӵ�
//	fread(&ptank->bullet.core, sizeof(COORD), 1, pFile);//����
//	fread(&ptank->bullet.dir, sizeof(int), 1, pFile);//����
//	fread(&ptank->bullet.state, sizeof(int), 1, pFile);//״̬
//	//��ȡ�з�
//	for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
//	{
//		//��ȡ�з�̹��
//		fread(&penemytank[i].core, sizeof(COORD), 1, pFile);//���Ľڵ�
//		for (int i = 0; i < 5; i++)
//			fread(&penemytank[i].body[i], sizeof(COORD), 1, pFile);//�����ڵ�
//		fread(&penemytank[i].dir, sizeof(int), 1, pFile);//����
//		fread(&penemytank[i].blood, sizeof(int), 1, pFile);//Ѫ��
//		fread(&penemytank[i].isAlive, sizeof(bool), 1, pFile);//�Ƿ���
//		fread(&penemytank[i].who, sizeof(int), 1, pFile);//���
//		//��ȡ�з��ӵ�
//		fread(&penemytank[i].bullet.core, sizeof(COORD), 1, pFile);//����
//		fread(&penemytank[i].bullet.dir, sizeof(int), 1, pFile);//����
//		fread(&penemytank[i].bullet.state, sizeof(int), 1, pFile);//״̬
//	}
//	fclose(pFile);
//}

// ��ӡ���
void CGame::DrawLogo()
{
	GotoxyAndPrint(MAP_X / 4 - 9, MAP_Y / 2 - 15, "MMP\"\"MM\"\"YMM                      `7MM      ");
	GotoxyAndPrint(MAP_X / 4 - 9, MAP_Y / 2 - 14, "P'   MM   `7                        MM      ");
	GotoxyAndPrint(MAP_X / 4 - 9, MAP_Y / 2 - 13, "     MM       ,6\"Yb.  `7MMpMMMb.    MM, MP'");
	GotoxyAndPrint(MAP_X / 4 - 9, MAP_Y / 2 - 12, "     MM      8)   MM    MM    MM    MM ;Y   ");
	GotoxyAndPrint(MAP_X / 4 - 9, MAP_Y / 2 - 11, "     MM       ,pm9MM    MM    MM    MM;Mm   ");
	GotoxyAndPrint(MAP_X / 4 - 9, MAP_Y / 2 - 10, "     MM      8M   MM    MM    MM    MM `Mb. ");
	GotoxyAndPrint(MAP_X / 4 - 9, MAP_Y / 2 - 9, "   .JMML.    `Moo9^Yo..JMML  JMML..JMML. YA.");
}
void CGame::DrawGameHelp()
{
	setColor(12, 0);
	GotoxyAndPrint(MAP_X / 2 - 10, 18, "����˵��");
	GotoxyAndPrint(MAP_X / 2 - 11, 20, "W: ��  S: ��");
	GotoxyAndPrint(MAP_X / 2 - 11, 22, "A: ��  D: ��");
	GotoxyAndPrint(MAP_X / 2 - 11, 24, "Q:  ��ͣ��Ϸ");
	GotoxyAndPrint(MAP_X / 2 - 11, 26, "�ո�: ����");
	setColor(7, 0);
}
void CGame::DrawGameInfo(CTank tank, CTank* penemytank)
{
	//����̹����
	int eneTankCount = GetLiveEnemyAmount(penemytank);
	//��ǰ�Ѷ�
	char level[10];
	if (m_levelEneTank == 300) strcpy_s(level, 10, "��\0");
	else if (m_levelEneTank == 200) strcpy_s(level, 10, "һ��\0");
	else if (m_levelEneTank == 100)strcpy_s(level, 10, "����\0");
	//����or��ͣ״̬
	setColor(12, 0);
	GotoxyAndPrint(MAP_X / 2 - 14, 1, "RUNNING");
	GotoxyAndPrint(MAP_X / 2 - 14, 2, "Q: ��ͣ��Ϸ");
	setColor(7, 0);
	//��Ϸ��Ϣ��ӡ
	setColor(12, 0);
	GotoxyAndPrint(MAP_X / 2 - 11, 5, "");
	printf("��ǰ����: %d", tank.m_blood);
	GotoxyAndPrint(MAP_X / 2 - 11, 7, "");
	//printf("��ǰ����: %d",-1);
	printf("��ǰ����: %d", ENEMY_TANK_AMOUNT - eneTankCount);
	GotoxyAndPrint(MAP_X / 2 - 11, 9, "");
	//printf("��̹����: %d",-1);
	printf("��̹����: %d", eneTankCount);
	GotoxyAndPrint(MAP_X / 2 - 11, 11, "");
	printf("��ǰ�Ѷ�: %s", level);
	setColor(7, 0);
}
void CGame::DrawMenu(const char** menu, int size, int index)
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