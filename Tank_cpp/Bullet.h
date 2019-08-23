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
private:
	COORD m_core;			// ����
	int m_dir;				// ����
	int m_state;			// ״̬
	int m_who;				// ����
public:
	// ��ȡ˽�г�Ա
	COORD GetCore();
	int GetDir();
	int GetState();
	int GetWho();
	// ����˽�г�Ա
	void SetCore(COORD core);
	void SetDir(int dir);
	void SetState(int state);
	void SetWho(int who);
	// ���ܺ���
	CBullet();
	void SetBullet(CTank tank);			//�����ӵ�����
	void MoveBullet();					//�ƶ��ӵ�
	void DrawBullet(CMap map);			//��ӡ�ӵ�
	void CleanBullet(COORD oldBulCore);	//������ӵ�
	void IsBulMeetOther(CTank& tank, vector<CTank>& myTank, vector<CTank>& enemyTank, CMap& map, CGame& game); //�ӵ���ײ
};
