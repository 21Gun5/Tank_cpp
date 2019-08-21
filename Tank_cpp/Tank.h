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
	void ManipulateTank(CTank* pMyTank, CTank* pEnemyTank, CMap map, CGame& game);
	bool IsTankMeetOther(int dir, CTank* pMyTank, CTank  *pEnemyTank, CMap map);//�赲�ҷ�̹��
	void DrawTank();	//��ӡ̹��
};

int GetLiveEnemyAmount(CTank* penemytank);					  //���о�����