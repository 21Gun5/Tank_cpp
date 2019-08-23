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

// 获取私有成员
bool CGame::GetIsRunning()
{
	return m_isRunning;
}
int CGame::GetLevelEneTank()
{
	return m_levelEneTank;
}
int CGame::GetLevelEneBul()
{
	return m_levelEneBul;
}
int CGame::GetStage()
{
	return m_stage;
}
bool CGame::GetIsOver()
{
	return m_isOver;
}
int CGame::GetMaxStage()
{
	return m_maxStage;
}
bool CGame::GetNeedLoadNewStage()
{
	return m_needLoadNewStage;
}
int CGame::GetMyTankAmount()
{
	return m_myTankAmount;
}
int CGame::GetEnemyTankAmount()
{
	return m_enemyTankAmount;
}
// 修改私有成员
void CGame::SetIsRunning(bool isRunning)
{
	m_isRunning = isRunning;
}
void CGame::SetLevelEneTank(int levelEneTank)
{
	m_levelEneTank = levelEneTank;
}
void CGame::SetLevelEneBul(int levelEneBul)
{
	m_levelEneBul = levelEneBul;
}
void CGame::SetStage(int stage)
{
	m_stage = stage;
}
void  CGame::SetIsOver(bool isOver)
{
	m_isOver = isOver;
}
void CGame::SetMaxStage(int maxStage)
{
	m_maxStage = maxStage;
}
void  CGame::SetNeedLoadNewStage(bool needLoadNewStage)
{
	m_needLoadNewStage = needLoadNewStage;
}
void CGame::SetMyTankAmount(int myTankAmount)
{
	m_myTankAmount = myTankAmount;
}
void CGame::SetEnemyTankAmount(int enemyTankAmount)
{
	m_enemyTankAmount = enemyTankAmount;
}
// 功能函数
void CGame::GameInit(CMap& map)
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
				map.SetArrMap(x, y, 边界);
			}
			//泉水
			if (x >= MAP_X_WALL / 4 - 2 && x <= MAP_X_WALL / 4 + 3 && y >= MAP_Y - 2 - 3 && y <= MAP_Y - 2)
			{
				if (x >= MAP_X_WALL / 4 && x <= MAP_X_WALL / 4 + 1 && y >= MAP_Y - 2 - 1 && y <= MAP_Y - 2)
					map.SetArrMap(x, y, 泉水);
				//else
				//	map.m_nArrMap[x][y] = 土块;
			}
		}
	}

	// 控制台相关设置
	SetCursorState(false);				//隐藏光标
	system("title Tank");				//设置标题

	// 窗口大小
	char strCmd[50];
	sprintf_s(strCmd, 50, "mode con cols=%d lines=%d", MAP_X, MAP_Y);
	system(strCmd);

	//初始化随机数种子
	srand((unsigned int)time(0));

	//播放背景音乐(先不放，烦的一批
	mciSendString("open conf/BGM.mp3 alias bgm", NULL, 0, NULL);//打开文件
	mciSendString("play bgm repeat", NULL, 0, NULL);			  // 循环播放
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
void CGame::SaveGameFile(vector<CTank>& myTank, vector<CTank>& enemyTank, CMap map)
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
	//写入游戏属性
	fwrite(&this->m_isRunning, sizeof(int), 1, pFile);		//游戏运行状态
	fwrite(&this->m_levelEneTank, sizeof(int), 1, pFile);	//写入难度，控制敌方坦克速度
	fwrite(&this->m_levelEneBul, sizeof(int), 1, pFile);	//写入难度，控制敌方子弹速度
	fwrite(&this->m_stage, sizeof(int), 1, pFile);//写入关卡数
	fwrite(&this->m_isOver, sizeof(bool), 1, pFile);//是否结束
	fwrite(&this->m_maxStage, sizeof(int), 1, pFile);//最大关卡
	fwrite(&this->m_needLoadNewStage, sizeof(bool), 1, pFile);//是否需要导入新关卡
	m_myTankAmount = myTank.size();
	fwrite(&this->m_myTankAmount, sizeof(int), 1, pFile);//我的坦克数量（读取时用
	m_enemyTankAmount = enemyTank.size();
	fwrite(&this->m_enemyTankAmount, sizeof(int), 1, pFile);//敌军坦克数量（
	// 写入障碍
	for (int x = 0; x < MAP_X_WALL; x++)
	{
		for (int y = 0; y < MAP_Y; y++)
		{
			int map_point_tmp = map.GetArrMap(x, y);
			fwrite(&map_point_tmp, sizeof(int), 1, pFile);
		}
	}
	// 写入我方
	for (vector<CTank>::iterator it = myTank.begin(); it != myTank.end(); it++)
	{
		//写入我方坦克
		COORD core_tmp = it->GetCore();
		fwrite(&core_tmp, sizeof(COORD), 1, pFile);//中心节点
		for (int i = 0; i < 5; i++)
		{
			COORD body_coor_tmp = it->GetBody(i);
			fwrite(&body_coor_tmp, sizeof(COORD), 1, pFile);//其他节点
		}
		int dir_tmp = it->GetDir();
		fwrite(&dir_tmp, sizeof(int), 1, pFile);//方向
		int blood_tmp = it->GetBlood();
		fwrite(&blood_tmp, sizeof(int), 1, pFile);//血量
		bool isAlve_tmp = it->GetIsAlive();
		fwrite(&isAlve_tmp, sizeof(bool), 1, pFile);//是否存活
		int who_tmp = it->GetWho();
		fwrite(&who_tmp, sizeof(int), 1, pFile);//身份
		bool isHidden_tmp = it->GetIsHidden();
		fwrite(&isHidden_tmp, sizeof(bool), 1, pFile);//是否隐藏
		int killCount_tmp = it->GetKillCount();
		fwrite(&killCount_tmp, sizeof(int), 1, pFile);//杀敌数
		int power_tmp = it->GetPower();
		fwrite(&power_tmp, sizeof(int), 1, pFile);//伤害

		//写入我方子弹
		COORD bul_core_tmp = it->m_bullet.GetCore();
		fwrite(&bul_core_tmp, sizeof(COORD), 1, pFile);//坐标
		int bul_dir_tmp = it->m_bullet.GetDir();
		fwrite(&bul_dir_tmp, sizeof(int), 1, pFile);//方向
		int bul_state_tmp = it->m_bullet.GetState();
		fwrite(&bul_state_tmp, sizeof(int), 1, pFile);//状态
		int bul_who_tmp = it->m_bullet.GetWho();
		fwrite(&bul_who_tmp, sizeof(int), 1, pFile);//哪一方的子弹
	}
	// 写入敌方
	for (vector<CTank>::iterator it = enemyTank.begin(); it != enemyTank.end(); it++)
	{
		//写入敌方坦克
		COORD core_tmp = it->GetCore();
		fwrite(&core_tmp, sizeof(COORD), 1, pFile);//中心节点
		for (int j = 0; j < 5; j++)
		{
			COORD body_coor_tmp = it->GetBody(j);
			fwrite(&body_coor_tmp, sizeof(COORD), 1, pFile);//其他节点
		}

		int dir_tmp = it->GetDir();
		fwrite(&dir_tmp, sizeof(int), 1, pFile);//方向
		int blood_tmp = it->GetBlood();
		fwrite(&blood_tmp, sizeof(int), 1, pFile);//血量
		bool isAlve_tmp = it->GetIsAlive();
		fwrite(&isAlve_tmp, sizeof(bool), 1, pFile);//是否存活
		int who_tmp = it->GetWho();
		fwrite(&who_tmp, sizeof(int), 1, pFile);//身份
		bool isHidden_tmp = it->GetIsHidden();
		fwrite(&isHidden_tmp, sizeof(bool), 1, pFile);//是否隐藏
		int killCount_tmp = it->GetKillCount();
		fwrite(&killCount_tmp, sizeof(int), 1, pFile);//杀敌数
		int power_tmp = it->GetPower();
		fwrite(&power_tmp, sizeof(int), 1, pFile);//伤害

		//写入敌方子弹
		COORD bul_core_tmp = it->m_bullet.GetCore();
		fwrite(&bul_core_tmp, sizeof(COORD), 1, pFile);//坐标
		int bul_dir_tmp = it->m_bullet.GetDir();
		fwrite(&bul_dir_tmp, sizeof(int), 1, pFile);//方向
		int bul_state_tmp = it->m_bullet.GetState();
		fwrite(&bul_state_tmp, sizeof(int), 1, pFile);//状态
		int bul_who_tmp = it->m_bullet.GetWho();
		fwrite(&bul_who_tmp, sizeof(int), 1, pFile);//哪一方的子弹

	}

	fclose(pFile);
}
void CGame::LoadGameFile(vector<CTank>& myTank, vector<CTank>& enemyTank, CMap& map, char* str)
{
	char* filename = (char*)malloc(40);
	sprintf_s(filename, 40, "%s%s", "conf/game/", str);
	FILE* pFile = NULL;
	errno_t err = fopen_s(&pFile, filename, "rb");
	//读取游戏属性
	fread(&this->m_isRunning, sizeof(int), 1, pFile);		//游戏运行状态
	fread(&this->m_levelEneTank, sizeof(int), 1, pFile);	//读取难度，控制敌方坦克速度
	fread(&this->m_levelEneBul, sizeof(int), 1, pFile);	//读取难度，控制敌方子弹速度
	fread(&this->m_stage, sizeof(int), 1, pFile);//写入关卡数
	fread(&this->m_isOver, sizeof(bool), 1, pFile);//是否结束
	fread(&this->m_maxStage, sizeof(int), 1, pFile);//最大关卡
	fread(&this->m_needLoadNewStage, sizeof(bool), 1, pFile);//是否需要导入新关卡
	fread(&this->m_myTankAmount, sizeof(int), 1, pFile);//我的坦克数量（读取时用
	fread(&this->m_enemyTankAmount, sizeof(int), 1, pFile);//敌军坦克数量（
	//读取障碍
	for (int x = 0; x < MAP_X_WALL; x++)
	{
		for (int y = 0; y < MAP_Y; y++)
		{
			int map_point_tmp;
			fread(&map_point_tmp, sizeof(int), 1, pFile);
			map.SetArrMap(x, y, map_point_tmp);
		}
	}
	//读取我方
	CTank mytankTmp;

	for (int i = 0; i < this->m_myTankAmount; i++)
	{
		//读取我方坦克
		COORD core_tmp;
		fread(&core_tmp, sizeof(COORD), 1, pFile);//中心节点
		mytankTmp.SetCore(core_tmp);
		for (int i = 0; i < 5; i++)
		{
			COORD body_coor_tmp;
			fread(&body_coor_tmp, sizeof(COORD), 1, pFile);//其他节点
			mytankTmp.SetBody(i, body_coor_tmp);
		}
		int dir_tmp;
		fread(&dir_tmp, sizeof(int), 1, pFile);//方向
		mytankTmp.SetDir(dir_tmp);
		int blood_tmp;
		fread(&blood_tmp, sizeof(int), 1, pFile);//血量
		mytankTmp.SetBlood(blood_tmp);
		bool isAlve_tmp;
		fread(&isAlve_tmp, sizeof(bool), 1, pFile);//是否存活
		mytankTmp.SetIsAlive(isAlve_tmp);
		int who_tmp;
		fread(&who_tmp, sizeof(int), 1, pFile);//身份
		mytankTmp.SetWho(who_tmp);
		bool isHidden_tmp;
		fread(&isHidden_tmp, sizeof(bool), 1, pFile);//是否隐藏
		mytankTmp.SetIsHidden(isHidden_tmp);
		int killCount_tmp;
		fread(&killCount_tmp, sizeof(int), 1, pFile);//杀敌数
		mytankTmp.SetKillCount(killCount_tmp);
		int power_tmp;
		fread(&power_tmp, sizeof(int), 1, pFile);//伤害
		mytankTmp.SetPower(power_tmp);

		//读取我方子弹		
		COORD bul_core_tmp;
		fread(&bul_core_tmp, sizeof(COORD), 1, pFile);//坐标
		mytankTmp.m_bullet.SetCore(bul_core_tmp);
		int bul_dir_tmp;
		fread(&bul_dir_tmp, sizeof(int), 1, pFile);//方向
		mytankTmp.m_bullet.SetDir(bul_dir_tmp);
		int bul_state_tmp;
		fread(&bul_state_tmp, sizeof(int), 1, pFile);//状态
		mytankTmp.m_bullet.SetState(bul_state_tmp);
		int bul_who_tmp;
		fread(&bul_who_tmp, sizeof(int), 1, pFile);//哪一方的子弹
		mytankTmp.m_bullet.SetWho(bul_who_tmp);
		// 临时坦克加入数组
		myTank.push_back(mytankTmp);
	}
	//读取敌方
	CTank enemytankTmp;
	for (int i = 0; i < this->m_enemyTankAmount; i++)
	{
		//读取敌方坦克
		COORD core_tmp;
		fread(&core_tmp, sizeof(COORD), 1, pFile);//中心节点
		enemytankTmp.SetCore(core_tmp);
		for (int i = 0; i < 5; i++)
		{
			COORD body_coor_tmp;
			fread(&body_coor_tmp, sizeof(COORD), 1, pFile);//其他节点
			enemytankTmp.SetBody(i, body_coor_tmp);
		}
		int dir_tmp;
		fread(&dir_tmp, sizeof(int), 1, pFile);//方向
		enemytankTmp.SetDir(dir_tmp);
		int blood_tmp;
		fread(&blood_tmp, sizeof(int), 1, pFile);//血量
		enemytankTmp.SetBlood(blood_tmp);
		bool isAlve_tmp;
		fread(&isAlve_tmp, sizeof(bool), 1, pFile);//是否存活
		enemytankTmp.SetIsAlive(isAlve_tmp);
		int who_tmp;
		fread(&who_tmp, sizeof(int), 1, pFile);//身份
		enemytankTmp.SetWho(who_tmp);
		bool isHidden_tmp;
		fread(&isHidden_tmp, sizeof(bool), 1, pFile);//是否隐藏
		enemytankTmp.SetIsHidden(isHidden_tmp);
		int killCount_tmp;
		fread(&killCount_tmp, sizeof(int), 1, pFile);//杀敌数
		enemytankTmp.SetKillCount(killCount_tmp);
		int power_tmp;
		fread(&power_tmp, sizeof(int), 1, pFile);//伤害
		enemytankTmp.SetPower(power_tmp);

		//fread(&enemytankTmp.m_core, sizeof(COORD), 1, pFile);//中心节点
		//for (int j = 0; j < 5; j++)
		//{
		//	fread(&enemytankTmp.m_body[j], sizeof(COORD), 1, pFile);//其他节点
		//}
		//fread(&enemytankTmp.m_dir, sizeof(int), 1, pFile);//方向
		//fread(&enemytankTmp.m_blood, sizeof(int), 1, pFile);//血量
		//fread(&enemytankTmp.m_isAlive, sizeof(bool), 1, pFile);//是否存活
		//fread(&enemytankTmp.m_who, sizeof(int), 1, pFile);//身份
		//fread(&enemytankTmp.m_isHidden, sizeof(bool), 1, pFile);//是否隐藏
		//fread(&enemytankTmp.m_killCount, sizeof(int), 1, pFile);//杀敌数
		//fread(&enemytankTmp.m_power, sizeof(int), 1, pFile);//伤害

		//读取敌方子弹		
		COORD bul_core_tmp;
		fread(&bul_core_tmp, sizeof(COORD), 1, pFile);//坐标
		enemytankTmp.m_bullet.SetCore(bul_core_tmp);
		int bul_dir_tmp;
		fread(&bul_dir_tmp, sizeof(int), 1, pFile);//方向
		enemytankTmp.m_bullet.SetDir(bul_dir_tmp);
		int bul_state_tmp;
		fread(&bul_state_tmp, sizeof(int), 1, pFile);//状态
		enemytankTmp.m_bullet.SetState(bul_state_tmp);
		int bul_who_tmp;
		fread(&bul_who_tmp, sizeof(int), 1, pFile);//哪一方的子弹
		enemytankTmp.m_bullet.SetWho(bul_who_tmp);

		// 临时敌军坦克添加进数组
		enemyTank.push_back(enemytankTmp);
	}


	fclose(pFile);
}
// 各种打印
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
	GotoxyAndPrint((MAP_X + MAP_X_WALL) / 4 - 3, 24, " 操  作  说  明", 提示颜色);
	GotoxyAndPrint((MAP_X + MAP_X_WALL) / 4 - 3, 26, "W/I: 上  S/K: 下", 提示颜色);
	GotoxyAndPrint((MAP_X + MAP_X_WALL) / 4 - 3, 28, "A/J: 左  D/L: 右", 提示颜色);
	GotoxyAndPrint((MAP_X + MAP_X_WALL) / 4 - 3, 30, "Q:  暂停游戏", 提示颜色);
	GotoxyAndPrint((MAP_X + MAP_X_WALL) / 4 - 3, 32, "空格/H: 开火", 提示颜色);
}
void CGame::DrawGameInfo(vector<CTank>& myTank, vector<CTank>& enemyTank)
{
	//获取存活敌坦数量
	int eneTankCount = enemyTank.size();
	//获取当前难度
	char level[10];
	if (m_levelEneTank == 300) strcpy_s(level, 10, "简单\0");
	else if (m_levelEneTank == 200) strcpy_s(level, 10, "一般\0");
	else if (m_levelEneTank == 100)strcpy_s(level, 10, "困难\0");
	//运行or暂停状态
	GotoxyAndPrint(MAP_X_WALL / 2 + 1, 1, "RUNNING", 提示颜色);
	GotoxyAndPrint(MAP_X_WALL / 2 + 1, 2, "Q: 暂停游戏", 提示颜色);
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
		printf("A 生命值: %2d", myTank[0].GetBlood());
		GotoxyAndPrint((MAP_X + MAP_X_WALL) / 4 - 3, 9, "", 提示颜色);
		printf("B 生命值: %2d", myTank[1].GetBlood());
	}
	else if (myTank.size() == 1)
	{
		if (myTank[0].GetWho() == 我方坦克A)
		{
			GotoxyAndPrint((MAP_X + MAP_X_WALL) / 4 - 3, 7, "", 提示颜色);
			printf("A 生命值: %2d", myTank[0].GetBlood());
			GotoxyAndPrint((MAP_X + MAP_X_WALL) / 4 - 3, 9, "B 生命值: 阵亡", 提示颜色);
		}
		else if (myTank[0].GetWho() == 我方坦克B)
		{
			GotoxyAndPrint((MAP_X + MAP_X_WALL) / 4 - 3, 7, "A 生命值: 阵亡", 提示颜色);
			GotoxyAndPrint((MAP_X + MAP_X_WALL) / 4 - 3, 9, "", 提示颜色);
			printf("B 生命值: %2d", myTank[0].GetBlood());
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
			GotoxyAndPrint(MAP_X / 4 - 5, MAP_Y / 2 - 6 + 2 * i, menu[i], 提示颜色);
		}
		else
			GotoxyAndPrint(MAP_X / 4 - 5, MAP_Y / 2 - 6 + 2 * i, menu[i], 默认颜色);
	}
}