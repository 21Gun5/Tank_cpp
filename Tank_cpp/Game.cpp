#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Game.h"
#include "Func.h"
#include "Map.h"
#include "Tank.h"
#pragma comment(lib,"winmm.lib")

//游戏相关
void CGame::GameInit(CMap &map)
{
	//设置地图
	for (int x = 0; x < MAP_X / 2; x++)
	{
		for (int y = 0; y < MAP_Y; y++)
		{
			//地图边界
			if (x == 0 || x == MAP_X / 2 - 1 || x == MAP_X_WALL / 2 ||	//三竖边
				y == 0 || y == MAP_Y - 1 ||							//两横边
				(x > MAP_X_WALL / 2 && y == MAP_Y / 2))				//帮助信息与游戏信息分割线
			{
				map.m_nArrMap[x][y] = 地图边界;
			}
			if (x >= MAP_X_WALL / 4 - 2 && x <= MAP_X_WALL / 4 + 3 && y >= MAP_Y - 2 - 3 && y <= MAP_Y - 2)
			{
				if (x >= MAP_X_WALL / 4 && x <= MAP_X_WALL / 4 + 1 && y >= MAP_Y - 2 - 1 && y <= MAP_Y - 2)
					map.m_nArrMap[x][y] = 我家泉水;
				else
					map.m_nArrMap[x][y] = 土块障碍;
			}
		}
	}

	SetCursorState(false);				//隐藏光标
	system("title Tank");				//设置标题
	srand((unsigned int)time(0));		//初始化随机数种子

	//播放背景音乐(先不放，烦人
	//mciSendString("open conf/BGM.mp3 alias bgm", NULL, 0, NULL);//打开文件
	//mciSendString("play bgm repeat", NULL, 0, NULL);			  // 循环播放
}

//char* ShowGameFile()
//{
//	//遍历指定目录及后缀的文件名并存入数组
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
//	//显示存档文件
//	system("cls");
//	GotoxyAndPrint(MAP_X / 4 - 5, MAP_Y / 2 - 8, "请选择存档");
//	int i = 0;								//循环变量在for外定义
//	for (; i < count; i++)
//	{
//		GotoxyAndPrint(MAP_X / 4 - 5, MAP_Y / 2 - 6 + i, "");
//		printf("%d.%s", i + 1, gameFiles[i]);
//	}
//	//选择
//	GotoxyAndPrint(MAP_X / 4 - 5, MAP_Y / 2 - 6 + i, "请输入选择-> ");
//	SetCursorState(true);
//	int input = _getch() - '0';				//保证0-9而非ASCII
//	SetCursorState(false);
//	char* _file = (char*)malloc(15);
//	strcpy_s(_file, 15, gameFiles[input - 1]);//数字始于1，而下标始于0	
//	return _file;
//}

