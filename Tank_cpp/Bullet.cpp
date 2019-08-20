#include "Bullet.h"
#include "Tank.h"
#include "Map.h"
#pragma comment(lib,"winmm.lib")

CBullet::CBullet()
{
	m_core = { 0,0 };
	m_dir = UP;
	m_state = ������;
}
void CBullet::SetBullet(COORD core, enum direction dir)
{
	m_core = core;
	m_dir = dir;
}
void CBullet::MoveBullet()
{
	switch (this->m_dir)
	{
	case UP:
		this->m_core.Y--;
		break;
	case DOWN:
		this->m_core.Y++;
		break;
	case LEFT:
		this->m_core.X--;
		break;
	case RIGHT:
		this->m_core.X++;
		break;
	default:
		break;
	}
}
void CBullet::CleanBullet(COORD oldBulCore)
{
	GotoxyAndPrint(oldBulCore.X, oldBulCore.Y, "  ");
}
void CBullet::IsMyBulMeetOther(CTank tank, CTank* pMyTank,CTank* pEnemyTank, CMap& map)
{
	//tank �������ڽ���ֵ+1

	//���߽�
	if (this->m_core.X <= 0 ||
		this->m_core.X >= MAP_X_WALL / 2 ||
		this->m_core.Y <= 0 ||
		this->m_core.Y >= MAP_Y - 1)
	{
		this->m_state = ������;
	}
	//�������ϰ�
	if (map.m_nArrMap[this->m_core.X][this->m_core.Y] == ����)
	{
		this->m_state = ������;
		map.m_nArrMap[this->m_core.X][this->m_core.Y] = �յ�;
	}
	//��ʯ���ϰ�
	if (map.m_nArrMap[this->m_core.X][this->m_core.Y] == ʯ��)
	{
		this->m_state = ������;
	}
	//��Ȫˮ
	if (map.m_nArrMap[this->m_core.X][this->m_core.Y] == Ȫˮ)
	{
		this->m_state = ������;
	}
	//���з�̹��
	for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
	{
		if (pEnemyTank[i].m_isAlive == false) continue;
		switch (this->m_dir)
		{
		case UP:
			if (
				(this->m_core.X == pEnemyTank[i].m_core.X) && (this->m_core.Y - pEnemyTank[i].m_core.Y == 0) ||
				(this->m_core.X == pEnemyTank[i].m_body[0].X) && (this->m_core.Y - pEnemyTank[i].m_body[0].Y == 0) ||
				(this->m_core.X == pEnemyTank[i].m_body[1].X) && (this->m_core.Y - pEnemyTank[i].m_body[1].Y == 0) ||
				(this->m_core.X == pEnemyTank[i].m_body[2].X) && (this->m_core.Y - pEnemyTank[i].m_body[2].Y == 0) ||
				(this->m_core.X == pEnemyTank[i].m_body[3].X) && (this->m_core.Y - pEnemyTank[i].m_body[3].Y == 0) ||
				(this->m_core.X == pEnemyTank[i].m_body[4].X) && (this->m_core.Y - pEnemyTank[i].m_body[4].Y == 0)
				)
			{
				PlaySound(TEXT("conf/duang.wav"), NULL, SND_FILENAME | SND_ASYNC);//������Ч
				this->m_state = ������;
				pEnemyTank[i].m_blood--;
				if (pEnemyTank[i].m_blood == 0)//��Ѫ��Ϊ0������
					pEnemyTank[i].m_isAlive = false;
				if (!pEnemyTank[i].m_isAlive && (ENEMY_TANK_AMOUNT - GetLiveEnemyAmount(pEnemyTank)) % 3 == 0)//ÿ������������ֵ+1
					(tank.m_blood)++;//Ҫ��!penemytank[i].isAlive��Ҫ���򵽶������ĵ�̹Ҳ����
			}
			break;
		case DOWN:
			if (
				(this->m_core.X == pEnemyTank[i].m_core.X) && (this->m_core.Y - pEnemyTank[i].m_core.Y == 0) ||
				(this->m_core.X == pEnemyTank[i].m_body[0].X) && (this->m_core.Y - pEnemyTank[i].m_body[0].Y == 0) ||
				(this->m_core.X == pEnemyTank[i].m_body[1].X) && (this->m_core.Y - pEnemyTank[i].m_body[1].Y == 0) ||
				(this->m_core.X == pEnemyTank[i].m_body[2].X) && (this->m_core.Y - pEnemyTank[i].m_body[2].Y == 0) ||
				(this->m_core.X == pEnemyTank[i].m_body[3].X) && (this->m_core.Y - pEnemyTank[i].m_body[3].Y == 0) ||
				(this->m_core.X == pEnemyTank[i].m_body[4].X) && (this->m_core.Y - pEnemyTank[i].m_body[4].Y == 0)
				)
			{
				PlaySound(TEXT("conf/duang.wav"), NULL, SND_FILENAME | SND_ASYNC);//������Ч
				this->m_state = ������;
				pEnemyTank[i].m_blood--;
				if (pEnemyTank[i].m_blood == 0)//��Ѫ��Ϊ0������
					pEnemyTank[i].m_isAlive = false;
				if (!pEnemyTank[i].m_isAlive && (ENEMY_TANK_AMOUNT - GetLiveEnemyAmount(pEnemyTank)) % 3 == 0)//ÿ������������ֵ+1
					(tank.m_blood)++;
			}
			break;
		case LEFT:
			if (
				(this->m_core.X == pEnemyTank[i].m_core.X) && (this->m_core.Y - pEnemyTank[i].m_core.Y == 0) ||
				(this->m_core.X == pEnemyTank[i].m_body[0].X) && (this->m_core.Y - pEnemyTank[i].m_body[0].Y == 0) ||
				(this->m_core.X == pEnemyTank[i].m_body[1].X) && (this->m_core.Y - pEnemyTank[i].m_body[1].Y == 0) ||
				(this->m_core.X == pEnemyTank[i].m_body[2].X) && (this->m_core.Y - pEnemyTank[i].m_body[2].Y == 0) ||
				(this->m_core.X == pEnemyTank[i].m_body[3].X) && (this->m_core.Y - pEnemyTank[i].m_body[3].Y == 0) ||
				(this->m_core.X == pEnemyTank[i].m_body[4].X) && (this->m_core.Y - pEnemyTank[i].m_body[4].Y == 0)
				)
			{
				PlaySound(TEXT("conf/duang.wav"), NULL, SND_FILENAME | SND_ASYNC);//������Ч
				this->m_state = ������;
				pEnemyTank[i].m_blood--;
				if (pEnemyTank[i].m_blood == 0)//��Ѫ��Ϊ0������
					pEnemyTank[i].m_isAlive = false;
				if (!pEnemyTank[i].m_isAlive && (ENEMY_TANK_AMOUNT - GetLiveEnemyAmount(pEnemyTank)) % 3 == 0)//ÿ������������ֵ+1
					(tank.m_blood)++;
			}
			break;
		case RIGHT:
			if (
				(this->m_core.X == pEnemyTank[i].m_core.X) && (this->m_core.Y - pEnemyTank[i].m_core.Y == 0) ||
				(this->m_core.X == pEnemyTank[i].m_body[0].X) && (this->m_core.Y - pEnemyTank[i].m_body[0].Y == 0) ||
				(this->m_core.X == pEnemyTank[i].m_body[1].X) && (this->m_core.Y - pEnemyTank[i].m_body[1].Y == 0) ||
				(this->m_core.X == pEnemyTank[i].m_body[2].X) && (this->m_core.Y - pEnemyTank[i].m_body[2].Y == 0) ||
				(this->m_core.X == pEnemyTank[i].m_body[3].X) && (this->m_core.Y - pEnemyTank[i].m_body[3].Y == 0) ||
				(this->m_core.X == pEnemyTank[i].m_body[4].X) && (this->m_core.Y - pEnemyTank[i].m_body[4].Y == 0)
				)
			{
				PlaySound(TEXT("conf/duang.wav"), NULL, SND_FILENAME | SND_ASYNC);//������Ч
				this->m_state = ������;
				pEnemyTank[i].m_blood--;
				if (pEnemyTank[i].m_blood == 0)//��Ѫ��Ϊ0������
					pEnemyTank[i].m_isAlive = false;
				if (!pEnemyTank[i].m_isAlive && (ENEMY_TANK_AMOUNT - GetLiveEnemyAmount(pEnemyTank)) % 3 == 0)//ÿ������������ֵ+1
					(tank.m_blood)++;
			}
			break;
		default:
			break;
		}
	}
	//���ҷ�����
	for (int i = 0; i < MY_TANK_AMOUNT; i++)
	{
		if (pMyTank[i].m_isAlive == false) continue;
		switch (this->m_dir)
		{
		case UP:
			if (
				(this->m_core.X == pMyTank[i].m_core.X) && (this->m_core.Y - pMyTank[i].m_core.Y == 0) ||
				(this->m_core.X == pMyTank[i].m_body[0].X) && (this->m_core.Y - pMyTank[i].m_body[0].Y == 0) ||
				(this->m_core.X == pMyTank[i].m_body[1].X) && (this->m_core.Y - pMyTank[i].m_body[1].Y == 0) ||
				(this->m_core.X == pMyTank[i].m_body[2].X) && (this->m_core.Y - pMyTank[i].m_body[2].Y == 0) ||
				(this->m_core.X == pMyTank[i].m_body[3].X) && (this->m_core.Y - pMyTank[i].m_body[3].Y == 0) ||
				(this->m_core.X == pMyTank[i].m_body[4].X) && (this->m_core.Y - pMyTank[i].m_body[4].Y == 0)
				)
			{
				this->m_state = ������;
			}
			break;
		case DOWN:
			if (
				(this->m_core.X == pMyTank[i].m_core.X) && (this->m_core.Y - pMyTank[i].m_core.Y == 0) ||
				(this->m_core.X == pMyTank[i].m_body[0].X) && (this->m_core.Y - pMyTank[i].m_body[0].Y == 0) ||
				(this->m_core.X == pMyTank[i].m_body[1].X) && (this->m_core.Y - pMyTank[i].m_body[1].Y == 0) ||
				(this->m_core.X == pMyTank[i].m_body[2].X) && (this->m_core.Y - pMyTank[i].m_body[2].Y == 0) ||
				(this->m_core.X == pMyTank[i].m_body[3].X) && (this->m_core.Y - pMyTank[i].m_body[3].Y == 0) ||
				(this->m_core.X == pMyTank[i].m_body[4].X) && (this->m_core.Y - pMyTank[i].m_body[4].Y == 0)
				)
			{
				this->m_state = ������;
			}
			break;
		case LEFT:
			if (
				(this->m_core.X == pMyTank[i].m_core.X) && (this->m_core.Y - pMyTank[i].m_core.Y == 0) ||
				(this->m_core.X == pMyTank[i].m_body[0].X) && (this->m_core.Y - pMyTank[i].m_body[0].Y == 0) ||
				(this->m_core.X == pMyTank[i].m_body[1].X) && (this->m_core.Y - pMyTank[i].m_body[1].Y == 0) ||
				(this->m_core.X == pMyTank[i].m_body[2].X) && (this->m_core.Y - pMyTank[i].m_body[2].Y == 0) ||
				(this->m_core.X == pMyTank[i].m_body[3].X) && (this->m_core.Y - pMyTank[i].m_body[3].Y == 0) ||
				(this->m_core.X == pMyTank[i].m_body[4].X) && (this->m_core.Y - pMyTank[i].m_body[4].Y == 0)
				)
			{
				this->m_state = ������;
			}
			break;
		case RIGHT:
			if (
				(this->m_core.X == pMyTank[i].m_core.X) && (this->m_core.Y - pMyTank[i].m_core.Y == 0) ||
				(this->m_core.X == pMyTank[i].m_body[0].X) && (this->m_core.Y - pMyTank[i].m_body[0].Y == 0) ||
				(this->m_core.X == pMyTank[i].m_body[1].X) && (this->m_core.Y - pMyTank[i].m_body[1].Y == 0) ||
				(this->m_core.X == pMyTank[i].m_body[2].X) && (this->m_core.Y - pMyTank[i].m_body[2].Y == 0) ||
				(this->m_core.X == pMyTank[i].m_body[3].X) && (this->m_core.Y - pMyTank[i].m_body[3].Y == 0) ||
				(this->m_core.X == pMyTank[i].m_body[4].X) && (this->m_core.Y - pMyTank[i].m_body[4].Y == 0)
				)
			{
				this->m_state = ������;
			}
			break;
		default:
			break;
		}
	}
}
void CBullet::IsEneBulMeetOther(CTank *pMyTank, CTank* pEnemyTank, CMap& map)
{
	//���߽�
	if (this->m_core.X <= 0 ||
		this->m_core.X >= MAP_X_WALL / 2 ||
		this->m_core.Y <= 0 ||
		this->m_core.Y >= MAP_Y - 1)
	{
		this->m_state = ������;
	}
	//�������ϰ�
	if (map.m_nArrMap[this->m_core.X][this->m_core.Y] == ����)
	{
		this->m_state = ������;
		map.m_nArrMap[this->m_core.X][this->m_core.Y] = �յ�;
	}
	//��ʯ���ϰ�
	if (map.m_nArrMap[this->m_core.X][this->m_core.Y] == ʯ��)
	{
		this->m_state = ������;
	}
	//��Ȫˮ
	if (map.m_nArrMap[this->m_core.X][this->m_core.Y] == Ȫˮ)
	{
		this->m_state = ������;
		pMyTank[0].m_blood = 0;//Ȫˮ�򵽣��ҷ�̹�˵���ȥ��
		pMyTank[1].m_blood = 0;//Ȫˮ�򵽣��ҷ�̹�˵���ȥ��
	}
	//�����ҷ�̹��
	for (int i = 0; i < MY_TANK_AMOUNT; i++)
	{
		switch (this->m_dir)
		{
		case UP:
			if (
				(this->m_core.X == pMyTank[i].m_core.X) && (this->m_core.Y - pMyTank[i].m_core.Y == 0) ||
				(this->m_core.X == pMyTank[i].m_body[0].X) && (this->m_core.Y - pMyTank[i].m_body[0].Y == 0) ||
				(this->m_core.X == pMyTank[i].m_body[1].X) && (this->m_core.Y - pMyTank[i].m_body[1].Y == 0) ||
				(this->m_core.X == pMyTank[i].m_body[2].X) && (this->m_core.Y - pMyTank[i].m_body[2].Y == 0) ||
				(this->m_core.X == pMyTank[i].m_body[3].X) && (this->m_core.Y - pMyTank[i].m_body[3].Y == 0) ||
				(this->m_core.X == pMyTank[i].m_body[4].X) && (this->m_core.Y - pMyTank[i].m_body[4].Y == 0)
				)
			{
				PlaySound(TEXT("conf/duang.wav"), NULL, SND_FILENAME | SND_ASYNC);//������Ч
				this->m_state = ������;
				(pMyTank[i].m_blood)--;
				if (pMyTank[i].m_blood == 0)//�����Ѫ��Ϊ0
					pMyTank[i].m_isAlive = false;//����Ϊ����
			}
			break;
		case DOWN:
			if (
				(this->m_core.X == pMyTank[i].m_core.X) && (this->m_core.Y - pMyTank[i].m_core.Y == 0) ||
				(this->m_core.X == pMyTank[i].m_body[0].X) && (this->m_core.Y - pMyTank[i].m_body[0].Y == 0) ||
				(this->m_core.X == pMyTank[i].m_body[1].X) && (this->m_core.Y - pMyTank[i].m_body[1].Y == 0) ||
				(this->m_core.X == pMyTank[i].m_body[2].X) && (this->m_core.Y - pMyTank[i].m_body[2].Y == 0) ||
				(this->m_core.X == pMyTank[i].m_body[3].X) && (this->m_core.Y - pMyTank[i].m_body[3].Y == 0) ||
				(this->m_core.X == pMyTank[i].m_body[4].X) && (this->m_core.Y - pMyTank[i].m_body[4].Y == 0)
				)
			{
				PlaySound(TEXT("conf/duang.wav"), NULL, SND_FILENAME | SND_ASYNC);//������Ч
				this->m_state = ������;
				(pMyTank[i].m_blood)--;
				if (pMyTank[i].m_blood == 0)//�����Ѫ��Ϊ0
					pMyTank[i].m_isAlive = false;//����Ϊ����
			}
			break;
		case LEFT:
			if (
				(this->m_core.X == pMyTank[i].m_core.X) && (this->m_core.Y - pMyTank[i].m_core.Y == 0) ||
				(this->m_core.X == pMyTank[i].m_body[0].X) && (this->m_core.Y - pMyTank[i].m_body[0].Y == 0) ||
				(this->m_core.X == pMyTank[i].m_body[1].X) && (this->m_core.Y - pMyTank[i].m_body[1].Y == 0) ||
				(this->m_core.X == pMyTank[i].m_body[2].X) && (this->m_core.Y - pMyTank[i].m_body[2].Y == 0) ||
				(this->m_core.X == pMyTank[i].m_body[3].X) && (this->m_core.Y - pMyTank[i].m_body[3].Y == 0) ||
				(this->m_core.X == pMyTank[i].m_body[4].X) && (this->m_core.Y - pMyTank[i].m_body[4].Y == 0)
				)
			{
				PlaySound(TEXT("conf/duang.wav"), NULL, SND_FILENAME | SND_ASYNC);//������Ч
				this->m_state = ������;
				(pMyTank[i].m_blood)--;
				if (pMyTank[i].m_blood == 0)//�����Ѫ��Ϊ0
					pMyTank[i].m_isAlive = false;//����Ϊ����
			}
			break;
		case RIGHT:
			if (
				(this->m_core.X == pMyTank[i].m_core.X) && (this->m_core.Y - pMyTank[i].m_core.Y == 0) ||
				(this->m_core.X == pMyTank[i].m_body[0].X) && (this->m_core.Y - pMyTank[i].m_body[0].Y == 0) ||
				(this->m_core.X == pMyTank[i].m_body[1].X) && (this->m_core.Y - pMyTank[i].m_body[1].Y == 0) ||
				(this->m_core.X == pMyTank[i].m_body[2].X) && (this->m_core.Y - pMyTank[i].m_body[2].Y == 0) ||
				(this->m_core.X == pMyTank[i].m_body[3].X) && (this->m_core.Y - pMyTank[i].m_body[3].Y == 0) ||
				(this->m_core.X == pMyTank[i].m_body[4].X) && (this->m_core.Y - pMyTank[i].m_body[4].Y == 0)
				)
			{
				PlaySound(TEXT("conf/duang.wav"), NULL, SND_FILENAME | SND_ASYNC);//������Ч
				this->m_state = ������;
				(pMyTank[i].m_blood)--;
				if (pMyTank[i].m_blood == 0)//�����Ѫ��Ϊ0
					pMyTank[i].m_isAlive = false;//����Ϊ����
			}
			break;
		default:
			break;
		}
	}
	//�������з�̹��
	for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
	{
		if (pEnemyTank[i].m_isAlive == false) continue;
		switch (this->m_dir)
		{
		case UP:
			if (
				(this->m_core.X == pEnemyTank[i].m_core.X) && (this->m_core.Y - pEnemyTank[i].m_core.Y == 0) ||
				(this->m_core.X == pEnemyTank[i].m_body[0].X) && (this->m_core.Y - pEnemyTank[i].m_body[0].Y == 0) ||
				(this->m_core.X == pEnemyTank[i].m_body[1].X) && (this->m_core.Y - pEnemyTank[i].m_body[1].Y == 0) ||
				(this->m_core.X == pEnemyTank[i].m_body[2].X) && (this->m_core.Y - pEnemyTank[i].m_body[2].Y == 0) ||
				(this->m_core.X == pEnemyTank[i].m_body[3].X) && (this->m_core.Y - pEnemyTank[i].m_body[3].Y == 0) ||
				(this->m_core.X == pEnemyTank[i].m_body[4].X) && (this->m_core.Y - pEnemyTank[i].m_body[4].Y == 0)
				)
			{
				this->m_state = ������;
			}
			break;
		case DOWN:
			if (
				(this->m_core.X == pEnemyTank[i].m_core.X) && (this->m_core.Y - pEnemyTank[i].m_core.Y == 0) ||
				(this->m_core.X == pEnemyTank[i].m_body[0].X) && (this->m_core.Y - pEnemyTank[i].m_body[0].Y == 0) ||
				(this->m_core.X == pEnemyTank[i].m_body[1].X) && (this->m_core.Y - pEnemyTank[i].m_body[1].Y == 0) ||
				(this->m_core.X == pEnemyTank[i].m_body[2].X) && (this->m_core.Y - pEnemyTank[i].m_body[2].Y == 0) ||
				(this->m_core.X == pEnemyTank[i].m_body[3].X) && (this->m_core.Y - pEnemyTank[i].m_body[3].Y == 0) ||
				(this->m_core.X == pEnemyTank[i].m_body[4].X) && (this->m_core.Y - pEnemyTank[i].m_body[4].Y == 0)
				)
			{
				this->m_state = ������;
			}
			break;
		case LEFT:
			if (
				(this->m_core.X == pEnemyTank[i].m_core.X) && (this->m_core.Y - pEnemyTank[i].m_core.Y == 0) ||
				(this->m_core.X == pEnemyTank[i].m_body[0].X) && (this->m_core.Y - pEnemyTank[i].m_body[0].Y == 0) ||
				(this->m_core.X == pEnemyTank[i].m_body[1].X) && (this->m_core.Y - pEnemyTank[i].m_body[1].Y == 0) ||
				(this->m_core.X == pEnemyTank[i].m_body[2].X) && (this->m_core.Y - pEnemyTank[i].m_body[2].Y == 0) ||
				(this->m_core.X == pEnemyTank[i].m_body[3].X) && (this->m_core.Y - pEnemyTank[i].m_body[3].Y == 0) ||
				(this->m_core.X == pEnemyTank[i].m_body[4].X) && (this->m_core.Y - pEnemyTank[i].m_body[4].Y == 0)
				)
			{
				this->m_state = ������;
			}
			break;
		case RIGHT:
			if (
				(this->m_core.X == pEnemyTank[i].m_core.X) && (this->m_core.Y - pEnemyTank[i].m_core.Y == 0) ||
				(this->m_core.X == pEnemyTank[i].m_body[0].X) && (this->m_core.Y - pEnemyTank[i].m_body[0].Y == 0) ||
				(this->m_core.X == pEnemyTank[i].m_body[1].X) && (this->m_core.Y - pEnemyTank[i].m_body[1].Y == 0) ||
				(this->m_core.X == pEnemyTank[i].m_body[2].X) && (this->m_core.Y - pEnemyTank[i].m_body[2].Y == 0) ||
				(this->m_core.X == pEnemyTank[i].m_body[3].X) && (this->m_core.Y - pEnemyTank[i].m_body[3].Y == 0) ||
				(this->m_core.X == pEnemyTank[i].m_body[4].X) && (this->m_core.Y - pEnemyTank[i].m_body[4].Y == 0)
				)
			{
				this->m_state = ������;
			}
			break;
		default:
			break;
		}
	}
}
void CBullet::DrawBullet(CTank tank, CMap map)
{
	//�����߽磬���ɱ߽����ɫ��ʵ���ӵ���ʧ��Ч��
	if (this->m_core.X <= 0 ||
		this->m_core.X >= MAP_X_WALL / 2 ||
		this->m_core.Y <= 0 ||
		this->m_core.Y >= MAP_Y - 1)
	{
		setColor(7, 0);
	}
	else
	{
		if (tank.m_who != �з�̹��)
			setColor(10, 0);
		else
			setColor(11, 0);
	}
	//�����ϰ������ӵ���Ϊ�ո�ʵ���ӵ���ʧ
	if (map.m_nArrMap[this->m_core.X][this->m_core.Y] == ����)
	{
		GotoxyAndPrint(this->m_core.X, this->m_core.Y, "  ");
	}
	//����ʯ���ϰ����ʵ���ӵ���ʧ��Ч��
	else if (map.m_nArrMap[this->m_core.X][this->m_core.Y] == ʯ��)
	{
		setColor(7, 0);
	}
	//����Ȫˮ�����ӵ���������ɫ����״��ʵ���ӵ���ʧ
	else if (map.m_nArrMap[this->m_core.X][this->m_core.Y] == Ȫˮ)
	{
		setColor(12, 0);
		GotoxyAndPrint(this->m_core.X, this->m_core.Y, "��");
	}
	//һ���˶�״̬
	else
	{
		GotoxyAndPrint(this->m_core.X, this->m_core.Y, "��");
	}
	setColor(7, 0);
}