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
public:
	CBullet();
	void SetBullet(COORD core, enum direction dir);
	void MoveBullet();	//�ƶ��ӵ�
	void CleanBullet(COORD oldBulCore);	//������ӵ�
	void IsMyBulMeetOther(CTank tank, CTank * penemytank,CMap &map); //�ҷ��ӵ���ײ
	void IsEneBulMeetOther(CTank &tank, CTank* penemytank,  CMap &map);//�з��ӵ���ײ
	void DrawBullet( CTank tank, CMap map);				//��ӡ�ӵ�
};