void CGame::GameOver(CTank * penemytank)
{
	//存活敌坦数量
	int eneTankCount = GetLiveEnemyAmount(penemytank);
	//关闭音乐文件
	mciSendString("close bgm", NULL, 0, NULL);	//close关闭而非stop停止
	//提示信息
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
//	int input = _getch();			//无回显接收
//	switch (input)
//	{
//	case _UP:
//		if (*pindex > 0)
//			* pindex -= 1;
//		break;
//	case _DOWN:
//		if (*pindex < size - 1)//最后一条
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
//	//提示信息
//	system("cls");
//	setColor(12, 0);
//	GotoxyAndPrint(MAP_X / 2 - 12, 12, "请输入存档名字");
//	GotoxyAndPrint(MAP_X / 2 - 12, 14, "");
//	//输入文件名
//	char str[15];
//	char* filename = (char*)malloc(40);
//	SetCursorState(true);
//	scanf_s("%s", str, 15);
//	SetCursorState(false);
//	setColor(7, 0);
//	sprintf_s(filename, 40, "%s%s%s", "conf/game/", str, ".i");
//	//打开文件
//	FILE* pFile = NULL;
//	errno_t err = fopen_s(&pFile, filename, "wb");
//	//写入全局变量
//	fwrite(&g_isRunning, sizeof(int), 1, pFile);		//游戏运行状态
//	fwrite(&g_levelEneTank, sizeof(int), 1, pFile);	//写入难度，控制敌方坦克速度
//	fwrite(&g_levelEneBul, sizeof(int), 1, pFile);	//写入难度，控制敌方子弹速度
//	//写入障碍
//	for (int x = 0; x < MAP_X_WALL; x++)
//	{
//		for (int y = 0; y < MAP_Y; y++)
//		{
//			fwrite(&g_MAP[x][y], sizeof(int), 1, pFile);
//		}
//	}
//	//写入我方坦克
//	fwrite(&ptank->core, sizeof(COORD), 1, pFile);//中心节点
//	for (int i = 0; i < 5; i++)
//		fwrite(&ptank->body[i], sizeof(COORD), 1, pFile);//其他节点
//	fwrite(&ptank->dir, sizeof(int), 1, pFile);//方向
//	fwrite(&ptank->blood, sizeof(int), 1, pFile);//血量
//	fwrite(&ptank->isAlive, sizeof(bool), 1, pFile);//是否存活
//	fwrite(&ptank->who, sizeof(int), 1, pFile);//身份
//	//写入我方子弹
//	fwrite(&ptank->bullet.core, sizeof(COORD), 1, pFile);//坐标
//	fwrite(&ptank->bullet.dir, sizeof(int), 1, pFile);//方向
//	fwrite(&ptank->bullet.state, sizeof(int), 1, pFile);//状态
//	//写入敌方
//	for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
//	{
//		//写入敌方坦克
//		fwrite(&penemytank[i].core, sizeof(COORD), 1, pFile);//中心节点
//		for (int i = 0; i < 5; i++)
//			fwrite(&penemytank[i].body[i], sizeof(COORD), 1, pFile);//其他节点
//		fwrite(&penemytank[i].dir, sizeof(int), 1, pFile);//方向
//		fwrite(&penemytank[i].blood, sizeof(int), 1, pFile);//血量
//		fwrite(&penemytank[i].isAlive, sizeof(bool), 1, pFile);//是否存活
//		fwrite(&penemytank[i].who, sizeof(int), 1, pFile);//身份
//		//写入敌方子弹
//		fwrite(&penemytank[i].bullet.core, sizeof(COORD), 1, pFile);//坐标
//		fwrite(&penemytank[i].bullet.dir, sizeof(int), 1, pFile);//方向
//		fwrite(&penemytank[i].bullet.state, sizeof(int), 1, pFile);//状态
//	}
//	fclose(pFile);
//}

//void LoadGame(PTANK ptank, PTANK penemytank, char* str)
//{
//	char* filename = (char*)malloc(40);
//	sprintf_s(filename, 40, "%s%s", "conf/game/", str);
//	FILE* pFile = NULL;
//	errno_t err = fopen_s(&pFile, filename, "rb");
//	//读取全局变量
//	fread(&g_isRunning, sizeof(int), 1, pFile);		//游戏运行状态
//	fread(&g_levelEneTank, sizeof(int), 1, pFile);	//读取难度，控制敌方坦克速度
//	fread(&g_levelEneBul, sizeof(int), 1, pFile);	//读取难度，控制敌方子弹速度
//	//读取障碍
//	for (int x = 0; x < MAP_X_WALL; x++)
//	{
//		for (int y = 0; y < MAP_Y; y++)
//		{
//			fread(&g_MAP[x][y], sizeof(int), 1, pFile);
//		}
//	}
//	//读取我方坦克
//	fread(&ptank->core, sizeof(COORD), 1, pFile);//中心节点
//	for (int i = 0; i < 5; i++)
//		fread(&ptank->body[i], sizeof(COORD), 1, pFile);//其他节点
//	fread(&ptank->dir, sizeof(int), 1, pFile);//方向
//	fread(&ptank->blood, sizeof(int), 1, pFile);//血量
//	fread(&ptank->isAlive, sizeof(bool), 1, pFile);//是否存活
//	fread(&ptank->who, sizeof(int), 1, pFile);//身份
//	//读取我方子弹
//	fread(&ptank->bullet.core, sizeof(COORD), 1, pFile);//坐标
//	fread(&ptank->bullet.dir, sizeof(int), 1, pFile);//方向
//	fread(&ptank->bullet.state, sizeof(int), 1, pFile);//状态
//	//读取敌方
//	for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
//	{
//		//读取敌方坦克
//		fread(&penemytank[i].core, sizeof(COORD), 1, pFile);//中心节点
//		for (int i = 0; i < 5; i++)
//			fread(&penemytank[i].body[i], sizeof(COORD), 1, pFile);//其他节点
//		fread(&penemytank[i].dir, sizeof(int), 1, pFile);//方向
//		fread(&penemytank[i].blood, sizeof(int), 1, pFile);//血量
//		fread(&penemytank[i].isAlive, sizeof(bool), 1, pFile);//是否存活
//		fread(&penemytank[i].who, sizeof(int), 1, pFile);//身份
//		//读取敌方子弹
//		fread(&penemytank[i].bullet.core, sizeof(COORD), 1, pFile);//坐标
//		fread(&penemytank[i].bullet.dir, sizeof(int), 1, pFile);//方向
//		fread(&penemytank[i].bullet.state, sizeof(int), 1, pFile);//状态
//	}
//	fclose(pFile);
//}

// 打印相关
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
	GotoxyAndPrint(MAP_X / 2 - 10, 18, "操作说明");
	GotoxyAndPrint(MAP_X / 2 - 11, 20, "W: 上  S: 下");
	GotoxyAndPrint(MAP_X / 2 - 11, 22, "A: 左  D: 右");
	GotoxyAndPrint(MAP_X / 2 - 11, 24, "Q:  暂停游戏");
	GotoxyAndPrint(MAP_X / 2 - 11, 26, "空格: 开火");
	setColor(7, 0);
}
void CGame::DrawGameInfo(CTank tank, CTank* penemytank)
{
	//存活敌坦数量
	int eneTankCount = GetLiveEnemyAmount(penemytank);
	//当前难度
	char level[10];
	if (m_levelEneTank == 300) strcpy_s(level, 10, "简单\0");
	else if (m_levelEneTank == 200) strcpy_s(level, 10, "一般\0");
	else if (m_levelEneTank == 100)strcpy_s(level, 10, "困难\0");
	//运行or暂停状态
	setColor(12, 0);
	GotoxyAndPrint(MAP_X / 2 - 14, 1, "RUNNING");
	GotoxyAndPrint(MAP_X / 2 - 14, 2, "Q: 暂停游戏");
	setColor(7, 0);
	//游戏信息打印
	setColor(12, 0);
	GotoxyAndPrint(MAP_X / 2 - 11, 5, "");
	printf("当前生命: %d", tank.m_blood);
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
void CGame::DrawMenu(const char** menu, int size, int index)
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