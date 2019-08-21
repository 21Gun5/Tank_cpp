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
		GotoxyAndPrint(oldBody[i].X, oldBody[i].Y, "  ");
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

//void CTank::ManipulateMyTank(CTank* pMyTank, CTank* pEnemyTank, CMap map, CGame& game)
//{
//	if (this->m_isAlive == false) return;
//	if (this->m_who == 我方坦克A)
//	{
//		if (KEYDOWN('W'))//小写不可，可大写和ASCII码
//		{
//			if (!this->IsTankMeetOther(UP,pMyTank, pEnemyTank, map))
//				this->m_core.Y--;
//			this->m_dir = UP;
//		}
//		else if (KEYDOWN('S'))
//		{
//			if (!this->IsTankMeetOther(DOWN, pMyTank,pEnemyTank, map))
//				this->m_core.Y++;
//			this->m_dir = DOWN;
//		}
//		else if (KEYDOWN('A'))
//		{
//			if (!this->IsTankMeetOther(LEFT, pMyTank,pEnemyTank, map))
//
//				this->m_core.X--;
//			this->m_dir = LEFT;
//		}
//		else if (KEYDOWN('D'))
//		{
//			if (!this->IsTankMeetOther(RIGHT, pMyTank,pEnemyTank, map))
//
//				this->m_core.X++;
//			this->m_dir = RIGHT;
//		}
//		else if (KEYDOWN(' '))
//		{
//			if (this->m_bullet.m_state != 已赋值)
//				this->m_bullet.m_state = 未赋值;//已赋值即在跑时，再开火，不可赋值为1，应该消失为0时，按键才生效
//		}
//		else if (KEYDOWN('Q'))
//		{
//			//暂停及恢复
//			mciSendString("pause bgm", NULL, 0, NULL);	//暂停bgm
//			setColor(12, 0);
//			GotoxyAndPrint(MAP_X_WALL / 2 + 1, 1, "       ");//先把较长的running清空
//			GotoxyAndPrint(MAP_X_WALL / 2 + 1, 1, "PAUSE");
//			GotoxyAndPrint(MAP_X_WALL / 2 + 1, 2, "1. 回到游戏");
//			GotoxyAndPrint(MAP_X_WALL / 2 + 1, 3, "2. 退出游戏");
//			char tmp;
//			do
//			{
//				tmp = _getch();	//利用阻塞函数暂停游戏
//			} while (!(tmp == '1' || tmp == '2' || tmp == '3'));//只有输入123才可
//			switch (tmp)
//			{
//			case '1'://恢复游戏
//			{
//				mciSendString("resume bgm", NULL, 0, NULL);//恢复bgm
//				GotoxyAndPrint(MAP_X_WALL / 2 + 1, 1, "RUNNING");
//				GotoxyAndPrint(MAP_X_WALL / 2 + 1, 2, "Q: 暂停游戏");
//				GotoxyAndPrint(MAP_X_WALL / 2 + 1, 3, "           ");
//				GotoxyAndPrint(MAP_X_WALL / 2 + 1, 4, "           ");
//				break;
//			}
//			case '2'://退出游戏
//			{
//				GotoxyAndPrint(MAP_X_WALL / 2 + 1, 1, "想如何退出?");
//				GotoxyAndPrint(MAP_X_WALL / 2 + 1, 2, "1. 保存退出");
//				GotoxyAndPrint(MAP_X_WALL / 2 + 1, 3, "2. 直接退出");
//				char op = _getch();
//				if (op == '1')		//保存退出
//				{
//					game.SaveGameFile(pMyTank, pEnemyTank, map);
//					game.GameOver(pEnemyTank);
//					game.m_isRunning = false;
//					break;
//				}
//				else if (op == '2')	//直接退出
//				{
//					game.GameOver(pEnemyTank);
//					game.m_isRunning = false;
//					break;
//				}
//			}
//			default:
//				break;
//			}
//		}
//	}
//	else if (this->m_who == 我方坦克B)
//	{
//		if (KEYDOWN('I'))//小写不可，可大写和ASCII码
//		{
//			if (!this->IsTankMeetOther(UP, pMyTank,pEnemyTank, map))
//				this->m_core.Y--;
//			this->m_dir = UP;
//		}
//		else if (KEYDOWN('K'))
//		{
//			if (!this->IsTankMeetOther(DOWN, pMyTank,pEnemyTank, map))
//				this->m_core.Y++;
//			this->m_dir = DOWN;
//		}
//		else if (KEYDOWN('J'))
//		{
//			if (!this->IsTankMeetOther(LEFT, pMyTank,pEnemyTank, map))
//
//				this->m_core.X--;
//			this->m_dir = LEFT;
//		}
//		else if (KEYDOWN('L'))
//		{
//			if (!this->IsTankMeetOther(RIGHT, pMyTank,pEnemyTank, map))
//
//				this->m_core.X++;
//			this->m_dir = RIGHT;
//		}
//		else if (KEYDOWN('H'))
//		{
//			if (this->m_bullet.m_state != 已赋值)
//				this->m_bullet.m_state = 未赋值;//已赋值即在跑时，再开火，不可赋值为1，应该消失为0时，按键才生效
//		}
//	}
//	SetTankShape();//每次移动后都要重新设置形态
//}

