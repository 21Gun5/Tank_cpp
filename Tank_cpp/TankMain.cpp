#include <iostream>
#include <conio.h>
#include <time.h>
#include "Func.h"
#include "Game.h"
#include "Map.h"
#include "Bullet.h"
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
	//CTank myTank = { { MAP_X_WALL / 4 + 5, MAP_Y - 3 }, UP, 3, 我方坦克 };
	CTank myTank[MY_TANK_AMOUNT] = {
		{{ MAP_X_WALL / 4 - 4, MAP_Y - 3 }, UP, 3, 我方坦克A },
		{{ MAP_X_WALL / 4 + 5, MAP_Y - 3 }, UP, 3, 我方坦克B }
	};

	//敌方坦克
	CTank enemyTank[ENEMY_TANK_AMOUNT] = {
		{{2, 2} ,DOWN ,2,敌方坦克},
		{{MAP_X_WALL / 4, 2},DOWN,1,敌方坦克 },
		{{MAP_X_WALL / 2 - 2, 2}, DOWN,2,敌方坦克}
	};

	////流程控制
	//int indexForPlay = 0;		//菜单索引
	//bool IsSelectedPlay = 0;	//是否选择结束
	//while (true)
	//{
	//	game.DrawMenu(game.menuPlay, _countof(game.menuPlay), indexForPlay);
	//	int play = game.SelectMenu(_countof(game.menuPlay), &indexForPlay);
	//	if (play == ENTER_KEY)
	//	{
	//		switch (indexForPlay)
	//		{
	//		case 开始游戏:
	//		{
	//			int indexForWhoMap = 0;//菜单索引
	//			bool IsSelectedWhoMap = 0; //选择的循环结束
	//			while (true)
	//			{
	//				game.DrawMenu(game.menuWhoMap, _countof(game.menuWhoMap), indexForWhoMap);
	//				int whoMap = game.SelectMenu(_countof(game.menuWhoMap), &indexForWhoMap);
	//				if (whoMap == ENTER_KEY)
	//				{
	//					switch (indexForWhoMap)
	//					{
	//					case 系统默认:
	//					{
	//						int indexForLevel = 0;
	//						bool IsSelectedLevel = 0;
	//						while (true)
	//						{
	//							game.DrawMenu(game.menuLevel, _countof(game.menuLevel), indexForLevel);
	//							int level = game.SelectMenu(_countof(game.menuLevel), &indexForLevel);
	//							if (level == ENTER_KEY)
	//							{
	//								switch (indexForLevel)
	//								{
	//								case 简单:
	//									game.m_levelEneTank = 300;
	//									game.m_levelEneBul = 90;
	//									IsSelectedLevel = 1;
	//									break;
	//								case 一般:
	//									game.m_levelEneTank = 200;
	//									game.m_levelEneBul = 70;
	//									IsSelectedLevel = 1;
	//									break;
	//								case 困难:
	//									game.m_levelEneTank = 100;
	//									game.m_levelEneBul = 50;
	//									IsSelectedLevel = 1;
	//									break;
	//								default:
	//									break;
	//								}
	//							}
	//							if (IsSelectedLevel == 1)
	//								break;
	//						}
	//						map.LoadDefaultMap();//使用默认的
	//						IsSelectedPlay = 1;
	//						IsSelectedWhoMap = 1;
	//						game.m_isRunning = 1;//游戏运行
	//						break;
	//					}
	//					case 玩家提供:
	//					{
	//						int indexForWhenMap = 0;//菜单索引
	//						bool IsSelectedWhenMap = 0; //选择的循环结束
	//						while (true)
	//						{
	//							game.DrawMenu(game.menuWhenMap, _countof(game.menuWhenMap), indexForWhenMap);
	//							int whenMap = game.SelectMenu(_countof(game.menuWhenMap), &indexForWhenMap);
	//							if (whenMap == ENTER_KEY)
	//							{
	//								switch (indexForWhenMap)
	//								{
	//								case 新建地图:
	//									IsSelectedPlay = 1;
	//									IsSelectedWhoMap = 1;
	//									IsSelectedWhenMap = 1;
	//									game.m_isRunning = 1;//要进入游戏了
	//									map.SaveMapFile(myTank, enemyTank);//手动设置并直接使用
	//									break;
	//								case 已有地图:
	//								{
	//									IsSelectedPlay = 1;
	//									IsSelectedWhoMap = 1;
	//									IsSelectedWhenMap = 1;
	//									game.m_isRunning = 1;//要进入游戏了
	//									char* mapFile = map.ShowMapFile();
	//									map.LoadMapFile(mapFile,map);//导入已有地图
	//									break;
	//								}
	//								case 返回上页:
	//								{
	//									IsSelectedWhenMap = 1;
	//									break;
	//								}
	//								default:
	//									break;
	//								}
	//							}
	//							if (IsSelectedWhenMap == 1)
	//								break;
	//						}
	//						break;
	//					}
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
	//		case 读取游戏:
	//		{
	//			IsSelectedPlay = 1;
	//			char* gameFile = game.ShowGameFile();
	//			game.LoadGameFile(myTank, enemyTank, map,gameFile);
	//			break;
	//		}
	//		case 退出游戏:
	//			return 0;
	//		default:
	//			break;
	//		}
	//	}
	//	if (IsSelectedPlay)//选择结束，进入游戏
	//		break;
	//}

	game.m_isRunning = 1;//要进入游戏了
	//map.CustomizeMap(tank, enemyTank);//手动设置并直接使用

	map.LoadDefaultMap();//使用默认的
	//game.m_isRunning = 1;//游戏运行

	//静态信息
	map.DrawStaticMap();
	//map.DrawDynamicMap();
	game.DrawGameHelp();
	

	//主循环
	while (game.m_isRunning)
	{
		//动态实时显示
		game.DrawGameInfo(myTank, enemyTank);
		map.DrawDynamicMap();

		//我方坦克线程
		if (clock() - time4Tank >= 100)
		{
			for (int i = 0; i < MY_TANK_AMOUNT; i++)
			{
				time4Tank = clock();
				COORD oldCore = myTank[i].m_core;
				COORD oldBody[5] = { myTank[i].m_body[0],myTank[i].m_body[1],myTank[i].m_body[2],myTank[i].m_body[3],myTank[i].m_body[4] };
				myTank[i].ManipulateTank(myTank,enemyTank, map, game);
				myTank[i].CleanTankTail(oldCore, oldBody);
				myTank[i].DrawTank();
			}
		}

		//我方子弹线程
		if (clock() - time4Bullet >= 50)
		{
			for (int i = 0; i < MY_TANK_AMOUNT; i++)
			{
				if (myTank[i].m_bullet.m_state != 不存在)
				{
					//子弹赋值
					if (myTank[i].m_bullet.m_state == 未赋值)//==1未赋值状态
					{
						//myTank[i].m_bullet.SetBullet({ myTank[i].m_body[0].X, myTank[i].m_body[0].Y }, myTank[i].m_dir);

						myTank[i].m_bullet.SetBullet(myTank[i]);
						myTank[i].m_bullet.m_state = 已赋值;
					}
					//子弹移动
					time4Bullet = clock();
					COORD oldBulCore = myTank[i].m_bullet.m_core;
					myTank[i].m_bullet.MoveBullet();
					myTank[i].m_bullet.CleanBullet(oldBulCore);
					myTank[i].m_bullet.DrawBullet( map);
					myTank[i].m_bullet.IsBulMeetOther(myTank[i], myTank,enemyTank, map);
				}
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
				//enemyTank[i].ManipulateTank(myTank, enemyTank,map,game);
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
						enemyTank[i].m_bullet.SetBullet(enemyTank[i] );
						enemyTank[i].m_bullet.m_state = 已赋值;
					}
					//子弹移动
					time4EnemyBullet = clock();
					COORD oldBulCore = enemyTank[i].m_bullet.m_core;
					enemyTank[i].m_bullet.MoveBullet();
					enemyTank[i].m_bullet.CleanBullet(oldBulCore);
					enemyTank[i].m_bullet.DrawBullet(map);
					enemyTank[i].m_bullet.IsBulMeetOther(enemyTank[i],myTank,enemyTank,map);
				}
			}
		}

		//判断游戏结束
		if ((myTank[0].m_blood == 0 && myTank[1].m_blood == 0) || GetLiveEnemyAmount(enemyTank) == 0)
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