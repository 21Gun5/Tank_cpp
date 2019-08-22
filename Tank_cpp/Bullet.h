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
	COORD m_core;			//����
	enum  direction m_dir;	//����
	int m_state;			//�ӵ�״̬
	int m_who;				//��һ�����ӵ�
public:
	CBullet();
	void SetBullet(CTank tank);
	void MoveBullet();	//�ƶ��ӵ�
	void CleanBullet(COORD oldBulCore);	//������ӵ�
	void IsBulMeetOther(CTank &tank, vector<CTank>& myTank, vector<CTank>& enemyTank,CMap &map,CGame &game); //�ҷ��ӵ���ײ

	void DrawBullet( CMap map);				//��ӡ�ӵ�
};

