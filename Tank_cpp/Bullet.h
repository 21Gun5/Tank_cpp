#pragma once
#include <windows.h>
#include "Func.h"
#include "Map.h"

//��ǰ����
//include��������������tank���壬�����г�Ա����bullet���໥���������
//class������ֻ�����д��࣬��û�о��嶨�壬��ûǣ���Ա����û����໥����
class CTank;

class CBullet
{
public:
	COORD m_core;			//����
	enum  direction m_dir;//����
	int m_state;			//�ӵ�״̬
public:
	CBullet() :m_core{ 0,0 }, m_dir(UP), m_state(������){}
	void SetBullet(COORD core, enum direction dir);
	void MoveBullet();	//�ƶ��ӵ�
	void CleanBullet(COORD oldBulCore);	//������ӵ�
	void IsMyBulMeetOther(CTank tank, CTank * penemytank,CMap &map); //�ҷ��ӵ���ײ
	void IsEneBulMeetOther(CTank tank, CTank* penemytank,  CMap &map);//�з��ӵ���ײ
	void DrawBullet( CTank tank, CMap map);				//��ӡ�ӵ�
};

