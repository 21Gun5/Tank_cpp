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
	//��ʼ��
	CGame game;
	CMap map;
	game.GameInit(map);

	int time4Tank = 0;
	int time4Bullet = 0;
	int time4EnemyTank = 0;
	int time4EnemyBullet = 0;

	// �ҷ�̹��
	vector<CTank> myTank;
	CTank myTankA = { { MAP_X_WALL / 4 - 4, MAP_Y - 3 }, UP, 3, �ҷ�̹��A };
	CTank myTankB = { { MAP_X_WALL / 4 + 5, MAP_Y - 3 }, UP, 3, �ҷ�̹��B };
	myTank.push_back(myTankA);
	myTank.push_back(myTankB);

	//�з�̹��
	vector<CTank> enemyTank;
	CTank enemyTankA = { {2, 2} ,DOWN ,2,�з�̹�� };
	CTank enemyTankB = { {MAP_X_WALL / 4, 2},DOWN,1,�з�̹�� };
	CTank enemyTankC = { {MAP_X_WALL / 4 - 17, MAP_Y - 3}, DOWN,1,�з�̹�� };
	CTank enemyTankD = { {MAP_X_WALL / 2 - 2, 2}, DOWN,1,�з�̹�� };
	enemyTank.push_back(enemyTankA);
	enemyTank.push_back(enemyTankB);
	enemyTank.push_back(enemyTankC);
	//enemyTank.push_back(enemyTankD);

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
	//						map.LoadDefaultMap();//ʹ��Ĭ�ϵ�
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
	//									map.SaveMapFile(myTank, enemyTank);//�ֶ����ò�ֱ��ʹ��
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
	//			game.LoadGameFile(myTank, enemyTank, map,gameFile);
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
	map.LoadDefaultMap();//ʹ��Ĭ�ϵ�


	//��̬��Ϣ
	map.DrawStaticMap();
	game.DrawGameHelp();

	//��ѭ��
	while (game.m_isRunning)
	{
		//��̬ʵʱ��ʾ
		game.DrawGameInfo(myTank, enemyTank);
		map.DrawDynamicMap();
		//�ҷ�̹���߳�
		if (clock() - time4Tank >= 100)
		{
			for (vector<CTank>::iterator it = myTank.begin(); it != myTank.end();)
			{
				time4Tank = clock();
				COORD oldCore = it->m_core;
				COORD oldBody[5] = { it->m_body[0],it->m_body[1],it->m_body[2],it->m_body[3],it->m_body[4] };
				it->ManipulateTank(myTank,enemyTank, map, game);
				it->CleanTankTail(oldCore, oldBody);
				it->DrawTank();

				// ��������ɾ����������������
				if (!it->m_isAlive)
				{
					// ɾ���������ָ����һ��
					it = myTank.erase(it);
				}
				else
				{
					it++;
				}
			}
		}
		//�ҷ��ӵ��߳�
		if (clock() - time4Bullet >= 50)
		{
			for (vector<CTank>::iterator it = myTank.begin(); it != myTank.end(); it++)
			{
				if (it->m_bullet.m_state != ������)
				{
					//�ӵ���ֵ
					if (it->m_bullet.m_state == δ��ֵ)//==1δ��ֵ״̬
					{
						it->m_bullet.SetBullet(*it);
						it->m_bullet.m_state = �Ѹ�ֵ;
					}
					//�ӵ��ƶ�
					time4Bullet = clock();
					COORD oldBulCore = it->m_bullet.m_core;
					it->m_bullet.MoveBullet();
					it->m_bullet.CleanBullet(oldBulCore);
					it->m_bullet.DrawBullet( map);
					it->m_bullet.IsBulMeetOther(*it, myTank,enemyTank, map,game);
				}
			}
			
		}
		//�з�̹���߳�
		if (clock() - time4EnemyTank >= game.m_levelEneTank)
		{

			for (vector<CTank>::iterator it = enemyTank.begin(); it != enemyTank.end();)
			{


				time4EnemyTank = clock();
				COORD oldCore = it->m_core;
				COORD oldBody[5] = { it->m_body[0],it->m_body[1],it->m_body[2],it->m_body[3],it->m_body[4] };
				it->ManipulateTank(myTank, enemyTank,map,game);
				it->CleanTankTail(oldCore, oldBody);
				it->DrawTank();

				// ��������ɾ����������������
				if (!it->m_isAlive)
				{
					// ɾ���������ָ����һ��
					it = enemyTank.erase(it);
				}
				else
				{
					it++;
				}
			}
		}
		//�з��ӵ��߳�
		if (clock() - time4EnemyBullet >= game.m_levelEneBul)
		{
			for (vector<CTank>::iterator it = enemyTank.begin(); it != enemyTank.end(); it++)
			{
				if (it->m_bullet.m_state != ������)
				{
					//�ӵ���ֵ
					if (it->m_bullet.m_state == δ��ֵ)//==1δ��ֵ״̬
					{
						it->m_bullet.SetBullet(*it );
						it->m_bullet.m_state = �Ѹ�ֵ;
					}
					//�ӵ��ƶ�
					time4EnemyBullet = clock();
					COORD oldBulCore = it->m_bullet.m_core;
					it->m_bullet.MoveBullet();
					it->m_bullet.CleanBullet(oldBulCore);
					it->m_bullet.DrawBullet(map);
					it->m_bullet.IsBulMeetOther(*it,myTank,enemyTank,map,game);
				}
			}
		}
		//�ж���Ϸ����
		if (game.m_isOver)
		{
			game.GameOver(enemyTank);
			break;
		}
		//// �ж��Ƿ����
		//if (enemyTank.size() == 0)
		//{
		//	game.NextStage();
		//	//stage = game.m_stage;
		//	isNextStage = true;
		//	continue;
		//}
	}


	////��ѭ��
	//int needLoadNewStage = 0;
	//while (game.m_isRunning)
	//{
	//	if (game.m_stage != 1 && needLoadNewStage ==1)
	//	{
	//		
	//		// �����ͼ�ļ�
	//		switch (game.m_stage)
	//		{
	//		case 2:
	//			map.LoadMapFile(const_cast<char*>("Stage2.i"), map);
	//			break;
	//		case 3:
	//			map.LoadMapFile(const_cast<char*>("222.i"), map);
	//			break;
	//		default:
	//			break;
	//		}
	//		// ���������´�ӡ
	//		system("cls");
	//		map.DrawStaticMap();
	//		game.DrawGameHelp();
	//		//���¸��о�̹�˸�ֵ
	//		//enemyTank[0] = {{{MAP_X_WALL / 4 - 9, MAP_Y - 3}, DOWN,1,�з�̹��}};
	//		enemyTank[0].m_isAlive = 1;
	//		// �������ɵо�̹��
	//		// Ӧ�ö�̬���ɣ���vector
	//		// ������ɣ��ٵ���һ���ٵ���
	//		needLoadNewStage = 0;
	//	}
	//	//��̬ʵʱ��ʾ
	//	game.DrawGameInfo(myTank, enemyTank);
	//	map.DrawDynamicMap();
	//	//�ҷ�̹���߳�
	//	if (clock() - time4Tank >= 100)
	//	{
	//		for (int i = 0; i < MY_TANK_AMOUNT; i++)
	//		{
	//			time4Tank = clock();
	//			COORD oldCore = myTank[i].m_core;
	//			COORD oldBody[5] = { myTank[i].m_body[0],myTank[i].m_body[1],myTank[i].m_body[2],myTank[i].m_body[3],myTank[i].m_body[4] };
	//			myTank[i].ManipulateTank(myTank, enemyTank, map, game);
	//			myTank[i].CleanTankTail(oldCore, oldBody);
	//			myTank[i].DrawTank();
	//		}
	//	}
	//	//�ҷ��ӵ��߳�
	//	if (clock() - time4Bullet >= 50)
	//	{
	//		for (int i = 0; i < MY_TANK_AMOUNT; i++)
	//		{
	//			if (myTank[i].m_bullet.m_state != ������)
	//			{
	//				//�ӵ���ֵ
	//				if (myTank[i].m_bullet.m_state == δ��ֵ)//==1δ��ֵ״̬
	//				{
	//					//myTank[i].m_bullet.SetBullet({ myTank[i].m_body[0].X, myTank[i].m_body[0].Y }, myTank[i].m_dir);
	//					myTank[i].m_bullet.SetBullet(myTank[i]);
	//					myTank[i].m_bullet.m_state = �Ѹ�ֵ;
	//				}
	//				//�ӵ��ƶ�
	//				time4Bullet = clock();
	//				COORD oldBulCore = myTank[i].m_bullet.m_core;
	//				myTank[i].m_bullet.MoveBullet();
	//				myTank[i].m_bullet.CleanBullet(oldBulCore);
	//				myTank[i].m_bullet.DrawBullet(map);
	//				myTank[i].m_bullet.IsBulMeetOther(myTank[i], myTank, enemyTank, map);
	//			}
	//		}
	//	}
	//	//�з�̹���߳�
	//	if (clock() - time4EnemyTank >= game.m_levelEneTank)
	//	{
	//		for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
	//		{
	//			time4EnemyTank = clock();
	//			COORD oldCore = enemyTank[i].m_core;
	//			COORD oldBody[5] = { enemyTank[i].m_body[0],enemyTank[i].m_body[1],enemyTank[i].m_body[2],enemyTank[i].m_body[3],enemyTank[i].m_body[4] };
	//			//enemyTank[i].ManipulateTank(myTank, enemyTank,map,game);
	//			enemyTank[i].CleanTankTail(oldCore, oldBody);
	//			enemyTank[i].DrawTank();
	//		}
	//	}
	//	//�з��ӵ��߳�
	//	if (clock() - time4EnemyBullet >= game.m_levelEneBul)
	//	{
	//		for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
	//		{
	//			if (enemyTank[i].m_bullet.m_state != ������)
	//			{
	//				//�ӵ���ֵ
	//				if (enemyTank[i].m_bullet.m_state == δ��ֵ)//==1δ��ֵ״̬
	//				{
	//					enemyTank[i].m_bullet.SetBullet(enemyTank[i]);
	//					enemyTank[i].m_bullet.m_state = �Ѹ�ֵ;
	//				}
	//				//�ӵ��ƶ�
	//				time4EnemyBullet = clock();
	//				COORD oldBulCore = enemyTank[i].m_bullet.m_core;
	//				enemyTank[i].m_bullet.MoveBullet();
	//				enemyTank[i].m_bullet.CleanBullet(oldBulCore);
	//				enemyTank[i].m_bullet.DrawBullet(map);
	//				enemyTank[i].m_bullet.IsBulMeetOther(enemyTank[i], myTank, enemyTank, map);
	//			}
	//		}
	//	}
	//	//�ж���Ϸ����
	//	//if ((myTank[0].m_blood == 0 && myTank[1].m_blood == 0) || GetLiveEnemyAmount(enemyTank) == 0)
	//	if ((myTank[0].m_blood == 0 && myTank[1].m_blood == 0))
	//	{
	//		game.GameOver(enemyTank);
	//		break;
	//	}
	//	// �ж��Ƿ����
	//	if (GetLiveEnemyAmount(enemyTank) == 0)
	//	{
	//		game.NextStage();
	//		needLoadNewStage = 1;
	//		//stage = game.m_stage;
	//		//isNextStage = true;
	//		continue;
	//	}
	//}


	//���Ķ����ַ�
	char ch = _getch();
	ch = _getch();

	return 0;
}