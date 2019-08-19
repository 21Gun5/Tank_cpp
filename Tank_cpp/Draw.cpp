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





void DrawGameInfo(CTank tank, CTank * penemytank)
{
	//存活敌坦数量
	int eneTankCount = GetLiveEnemyAmount(penemytank);
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
	//printf("当前分数: %d",-1);
	printf("当前分数: %d", ENEMY_TANK_AMOUNT - eneTankCount);
	GotoxyAndPrint(MAP_X / 2 - 11, 9, "");
	//printf("敌坦个数: %d",-1);
	printf("敌坦个数: %d", eneTankCount);
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