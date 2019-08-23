#pragma once
#include <windows.h>
#include <vector>
#include "Bullet.h"
using namespace std;

class CGame;
class CMap;

class CTank
{
private:
	COORD m_core;			// ���ĵ�
	COORD m_body[5] = { 0 };// �����ڵ�
	int m_dir;				// ����
	unsigned m_blood;		// Ѫ��
	bool m_isAlive;			// �Ƿ���
	int m_who;				// ��һ��
	bool m_isHidden;		// �Ƿ����أ��Ƿ��ܱ����ܿ���
	int m_killCount = 0;	// ɱ����
	int m_power = 1;
public:
	CBullet m_bullet;		//  �ӵ�
public:
	// ��ȡ˽�г�Ա
	COORD GetCore();
	COORD GetBody(int i);
	int GetDir();
	unsigned GetBlood();
	bool GetIsAlive();
	int GetWho();
	bool GetIsHidden();
	int GetKillCount();
	int GetPower();
	// ����˽�г�Ա
	void SetCore(COORD core);
	void SetBody(int i, COORD coor);
	void SetDir(int dir);
	void SetBlood(int blood);
	void SetIsAlive(bool isAlive);
	void SetWho(int who);
	void SetIsHidden(bool isHidden);
	void SetKillCount(int killCount);
	void SetPower(int power);
	// ���캯��
	CTank();
	CTank(COORD core, enum direction dir, int blood, int who, int power = 1);
	// ���ܺ���
	void DrawTank();									// ��ӡ̹��
	void SetTankShape();								// ������̬
	void CleanTankTail(COORD oldCore, PCOORD oldBody);	// �����̹��
	bool IsTankMeetOther(int dir, vector<CTank>& myTank, vector<CTank>& enemyTank, CMap map);	// �ж��赲
	void ManipulateTank(vector<CTank>& myTank, vector<CTank>& enemyTank, CMap map, CGame& game);// ����̹��
};