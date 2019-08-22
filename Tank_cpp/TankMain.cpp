#include <iostream>
#include <conio.h>
#include <time.h>
#include <vector>
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
	vector<CTank> myTank;
	CTank myTankA = { { MAP_X_WALL / 4 - 4, MAP_Y - 3 }, UP, 30, 我方坦克A };
	CTank myTankB = { { MAP_X_WALL / 4 + 5, MAP_Y - 3 }, UP, 3, 我方坦克B };
	myTank.push_back(myTankA);
//	myTank.push_back(myTankB);

	//敌方坦克
	vector<CTank> enemyTank;
	CTank enemyTankA = { {2, 2} ,DOWN ,20,敌方坦克 };
	CTank enemyTankB = { {MAP_X_WALL / 4, 2},DOWN,1,敌方坦克 };
	CTank enemyTankC = { {MAP_X_WALL / 2 - 2, 2}, DOWN,1,敌方坦克 };
	CTank enemyTankD = { {MAP_X_WALL / 4 - 8, MAP_Y - 3}, LEFT,1,敌方坦克 };
	enemyTank.push_back(enemyTankA);
	enemyTank.push_back(enemyTankB);
	//enemyTank.push_back(enemyTankD);
	enemyTank.push_back(enemyTankC);
	

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

	//静态信息
	map.DrawStaticMap();
	game.DrawGameHelp();

	//主循环
	while (game.m_isRunning)
	{
		// 进入相应关卡
		if (game.m_stage > 1 && game.m_needLoadNewStage&& game.m_stage <= game.m_maxStage)
		{
			// 导入地图文件、设置难度
			switch (game.m_stage)
			{
			case 2:
				map.LoadMapFile(const_cast<char*>("Stage2.i"), map);
				game.m_levelEneTank = 200;
				game.m_levelEneBul = 70;
				break;
			case 3:
				map.LoadMapFile(const_cast<char*>("Stage3.i"), map);
				game.m_levelEneTank = 100;
				game.m_levelEneBul = 50;
				break;
			default:
				break;
			}
			// 清屏
			system("cls");
			//重新打印静态信息
			map.DrawStaticMap();
			game.DrawGameHelp();
			// 重新生成敌军坦克
			enemyTank.push_back(enemyTankA);
			enemyTank.push_back(enemyTankB);
			enemyTank.push_back(enemyTankC);
			//enemyTank.push_back(enemyTankD);

			// 标记关卡导入完成
			game.m_needLoadNewStage = false;
		}

		//动态实时显示
		game.DrawGameInfo(myTank, enemyTank);
		map.DrawDynamicMap();
		//我方坦克线程
		if (clock() - time4Tank >= 100)
		{
			for (vector<CTank>::iterator it = myTank.begin(); it != myTank.end();)
			{
				time4Tank = clock();
				COORD oldCore = it->m_core;
				COORD oldBody[5] = { it->m_body[0],it->m_body[1],it->m_body[2],it->m_body[3],it->m_body[4] };
				it->ManipulateTank(myTank, enemyTank, map, game);
				it->CleanTankTail(oldCore, oldBody);
				it->DrawTank();

				// 若死亡则删除，否则正常迭代
				if (!it->m_isAlive)
				{
					// 删除后迭代器指向下一个
					GotoxyAndPrint(it->m_bullet.m_core.X, it->m_bullet.m_core.Y, " ");// 抹除其子弹
					it = myTank.erase(it);//删除
					
				}
				else
				{
					it++;
				}
			}
		}
		//我方子弹线程
		if (clock() - time4Bullet >= 50)
		{
			for (vector<CTank>::iterator it = myTank.begin(); it != myTank.end(); it++)
			{
				if (it->m_bullet.m_state != 不存在)
				{
					//子弹赋值
					if (it->m_bullet.m_state == 未赋值)//==1未赋值状态
					{
						it->m_bullet.SetBullet(*it);
						it->m_bullet.m_state = 已赋值;
					}
					//子弹移动
					time4Bullet = clock();
					COORD oldBulCore = it->m_bullet.m_core;
					it->m_bullet.MoveBullet();
					it->m_bullet.CleanBullet(oldBulCore);
					it->m_bullet.DrawBullet(map);
					it->m_bullet.IsBulMeetOther(*it, myTank, enemyTank, map, game);
				}
			}

		}
		//敌方坦克线程
		if (clock() - time4EnemyTank >= game.m_levelEneTank)
		{
			for (vector<CTank>::iterator it = enemyTank.begin(); it != enemyTank.end();)
			{
				time4EnemyTank = clock();
				COORD oldCore = it->m_core;
				COORD oldBody[5] = { it->m_body[0],it->m_body[1],it->m_body[2],it->m_body[3],it->m_body[4] };
				it->ManipulateTank(myTank, enemyTank, map, game);
				it->CleanTankTail(oldCore, oldBody);
				it->DrawTank();

				// 坦克死亡与否
				if (!it->m_isAlive)
				{
					// 删除后迭代器指向下一个
					GotoxyAndPrint(it->m_bullet.m_core.X, it->m_bullet.m_core.Y , " ");// 抹除其子弹
					it = enemyTank.erase(it);//删除
				}
				else
				{
					//未死亡则正常迭代
					it++;
				}
			}
		}
		//敌方子弹线程
		if (clock() - time4EnemyBullet >= game.m_levelEneBul)
		{
			for (vector<CTank>::iterator it = enemyTank.begin(); it != enemyTank.end(); it++)
			{
				if (it->m_bullet.m_state != 不存在)
				{
					//子弹赋值
					if (it->m_bullet.m_state == 未赋值)//==1未赋值状态
					{
						it->m_bullet.SetBullet(*it);
						it->m_bullet.m_state = 已赋值;
					}
					//子弹移动
					time4EnemyBullet = clock();
					COORD oldBulCore = it->m_bullet.m_core;
					it->m_bullet.MoveBullet();
					it->m_bullet.CleanBullet(oldBulCore);
					it->m_bullet.DrawBullet(map);
					it->m_bullet.IsBulMeetOther(*it, myTank, enemyTank, map, game);
				}
			}
		}
		//判断游戏结束（我方全阵亡或全部通关
		if (game.m_isOver || game.m_stage > game.m_maxStage)
		{
			game.GameOver(enemyTank);
			break;
		}
		// 判断是否过关
		if (enemyTank.size() == 0)
		{
			game.NextStage();	
			continue;
		}

	}

	//消耗多余字符
	char ch = _getch();
	ch = _getch();

	return 0;
}