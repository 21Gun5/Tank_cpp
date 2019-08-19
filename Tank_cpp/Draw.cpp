#include <Windows.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include "Data.h"
#include "Func.h"
#include "Draw.h"
#include "Tank.h"

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

void DrawTank(CTank tank, int who)
{
	if (tank.isAlive == false) return;
	if (who == �ҷ�̹��)
	{
		setColor(10, 0);
		GotoxyAndPrint(tank.core.X, tank.core.Y, "��");//���ĵ�
		for (int i = 0; i < 5; i++)//������
		{
			GotoxyAndPrint(tank.body[i].X, tank.body[i].Y, "��");
		}
		setColor(7, 0);
	}
	else if (who == �з�̹��)
	{
		setColor(11, 0);//����ɫ
		if (tank.blood == 2)
		{
			GotoxyAndPrint(tank.core.X, tank.core.Y, "��");//���ĵ�
			for (int i = 0; i < 5; i++)//������
				GotoxyAndPrint(tank.body[i].X, tank.body[i].Y, "��");//���ĵ�
		}
		else if (tank.blood == 1)
		{
			GotoxyAndPrint(tank.core.X, tank.core.Y, "��");//���ĵ�
			for (int i = 0; i < 5; i++)//������
				GotoxyAndPrint(tank.body[i].X, tank.body[i].Y, "��");
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

void DrawGameInfo(CTank tank, CTank * penemytank)
{
	//����̹����
	//int eneTankCount = GetLiveEnemyAmount(penemytank);
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
	printf("��ǰ����: %d", tank.blood);
	GotoxyAndPrint(MAP_X / 2 - 11, 7, "");
	printf("��ǰ����: %d",-1);
	//printf("��ǰ����: %d", ENEMY_TANK_AMOUNT - eneTankCount);
	GotoxyAndPrint(MAP_X / 2 - 11, 9, "");
	printf("��̹����: %d",-1);
	//printf("��̹����: %d", eneTankCount);
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