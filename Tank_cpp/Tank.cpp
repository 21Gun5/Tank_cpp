#include <conio.h>
#include "Tank.h"
#include "Map.h"
#include "Game.h"

//坦克相关
CTank::CTank(COORD core, enum direction dir, int blood, int who,int power)
{
	m_core = core;
	m_dir = dir;
	m_blood = blood;
	m_isAlive = true;
	m_who = who;
	m_isHided = false;//默认非隐藏的
	m_power = power;
	SetTankShape();
}

void CTank::CleanTankTail(COORD oldCore, PCOORD oldBody)
{
	//if (this->m_isAlive == false) return;//不加在草丛里死亡后一直闪，加了后尸体不消失，综合，还是不加
	GotoxyAndPrint(oldCore.X, oldCore.Y, "  ");//中心点
	for (int i = 0; i < 5; i++)//其他点
		GotoxyAndPrint(oldBody[i].X, oldBody[i].Y, "  ");
}
void CTank::SetTankShape()
{
	//if (this->m_isAlive == false) return;

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

void CTank::ManipulateTank(vector<CTank>& myTank, vector<CTank>& enemyTank, CMap map, CGame& game)
{
	//if (this->m_isAlive == false) return;
	if (this->m_who == 我方坦克A)
	{
		if (KEYDOWN('W'))//小写不可，可大写和ASCII码
		{
			if (!this->IsTankMeetOther(UP, myTank, enemyTank, map))
				this->m_core.Y--;
			this->m_dir = UP;
		}
		else if (KEYDOWN('S'))
		{
			if (!this->IsTankMeetOther(DOWN, myTank, enemyTank, map))
				this->m_core.Y++;
			this->m_dir = DOWN;
		}
		else if (KEYDOWN('A'))
		{
			if (!this->IsTankMeetOther(LEFT, myTank, enemyTank, map))

				this->m_core.X--;
			this->m_dir = LEFT;
		}
		else if (KEYDOWN('D'))
		{
			if (!this->IsTankMeetOther(RIGHT, myTank, enemyTank, map))

				this->m_core.X++;
			this->m_dir = RIGHT;
		}
		else if (KEYDOWN(' '))
		{
			// 非隐藏状态才可开火
			if (!m_isHided)
			{
				if (this->m_bullet.m_state != 已赋值)
				{
					this->m_bullet.m_state = 未赋值;//已赋值即在跑时，再开火，不可赋值为1，应该消失为0时，按键才生效
				}
			}
		}
		else if (KEYDOWN('Q'))
		{
			//暂停及恢复
			mciSendString("pause bgm", NULL, 0, NULL);	//暂停bgm
			GotoxyAndPrint(MAP_X_WALL / 2 + 1, 1, "       ");//先把较长的running清空
			GotoxyAndPrint(MAP_X_WALL / 2 + 1, 1, "PAUSE", 提示颜色);
			GotoxyAndPrint(MAP_X_WALL / 2 + 1, 2, "1. 回到游戏", 提示颜色);
			GotoxyAndPrint(MAP_X_WALL / 2 + 1, 3, "2. 退出游戏", 提示颜色);
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
				GotoxyAndPrint(MAP_X_WALL / 2 + 1, 1, "RUNNING", 提示颜色);
				GotoxyAndPrint(MAP_X_WALL / 2 + 1, 2, "Q: 暂停游戏", 提示颜色);
				GotoxyAndPrint(MAP_X_WALL / 2 + 1, 3, "           ");
				GotoxyAndPrint(MAP_X_WALL / 2 + 1, 4, "           ");
				break;
			}
			case '2'://退出游戏
			{
				GotoxyAndPrint(MAP_X_WALL / 2 + 1, 1, "想如何退出?", 提示颜色);
				GotoxyAndPrint(MAP_X_WALL / 2 + 1, 2, "1. 保存退出", 提示颜色);
				GotoxyAndPrint(MAP_X_WALL / 2 + 1, 3, "2. 直接退出", 提示颜色);
				char op = _getch();
				if (op == '1')		//保存退出
				{
					game.SaveGameFile(myTank, enemyTank, map);
					game.GameOver(enemyTank);
					game.m_isRunning = false;
					break;
				}
				else if (op == '2')	//直接退出
				{
					game.GameOver(enemyTank);
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
			if (!this->IsTankMeetOther(UP, myTank, enemyTank, map))
				this->m_core.Y--;
			this->m_dir = UP;
		}
		else if (KEYDOWN('K'))
		{
			if (!this->IsTankMeetOther(DOWN, myTank, enemyTank, map))
				this->m_core.Y++;
			this->m_dir = DOWN;
		}
		else if (KEYDOWN('J'))
		{
			if (!this->IsTankMeetOther(LEFT, myTank, enemyTank, map))

				this->m_core.X--;
			this->m_dir = LEFT;
		}
		else if (KEYDOWN('L'))
		{
			if (!this->IsTankMeetOther(RIGHT, myTank, enemyTank, map))

				this->m_core.X++;
			this->m_dir = RIGHT;
		}
		else if (KEYDOWN('H'))
		{
			// 非隐藏状态才可开火
			if (!m_isHided)
			{
				if (this->m_bullet.m_state != 已赋值)
				{
					this->m_bullet.m_state = 未赋值;//已赋值即在跑时，再开火，不可赋值为1，应该消失为0时，按键才生效
				}
			}
		}
	}
	else if (this->m_who == 敌方坦克)
	{
		//switch (rand() % 5)
		switch (4)
		{
		case UP:
			if (!this->IsTankMeetOther(UP, myTank, enemyTank, map))
				this->m_core.Y--;
			this->m_dir = UP;
			break;
		case DOWN:
			if (!this->IsTankMeetOther(DOWN, myTank, enemyTank, map))
				this->m_core.Y++;
			this->m_dir = DOWN;
			break;
		case LEFT:
			if (!this->IsTankMeetOther(LEFT, myTank, enemyTank, map))
				this->m_core.X--;
			this->m_dir = LEFT;
			break;
		case RIGHT:
			if (!this->IsTankMeetOther(RIGHT, myTank, enemyTank, map))
				this->m_core.X++;
			this->m_dir = RIGHT;
			break;
		case 4:
			// 非隐藏状态才可开火
			if (!m_isHided)
			{
				if (this->m_bullet.m_state != 已赋值)
				{
					this->m_bullet.m_state = 未赋值;//已赋值即在跑时，再开火，不可赋值为1，应该消失为0时，按键才生效
				}
			}
			break;
		default:
			break;
		}
	}

	SetTankShape();//每次移动后都要重新设置形态
}

bool CTank::IsTankMeetOther(int dir, vector<CTank>& myTank, vector<CTank>& enemyTank, CMap map)
{
	switch (dir)
	{
	case UP:
		//遇边界
		if (this->m_core.Y <= 2)
		{
			return true;
		}
		//遇河流等不可通过障碍
		if ((map.m_nArrMap[m_core.X][m_core.Y - 2] == 土块 || map.m_nArrMap[m_core.X - 1][m_core.Y - 2] == 土块 || map.m_nArrMap[m_core.X + 1][m_core.Y - 2] == 土块) ||
			(map.m_nArrMap[m_core.X][m_core.Y - 2] == 石块 || map.m_nArrMap[m_core.X - 1][m_core.Y - 2] == 石块 || map.m_nArrMap[m_core.X + 1][m_core.Y - 2] == 石块) ||
			(map.m_nArrMap[m_core.X][m_core.Y - 2] == 河流 || map.m_nArrMap[m_core.X - 1][m_core.Y - 2] == 河流 || map.m_nArrMap[m_core.X + 1][m_core.Y - 2] == 河流))
		{
			return true;
		}
		//进草丛可隐藏
		if (map.m_nArrMap[m_core.X][m_core.Y ] == 草丛 || map.m_nArrMap[m_core.X - 1][m_core.Y ] == 草丛 || map.m_nArrMap[m_core.X + 1][m_core.Y ] == 草丛)
		{
			
			m_isHided = true;
		}
		// 出草丛则显示（if 与else if 还是有区别的，被坑了
		if (map.m_nArrMap[m_core.X][m_core.Y -2] == 空地 || map.m_nArrMap[m_core.X - 1][m_core.Y -2] == 空地 || map.m_nArrMap[m_core.X + 1][m_core.Y -2] == 空地)
		{
			
			m_isHided = false;
		}

		//遇我方坦克
		for (vector<CTank>::iterator it = myTank.begin(); it != myTank.end(); it++)
		//for (int i = 0; i < MY_TANK_AMOUNT; i++)
		{
			//若是我坦，则跳过自己
			if (m_who != 敌方坦克)
			{
				if (this->m_core.X == it->m_core.X && this->m_core.Y == it->m_core.Y)//排除自己
					continue;
			}
			// 若此坦克死亡，则不阻挡
			//if (it->m_isAlive == false) continue;
			if (
				((this->m_core.X == it->m_core.X - 0) && (this->m_core.Y - it->m_core.Y == 3)) ||
				((this->m_core.X == it->m_core.X - 1) && (this->m_core.Y - it->m_core.Y == 3)) ||
				((this->m_core.X == it->m_core.X - 2) && (this->m_core.Y - it->m_core.Y == 3)) ||
				((this->m_core.X == it->m_core.X + 1) && (this->m_core.Y - it->m_core.Y == 3)) ||
				((this->m_core.X == it->m_core.X + 2) && (this->m_core.Y - it->m_core.Y == 3))
				)//要==3,而非<=，只有在挨着的时候可被当，如果小于，虽没挨着敌坦1，但距离却小于2，被2干扰
			{
				return true;
			}
		}
		//遇敌方坦克
		for (vector<CTank>::iterator it = enemyTank.begin(); it != enemyTank.end(); it++)
		{
			//若是敌坦，则跳过自己
			if (m_who == 敌方坦克)
			{
				if (this->m_core.X == it->m_core.X && this->m_core.Y == it->m_core.Y)//排除自己
					continue;
			}
			// 若此坦克死亡，则不阻挡
			//if (it->m_isAlive == false) continue;
			if (
				((this->m_core.X == it->m_core.X) && (this->m_core.Y - it->m_core.Y == 3)) ||
				((this->m_core.X == it->m_core.X - 1) && (this->m_core.Y - it->m_core.Y == 3)) ||
				((this->m_core.X == it->m_core.X - 2) && (this->m_core.Y - it->m_core.Y == 3)) ||
				((this->m_core.X == it->m_core.X + 1) && (this->m_core.Y - it->m_core.Y == 3)) ||
				((this->m_core.X == it->m_core.X + 2) && (this->m_core.Y - it->m_core.Y == 3))
				)//要==3,而非<=，只有在挨着的时候可被当，如果小于，虽没挨着敌坦1，但距离却小于2，被2干扰
			{
				return true;
			}
		}
		break;
	case DOWN:
		//遇边界
		if (this->m_core.Y >= MAP_Y - 3)
		{
			return true;
		}
		//遇河流等不可通过障碍
		if ((map.m_nArrMap[m_core.X][m_core.Y + 2] == 土块 || map.m_nArrMap[m_core.X - 1][m_core.Y + 2] == 土块 || map.m_nArrMap[m_core.X + 1][m_core.Y + 2] == 土块) ||
			(map.m_nArrMap[m_core.X][m_core.Y + 2] == 石块 || map.m_nArrMap[m_core.X - 1][m_core.Y + 2] == 石块 || map.m_nArrMap[m_core.X + 1][m_core.Y + 2] == 石块) ||
			(map.m_nArrMap[m_core.X][m_core.Y + 2] == 河流 || map.m_nArrMap[m_core.X - 1][m_core.Y + 2] == 河流 || map.m_nArrMap[m_core.X + 1][m_core.Y + 2] == 河流))
		{
			return true;
		}
		
		// 进草丛可隐藏
		if (map.m_nArrMap[m_core.X][m_core.Y ] == 草丛 || map.m_nArrMap[m_core.X - 1][m_core.Y ] == 草丛 || map.m_nArrMap[m_core.X + 1][m_core.Y ] == 草丛)
		{
			
			m_isHided = true;
		}
		// 出草丛则显示
		if (map.m_nArrMap[m_core.X][m_core.Y + 2] == 空地 || map.m_nArrMap[m_core.X - 1][m_core.Y + 2] == 空地 || map.m_nArrMap[m_core.X + 1][m_core.Y + 2] == 空地)
		{
			
			m_isHided = false;
		}

		//遇泉水
		if (map.m_nArrMap[this->m_core.X][this->m_core.Y+2] == 泉水)
		{
			return true;
		}
		//遇我方坦克
		for (vector<CTank>::iterator it = myTank.begin(); it != myTank.end(); it++)
		{
			//若是我坦，则跳过自己
			if (m_who != 敌方坦克)
			{
				if (this->m_core.X == it->m_core.X && this->m_core.Y == it->m_core.Y)//排除自己
					continue;
			}
			// 若此坦克死亡，则不阻挡
			//if (it->m_isAlive == false) continue;
			if (
				((this->m_core.X == it->m_core.X - 0) && (it->m_core.Y - this->m_core.Y == 3)) ||
				((this->m_core.X == it->m_core.X - 1) && (it->m_core.Y - this->m_core.Y == 3)) ||
				((this->m_core.X == it->m_core.X - 2) && (it->m_core.Y - this->m_core.Y == 3)) ||
				((this->m_core.X == it->m_core.X + 1) && (it->m_core.Y - this->m_core.Y == 3)) ||
				((this->m_core.X == it->m_core.X + 2) && (it->m_core.Y - this->m_core.Y == 3))
				)
			{
				return true;
			}
		}
		//遇敌方坦克
		for (vector<CTank>::iterator it = enemyTank.begin(); it != enemyTank.end(); it++)
		{
			//若是敌坦，则跳过自己
			if (m_who == 敌方坦克)
			{
				if (this->m_core.X == it->m_core.X && this->m_core.Y == it->m_core.Y)//排除自己
					continue;
			}
			// 若此坦克死亡，则不阻挡
			//if (it->m_isAlive == false) continue;
			if (
				((this->m_core.X == it->m_core.X) && (it->m_core.Y - this->m_core.Y == 3)) ||
				((this->m_core.X == it->m_core.X - 1) && (it->m_core.Y - this->m_core.Y == 3)) ||
				((this->m_core.X == it->m_core.X - 2) && (it->m_core.Y - this->m_core.Y == 3)) ||
				((this->m_core.X == it->m_core.X + 1) && (it->m_core.Y - this->m_core.Y == 3)) ||
				((this->m_core.X == it->m_core.X + 2) && (it->m_core.Y - this->m_core.Y == 3))
				)
			{
				return true;
			}
		}
		break;
	case LEFT:
		//遇边界
		if (this->m_core.X <= 2)
		{
			return true;
		}
		//遇河流等不可通过障碍
		if ((map.m_nArrMap[m_core.X - 2][m_core.Y] == 土块 || map.m_nArrMap[m_core.X - 2][m_core.Y - 1] == 土块 || map.m_nArrMap[m_core.X - 2][m_core.Y + 1] == 土块) ||
			(map.m_nArrMap[m_core.X - 2][m_core.Y] == 石块 || map.m_nArrMap[m_core.X - 2][m_core.Y - 1] == 石块 || map.m_nArrMap[m_core.X - 2][m_core.Y + 1] == 石块) ||
			(map.m_nArrMap[m_core.X - 2][m_core.Y] == 河流 || map.m_nArrMap[m_core.X - 2][m_core.Y - 1] == 河流 || map.m_nArrMap[m_core.X - 2][m_core.Y + 1] == 河流))
		{
			return true;
		}

		// 进草丛可隐藏
		if (map.m_nArrMap[m_core.X ][m_core.Y] == 草丛 || map.m_nArrMap[m_core.X ][m_core.Y - 1] == 草丛 || map.m_nArrMap[m_core.X ][m_core.Y + 1] == 草丛)
		{
			
			m_isHided = true;
		}
		// 出草丛则显示
		if (map.m_nArrMap[m_core.X - 2][m_core.Y] == 空地 || map.m_nArrMap[m_core.X - 2][m_core.Y - 1] == 空地 || map.m_nArrMap[m_core.X - 2][m_core.Y + 1] == 空地)
		{
			m_isHided = false;
		}

		//遇泉水
		if (map.m_nArrMap[this->m_core.X-2][this->m_core.Y] == 泉水)
		{
			return true;
		}
		//遇我方坦克
		for (vector<CTank>::iterator it = myTank.begin(); it != myTank.end(); it++)
		{
			//若是我坦，则跳过自己
			if (m_who != 敌方坦克)
			{
				if (this->m_core.X == it->m_core.X && this->m_core.Y == it->m_core.Y)//排除自己
					continue;
			}
			// 若此坦克死亡，则不阻挡
			//if (it->m_isAlive == false) continue;
			if (
				((this->m_core.Y == it->m_core.Y - 0) && (this->m_core.X - it->m_core.X == 3)) ||
				((this->m_core.Y == it->m_core.Y - 1) && (this->m_core.X - it->m_core.X == 3)) ||
				((this->m_core.Y == it->m_core.Y - 2) && (this->m_core.X - it->m_core.X == 3)) ||
				((this->m_core.Y == it->m_core.Y + 1) && (this->m_core.X - it->m_core.X == 3)) ||
				((this->m_core.Y == it->m_core.Y + 2) && (this->m_core.X - it->m_core.X == 3))
				)
			{
				return true;
			}
		}
		//遇敌方坦克
		for (vector<CTank>::iterator it = enemyTank.begin(); it != enemyTank.end(); it++)
		//for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
		{
			//若是敌坦，则跳过自己
			if (m_who == 敌方坦克)
			{
				if (this->m_core.X == it->m_core.X && this->m_core.Y == it->m_core.Y)//排除自己
					continue;
			}
			// 若此坦克死亡，则不阻挡
			//if (it->m_isAlive == false) continue;
			if (
				((this->m_core.Y == it->m_core.Y) && (this->m_core.X - it->m_core.X == 3)) ||
				((this->m_core.Y == it->m_core.Y - 1) && (this->m_core.X - it->m_core.X == 3)) ||
				((this->m_core.Y == it->m_core.Y - 2) && (this->m_core.X - it->m_core.X == 3)) ||
				((this->m_core.Y == it->m_core.Y + 1) && (this->m_core.X - it->m_core.X == 3)) ||
				((this->m_core.Y == it->m_core.Y + 2) && (this->m_core.X - it->m_core.X == 3))
				)
			{
				return true;
			}
		}
		break;
	case RIGHT:
		//遇边界
		if (this->m_core.X >= MAP_X_WALL / 2 - 2)
		{
			return true;
		}
		//遇河流等不可通过障碍
		if ((map.m_nArrMap[m_core.X + 2][m_core.Y] == 土块 || map.m_nArrMap[m_core.X + 2][m_core.Y - 1] == 土块 || map.m_nArrMap[m_core.X + 2][m_core.Y + 1] == 土块) ||
			(map.m_nArrMap[m_core.X + 2][m_core.Y] == 石块 || map.m_nArrMap[m_core.X + 2][m_core.Y - 1] == 石块 || map.m_nArrMap[m_core.X + 2][m_core.Y + 1] == 石块) ||
			(map.m_nArrMap[m_core.X + 2][m_core.Y] == 河流 || map.m_nArrMap[m_core.X + 2][m_core.Y - 1] == 河流 || map.m_nArrMap[m_core.X + 2][m_core.Y + 1] == 河流))
		{
			return true;
		}

		// 进草丛可隐藏
		if (map.m_nArrMap[m_core.X ][m_core.Y] == 草丛 || map.m_nArrMap[m_core.X ][m_core.Y - 1] == 草丛 || map.m_nArrMap[m_core.X][m_core.Y + 1] == 草丛)
		{
			m_isHided = true;
		}
		// 出草丛则显示
		if (map.m_nArrMap[m_core.X + 2][m_core.Y] == 空地 || map.m_nArrMap[m_core.X + 2][m_core.Y - 1] == 空地 || map.m_nArrMap[m_core.X +2][m_core.Y + 1] == 空地)
		{
			m_isHided = false;
		}

		//遇泉水
		if (map.m_nArrMap[this->m_core.X+2][this->m_core.Y] == 泉水)
		{
			return true;
		}
		//遇我方坦克
		for (vector<CTank>::iterator it = myTank.begin(); it != myTank.end(); it++)
		{
			//若是我坦，则跳过自己
			if (m_who != 敌方坦克)
			{
				if (this->m_core.X == it->m_core.X && this->m_core.Y == it->m_core.Y)//排除自己
					continue;
			}
			// 若此坦克死亡，则不阻挡
			//if (it->m_isAlive == false) continue;
			if (
				((this->m_core.Y == it->m_core.Y - 0) && (it->m_core.X - this->m_core.X == 3)) ||
				((this->m_core.Y == it->m_core.Y - 1) && (it->m_core.X - this->m_core.X == 3)) ||
				((this->m_core.Y == it->m_core.Y - 2) && (it->m_core.X - this->m_core.X == 3)) ||
				((this->m_core.Y == it->m_core.Y + 1) && (it->m_core.X - this->m_core.X == 3)) ||
				((this->m_core.Y == it->m_core.Y + 2) && (it->m_core.X - this->m_core.X == 3))
				)
			{
				return true;
			}
		}
		//遇敌方坦克
		for (vector<CTank>::iterator it = enemyTank.begin(); it != enemyTank.end(); it++)
		//for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
		{
			//若是敌坦，则跳过自己
			if (m_who == 敌方坦克)
			{
				if (this->m_core.X == it->m_core.X && this->m_core.Y == it->m_core.Y)//排除自己
					continue;
			}
			// 若此坦克死亡，则不阻挡
			//if (it->m_isAlive == false) continue;
			if (
				((this->m_core.Y == it->m_core.Y) && (it->m_core.X - this->m_core.X == 3)) ||
				((this->m_core.Y == it->m_core.Y - 1) && (it->m_core.X - this->m_core.X == 3)) ||
				((this->m_core.Y == it->m_core.Y - 2) && (it->m_core.X - this->m_core.X == 3)) ||
				((this->m_core.Y == it->m_core.Y + 1) && (it->m_core.X - this->m_core.X == 3)) ||
				((this->m_core.Y == it->m_core.Y + 2) && (it->m_core.X - this->m_core.X == 3))
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
	// 若死亡，则不画（否则我坦尸体仍存在
	if (this->m_isAlive == false) return;
	if (this->m_who != 敌方坦克)
	{
		if (m_who == 我方坦克A)
		{
			GotoxyAndPrint(this->m_core.X, this->m_core.Y, "■", 我坦颜色);//中心点

		}
		else if (m_who == 我方坦克B)
		{
			GotoxyAndPrint(this->m_core.X, this->m_core.Y, "□", 我坦颜色);//中心点
		}
		for (int i = 0; i < 5; i++)//其他点
		{
			GotoxyAndPrint(this->m_body[i].X, this->m_body[i].Y, "■", 我坦颜色);
		}
	}
	else if (m_who == 敌方坦克)
	{
		// 两条命
		if (this->m_blood == 2)
		{
			GotoxyAndPrint(this->m_core.X, this->m_core.Y, "■", 敌坦颜色);//中心点
			for (int i = 0; i < 5; i++)//其他点
			{
				GotoxyAndPrint(this->m_body[i].X, this->m_body[i].Y, "■", 敌坦颜色);//中心点
			}
		}
		// 一条命
		else if (this->m_blood == 1)
		{
			// 一点攻击力
			if (m_power == 1)
			{
				GotoxyAndPrint(this->m_core.X, this->m_core.Y, "□", 敌坦颜色);//中心点
				for (int i = 0; i < 5; i++)//其他点
				{
					GotoxyAndPrint(this->m_body[i].X, this->m_body[i].Y, "□", 敌坦颜色);
				}
			}
			// 两点攻击力
			else if (m_power == 2)
			{
				GotoxyAndPrint(this->m_core.X, this->m_core.Y, "※", 敌坦颜色);//中心点
				for (int i = 0; i < 5; i++)//其他点
				{
					GotoxyAndPrint(this->m_body[i].X, this->m_body[i].Y, "※", 敌坦颜色);
				}
			}

		}
	}
}


//int GetLiveEnemyAmount(vector<CTank>& enemyTank)
//{
//	int count = 0;
//	for (vector<CTank>::iterator it = enemyTank.begin(); it != enemyTank.end(); it++)
//	{
//		if (it->m_isAlive) count++;
//	}
//	return count;
//}