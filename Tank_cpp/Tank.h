#pragma once
#include "Bullet.h"

class CTank
{
public:
	COORD core;			//���ĵ�
	COORD body[5];		//�����ڵ�
	enum direction dir;	//����
	unsigned blood;		//Ѫ��
	bool isAlive;		//�Ƿ���
	int m_who;			//��һ��
	CBullet bullet;
public:
	CTank(COORD cor, enum direction di,int bl,int who) :core(cor) ,body{0},dir(di),blood(bl),isAlive(true),m_who(who)
	{
		SetTankShape();
	}
	void SetTankShape();								  //����̹����̬

	

	void CleanTankTail(COORD oldCore, PCOORD oldBody);			  //�����̹��
	void ManipulateMyTank(CTank * penemytank); //�����ҷ�̹��
	bool IsMyTankMeetOther(int dir, CTank  *penemytank);//�赲�ҷ�̹��
	void ManipulateEneTank(CTank pmytank, CTank * penemytank);//���ݵз�̹��
	bool IsEneTankMeetOther(int dir, CTank pmytank, CTank * penemytank);//�赲�з�̹��
};

int GetLiveEnemyAmount(CTank* penemytank);					  //���о�����