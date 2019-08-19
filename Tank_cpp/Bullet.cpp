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
	//遇边界
	if (this->core.X <= 0 ||
		this->core.X >= MAP_X_WALL / 2 ||
		this->core.Y <= 0 ||
		this->core.Y >= MAP_Y - 1)
	{
		this->state = 不存在;
	}
	//遇土块障碍
	if (map.m_nArrMap[this->core.X][this->core.Y] == 土块障碍)
	{
		this->state = 不存在;
		map.m_nArrMap[this->core.X][this->core.Y] = 空地;
	}
	//遇石块障碍
	if (map.m_nArrMap[this->core.X][this->core.Y] == 石块障碍)
	{
		this->state = 不存在;
	}
	//遇泉水
	if (map.m_nArrMap[this->core.X][this->core.Y] == 我家泉水)
	{
		this->state = 不存在;
	}
	//遇敌方坦克
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
				PlaySound(TEXT("conf/duang.wav"), NULL, SND_FILENAME | SND_ASYNC);//播放音效
				this->state = 不存在;
				penemytank[i].blood--;
				if (penemytank[i].blood == 0)//减血后为0则死亡
					penemytank[i].isAlive = false;
				if (!penemytank[i].isAlive && (ENEMY_TANK_AMOUNT - GetLiveEnemyAmount(penemytank)) % 3 == 0)//每打死三个生命值+1
					(tank.blood)++;//要加!penemytank[i].isAlive，要不打到多条命的敌坦也加命
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
				PlaySound(TEXT("conf/duang.wav"), NULL, SND_FILENAME | SND_ASYNC);//播放音效
				this->state = 不存在;
				penemytank[i].blood--;
				if (penemytank[i].blood == 0)//减血后为0则死亡
					penemytank[i].isAlive = false;
				if (!penemytank[i].isAlive && (ENEMY_TANK_AMOUNT - GetLiveEnemyAmount(penemytank)) % 3 == 0)//每打死三个生命值+1
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
				PlaySound(TEXT("conf/duang.wav"), NULL, SND_FILENAME | SND_ASYNC);//播放音效
				this->state = 不存在;
				penemytank[i].blood--;
				if (penemytank[i].blood == 0)//减血后为0则死亡
					penemytank[i].isAlive = false;
				if (!penemytank[i].isAlive && (ENEMY_TANK_AMOUNT - GetLiveEnemyAmount(penemytank)) % 3 == 0)//每打死三个生命值+1
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
				PlaySound(TEXT("conf/duang.wav"), NULL, SND_FILENAME | SND_ASYNC);//播放音效
				this->state = 不存在;
				penemytank[i].blood--;
				if (penemytank[i].blood == 0)//减血后为0则死亡
					penemytank[i].isAlive = false;
				if (!penemytank[i].isAlive && (ENEMY_TANK_AMOUNT - GetLiveEnemyAmount(penemytank)) % 3 == 0)//每打死三个生命值+1
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
	//遇边界
	if (this->core.X <= 0 ||
		this->core.X >= MAP_X_WALL / 2 ||
		this->core.Y <= 0 ||
		this->core.Y >= MAP_Y - 1)
	{
		this->state = 不存在;
	}
	//遇土块障碍
	if (map.m_nArrMap[this->core.X][this->core.Y] == 土块障碍)
	{
		this->state = 不存在;
		map.m_nArrMap[this->core.X][this->core.Y] = 空地;
	}
	//遇石块障碍
	if (map.m_nArrMap[this->core.X][this->core.Y] == 石块障碍)
	{
		this->state = 不存在;
	}
	//遇泉水
	if (map.m_nArrMap[this->core.X][this->core.Y] == 我家泉水)
	{
		this->state = 不存在;
		tank.blood = 0;//泉水打到，我方坦克当场去世
	}
	//遇到我方坦克
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
			PlaySound(TEXT("conf/duang.wav"), NULL, SND_FILENAME | SND_ASYNC);//播放音效
			this->state = 不存在;
			(tank.blood)--;
			if (tank.blood == 0)//如果减血后为0
				tank.isAlive = false;//声明为死亡
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
			PlaySound(TEXT("conf/duang.wav"), NULL, SND_FILENAME | SND_ASYNC);//播放音效
			this->state = 不存在;
			(tank.blood)--;
			if (tank.blood == 0)//如果减血后为0
				tank.isAlive = false;//声明为死亡
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
			PlaySound(TEXT("conf/duang.wav"), NULL, SND_FILENAME | SND_ASYNC);//播放音效
			this->state = 不存在;
			(tank.blood)--;
			if (tank.blood == 0)//如果减血后为0
				tank.isAlive = false;//声明为死亡
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
			PlaySound(TEXT("conf/duang.wav"), NULL, SND_FILENAME | SND_ASYNC);//播放音效
			this->state = 不存在;
			(tank.blood)--;
			if (tank.blood == 0)//如果减血后为0
				tank.isAlive = false;//声明为死亡
		}
		break;
	default:
		break;
	}
	//遇其他敌方坦克
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
				this->state = 不存在;
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
				this->state = 不存在;
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
				this->state = 不存在;
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
				this->state = 不存在;
			}
			break;
		default:
			break;
		}
	}
}
void CBullet::DrawBullet(CTank tank, CMap map)
{
	//碰到边界，换成边界的颜色，实现子弹消失的效果
	if (this->core.X <= 0 ||
		this->core.X >= MAP_X_WALL / 2 ||
		this->core.Y <= 0 ||
		this->core.Y >= MAP_Y - 1)
	{
		setColor(7, 0);
	}
	else
	{
		if (tank.m_who == 我方坦克)
			setColor(10, 0);
		else if (tank.m_who == 敌方坦克)
			setColor(11, 0);
	}
	//碰到障碍，将子弹画为空格，实现子弹消失
	if (map.m_nArrMap[this->core.X][this->core.Y] == 土块障碍)
	{
		GotoxyAndPrint(this->core.X, this->core.Y, "  ");
	}
	//碰到石块障碍物，，实现子弹消失的效果
	else if (map.m_nArrMap[this->core.X][this->core.Y] == 石块障碍)
	{
		setColor(7, 0);
	}
	//碰到泉水，将子弹换成其颜色和形状，实现子弹消失
	else if (map.m_nArrMap[this->core.X][this->core.Y] == 我家泉水)
	{
		setColor(12, 0);
		GotoxyAndPrint(this->core.X, this->core.Y, "★");
	}
	//一般运动状态
	else
	{
		GotoxyAndPrint(this->core.X, this->core.Y, "■");
	}
	setColor(7, 0);
}