//bool CTank::IsTankMeetOther(int dir,CTank * pMyTank, CTank* pEnemyTank, CMap map)
//{
//	switch (dir)
//	{
//	case UP:
//		//是否撞边界
//		if (this->m_core.Y <= 2)
//		{
//			return true;
//		}
//		//是否撞障碍物
//		if ((map.m_nArrMap[m_core.X][m_core.Y - 2] == 土块 || map.m_nArrMap[m_core.X - 1][m_core.Y - 2] == 土块 || map.m_nArrMap[m_core.X + 1][m_core.Y - 2] == 土块) ||
//			(map.m_nArrMap[m_core.X][m_core.Y - 2] == 石块 || map.m_nArrMap[m_core.X - 1][m_core.Y - 2] == 石块 || map.m_nArrMap[m_core.X + 1][m_core.Y - 2] == 石块) ||
//			(map.m_nArrMap[m_core.X][m_core.Y - 2] == 河流 || map.m_nArrMap[m_core.X - 1][m_core.Y - 2] == 河流 || map.m_nArrMap[m_core.X + 1][m_core.Y - 2] == 河流))
//		{
//			return true;
//		}
//		//是否撞我方其他
//		for (int i = 0; i < MY_TANK_AMOUNT; i++)
//		{
//			if (this->m_core.X == pMyTank[i].m_core.X && this->m_core.Y == pMyTank[i].m_core.Y)//排除自己
//				continue;
//			if (
//				((this->m_core.X == pMyTank[i].m_core.X) && (this->m_core.Y - pMyTank[i].m_core.Y == 3)) ||
//				((this->m_core.X == pMyTank[i].m_core.X - 1) && (this->m_core.Y - pMyTank[i].m_core.Y == 3)) ||
//				((this->m_core.X == pMyTank[i].m_core.X - 2) && (this->m_core.Y - pMyTank[i].m_core.Y == 3)) ||
//				((this->m_core.X == pMyTank[i].m_core.X + 1) && (this->m_core.Y - pMyTank[i].m_core.Y == 3)) ||
//				((this->m_core.X == pMyTank[i].m_core.X + 2) && (this->m_core.Y - pMyTank[i].m_core.Y == 3))
//				)//要==3,而非<=，只有在挨着的时候可被当，如果小于，虽没挨着敌坦1，但距离却小于2，被2干扰
//			{
//				return true;
//			}
//		}
//		//是否撞敌方坦克
//		for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
//		{
//			if (pEnemyTank[i].m_isAlive == false) continue;
//			if (
//				((this->m_core.X == pEnemyTank[i].m_core.X) && (this->m_core.Y - pEnemyTank[i].m_core.Y == 3)) ||
//				((this->m_core.X == pEnemyTank[i].m_core.X - 1) && (this->m_core.Y - pEnemyTank[i].m_core.Y == 3)) ||
//				((this->m_core.X == pEnemyTank[i].m_core.X - 2) && (this->m_core.Y - pEnemyTank[i].m_core.Y == 3)) ||
//				((this->m_core.X == pEnemyTank[i].m_core.X + 1) && (this->m_core.Y - pEnemyTank[i].m_core.Y == 3)) ||
//				((this->m_core.X == pEnemyTank[i].m_core.X + 2) && (this->m_core.Y - pEnemyTank[i].m_core.Y == 3))
//				)//要==3,而非<=，只有在挨着的时候可被当，如果小于，虽没挨着敌坦1，但距离却小于2，被2干扰
//			{
//				return true;
//			}
//		}
//		break;
//	case DOWN:
//		//是否撞边界
//		if (this->m_core.Y >= MAP_Y - 3) 
//			return true;
//		//是否撞障碍物
//		if ((map.m_nArrMap[m_core.X][m_core.Y + 2] == 土块 || map.m_nArrMap[m_core.X - 1][m_core.Y + 2] == 土块 || map.m_nArrMap[m_core.X + 1][m_core.Y + 2] == 土块) ||
//			(map.m_nArrMap[m_core.X][m_core.Y + 2] == 石块 || map.m_nArrMap[m_core.X - 1][m_core.Y + 2] == 石块 || map.m_nArrMap[m_core.X + 1][m_core.Y + 2] == 石块) ||
//			(map.m_nArrMap[m_core.X][m_core.Y + 2] == 河流 || map.m_nArrMap[m_core.X - 1][m_core.Y + 2] == 河流 || map.m_nArrMap[m_core.X + 1][m_core.Y + 2] == 河流))
//		{
//			return true;
//		}
//		//是否遇到我家泉水
//		if (map.m_nArrMap[this->m_core.X][this->m_core.Y] == 泉水)
//		{
//			return true;
//		}
//		//是否撞我方其他
//		for (int i = 0; i < MY_TANK_AMOUNT; i++)
//		{
//			if (this->m_core.X == pMyTank[i].m_core.X && this->m_core.Y == pMyTank[i].m_core.Y)//排除自己
//				continue;
//			if (
//				((this->m_core.X == pMyTank[i].m_core.X) && (pMyTank[i].m_core.Y - this->m_core.Y == 3)) ||
//				((this->m_core.X == pMyTank[i].m_core.X - 1) && (pMyTank[i].m_core.Y - this->m_core.Y == 3)) ||
//				((this->m_core.X == pMyTank[i].m_core.X - 2) && (pMyTank[i].m_core.Y - this->m_core.Y == 3)) ||
//				((this->m_core.X == pMyTank[i].m_core.X + 1) && (pMyTank[i].m_core.Y - this->m_core.Y == 3)) ||
//				((this->m_core.X == pMyTank[i].m_core.X + 2) && (pMyTank[i].m_core.Y - this->m_core.Y == 3))
//				)
//			{
//				return true;
//			}
//		}
//		//是否撞敌方坦克
//		for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
//		{
//			if (pEnemyTank[i].m_isAlive == false) continue;
//			if (
//				((this->m_core.X == pEnemyTank[i].m_core.X) && (pEnemyTank[i].m_core.Y - this->m_core.Y == 3)) ||
//				((this->m_core.X == pEnemyTank[i].m_core.X - 1) && (pEnemyTank[i].m_core.Y - this->m_core.Y == 3)) ||
//				((this->m_core.X == pEnemyTank[i].m_core.X - 2) && (pEnemyTank[i].m_core.Y - this->m_core.Y == 3)) ||
//				((this->m_core.X == pEnemyTank[i].m_core.X + 1) && (pEnemyTank[i].m_core.Y - this->m_core.Y == 3)) ||
//				((this->m_core.X == pEnemyTank[i].m_core.X + 2) && (pEnemyTank[i].m_core.Y - this->m_core.Y == 3))
//				)
//			{
//				return true;
//			}
//		}
//		break;
//	case LEFT:
//		//是否撞边界
//		if (this->m_core.X <= 2)
//		{
//			return true;
//		}
//		//是否撞障碍物
//		if ((map.m_nArrMap[m_core.X - 2][m_core.Y] == 土块 || map.m_nArrMap[m_core.X - 2][m_core.Y - 1] == 土块 || map.m_nArrMap[m_core.X - 2][m_core.Y + 1] == 土块) ||
//			(map.m_nArrMap[m_core.X - 2][m_core.Y] == 石块 || map.m_nArrMap[m_core.X - 2][m_core.Y - 1] == 石块 || map.m_nArrMap[m_core.X - 2][m_core.Y + 1] == 石块) ||
//			(map.m_nArrMap[m_core.X - 2][m_core.Y] == 河流 || map.m_nArrMap[m_core.X - 2][m_core.Y - 1] == 河流 || map.m_nArrMap[m_core.X - 2][m_core.Y + 1] == 河流))
//		{
//			return true;
//		}
//		//是否遇到我家泉水
//		if (map.m_nArrMap[this->m_core.X][this->m_core.Y] == 泉水)
//		{
//			return true;
//		}
//		//是否撞我方其他
//		for (int i = 0; i < MY_TANK_AMOUNT; i++)
//		{
//			if (this->m_core.X == pMyTank[i].m_core.X && this->m_core.Y == pMyTank[i].m_core.Y)//排除自己
//				continue;
//			if (
//				((this->m_core.Y == pMyTank[i].m_core.Y) && (this->m_core.X - pMyTank[i].m_core.X == 3)) ||
//				((this->m_core.Y == pMyTank[i].m_core.Y - 1) && (this->m_core.X - pMyTank[i].m_core.X == 3)) ||
//				((this->m_core.Y == pMyTank[i].m_core.Y - 2) && (this->m_core.X - pMyTank[i].m_core.X == 3)) ||
//				((this->m_core.Y == pMyTank[i].m_core.Y + 1) && (this->m_core.X - pMyTank[i].m_core.X == 3)) ||
//				((this->m_core.Y == pMyTank[i].m_core.Y + 2) && (this->m_core.X - pMyTank[i].m_core.X == 3))
//				)
//			{
//				return true;
//			}
//		}
//		//是否撞敌方坦克
//		for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
//		{
//			if (pEnemyTank[i].m_isAlive == false) continue;
//			if (
//				((this->m_core.Y == pEnemyTank[i].m_core.Y) && (this->m_core.X - pEnemyTank[i].m_core.X == 3)) ||
//				((this->m_core.Y == pEnemyTank[i].m_core.Y - 1) && (this->m_core.X - pEnemyTank[i].m_core.X == 3)) ||
//				((this->m_core.Y == pEnemyTank[i].m_core.Y - 2) && (this->m_core.X - pEnemyTank[i].m_core.X == 3)) ||
//				((this->m_core.Y == pEnemyTank[i].m_core.Y + 1) && (this->m_core.X - pEnemyTank[i].m_core.X == 3)) ||
//				((this->m_core.Y == pEnemyTank[i].m_core.Y + 2) && (this->m_core.X - pEnemyTank[i].m_core.X == 3))
//				)
//			{
//				return true;
//			}
//		}
//		break;
//	case RIGHT:
//		//是否撞边界
//		if (this->m_core.X >= MAP_X_WALL / 2 - 2)
//		{
//			return true;
//		}
//		//是否撞障碍物
//		if ((map.m_nArrMap[m_core.X + 2][m_core.Y] == 土块 || map.m_nArrMap[m_core.X + 2][m_core.Y - 1] == 土块 || map.m_nArrMap[m_core.X + 2][m_core.Y + 1] == 土块) ||
//			(map.m_nArrMap[m_core.X + 2][m_core.Y] == 石块 || map.m_nArrMap[m_core.X + 2][m_core.Y - 1] == 石块 || map.m_nArrMap[m_core.X + 2][m_core.Y + 1] == 石块) ||
//			(map.m_nArrMap[m_core.X + 2][m_core.Y] == 河流 || map.m_nArrMap[m_core.X + 2][m_core.Y - 1] == 河流 || map.m_nArrMap[m_core.X + 2][m_core.Y + 1] == 河流))
//		{
//			return true;
//		}
//		//是否遇到我家泉水
//		if (map.m_nArrMap[this->m_core.X][this->m_core.Y] == 泉水)
//		{
//			return true;
//		}
//		//是否撞我方其他
//		for (int i = 0; i < MY_TANK_AMOUNT; i++)
//		{
//			if (this->m_core.X == pMyTank[i].m_core.X && this->m_core.Y == pMyTank[i].m_core.Y)//排除自己
//				continue;
//			if (
//				((this->m_core.Y == pMyTank[i].m_core.Y) && (pMyTank[i].m_core.X - this->m_core.X == 3)) ||
//				((this->m_core.Y == pMyTank[i].m_core.Y - 1) && (pMyTank[i].m_core.X - this->m_core.X == 3)) ||
//				((this->m_core.Y == pMyTank[i].m_core.Y - 2) && (pMyTank[i].m_core.X - this->m_core.X == 3)) ||
//				((this->m_core.Y == pMyTank[i].m_core.Y + 1) && (pMyTank[i].m_core.X - this->m_core.X == 3)) ||
//				((this->m_core.Y == pMyTank[i].m_core.Y + 2) && (pMyTank[i].m_core.X - this->m_core.X == 3))
//				)
//			{
//				return true;
//			}
//		}
//		//是否撞敌方坦克
//		for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
//		{
//			if (pEnemyTank[i].m_isAlive == false) continue;
//			if (
//				((this->m_core.Y == pEnemyTank[i].m_core.Y) && (pEnemyTank[i].m_core.X - this->m_core.X == 3)) ||
//				((this->m_core.Y == pEnemyTank[i].m_core.Y - 1) && (pEnemyTank[i].m_core.X - this->m_core.X == 3)) ||
//				((this->m_core.Y == pEnemyTank[i].m_core.Y - 2) && (pEnemyTank[i].m_core.X - this->m_core.X == 3)) ||
//				((this->m_core.Y == pEnemyTank[i].m_core.Y + 1) && (pEnemyTank[i].m_core.X - this->m_core.X == 3)) ||
//				((this->m_core.Y == pEnemyTank[i].m_core.Y + 2) && (pEnemyTank[i].m_core.X - this->m_core.X == 3))
//				)
//			{
//				return true;
//			}
//		}
//		break;
//	default:
//		break;
//	}
//	return false;
//}

