#pragma once


class CBullet
{
public:
	COORD core;			//����
	enum  direction dir;//����
	int state;			//�ӵ�״̬
public:
	CBullet() :core{0,0}, dir(UP), state(������)
	{
	}
	void MoveBullet(PBULLET pbullet);	//�ƶ��ӵ�
	void CleanBullet(COORD oldBulCore);	//������ӵ�
	void IsMyBulMeetOther(PBULLET pbullet, PTANK penemytank, PTANK ptank); //�ҷ��ӵ���ײ
	void IsEneBulMeetOther(PBULLET pbullet, PTANK penemytank, PTANK ptank);//�з��ӵ���ײ
};

