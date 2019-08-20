#include <conio.h>
#include "Tank.h"
#include "Map.h"
#include "Game.h"

//坦克相关
CTank::CTank(COORD core, enum direction dir, int blood, int who)
{
	m_core = core;
	//m_body[5] = { {0,0} };
	m_dir= dir;
	m_blood= blood;
	m_isAlive=true;
	m_who = who;
	SetTankShape();
}
void CTank::CleanTankTail(COORD oldCore, PCOORD oldBody)
{
	GotoxyAndPrint(oldCore.X, oldCore.Y, "  ");//中心点
	for (int i = 0; i < 5; i++)//其他点
	{
		GotoxyAndPrint(oldBody[i].X, oldBody[i].Y, "  ");
	}
}
void CTank::SetTankShape()
{
	if (this->m_isAlive == false) return;
	if (this->m_dir == UP)
	{
		this->m_body[0] = { this->m_core.X, this->m_core.Y - 1 };
		this->m_body[1] = { this->m_core.X - 1, this->m_core.Y };
		this->m_body[2] = { this->m_core.X + 1, this->m_core.Y };
		this->m_body[3] = { this->m_core.X - 1, this->m_core.Y + 1 };
		this->m_body[4] = { this->m_core.X + 1, this->m_core.Y + 1 };
	}
	else if (this->m_dir == DOWN)
	{
		this->m_body[0] = { this->m_core.X, this->m_core.Y + 1 };
		this->m_body[1] = { this->m_core.X - 1, this->m_core.Y };
		this->m_body[2] = { this->m_core.X + 1, this->m_core.Y };
		this->m_body[3] = { this->m_core.X - 1, this->m_core.Y - 1 };
		this->m_body[4] = { this->m_core.X + 1, this->m_core.Y - 1 };
	}
	else if (this->m_dir == LEFT)
	{
		this->m_body[0] = { this->m_core.X - 1, this->m_core.Y };
		this->m_body[1] = { this->m_core.X , this->m_core.Y + 1 };
		this->m_body[2] = { this->m_core.X , this->m_core.Y - 1 };
		this->m_body[3] = { this->m_core.X + 1, this->m_core.Y + 1 };
		this->m_body[4] = { this->m_core.X + 1, this->m_core.Y - 1 };
	}
	else if (this->m_dir == RIGHT)
	{
		this->m_body[0] = { this->m_core.X + 1, this->m_core.Y };
		this->m_body[1] = { this->m_core.X , this->m_core.Y + 1 };
		this->m_body[2] = { this->m_core.X , this->m_core.Y - 1 };
		this->m_body[3] = { this->m_core.X - 1, this->m_core.Y + 1 };
		this->m_body[4] = { this->m_core.X - 1, this->m_core.Y - 1 };
	}
}
void CTank::ManipulateMyTank(CTank * penemytank,CMap map,CGame &game)
{
	if (this->m_isAlive == false) return;
	if (this->m_who == 我方坦克)
	{
		char ch = 0;
		if (_kbhit())				//非阻塞函数 
		{
			ch = _getch();			//无回显接受输入
			switch (ch)
			{
			case 'w':
				if (!this->IsMyTankMeetOther(UP, penemytank,map))
					this->m_core.Y--;
				this->m_dir = UP;
				break;
			case 's':
				if (!this->IsMyTankMeetOther(DOWN, penemytank, map))
					this->m_core.Y++;
				this->m_dir = DOWN;
				break;
			case 'a':
				if (!this->IsMyTankMeetOther(LEFT, penemytank, map))
					this->m_core.X--;
				this->m_dir = LEFT;
				break;
			case 'd':
				if (!this->IsMyTankMeetOther(RIGHT, penemytank, map))
					this->m_core.X++;
				this->m_dir = RIGHT;
				break;
			case ' ':
				if (this->m_bullet.m_state != 已赋值)
					this->m_bullet.m_state = 未赋值;//已赋值即在跑时，再开火，不可赋值为1，应该消失为0时，按键才生效
				break;
			case 'q':
			{
				//暂停及恢复
				mciSendString("pause bgm", NULL, 0, NULL);	//暂停bgm
				setColor(12, 0);
				GotoxyAndPrint(MAP_X_WALL / 2 + 1, 1, "       ");//先把较长的running清空
				GotoxyAndPrint(MAP_X_WALL / 2 + 1, 1, "PAUSE");
				GotoxyAndPrint(MAP_X_WALL / 2 + 1, 2, "1. 回到游戏");
				GotoxyAndPrint(MAP_X_WALL / 2 + 1, 3, "2. 退出游戏");
				char tmp;
				do
				{
					tmp = _getch();	//利用阻塞函数暂停游戏
				} while (!(tmp == '1' || tmp == '2' || tmp == '3'));//只有输入123才可
				switch (tmp)
				{
				case '1'://恢复游戏
				{
					mciSendString("resume bgm", NULL, 0, NULL);//恢复bgm
					GotoxyAndPrint(MAP_X_WALL / 2 + 1, 1, "RUNNING");
					GotoxyAndPrint(MAP_X_WALL / 2 + 1, 2, "Q: 暂停游戏");
					GotoxyAndPrint(MAP_X_WALL / 2 + 1, 3, "           ");
					GotoxyAndPrint(MAP_X_WALL / 2 + 1, 4, "           ");
					break;
				}
				case '2'://退出游戏
				{
					GotoxyAndPrint(MAP_X_WALL / 2 + 1, 1, "想如何退出?");
					GotoxyAndPrint(MAP_X_WALL / 2 + 1, 2, "1. 保存退出");
					GotoxyAndPrint(MAP_X_WALL / 2 + 1, 3, "2. 直接退出");
					char op = _getch();
					if (op == '1')		//保存退出
					{
						game.SaveGame(*this, penemytank,map);
						game.GameOver(penemytank);
						game.m_isRunning = false;
						break;
					}
					else if (op == '2')	//直接退出
					{
						game.GameOver(penemytank);
						game.m_isRunning = false;
						break;
					}
				}
				default:
					break;
				}
				break;
			}
			default:
				break;
			}
		}
	}
	SetTankShape();//每次移动后都要重新设置形态
}
bool CTank::IsMyTankMeetOther(int dir, CTank * penemytank,CMap map)
{
	switch (dir)
	{
	case UP:
		//是否撞边界
		if (this->m_core.Y <= 2)
		{
			return true;
		}
		//是否撞障碍物
		if ((map.m_nArrMap[this->m_core.X][this->m_core.Y - 2] == 土块 ||
			map.m_nArrMap[this->m_core.X - 1][this->m_core.Y - 2] == 土块 ||
			map.m_nArrMap[this->m_core.X + 1][this->m_core.Y - 2] == 土块) ||
			(map.m_nArrMap[this->m_core.X][this->m_core.Y - 2] == 石块 ||
				map.m_nArrMap[this->m_core.X - 1][this->m_core.Y - 2] == 石块 ||
				map.m_nArrMap[this->m_core.X + 1][this->m_core.Y - 2] == 石块))
		{
			return true;
		}
		//是否撞敌方坦克
		for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
		{
			if (penemytank[i].m_isAlive == false) continue;
			if (
				((this->m_core.X == penemytank[i].m_core.X) && (this->m_core.Y - penemytank[i].m_core.Y == 3)) ||
				((this->m_core.X == penemytank[i].m_core.X - 1) && (this->m_core.Y - penemytank[i].m_core.Y == 3)) ||
				((this->m_core.X == penemytank[i].m_core.X - 2) && (this->m_core.Y - penemytank[i].m_core.Y == 3)) ||
				((this->m_core.X == penemytank[i].m_core.X + 1) && (this->m_core.Y - penemytank[i].m_core.Y == 3)) ||
				((this->m_core.X == penemytank[i].m_core.X + 2) && (this->m_core.Y - penemytank[i].m_core.Y == 3))
				)//要==3,而非<=，只有在挨着的时候可被当，如果小于，虽没挨着敌坦1，但距离却小于2，被2干扰
			{
				return true;
			}
		}
		break;
	case DOWN:
		//是否撞边界
		if (this->m_core.Y >= MAP_Y - 3)
		{
			return true;
		}
		//是否撞障碍物
		if ((map.m_nArrMap[this->m_core.X][this->m_core.Y + 2] == 土块 ||
			map.m_nArrMap[this->m_core.X - 1][this->m_core.Y + 2] == 土块 ||
			map.m_nArrMap[this->m_core.X + 1][this->m_core.Y + 2] == 土块) ||
			(map.m_nArrMap[this->m_core.X][this->m_core.Y + 2] == 石块 ||
				map.m_nArrMap[this->m_core.X - 1][this->m_core.Y + 2] == 石块 ||
				map.m_nArrMap[this->m_core.X + 1][this->m_core.Y + 2] == 石块))
		{
			return true;
		}
		//是否遇到我家泉水
		if (map.m_nArrMap[this->m_core.X][this->m_core.Y] == 泉水)
		{
			return true;
		}
		//是否撞敌方坦克
		for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
		{
			if (penemytank[i].m_isAlive == false) continue;
			if (
				((this->m_core.X == penemytank[i].m_core.X) && (penemytank[i].m_core.Y - this->m_core.Y == 3)) ||
				((this->m_core.X == penemytank[i].m_core.X - 1) && (penemytank[i].m_core.Y - this->m_core.Y == 3)) ||
				((this->m_core.X == penemytank[i].m_core.X - 2) && (penemytank[i].m_core.Y - this->m_core.Y == 3)) ||
				((this->m_core.X == penemytank[i].m_core.X + 1) && (penemytank[i].m_core.Y - this->m_core.Y == 3)) ||
				((this->m_core.X == penemytank[i].m_core.X + 2) && (penemytank[i].m_core.Y - this->m_core.Y == 3))
				)
			{
				return true;
			}
		}
		break;
	case LEFT:
		//是否撞边界
		if (this->m_core.X <= 2)
		{
			return true;
		}
		//是否撞障碍物
		if ((map.m_nArrMap[this->m_core.X - 2][this->m_core.Y] == 土块 ||
			map.m_nArrMap[this->m_core.X - 2][this->m_core.Y - 1] == 土块 ||
			map.m_nArrMap[this->m_core.X - 2][this->m_core.Y + 1] == 土块) ||
			(map.m_nArrMap[this->m_core.X - 2][this->m_core.Y] == 石块 ||
				map.m_nArrMap[this->m_core.X - 2][this->m_core.Y - 1] == 石块 ||
				map.m_nArrMap[this->m_core.X - 2][this->m_core.Y + 1] == 石块))
		{
			return true;
		}
		//是否遇到我家泉水
		if (map.m_nArrMap[this->m_core.X][this->m_core.Y] == 泉水)
		{
			return true;
		}
		//是否撞敌方坦克
		for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
		{
			if (penemytank[i].m_isAlive == false) continue;
			if (
				((this->m_core.Y == penemytank[i].m_core.Y) && (this->m_core.X - penemytank[i].m_core.X == 3)) ||
				((this->m_core.Y == penemytank[i].m_core.Y - 1) && (this->m_core.X - penemytank[i].m_core.X == 3)) ||
				((this->m_core.Y == penemytank[i].m_core.Y - 2) && (this->m_core.X - penemytank[i].m_core.X == 3)) ||
				((this->m_core.Y == penemytank[i].m_core.Y + 1) && (this->m_core.X - penemytank[i].m_core.X == 3)) ||
				((this->m_core.Y == penemytank[i].m_core.Y + 2) && (this->m_core.X - penemytank[i].m_core.X == 3))
				)
			{
				return true;
			}
		}
		break;
	case RIGHT:
		//是否撞边界
		if (this->m_core.X >= MAP_X_WALL / 2 - 2)
		{
			return true;
		}
		//是否撞障碍物
		if ((map.m_nArrMap[this->m_core.X + 2][this->m_core.Y] == 土块 ||
			map.m_nArrMap[this->m_core.X + 2][this->m_core.Y - 1] == 土块 ||
			map.m_nArrMap[this->m_core.X + 2][this->m_core.Y + 1] == 土块) ||
			(map.m_nArrMap[this->m_core.X + 2][this->m_core.Y] == 石块 ||
				map.m_nArrMap[this->m_core.X + 2][this->m_core.Y - 1] == 石块 ||
				map.m_nArrMap[this->m_core.X + 2][this->m_core.Y + 1] == 石块))
		{
			return true;
		}
		//是否遇到我家泉水
		if (map.m_nArrMap[this->m_core.X][this->m_core.Y] == 泉水)
		{
			return true;
		}
		//是否撞敌方坦克
		for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
		{
			if (penemytank[i].m_isAlive == false) continue;
			if (
				((this->m_core.Y == penemytank[i].m_core.Y) && (penemytank[i].m_core.X - this->m_core.X == 3)) ||
				((this->m_core.Y == penemytank[i].m_core.Y - 1) && (penemytank[i].m_core.X - this->m_core.X == 3)) ||
				((this->m_core.Y == penemytank[i].m_core.Y - 2) && (penemytank[i].m_core.X - this->m_core.X == 3)) ||
				((this->m_core.Y == penemytank[i].m_core.Y + 1) && (penemytank[i].m_core.X - this->m_core.X == 3)) ||
				((this->m_core.Y == penemytank[i].m_core.Y + 2) && (penemytank[i].m_core.X - this->m_core.X == 3))
				)
			{
				return true;
			}
		}
		break;
	default:
		break;
	}
	return false;
}
void CTank::ManipulateEneTank(CTank pmytank, CTank* penemytank, CMap map)
{
	if (this->m_isAlive == false) return;
	if (this->m_who == 敌方坦克)
	{
		switch (rand() % 5)
		{
		case UP:
			if (!this->IsEneTankMeetOther( UP, pmytank, penemytank,map))
				this->m_core.Y--;
			this->m_dir = UP;
			break;
		case DOWN:
			if (!this->IsEneTankMeetOther( DOWN, pmytank, penemytank,map))
				this->m_core.Y++;
			this->m_dir = DOWN;
			break;
		case LEFT:
			if (!this->IsEneTankMeetOther(LEFT, pmytank, penemytank,map))
				this->m_core.X--;
			this->m_dir = LEFT;
			break;
		case RIGHT:
			if (!this->IsEneTankMeetOther(RIGHT, pmytank, penemytank,map))
				this->m_core.X++;
			this->m_dir = RIGHT;
			break;
		case 4:
			if (this->m_bullet.m_state != 已赋值)
				this->m_bullet.m_state = 未赋值;
			break;
		default:
			break;
		}
	}
	SetTankShape();//每次移动后都要重新设置形态
}
bool CTank::IsEneTankMeetOther(int dir, CTank pmytank, CTank* penemytank, CMap map)
{
	switch (dir)
	{
	case UP:
		//是否撞边界
		if (this->m_core.Y <= 2)
		{
			return true;
		}
		//是否撞障碍物
		if ((map.m_nArrMap[this->m_core.X][this->m_core.Y - 2] == 土块 ||
			map.m_nArrMap[this->m_core.X - 1][this->m_core.Y - 2] == 土块 ||
			map.m_nArrMap[this->m_core.X + 1][this->m_core.Y - 2] == 土块) ||
			(map.m_nArrMap[this->m_core.X][this->m_core.Y - 2] == 石块 ||
				map.m_nArrMap[this->m_core.X - 1][this->m_core.Y - 2] == 石块 ||
				map.m_nArrMap[this->m_core.X + 1][this->m_core.Y - 2] == 石块))
		{
			return true;
		}
		//是否撞我方坦克
		if (
			((this->m_core.X == pmytank.m_core.X - 0) && (this->m_core.Y - pmytank.m_core.Y == 3)) ||
			((this->m_core.X == pmytank.m_core.X - 1) && (this->m_core.Y - pmytank.m_core.Y == 3)) ||
			((this->m_core.X == pmytank.m_core.X - 2) && (this->m_core.Y - pmytank.m_core.Y == 3)) ||
			((this->m_core.X == pmytank.m_core.X + 1) && (this->m_core.Y - pmytank.m_core.Y == 3)) ||
			((this->m_core.X == pmytank.m_core.X + 2) && (this->m_core.Y - pmytank.m_core.Y == 3))
			)//要==3,而非<=，只有在挨着的时候可被当，如果小于，虽没挨着敌坦1，但距离却小于2，被2干扰
		{
			return true;
		}
		//是否撞其他敌方坦克
		for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
		{
			if (this->m_core.X == penemytank[i].m_core.X && this->m_core.Y == penemytank[i].m_core.Y)//排除自己
				continue;
			if (
				((this->m_core.X == penemytank[i].m_core.X) && (this->m_core.Y - penemytank[i].m_core.Y == 3)) ||
				((this->m_core.X == penemytank[i].m_core.X - 1) && (this->m_core.Y - penemytank[i].m_core.Y == 3)) ||
				((this->m_core.X == penemytank[i].m_core.X - 2) && (this->m_core.Y - penemytank[i].m_core.Y == 3)) ||
				((this->m_core.X == penemytank[i].m_core.X + 1) && (this->m_core.Y - penemytank[i].m_core.Y == 3)) ||
				((this->m_core.X == penemytank[i].m_core.X + 2) && (this->m_core.Y - penemytank[i].m_core.Y == 3))
				)//要==3,而非<=，只有在挨着的时候可被当，如果小于，虽没挨着敌坦1，但距离却小于2，被2干扰
			{
				return true;
			}
		}
		break;
	case DOWN:
		//是否撞边界
		if (this->m_core.Y >= MAP_Y - 3)
		{
			return true;
		}
		//是否撞障碍物
		if ((map.m_nArrMap[this->m_core.X][this->m_core.Y + 2] == 土块 ||
			map.m_nArrMap[this->m_core.X - 1][this->m_core.Y + 2] == 土块 ||
			map.m_nArrMap[this->m_core.X + 1][this->m_core.Y + 2] == 土块) ||
			(map.m_nArrMap[this->m_core.X][this->m_core.Y + 2] == 石块 ||
				map.m_nArrMap[this->m_core.X - 1][this->m_core.Y + 2] == 石块 ||
				map.m_nArrMap[this->m_core.X + 1][this->m_core.Y + 2] == 石块))
		{
			return true;
		}
		//是否遇到我家泉水
		if (map.m_nArrMap[this->m_core.X][this->m_core.Y] == 泉水)
		{
			return true;
		}
		//是否撞我方坦克
		if (
			((this->m_core.X == pmytank.m_core.X - 0) && (pmytank.m_core.Y - this->m_core.Y == 3)) ||
			((this->m_core.X == pmytank.m_core.X - 1) && (pmytank.m_core.Y - this->m_core.Y == 3)) ||
			((this->m_core.X == pmytank.m_core.X - 2) && (pmytank.m_core.Y - this->m_core.Y == 3)) ||
			((this->m_core.X == pmytank.m_core.X + 1) && (pmytank.m_core.Y - this->m_core.Y == 3)) ||
			((this->m_core.X == pmytank.m_core.X + 2) && (pmytank.m_core.Y - this->m_core.Y == 3))
			)
		{
			return true;
		}
		//是否撞其他敌方坦克
		for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
		{
			if (this->m_core.X == penemytank[i].m_core.X && this->m_core.Y == penemytank[i].m_core.Y)//排除自己
				continue;
			if (
				((this->m_core.X == penemytank[i].m_core.X) && (penemytank[i].m_core.Y - this->m_core.Y == 3)) ||
				((this->m_core.X == penemytank[i].m_core.X - 1) && (penemytank[i].m_core.Y - this->m_core.Y == 3)) ||
				((this->m_core.X == penemytank[i].m_core.X - 2) && (penemytank[i].m_core.Y - this->m_core.Y == 3)) ||
				((this->m_core.X == penemytank[i].m_core.X + 1) && (penemytank[i].m_core.Y - this->m_core.Y == 3)) ||
				((this->m_core.X == penemytank[i].m_core.X + 2) && (penemytank[i].m_core.Y - this->m_core.Y == 3))
				)
			{
				return true;
			}
		}
		break;
	case LEFT:
		//是否撞边界
		if (this->m_core.X <= 2)
		{
			return true;
		}
		//是否撞障碍物
		if ((map.m_nArrMap[this->m_core.X - 2][this->m_core.Y] == 土块 ||
			map.m_nArrMap[this->m_core.X - 2][this->m_core.Y - 1] == 土块 ||
			map.m_nArrMap[this->m_core.X - 2][this->m_core.Y + 1] == 土块) ||
			(map.m_nArrMap[this->m_core.X - 2][this->m_core.Y] == 石块 ||
				map.m_nArrMap[this->m_core.X - 2][this->m_core.Y - 1] == 石块 ||
				map.m_nArrMap[this->m_core.X - 2][this->m_core.Y + 1] == 石块))
		{
			return true;
		}
		//是否遇到我家泉水
		if (map.m_nArrMap[this->m_core.X][this->m_core.Y] == 泉水)
		{
			return true;
		}
		//是否撞我方坦克
		if (
			((this->m_core.Y == pmytank.m_core.Y - 0) && (this->m_core.X - pmytank.m_core.X == 3)) ||
			((this->m_core.Y == pmytank.m_core.Y - 1) && (this->m_core.X - pmytank.m_core.X == 3)) ||
			((this->m_core.Y == pmytank.m_core.Y - 2) && (this->m_core.X - pmytank.m_core.X == 3)) ||
			((this->m_core.Y == pmytank.m_core.Y + 1) && (this->m_core.X - pmytank.m_core.X == 3)) ||
			((this->m_core.Y == pmytank.m_core.Y + 2) && (this->m_core.X - pmytank.m_core.X == 3))
			)
		{
			return true;
		}
		//是否撞其他敌方坦克
		for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
		{
			if (this->m_core.X == penemytank[i].m_core.X && this->m_core.Y == penemytank[i].m_core.Y)//排除自己
				continue;
			if (
				((this->m_core.Y == penemytank[i].m_core.Y) && (this->m_core.X - penemytank[i].m_core.X == 3)) ||
				((this->m_core.Y == penemytank[i].m_core.Y - 1) && (this->m_core.X - penemytank[i].m_core.X == 3)) ||
				((this->m_core.Y == penemytank[i].m_core.Y - 2) && (this->m_core.X - penemytank[i].m_core.X == 3)) ||
				((this->m_core.Y == penemytank[i].m_core.Y + 1) && (this->m_core.X - penemytank[i].m_core.X == 3)) ||
				((this->m_core.Y == penemytank[i].m_core.Y + 2) && (this->m_core.X - penemytank[i].m_core.X == 3))
				)
			{
				return true;
			}
		}
		break;
	case RIGHT:
		//是否撞边界
		if (this->m_core.X >= MAP_X_WALL / 2 - 2)
		{
			return true;
		}
		//是否撞障碍物
		if ((map.m_nArrMap[this->m_core.X + 2][this->m_core.Y] == 土块 ||
			map.m_nArrMap[this->m_core.X + 2][this->m_core.Y - 1] == 土块 ||
			map.m_nArrMap[this->m_core.X + 2][this->m_core.Y + 1] == 土块) ||
			(map.m_nArrMap[this->m_core.X + 2][this->m_core.Y] == 石块 ||
				map.m_nArrMap[this->m_core.X + 2][this->m_core.Y - 1] == 石块 ||
				map.m_nArrMap[this->m_core.X + 2][this->m_core.Y + 1] == 石块))
		{
			return true;
		}
		//是否遇到我家泉水
		if (map.m_nArrMap[this->m_core.X][this->m_core.Y] == 泉水)
		{
			return true;
		}
		//是否撞我方坦克
		if (
			((this->m_core.Y == pmytank.m_core.Y - 0) && (pmytank.m_core.X - this->m_core.X == 3)) ||
			((this->m_core.Y == pmytank.m_core.Y - 1) && (pmytank.m_core.X - this->m_core.X == 3)) ||
			((this->m_core.Y == pmytank.m_core.Y - 2) && (pmytank.m_core.X - this->m_core.X == 3)) ||
			((this->m_core.Y == pmytank.m_core.Y + 1) && (pmytank.m_core.X - this->m_core.X == 3)) ||
			((this->m_core.Y == pmytank.m_core.Y + 2) && (pmytank.m_core.X - this->m_core.X == 3))
			)
		{
			return true;
		}
		//是否撞其他敌方坦克
		for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
		{
			if (this->m_core.X == penemytank[i].m_core.X && this->m_core.Y == penemytank[i].m_core.Y)//排除自己
				continue;
			if (
				((this->m_core.Y == penemytank[i].m_core.Y) && (penemytank[i].m_core.X - this->m_core.X == 3)) ||
				((this->m_core.Y == penemytank[i].m_core.Y - 1) && (penemytank[i].m_core.X - this->m_core.X == 3)) ||
				((this->m_core.Y == penemytank[i].m_core.Y - 2) && (penemytank[i].m_core.X - this->m_core.X == 3)) ||
				((this->m_core.Y == penemytank[i].m_core.Y + 1) && (penemytank[i].m_core.X - this->m_core.X == 3)) ||
				((this->m_core.Y == penemytank[i].m_core.Y + 2) && (penemytank[i].m_core.X - this->m_core.X == 3))
				)
			{
				return true;
			}
		}
		break;
	default:
		break;
	}
	return false;
}
void CTank::DrawTank()
{
	if (this->m_isAlive == false) return;
	if (this->m_who == 我方坦克)
	{
		setColor(10, 0);
		GotoxyAndPrint(this->m_core.X, this->m_core.Y, "■");//中心点
		for (int i = 0; i < 5; i++)//其他点
		{
			GotoxyAndPrint(this->m_body[i].X, this->m_body[i].Y, "■");
		}
		setColor(7, 0);
	}
	else if (this->m_who == 敌方坦克)
	{
		setColor(11, 0);//亮蓝色
		if (this->m_blood == 2)
		{
			GotoxyAndPrint(this->m_core.X, this->m_core.Y, "■");//中心点
			for (int i = 0; i < 5; i++)//其他点
				GotoxyAndPrint(this->m_body[i].X, this->m_body[i].Y, "■");//中心点
		}
		else if (this->m_blood == 1)
		{
			GotoxyAndPrint(this->m_core.X, this->m_core.Y, "□");//中心点
			for (int i = 0; i < 5; i++)//其他点
				GotoxyAndPrint(this->m_body[i].X, this->m_body[i].Y, "□");
		}
		setColor(7, 0);
	}
}
int GetLiveEnemyAmount(CTank* penemytank)
{
	int count = 0;
	for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
	{
		if (penemytank[i].m_isAlive == true)
			count++;
	}
	return count;
}