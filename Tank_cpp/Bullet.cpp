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

//子弹相关
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
	//遇边界
	if (pbullet->core.X <= 0 ||
		pbullet->core.X >= MAP_X_WALL / 2 ||
		pbullet->core.Y <= 0 ||
		pbullet->core.Y >= MAP_Y - 1)
	{
		pbullet->state = 不存在;
	}
	//遇土块障碍
	if (g_MAP[pbullet->core.X][pbullet->core.Y] == 土块障碍)
	{
		pbullet->state = 不存在;
		g_MAP[pbullet->core.X][pbullet->core.Y] = 空地;
	}
	//遇石块障碍
	if (g_MAP[pbullet->core.X][pbullet->core.Y] == 石块障碍)
	{
		pbullet->state = 不存在;
	}
	//遇泉水
	if (g_MAP[pbullet->core.X][pbullet->core.Y] == 我家泉水)
	{
		pbullet->state = 不存在;
	}
	//遇敌方坦克
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
				PlaySound(TEXT("conf/duang.wav"), NULL, SND_FILENAME | SND_ASYNC);//播放音效
				pbullet->state = 不存在;
				penemytank[i].blood--;
				if (penemytank[i].blood == 0)//减血后为0则死亡
					penemytank[i].isAlive = false;
				if (!penemytank[i].isAlive && (ENEMY_TANK_AMOUNT - GetLiveEnemyAmount(penemytank)) % 3 == 0)//每打死三个生命值+1
					(ptank->blood)++;//要加!penemytank[i].isAlive，要不打到多条命的敌坦也加命
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
				PlaySound(TEXT("conf/duang.wav"), NULL, SND_FILENAME | SND_ASYNC);//播放音效
				pbullet->state = 不存在;
				penemytank[i].blood--;
				if (penemytank[i].blood == 0)//减血后为0则死亡
					penemytank[i].isAlive = false;
				if (!penemytank[i].isAlive && (ENEMY_TANK_AMOUNT - GetLiveEnemyAmount(penemytank)) % 3 == 0)//每打死三个生命值+1
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
				PlaySound(TEXT("conf/duang.wav"), NULL, SND_FILENAME | SND_ASYNC);//播放音效
				pbullet->state = 不存在;
				penemytank[i].blood--;
				if (penemytank[i].blood == 0)//减血后为0则死亡
					penemytank[i].isAlive = false;
				if (!penemytank[i].isAlive && (ENEMY_TANK_AMOUNT - GetLiveEnemyAmount(penemytank)) % 3 == 0)//每打死三个生命值+1
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
				PlaySound(TEXT("conf/duang.wav"), NULL, SND_FILENAME | SND_ASYNC);//播放音效
				pbullet->state = 不存在;
				penemytank[i].blood--;
				if (penemytank[i].blood == 0)//减血后为0则死亡
					penemytank[i].isAlive = false;
				if (!penemytank[i].isAlive && (ENEMY_TANK_AMOUNT - GetLiveEnemyAmount(penemytank)) % 3 == 0)//每打死三个生命值+1
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
	//遇边界
	if (pbullet->core.X <= 0 ||
		pbullet->core.X >= MAP_X_WALL / 2 ||
		pbullet->core.Y <= 0 ||
		pbullet->core.Y >= MAP_Y - 1)
	{
		pbullet->state = 不存在;
	}
	//遇土块障碍
	if (g_MAP[pbullet->core.X][pbullet->core.Y] == 土块障碍)
	{
		pbullet->state = 不存在;
		g_MAP[pbullet->core.X][pbullet->core.Y] = 空地;
	}
	//遇石块障碍
	if (g_MAP[pbullet->core.X][pbullet->core.Y] == 石块障碍)
	{
		pbullet->state = 不存在;
	}
	//遇泉水
	if (g_MAP[pbullet->core.X][pbullet->core.Y] == 我家泉水)
	{
		pbullet->state = 不存在;
		ptank->blood = 0;//泉水打到，我方坦克当场去世
	}
	//遇到我方坦克
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
			PlaySound(TEXT("conf/duang.wav"), NULL, SND_FILENAME | SND_ASYNC);//播放音效
			pbullet->state = 不存在;
			(ptank->blood)--;
			if (ptank->blood == 0)//如果减血后为0
				ptank->isAlive = false;//声明为死亡
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
			PlaySound(TEXT("conf/duang.wav"), NULL, SND_FILENAME | SND_ASYNC);//播放音效
			pbullet->state = 不存在;
			(ptank->blood)--;
			if (ptank->blood == 0)//如果减血后为0
				ptank->isAlive = false;//声明为死亡
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
			PlaySound(TEXT("conf/duang.wav"), NULL, SND_FILENAME | SND_ASYNC);//播放音效
			pbullet->state = 不存在;
			(ptank->blood)--;
			if (ptank->blood == 0)//如果减血后为0
				ptank->isAlive = false;//声明为死亡
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
			PlaySound(TEXT("conf/duang.wav"), NULL, SND_FILENAME | SND_ASYNC);//播放音效
			pbullet->state = 不存在;
			(ptank->blood)--;
			if (ptank->blood == 0)//如果减血后为0
				ptank->isAlive = false;//声明为死亡
		}
		break;
	default:
		break;
	}
	//遇其他敌方坦克
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
				pbullet->state = 不存在;
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
				pbullet->state = 不存在;
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
				pbullet->state = 不存在;
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
				pbullet->state = 不存在;
			}
			break;
		default:
			break;
		}
	}
}