#pragma once
#include <windows.h>
#include "Bullet.h"

class CGame;
class CMap;

class CTank
{
public:
	COORD m_core;			//���ĵ�
	COORD m_body[5] = {0};	//�����ڵ�
	enum direction m_dir;	//����
	unsigned m_blood;		//Ѫ��
	bool m_isAlive;			//�Ƿ���
	int m_who;				//��һ��
	CBullet m_bullet;
public:
	CTank(COORD core, enum direction dir, int blood, int who);
	void SetTankShape();								//����̹����̬
	void CleanTankTail(COORD oldCore, PCOORD oldBody);	//�����̹��
	void ManipulateMyTank(CTank * penemytank,CMap map,CGame &game);	//�����ҷ�̹��
	bool IsMyTankMeetOther(int dir, CTank  *penemytank, CMap map);//�赲�ҷ�̹��
	void ManipulateEneTank(CTank pmytank, CTank * penemytank, CMap map);//���ݵз�̹��
	bool IsEneTankMeetOther(int dir, CTank pmytank, CTank * penemytank , CMap map);//�赲�з�̹��
	void DrawTank();	//��ӡ̹��
};

int GetLiveEnemyAmount(CTank* penemytank);					  //���о�����