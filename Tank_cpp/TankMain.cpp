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
	// ��ʼ��
	CGame game;
	CMap map;
	game.GameInit(map);

	// ģ����߳�
	int time4Tank = 0;
	int time4Bullet = 0;
	int time4EnemyTank = 0;
	int time4EnemyBullet = 0;

	// �ҷ�̹��
	vector<CTank> myTank;
	CTank myTankA = { { MAP_X_WALL / 4 - 4, MAP_Y - 3 }, UP, 3, �ҷ�̹��A };
	CTank myTankB = { { MAP_X_WALL / 4 + 5, MAP_Y - 3 }, UP, 3, �ҷ�̹��B };

	// �з�̹��
	vector<CTank> enemyTank;
	CTank enemyTankA = { {2, 2} ,DOWN ,1,�з�̹��,2 };
	CTank enemyTankB = { {MAP_X_WALL / 8 + 1, 2},DOWN,2,�з�̹��,1 };
	CTank enemyTankC = { {MAP_X_WALL / 4, 2},DOWN,1,�з�̹��,1 };
	CTank enemyTankD = { {MAP_X_WALL / 8 + MAP_X_WALL / 4 - 1, 2}, DOWN,1,�з�̹��,2 };
	CTank enemyTankE = { {MAP_X_WALL / 2 - 2, 2}, DOWN,2,�з�̹�� ,1 };

	// ���̿���
	int indexForPlay = 0;		//�˵�����
	bool IsSelectedPlay = 0;	//�Ƿ�ѡ�����
	while (true)
	{
		game.DrawMenu(game.menuPlay, _countof(game.menuPlay), indexForPlay);
		int play = game.SelectMenu(_countof(game.menuPlay), &indexForPlay);
		if (play == ENTER_KEY)
		{
			switch (indexForPlay)
			{
			case ��ʼ��Ϸ:
			{
				// ����Ϸ�����̹��
				myTank.push_back(myTankA);
				myTank.push_back(myTankB);
				enemyTank.push_back(enemyTankA);
				enemyTank.push_back(enemyTankB);
				enemyTank.push_back(enemyTankC);
				enemyTank.push_back(enemyTankD);
				enemyTank.push_back(enemyTankE);
				int indexForWhoMap = 0;//�˵�����
				bool IsSelectedWhoMap = 0; //ѡ���ѭ������
				while (true)
				{
					game.DrawMenu(game.menuWhoMap, _countof(game.menuWhoMap), indexForWhoMap);
					int whoMap = game.SelectMenu(_countof(game.menuWhoMap), &indexForWhoMap);
					if (whoMap == ENTER_KEY)
					{
						switch (indexForWhoMap)
						{
						case ϵͳĬ��:
						{
							int indexForLevel = 0;
							bool IsSelectedLevel = 0;
							while (true)
							{
								game.DrawMenu(game.menuLevel, _countof(game.menuLevel), indexForLevel);
								int level = game.SelectMenu(_countof(game.menuLevel), &indexForLevel);
								if (level == ENTER_KEY)
								{
									switch (indexForLevel)
									{
									case ��:
										game.SetLevelEneTank(300);
										game.SetLevelEneBul(90);
										IsSelectedLevel = 1;
										break;
									case һ��:
										game.SetLevelEneTank(200);
										game.SetLevelEneBul(70);
										IsSelectedLevel = 1;
										break;
									case ����:
										game.SetLevelEneTank(100);
										game.SetLevelEneBul(50);
										IsSelectedLevel = 1;
										break;
									default:
										break;
									}
								}
								if (IsSelectedLevel == 1)
									break;
							}
							map.LoadDefaultMap();//ʹ��Ĭ�ϵ�
							IsSelectedPlay = 1;
							IsSelectedWhoMap = 1;
							game.SetIsRunning(true);//��Ϸ����
							break;
						}
						case ����ṩ:
						{
							int indexForWhenMap = 0;//�˵�����
							bool IsSelectedWhenMap = 0; //ѡ���ѭ������
							while (true)
							{
								game.DrawMenu(game.menuWhenMap, _countof(game.menuWhenMap), indexForWhenMap);
								int whenMap = game.SelectMenu(_countof(game.menuWhenMap), &indexForWhenMap);
								if (whenMap == ENTER_KEY)
								{
									switch (indexForWhenMap)
									{
									case �½���ͼ:
										IsSelectedPlay = 1;
										IsSelectedWhoMap = 1;
										IsSelectedWhenMap = 1;
										game.SetIsRunning(true);//��Ϸ����
										map.SaveMapFile(myTank, enemyTank);//�ֶ����ò�ֱ��ʹ��
										break;
									case ���е�ͼ:
									{
										IsSelectedPlay = 1;
										IsSelectedWhoMap = 1;
										IsSelectedWhenMap = 1;
										game.SetIsRunning(true);//��Ϸ����
										char* mapFile = map.ShowMapFile();
										map.LoadMapFile(mapFile, map);//�������е�ͼ
										break;
									}
									case ������ҳ:
									{
										IsSelectedWhenMap = 1;
										break;
									}
									default:
										break;
									}
								}
								if (IsSelectedWhenMap == 1)
									break;
							}
							break;
						}
						case ������ҳ:
						{
							IsSelectedWhoMap = 1;
							break;
						}
						default:
							break;
						}
					}
					if (IsSelectedWhoMap == 1)
						break;
				}
				break;
			}
			case ��ȡ��Ϸ:
			{
				IsSelectedPlay = 1;
				char* gameFile = game.ShowGameFile();
				game.LoadGameFile(myTank, enemyTank, map, gameFile);
				break;
			}
			case �˳���Ϸ:
				return 0;
			default:
				break;
			}
		}
		if (IsSelectedPlay)//ѡ�������������Ϸ
			break;
	}

	// ��̬��Ϣ
	map.DrawStaticMap();
	game.DrawGameHelp();

	// ��ѭ��
	while (game.GetIsRunning())
	{
		// ������Ӧ�ؿ�
		if (game.GetStage() > 1 && game.GetNeedLoadNewStage() && game.GetStage() <= game.GetMaxStage())
		{
			// �����ͼ�ļ��������Ѷ�
			switch (game.GetStage())
			{
			case 2:
				map.LoadMapFile(const_cast<char*>("Stage2.i"), map);
				game.SetLevelEneTank(200);
				game.SetLevelEneBul(70);
				break;
			case 3:
				map.LoadMapFile(const_cast<char*>("Stage3.i"), map);
				game.SetLevelEneTank(100);
				game.SetLevelEneBul(50);
				break;
			default:
				break;
			}
			// ����
			system("cls");
			//���´�ӡ��̬��Ϣ
			map.DrawStaticMap();
			game.DrawGameHelp();
			// �������ɵо�̹��
			enemyTank.push_back(enemyTankA);
			enemyTank.push_back(enemyTankB);
			enemyTank.push_back(enemyTankC);
			enemyTank.push_back(enemyTankD);
			enemyTank.push_back(enemyTankE);
			// ��ǹؿ��������
			game.SetNeedLoadNewStage(false);
		}
		// ��̬ʵʱ��ʾ
		game.DrawGameInfo(myTank, enemyTank);
		map.DrawDynamicMap();
		// �ҷ�̹���߳�
		if (clock() - time4Tank >= 100)
		{
			for (vector<CTank>::iterator it = myTank.begin(); it != myTank.end();)
			{
				time4Tank = clock();
				COORD oldCore = it->GetCore();
				COORD oldBody[5] = { it->GetBody(0),it->GetBody(1),it->GetBody(2),it->GetBody(3),it->GetBody(4) };
				it->ManipulateTank(myTank, enemyTank, map, game);
				it->CleanTankTail(oldCore, oldBody);
				it->DrawTank();
				// ��������ɾ����������������
				if (!it->GetIsAlive())
				{
					// ɾ��̹��ǰ��Ĩ���ӵ�������ֹ�߽类Ĩ�������ù��ϰ������Ƕ�̬�ģ����߽��Ǿ�̬�ģ�
					if (map.GetArrMap(it->m_bullet.GetCore().X, it->m_bullet.GetCore().Y) != �߽�)
					{
						GotoxyAndPrint(it->m_bullet.GetCore().X, it->m_bullet.GetCore().Y, " ");// Ĩ�����ӵ�
					}
					it = myTank.erase(it);//ɾ����������Զ�ָ����һ��
				}
				else
				{
					it++;
				}
				if (myTank.size() == 0)
				{
					game.SetIsOver(true);
				}
			}
		}
		// �ҷ��ӵ��߳�
		if (clock() - time4Bullet >= 50)
		{
			for (vector<CTank>::iterator it = myTank.begin(); it != myTank.end(); it++)
			{
				if (it->m_bullet.GetState() != ������)
				{
					//�ӵ���ֵ
					if (it->m_bullet.GetState() == δ��ֵ)//==1δ��ֵ״̬
					{
						//it->SetBullet(*it, �Ѹ�ֵ);
						it->m_bullet.SetBullet(*it);
						it->m_bullet.SetState(�Ѹ�ֵ);
					}
					//�ӵ��ƶ�
					time4Bullet = clock();
					COORD oldBulCore = it->m_bullet.GetCore();
					it->m_bullet.MoveBullet();
					it->m_bullet.CleanBullet(oldBulCore);
					it->m_bullet.DrawBullet(map);
					it->m_bullet.IsBulMeetOther(*it, myTank, enemyTank, map, game);
				}
			}
		}
		// �з�̹���߳�
		if (clock() - time4EnemyTank >= game.GetLevelEneTank())
		{
			for (vector<CTank>::iterator it = enemyTank.begin(); it != enemyTank.end();)
			{
				time4EnemyTank = clock();
				COORD oldCore = it->GetCore();
				COORD oldBody[5] = { it->GetBody(0),it->GetBody(1),it->GetBody(2),it->GetBody(3),it->GetBody(4) };
				it->ManipulateTank(myTank, enemyTank, map, game);
				it->CleanTankTail(oldCore, oldBody);
				it->DrawTank();
				// ̹���������
				if (!it->GetIsAlive())
				{
					// ɾ��̹��ǰ��Ĩ���ӵ�������ֹ�߽类Ĩ��
					if (map.GetArrMap(it->m_bullet.GetCore().X, it->m_bullet.GetCore().Y) != �߽�)
					{
						GotoxyAndPrint(it->m_bullet.GetCore().X, it->m_bullet.GetCore().Y, " ");// Ĩ�����ӵ�
					}
					it = enemyTank.erase(it);//ɾ���������ָ����һ��
				}
				else
				{
					//δ��������������
					it++;
				}
			}
		}
		// �з��ӵ��߳�
		if (clock() - time4EnemyBullet >= game.GetLevelEneBul())
		{
			for (vector<CTank>::iterator it = enemyTank.begin(); it != enemyTank.end(); it++)
			{
				if (it->m_bullet.GetState() != ������)
				{
					//�ӵ���ֵ
					if (it->m_bullet.GetState() == δ��ֵ)//==1δ��ֵ״̬
					{
						it->m_bullet.SetBullet(*it);
						it->m_bullet.SetState(�Ѹ�ֵ);
					}
					//�ӵ��ƶ�
					time4EnemyBullet = clock();
					COORD oldBulCore = it->m_bullet.GetCore();
					it->m_bullet.MoveBullet();
					it->m_bullet.CleanBullet(oldBulCore);
					it->m_bullet.DrawBullet(map);
					it->m_bullet.IsBulMeetOther(*it, myTank, enemyTank, map, game);
				}
			}
		}
		// �ж���Ϸ�������ҷ�ȫ������ȫ��ͨ��
		if (game.GetIsOver() || game.GetStage() > game.GetMaxStage())
		{
			game.GameOver(enemyTank);
			break;
		}
		// �ж��Ƿ����
		if (enemyTank.size() == 0)
		{
			game.NextStage();
			continue;
		}
	}

	// ���Ķ����ַ�
	char ch = _getch();
	ch = _getch();

	return 0;
}