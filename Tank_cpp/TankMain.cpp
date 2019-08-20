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
	//��ʼ��
	CGame game;
	CMap map;
	game.GameInit(map);

	int time4Tank = 0;
	int time4Bullet = 0;
	int time4EnemyTank = 0;
	int time4EnemyBullet = 0;

	// �ҷ�̹��
	CTank tank({ MAP_X_WALL / 4, MAP_Y / 2 }, UP, 3, �ҷ�̹��);

	//�з�̹��
	CTank enemyTank[ENEMY_TANK_AMOUNT] = {
	{{2, 2} ,DOWN ,2,�з�̹��},
	{{MAP_X_WALL / 4, 2},UP,1,�з�̹��, },
	};

	////���̿���
	//int indexForPlay = 0;		//�˵�����
	//bool IsSelectedPlay = 0;	//�Ƿ�ѡ�����
	//while (true)
	//{
	//	game.DrawMenu(game.menuPlay, _countof(game.menuPlay), indexForPlay);
	//	int play = game.SelectMenu(_countof(game.menuPlay), &indexForPlay);
	//	if (play == ENTER_KEY)
	//	{
	//		switch (indexForPlay)
	//		{
	//		case ��ʼ��Ϸ:
	//		{
	//			int indexForWhoMap = 0;//�˵�����
	//			bool IsSelectedWhoMap = 0; //ѡ���ѭ������
	//			while (true)
	//			{
	//				game.DrawMenu(game.menuWhoMap, _countof(game.menuWhoMap), indexForWhoMap);
	//				int whoMap = game.SelectMenu(_countof(game.menuWhoMap), &indexForWhoMap);
	//				if (whoMap == ENTER_KEY)
	//				{
	//					switch (indexForWhoMap)
	//					{
	//					case ϵͳĬ��:
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
	//								case ��:
	//									game.m_levelEneTank = 300;
	//									game.m_levelEneBul = 90;
	//									IsSelectedLevel = 1;
	//									break;
	//								case һ��:
	//									game.m_levelEneTank = 200;
	//									game.m_levelEneBul = 70;
	//									IsSelectedLevel = 1;
	//									break;
	//								case ����:
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
	//						map.SetDefaultMap();//ʹ��Ĭ�ϵ�
	//						IsSelectedPlay = 1;
	//						IsSelectedWhoMap = 1;
	//						game.m_isRunning = 1;//��Ϸ����
	//						break;
	//					}
	//					case ����ṩ:
	//					{
	//						int indexForWhenMap = 0;//�˵�����
	//						bool IsSelectedWhenMap = 0; //ѡ���ѭ������
	//						while (true)
	//						{
	//							game.DrawMenu(game.menuWhenMap, _countof(game.menuWhenMap), indexForWhenMap);
	//							int whenMap = game.SelectMenu(_countof(game.menuWhenMap), &indexForWhenMap);
	//							if (whenMap == ENTER_KEY)
	//							{
	//								switch (indexForWhenMap)
	//								{
	//								case �½���ͼ:
	//									IsSelectedPlay = 1;
	//									IsSelectedWhoMap = 1;
	//									IsSelectedWhenMap = 1;
	//									game.m_isRunning = 1;//Ҫ������Ϸ��
	//									map.CustomizeMap(tank, enemyTank,map);//�ֶ����ò�ֱ��ʹ��
	//									break;
	//								case ���е�ͼ:
	//								{
	//									IsSelectedPlay = 1;
	//									IsSelectedWhoMap = 1;
	//									IsSelectedWhenMap = 1;
	//									game.m_isRunning = 1;//Ҫ������Ϸ��
	//									char* mapFile = map.ShowMapFile();
	//									map.LoadMapFile(mapFile,map);//�������е�ͼ
	//									break;
	//								}
	//								case ������ҳ:
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
	//					case ������ҳ:
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
	//		case ��ȡ��Ϸ:
	//		{
	//			IsSelectedPlay = 1;
	//			char* gameFile = game.ShowGameFile();
	//			game.LoadGame(tank, enemyTank, map,gameFile);
	//			break;
	//		}
	//		case �˳���Ϸ:
	//			return 0;
	//		default:
	//			break;
	//		}
	//	}
	//	if (IsSelectedPlay)//ѡ�������������Ϸ
	//		break;
	//}


	game.m_isRunning = 1;//Ҫ������Ϸ��
	//map.CustomizeMap(tank, enemyTank);//�ֶ����ò�ֱ��ʹ��

	map.SetDefaultMap();//ʹ��Ĭ�ϵ�
	//game.m_isRunning = 1;//��Ϸ����


	//�߽缰�ϰ�
	map.DrawBorder();
	map.DrawBarr();
	game.DrawGameHelp();
	

	//��ѭ��
	while (game.m_isRunning)
	{
		//��Ϣʵʱ��ʾ
		game.DrawGameInfo(tank, enemyTank);
		//�ҷ�̹���߳�
		if (clock() - time4Tank >= 100)
		{
			time4Tank = clock();
			COORD oldCore = tank.m_core;
			COORD oldBody[5] = { tank.m_body[0],tank.m_body[1],tank.m_body[2],tank.m_body[3],tank.m_body[4] };
			
			tank.ManipulateMyTank(enemyTank,map,game);
			tank.CleanTankTail(oldCore, oldBody);
			tank.DrawTank();
		}
		//�ҷ��ӵ��߳�
		if (clock() - time4Bullet >= 50)
		{
			if (tank.m_bullet.m_state != ������)
			{
				//�ӵ���ֵ
				if (tank.m_bullet.m_state == δ��ֵ)//==1δ��ֵ״̬
				{
					tank.m_bullet.SetBullet({ tank.m_body[0].X, tank.m_body[0].Y }, tank.m_dir);
					tank.m_bullet.m_state = �Ѹ�ֵ;
				}
				//�ӵ��ƶ�
				time4Bullet = clock();
				COORD oldBulCore = tank.m_bullet.m_core;
				tank.m_bullet.MoveBullet();
				tank.m_bullet.CleanBullet(oldBulCore);
				tank.m_bullet.DrawBullet(tank,map);
				tank.m_bullet.IsMyBulMeetOther( tank, enemyTank,map);
			}
		}
		//�з�̹���߳�
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
		//�з��ӵ��߳�
		if (clock() - time4EnemyBullet >= game.m_levelEneBul)
		{
			for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
			{
				if (enemyTank[i].m_bullet.m_state != ������)
				{
					//�ӵ���ֵ
					if (enemyTank[i].m_bullet.m_state == δ��ֵ)//==1δ��ֵ״̬
					{
						enemyTank[i].m_bullet.SetBullet({enemyTank[i].m_body[0].X, enemyTank[i].m_body[0].Y}, enemyTank[i].m_dir );
						enemyTank[i].m_bullet.m_state = �Ѹ�ֵ;
					}
					//�ӵ��ƶ�
					time4EnemyBullet = clock();
					COORD oldBulCore = enemyTank[i].m_bullet.m_core;
					enemyTank[i].m_bullet.MoveBullet();
					enemyTank[i].m_bullet.CleanBullet(oldBulCore);
					enemyTank[i].m_bullet.DrawBullet(enemyTank[i],map);
					enemyTank[i].m_bullet.IsEneBulMeetOther(tank,enemyTank,map);
				}
			}
		}
		//�ж���Ϸ����
		if (tank.m_blood == 0 || GetLiveEnemyAmount(enemyTank) == 0)
		{
			game.GameOver(enemyTank);
			break;
		}
	}

	//���Ķ����ַ�
	char ch = _getch();
	ch = _getch();

	return 0;
}