void CTank::ManipulateTank(CTank* pMyTank, CTank* pEnemyTank, CMap map, CGame& game)
{
	if (this->m_isAlive == false) return;
	if (this->m_who == 我方坦克A)
	{
		if (KEYDOWN('W'))//小写不可，可大写和ASCII码
		{
			if (!this->IsTankMeetOther(UP, pMyTank, pEnemyTank, map))
				this->m_core.Y--;
			this->m_dir = UP;
		}
		else if (KEYDOWN('S'))
		{
			if (!this->IsTankMeetOther(DOWN, pMyTank, pEnemyTank, map))
				this->m_core.Y++;
			this->m_dir = DOWN;
		}
		else if (KEYDOWN('A'))
		{
			if (!this->IsTankMeetOther(LEFT, pMyTank, pEnemyTank, map))

				this->m_core.X--;
			this->m_dir = LEFT;
		}
		else if (KEYDOWN('D'))
		{
			if (!this->IsTankMeetOther(RIGHT, pMyTank, pEnemyTank, map))

				this->m_core.X++;
			this->m_dir = RIGHT;
		}
		else if (KEYDOWN(' '))
		{
			if (this->m_bullet.m_state != 已赋值)
				this->m_bullet.m_state = 未赋值;//已赋值即在跑时，再开火，不可赋值为1，应该消失为0时，按键才生效
		}
		else if (KEYDOWN('Q'))
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
					game.SaveGameFile(pMyTank, pEnemyTank, map);
					game.GameOver(pEnemyTank);
					game.m_isRunning = false;
					break;
				}
				else if (op == '2')	//直接退出
				{
					game.GameOver(pEnemyTank);
					game.m_isRunning = false;
					break;
				}
			}
			default:
				break;
			}
		}
	}
	else if (this->m_who == 我方坦克B)
	{
		if (KEYDOWN('I'))//小写不可，可大写和ASCII码
		{
			if (!this->IsTankMeetOther(UP, pMyTank, pEnemyTank, map))
				this->m_core.Y--;
			this->m_dir = UP;
		}
		else if (KEYDOWN('K'))
		{
			if (!this->IsTankMeetOther(DOWN, pMyTank, pEnemyTank, map))
				this->m_core.Y++;
			this->m_dir = DOWN;
		}
		else if (KEYDOWN('J'))
		{
			if (!this->IsTankMeetOther(LEFT, pMyTank, pEnemyTank, map))

				this->m_core.X--;
			this->m_dir = LEFT;
		}
		else if (KEYDOWN('L'))
		{
			if (!this->IsTankMeetOther(RIGHT, pMyTank, pEnemyTank, map))

				this->m_core.X++;
			this->m_dir = RIGHT;
		}
		else if (KEYDOWN('H'))
		{
			if (this->m_bullet.m_state != 已赋值)
				this->m_bullet.m_state = 未赋值;//已赋值即在跑时，再开火，不可赋值为1，应该消失为0时，按键才生效
		}
	}
	else if (this->m_who == 敌方坦克)
	{
	switch (rand() % 5)
	{
	case UP:
		if (!this->IsTankMeetOther(UP, pMyTank, pEnemyTank, map))
			this->m_core.Y--;
		this->m_dir = UP;
		break;
	case DOWN:
		if (!this->IsTankMeetOther(DOWN, pMyTank, pEnemyTank, map))
			this->m_core.Y++;
		this->m_dir = DOWN;
		break;
	case LEFT:
		if (!this->IsTankMeetOther(LEFT, pMyTank, pEnemyTank, map))
			this->m_core.X--;
		this->m_dir = LEFT;
		break;
	case RIGHT:
		if (!this->IsTankMeetOther(RIGHT, pMyTank, pEnemyTank, map))
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

//void CTank::ManipulateEneTank(CTank* pMyTank, CTank* pEnemyTank, CMap map)
//{
//	if (this->m_isAlive == false) return;
//	if (this->m_who == 敌方坦克)
//	{
//		switch (rand() % 5)
//		{
//		case UP:
//			if (!this->IsTankMeetOther(UP, pMyTank, pEnemyTank, map))
//				this->m_core.Y--;
//			this->m_dir = UP;
//			break;
//		case DOWN:
//			if (!this->IsTankMeetOther(DOWN, pMyTank, pEnemyTank, map))
//				this->m_core.Y++;
//			this->m_dir = DOWN;
//			break;
//		case LEFT:
//			if (!this->IsTankMeetOther(LEFT, pMyTank, pEnemyTank, map))
//				this->m_core.X--;
//			this->m_dir = LEFT;
//			break;
//		case RIGHT:
//			if (!this->IsTankMeetOther(RIGHT, pMyTank, pEnemyTank, map))
//				this->m_core.X++;
//			this->m_dir = RIGHT;
//			break;
//		case 4:
//			if (this->m_bullet.m_state != 已赋值)
//				this->m_bullet.m_state = 未赋值;
//			break;
//		default:
//			break;
//		}
//	}
//	SetTankShape();//每次移动后都要重新设置形态
//}

//bool CTank::IsEneTankMeetOther(int dir, CTank *pMyTank, CTank* pEnemyTank,CMap map)
//{
//	switch (dir)
//	{
//	case UP:
//		//是否撞边界
//		if (this->m_core.Y <= 2)
//		{
//			return true;
//		}
//		//是否撞障碍物
//		if ((map.m_nArrMap[m_core.X][m_core.Y - 2] == 土块 || map.m_nArrMap[m_core.X - 1][m_core.Y - 2] == 土块 || map.m_nArrMap[m_core.X + 1][m_core.Y - 2] == 土块) ||
//			(map.m_nArrMap[m_core.X][m_core.Y - 2] == 石块 || map.m_nArrMap[m_core.X - 1][m_core.Y - 2] == 石块 || map.m_nArrMap[m_core.X + 1][m_core.Y - 2] == 石块) ||
//			(map.m_nArrMap[m_core.X][m_core.Y - 2] == 河流 || map.m_nArrMap[m_core.X - 1][m_core.Y - 2] == 河流 || map.m_nArrMap[m_core.X + 1][m_core.Y - 2] == 河流))
//		{
//			return true;
//		}
//		//是否撞我方坦克
//		for (int i = 0; i < MY_TANK_AMOUNT; i++)
//		{
//			if (
//				((this->m_core.X == pMyTank[i].m_core.X - 0) && (this->m_core.Y - pMyTank[i].m_core.Y == 3)) ||
//				((this->m_core.X == pMyTank[i].m_core.X - 1) && (this->m_core.Y - pMyTank[i].m_core.Y == 3)) ||
//				((this->m_core.X == pMyTank[i].m_core.X - 2) && (this->m_core.Y - pMyTank[i].m_core.Y == 3)) ||
//				((this->m_core.X == pMyTank[i].m_core.X + 1) && (this->m_core.Y - pMyTank[i].m_core.Y == 3)) ||
//				((this->m_core.X == pMyTank[i].m_core.X + 2) && (this->m_core.Y - pMyTank[i].m_core.Y == 3))
//				)//要==3,而非<=，只有在挨着的时候可被当，如果小于，虽没挨着敌坦1，但距离却小于2，被2干扰
//			{
//				return true;
//			}
//		}
//		//是否撞其他敌方坦克
//		for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
//		{
//			if (this->m_core.X == pEnemyTank[i].m_core.X && this->m_core.Y == pEnemyTank[i].m_core.Y)//排除自己
//				continue;
//			if (
//				((this->m_core.X == pEnemyTank[i].m_core.X) && (this->m_core.Y - pEnemyTank[i].m_core.Y == 3)) ||
//				((this->m_core.X == pEnemyTank[i].m_core.X - 1) && (this->m_core.Y - pEnemyTank[i].m_core.Y == 3)) ||
//				((this->m_core.X == pEnemyTank[i].m_core.X - 2) && (this->m_core.Y - pEnemyTank[i].m_core.Y == 3)) ||
//				((this->m_core.X == pEnemyTank[i].m_core.X + 1) && (this->m_core.Y - pEnemyTank[i].m_core.Y == 3)) ||
//				((this->m_core.X == pEnemyTank[i].m_core.X + 2) && (this->m_core.Y - pEnemyTank[i].m_core.Y == 3))
//				)//要==3,而非<=，只有在挨着的时候可被当，如果小于，虽没挨着敌坦1，但距离却小于2，被2干扰
//			{
//				return true;
//			}
//		}
//		break;
//	case DOWN:
//		//是否撞边界
//		if (this->m_core.Y >= MAP_Y - 3)
//		{
//			return true;
//		}
//		//是否撞障碍物
//		if ((map.m_nArrMap[m_core.X][m_core.Y + 2] == 土块 || map.m_nArrMap[m_core.X - 1][m_core.Y + 2] == 土块 || map.m_nArrMap[m_core.X + 1][m_core.Y + 2] == 土块) ||
//			(map.m_nArrMap[m_core.X][m_core.Y + 2] == 石块 || map.m_nArrMap[m_core.X - 1][m_core.Y + 2] == 石块 || map.m_nArrMap[m_core.X + 1][m_core.Y + 2] == 石块) ||
//			(map.m_nArrMap[m_core.X][m_core.Y + 2] == 河流 || map.m_nArrMap[m_core.X - 1][m_core.Y + 2] == 河流 || map.m_nArrMap[m_core.X + 1][m_core.Y + 2] == 河流) )
//		{
//			return true;
//		}
//		//是否遇到我家泉水
//		if (map.m_nArrMap[this->m_core.X][this->m_core.Y] == 泉水)
//		{
//			return true;
//		}
//		//是否撞我方坦克
//		for (int i = 0; i < MY_TANK_AMOUNT; i++)
//		{
//			if (
//				((this->m_core.X == pMyTank[i].m_core.X - 0) && (pMyTank[i].m_core.Y - this->m_core.Y == 3)) ||
//				((this->m_core.X == pMyTank[i].m_core.X - 1) && (pMyTank[i].m_core.Y - this->m_core.Y == 3)) ||
//				((this->m_core.X == pMyTank[i].m_core.X - 2) && (pMyTank[i].m_core.Y - this->m_core.Y == 3)) ||
//				((this->m_core.X == pMyTank[i].m_core.X + 1) && (pMyTank[i].m_core.Y - this->m_core.Y == 3)) ||
//				((this->m_core.X == pMyTank[i].m_core.X + 2) && (pMyTank[i].m_core.Y - this->m_core.Y == 3))
//				)
//			{
//				return true;
//			}
//		}
//		//是否撞其他敌方坦克
//		for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
//		{
//			if (this->m_core.X == pEnemyTank[i].m_core.X && this->m_core.Y == pEnemyTank[i].m_core.Y)//排除自己
//				continue;
//			if (
//				((this->m_core.X == pEnemyTank[i].m_core.X) && (pEnemyTank[i].m_core.Y - this->m_core.Y == 3)) ||
//				((this->m_core.X == pEnemyTank[i].m_core.X - 1) && (pEnemyTank[i].m_core.Y - this->m_core.Y == 3)) ||
//				((this->m_core.X == pEnemyTank[i].m_core.X - 2) && (pEnemyTank[i].m_core.Y - this->m_core.Y == 3)) ||
//				((this->m_core.X == pEnemyTank[i].m_core.X + 1) && (pEnemyTank[i].m_core.Y - this->m_core.Y == 3)) ||
//				((this->m_core.X == pEnemyTank[i].m_core.X + 2) && (pEnemyTank[i].m_core.Y - this->m_core.Y == 3))
//				)
//			{
//				return true;
//			}
//		}
//		break;
//	case LEFT:
//		//是否撞边界
//		if (this->m_core.X <= 2)
//		{
//			return true;
//		}
//		//是否撞障碍物
//		if ((map.m_nArrMap[m_core.X - 2][m_core.Y] == 土块 || map.m_nArrMap[m_core.X - 2][m_core.Y - 1] == 土块 || map.m_nArrMap[m_core.X - 2][m_core.Y + 1] == 土块) ||
//			(map.m_nArrMap[m_core.X - 2][m_core.Y] == 石块 || map.m_nArrMap[m_core.X - 2][m_core.Y - 1] == 石块 || map.m_nArrMap[m_core.X - 2][m_core.Y + 1] == 石块) ||
//			(map.m_nArrMap[m_core.X - 2][m_core.Y] == 河流 || map.m_nArrMap[m_core.X - 2][m_core.Y - 1] == 河流 || map.m_nArrMap[m_core.X - 2][m_core.Y + 1] == 河流))
//		{
//			return true;
//		}
//		//是否遇到我家泉水
//		if (map.m_nArrMap[this->m_core.X][this->m_core.Y] == 泉水)
//		{
//			return true;
//		}
//		//是否撞我方坦克
//		for (int i = 0; i < MY_TANK_AMOUNT; i++)
//		{
//			if (
//				((this->m_core.Y == pMyTank[i].m_core.Y - 0) && (this->m_core.X - pMyTank[i].m_core.X == 3)) ||
//				((this->m_core.Y == pMyTank[i].m_core.Y - 1) && (this->m_core.X - pMyTank[i].m_core.X == 3)) ||
//				((this->m_core.Y == pMyTank[i].m_core.Y - 2) && (this->m_core.X - pMyTank[i].m_core.X == 3)) ||
//				((this->m_core.Y == pMyTank[i].m_core.Y + 1) && (this->m_core.X - pMyTank[i].m_core.X == 3)) ||
//				((this->m_core.Y == pMyTank[i].m_core.Y + 2) && (this->m_core.X - pMyTank[i].m_core.X == 3))
//				)
//			{
//				return true;
//			}
//		}
//		//是否撞其他敌方坦克
//		for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
//		{
//			if (this->m_core.X == pEnemyTank[i].m_core.X && this->m_core.Y == pEnemyTank[i].m_core.Y)//排除自己
//				continue;
//			if (
//				((this->m_core.Y == pEnemyTank[i].m_core.Y) && (this->m_core.X - pEnemyTank[i].m_core.X == 3)) ||
//				((this->m_core.Y == pEnemyTank[i].m_core.Y - 1) && (this->m_core.X - pEnemyTank[i].m_core.X == 3)) ||
//				((this->m_core.Y == pEnemyTank[i].m_core.Y - 2) && (this->m_core.X - pEnemyTank[i].m_core.X == 3)) ||
//				((this->m_core.Y == pEnemyTank[i].m_core.Y + 1) && (this->m_core.X - pEnemyTank[i].m_core.X == 3)) ||
//				((this->m_core.Y == pEnemyTank[i].m_core.Y + 2) && (this->m_core.X - pEnemyTank[i].m_core.X == 3))
//				)
//			{
//				return true;
//			}
//		}
//		break;
//	case RIGHT:
//		//是否撞边界
//		if (this->m_core.X >= MAP_X_WALL / 2 - 2)
//		{
//			return true;
//		}
//		//是否撞障碍物
//		if ((map.m_nArrMap[m_core.X + 2][m_core.Y] == 土块 || map.m_nArrMap[m_core.X + 2][m_core.Y - 1] == 土块 || map.m_nArrMap[m_core.X + 2][m_core.Y + 1] == 土块) ||
//			(map.m_nArrMap[m_core.X + 2][m_core.Y] == 石块 || map.m_nArrMap[m_core.X + 2][m_core.Y - 1] == 石块 || map.m_nArrMap[m_core.X + 2][m_core.Y + 1] == 石块) ||
//			(map.m_nArrMap[m_core.X + 2][m_core.Y] == 河流 || map.m_nArrMap[m_core.X + 2][m_core.Y - 1] == 河流 || map.m_nArrMap[m_core.X + 2][m_core.Y + 1] == 河流))
//		{
//			return true;
//		}
//		//是否遇到我家泉水
//		if (map.m_nArrMap[this->m_core.X][this->m_core.Y] == 泉水)
//		{
//			return true;
//		}
//		//是否撞我方坦克
//		for (int i = 0; i < MY_TANK_AMOUNT; i++)
//		{
//			if (
//				((this->m_core.Y == pMyTank[i].m_core.Y - 0) && (pMyTank[i].m_core.X - this->m_core.X == 3)) ||
//				((this->m_core.Y == pMyTank[i].m_core.Y - 1) && (pMyTank[i].m_core.X - this->m_core.X == 3)) ||
//				((this->m_core.Y == pMyTank[i].m_core.Y - 2) && (pMyTank[i].m_core.X - this->m_core.X == 3)) ||
//				((this->m_core.Y == pMyTank[i].m_core.Y + 1) && (pMyTank[i].m_core.X - this->m_core.X == 3)) ||
//				((this->m_core.Y == pMyTank[i].m_core.Y + 2) && (pMyTank[i].m_core.X - this->m_core.X == 3))
//				)
//			{
//				return true;
//			}
//		}
//		//是否撞其他敌方坦克
//		for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
//		{
//			if (this->m_core.X == pEnemyTank[i].m_core.X && this->m_core.Y == pEnemyTank[i].m_core.Y)//排除自己
//				continue;
//			if (
//				((this->m_core.Y == pEnemyTank[i].m_core.Y) && (pEnemyTank[i].m_core.X - this->m_core.X == 3)) ||
//				((this->m_core.Y == pEnemyTank[i].m_core.Y - 1) && (pEnemyTank[i].m_core.X - this->m_core.X == 3)) ||
//				((this->m_core.Y == pEnemyTank[i].m_core.Y - 2) && (pEnemyTank[i].m_core.X - this->m_core.X == 3)) ||
//				((this->m_core.Y == pEnemyTank[i].m_core.Y + 1) && (pEnemyTank[i].m_core.X - this->m_core.X == 3)) ||
//				((this->m_core.Y == pEnemyTank[i].m_core.Y + 2) && (pEnemyTank[i].m_core.X - this->m_core.X == 3))
//				)
//			{
//				return true;
//			}
//		}
//		break;
//	default:
//		break;
//	}
//	return false;
//}

bool CTank::IsTankMeetOther(int dir, CTank* pMyTank, CTank* pEnemyTank, CMap map)
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
		if ((map.m_nArrMap[m_core.X][m_core.Y - 2] == 土块 || map.m_nArrMap[m_core.X - 1][m_core.Y - 2] == 土块 || map.m_nArrMap[m_core.X + 1][m_core.Y - 2] == 土块) ||
			(map.m_nArrMap[m_core.X][m_core.Y - 2] == 石块 || map.m_nArrMap[m_core.X - 1][m_core.Y - 2] == 石块 || map.m_nArrMap[m_core.X + 1][m_core.Y - 2] == 石块) ||
			(map.m_nArrMap[m_core.X][m_core.Y - 2] == 河流 || map.m_nArrMap[m_core.X - 1][m_core.Y - 2] == 河流 || map.m_nArrMap[m_core.X + 1][m_core.Y - 2] == 河流))
		{
			return true;
		}
		//是否撞我方坦克
		for (int i = 0; i < MY_TANK_AMOUNT; i++)
		{
			//若是我坦，则跳过自己
			if (m_who != 敌方坦克)
			{
				if (this->m_core.X == pMyTank[i].m_core.X && this->m_core.Y == pMyTank[i].m_core.Y)//排除自己
					continue;
			}
			// 若此坦克死亡，则不阻挡
			if (pMyTank[i].m_isAlive == false) continue;
			if (
				((this->m_core.X == pMyTank[i].m_core.X - 0) && (this->m_core.Y - pMyTank[i].m_core.Y == 3)) ||
				((this->m_core.X == pMyTank[i].m_core.X - 1) && (this->m_core.Y - pMyTank[i].m_core.Y == 3)) ||
				((this->m_core.X == pMyTank[i].m_core.X - 2) && (this->m_core.Y - pMyTank[i].m_core.Y == 3)) ||
				((this->m_core.X == pMyTank[i].m_core.X + 1) && (this->m_core.Y - pMyTank[i].m_core.Y == 3)) ||
				((this->m_core.X == pMyTank[i].m_core.X + 2) && (this->m_core.Y - pMyTank[i].m_core.Y == 3))
				)//要==3,而非<=，只有在挨着的时候可被当，如果小于，虽没挨着敌坦1，但距离却小于2，被2干扰
			{
				return true;
			}
		}
		//是否撞敌方坦克
		for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
		{
			//若是敌坦，则跳过自己
			if (m_who == 敌方坦克)
			{
				if (this->m_core.X == pEnemyTank[i].m_core.X && this->m_core.Y == pEnemyTank[i].m_core.Y)//排除自己
					continue;
			}
			// 若此坦克死亡，则不阻挡
			if (pEnemyTank[i].m_isAlive == false) continue;
			if (
				((this->m_core.X == pEnemyTank[i].m_core.X) && (this->m_core.Y - pEnemyTank[i].m_core.Y == 3)) ||
				((this->m_core.X == pEnemyTank[i].m_core.X - 1) && (this->m_core.Y - pEnemyTank[i].m_core.Y == 3)) ||
				((this->m_core.X == pEnemyTank[i].m_core.X - 2) && (this->m_core.Y - pEnemyTank[i].m_core.Y == 3)) ||
				((this->m_core.X == pEnemyTank[i].m_core.X + 1) && (this->m_core.Y - pEnemyTank[i].m_core.Y == 3)) ||
				((this->m_core.X == pEnemyTank[i].m_core.X + 2) && (this->m_core.Y - pEnemyTank[i].m_core.Y == 3))
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
		if ((map.m_nArrMap[m_core.X][m_core.Y + 2] == 土块 || map.m_nArrMap[m_core.X - 1][m_core.Y + 2] == 土块 || map.m_nArrMap[m_core.X + 1][m_core.Y + 2] == 土块) ||
			(map.m_nArrMap[m_core.X][m_core.Y + 2] == 石块 || map.m_nArrMap[m_core.X - 1][m_core.Y + 2] == 石块 || map.m_nArrMap[m_core.X + 1][m_core.Y + 2] == 石块) ||
			(map.m_nArrMap[m_core.X][m_core.Y + 2] == 河流 || map.m_nArrMap[m_core.X - 1][m_core.Y + 2] == 河流 || map.m_nArrMap[m_core.X + 1][m_core.Y + 2] == 河流))
		{
			return true;
		}
		//是否遇到我家泉水
		if (map.m_nArrMap[this->m_core.X][this->m_core.Y] == 泉水)
		{
			return true;
		}
		//是否撞我方坦克
		for (int i = 0; i < MY_TANK_AMOUNT; i++)
		{
			//若是我坦，则跳过自己
			if (m_who != 敌方坦克)
			{
				if (this->m_core.X == pMyTank[i].m_core.X && this->m_core.Y == pMyTank[i].m_core.Y)//排除自己
					continue;
			}
			// 若此坦克死亡，则不阻挡
			if (pMyTank[i].m_isAlive == false) continue;
			if (
				((this->m_core.X == pMyTank[i].m_core.X - 0) && (pMyTank[i].m_core.Y - this->m_core.Y == 3)) ||
				((this->m_core.X == pMyTank[i].m_core.X - 1) && (pMyTank[i].m_core.Y - this->m_core.Y == 3)) ||
				((this->m_core.X == pMyTank[i].m_core.X - 2) && (pMyTank[i].m_core.Y - this->m_core.Y == 3)) ||
				((this->m_core.X == pMyTank[i].m_core.X + 1) && (pMyTank[i].m_core.Y - this->m_core.Y == 3)) ||
				((this->m_core.X == pMyTank[i].m_core.X + 2) && (pMyTank[i].m_core.Y - this->m_core.Y == 3))
				)
			{
				return true;
			}
		}
		//是否撞其他敌方坦克
		for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
		{
			//若是敌坦，则跳过自己
			if (m_who == 敌方坦克)
			{
				if (this->m_core.X == pEnemyTank[i].m_core.X && this->m_core.Y == pEnemyTank[i].m_core.Y)//排除自己
					continue;
			}
			// 若此坦克死亡，则不阻挡
			if (pEnemyTank[i].m_isAlive == false) continue;
			if (
				((this->m_core.X == pEnemyTank[i].m_core.X) && (pEnemyTank[i].m_core.Y - this->m_core.Y == 3)) ||
				((this->m_core.X == pEnemyTank[i].m_core.X - 1) && (pEnemyTank[i].m_core.Y - this->m_core.Y == 3)) ||
				((this->m_core.X == pEnemyTank[i].m_core.X - 2) && (pEnemyTank[i].m_core.Y - this->m_core.Y == 3)) ||
				((this->m_core.X == pEnemyTank[i].m_core.X + 1) && (pEnemyTank[i].m_core.Y - this->m_core.Y == 3)) ||
				((this->m_core.X == pEnemyTank[i].m_core.X + 2) && (pEnemyTank[i].m_core.Y - this->m_core.Y == 3))
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
		if ((map.m_nArrMap[m_core.X - 2][m_core.Y] == 土块 || map.m_nArrMap[m_core.X - 2][m_core.Y - 1] == 土块 || map.m_nArrMap[m_core.X - 2][m_core.Y + 1] == 土块) ||
			(map.m_nArrMap[m_core.X - 2][m_core.Y] == 石块 || map.m_nArrMap[m_core.X - 2][m_core.Y - 1] == 石块 || map.m_nArrMap[m_core.X - 2][m_core.Y + 1] == 石块) ||
			(map.m_nArrMap[m_core.X - 2][m_core.Y] == 河流 || map.m_nArrMap[m_core.X - 2][m_core.Y - 1] == 河流 || map.m_nArrMap[m_core.X - 2][m_core.Y + 1] == 河流))
		{
			return true;
		}
		//是否遇到我家泉水
		if (map.m_nArrMap[this->m_core.X][this->m_core.Y] == 泉水)
		{
			return true;
		}
		//是否撞我方坦克
		for (int i = 0; i < MY_TANK_AMOUNT; i++)
		{
			//若是我坦，则跳过自己
			if (m_who != 敌方坦克)
			{
				if (this->m_core.X == pMyTank[i].m_core.X && this->m_core.Y == pMyTank[i].m_core.Y)//排除自己
					continue;
			}
			// 若此坦克死亡，则不阻挡
			if (pMyTank[i].m_isAlive == false) continue;
			if (
				((this->m_core.Y == pMyTank[i].m_core.Y - 0) && (this->m_core.X - pMyTank[i].m_core.X == 3)) ||
				((this->m_core.Y == pMyTank[i].m_core.Y - 1) && (this->m_core.X - pMyTank[i].m_core.X == 3)) ||
				((this->m_core.Y == pMyTank[i].m_core.Y - 2) && (this->m_core.X - pMyTank[i].m_core.X == 3)) ||
				((this->m_core.Y == pMyTank[i].m_core.Y + 1) && (this->m_core.X - pMyTank[i].m_core.X == 3)) ||
				((this->m_core.Y == pMyTank[i].m_core.Y + 2) && (this->m_core.X - pMyTank[i].m_core.X == 3))
				)
			{
				return true;
			}
		}
		//是否撞其他敌方坦克
		for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
		{
			//若是敌坦，则跳过自己
			if (m_who == 敌方坦克)
			{
				if (this->m_core.X == pEnemyTank[i].m_core.X && this->m_core.Y == pEnemyTank[i].m_core.Y)//排除自己
					continue;
			}
			// 若此坦克死亡，则不阻挡
			if (pEnemyTank[i].m_isAlive == false) continue;
			if (
				((this->m_core.Y == pEnemyTank[i].m_core.Y) && (this->m_core.X - pEnemyTank[i].m_core.X == 3)) ||
				((this->m_core.Y == pEnemyTank[i].m_core.Y - 1) && (this->m_core.X - pEnemyTank[i].m_core.X == 3)) ||
				((this->m_core.Y == pEnemyTank[i].m_core.Y - 2) && (this->m_core.X - pEnemyTank[i].m_core.X == 3)) ||
				((this->m_core.Y == pEnemyTank[i].m_core.Y + 1) && (this->m_core.X - pEnemyTank[i].m_core.X == 3)) ||
				((this->m_core.Y == pEnemyTank[i].m_core.Y + 2) && (this->m_core.X - pEnemyTank[i].m_core.X == 3))
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
		if ((map.m_nArrMap[m_core.X + 2][m_core.Y] == 土块 || map.m_nArrMap[m_core.X + 2][m_core.Y - 1] == 土块 || map.m_nArrMap[m_core.X + 2][m_core.Y + 1] == 土块) ||
			(map.m_nArrMap[m_core.X + 2][m_core.Y] == 石块 || map.m_nArrMap[m_core.X + 2][m_core.Y - 1] == 石块 || map.m_nArrMap[m_core.X + 2][m_core.Y + 1] == 石块) ||
			(map.m_nArrMap[m_core.X + 2][m_core.Y] == 河流 || map.m_nArrMap[m_core.X + 2][m_core.Y - 1] == 河流 || map.m_nArrMap[m_core.X + 2][m_core.Y + 1] == 河流))
		{
			return true;
		}
		//是否遇到我家泉水
		if (map.m_nArrMap[this->m_core.X][this->m_core.Y] == 泉水)
		{
			return true;
		}
		//是否撞我方坦克
		for (int i = 0; i < MY_TANK_AMOUNT; i++)
		{
			//若是我坦，则跳过自己
			if (m_who != 敌方坦克)
			{
				if (this->m_core.X == pMyTank[i].m_core.X && this->m_core.Y == pMyTank[i].m_core.Y)//排除自己
					continue;
			}
			// 若此坦克死亡，则不阻挡
			if (pMyTank[i].m_isAlive == false) continue;
			if (
				((this->m_core.Y == pMyTank[i].m_core.Y - 0) && (pMyTank[i].m_core.X - this->m_core.X == 3)) ||
				((this->m_core.Y == pMyTank[i].m_core.Y - 1) && (pMyTank[i].m_core.X - this->m_core.X == 3)) ||
				((this->m_core.Y == pMyTank[i].m_core.Y - 2) && (pMyTank[i].m_core.X - this->m_core.X == 3)) ||
				((this->m_core.Y == pMyTank[i].m_core.Y + 1) && (pMyTank[i].m_core.X - this->m_core.X == 3)) ||
				((this->m_core.Y == pMyTank[i].m_core.Y + 2) && (pMyTank[i].m_core.X - this->m_core.X == 3))
				)
			{
				return true;
			}
		}
		//是否撞其他敌方坦克
		for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
		{
			//若是敌坦，则跳过自己
			if (m_who == 敌方坦克)
			{
				if (this->m_core.X == pEnemyTank[i].m_core.X && this->m_core.Y == pEnemyTank[i].m_core.Y)//排除自己
					continue;
			}
			// 若此坦克死亡，则不阻挡
			if (pEnemyTank[i].m_isAlive == false) continue;
			if (
				((this->m_core.Y == pEnemyTank[i].m_core.Y) && (pEnemyTank[i].m_core.X - this->m_core.X == 3)) ||
				((this->m_core.Y == pEnemyTank[i].m_core.Y - 1) && (pEnemyTank[i].m_core.X - this->m_core.X == 3)) ||
				((this->m_core.Y == pEnemyTank[i].m_core.Y - 2) && (pEnemyTank[i].m_core.X - this->m_core.X == 3)) ||
				((this->m_core.Y == pEnemyTank[i].m_core.Y + 1) && (pEnemyTank[i].m_core.X - this->m_core.X == 3)) ||
				((this->m_core.Y == pEnemyTank[i].m_core.Y + 2) && (pEnemyTank[i].m_core.X - this->m_core.X == 3))
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
	if (this->m_who != 敌方坦克)
	{
		setColor(10, 0);
		if(m_who == 我方坦克A)
			GotoxyAndPrint(this->m_core.X, this->m_core.Y, "■");//中心点
		else if(m_who == 我方坦克B)
			GotoxyAndPrint(this->m_core.X, this->m_core.Y, "□");//中心点
		for (int i = 0; i < 5; i++)//其他点
			GotoxyAndPrint(this->m_body[i].X, this->m_body[i].Y, "■");
		setColor(7, 0);
	}
	else
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