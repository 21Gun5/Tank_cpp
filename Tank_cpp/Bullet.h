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
	//COORD m_core;			//����
	//int m_dir;	//����
	//int m_state;			//�ӵ�״̬
	//int m_who;				//��һ�����ӵ�
private:
	COORD m_core;			//����
	int m_dir;	//����
	int m_state;			//�ӵ�״̬
	int m_who;				//��һ�����ӵ�
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
	void MoveBullet();	//�ƶ��ӵ�
	void CleanBullet(COORD oldBulCore);	//������ӵ�
	void IsBulMeetOther(CTank &tank, vector<CTank>& myTank, vector<CTank>& enemyTank,CMap &map,CGame &game); //�ҷ��ӵ���ײ

	void DrawBullet( CMap map);				//��ӡ�ӵ�
};

