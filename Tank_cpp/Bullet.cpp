#include <Windows.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include "Data.h"
#include "Func.h"
#include "Bullet.h"
#include "Tank.h"

//�ӵ����
void CBullet::MoveBullet(PBULLET pbullet)
{
	switch (pbullet->dir)
	{
	case UP:
		pbullet->core.Y--;
		break;
	case DOWN:
		pbullet->core.Y++;
		break;
	case LEFT:
		pbullet->core.X--;
		break;
	case RIGHT:
		pbullet->core.X++;
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
void CBullet::IsMyBulMeetOther(PBULLET pbullet, PTANK penemytank, PTANK ptank)
{
	//���߽�
	if (pbullet->core.X <= 0 ||
		pbullet->core.X >= MAP_X_WALL / 2 ||
		pbullet->core.Y <= 0 ||
		pbullet->core.Y >= MAP_Y - 1)
	{
		pbullet->state = ������;
	}
	//�������ϰ�
	if (g_MAP[pbullet->core.X][pbullet->core.Y] == �����ϰ�)
	{
		pbullet->state = ������;
		g_MAP[pbullet->core.X][pbullet->core.Y] = �յ�;
	}
	//��ʯ���ϰ�
	if (g_MAP[pbullet->core.X][pbullet->core.Y] == ʯ���ϰ�)
	{
		pbullet->state = ������;
	}
	//��Ȫˮ
	if (g_MAP[pbullet->core.X][pbullet->core.Y] == �Ҽ�Ȫˮ)
	{
		pbullet->state = ������;
	}
	//���з�̹��
	for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
	{
		if (penemytank[i].isAlive == false) continue;
		switch (pbullet->dir)
		{
		case UP:
			if (
				(pbullet->core.X == penemytank[i].core.X) && (pbullet->core.Y - penemytank[i].core.Y == 0) ||
				(pbullet->core.X == penemytank[i].body[0].X) && (pbullet->core.Y - penemytank[i].body[0].Y == 0) ||
				(pbullet->core.X == penemytank[i].body[1].X) && (pbullet->core.Y - penemytank[i].body[1].Y == 0) ||
				(pbullet->core.X == penemytank[i].body[2].X) && (pbullet->core.Y - penemytank[i].body[2].Y == 0) ||
				(pbullet->core.X == penemytank[i].body[3].X) && (pbullet->core.Y - penemytank[i].body[3].Y == 0) ||
				(pbullet->core.X == penemytank[i].body[4].X) && (pbullet->core.Y - penemytank[i].body[4].Y == 0)
				)
			{
				PlaySound(TEXT("conf/duang.wav"), NULL, SND_FILENAME | SND_ASYNC);//������Ч
				pbullet->state = ������;
				penemytank[i].blood--;
				if (penemytank[i].blood == 0)//��Ѫ��Ϊ0������
					penemytank[i].isAlive = false;
				if (!penemytank[i].isAlive && (ENEMY_TANK_AMOUNT - GetLiveEnemyAmount(penemytank)) % 3 == 0)//ÿ������������ֵ+1
					(ptank->blood)++;//Ҫ��!penemytank[i].isAlive��Ҫ���򵽶������ĵ�̹Ҳ����
			}
			break;
		case DOWN:
			if (
				(pbullet->core.X == penemytank[i].core.X) && (pbullet->core.Y - penemytank[i].core.Y == 0) ||
				(pbullet->core.X == penemytank[i].body[0].X) && (pbullet->core.Y - penemytank[i].body[0].Y == 0) ||
				(pbullet->core.X == penemytank[i].body[1].X) && (pbullet->core.Y - penemytank[i].body[1].Y == 0) ||
				(pbullet->core.X == penemytank[i].body[2].X) && (pbullet->core.Y - penemytank[i].body[2].Y == 0) ||
				(pbullet->core.X == penemytank[i].body[3].X) && (pbullet->core.Y - penemytank[i].body[3].Y == 0) ||
				(pbullet->core.X == penemytank[i].body[4].X) && (pbullet->core.Y - penemytank[i].body[4].Y == 0)
				)
			{
				PlaySound(TEXT("conf/duang.wav"), NULL, SND_FILENAME | SND_ASYNC);//������Ч
				pbullet->state = ������;
				penemytank[i].blood--;
				if (penemytank[i].blood == 0)//��Ѫ��Ϊ0������
					penemytank[i].isAlive = false;
				if (!penemytank[i].isAlive && (ENEMY_TANK_AMOUNT - GetLiveEnemyAmount(penemytank)) % 3 == 0)//ÿ������������ֵ+1
					(ptank->blood)++;
			}
			break;
		case LEFT:
			if (
				(pbullet->core.X == penemytank[i].core.X) && (pbullet->core.Y - penemytank[i].core.Y == 0) ||
				(pbullet->core.X == penemytank[i].body[0].X) && (pbullet->core.Y - penemytank[i].body[0].Y == 0) ||
				(pbullet->core.X == penemytank[i].body[1].X) && (pbullet->core.Y - penemytank[i].body[1].Y == 0) ||
				(pbullet->core.X == penemytank[i].body[2].X) && (pbullet->core.Y - penemytank[i].body[2].Y == 0) ||
				(pbullet->core.X == penemytank[i].body[3].X) && (pbullet->core.Y - penemytank[i].body[3].Y == 0) ||
				(pbullet->core.X == penemytank[i].body[4].X) && (pbullet->core.Y - penemytank[i].body[4].Y == 0)
				)
			{
				PlaySound(TEXT("conf/duang.wav"), NULL, SND_FILENAME | SND_ASYNC);//������Ч
				pbullet->state = ������;
				penemytank[i].blood--;
				if (penemytank[i].blood == 0)//��Ѫ��Ϊ0������
					penemytank[i].isAlive = false;
				if (!penemytank[i].isAlive && (ENEMY_TANK_AMOUNT - GetLiveEnemyAmount(penemytank)) % 3 == 0)//ÿ������������ֵ+1
					(ptank->blood)++;
			}
			break;
		case RIGHT:
			if (
				(pbullet->core.X == penemytank[i].core.X) && (pbullet->core.Y - penemytank[i].core.Y == 0) ||
				(pbullet->core.X == penemytank[i].body[0].X) && (pbullet->core.Y - penemytank[i].body[0].Y == 0) ||
				(pbullet->core.X == penemytank[i].body[1].X) && (pbullet->core.Y - penemytank[i].body[1].Y == 0) ||
				(pbullet->core.X == penemytank[i].body[2].X) && (pbullet->core.Y - penemytank[i].body[2].Y == 0) ||
				(pbullet->core.X == penemytank[i].body[3].X) && (pbullet->core.Y - penemytank[i].body[3].Y == 0) ||
				(pbullet->core.X == penemytank[i].body[4].X) && (pbullet->core.Y - penemytank[i].body[4].Y == 0)
				)
			{
				PlaySound(TEXT("conf/duang.wav"), NULL, SND_FILENAME | SND_ASYNC);//������Ч
				pbullet->state = ������;
				penemytank[i].blood--;
				if (penemytank[i].blood == 0)//��Ѫ��Ϊ0������
					penemytank[i].isAlive = false;
				if (!penemytank[i].isAlive && (ENEMY_TANK_AMOUNT - GetLiveEnemyAmount(penemytank)) % 3 == 0)//ÿ������������ֵ+1
					(ptank->blood)++;
			}
			break;
		default:
			break;
		}
	}
}
void CBullet::IsEneBulMeetOther(PBULLET pbullet, PTANK penemytank, PTANK ptank)
{
	//���߽�
	if (pbullet->core.X <= 0 ||
		pbullet->core.X >= MAP_X_WALL / 2 ||
		pbullet->core.Y <= 0 ||
		pbullet->core.Y >= MAP_Y - 1)
	{
		pbullet->state = ������;
	}
	//�������ϰ�
	if (g_MAP[pbullet->core.X][pbullet->core.Y] == �����ϰ�)
	{
		pbullet->state = ������;
		g_MAP[pbullet->core.X][pbullet->core.Y] = �յ�;
	}
	//��ʯ���ϰ�
	if (g_MAP[pbullet->core.X][pbullet->core.Y] == ʯ���ϰ�)
	{
		pbullet->state = ������;
	}
	//��Ȫˮ
	if (g_MAP[pbullet->core.X][pbullet->core.Y] == �Ҽ�Ȫˮ)
	{
		pbullet->state = ������;
		ptank->blood = 0;//Ȫˮ�򵽣��ҷ�̹�˵���ȥ��
	}
	//�����ҷ�̹��
	switch (pbullet->dir)
	{
	case UP:
		if (
			(pbullet->core.X == ptank->core.X) && (pbullet->core.Y - ptank->core.Y == 0) ||
			(pbullet->core.X == ptank->body[0].X) && (pbullet->core.Y - ptank->body[0].Y == 0) ||
			(pbullet->core.X == ptank->body[1].X) && (pbullet->core.Y - ptank->body[1].Y == 0) ||
			(pbullet->core.X == ptank->body[2].X) && (pbullet->core.Y - ptank->body[2].Y == 0) ||
			(pbullet->core.X == ptank->body[3].X) && (pbullet->core.Y - ptank->body[3].Y == 0) ||
			(pbullet->core.X == ptank->body[4].X) && (pbullet->core.Y - ptank->body[4].Y == 0)
			)
		{
			PlaySound(TEXT("conf/duang.wav"), NULL, SND_FILENAME | SND_ASYNC);//������Ч
			pbullet->state = ������;
			(ptank->blood)--;
			if (ptank->blood == 0)//�����Ѫ��Ϊ0
				ptank->isAlive = false;//����Ϊ����
		}
		break;
	case DOWN:
		if (
			(pbullet->core.X == ptank->core.X) && (pbullet->core.Y - ptank->core.Y == 0) ||
			(pbullet->core.X == ptank->body[0].X) && (pbullet->core.Y - ptank->body[0].Y == 0) ||
			(pbullet->core.X == ptank->body[1].X) && (pbullet->core.Y - ptank->body[1].Y == 0) ||
			(pbullet->core.X == ptank->body[2].X) && (pbullet->core.Y - ptank->body[2].Y == 0) ||
			(pbullet->core.X == ptank->body[3].X) && (pbullet->core.Y - ptank->body[3].Y == 0) ||
			(pbullet->core.X == ptank->body[4].X) && (pbullet->core.Y - ptank->body[4].Y == 0)
			)
		{
			PlaySound(TEXT("conf/duang.wav"), NULL, SND_FILENAME | SND_ASYNC);//������Ч
			pbullet->state = ������;
			(ptank->blood)--;
			if (ptank->blood == 0)//�����Ѫ��Ϊ0
				ptank->isAlive = false;//����Ϊ����
		}
		break;
	case LEFT:
		if (
			(pbullet->core.X == ptank->core.X) && (pbullet->core.Y - ptank->core.Y == 0) ||
			(pbullet->core.X == ptank->body[0].X) && (pbullet->core.Y - ptank->body[0].Y == 0) ||
			(pbullet->core.X == ptank->body[1].X) && (pbullet->core.Y - ptank->body[1].Y == 0) ||
			(pbullet->core.X == ptank->body[2].X) && (pbullet->core.Y - ptank->body[2].Y == 0) ||
			(pbullet->core.X == ptank->body[3].X) && (pbullet->core.Y - ptank->body[3].Y == 0) ||
			(pbullet->core.X == ptank->body[4].X) && (pbullet->core.Y - ptank->body[4].Y == 0)
			)
		{
			PlaySound(TEXT("conf/duang.wav"), NULL, SND_FILENAME | SND_ASYNC);//������Ч
			pbullet->state = ������;
			(ptank->blood)--;
			if (ptank->blood == 0)//�����Ѫ��Ϊ0
				ptank->isAlive = false;//����Ϊ����
		}
		break;
	case RIGHT:
		if (
			(pbullet->core.X == ptank->core.X) && (pbullet->core.Y - ptank->core.Y == 0) ||
			(pbullet->core.X == ptank->body[0].X) && (pbullet->core.Y - ptank->body[0].Y == 0) ||
			(pbullet->core.X == ptank->body[1].X) && (pbullet->core.Y - ptank->body[1].Y == 0) ||
			(pbullet->core.X == ptank->body[2].X) && (pbullet->core.Y - ptank->body[2].Y == 0) ||
			(pbullet->core.X == ptank->body[3].X) && (pbullet->core.Y - ptank->body[3].Y == 0) ||
			(pbullet->core.X == ptank->body[4].X) && (pbullet->core.Y - ptank->body[4].Y == 0)
			)
		{
			PlaySound(TEXT("conf/duang.wav"), NULL, SND_FILENAME | SND_ASYNC);//������Ч
			pbullet->state = ������;
			(ptank->blood)--;
			if (ptank->blood == 0)//�����Ѫ��Ϊ0
				ptank->isAlive = false;//����Ϊ����
		}
		break;
	default:
		break;
	}
	//�������з�̹��
	for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
	{
		if (penemytank[i].isAlive == false) continue;
		switch (pbullet->dir)
		{
		case UP:
			if (
				(pbullet->core.X == penemytank[i].core.X) && (pbullet->core.Y - penemytank[i].core.Y == 0) ||
				(pbullet->core.X == penemytank[i].body[0].X) && (pbullet->core.Y - penemytank[i].body[0].Y == 0) ||
				(pbullet->core.X == penemytank[i].body[1].X) && (pbullet->core.Y - penemytank[i].body[1].Y == 0) ||
				(pbullet->core.X == penemytank[i].body[2].X) && (pbullet->core.Y - penemytank[i].body[2].Y == 0) ||
				(pbullet->core.X == penemytank[i].body[3].X) && (pbullet->core.Y - penemytank[i].body[3].Y == 0) ||
				(pbullet->core.X == penemytank[i].body[4].X) && (pbullet->core.Y - penemytank[i].body[4].Y == 0)
				)
			{
				pbullet->state = ������;
			}
			break;
		case DOWN:
			if (
				(pbullet->core.X == penemytank[i].core.X) && (pbullet->core.Y - penemytank[i].core.Y == 0) ||
				(pbullet->core.X == penemytank[i].body[0].X) && (pbullet->core.Y - penemytank[i].body[0].Y == 0) ||
				(pbullet->core.X == penemytank[i].body[1].X) && (pbullet->core.Y - penemytank[i].body[1].Y == 0) ||
				(pbullet->core.X == penemytank[i].body[2].X) && (pbullet->core.Y - penemytank[i].body[2].Y == 0) ||
				(pbullet->core.X == penemytank[i].body[3].X) && (pbullet->core.Y - penemytank[i].body[3].Y == 0) ||
				(pbullet->core.X == penemytank[i].body[4].X) && (pbullet->core.Y - penemytank[i].body[4].Y == 0)
				)
			{
				pbullet->state = ������;
			}
			break;
		case LEFT:
			if (
				(pbullet->core.X == penemytank[i].core.X) && (pbullet->core.Y - penemytank[i].core.Y == 0) ||
				(pbullet->core.X == penemytank[i].body[0].X) && (pbullet->core.Y - penemytank[i].body[0].Y == 0) ||
				(pbullet->core.X == penemytank[i].body[1].X) && (pbullet->core.Y - penemytank[i].body[1].Y == 0) ||
				(pbullet->core.X == penemytank[i].body[2].X) && (pbullet->core.Y - penemytank[i].body[2].Y == 0) ||
				(pbullet->core.X == penemytank[i].body[3].X) && (pbullet->core.Y - penemytank[i].body[3].Y == 0) ||
				(pbullet->core.X == penemytank[i].body[4].X) && (pbullet->core.Y - penemytank[i].body[4].Y == 0)
				)
			{
				pbullet->state = ������;
			}
			break;
		case RIGHT:
			if (
				(pbullet->core.X == penemytank[i].core.X) && (pbullet->core.Y - penemytank[i].core.Y == 0) ||
				(pbullet->core.X == penemytank[i].body[0].X) && (pbullet->core.Y - penemytank[i].body[0].Y == 0) ||
				(pbullet->core.X == penemytank[i].body[1].X) && (pbullet->core.Y - penemytank[i].body[1].Y == 0) ||
				(pbullet->core.X == penemytank[i].body[2].X) && (pbullet->core.Y - penemytank[i].body[2].Y == 0) ||
				(pbullet->core.X == penemytank[i].body[3].X) && (pbullet->core.Y - penemytank[i].body[3].Y == 0) ||
				(pbullet->core.X == penemytank[i].body[4].X) && (pbullet->core.Y - penemytank[i].body[4].Y == 0)
				)
			{
				pbullet->state = ������;
			}
			break;
		default:
			break;
		}
	}
}