#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <io.h>

#include "Game.h"
#include "Func.h"
#include "Map.h"
#include "Tank.h"
#pragma comment(lib,"winmm.lib")


//游戏相关
void CGame::GameInit(CMap &map)
{
	//设置地图（静态的
	for (int x = 0; x < MAP_X / 2; x++)
	{
		for (int y = 0; y < MAP_Y; y++)
		{
			//地图边界
			if (x == 0 || x == MAP_X / 2 - 1 || x == MAP_X_WALL / 2 ||	//三竖边
				y == 0 || y == MAP_Y - 1 ||							//两横边
				(x > MAP_X_WALL / 2 && y == MAP_Y / 2))				//帮助信息与游戏信息分割线
			{
				map.m_nArrMap[x][y] = 边界;
			}
			//泉水
			if (x >= MAP_X_WALL / 4 - 2 && x <= MAP_X_WALL / 4 + 3 && y >= MAP_Y - 2 - 3 && y <= MAP_Y - 2)
			{
				if (x >= MAP_X_WALL / 4 && x <= MAP_X_WALL / 4 + 1 && y >= MAP_Y - 2 - 1 && y <= MAP_Y - 2)
					map.m_nArrMap[x][y] = 泉水;
				//else
				//	map.m_nArrMap[x][y] = 土块;
			}
		}
	}

	// 控制台相关设置
	SetCursorState(false);				//隐藏光标
	system("title Tank");				//设置标题
	//system("color fc");				//设置颜色	

	// 窗口大小
	char strCmd[50];
	sprintf_s(strCmd,50,"mode con cols=%d lines=%d", MAP_X, MAP_Y);
	system(strCmd);

	//初始化随机数种子
	srand((unsigned int)time(0));		
	
	//播放背景音乐(先不放，烦人
	//mciSendString("open conf/BGM.mp3 alias bgm", NULL, 0, NULL);//打开文件
	//mciSendString("play bgm repeat", NULL, 0, NULL);			  // 循环播放
}

char* CGame::ShowGameFile()
{
	//遍历指定目录及后缀的文件名并存入数组
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
	//显示存档文件
	system("cls");
	GotoxyAndPrint(MAP_X / 4 - 5, MAP_Y / 2 - 8, "请选择存档");
	int i = 0;								//循环变量在for外定义
	for (; i < count; i++)
	{
		GotoxyAndPrint(MAP_X / 4 - 5, MAP_Y / 2 - 6 + i, "");
		printf("%d.%s", i + 1, gameFiles[i]);
	}
	//选择
	GotoxyAndPrint(MAP_X / 4 - 5, MAP_Y / 2 - 6 + i, "请输入选择-> ");
	SetCursorState(true);
	int input = _getch() - '0';				//保证0-9而非ASCII
	SetCursorState(false);
	char* _file = (char*)malloc(15);
	strcpy_s(_file, 15, gameFiles[input - 1]);//数字始于1，而下标始于0	
	return _file;
}

void CGame::GameOver(vector<CTank>& enemyTank)
{
	//存活敌坦数量
	int eneTankCount = enemyTank.size();
	//关闭音乐文件
	mciSendString("close bgm", NULL, 0, NULL);	//close关闭而非stop停止
	//提示信息
	GotoxyAndPrint(MAP_X_WALL / 4 - 2, MAP_Y / 2 - 7, "GAME OVER! ", 提示颜色);
	if (eneTankCount == 0)
		GotoxyAndPrint(MAP_X_WALL / 4 - 2, MAP_Y / 2 - 5, "A Winner!", 提示颜色);
	else
		GotoxyAndPrint(MAP_X_WALL / 4 - 2, MAP_Y / 2 - 5, "A Loser!", 提示颜色);
	GotoxyAndPrint(MAP_X_WALL / 4 - 2, MAP_Y / 2 - 3, "", 提示颜色);
	printf("Scores: %d", ENEMY_TANK_AMOUNT - eneTankCount);
}

void CGame::NextStage()
{
	m_stage++;
	m_needLoadNewStage = true;
}

int  CGame::SelectMenu(int size, int* pindex)
{
	int input = _getch();			//无回显接收
	switch (input)
	{
	case UP_KEY:
		if (*pindex > 0)
			* pindex -= 1;
		break;
	case DOWN_KEY:
		if (*pindex < size - 1)//最后一条
			* pindex += 1;
		break;
	case ENTER_KEY:
		return ENTER_KEY;
		break;
	default:
		break;
	}
	return 0;
}

