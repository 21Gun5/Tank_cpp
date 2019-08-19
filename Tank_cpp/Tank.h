#pragma once
#include <windows.h>
#include "Bullet.h"
#include "Map.h"

class CTank
{
public:
	COORD m_core;			//���ĵ�
	COORD m_body[5];		//�����ڵ�
	enum direction m_dir;	//����
	unsigned m_blood;		//Ѫ��
	bool m_isAlive;		//�Ƿ���
	int m_who;			//��һ��
	CBullet m_bullet;
public:
	CTank(COORD core, enum direction dir,int blood,int who) :m_core(core) ,m_body{0},m_dir(dir),m_blood(blood),m_isAlive(true),m_who(who)
	{
		SetTankShape();
	}
	void SetTankShape();								//����̹����̬
	void CleanTankTail(COORD oldCore, PCOORD oldBody);	//�����̹��
	void ManipulateMyTank(CTank * penemytank,CMap map);	//�����ҷ�̹��
	bool IsMyTankMeetOther(int dir, CTank  *penemytank, CMap map);//�赲�ҷ�̹��
	void ManipulateEneTank(CTank pmytank, CTank * penemytank, CMap map);//���ݵз�̹��
	bool IsEneTankMeetOther(int dir, CTank pmytank, CTank * penemytank , CMap map);//�赲�з�̹��

	void DrawTank();	//��ӡ̹��
};

int GetLiveEnemyAmount(CTank* penemytank);					  //���о�����