#include <iostream>
#include <conio.h>
#include <time.h>
#include "Func.h"
#include "Game.h"
#include "Map.h"
//#include "Bullet.h"
#include "Tank.h"
using namespace std;

int main()
{
	//初始化
	CGame game;
	CMap map;
	game.GameInit(map);

	int time4Tank = 0;
	int time4Bullet = 0;
	int time4EnemyTank = 0;
	int time4EnemyBullet = 0;

	// 我方坦克
	CTank tank({ MAP_X_WALL / 4, MAP_Y / 2 }, UP, 3, 我方坦克);

	//敌方坦克
	CTank enemyTank[ENEMY_TANK_AMOUNT] = {
	{{2, 2} ,DOWN ,2,敌方坦克},
	{{MAP_X_WALL / 4, 2},UP,1,敌方坦克, },
	};

	////流程控制
	//int indexForPlay = 0;		//菜单索引
	//bool IsSelectedPlay = 0;	//是否选择结束
	//while (true)
	//{
	//	DrawMenu(menuPlay, _countof(menuPlay), indexForPlay);
	//	int play = SelectMenu(_countof(menuPlay), &indexForPlay);
	//	if (play == ENTER)
	//	{
	//		switch (indexForPlay)
	//		{
	//		case 开始游戏:
	//		{
	//			int indexForWhoMap = 0;//菜单索引
	//			bool IsSelectedWhoMap = 0; //选择的循环结束
	//			while (true)
	//			{
	//				DrawMenu(menuWhoMap, _countof(menuWhoMap), indexForWhoMap);
	//				int whoMap = SelectMenu(_countof(menuWhoMap), &indexForWhoMap);
	//				if (whoMap == ENTER)
	//				{
	//					switch (indexForWhoMap)
	//					{
	//					case 系统默认:
	//					{
	//						int indexForLevel = 0;
	//						bool IsSelectedLevel = 0;
	//						while (true)
	//						{
	//							DrawMenu(menuLevel, _countof(menuLevel), indexForLevel);
	//							int level = SelectMenu(_countof(menuLevel), &indexForLevel);
	//							if (level == ENTER)
	//							{
	//								switch (indexForLevel)
	//								{
	//								case 简单:
	//									g_levelEneTank = 300;
	//									g_levelEneBul = 90;
	//									IsSelectedLevel = 1;
	//									break;
	//								case 一般:
	//									g_levelEneTank = 200;
	//									g_levelEneBul = 70;
	//									IsSelectedLevel = 1;
	//									break;
	//								case 困难:
	//									g_levelEneTank = 100;
	//									g_levelEneBul = 50;
	//									IsSelectedLevel = 1;
	//									break;
	//								default:
	//									break;
	//								}
	//							}
	//							if (IsSelectedLevel == 1)
	//								break;
	//						}
	//						SetDefaultMap();//使用默认的
	//						IsSelectedPlay = 1;
	//						IsSelectedWhoMap = 1;
	//						g_isRunning = 1;//游戏运行
	//						break;
	//					}
	//					//case 玩家提供:
	//					//{
	//					//	int indexForWhenMap = 0;//菜单索引
	//					//	bool IsSelectedWhenMap = 0; //选择的循环结束
	//					//	while (true)
	//					//	{
	//					//		DrawMenu(menuWhenMap, _countof(menuWhenMap), indexForWhenMap);
	//					//		int whenMap = SelectMenu(_countof(menuWhenMap), &indexForWhenMap);
	//					//		if (whenMap == ENTER)
	//					//		{
	//					//			switch (indexForWhenMap)
	//					//			{
	//					//			case 新建地图:
	//					//				IsSelectedPlay = 1;
	//					//				IsSelectedWhoMap = 1;
	//					//				IsSelectedWhenMap = 1;
	//					//				g_isRunning = 1;//要进入游戏了
	//					//				CustomizeMap(&tank, enemyTank);//手动设置并直接使用
	//					//				break;
	//					//			case 已有地图:
	//					//			{
	//					//				IsSelectedPlay = 1;
	//					//				IsSelectedWhoMap = 1;
	//					//				IsSelectedWhenMap = 1;
	//					//				g_isRunning = 1;//要进入游戏了
	//					//				char* mapFile = ShowMapFile();
	//					//				LoadMapFile(mapFile);//导入已有地图
	//					//				break;
	//					//			}
	//					//			case 返回上页:
	//					//			{
	//					//				IsSelectedWhenMap = 1;
	//					//				break;
	//					//			}
	//					//			default:
	//					//				break;
	//					//			}
	//					//		}
	//					//		if (IsSelectedWhenMap == 1)
	//					//			break;
	//					//	}
	//					//	break;
	//					//}
	//					case 返回上页:
	//					{
	//						IsSelectedWhoMap = 1;
	//						break;
	//					}
	//					default:
	//						break;
	//					}
	//				}
	//				if (IsSelectedWhoMap == 1)
	//					break;
	//			}
	//			break;
	//		}
	//		//case 读取游戏:
	//		//{
	//		//	IsSelectedPlay = 1;
	//		//	char* gameFile = ShowGameFile();
	//		//	LoadGame(&tank, enemyTank, gameFile);
	//		//	break;
	//		//}
	//		case 退出游戏:
	//			return 0;
	//		default:
	//			break;
	//		}
	//	}
	//	if (IsSelectedPlay)//选择结束，进入游戏
	//		break;
	//}

	map.SetDefaultMap();
	game.m_isRunning = 1;

	//边界及障碍
	map.DrawBorder();
	game.DrawGameHelp();
	map.DrawBarr();

	//主循环
	while (game.m_isRunning)
	{
		//信息实时显示
		game.DrawGameInfo(tank, enemyTank);
		//我方坦克线程
		if (clock() - time4Tank >= 100)
		{
			time4Tank = clock();
			COORD oldCore = tank.m_core;
			COORD oldBody[5] = { tank.m_body[0],tank.m_body[1],tank.m_body[2],tank.m_body[3],tank.m_body[4] };
			
			tank.ManipulateMyTank(enemyTank,map);
			tank.CleanTankTail(oldCore, oldBody);
			tank.DrawTank();
		}
		//我方子弹线程
		if (clock() - time4Bullet >= 50)
		{
			if (tank.m_bullet.m_state != 不存在)
			{
				//子弹赋值
				if (tank.m_bullet.m_state == 未赋值)//==1未赋值状态
				{
					tank.m_bullet.SetBullet({ tank.m_body[0].X, tank.m_body[0].Y }, tank.m_dir);
					tank.m_bullet.m_state = 已赋值;
				}
				//子弹移动
				time4Bullet = clock();
				COORD oldBulCore = tank.m_bullet.m_core;
				tank.m_bullet.MoveBullet();
				tank.m_bullet.CleanBullet(oldBulCore);
				tank.m_bullet.DrawBullet(tank,map);
				tank.m_bullet.IsMyBulMeetOther( tank, enemyTank,map);
			}
		}
		//敌方坦克线程
		if (clock() - time4EnemyTank >= game.m_levelEneTank)
		{
			for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
			{
				time4EnemyTank = clock();
				COORD oldCore = enemyTank[i].m_core;
				COORD oldBody[5] = { enemyTank[i].m_body[0],enemyTank[i].m_body[1],enemyTank[i].m_body[2],enemyTank[i].m_body[3],enemyTank[i].m_body[4] };
				enemyTank[i].ManipulateEneTank(tank, enemyTank,map);
				enemyTank[i].CleanTankTail(oldCore, oldBody);
				enemyTank[i].DrawTank();
			}
		}
		//敌方子弹线程
		if (clock() - time4EnemyBullet >= game.m_levelEneBul)
		{
			for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
			{
				if (enemyTank[i].m_bullet.m_state != 不存在)
				{
					//子弹赋值
					if (enemyTank[i].m_bullet.m_state == 未赋值)//==1未赋值状态
					{
						enemyTank[i].m_bullet.SetBullet({enemyTank[i].m_body[0].X, enemyTank[i].m_body[0].Y}, enemyTank[i].m_dir );
						enemyTank[i].m_bullet.m_state = 已赋值;
					}
					//子弹移动
					time4EnemyBullet = clock();
					COORD oldBulCore = enemyTank[i].m_bullet.m_core;
					enemyTank[i].m_bullet.MoveBullet();
					enemyTank[i].m_bullet.CleanBullet(oldBulCore);
					enemyTank[i].m_bullet.DrawBullet(enemyTank[i],map);
					enemyTank[i].m_bullet.IsEneBulMeetOther(tank,enemyTank,map);
				}
			}
		}
		//判断游戏结束
		if (tank.m_blood == 0 || GetLiveEnemyAmount(enemyTank) == 0)
		{
			game.GameOver(enemyTank);
			break;
		}
	}

	//消耗多余字符
	char ch = _getch();
	ch = _getch();

	return 0;
}