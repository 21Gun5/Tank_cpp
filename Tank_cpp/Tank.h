#pragma once
#include <windows.h>
#include <vector>
#include "Bullet.h"
using namespace std;

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
	bool m_isHided;			//�Ƿ����أ��Ƿ��ܱ��ҡ��ܱ����ܿ���
	int m_killCount = 0;//ɱ����
	CBullet m_bullet;
	int m_power = 1;
public:
	CTank(COORD core, enum direction dir, int blood, int who,int power=1);
	void SetTankShape();								//����̹����̬
	void CleanTankTail(COORD oldCore, PCOORD oldBody);	//�����̹��
	void ManipulateTank(vector<CTank>& myTank, vector<CTank>& enemyTank, CMap map, CGame& game);
	bool IsTankMeetOther(int dir, vector<CTank>& myTank,vector<CTank> &enemyTank, CMap map);//�赲�ҷ�̹��
	void DrawTank();	//��ӡ̹��
};

//int GetLiveEnemyAmount(vector<CTank>& enemyTank);					  //���о�����