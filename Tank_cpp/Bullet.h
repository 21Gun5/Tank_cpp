#pragma once
#include <windows.h>
#include "Func.h"
#include <vector>
using namespace std;

class CTank;
class CMap;
class CGame;

class CBullet
{
private:
	COORD m_core;			// 坐标
	int m_dir;				// 方向
	int m_state;			// 状态
	int m_who;				// 归属
public:
	// 获取私有成员
	COORD GetCore();
	int GetDir();
	int GetState();
	int GetWho();
	// 设置私有成员
	void SetCore(COORD core);
	void SetDir(int dir);
	void SetState(int state);
	void SetWho(int who);
	// 功能函数
	CBullet();
	void SetBullet(CTank tank);			//设置子弹属性
	void MoveBullet();					//移动子弹
	void DrawBullet(CMap map);			//打印子弹
	void CleanBullet(COORD oldBulCore);	//清理旧子弹
	void IsBulMeetOther(CTank& tank, vector<CTank>& myTank, vector<CTank>& enemyTank, CMap& map, CGame& game); //子弹碰撞
};
