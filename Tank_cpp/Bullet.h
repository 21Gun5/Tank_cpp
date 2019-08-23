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
public:
	//COORD m_core;			//坐标
	//int m_dir;	//方向
	//int m_state;			//子弹状态
	//int m_who;				//哪一方的子弹
private:
	COORD m_core;			//坐标
	int m_dir;	//方向
	int m_state;			//子弹状态
	int m_who;				//哪一方的子弹
public:
	CBullet();

	COORD GetCore();
	int GetDir();
	int GetState();
	int GetWho();

	void SetCore(COORD core);
	void SetDir(int dir);
	void SetState(int state);
	void SetWho(int who);



	void SetBullet(CTank tank);
	void MoveBullet();	//移动子弹
	void CleanBullet(COORD oldBulCore);	//清理旧子弹
	void IsBulMeetOther(CTank &tank, vector<CTank>& myTank, vector<CTank>& enemyTank,CMap &map,CGame &game); //我方子弹碰撞

	void DrawBullet( CMap map);				//打印子弹
};

