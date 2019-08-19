#include <Windows.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include "Data.h"
#include "Func.h"
#include "Tank.h"
#include "Bullet.h"

void CBullet::SetBullet(COORD cor, enum direction di)
{
	core = cor;
	dir = di;
}
void CBullet::MoveBullet()
{
	switch (this->dir)
	{
	case UP:
		this->core.Y--;
		break;
	case DOWN:
		this->core.Y++;
		break;
	case LEFT:
		this->core.X--;
		break;
	case RIGHT:
		this->core.X++;
		break;
	default:
		break;
	}
}
void CBullet::CleanBullet(COORD oldBulCore)
{
	GotoxyAndPrint(oldBulCore.X, oldBulCore.Y, "  ");
	//printf("  ");
}
void CBullet::IsMyBulMeetOther(CTank tank, CTank* penemytank, CMap& map)
{
	//���߽�
	if (this->core.X <= 0 ||
		this->core.X >= MAP_X_WALL / 2 ||
		this->core.Y <= 0 ||
		this->core.Y >= MAP_Y - 1)
	{
		this->state = ������;
	}
	//�������ϰ�
	if (map.m_nArrMap[this->core.X][this->core.Y] == �����ϰ�)
	{
		this->state = ������;
		map.m_nArrMap[this->core.X][this->core.Y] = �յ�;
	}
	//��ʯ���ϰ�
	if (map.m_nArrMap[this->core.X][this->core.Y] == ʯ���ϰ�)
	{
		this->state = ������;
	}
	//��Ȫˮ
	if (map.m_nArrMap[this->core.X][this->core.Y] == �Ҽ�Ȫˮ)
	{
		this->state = ������;
	}
	//���з�̹��
	for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
	{
		if (penemytank[i].isAlive == false) continue;
		switch (this->dir)
		{
		case UP:
			if (
				(this->core.X == penemytank[i].core.X) && (this->core.Y - penemytank[i].core.Y == 0) ||
				(this->core.X == penemytank[i].body[0].X) && (this->core.Y - penemytank[i].body[0].Y == 0) ||
				(this->core.X == penemytank[i].body[1].X) && (this->core.Y - penemytank[i].body[1].Y == 0) ||
				(this->core.X == penemytank[i].body[2].X) && (this->core.Y - penemytank[i].body[2].Y == 0) ||
				(this->core.X == penemytank[i].body[3].X) && (this->core.Y - penemytank[i].body[3].Y == 0) ||
				(this->core.X == penemytank[i].body[4].X) && (this->core.Y - penemytank[i].body[4].Y == 0)
				)
			{
				PlaySound(TEXT("conf/duang.wav"), NULL, SND_FILENAME | SND_ASYNC);//������Ч
				this->state = ������;
				penemytank[i].blood--;
				if (penemytank[i].blood == 0)//��Ѫ��Ϊ0������
					penemytank[i].isAlive = false;
				if (!penemytank[i].isAlive && (ENEMY_TANK_AMOUNT - GetLiveEnemyAmount(penemytank)) % 3 == 0)//ÿ������������ֵ+1
					(tank.blood)++;//Ҫ��!penemytank[i].isAlive��Ҫ���򵽶������ĵ�̹Ҳ����
			}
			break;
		case DOWN:
			if (
				(this->core.X == penemytank[i].core.X) && (this->core.Y - penemytank[i].core.Y == 0) ||
				(this->core.X == penemytank[i].body[0].X) && (this->core.Y - penemytank[i].body[0].Y == 0) ||
				(this->core.X == penemytank[i].body[1].X) && (this->core.Y - penemytank[i].body[1].Y == 0) ||
				(this->core.X == penemytank[i].body[2].X) && (this->core.Y - penemytank[i].body[2].Y == 0) ||
				(this->core.X == penemytank[i].body[3].X) && (this->core.Y - penemytank[i].body[3].Y == 0) ||
				(this->core.X == penemytank[i].body[4].X) && (this->core.Y - penemytank[i].body[4].Y == 0)
				)
			{
				PlaySound(TEXT("conf/duang.wav"), NULL, SND_FILENAME | SND_ASYNC);//������Ч
				this->state = ������;
				penemytank[i].blood--;
				if (penemytank[i].blood == 0)//��Ѫ��Ϊ0������
					penemytank[i].isAlive = false;
				if (!penemytank[i].isAlive && (ENEMY_TANK_AMOUNT - GetLiveEnemyAmount(penemytank)) % 3 == 0)//ÿ������������ֵ+1
					(tank.blood)++;
			}
			break;
		case LEFT:
			if (
				(this->core.X == penemytank[i].core.X) && (this->core.Y - penemytank[i].core.Y == 0) ||
				(this->core.X == penemytank[i].body[0].X) && (this->core.Y - penemytank[i].body[0].Y == 0) ||
				(this->core.X == penemytank[i].body[1].X) && (this->core.Y - penemytank[i].body[1].Y == 0) ||
				(this->core.X == penemytank[i].body[2].X) && (this->core.Y - penemytank[i].body[2].Y == 0) ||
				(this->core.X == penemytank[i].body[3].X) && (this->core.Y - penemytank[i].body[3].Y == 0) ||
				(this->core.X == penemytank[i].body[4].X) && (this->core.Y - penemytank[i].body[4].Y == 0)
				)
			{
				PlaySound(TEXT("conf/duang.wav"), NULL, SND_FILENAME | SND_ASYNC);//������Ч
				this->state = ������;
				penemytank[i].blood--;
				if (penemytank[i].blood == 0)//��Ѫ��Ϊ0������
					penemytank[i].isAlive = false;
				if (!penemytank[i].isAlive && (ENEMY_TANK_AMOUNT - GetLiveEnemyAmount(penemytank)) % 3 == 0)//ÿ������������ֵ+1
					(tank.blood)++;
			}
			break;
		case RIGHT:
			if (
				(this->core.X == penemytank[i].core.X) && (this->core.Y - penemytank[i].core.Y == 0) ||
				(this->core.X == penemytank[i].body[0].X) && (this->core.Y - penemytank[i].body[0].Y == 0) ||
				(this->core.X == penemytank[i].body[1].X) && (this->core.Y - penemytank[i].body[1].Y == 0) ||
				(this->core.X == penemytank[i].body[2].X) && (this->core.Y - penemytank[i].body[2].Y == 0) ||
				(this->core.X == penemytank[i].body[3].X) && (this->core.Y - penemytank[i].body[3].Y == 0) ||
				(this->core.X == penemytank[i].body[4].X) && (this->core.Y - penemytank[i].body[4].Y == 0)
				)
			{
				PlaySound(TEXT("conf/duang.wav"), NULL, SND_FILENAME | SND_ASYNC);//������Ч
				this->state = ������;
				penemytank[i].blood--;
				if (penemytank[i].blood == 0)//��Ѫ��Ϊ0������
					penemytank[i].isAlive = false;
				if (!penemytank[i].isAlive && (ENEMY_TANK_AMOUNT - GetLiveEnemyAmount(penemytank)) % 3 == 0)//ÿ������������ֵ+1
					(tank.blood)++;
			}
			break;
		default:
			break;
		}
	}
}
void CBullet::IsEneBulMeetOther(CTank tank, CTank* penemytank, CMap& map)
{
	//���߽�
	if (this->core.X <= 0 ||
		this->core.X >= MAP_X_WALL / 2 ||
		this->core.Y <= 0 ||
		this->core.Y >= MAP_Y - 1)
	{
		this->state = ������;
	}
	//�������ϰ�
	if (map.m_nArrMap[this->core.X][this->core.Y] == �����ϰ�)
	{
		this->state = ������;
		map.m_nArrMap[this->core.X][this->core.Y] = �յ�;
	}
	//��ʯ���ϰ�
	if (map.m_nArrMap[this->core.X][this->core.Y] == ʯ���ϰ�)
	{
		this->state = ������;
	}
	//��Ȫˮ
	if (map.m_nArrMap[this->core.X][this->core.Y] == �Ҽ�Ȫˮ)
	{
		this->state = ������;
		tank.blood = 0;//Ȫˮ�򵽣��ҷ�̹�˵���ȥ��
	}
	//�����ҷ�̹��
	switch (this->dir)
	{
	case UP:
		if (
			(this->core.X == tank.core.X) && (this->core.Y - tank.core.Y == 0) ||
			(this->core.X == tank.body[0].X) && (this->core.Y - tank.body[0].Y == 0) ||
			(this->core.X == tank.body[1].X) && (this->core.Y - tank.body[1].Y == 0) ||
			(this->core.X == tank.body[2].X) && (this->core.Y - tank.body[2].Y == 0) ||
			(this->core.X == tank.body[3].X) && (this->core.Y - tank.body[3].Y == 0) ||
			(this->core.X == tank.body[4].X) && (this->core.Y - tank.body[4].Y == 0)
			)
		{
			PlaySound(TEXT("conf/duang.wav"), NULL, SND_FILENAME | SND_ASYNC);//������Ч
			this->state = ������;
			(tank.blood)--;
			if (tank.blood == 0)//�����Ѫ��Ϊ0
				tank.isAlive = false;//����Ϊ����
		}
		break;
	case DOWN:
		if (
			(this->core.X == tank.core.X) && (this->core.Y - tank.core.Y == 0) ||
			(this->core.X == tank.body[0].X) && (this->core.Y - tank.body[0].Y == 0) ||
			(this->core.X == tank.body[1].X) && (this->core.Y - tank.body[1].Y == 0) ||
			(this->core.X == tank.body[2].X) && (this->core.Y - tank.body[2].Y == 0) ||
			(this->core.X == tank.body[3].X) && (this->core.Y - tank.body[3].Y == 0) ||
			(this->core.X == tank.body[4].X) && (this->core.Y - tank.body[4].Y == 0)
			)
		{
			PlaySound(TEXT("conf/duang.wav"), NULL, SND_FILENAME | SND_ASYNC);//������Ч
			this->state = ������;
			(tank.blood)--;
			if (tank.blood == 0)//�����Ѫ��Ϊ0
				tank.isAlive = false;//����Ϊ����
		}
		break;
	case LEFT:
		if (
			(this->core.X == tank.core.X) && (this->core.Y - tank.core.Y == 0) ||
			(this->core.X == tank.body[0].X) && (this->core.Y - tank.body[0].Y == 0) ||
			(this->core.X == tank.body[1].X) && (this->core.Y - tank.body[1].Y == 0) ||
			(this->core.X == tank.body[2].X) && (this->core.Y - tank.body[2].Y == 0) ||
			(this->core.X == tank.body[3].X) && (this->core.Y - tank.body[3].Y == 0) ||
			(this->core.X == tank.body[4].X) && (this->core.Y - tank.body[4].Y == 0)
			)
		{
			PlaySound(TEXT("conf/duang.wav"), NULL, SND_FILENAME | SND_ASYNC);//������Ч
			this->state = ������;
			(tank.blood)--;
			if (tank.blood == 0)//�����Ѫ��Ϊ0
				tank.isAlive = false;//����Ϊ����
		}
		break;
	case RIGHT:
		if (
			(this->core.X == tank.core.X) && (this->core.Y - tank.core.Y == 0) ||
			(this->core.X == tank.body[0].X) && (this->core.Y - tank.body[0].Y == 0) ||
			(this->core.X == tank.body[1].X) && (this->core.Y - tank.body[1].Y == 0) ||
			(this->core.X == tank.body[2].X) && (this->core.Y - tank.body[2].Y == 0) ||
			(this->core.X == tank.body[3].X) && (this->core.Y - tank.body[3].Y == 0) ||
			(this->core.X == tank.body[4].X) && (this->core.Y - tank.body[4].Y == 0)
			)
		{
			PlaySound(TEXT("conf/duang.wav"), NULL, SND_FILENAME | SND_ASYNC);//������Ч
			this->state = ������;
			(tank.blood)--;
			if (tank.blood == 0)//�����Ѫ��Ϊ0
				tank.isAlive = false;//����Ϊ����
		}
		break;
	default:
		break;
	}
	//�������з�̹��
	for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
	{
		if (penemytank[i].isAlive == false) continue;
		switch (this->dir)
		{
		case UP:
			if (
				(this->core.X == penemytank[i].core.X) && (this->core.Y - penemytank[i].core.Y == 0) ||
				(this->core.X == penemytank[i].body[0].X) && (this->core.Y - penemytank[i].body[0].Y == 0) ||
				(this->core.X == penemytank[i].body[1].X) && (this->core.Y - penemytank[i].body[1].Y == 0) ||
				(this->core.X == penemytank[i].body[2].X) && (this->core.Y - penemytank[i].body[2].Y == 0) ||
				(this->core.X == penemytank[i].body[3].X) && (this->core.Y - penemytank[i].body[3].Y == 0) ||
				(this->core.X == penemytank[i].body[4].X) && (this->core.Y - penemytank[i].body[4].Y == 0)
				)
			{
				this->state = ������;
			}
			break;
		case DOWN:
			if (
				(this->core.X == penemytank[i].core.X) && (this->core.Y - penemytank[i].core.Y == 0) ||
				(this->core.X == penemytank[i].body[0].X) && (this->core.Y - penemytank[i].body[0].Y == 0) ||
				(this->core.X == penemytank[i].body[1].X) && (this->core.Y - penemytank[i].body[1].Y == 0) ||
				(this->core.X == penemytank[i].body[2].X) && (this->core.Y - penemytank[i].body[2].Y == 0) ||
				(this->core.X == penemytank[i].body[3].X) && (this->core.Y - penemytank[i].body[3].Y == 0) ||
				(this->core.X == penemytank[i].body[4].X) && (this->core.Y - penemytank[i].body[4].Y == 0)
				)
			{
				this->state = ������;
			}
			break;
		case LEFT:
			if (
				(this->core.X == penemytank[i].core.X) && (this->core.Y - penemytank[i].core.Y == 0) ||
				(this->core.X == penemytank[i].body[0].X) && (this->core.Y - penemytank[i].body[0].Y == 0) ||
				(this->core.X == penemytank[i].body[1].X) && (this->core.Y - penemytank[i].body[1].Y == 0) ||
				(this->core.X == penemytank[i].body[2].X) && (this->core.Y - penemytank[i].body[2].Y == 0) ||
				(this->core.X == penemytank[i].body[3].X) && (this->core.Y - penemytank[i].body[3].Y == 0) ||
				(this->core.X == penemytank[i].body[4].X) && (this->core.Y - penemytank[i].body[4].Y == 0)
				)
			{
				this->state = ������;
			}
			break;
		case RIGHT:
			if (
				(this->core.X == penemytank[i].core.X) && (this->core.Y - penemytank[i].core.Y == 0) ||
				(this->core.X == penemytank[i].body[0].X) && (this->core.Y - penemytank[i].body[0].Y == 0) ||
				(this->core.X == penemytank[i].body[1].X) && (this->core.Y - penemytank[i].body[1].Y == 0) ||
				(this->core.X == penemytank[i].body[2].X) && (this->core.Y - penemytank[i].body[2].Y == 0) ||
				(this->core.X == penemytank[i].body[3].X) && (this->core.Y - penemytank[i].body[3].Y == 0) ||
				(this->core.X == penemytank[i].body[4].X) && (this->core.Y - penemytank[i].body[4].Y == 0)
				)
			{
				this->state = ������;
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
	if (this->core.X <= 0 ||
		this->core.X >= MAP_X_WALL / 2 ||
		this->core.Y <= 0 ||
		this->core.Y >= MAP_Y - 1)
	{
		setColor(7, 0);
	}
	else
	{
		if (tank.m_who == �ҷ�̹��)
			setColor(10, 0);
		else if (tank.m_who == �з�̹��)
			setColor(11, 0);
	}
	//�����ϰ������ӵ���Ϊ�ո�ʵ���ӵ���ʧ
	if (map.m_nArrMap[this->core.X][this->core.Y] == �����ϰ�)
	{
		GotoxyAndPrint(this->core.X, this->core.Y, "  ");
	}
	//����ʯ���ϰ����ʵ���ӵ���ʧ��Ч��
	else if (map.m_nArrMap[this->core.X][this->core.Y] == ʯ���ϰ�)
	{
		setColor(7, 0);
	}
	//����Ȫˮ�����ӵ���������ɫ����״��ʵ���ӵ���ʧ
	else if (map.m_nArrMap[this->core.X][this->core.Y] == �Ҽ�Ȫˮ)
	{
		setColor(12, 0);
		GotoxyAndPrint(this->core.X, this->core.Y, "��");
	}
	//һ���˶�״̬
	else
	{
		GotoxyAndPrint(this->core.X, this->core.Y, "��");
	}
	setColor(7, 0);
}