#pragma once

#include "Func.h"

class CTank;//����໥��������
class CMap;

class CBullet
{
public:
	COORD core;			//����
	enum  direction dir;//����
	int state;			//�ӵ�״̬
public:
	CBullet() :core{ 0,0 }, dir(UP), state(������){}
	void SetBullet(COORD cor, enum direction di);
	void MoveBullet();	//�ƶ��ӵ�
	void CleanBullet(COORD oldBulCore);	//������ӵ�

	void IsMyBulMeetOther(CTank tank, CTank * penemytank,CMap &map); //�ҷ��ӵ���ײ

	void IsEneBulMeetOther(CTank tank, CTank* penemytank,  CMap &map);//�з��ӵ���ײ

	void DrawBullet( CTank tank, CMap map);				//��ӡ�ӵ�
};

