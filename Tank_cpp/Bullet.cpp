#include "Bullet.h"
#include "Tank.h"
#include "Map.h"
#include "Game.h"
#pragma comment(lib,"winmm.lib")

CBullet::CBullet()
{
	m_core = { 0,0 };
	m_dir = UP;
	m_state = 不存在;
	m_who = -1;
}
void CBullet::SetBullet(CTank tank)
{
	m_core = tank.m_core;
	m_dir = tank.m_dir;
	m_who = tank.m_who;
}
void CBullet::MoveBullet()
{
	// 不存在状态时则不移动
	if (m_state == 不存在) return;

	switch (m_dir)
	{
	case UP:
		m_core.Y--;
		break;
	case DOWN:
		m_core.Y++;
		break;
	case LEFT:
		m_core.X--;
		break;
	case RIGHT:
		m_core.X++;
		break;
	default:
		break;
	}
}
void CBullet::CleanBullet(COORD oldBulCore)
{
	GotoxyAndPrint(oldBulCore.X, oldBulCore.Y, "  ");
}
void CBullet::IsBulMeetOther(CTank &tank, vector<CTank>& myTank, vector<CTank>& enemyTank, CMap& map,CGame &game)
{
	//tank 参数：为了获取奖励值

	//遇边界
	if (m_core.X <= 0 || m_core.X >= MAP_X_WALL / 2 || m_core.Y <= 0 || m_core.Y >= MAP_Y - 1)
	{
		m_state = 不存在;
	}	
	//遇石块
	if (map.m_nArrMap[m_core.X][m_core.Y] == 石块)
	{
		m_state = 不存在;
	}
	//遇土块（遇草丛、河流则穿过
	if (map.m_nArrMap[m_core.X][m_core.Y] == 土块)
	{
		m_state = 不存在;
		map.m_nArrMap[m_core.X][m_core.Y] = 空地;
	}
	//遇子弹
	if (m_who != 敌方坦克)
	{
		//遇泉水
		if (map.m_nArrMap[m_core.X][m_core.Y] == 泉水)
			m_state = 不存在;
		// 遇我方其他
		for (vector<CTank>::iterator it = myTank.begin(); it != myTank.end(); it++)
		{
			// 死坦克不判断
			//if (it->m_isAlive == false) continue;
			// 发出本子弹的坦克不判断（对比body而非core，因为子弹已经向前走了一步；C版本未判断但是正常也许某些实现不一样
			if (m_core.X == it->m_body[0].X && m_core.Y == it->m_body[0].Y) continue;
			if (
				(m_core.X == it->m_core.X) && (m_core.Y == it->m_core.Y) ||
				(m_core.X == it->m_body[0].X) && (m_core.Y == it->m_body[0].Y) ||
				(m_core.X == it->m_body[1].X) && (m_core.Y == it->m_body[1].Y) ||
				(m_core.X == it->m_body[2].X) && (m_core.Y == it->m_body[2].Y) ||
				(m_core.X == it->m_body[3].X) && (m_core.Y == it->m_body[3].Y) ||
				(m_core.X == it->m_body[4].X) && (m_core.Y == it->m_body[4].Y)
				)
			{
				m_state = 不存在;
			}
		}
		// 遇敌方坦克及子弹
		for (vector<CTank>::iterator it = enemyTank.begin(); it != enemyTank.end();it++)
		{
			
			//if (it->m_isAlive == false) continue;// 死坦克不判断
			
			// 遇坦克
			if (
				(m_core.X == it->m_core.X) && (m_core.Y == it->m_core.Y) ||
				(m_core.X == it->m_body[0].X) && (m_core.Y == it->m_body[0].Y) ||
				(m_core.X == it->m_body[1].X) && (m_core.Y == it->m_body[1].Y) ||
				(m_core.X == it->m_body[2].X) && (m_core.Y == it->m_body[2].Y) ||
				(m_core.X == it->m_body[3].X) && (m_core.Y == it->m_body[3].Y) ||
				(m_core.X == it->m_body[4].X) && (m_core.Y == it->m_body[4].Y) 
				)
			{
				PlaySound(TEXT("C:\\Users\\ry1yn\\source\\repos\\15PB\\Tank_cpp\\conf\\duang.wav"), NULL, SND_FILENAME | SND_ASYNC);//播放音效
				m_state = 不存在;
				it->m_blood--;
				//减血后为0则死亡
				if (it->m_blood == 0)
				{
					it->m_isAlive = false;//死亡
					tank.m_killCount++;//杀敌数+1
				}
				// 每打死三个奖励一条生命值
				if (tank.m_killCount == 3)
				{
					tank.m_blood++;
					tank.m_killCount = 0;
				}
			}
			// 遇子弹
			if ((m_core.X == it->m_bullet.m_core.X) && (m_core.Y == it->m_bullet.m_core.Y))
			{
				// 设置子弹状态
				m_state = 不存在;
				it->m_bullet.m_state = 不存在;
				// 抹除子弹
				GotoxyAndPrint(m_core.X, m_core.Y, " ");
				GotoxyAndPrint(it->m_bullet.m_core.X, it->m_bullet.m_core.Y, " ");
				// 破坏相等的条件
				m_core = { 0 };
				it->m_bullet.m_core = { -1 };
			}
		}
	}

	else if (m_who == 敌方坦克)
	{
		//遇泉水
		if (map.m_nArrMap[m_core.X][m_core.Y] == 泉水)
		{
			m_state = 不存在;
			game.m_isOver = 1;
			//myTank[0].m_blood = 0;//泉水打到，我方坦克当场去世
			//myTank[1].m_blood = 0;//泉水打到，我方坦克当场去世
		}
		//遇到我方坦克及子弹
		for (vector<CTank>::iterator it = myTank.begin(); it != myTank.end(); it++)
		{
			
			//if (it->m_isAlive == false) continue;// 死坦克不判断
			
			// 遇到坦克
			if (
				(m_core.X == it->m_core.X) && (m_core.Y == it->m_core.Y) ||
				(m_core.X == it->m_body[0].X) && (m_core.Y == it->m_body[0].Y ) ||
				(m_core.X == it->m_body[1].X) && (m_core.Y == it->m_body[1].Y ) ||
				(m_core.X == it->m_body[2].X) && (m_core.Y == it->m_body[2].Y ) ||
				(m_core.X == it->m_body[3].X) && (m_core.Y == it->m_body[3].Y ) ||
				(m_core.X == it->m_body[4].X) && (m_core.Y == it->m_body[4].Y )
				)
			{
				PlaySound(TEXT("conf/duang.wav"), NULL, SND_FILENAME | SND_ASYNC);//播放音效
				m_state = 不存在;
				// 坦克在隐藏状态被打到不掉血
				if (!it->m_isHided)
				{
					if (tank.m_power == 1)
						it->m_blood--;
					else if (tank.m_power == 2)
						it->m_blood -= 2;
				}
				//如果减血后为0
				if (it->m_blood == 0)
				{
					it->m_isAlive = false;//声明为死亡
				}
					
			}

			// 遇子弹
			if ((m_core.X == it->m_bullet.m_core.X) && (m_core.Y == it->m_bullet.m_core.Y))
			{
				// 设置子弹状态
				m_state = 不存在;
				it->m_bullet.m_state = 不存在;
				// 抹除子弹
				GotoxyAndPrint(m_core.X, m_core.Y, " ");// 抹除其子弹
				GotoxyAndPrint(it->m_bullet.m_core.X, it->m_bullet.m_core.Y, " ");// 抹除其子弹
				// 破坏相等的条件
				m_core = { 0 };
				it->m_bullet.m_core = { -1 };
			}

		}

		//遇其他敌方坦克
		for (vector<CTank>::iterator it = enemyTank.begin(); it != enemyTank.end(); it++)
		{
			// 死坦克不判断
			if (it->m_isAlive == false) continue;
			//发出本子弹的坦克不判断
			if (m_core.X == it->m_body[0].X && m_core.Y == it->m_body[0].Y) continue;

			if (
				(m_core.X == it->m_core.X) && (m_core.Y == it->m_core.Y) ||
				(m_core.X == it->m_body[0].X) && (m_core.Y == it->m_body[0].Y ) ||
				(m_core.X == it->m_body[1].X) && (m_core.Y == it->m_body[1].Y ) ||
				(m_core.X == it->m_body[2].X) && (m_core.Y == it->m_body[2].Y ) ||
				(m_core.X == it->m_body[3].X) && (m_core.Y == it->m_body[3].Y ) ||
				(m_core.X == it->m_body[4].X) && (m_core.Y == it->m_body[4].Y )
				)
			{
				m_state = 不存在;
			}

		}
	}
}
void CBullet::DrawBullet(CMap map)
{
	// 不存在状态时则不画
	if (m_state == 不存在) return;
	//遇边界，更改为其颜色
	if (m_core.X <= 0 ||m_core.X >= MAP_X_WALL / 2 ||m_core.Y <= 0 ||m_core.Y >= MAP_Y - 1)
	{
		GotoxyAndPrint(m_core.X, m_core.Y, "■",默认颜色);
	}
	//遇石块，更改为其颜色
	else if (map.m_nArrMap[m_core.X][m_core.Y] == 石块)
	{
		GotoxyAndPrint(m_core.X, m_core.Y, "■", 石块颜色);
	}
	//遇土块，画为空格（遇草丛、河流则不变
	else if (map.m_nArrMap[m_core.X][m_core.Y] == 土块)
	{
		GotoxyAndPrint(m_core.X, m_core.Y, "  ",默认颜色);
	}
	//碰到泉水，更改为其颜色和形状
	else if (map.m_nArrMap[m_core.X][m_core.Y] == 泉水)
	{
		GotoxyAndPrint(m_core.X, m_core.Y, "★",泉水颜色);
	}
	//一般运动状态
	else
	{
		if (m_who != 敌方坦克)
			GotoxyAndPrint(m_core.X, m_core.Y, "■",我坦颜色);
		else
			GotoxyAndPrint(m_core.X, m_core.Y, "■", 敌坦颜色);		
	}
}