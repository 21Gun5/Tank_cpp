#pragma once

class CTank;//����໥��������

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

	void IsMyBulMeetOther(CTank tank, CTank * penemytank ); //�ҷ��ӵ���ײ

	void IsEneBulMeetOther(CTank tank, CTank* penemytank);//�з��ӵ���ײ
};