void CGame::SaveGameFile(vector<CTank>& myTank, vector<CTank>& enemyTank,CMap map)
{
	//提示信息
	system("cls");
	GotoxyAndPrint(MAP_X / 2 - 12, 12, "请输入存档名字", 提示颜色);
	GotoxyAndPrint(MAP_X / 2 - 12, 14, "");
	//输入文件名
	char str[15];
	char* filename = (char*)malloc(40);
	SetCursorState(true);
	scanf_s("%s", str, 15);
	SetCursorState(false);
	sprintf_s(filename, 40, "%s%s%s", "conf/game/", str, ".i");
	//打开文件
	FILE* pFile = NULL;
	errno_t err = fopen_s(&pFile, filename, "wb");
	//写入全局变量
	fwrite(&this->m_isRunning, sizeof(int), 1, pFile);		//游戏运行状态
	fwrite(&this->m_levelEneTank, sizeof(int), 1, pFile);	//写入难度，控制敌方坦克速度
	fwrite(&this->m_levelEneBul, sizeof(int), 1, pFile);	//写入难度，控制敌方子弹速度
	//写入障碍
	for (int x = 0; x < MAP_X_WALL; x++)
	{
		for (int y = 0; y < MAP_Y; y++)
		{
			fwrite(&map.m_nArrMap[x][y], sizeof(int), 1, pFile);
		}
	}
	for (vector<CTank>::iterator it = myTank.begin(); it != myTank.end(); it++)
	{
		//写入我方坦克
		fwrite(&it->m_core, sizeof(COORD), 1, pFile);//中心节点
		for (int i = 0; i < 5; i++)
			fwrite(&it->m_body[i], sizeof(COORD), 1, pFile);//其他节点
		fwrite(&it->m_dir, sizeof(int), 1, pFile);//方向
		fwrite(&it->m_blood, sizeof(int), 1, pFile);//血量
		fwrite(&it->m_isAlive, sizeof(bool), 1, pFile);//是否存活
		fwrite(&it->m_who, sizeof(int), 1, pFile);//身份
		//写入我方子弹
		fwrite(&it->m_bullet.m_core, sizeof(COORD), 1, pFile);//坐标
		fwrite(&it->m_bullet.m_dir, sizeof(int), 1, pFile);//方向
		fwrite(&it->m_bullet.m_state, sizeof(int), 1, pFile);//状态
	}
	//写入敌方
	for (vector<CTank>::iterator it = enemyTank.begin(); it != enemyTank.end(); it++)
	{
		//写入敌方坦克
		fwrite(&it->m_core, sizeof(COORD), 1, pFile);//中心节点
		for (int j = 0; j < 5; j++)
			fwrite(&it->m_body[j], sizeof(COORD), 1, pFile);//其他节点
		fwrite(&it->m_dir, sizeof(int), 1, pFile);//方向
		fwrite(&it->m_blood, sizeof(int), 1, pFile);//血量
		fwrite(&it->m_isAlive, sizeof(bool), 1, pFile);//是否存活
		fwrite(&it->m_who, sizeof(int), 1, pFile);//身份
		//写入敌方子弹
		fwrite(&it->m_bullet.m_core, sizeof(COORD), 1, pFile);//坐标
		fwrite(&it->m_bullet.m_dir, sizeof(int), 1, pFile);//方向
		fwrite(&it->m_bullet.m_state, sizeof(int), 1, pFile);//状态
	}
	fclose(pFile);
}

