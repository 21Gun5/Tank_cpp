#pragma once
#include <windows.h>
#include <vector>
#include "Bullet.h"
using namespace std;

class CGame;
class CMap;

class CTank
{
private:
	COORD m_core;			// 中心点
	COORD m_body[5] = { 0 };// 其他节点
	int m_dir;				// 方向
	unsigned m_blood;		// 血量
	bool m_isAlive;			// 是否存活
	int m_who;				// 哪一方
	bool m_isHidden;		// 是否隐藏（是否能被打、能开火
	int m_killCount = 0;	// 杀敌数
	int m_power = 1;
public:
	CBullet m_bullet;		//  子弹
public:
	// 获取私有成员
	COORD GetCore();
	COORD GetBody(int i);
	int GetDir();
	unsigned GetBlood();
	bool GetIsAlive();
	int GetWho();
	bool GetIsHidden();
	int GetKillCount();
	int GetPower();
	// 设置私有成员
	void SetCore(COORD core);
	void SetBody(int i, COORD coor);
	void SetDir(int dir);
	void SetBlood(int blood);
	void SetIsAlive(bool isAlive);
	void SetWho(int who);
	void SetIsHidden(bool isHidden);
	void SetKillCount(int killCount);
	void SetPower(int power);
	// 构造函数
	CTank();
	CTank(COORD core, enum direction dir, int blood, int who, int power = 1);
	// 功能函数
	void DrawTank();									// 打印坦克
	void SetTankShape();								// 设置形态
	void CleanTankTail(COORD oldCore, PCOORD oldBody);	// 清除旧坦克
	bool IsTankMeetOther(int dir, vector<CTank>& myTank, vector<CTank>& enemyTank, CMap map);	// 判断阻挡
	void ManipulateTank(vector<CTank>& myTank, vector<CTank>& enemyTank, CMap map, CGame& game);// 操纵坦克
};