#include "Bullet.h"
#include "Tank.h"
#include "Map.h"
#pragma comment(lib,"winmm.lib")

CBullet::CBullet()
{
	m_core = { 0,0 };
	m_dir = UP;
	m_state = 不存在;
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
void CBullet::IsMyBulMeetOther(CTank tank, CTank* penemytank, CMap& map)
{
	//遇边界
	if (this->m_core.X <= 0 ||
		this->m_core.X >= MAP_X_WALL / 2 ||
		this->m_core.Y <= 0 ||
		this->m_core.Y >= MAP_Y - 1)
	{
		this->m_state = 不存在;
	}
	//遇土块障碍
	if (map.m_nArrMap[this->m_core.X][this->m_core.Y] == 土块障碍)
	{
		this->m_state = 不存在;
		map.m_nArrMap[this->m_core.X][this->m_core.Y] = 空地;
	}
	//遇石块障碍
	if (map.m_nArrMap[this->m_core.X][this->m_core.Y] == 石块障碍)
	{
		this->m_state = 不存在;
	}
	//遇泉水
	if (map.m_nArrMap[this->m_core.X][this->m_core.Y] == 我家泉水)
	{
		this->m_state = 不存在;
	}
	//遇敌方坦克
	for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
	{
		if (penemytank[i].m_isAlive == false) continue;
		switch (this->m_dir)
		{
		case UP:
			if (
				(this->m_core.X == penemytank[i].m_core.X) && (this->m_core.Y - penemytank[i].m_core.Y == 0) ||
				(this->m_core.X == penemytank[i].m_body[0].X) && (this->m_core.Y - penemytank[i].m_body[0].Y == 0) ||
				(this->m_core.X == penemytank[i].m_body[1].X) && (this->m_core.Y - penemytank[i].m_body[1].Y == 0) ||
				(this->m_core.X == penemytank[i].m_body[2].X) && (this->m_core.Y - penemytank[i].m_body[2].Y == 0) ||
				(this->m_core.X == penemytank[i].m_body[3].X) && (this->m_core.Y - penemytank[i].m_body[3].Y == 0) ||
				(this->m_core.X == penemytank[i].m_body[4].X) && (this->m_core.Y - penemytank[i].m_body[4].Y == 0)
				)
			{
				PlaySound(TEXT("conf/duang.wav"), NULL, SND_FILENAME | SND_ASYNC);//播放音效
				this->m_state = 不存在;
				penemytank[i].m_blood--;
				if (penemytank[i].m_blood == 0)//减血后为0则死亡
					penemytank[i].m_isAlive = false;
				if (!penemytank[i].m_isAlive && (ENEMY_TANK_AMOUNT - GetLiveEnemyAmount(penemytank)) % 3 == 0)//每打死三个生命值+1
					(tank.m_blood)++;//要加!penemytank[i].isAlive，要不打到多条命的敌坦也加命
			}
			break;
		case DOWN:
			if (
				(this->m_core.X == penemytank[i].m_core.X) && (this->m_core.Y - penemytank[i].m_core.Y == 0) ||
				(this->m_core.X == penemytank[i].m_body[0].X) && (this->m_core.Y - penemytank[i].m_body[0].Y == 0) ||
				(this->m_core.X == penemytank[i].m_body[1].X) && (this->m_core.Y - penemytank[i].m_body[1].Y == 0) ||
				(this->m_core.X == penemytank[i].m_body[2].X) && (this->m_core.Y - penemytank[i].m_body[2].Y == 0) ||
				(this->m_core.X == penemytank[i].m_body[3].X) && (this->m_core.Y - penemytank[i].m_body[3].Y == 0) ||
				(this->m_core.X == penemytank[i].m_body[4].X) && (this->m_core.Y - penemytank[i].m_body[4].Y == 0)
				)
			{
				PlaySound(TEXT("conf/duang.wav"), NULL, SND_FILENAME | SND_ASYNC);//播放音效
				this->m_state = 不存在;
				penemytank[i].m_blood--;
				if (penemytank[i].m_blood == 0)//减血后为0则死亡
					penemytank[i].m_isAlive = false;
				if (!penemytank[i].m_isAlive && (ENEMY_TANK_AMOUNT - GetLiveEnemyAmount(penemytank)) % 3 == 0)//每打死三个生命值+1
					(tank.m_blood)++;
			}
			break;
		case LEFT:
			if (
				(this->m_core.X == penemytank[i].m_core.X) && (this->m_core.Y - penemytank[i].m_core.Y == 0) ||
				(this->m_core.X == penemytank[i].m_body[0].X) && (this->m_core.Y - penemytank[i].m_body[0].Y == 0) ||
				(this->m_core.X == penemytank[i].m_body[1].X) && (this->m_core.Y - penemytank[i].m_body[1].Y == 0) ||
				(this->m_core.X == penemytank[i].m_body[2].X) && (this->m_core.Y - penemytank[i].m_body[2].Y == 0) ||
				(this->m_core.X == penemytank[i].m_body[3].X) && (this->m_core.Y - penemytank[i].m_body[3].Y == 0) ||
				(this->m_core.X == penemytank[i].m_body[4].X) && (this->m_core.Y - penemytank[i].m_body[4].Y == 0)
				)
			{
				PlaySound(TEXT("conf/duang.wav"), NULL, SND_FILENAME | SND_ASYNC);//播放音效
				this->m_state = 不存在;
				penemytank[i].m_blood--;
				if (penemytank[i].m_blood == 0)//减血后为0则死亡
					penemytank[i].m_isAlive = false;
				if (!penemytank[i].m_isAlive && (ENEMY_TANK_AMOUNT - GetLiveEnemyAmount(penemytank)) % 3 == 0)//每打死三个生命值+1
					(tank.m_blood)++;
			}
			break;
		case RIGHT:
			if (
				(this->m_core.X == penemytank[i].m_core.X) && (this->m_core.Y - penemytank[i].m_core.Y == 0) ||
				(this->m_core.X == penemytank[i].m_body[0].X) && (this->m_core.Y - penemytank[i].m_body[0].Y == 0) ||
				(this->m_core.X == penemytank[i].m_body[1].X) && (this->m_core.Y - penemytank[i].m_body[1].Y == 0) ||
				(this->m_core.X == penemytank[i].m_body[2].X) && (this->m_core.Y - penemytank[i].m_body[2].Y == 0) ||
				(this->m_core.X == penemytank[i].m_body[3].X) && (this->m_core.Y - penemytank[i].m_body[3].Y == 0) ||
				(this->m_core.X == penemytank[i].m_body[4].X) && (this->m_core.Y - penemytank[i].m_body[4].Y == 0)
				)
			{
				PlaySound(TEXT("conf/duang.wav"), NULL, SND_FILENAME | SND_ASYNC);//播放音效
				this->m_state = 不存在;
				penemytank[i].m_blood--;
				if (penemytank[i].m_blood == 0)//减血后为0则死亡
					penemytank[i].m_isAlive = false;
				if (!penemytank[i].m_isAlive && (ENEMY_TANK_AMOUNT - GetLiveEnemyAmount(penemytank)) % 3 == 0)//每打死三个生命值+1
					(tank.m_blood)++;
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
	if (this->m_core.X <= 0 ||
		this->m_core.X >= MAP_X_WALL / 2 ||
		this->m_core.Y <= 0 ||
		this->m_core.Y >= MAP_Y - 1)
	{
		this->m_state = 不存在;
	}
	//遇土块障碍
	if (map.m_nArrMap[this->m_core.X][this->m_core.Y] == 土块障碍)
	{
		this->m_state = 不存在;
		map.m_nArrMap[this->m_core.X][this->m_core.Y] = 空地;
	}
	//遇石块障碍
	if (map.m_nArrMap[this->m_core.X][this->m_core.Y] == 石块障碍)
	{
		this->m_state = 不存在;
	}
	//遇泉水
	if (map.m_nArrMap[this->m_core.X][this->m_core.Y] == 我家泉水)
	{
		this->m_state = 不存在;
		tank.m_blood = 0;//泉水打到，我方坦克当场去世
	}
	//遇到我方坦克
	switch (this->m_dir)
	{
	case UP:
		if (
			(this->m_core.X == tank.m_core.X) && (this->m_core.Y - tank.m_core.Y == 0) ||
			(this->m_core.X == tank.m_body[0].X) && (this->m_core.Y - tank.m_body[0].Y == 0) ||
			(this->m_core.X == tank.m_body[1].X) && (this->m_core.Y - tank.m_body[1].Y == 0) ||
			(this->m_core.X == tank.m_body[2].X) && (this->m_core.Y - tank.m_body[2].Y == 0) ||
			(this->m_core.X == tank.m_body[3].X) && (this->m_core.Y - tank.m_body[3].Y == 0) ||
			(this->m_core.X == tank.m_body[4].X) && (this->m_core.Y - tank.m_body[4].Y == 0)
			)
		{
			PlaySound(TEXT("conf/duang.wav"), NULL, SND_FILENAME | SND_ASYNC);//播放音效
			this->m_state = 不存在;
			(tank.m_blood)--;
			if (tank.m_blood == 0)//如果减血后为0
				tank.m_isAlive = false;//声明为死亡
		}
		break;
	case DOWN:
		if (
			(this->m_core.X == tank.m_core.X) && (this->m_core.Y - tank.m_core.Y == 0) ||
			(this->m_core.X == tank.m_body[0].X) && (this->m_core.Y - tank.m_body[0].Y == 0) ||
			(this->m_core.X == tank.m_body[1].X) && (this->m_core.Y - tank.m_body[1].Y == 0) ||
			(this->m_core.X == tank.m_body[2].X) && (this->m_core.Y - tank.m_body[2].Y == 0) ||
			(this->m_core.X == tank.m_body[3].X) && (this->m_core.Y - tank.m_body[3].Y == 0) ||
			(this->m_core.X == tank.m_body[4].X) && (this->m_core.Y - tank.m_body[4].Y == 0)
			)
		{
			PlaySound(TEXT("conf/duang.wav"), NULL, SND_FILENAME | SND_ASYNC);//播放音效
			this->m_state = 不存在;
			(tank.m_blood)--;
			if (tank.m_blood == 0)//如果减血后为0
				tank.m_isAlive = false;//声明为死亡
		}
		break;
	case LEFT:
		if (
			(this->m_core.X == tank.m_core.X) && (this->m_core.Y - tank.m_core.Y == 0) ||
			(this->m_core.X == tank.m_body[0].X) && (this->m_core.Y - tank.m_body[0].Y == 0) ||
			(this->m_core.X == tank.m_body[1].X) && (this->m_core.Y - tank.m_body[1].Y == 0) ||
			(this->m_core.X == tank.m_body[2].X) && (this->m_core.Y - tank.m_body[2].Y == 0) ||
			(this->m_core.X == tank.m_body[3].X) && (this->m_core.Y - tank.m_body[3].Y == 0) ||
			(this->m_core.X == tank.m_body[4].X) && (this->m_core.Y - tank.m_body[4].Y == 0)
			)
		{
			PlaySound(TEXT("conf/duang.wav"), NULL, SND_FILENAME | SND_ASYNC);//播放音效
			this->m_state = 不存在;
			(tank.m_blood)--;
			if (tank.m_blood == 0)//如果减血后为0
				tank.m_isAlive = false;//声明为死亡
		}
		break;
	case RIGHT:
		if (
			(this->m_core.X == tank.m_core.X) && (this->m_core.Y - tank.m_core.Y == 0) ||
			(this->m_core.X == tank.m_body[0].X) && (this->m_core.Y - tank.m_body[0].Y == 0) ||
			(this->m_core.X == tank.m_body[1].X) && (this->m_core.Y - tank.m_body[1].Y == 0) ||
			(this->m_core.X == tank.m_body[2].X) && (this->m_core.Y - tank.m_body[2].Y == 0) ||
			(this->m_core.X == tank.m_body[3].X) && (this->m_core.Y - tank.m_body[3].Y == 0) ||
			(this->m_core.X == tank.m_body[4].X) && (this->m_core.Y - tank.m_body[4].Y == 0)
			)
		{
			PlaySound(TEXT("conf/duang.wav"), NULL, SND_FILENAME | SND_ASYNC);//播放音效
			this->m_state = 不存在;
			(tank.m_blood)--;
			if (tank.m_blood == 0)//如果减血后为0
				tank.m_isAlive = false;//声明为死亡
		}
		break;
	default:
		break;
	}
	//遇其他敌方坦克
	for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
	{
		if (penemytank[i].m_isAlive == false) continue;
		switch (this->m_dir)
		{
		case UP:
			if (
				(this->m_core.X == penemytank[i].m_core.X) && (this->m_core.Y - penemytank[i].m_core.Y == 0) ||
				(this->m_core.X == penemytank[i].m_body[0].X) && (this->m_core.Y - penemytank[i].m_body[0].Y == 0) ||
				(this->m_core.X == penemytank[i].m_body[1].X) && (this->m_core.Y - penemytank[i].m_body[1].Y == 0) ||
				(this->m_core.X == penemytank[i].m_body[2].X) && (this->m_core.Y - penemytank[i].m_body[2].Y == 0) ||
				(this->m_core.X == penemytank[i].m_body[3].X) && (this->m_core.Y - penemytank[i].m_body[3].Y == 0) ||
				(this->m_core.X == penemytank[i].m_body[4].X) && (this->m_core.Y - penemytank[i].m_body[4].Y == 0)
				)
			{
				this->m_state = 不存在;
			}
			break;
		case DOWN:
			if (
				(this->m_core.X == penemytank[i].m_core.X) && (this->m_core.Y - penemytank[i].m_core.Y == 0) ||
				(this->m_core.X == penemytank[i].m_body[0].X) && (this->m_core.Y - penemytank[i].m_body[0].Y == 0) ||
				(this->m_core.X == penemytank[i].m_body[1].X) && (this->m_core.Y - penemytank[i].m_body[1].Y == 0) ||
				(this->m_core.X == penemytank[i].m_body[2].X) && (this->m_core.Y - penemytank[i].m_body[2].Y == 0) ||
				(this->m_core.X == penemytank[i].m_body[3].X) && (this->m_core.Y - penemytank[i].m_body[3].Y == 0) ||
				(this->m_core.X == penemytank[i].m_body[4].X) && (this->m_core.Y - penemytank[i].m_body[4].Y == 0)
				)
			{
				this->m_state = 不存在;
			}
			break;
		case LEFT:
			if (
				(this->m_core.X == penemytank[i].m_core.X) && (this->m_core.Y - penemytank[i].m_core.Y == 0) ||
				(this->m_core.X == penemytank[i].m_body[0].X) && (this->m_core.Y - penemytank[i].m_body[0].Y == 0) ||
				(this->m_core.X == penemytank[i].m_body[1].X) && (this->m_core.Y - penemytank[i].m_body[1].Y == 0) ||
				(this->m_core.X == penemytank[i].m_body[2].X) && (this->m_core.Y - penemytank[i].m_body[2].Y == 0) ||
				(this->m_core.X == penemytank[i].m_body[3].X) && (this->m_core.Y - penemytank[i].m_body[3].Y == 0) ||
				(this->m_core.X == penemytank[i].m_body[4].X) && (this->m_core.Y - penemytank[i].m_body[4].Y == 0)
				)
			{
				this->m_state = 不存在;
			}
			break;
		case RIGHT:
			if (
				(this->m_core.X == penemytank[i].m_core.X) && (this->m_core.Y - penemytank[i].m_core.Y == 0) ||
				(this->m_core.X == penemytank[i].m_body[0].X) && (this->m_core.Y - penemytank[i].m_body[0].Y == 0) ||
				(this->m_core.X == penemytank[i].m_body[1].X) && (this->m_core.Y - penemytank[i].m_body[1].Y == 0) ||
				(this->m_core.X == penemytank[i].m_body[2].X) && (this->m_core.Y - penemytank[i].m_body[2].Y == 0) ||
				(this->m_core.X == penemytank[i].m_body[3].X) && (this->m_core.Y - penemytank[i].m_body[3].Y == 0) ||
				(this->m_core.X == penemytank[i].m_body[4].X) && (this->m_core.Y - penemytank[i].m_body[4].Y == 0)
				)
			{
				this->m_state = 不存在;
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
	if (this->m_core.X <= 0 ||
		this->m_core.X >= MAP_X_WALL / 2 ||
		this->m_core.Y <= 0 ||
		this->m_core.Y >= MAP_Y - 1)
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
	if (map.m_nArrMap[this->m_core.X][this->m_core.Y] == 土块障碍)
	{
		GotoxyAndPrint(this->m_core.X, this->m_core.Y, "  ");
	}
	//碰到石块障碍物，，实现子弹消失的效果
	else if (map.m_nArrMap[this->m_core.X][this->m_core.Y] == 石块障碍)
	{
		setColor(7, 0);
	}
	//碰到泉水，将子弹换成其颜色和形状，实现子弹消失
	else if (map.m_nArrMap[this->m_core.X][this->m_core.Y] == 我家泉水)
	{
		setColor(12, 0);
		GotoxyAndPrint(this->m_core.X, this->m_core.Y, "★");
	}
	//一般运动状态
	else
	{
		GotoxyAndPrint(this->m_core.X, this->m_core.Y, "■");
	}
	setColor(7, 0);
}