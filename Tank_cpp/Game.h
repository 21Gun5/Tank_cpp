#pragma once
#include <vector>
using namespace std;

class CMap;
class CTank;

class CGame
{
private:
	bool m_isRunning = false;		//是否运行
	int m_levelEneTank = 300;		//难度（敌坦速度
	int m_levelEneBul = 90;			//难度（敌弹速度
	int m_stage = 1;				//游戏关卡
	bool m_isOver = false;			//是否结束
	int m_maxStage = 3;				//最大关卡
	bool m_needLoadNewStage = false;//是否需要导入新关卡
	int m_myTankAmount;				//现存我坦（读档用
	int m_enemyTankAmount;			//现存敌坦数量（读档用
public:
	// 选择菜单
	const char* menuPlay[3] = { "开始游戏","读取游戏","退出游戏" };
	const char* menuWhoMap[3] = { "系统默认","玩家提供","返回上页" };
	const char* menuWhenMap[3] = { "新建地图","已有地图","返回上页" };
	const char* menuLevel[3] = { "简单","一般","困难" };
public:
	//获取属性
	bool GetIsRunning();
	int GetLevelEneTank();
	int GetLevelEneBul();
	int GetStage();
	bool GetIsOver();
	int GetMaxStage();
	bool GetNeedLoadNewStage();
	int GetMyTankAmount();
	int GetEnemyTankAmount();
	// 设置属性
	void SetIsRunning(bool isRunning);
	void SetLevelEneTank(int levelEneTank);
	void SetLevelEneBul(int levelEneBul);
	void SetStage(int stage);
	void SetIsOver(bool isOver);
	void SetMaxStage(int maxStage);
	void SetNeedLoadNewStage(bool needLoadNewStage);
	void SetMyTankAmount(int myTankAmount);
	void SetEnemyTankAmount(int enemyTankAmount);
	// 功能函数
	void GameInit(CMap& map);				//初始化工作
	char* ShowGameFile();					//显示存档
	void GameOver(vector<CTank>& enemyTank);//善后工作
	void NextStage();						//下一关
	int SelectMenu(int size, int* pindex);  //选择菜单项
	void SaveGameFile(vector<CTank>& myTank, vector<CTank>& enemyTank, CMap map);				//存档
	void LoadGameFile(vector<CTank>& myTank, vector<CTank>& enemyTank, CMap& map, char* str);	//读档
	// 打印相关
	void DrawLogo();						//打印图标
	void DrawGameHelp();					//打印帮助
	void DrawMenu(const char** menu, int size, int index);				//打印各种菜单
	void DrawGameInfo(vector<CTank>& myTank, vector<CTank>& enemyTank);	//打印游戏信息
};
