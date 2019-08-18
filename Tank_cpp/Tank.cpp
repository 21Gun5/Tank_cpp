#include <stdio.h>
#include <time.h>
#include "Data.h"
#include "Func.h"
#include <conio.h>

int main()
{
	//��ʼ��
	GameInit();
	int time4Tank = 0;
	int time4Bullet = 0;
	int time4EnemyTank = 0;
	int time4EnemyBullet = 0;

	//�ҷ�̹��
	TANK tank = {
		{MAP_X_WALL / 4, MAP_Y / 2},
		{0},UP,3,true,�ҷ�̹��,
		{{0},UP,������}
	};
	SetTankShape(&tank);//������̬
	//�з�̹��
	TANK enemyTank[ENEMY_TANK_AMOUNT] = {
		{{2, 2}, {0},DOWN ,2,true,�з�̹��,{{0},UP,������}},
		{{MAP_X_WALL / 4, 2}, {0},UP,1,true,�з�̹��,{{0},UP,������} },
		{{MAP_X_WALL / 2 - 2, 2}, {0},DOWN,2,true,�з�̹��,{{0},UP,������} },
		{{2,  MAP_Y / 2}, {0},UP ,1,true,�з�̹��,{{0},UP,������}},
		{{MAP_X_WALL / 2 - 2,  MAP_Y / 2}, {0},UP,1,true,�з�̹��,{{0},UP,������} },
		{{2,  MAP_Y - 3}, {0},UP ,2,true,�з�̹��,{{0},UP,������}},
		//{{MAP_X_WALL / 4, MAP_Y - 3} ,{0},UP ,2,true,�з�̹��,{{0},UP,������} },
		{{MAP_X_WALL / 2 - 2,  MAP_Y - 3}, {0},UP,2,true,�з�̹��,{{0},UP,������} }
	};
	for (int i = 0; i < ENEMY_TANK_AMOUNT; i++) { SetTankShape(&enemyTank[i]); }//������̬

	//���̿���
	int indexForPlay = 0;		//�˵�����
	bool IsSelectedPlay = 0;	//�Ƿ�ѡ�����
	while (true)
	{
		DrawMenu(menuPlay, _countof(menuPlay), indexForPlay);
		int play = SelectMenu(_countof(menuPlay), &indexForPlay);
		if (play == ENTER)
		{
			switch (indexForPlay)
			{
			case ��ʼ��Ϸ:
			{
				int indexForWhoMap = 0;//�˵�����
				bool IsSelectedWhoMap = 0; //ѡ���ѭ������
				while (true)
				{
					DrawMenu(menuWhoMap, _countof(menuWhoMap), indexForWhoMap);
					int whoMap = SelectMenu(_countof(menuWhoMap), &indexForWhoMap);
					if (whoMap == ENTER)
					{
						switch (indexForWhoMap)
						{
						case ϵͳĬ��:
						{
							int indexForLevel = 0;
							bool IsSelectedLevel = 0;
							while (true)
							{
								DrawMenu(menuLevel, _countof(menuLevel), indexForLevel);
								int level = SelectMenu(_countof(menuLevel), &indexForLevel);
								if (level == ENTER)
								{
									switch (indexForLevel)
									{
									case ��:
										g_levelEneTank = 300;
										g_levelEneBul = 90;
										IsSelectedLevel = 1;
										break;
									case һ��:
										g_levelEneTank = 200;
										g_levelEneBul = 70;
										IsSelectedLevel = 1;
										break;
									case ����:
										g_levelEneTank = 100;
										g_levelEneBul = 50;
										IsSelectedLevel = 1;
										break;
									default:
										break;
									}
								}
								if (IsSelectedLevel == 1)
									break;
							}
							SetDefaultMap();//ʹ��Ĭ�ϵ�
							IsSelectedPlay = 1;
							IsSelectedWhoMap = 1;
							g_isRunning = 1;//��Ϸ����
							break;
						}
						case ����ṩ:
						{
							int indexForWhenMap = 0;//�˵�����
							bool IsSelectedWhenMap = 0; //ѡ���ѭ������
							while (true)
							{
								DrawMenu(menuWhenMap, _countof(menuWhenMap), indexForWhenMap);
								int whenMap = SelectMenu(_countof(menuWhenMap), &indexForWhenMap);
								if (whenMap == ENTER)
								{
									switch (indexForWhenMap)
									{
									case �½���ͼ:
										IsSelectedPlay = 1;
										IsSelectedWhoMap = 1;
										IsSelectedWhenMap = 1;
										g_isRunning = 1;//Ҫ������Ϸ��
										CustomizeMap(&tank, enemyTank);//�ֶ����ò�ֱ��ʹ��
										break;
									case ���е�ͼ:
									{
										IsSelectedPlay = 1;
										IsSelectedWhoMap = 1;
										IsSelectedWhenMap = 1;
										g_isRunning = 1;//Ҫ������Ϸ��
										char* mapFile = ShowMapFile();
										LoadMapFile(mapFile);//�������е�ͼ
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
				char* gameFile = ShowGameFile();
				LoadGame(&tank, enemyTank, gameFile);
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

	//�߽缰�ϰ�
	DrawBorder();
	DrawGameHelp();
	DrawBarr();

	//��ѭ��
	while (g_isRunning)
	{
		//��Ϣʵʱ��ʾ
		DrawGameInfo(&tank, enemyTank);
		//�ҷ�̹���߳�
		if (clock() - time4Tank >= 100)
		{
			time4Tank = clock();
			COORD oldCore = tank.core;
			COORD oldBody[5] = { tank.body[0],tank.body[1],tank.body[2],tank.body[3],tank.body[4] };
			ManipulateMyTank(&tank, �ҷ�̹��, enemyTank);
			CleanTankTail(oldCore, oldBody);
			DrawTank(&tank, �ҷ�̹��);
		}
		//�ҷ��ӵ��߳�
		if (clock() - time4Bullet >= 50)
		{
			if (tank.bullet.state != ������)
			{
				//�ӵ���ֵ
				if (tank.bullet.state == δ��ֵ)//==1δ��ֵ״̬
				{
					tank.bullet = { {tank.body[0].X, tank.body[0].Y}, tank.dir };
					tank.bullet.state = �Ѹ�ֵ;
					//g_isBulExist++;//==2�Ѹ�ֵ״̬
				}
				//�ӵ��ƶ�
				time4Bullet = clock();
				COORD oldBulCore = tank.bullet.core;
				MoveBullet(&tank.bullet);
				CleanBullet(oldBulCore);
				DrawBullet(&tank.bullet, &tank);
				IsMyBulMeetOther(&tank.bullet, enemyTank, &tank);
			}
		}
		//�з�̹���߳�
		if (clock() - time4EnemyTank >= g_levelEneTank)
		{
			for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
			{
				time4EnemyTank = clock();
				COORD oldCore = enemyTank[i].core;
				COORD oldBody[5] = { enemyTank[i].body[0],enemyTank[i].body[1],enemyTank[i].body[2],enemyTank[i].body[3],enemyTank[i].body[4] };
				ManipulateEneTank(&enemyTank[i], �з�̹��, &tank, enemyTank);
				CleanTankTail(oldCore, oldBody);
				DrawTank(&enemyTank[i], �з�̹��);
			}
		}
		//�з��ӵ��߳�
		if (clock() - time4EnemyBullet >= g_levelEneBul)
		{
			for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
			{
				if (enemyTank[i].bullet.state != ������)
				{
					//�ӵ���ֵ
					if (enemyTank[i].bullet.state == δ��ֵ)//==1δ��ֵ״̬
					{
						enemyTank[i].bullet = { {enemyTank[i].body[0].X, enemyTank[i].body[0].Y}, enemyTank[i].dir };
						enemyTank[i].bullet.state = �Ѹ�ֵ;
					}
					//�ӵ��ƶ�
					time4EnemyBullet = clock();
					COORD oldBulCore = enemyTank[i].bullet.core;
					MoveBullet(&enemyTank[i].bullet);
					CleanBullet(oldBulCore);
					DrawBullet(&enemyTank[i].bullet, &enemyTank[i]);
					IsEneBulMeetOther(&enemyTank[i].bullet, enemyTank, &tank);
				}
			}
		}
		//�ж���Ϸ����
		if (tank.blood == 0 || GetLiveEnemyAmount(enemyTank) == 0)
		{
			GameOver(enemyTank);
			break;
		}
	}

	//���Ķ����ַ�
	char ch = _getch();
	ch = _getch();

	return 0;
}