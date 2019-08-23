#pragma once

#include <vector>

using namespace std;

class CMap;
class CTank;

class CGame
{
//public:
	//bool m_isRunning = false;
	//int m_levelEneTank = 200;
	//int m_levelEneBul = 70;
	//int m_stage = 1;//游戏关卡
	//bool m_isOver = 0;
	//int m_maxStage = 3;
	//bool m_needLoadNewStage = 0;//是否需要导入新关卡
	//int m_myTankAmount;
	//int m_enemyTankAmount;
private:
	bool m_isRunning = false;
	int m_levelEneTank = 200;
	int m_levelEneBul = 70;
	int m_stage = 1;//游戏关卡
	bool m_isOver = 0;
	int m_maxStage = 3;
	bool m_needLoadNewStage = 0;//是否需要导入新关卡
	int m_myTankAmount;
	int m_enemyTankAmount;
public:
	const char* menuPlay[3] = { "开始游戏","读取游戏","退出游戏" };
	const char* menuWhoMap[3] = { "系统默认","玩家提供","返回上页" };
	const char* menuWhenMap[3] = { "新建地图","已有地图","返回上页" };
	const char* menuLevel[3] = { "简单","一般","困难" };
public:

	bool GetisRunning () ;
	int GetlevelEneTank () ;
	int GetlevelEneBul () ;
	int Getstage () ;//游戏关卡
	bool GetisOver () ;
	int GetmaxStage () ;
	bool GetneedLoadNewStage () ;//是否需要导入新关卡
	int GetmyTankAmount();
	int GetenemyTankAmount();

	void SetisRunning(bool isRunning);
	void SetlevelEneTank(int levelEneTank);
	void SetlevelEneBul(int levelEneBul);
	void Setstage(int stage);//游戏关卡
	void  SetisOver(bool isOver);
	void SetmaxStage(int maxStage);
	void  SetneedLoadNewStage(bool needLoadNewStage);//是否需要导入新关卡
	void SetmyTankAmount(int myTankAmount);
	void SetenemyTankAmount(int enemyTankAmount);


	void GameInit(CMap& map);				//初始化工作
	char* ShowGameFile();					//显示存档
	void GameOver(vector<CTank>& enemyTank);		//善后工作
	void NextStage();//下一关

	int SelectMenu(int size, int* pindex);  //选择菜单项
	void SaveGameFile(vector<CTank>& myTank, vector<CTank>& enemyTank,CMap map);	//存档
	void LoadGameFile(vector<CTank>& myTank, vector<CTank>& enemyTank, CMap &map, char* str);	//读档

	// 打印相关
	void DrawLogo();						//打印图标
	void DrawGameHelp();					//打印帮助
	void DrawGameInfo(vector<CTank>& myTank, vector<CTank>& enemyTank);			//打印游戏信息
	void DrawMenu(const char** menu, int size, int index);		//打印各种菜单
};


