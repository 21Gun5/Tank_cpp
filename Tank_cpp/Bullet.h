#pragma once
#include <windows.h>
#include "Func.h"

class CTank;
class CMap;

class CBullet
{
public:
	COORD m_core;			//����
	enum  direction m_dir;	//����
	int m_state;			//�ӵ�״̬
	int m_who;				//��һ�����ӵ�
public:
	CBullet();
	//void SetBullet(COORD core, enum direction dir);
	void SetBullet(CTank tank);
	void MoveBullet();	//�ƶ��ӵ�
	void CleanBullet(COORD oldBulCore);	//������ӵ�
	//void IsMyBulMeetOther(CTank tank, CTank* pMyTank,CTank * penemytank,CMap &map); //�ҷ��ӵ���ײ
	//void IsEneBulMeetOther(CTank *pMyTank, CTank* pEnemyTank,  CMap &map);//�з��ӵ���ײ
	void IsBulMeetOther(CTank tank, CTank* pMyTank,CTank * penemytank,CMap &map); //�ҷ��ӵ���ײ

	void DrawBullet( CMap map);				//��ӡ�ӵ�
};

