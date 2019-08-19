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
#include "Game.h"

//坦克相关
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
	if (this->isAlive == false) return;
	if (this->dir == UP)
	{
		this->body[0] = { this->core.X, this->core.Y - 1 };
		this->body[1] = { this->core.X - 1, this->core.Y };
		this->body[2] = { this->core.X + 1, this->core.Y };
		this->body[3] = { this->core.X - 1, this->core.Y + 1 };
		this->body[4] = { this->core.X + 1, this->core.Y + 1 };
	}
	else if (this->dir == DOWN)
	{
		this->body[0] = { this->core.X, this->core.Y + 1 };
		this->body[1] = { this->core.X - 1, this->core.Y };
		this->body[2] = { this->core.X + 1, this->core.Y };
		this->body[3] = { this->core.X - 1, this->core.Y - 1 };
		this->body[4] = { this->core.X + 1, this->core.Y - 1 };
	}
	else if (this->dir == LEFT)
	{
		this->body[0] = { this->core.X - 1, this->core.Y };
		this->body[1] = { this->core.X , this->core.Y + 1 };
		this->body[2] = { this->core.X , this->core.Y - 1 };
		this->body[3] = { this->core.X + 1, this->core.Y + 1 };
		this->body[4] = { this->core.X + 1, this->core.Y - 1 };
	}
	else if (this->dir == RIGHT)
	{
		this->body[0] = { this->core.X + 1, this->core.Y };
		this->body[1] = { this->core.X , this->core.Y + 1 };
		this->body[2] = { this->core.X , this->core.Y - 1 };
		this->body[3] = { this->core.X - 1, this->core.Y + 1 };
		this->body[4] = { this->core.X - 1, this->core.Y - 1 };
	}
}

void CTank::ManipulateMyTank(CTank * penemytank)
{
	if (this->isAlive == false) return;
	if (this->m_who == 我方坦克)
	{
		char ch = 0;
		if (_kbhit())				//非阻塞函数 
		{
			ch = _getch();			//无回显接受输入
			switch (ch)
			{
			case 'w':
				if (!this->IsMyTankMeetOther(UP, penemytank))
					this->core.Y--;
				this->dir = UP;
				break;
			case 's':
				if (!this->IsMyTankMeetOther(DOWN, penemytank))
					this->core.Y++;
				this->dir = DOWN;
				break;
			case 'a':
				if (!this->IsMyTankMeetOther(LEFT, penemytank))
					this->core.X--;
				this->dir = LEFT;
				break;
			case 'd':
				if (!this->IsMyTankMeetOther(RIGHT, penemytank))
					this->core.X++;
				this->dir = RIGHT;
				break;
			case ' ':
				if (this->bullet.state != 已赋值)
					this->bullet.state = 未赋值;//已赋值即在跑时，再开火，不可赋值为1，应该消失为0时，按键才生效
				break;
			case 'q':
			//{
			//	//暂停及恢复
			//	mciSendString("pause bgm", NULL, 0, NULL);	//暂停bgm
			//	setColor(12, 0);
			//	GotoxyAndPrint(MAP_X / 2 - 14, 1, "       ");//先把较长的running清空
			//	GotoxyAndPrint(MAP_X / 2 - 14, 1, "PAUSE");
			//	GotoxyAndPrint(MAP_X / 2 - 14, 2, "1. 回到游戏");
			//	GotoxyAndPrint(MAP_X / 2 - 14, 3, "2. 退出游戏");
			//	char tmp;
			//	do
			//	{
			//		tmp = _getch();	//利用阻塞函数暂停游戏
			//	} while (!(tmp == '1' || tmp == '2' || tmp == '3'));//只有输入123才可
			//	switch (tmp)
			//	{
			//	case '1'://恢复游戏
			//	{
			//		mciSendString("resume bgm", NULL, 0, NULL);//恢复bgm
			//		GotoxyAndPrint(MAP_X / 2 - 14, 1, "RUNNING");
			//		GotoxyAndPrint(MAP_X / 2 - 14, 2, "Q: 暂停游戏");
			//		GotoxyAndPrint(MAP_X / 2 - 14, 3, "           ");
			//		GotoxyAndPrint(MAP_X / 2 - 14, 4, "           ");
			//		break;
			//	}
			//	case '2'://退出游戏
			//	{
			//		GotoxyAndPrint(MAP_X / 2 - 14, 1, "想如何退出?");
			//		GotoxyAndPrint(MAP_X / 2 - 14, 2, "1. 保存退出");
			//		GotoxyAndPrint(MAP_X / 2 - 14, 3, "2. 直接退出");
			//		char op = _getch();
			//		if (op == '1')		//保存退出
			//		{
			//			SaveGame(this, penemytank);
			//			GameOver(penemytank);
			//			g_isRunning = false;
			//			break;
			//		}
			//		else if (op == '2')	//直接退出
			//		{
			//			GameOver(penemytank);
			//			g_isRunning = false;
			//			break;
			//		}
			//	}
			//	default:
			//		break;
			//	}
			//	break;
			//}

			default:
				break;
			}
		}
	}
	SetTankShape();//每次移动后都要重新设置形态
}