void CGame::LoadGameFile(vector<CTank>& myTank, vector<CTank>& enemyTank, CMap& map, char* str)
{
	char* filename = (char*)malloc(40);
	sprintf_s(filename, 40, "%s%s", "conf/game/", str);
	FILE* pFile = NULL;
	errno_t err = fopen_s(&pFile, filename, "rb");
	//读取全局变量
	fread(&this->m_isRunning, sizeof(int), 1, pFile);		//游戏运行状态
	fread(&this->m_levelEneTank, sizeof(int), 1, pFile);	//读取难度，控制敌方坦克速度
	fread(&this->m_levelEneBul, sizeof(int), 1, pFile);	//读取难度，控制敌方子弹速度
	//读取障碍
	for (int x = 0; x < MAP_X_WALL; x++)
	{
		for (int y = 0; y < MAP_Y; y++)
		{
			fread(&map.m_nArrMap[x][y], sizeof(int), 1, pFile);
		}
	}
	//读取我方
	for (vector<CTank>::iterator it = myTank.begin(); it != myTank.end(); it++)
	{
		//读取我方坦克
		fread(&it->m_core, sizeof(COORD), 1, pFile);//中心节点
		for (int i = 0; i < 5; i++)
			fread(&it->m_body[i], sizeof(COORD), 1, pFile);//其他节点
		fread(&it->m_dir, sizeof(int), 1, pFile);//方向
		fread(&it->m_blood, sizeof(int), 1, pFile);//血量
		fread(&it->m_isAlive, sizeof(bool), 1, pFile);//是否存活
		fread(&it->m_who, sizeof(int), 1, pFile);//身份
		//读取我方子弹
		fread(&it->m_bullet.m_core, sizeof(COORD), 1, pFile);//坐标
		fread(&it->m_bullet.m_dir, sizeof(int), 1, pFile);//方向
		fread(&it->m_bullet.m_state, sizeof(int), 1, pFile);//状态
	}
	//读取敌方
	for (vector<CTank>::iterator it = enemyTank.begin(); it != enemyTank.end(); it++)
	{
		//读取敌方坦克
		fread(&it->m_core, sizeof(COORD), 1, pFile);//中心节点
		for (int j = 0; j < 5; j++)
			fread(&it->m_body[j], sizeof(COORD), 1, pFile);//其他节点
		fread(&it->m_dir, sizeof(int), 1, pFile);//方向
		fread(&it->m_blood, sizeof(int), 1, pFile);//血量
		fread(&it->m_isAlive, sizeof(bool), 1, pFile);//是否存活
		fread(&it->m_who, sizeof(int), 1, pFile);//身份
		//读取敌方子弹
		fread(&it->m_bullet.m_core, sizeof(COORD), 1, pFile);//坐标
		fread(&it->m_bullet.m_dir, sizeof(int), 1, pFile);//方向
		fread(&it->m_bullet.m_state, sizeof(int), 1, pFile);//状态
	}
	fclose(pFile);
}

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
	GotoxyAndPrint((MAP_X + MAP_X_WALL) / 4 - 3, 24, "操 作 说 明", 提示颜色);
	GotoxyAndPrint((MAP_X + MAP_X_WALL) / 4 - 3, 26, "W: 上 S: 下", 提示颜色);
	GotoxyAndPrint((MAP_X + MAP_X_WALL) / 4 - 3, 28, "A: 左 D: 右", 提示颜色);
	GotoxyAndPrint((MAP_X + MAP_X_WALL) / 4 - 3, 30, "Q: 暂停游戏", 提示颜色);
	GotoxyAndPrint((MAP_X + MAP_X_WALL) / 4 - 3, 32, "空格:  开火", 提示颜色);
}
void CGame::DrawGameInfo(vector<CTank>& myTank,vector<CTank> &enemyTank)
{
	//获取存活敌坦数量
	int eneTankCount = enemyTank.size();
	//获取当前难度
	char level[10];
	if (m_levelEneTank == 300) strcpy_s(level, 10, "简单\0");
	else if (m_levelEneTank == 200) strcpy_s(level, 10, "一般\0");
	else if (m_levelEneTank == 100)strcpy_s(level, 10, "困难\0");
	//运行or暂停状态
	GotoxyAndPrint(MAP_X_WALL/2 + 1, 1, "RUNNING",提示颜色);
	GotoxyAndPrint(MAP_X_WALL/2 + 1, 2, "Q: 暂停游戏", 提示颜色);
	// 当前关卡
	if (m_stage <= m_maxStage)
	{
		GotoxyAndPrint((MAP_X + MAP_X_WALL) / 4 - 3, 5, "", 提示颜色);
		printf("当前关卡: %2d", m_stage);
	}
	else
	{
		GotoxyAndPrint((MAP_X + MAP_X_WALL) / 4 - 3, 5, "当前关卡: 全部通关", 提示颜色);
	}
	// 坦克生命值
	if (myTank.size() == 2)
	{
		GotoxyAndPrint((MAP_X + MAP_X_WALL) / 4 - 3, 7, "", 提示颜色);
		printf("A 生命值: %2d", myTank[0].m_blood);
		GotoxyAndPrint((MAP_X + MAP_X_WALL) / 4 - 3, 9, "", 提示颜色);
		printf("B 生命值: %2d", myTank[1].m_blood);
	}
	else if (myTank.size() == 1)
	{
		if (myTank[0].m_who == 我方坦克A)
		{
			GotoxyAndPrint((MAP_X + MAP_X_WALL) / 4 - 3, 7, "", 提示颜色);
			printf("A 生命值: %2d", myTank[0].m_blood);
			GotoxyAndPrint((MAP_X + MAP_X_WALL) / 4 - 3, 9, "B 生命值: 阵亡", 提示颜色);
		}
		else if (myTank[0].m_who == 我方坦克B)
		{
			GotoxyAndPrint((MAP_X + MAP_X_WALL) / 4 - 3, 7, "A 生命值: 阵亡", 提示颜色);
			GotoxyAndPrint((MAP_X + MAP_X_WALL) / 4 - 3, 9, "", 提示颜色);
			printf("B 生命值: %2d", myTank[0].m_blood);
		}
	}
	else if (myTank.size() == 0)
	{
		GotoxyAndPrint((MAP_X + MAP_X_WALL) / 4 - 3, 7, "A 生命值: 阵亡", 提示颜色);
		GotoxyAndPrint((MAP_X + MAP_X_WALL) / 4 - 3, 9, "B 生命值: 阵亡", 提示颜色);
	}
	//游戏信息打印
	GotoxyAndPrint((MAP_X + MAP_X_WALL) / 4 - 3, 11, "", 提示颜色);
	printf("当前分数: %2d", ENEMY_TANK_AMOUNT - eneTankCount);
	GotoxyAndPrint((MAP_X + MAP_X_WALL) / 4 - 3, 13, "", 提示颜色);
	printf("敌坦个数: %2d", eneTankCount);
	GotoxyAndPrint((MAP_X + MAP_X_WALL) / 4 - 3, 15, "", 提示颜色);
	printf("当前难度: %s", level);
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
			GotoxyAndPrint(MAP_X / 4 - 5, MAP_Y / 2 - 6 + 2 * i, menu[i],  提示颜色);
		}
		else
			GotoxyAndPrint(MAP_X / 4 - 5, MAP_Y / 2 - 6 + 2 * i, menu[i],默认颜色);
	}
}