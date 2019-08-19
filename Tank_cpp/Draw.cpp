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

//打印相关
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
			if (g_MAP[x][y] == 石块障碍) GotoxyAndPrint(x, y, "■");
			if (g_MAP[x][y] == 土块障碍) GotoxyAndPrint(x, y, "※");
		}
	}
}
void DrawBorder()
{
	system("cls");						//换页则清屏
	for (int x = 0; x < MAP_X; x++)
	{
		for (int y = 0; y < MAP_Y; y++)
		{
			if (g_MAP[x][y] == 地图边界)
			{
				GotoxyAndPrint(x, y, "■");
			}
			if (g_MAP[x][y] == 我家泉水)
			{
				setColor(12, 0);
				GotoxyAndPrint(x, y, "★");
				setColor(7, 0);
			}
		}
	}
}
void DrawGameHelp()
{
	setColor(12, 0);
	GotoxyAndPrint(MAP_X / 2 - 10, 18, "操作说明");
	GotoxyAndPrint(MAP_X / 2 - 11, 20, "W: 上  S: 下");
	GotoxyAndPrint(MAP_X / 2 - 11, 22, "A: 左  D: 右");
	GotoxyAndPrint(MAP_X / 2 - 11, 24, "Q:  暂停游戏");
	GotoxyAndPrint(MAP_X / 2 - 11, 26, "空格: 开火");
	setColor(7, 0);
}

void DrawTank(CTank tank, int who)
{
	if (tank.isAlive == false) return;
	if (who == 我方坦克)
	{
		setColor(10, 0);
		GotoxyAndPrint(tank.core.X, tank.core.Y, "■");//中心点
		for (int i = 0; i < 5; i++)//其他点
		{
			GotoxyAndPrint(tank.body[i].X, tank.body[i].Y, "■");
		}
		setColor(7, 0);
	}
	else if (who == 敌方坦克)
	{
		setColor(11, 0);//亮蓝色
		if (tank.blood == 2)
		{
			GotoxyAndPrint(tank.core.X, tank.core.Y, "■");//中心点
			for (int i = 0; i < 5; i++)//其他点
				GotoxyAndPrint(tank.body[i].X, tank.body[i].Y, "■");//中心点
		}
		else if (tank.blood == 1)
		{
			GotoxyAndPrint(tank.core.X, tank.core.Y, "□");//中心点
			for (int i = 0; i < 5; i++)//其他点
				GotoxyAndPrint(tank.body[i].X, tank.body[i].Y, "□");
		}
		setColor(7, 0);
	}
}

void DrawBullet(PBULLET pbullet, PTANK ptank)
{
	//碰到边界，换成边界的颜色，实现子弹消失的效果
	if (pbullet->core.X <= 0 ||
		pbullet->core.X >= MAP_X_WALL / 2 ||
		pbullet->core.Y <= 0 ||
		pbullet->core.Y >= MAP_Y - 1)
	{
		setColor(7, 0);
	}
	else
	{
		if (ptank->who == 我方坦克)
			setColor(10, 0);
		else if (ptank->who == 敌方坦克)
			setColor(11, 0);
	}
	//碰到障碍，将子弹画为空格，实现子弹消失
	if (g_MAP[pbullet->core.X][pbullet->core.Y] == 土块障碍)
	{
		GotoxyAndPrint(pbullet->core.X, pbullet->core.Y, "  ");
	}
	//碰到石块障碍物，，实现子弹消失的效果
	else if (g_MAP[pbullet->core.X][pbullet->core.Y] == 石块障碍)
	{
		setColor(7, 0);
	}
	//碰到泉水，将子弹换成其颜色和形状，实现子弹消失
	else if (g_MAP[pbullet->core.X][pbullet->core.Y] == 我家泉水)
	{
		setColor(12, 0);
		GotoxyAndPrint(pbullet->core.X, pbullet->core.Y, "★");
	}
	//一般运动状态
	else
	{
		GotoxyAndPrint(pbullet->core.X, pbullet->core.Y, "■");
	}
	setColor(7, 0);
}

void DrawGameInfo(CTank tank, CTank * penemytank)
{
	//存活敌坦数量
	//int eneTankCount = GetLiveEnemyAmount(penemytank);
	//当前难度
	char level[10];
	if (g_levelEneTank == 300) strcpy_s(level, 10, "简单\0");
	else if (g_levelEneTank == 200) strcpy_s(level, 10, "一般\0");
	else if (g_levelEneTank == 100)strcpy_s(level, 10, "困难\0");
	//运行or暂停状态
	setColor(12, 0);
	GotoxyAndPrint(MAP_X / 2 - 14, 1, "RUNNING");
	GotoxyAndPrint(MAP_X / 2 - 14, 2, "Q: 暂停游戏");
	setColor(7, 0);
	//游戏信息打印
	setColor(12, 0);
	GotoxyAndPrint(MAP_X / 2 - 11, 5, "");
	printf("当前生命: %d", tank.blood);
	GotoxyAndPrint(MAP_X / 2 - 11, 7, "");
	printf("当前分数: %d",-1);
	//printf("当前分数: %d", ENEMY_TANK_AMOUNT - eneTankCount);
	GotoxyAndPrint(MAP_X / 2 - 11, 9, "");
	printf("敌坦个数: %d",-1);
	//printf("敌坦个数: %d", eneTankCount);
	GotoxyAndPrint(MAP_X / 2 - 11, 11, "");
	printf("当前难度: %s", level);
	setColor(7, 0);
}

void DrawMenu(const char** menu, int size, int index)
{
	system("cls");
	DrawLogo();
	//提示信息
	for (int i = 0; i < size; i++)//菜单条数
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