bool CTank::IsMyTankMeetOther(int dir, CTank * penemytank)
{
	switch (dir)
	{
	case UP:
		//是否撞边界
		if (this->core.Y <= 2)
		{
			return true;
		}
		//是否撞障碍物
		if ((g_MAP[this->core.X][this->core.Y - 2] == 土块障碍 ||
			g_MAP[this->core.X - 1][this->core.Y - 2] == 土块障碍 ||
			g_MAP[this->core.X + 1][this->core.Y - 2] == 土块障碍) ||
			(g_MAP[this->core.X][this->core.Y - 2] == 石块障碍 ||
			g_MAP[this->core.X - 1][this->core.Y - 2] == 石块障碍 ||
			g_MAP[this->core.X + 1][this->core.Y - 2] == 石块障碍))
		{
			return true;
		}
		//是否撞敌方坦克
		for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
		{
			if (penemytank[i].isAlive == false) continue;
			if (
				((this->core.X == penemytank[i].core.X) && (this->core.Y - penemytank[i].core.Y == 3)) ||
				((this->core.X == penemytank[i].core.X - 1) && (this->core.Y - penemytank[i].core.Y == 3)) ||
				((this->core.X == penemytank[i].core.X - 2) && (this->core.Y - penemytank[i].core.Y == 3)) ||
				((this->core.X == penemytank[i].core.X + 1) && (this->core.Y - penemytank[i].core.Y == 3)) ||
				((this->core.X == penemytank[i].core.X + 2) && (this->core.Y - penemytank[i].core.Y == 3))
				)//要==3,而非<=，只有在挨着的时候可被当，如果小于，虽没挨着敌坦1，但距离却小于2，被2干扰
			{
				return true;
			}
		}
		break;
	case DOWN:
		//是否撞边界
		if (this->core.Y >= MAP_Y - 3)
		{
			return true;
		}
		//是否撞障碍物
		if ((g_MAP[this->core.X][this->core.Y + 2] == 土块障碍 ||
			g_MAP[this->core.X - 1][this->core.Y + 2] == 土块障碍 ||
			g_MAP[this->core.X + 1][this->core.Y + 2] == 土块障碍) ||
			(g_MAP[this->core.X][this->core.Y + 2] == 石块障碍 ||
				g_MAP[this->core.X - 1][this->core.Y + 2] == 石块障碍 ||
				g_MAP[this->core.X + 1][this->core.Y + 2] == 石块障碍))
		{
			return true;
		}
		//是否遇到我家泉水
		if (g_MAP[this->core.X][this->core.Y] == 我家泉水)
		{
			return true;
		}
		//是否撞敌方坦克
		for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
		{
			if (penemytank[i].isAlive == false) continue;
			if (
				((this->core.X == penemytank[i].core.X) && (penemytank[i].core.Y - this->core.Y == 3)) ||
				((this->core.X == penemytank[i].core.X - 1) && (penemytank[i].core.Y - this->core.Y == 3)) ||
				((this->core.X == penemytank[i].core.X - 2) && (penemytank[i].core.Y - this->core.Y == 3)) ||
				((this->core.X == penemytank[i].core.X + 1) && (penemytank[i].core.Y - this->core.Y == 3)) ||
				((this->core.X == penemytank[i].core.X + 2) && (penemytank[i].core.Y - this->core.Y == 3))
				)
			{
				return true;
			}
		}
		break;
	case LEFT:
		//是否撞边界
		if (this->core.X <= 2)
		{
			return true;
		}
		//是否撞障碍物
		if ((g_MAP[this->core.X - 2][this->core.Y] == 土块障碍 ||
			g_MAP[this->core.X - 2][this->core.Y - 1] == 土块障碍 ||
			g_MAP[this->core.X - 2][this->core.Y + 1] == 土块障碍) ||
			(g_MAP[this->core.X - 2][this->core.Y] == 石块障碍 ||
				g_MAP[this->core.X - 2][this->core.Y - 1] == 石块障碍 ||
				g_MAP[this->core.X - 2][this->core.Y + 1] == 石块障碍))
		{
			return true;
		}
		//是否遇到我家泉水
		if (g_MAP[this->core.X][this->core.Y] == 我家泉水)
		{
			return true;
		}
		//是否撞敌方坦克
		for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
		{
			if (penemytank[i].isAlive == false) continue;
			if (
				((this->core.Y == penemytank[i].core.Y) && (this->core.X - penemytank[i].core.X == 3)) ||
				((this->core.Y == penemytank[i].core.Y - 1) && (this->core.X - penemytank[i].core.X == 3)) ||
				((this->core.Y == penemytank[i].core.Y - 2) && (this->core.X - penemytank[i].core.X == 3)) ||
				((this->core.Y == penemytank[i].core.Y + 1) && (this->core.X - penemytank[i].core.X == 3)) ||
				((this->core.Y == penemytank[i].core.Y + 2) && (this->core.X - penemytank[i].core.X == 3))
				)
			{
				return true;
			}
		}
		break;
	case RIGHT:
		//是否撞边界
		if (this->core.X >= MAP_X_WALL / 2 - 2)
		{
			return true;
		}
		//是否撞障碍物
		if ((g_MAP[this->core.X + 2][this->core.Y] == 土块障碍 ||
			g_MAP[this->core.X + 2][this->core.Y - 1] == 土块障碍 ||
			g_MAP[this->core.X + 2][this->core.Y + 1] == 土块障碍) ||
			(g_MAP[this->core.X + 2][this->core.Y] == 石块障碍 ||
				g_MAP[this->core.X + 2][this->core.Y - 1] == 石块障碍 ||
				g_MAP[this->core.X + 2][this->core.Y + 1] == 石块障碍))
		{
			return true;
		}
		//是否遇到我家泉水
		if (g_MAP[this->core.X][this->core.Y] == 我家泉水)
		{
			return true;
		}
		//是否撞敌方坦克
		for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
		{
			if (penemytank[i].isAlive == false) continue;
			if (
				((this->core.Y == penemytank[i].core.Y) && (penemytank[i].core.X - this->core.X == 3)) ||
				((this->core.Y == penemytank[i].core.Y - 1) && (penemytank[i].core.X - this->core.X == 3)) ||
				((this->core.Y == penemytank[i].core.Y - 2) && (penemytank[i].core.X - this->core.X == 3)) ||
				((this->core.Y == penemytank[i].core.Y + 1) && (penemytank[i].core.X - this->core.X == 3)) ||
				((this->core.Y == penemytank[i].core.Y + 2) && (penemytank[i].core.X - this->core.X == 3))
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

void CTank::ManipulateEneTank(CTank pmytank, CTank* penemytank)
{
	if (this->isAlive == false) return;
	if (this->m_who == 敌方坦克)
	{
		switch (rand() % 5)
		{
		case UP:
			if (!this->IsEneTankMeetOther( UP, pmytank, penemytank))
				this->core.Y--;
			this->dir = UP;
			break;
		case DOWN:
			if (!this->IsEneTankMeetOther( DOWN, pmytank, penemytank))
				this->core.Y++;
			this->dir = DOWN;
			break;
		case LEFT:
			if (!this->IsEneTankMeetOther(LEFT, pmytank, penemytank))
				this->core.X--;
			this->dir = LEFT;
			break;
		case RIGHT:
			if (!this->IsEneTankMeetOther(RIGHT, pmytank, penemytank))
				this->core.X++;
			this->dir = RIGHT;
			break;
		case 4:
			if (this->bullet.state != 已赋值)
				this->bullet.state = 未赋值;
			break;
		default:
			break;
		}
	}
	SetTankShape();//每次移动后都要重新设置形态
}

bool CTank::IsEneTankMeetOther(int dir, CTank pmytank, CTank* penemytank)
{
	switch (dir)
	{
	case UP:
		//是否撞边界
		if (this->core.Y <= 2)
		{
			return true;
		}
		//是否撞障碍物
		if ((g_MAP[this->core.X][this->core.Y - 2] == 土块障碍 ||
			g_MAP[this->core.X - 1][this->core.Y - 2] == 土块障碍 ||
			g_MAP[this->core.X + 1][this->core.Y - 2] == 土块障碍) ||
			(g_MAP[this->core.X][this->core.Y - 2] == 石块障碍 ||
				g_MAP[this->core.X - 1][this->core.Y - 2] == 石块障碍 ||
				g_MAP[this->core.X + 1][this->core.Y - 2] == 石块障碍))
		{
			return true;
		}
		//是否撞我方坦克
		if (
			((this->core.X == pmytank.core.X - 0) && (this->core.Y - pmytank.core.Y == 3)) ||
			((this->core.X == pmytank.core.X - 1) && (this->core.Y - pmytank.core.Y == 3)) ||
			((this->core.X == pmytank.core.X - 2) && (this->core.Y - pmytank.core.Y == 3)) ||
			((this->core.X == pmytank.core.X + 1) && (this->core.Y - pmytank.core.Y == 3)) ||
			((this->core.X == pmytank.core.X + 2) && (this->core.Y - pmytank.core.Y == 3))
			)//要==3,而非<=，只有在挨着的时候可被当，如果小于，虽没挨着敌坦1，但距离却小于2，被2干扰
		{
			return true;
		}
		//是否撞其他敌方坦克
		for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
		{
			if (this->core.X == penemytank[i].core.X && this->core.Y == penemytank[i].core.Y)//排除自己
				continue;
			if (
				((this->core.X == penemytank[i].core.X) && (this->core.Y - penemytank[i].core.Y == 3)) ||
				((this->core.X == penemytank[i].core.X - 1) && (this->core.Y - penemytank[i].core.Y == 3)) ||
				((this->core.X == penemytank[i].core.X - 2) && (this->core.Y - penemytank[i].core.Y == 3)) ||
				((this->core.X == penemytank[i].core.X + 1) && (this->core.Y - penemytank[i].core.Y == 3)) ||
				((this->core.X == penemytank[i].core.X + 2) && (this->core.Y - penemytank[i].core.Y == 3))
				)//要==3,而非<=，只有在挨着的时候可被当，如果小于，虽没挨着敌坦1，但距离却小于2，被2干扰
			{
				return true;
			}
		}
		break;
	case DOWN:
		//是否撞边界
		if (this->core.Y >= MAP_Y - 3)
		{
			return true;
		}
		//是否撞障碍物
		if ((g_MAP[this->core.X][this->core.Y + 2] == 土块障碍 ||
			g_MAP[this->core.X - 1][this->core.Y + 2] == 土块障碍 ||
			g_MAP[this->core.X + 1][this->core.Y + 2] == 土块障碍) ||
			(g_MAP[this->core.X][this->core.Y + 2] == 石块障碍 ||
				g_MAP[this->core.X - 1][this->core.Y + 2] == 石块障碍 ||
				g_MAP[this->core.X + 1][this->core.Y + 2] == 石块障碍))
		{
			return true;
		}
		//是否遇到我家泉水
		if (g_MAP[this->core.X][this->core.Y] == 我家泉水)
		{
			return true;
		}
		//是否撞我方坦克
		if (
			((this->core.X == pmytank.core.X - 0) && (pmytank.core.Y - this->core.Y == 3)) ||
			((this->core.X == pmytank.core.X - 1) && (pmytank.core.Y - this->core.Y == 3)) ||
			((this->core.X == pmytank.core.X - 2) && (pmytank.core.Y - this->core.Y == 3)) ||
			((this->core.X == pmytank.core.X + 1) && (pmytank.core.Y - this->core.Y == 3)) ||
			((this->core.X == pmytank.core.X + 2) && (pmytank.core.Y - this->core.Y == 3))
			)
		{
			return true;
		}
		//是否撞其他敌方坦克
		for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
		{
			if (this->core.X == penemytank[i].core.X && this->core.Y == penemytank[i].core.Y)//排除自己
				continue;
			if (
				((this->core.X == penemytank[i].core.X) && (penemytank[i].core.Y - this->core.Y == 3)) ||
				((this->core.X == penemytank[i].core.X - 1) && (penemytank[i].core.Y - this->core.Y == 3)) ||
				((this->core.X == penemytank[i].core.X - 2) && (penemytank[i].core.Y - this->core.Y == 3)) ||
				((this->core.X == penemytank[i].core.X + 1) && (penemytank[i].core.Y - this->core.Y == 3)) ||
				((this->core.X == penemytank[i].core.X + 2) && (penemytank[i].core.Y - this->core.Y == 3))
				)
			{
				return true;
			}
		}
		break;
	case LEFT:
		//是否撞边界
		if (this->core.X <= 2)
		{
			return true;
		}
		//是否撞障碍物
		if ((g_MAP[this->core.X - 2][this->core.Y] == 土块障碍 ||
			g_MAP[this->core.X - 2][this->core.Y - 1] == 土块障碍 ||
			g_MAP[this->core.X - 2][this->core.Y + 1] == 土块障碍) ||
			(g_MAP[this->core.X - 2][this->core.Y] == 石块障碍 ||
				g_MAP[this->core.X - 2][this->core.Y - 1] == 石块障碍 ||
				g_MAP[this->core.X - 2][this->core.Y + 1] == 石块障碍))
		{
			return true;
		}
		//是否遇到我家泉水
		if (g_MAP[this->core.X][this->core.Y] == 我家泉水)
		{
			return true;
		}
		//是否撞我方坦克
		if (
			((this->core.Y == pmytank.core.Y - 0) && (this->core.X - pmytank.core.X == 3)) ||
			((this->core.Y == pmytank.core.Y - 1) && (this->core.X - pmytank.core.X == 3)) ||
			((this->core.Y == pmytank.core.Y - 2) && (this->core.X - pmytank.core.X == 3)) ||
			((this->core.Y == pmytank.core.Y + 1) && (this->core.X - pmytank.core.X == 3)) ||
			((this->core.Y == pmytank.core.Y + 2) && (this->core.X - pmytank.core.X == 3))
			)
		{
			return true;
		}
		//是否撞其他敌方坦克
		for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
		{
			if (this->core.X == penemytank[i].core.X && this->core.Y == penemytank[i].core.Y)//排除自己
				continue;
			if (
				((this->core.Y == penemytank[i].core.Y) && (this->core.X - penemytank[i].core.X == 3)) ||
				((this->core.Y == penemytank[i].core.Y - 1) && (this->core.X - penemytank[i].core.X == 3)) ||
				((this->core.Y == penemytank[i].core.Y - 2) && (this->core.X - penemytank[i].core.X == 3)) ||
				((this->core.Y == penemytank[i].core.Y + 1) && (this->core.X - penemytank[i].core.X == 3)) ||
				((this->core.Y == penemytank[i].core.Y + 2) && (this->core.X - penemytank[i].core.X == 3))
				)
			{
				return true;
			}
		}
		break;
	case RIGHT:
		//是否撞边界
		if (this->core.X >= MAP_X_WALL / 2 - 2)
		{
			return true;
		}
		//是否撞障碍物
		if ((g_MAP[this->core.X + 2][this->core.Y] == 土块障碍 ||
			g_MAP[this->core.X + 2][this->core.Y - 1] == 土块障碍 ||
			g_MAP[this->core.X + 2][this->core.Y + 1] == 土块障碍) ||
			(g_MAP[this->core.X + 2][this->core.Y] == 石块障碍 ||
				g_MAP[this->core.X + 2][this->core.Y - 1] == 石块障碍 ||
				g_MAP[this->core.X + 2][this->core.Y + 1] == 石块障碍))
		{
			return true;
		}
		//是否遇到我家泉水
		if (g_MAP[this->core.X][this->core.Y] == 我家泉水)
		{
			return true;
		}
		//是否撞我方坦克
		if (
			((this->core.Y == pmytank.core.Y - 0) && (pmytank.core.X - this->core.X == 3)) ||
			((this->core.Y == pmytank.core.Y - 1) && (pmytank.core.X - this->core.X == 3)) ||
			((this->core.Y == pmytank.core.Y - 2) && (pmytank.core.X - this->core.X == 3)) ||
			((this->core.Y == pmytank.core.Y + 1) && (pmytank.core.X - this->core.X == 3)) ||
			((this->core.Y == pmytank.core.Y + 2) && (pmytank.core.X - this->core.X == 3))
			)
		{
			return true;
		}
		//是否撞其他敌方坦克
		for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
		{
			if (this->core.X == penemytank[i].core.X && this->core.Y == penemytank[i].core.Y)//排除自己
				continue;
			if (
				((this->core.Y == penemytank[i].core.Y) && (penemytank[i].core.X - this->core.X == 3)) ||
				((this->core.Y == penemytank[i].core.Y - 1) && (penemytank[i].core.X - this->core.X == 3)) ||
				((this->core.Y == penemytank[i].core.Y - 2) && (penemytank[i].core.X - this->core.X == 3)) ||
				((this->core.Y == penemytank[i].core.Y + 1) && (penemytank[i].core.X - this->core.X == 3)) ||
				((this->core.Y == penemytank[i].core.Y + 2) && (penemytank[i].core.X - this->core.X == 3))
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

int GetLiveEnemyAmount(CTank* penemytank)
{
	int count = 0;
	for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
	{
		if (penemytank[i].isAlive == true)
			count++;
	}
	return count;
}