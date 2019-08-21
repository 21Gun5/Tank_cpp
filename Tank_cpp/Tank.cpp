#include <conio.h>
#include "Tank.h"
#include "Map.h"
#include "Game.h"

//̹�����
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
	GotoxyAndPrint(oldCore.X, oldCore.Y, "  ");//���ĵ�
	for (int i = 0; i < 5; i++)//������
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
//	if (this->m_who == �ҷ�̹��A)
//	{
//		if (KEYDOWN('W'))//Сд���ɣ��ɴ�д��ASCII��
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
//			if (this->m_bullet.m_state != �Ѹ�ֵ)
//				this->m_bullet.m_state = δ��ֵ;//�Ѹ�ֵ������ʱ���ٿ��𣬲��ɸ�ֵΪ1��Ӧ����ʧΪ0ʱ����������Ч
//		}
//		else if (KEYDOWN('Q'))
//		{
//			//��ͣ���ָ�
//			mciSendString("pause bgm", NULL, 0, NULL);	//��ͣbgm
//			setColor(12, 0);
//			GotoxyAndPrint(MAP_X_WALL / 2 + 1, 1, "       ");//�Ȱѽϳ���running���
//			GotoxyAndPrint(MAP_X_WALL / 2 + 1, 1, "PAUSE");
//			GotoxyAndPrint(MAP_X_WALL / 2 + 1, 2, "1. �ص���Ϸ");
//			GotoxyAndPrint(MAP_X_WALL / 2 + 1, 3, "2. �˳���Ϸ");
//			char tmp;
//			do
//			{
//				tmp = _getch();	//��������������ͣ��Ϸ
//			} while (!(tmp == '1' || tmp == '2' || tmp == '3'));//ֻ������123�ſ�
//			switch (tmp)
//			{
//			case '1'://�ָ���Ϸ
//			{
//				mciSendString("resume bgm", NULL, 0, NULL);//�ָ�bgm
//				GotoxyAndPrint(MAP_X_WALL / 2 + 1, 1, "RUNNING");
//				GotoxyAndPrint(MAP_X_WALL / 2 + 1, 2, "Q: ��ͣ��Ϸ");
//				GotoxyAndPrint(MAP_X_WALL / 2 + 1, 3, "           ");
//				GotoxyAndPrint(MAP_X_WALL / 2 + 1, 4, "           ");
//				break;
//			}
//			case '2'://�˳���Ϸ
//			{
//				GotoxyAndPrint(MAP_X_WALL / 2 + 1, 1, "������˳�?");
//				GotoxyAndPrint(MAP_X_WALL / 2 + 1, 2, "1. �����˳�");
//				GotoxyAndPrint(MAP_X_WALL / 2 + 1, 3, "2. ֱ���˳�");
//				char op = _getch();
//				if (op == '1')		//�����˳�
//				{
//					game.SaveGameFile(pMyTank, pEnemyTank, map);
//					game.GameOver(pEnemyTank);
//					game.m_isRunning = false;
//					break;
//				}
//				else if (op == '2')	//ֱ���˳�
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
//	else if (this->m_who == �ҷ�̹��B)
//	{
//		if (KEYDOWN('I'))//Сд���ɣ��ɴ�д��ASCII��
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
//			if (this->m_bullet.m_state != �Ѹ�ֵ)
//				this->m_bullet.m_state = δ��ֵ;//�Ѹ�ֵ������ʱ���ٿ��𣬲��ɸ�ֵΪ1��Ӧ����ʧΪ0ʱ����������Ч
//		}
//	}
//	SetTankShape();//ÿ���ƶ���Ҫ����������̬
//}

//bool CTank::IsTankMeetOther(int dir,CTank * pMyTank, CTank* pEnemyTank, CMap map)
//{
//	switch (dir)
//	{
//	case UP:
//		//�Ƿ�ײ�߽�
//		if (this->m_core.Y <= 2)
//		{
//			return true;
//		}
//		//�Ƿ�ײ�ϰ���
//		if ((map.m_nArrMap[m_core.X][m_core.Y - 2] == ���� || map.m_nArrMap[m_core.X - 1][m_core.Y - 2] == ���� || map.m_nArrMap[m_core.X + 1][m_core.Y - 2] == ����) ||
//			(map.m_nArrMap[m_core.X][m_core.Y - 2] == ʯ�� || map.m_nArrMap[m_core.X - 1][m_core.Y - 2] == ʯ�� || map.m_nArrMap[m_core.X + 1][m_core.Y - 2] == ʯ��) ||
//			(map.m_nArrMap[m_core.X][m_core.Y - 2] == ���� || map.m_nArrMap[m_core.X - 1][m_core.Y - 2] == ���� || map.m_nArrMap[m_core.X + 1][m_core.Y - 2] == ����))
//		{
//			return true;
//		}
//		//�Ƿ�ײ�ҷ�����
//		for (int i = 0; i < MY_TANK_AMOUNT; i++)
//		{
//			if (this->m_core.X == pMyTank[i].m_core.X && this->m_core.Y == pMyTank[i].m_core.Y)//�ų��Լ�
//				continue;
//			if (
//				((this->m_core.X == pMyTank[i].m_core.X) && (this->m_core.Y - pMyTank[i].m_core.Y == 3)) ||
//				((this->m_core.X == pMyTank[i].m_core.X - 1) && (this->m_core.Y - pMyTank[i].m_core.Y == 3)) ||
//				((this->m_core.X == pMyTank[i].m_core.X - 2) && (this->m_core.Y - pMyTank[i].m_core.Y == 3)) ||
//				((this->m_core.X == pMyTank[i].m_core.X + 1) && (this->m_core.Y - pMyTank[i].m_core.Y == 3)) ||
//				((this->m_core.X == pMyTank[i].m_core.X + 2) && (this->m_core.Y - pMyTank[i].m_core.Y == 3))
//				)//Ҫ==3,����<=��ֻ���ڰ��ŵ�ʱ��ɱ��������С�ڣ���û���ŵ�̹1��������ȴС��2����2����
//			{
//				return true;
//			}
//		}
//		//�Ƿ�ײ�з�̹��
//		for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
//		{
//			if (pEnemyTank[i].m_isAlive == false) continue;
//			if (
//				((this->m_core.X == pEnemyTank[i].m_core.X) && (this->m_core.Y - pEnemyTank[i].m_core.Y == 3)) ||
//				((this->m_core.X == pEnemyTank[i].m_core.X - 1) && (this->m_core.Y - pEnemyTank[i].m_core.Y == 3)) ||
//				((this->m_core.X == pEnemyTank[i].m_core.X - 2) && (this->m_core.Y - pEnemyTank[i].m_core.Y == 3)) ||
//				((this->m_core.X == pEnemyTank[i].m_core.X + 1) && (this->m_core.Y - pEnemyTank[i].m_core.Y == 3)) ||
//				((this->m_core.X == pEnemyTank[i].m_core.X + 2) && (this->m_core.Y - pEnemyTank[i].m_core.Y == 3))
//				)//Ҫ==3,����<=��ֻ���ڰ��ŵ�ʱ��ɱ��������С�ڣ���û���ŵ�̹1��������ȴС��2����2����
//			{
//				return true;
//			}
//		}
//		break;
//	case DOWN:
//		//�Ƿ�ײ�߽�
//		if (this->m_core.Y >= MAP_Y - 3) 
//			return true;
//		//�Ƿ�ײ�ϰ���
//		if ((map.m_nArrMap[m_core.X][m_core.Y + 2] == ���� || map.m_nArrMap[m_core.X - 1][m_core.Y + 2] == ���� || map.m_nArrMap[m_core.X + 1][m_core.Y + 2] == ����) ||
//			(map.m_nArrMap[m_core.X][m_core.Y + 2] == ʯ�� || map.m_nArrMap[m_core.X - 1][m_core.Y + 2] == ʯ�� || map.m_nArrMap[m_core.X + 1][m_core.Y + 2] == ʯ��) ||
//			(map.m_nArrMap[m_core.X][m_core.Y + 2] == ���� || map.m_nArrMap[m_core.X - 1][m_core.Y + 2] == ���� || map.m_nArrMap[m_core.X + 1][m_core.Y + 2] == ����))
//		{
//			return true;
//		}
//		//�Ƿ������Ҽ�Ȫˮ
//		if (map.m_nArrMap[this->m_core.X][this->m_core.Y] == Ȫˮ)
//		{
//			return true;
//		}
//		//�Ƿ�ײ�ҷ�����
//		for (int i = 0; i < MY_TANK_AMOUNT; i++)
//		{
//			if (this->m_core.X == pMyTank[i].m_core.X && this->m_core.Y == pMyTank[i].m_core.Y)//�ų��Լ�
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
//		//�Ƿ�ײ�з�̹��
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
//		//�Ƿ�ײ�߽�
//		if (this->m_core.X <= 2)
//		{
//			return true;
//		}
//		//�Ƿ�ײ�ϰ���
//		if ((map.m_nArrMap[m_core.X - 2][m_core.Y] == ���� || map.m_nArrMap[m_core.X - 2][m_core.Y - 1] == ���� || map.m_nArrMap[m_core.X - 2][m_core.Y + 1] == ����) ||
//			(map.m_nArrMap[m_core.X - 2][m_core.Y] == ʯ�� || map.m_nArrMap[m_core.X - 2][m_core.Y - 1] == ʯ�� || map.m_nArrMap[m_core.X - 2][m_core.Y + 1] == ʯ��) ||
//			(map.m_nArrMap[m_core.X - 2][m_core.Y] == ���� || map.m_nArrMap[m_core.X - 2][m_core.Y - 1] == ���� || map.m_nArrMap[m_core.X - 2][m_core.Y + 1] == ����))
//		{
//			return true;
//		}
//		//�Ƿ������Ҽ�Ȫˮ
//		if (map.m_nArrMap[this->m_core.X][this->m_core.Y] == Ȫˮ)
//		{
//			return true;
//		}
//		//�Ƿ�ײ�ҷ�����
//		for (int i = 0; i < MY_TANK_AMOUNT; i++)
//		{
//			if (this->m_core.X == pMyTank[i].m_core.X && this->m_core.Y == pMyTank[i].m_core.Y)//�ų��Լ�
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
//		//�Ƿ�ײ�з�̹��
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
//		//�Ƿ�ײ�߽�
//		if (this->m_core.X >= MAP_X_WALL / 2 - 2)
//		{
//			return true;
//		}
//		//�Ƿ�ײ�ϰ���
//		if ((map.m_nArrMap[m_core.X + 2][m_core.Y] == ���� || map.m_nArrMap[m_core.X + 2][m_core.Y - 1] == ���� || map.m_nArrMap[m_core.X + 2][m_core.Y + 1] == ����) ||
//			(map.m_nArrMap[m_core.X + 2][m_core.Y] == ʯ�� || map.m_nArrMap[m_core.X + 2][m_core.Y - 1] == ʯ�� || map.m_nArrMap[m_core.X + 2][m_core.Y + 1] == ʯ��) ||
//			(map.m_nArrMap[m_core.X + 2][m_core.Y] == ���� || map.m_nArrMap[m_core.X + 2][m_core.Y - 1] == ���� || map.m_nArrMap[m_core.X + 2][m_core.Y + 1] == ����))
//		{
//			return true;
//		}
//		//�Ƿ������Ҽ�Ȫˮ
//		if (map.m_nArrMap[this->m_core.X][this->m_core.Y] == Ȫˮ)
//		{
//			return true;
//		}
//		//�Ƿ�ײ�ҷ�����
//		for (int i = 0; i < MY_TANK_AMOUNT; i++)
//		{
//			if (this->m_core.X == pMyTank[i].m_core.X && this->m_core.Y == pMyTank[i].m_core.Y)//�ų��Լ�
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
//		//�Ƿ�ײ�з�̹��
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
	if (this->m_who == �ҷ�̹��A)
	{
		if (KEYDOWN('W'))//Сд���ɣ��ɴ�д��ASCII��
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
			if (this->m_bullet.m_state != �Ѹ�ֵ)
				this->m_bullet.m_state = δ��ֵ;//�Ѹ�ֵ������ʱ���ٿ��𣬲��ɸ�ֵΪ1��Ӧ����ʧΪ0ʱ����������Ч
		}
		else if (KEYDOWN('Q'))
		{
			//��ͣ���ָ�
			mciSendString("pause bgm", NULL, 0, NULL);	//��ͣbgm
			setColor(12, 0);
			GotoxyAndPrint(MAP_X_WALL / 2 + 1, 1, "       ");//�Ȱѽϳ���running���
			GotoxyAndPrint(MAP_X_WALL / 2 + 1, 1, "PAUSE");
			GotoxyAndPrint(MAP_X_WALL / 2 + 1, 2, "1. �ص���Ϸ");
			GotoxyAndPrint(MAP_X_WALL / 2 + 1, 3, "2. �˳���Ϸ");
			char tmp;
			do
			{
				tmp = _getch();	//��������������ͣ��Ϸ
			} while (!(tmp == '1' || tmp == '2' || tmp == '3'));//ֻ������123�ſ�
			switch (tmp)
			{
			case '1'://�ָ���Ϸ
			{
				mciSendString("resume bgm", NULL, 0, NULL);//�ָ�bgm
				GotoxyAndPrint(MAP_X_WALL / 2 + 1, 1, "RUNNING");
				GotoxyAndPrint(MAP_X_WALL / 2 + 1, 2, "Q: ��ͣ��Ϸ");
				GotoxyAndPrint(MAP_X_WALL / 2 + 1, 3, "           ");
				GotoxyAndPrint(MAP_X_WALL / 2 + 1, 4, "           ");
				break;
			}
			case '2'://�˳���Ϸ
			{
				GotoxyAndPrint(MAP_X_WALL / 2 + 1, 1, "������˳�?");
				GotoxyAndPrint(MAP_X_WALL / 2 + 1, 2, "1. �����˳�");
				GotoxyAndPrint(MAP_X_WALL / 2 + 1, 3, "2. ֱ���˳�");
				char op = _getch();
				if (op == '1')		//�����˳�
				{
					game.SaveGameFile(pMyTank, pEnemyTank, map);
					game.GameOver(pEnemyTank);
					game.m_isRunning = false;
					break;
				}
				else if (op == '2')	//ֱ���˳�
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
	else if (this->m_who == �ҷ�̹��B)
	{
		if (KEYDOWN('I'))//Сд���ɣ��ɴ�д��ASCII��
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
			if (this->m_bullet.m_state != �Ѹ�ֵ)
				this->m_bullet.m_state = δ��ֵ;//�Ѹ�ֵ������ʱ���ٿ��𣬲��ɸ�ֵΪ1��Ӧ����ʧΪ0ʱ����������Ч
		}
	}
	else if (this->m_who == �з�̹��)
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
		if (this->m_bullet.m_state != �Ѹ�ֵ)
			this->m_bullet.m_state = δ��ֵ;
		break;
	default:
		break;
	}
	}

	SetTankShape();//ÿ���ƶ���Ҫ����������̬
}

//void CTank::ManipulateEneTank(CTank* pMyTank, CTank* pEnemyTank, CMap map)
//{
//	if (this->m_isAlive == false) return;
//	if (this->m_who == �з�̹��)
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
//			if (this->m_bullet.m_state != �Ѹ�ֵ)
//				this->m_bullet.m_state = δ��ֵ;
//			break;
//		default:
//			break;
//		}
//	}
//	SetTankShape();//ÿ���ƶ���Ҫ����������̬
//}

//bool CTank::IsEneTankMeetOther(int dir, CTank *pMyTank, CTank* pEnemyTank,CMap map)
//{
//	switch (dir)
//	{
//	case UP:
//		//�Ƿ�ײ�߽�
//		if (this->m_core.Y <= 2)
//		{
//			return true;
//		}
//		//�Ƿ�ײ�ϰ���
//		if ((map.m_nArrMap[m_core.X][m_core.Y - 2] == ���� || map.m_nArrMap[m_core.X - 1][m_core.Y - 2] == ���� || map.m_nArrMap[m_core.X + 1][m_core.Y - 2] == ����) ||
//			(map.m_nArrMap[m_core.X][m_core.Y - 2] == ʯ�� || map.m_nArrMap[m_core.X - 1][m_core.Y - 2] == ʯ�� || map.m_nArrMap[m_core.X + 1][m_core.Y - 2] == ʯ��) ||
//			(map.m_nArrMap[m_core.X][m_core.Y - 2] == ���� || map.m_nArrMap[m_core.X - 1][m_core.Y - 2] == ���� || map.m_nArrMap[m_core.X + 1][m_core.Y - 2] == ����))
//		{
//			return true;
//		}
//		//�Ƿ�ײ�ҷ�̹��
//		for (int i = 0; i < MY_TANK_AMOUNT; i++)
//		{
//			if (
//				((this->m_core.X == pMyTank[i].m_core.X - 0) && (this->m_core.Y - pMyTank[i].m_core.Y == 3)) ||
//				((this->m_core.X == pMyTank[i].m_core.X - 1) && (this->m_core.Y - pMyTank[i].m_core.Y == 3)) ||
//				((this->m_core.X == pMyTank[i].m_core.X - 2) && (this->m_core.Y - pMyTank[i].m_core.Y == 3)) ||
//				((this->m_core.X == pMyTank[i].m_core.X + 1) && (this->m_core.Y - pMyTank[i].m_core.Y == 3)) ||
//				((this->m_core.X == pMyTank[i].m_core.X + 2) && (this->m_core.Y - pMyTank[i].m_core.Y == 3))
//				)//Ҫ==3,����<=��ֻ���ڰ��ŵ�ʱ��ɱ��������С�ڣ���û���ŵ�̹1��������ȴС��2����2����
//			{
//				return true;
//			}
//		}
//		//�Ƿ�ײ�����з�̹��
//		for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
//		{
//			if (this->m_core.X == pEnemyTank[i].m_core.X && this->m_core.Y == pEnemyTank[i].m_core.Y)//�ų��Լ�
//				continue;
//			if (
//				((this->m_core.X == pEnemyTank[i].m_core.X) && (this->m_core.Y - pEnemyTank[i].m_core.Y == 3)) ||
//				((this->m_core.X == pEnemyTank[i].m_core.X - 1) && (this->m_core.Y - pEnemyTank[i].m_core.Y == 3)) ||
//				((this->m_core.X == pEnemyTank[i].m_core.X - 2) && (this->m_core.Y - pEnemyTank[i].m_core.Y == 3)) ||
//				((this->m_core.X == pEnemyTank[i].m_core.X + 1) && (this->m_core.Y - pEnemyTank[i].m_core.Y == 3)) ||
//				((this->m_core.X == pEnemyTank[i].m_core.X + 2) && (this->m_core.Y - pEnemyTank[i].m_core.Y == 3))
//				)//Ҫ==3,����<=��ֻ���ڰ��ŵ�ʱ��ɱ��������С�ڣ���û���ŵ�̹1��������ȴС��2����2����
//			{
//				return true;
//			}
//		}
//		break;
//	case DOWN:
//		//�Ƿ�ײ�߽�
//		if (this->m_core.Y >= MAP_Y - 3)
//		{
//			return true;
//		}
//		//�Ƿ�ײ�ϰ���
//		if ((map.m_nArrMap[m_core.X][m_core.Y + 2] == ���� || map.m_nArrMap[m_core.X - 1][m_core.Y + 2] == ���� || map.m_nArrMap[m_core.X + 1][m_core.Y + 2] == ����) ||
//			(map.m_nArrMap[m_core.X][m_core.Y + 2] == ʯ�� || map.m_nArrMap[m_core.X - 1][m_core.Y + 2] == ʯ�� || map.m_nArrMap[m_core.X + 1][m_core.Y + 2] == ʯ��) ||
//			(map.m_nArrMap[m_core.X][m_core.Y + 2] == ���� || map.m_nArrMap[m_core.X - 1][m_core.Y + 2] == ���� || map.m_nArrMap[m_core.X + 1][m_core.Y + 2] == ����) )
//		{
//			return true;
//		}
//		//�Ƿ������Ҽ�Ȫˮ
//		if (map.m_nArrMap[this->m_core.X][this->m_core.Y] == Ȫˮ)
//		{
//			return true;
//		}
//		//�Ƿ�ײ�ҷ�̹��
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
//		//�Ƿ�ײ�����з�̹��
//		for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
//		{
//			if (this->m_core.X == pEnemyTank[i].m_core.X && this->m_core.Y == pEnemyTank[i].m_core.Y)//�ų��Լ�
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
//		//�Ƿ�ײ�߽�
//		if (this->m_core.X <= 2)
//		{
//			return true;
//		}
//		//�Ƿ�ײ�ϰ���
//		if ((map.m_nArrMap[m_core.X - 2][m_core.Y] == ���� || map.m_nArrMap[m_core.X - 2][m_core.Y - 1] == ���� || map.m_nArrMap[m_core.X - 2][m_core.Y + 1] == ����) ||
//			(map.m_nArrMap[m_core.X - 2][m_core.Y] == ʯ�� || map.m_nArrMap[m_core.X - 2][m_core.Y - 1] == ʯ�� || map.m_nArrMap[m_core.X - 2][m_core.Y + 1] == ʯ��) ||
//			(map.m_nArrMap[m_core.X - 2][m_core.Y] == ���� || map.m_nArrMap[m_core.X - 2][m_core.Y - 1] == ���� || map.m_nArrMap[m_core.X - 2][m_core.Y + 1] == ����))
//		{
//			return true;
//		}
//		//�Ƿ������Ҽ�Ȫˮ
//		if (map.m_nArrMap[this->m_core.X][this->m_core.Y] == Ȫˮ)
//		{
//			return true;
//		}
//		//�Ƿ�ײ�ҷ�̹��
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
//		//�Ƿ�ײ�����з�̹��
//		for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
//		{
//			if (this->m_core.X == pEnemyTank[i].m_core.X && this->m_core.Y == pEnemyTank[i].m_core.Y)//�ų��Լ�
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
//		//�Ƿ�ײ�߽�
//		if (this->m_core.X >= MAP_X_WALL / 2 - 2)
//		{
//			return true;
//		}
//		//�Ƿ�ײ�ϰ���
//		if ((map.m_nArrMap[m_core.X + 2][m_core.Y] == ���� || map.m_nArrMap[m_core.X + 2][m_core.Y - 1] == ���� || map.m_nArrMap[m_core.X + 2][m_core.Y + 1] == ����) ||
//			(map.m_nArrMap[m_core.X + 2][m_core.Y] == ʯ�� || map.m_nArrMap[m_core.X + 2][m_core.Y - 1] == ʯ�� || map.m_nArrMap[m_core.X + 2][m_core.Y + 1] == ʯ��) ||
//			(map.m_nArrMap[m_core.X + 2][m_core.Y] == ���� || map.m_nArrMap[m_core.X + 2][m_core.Y - 1] == ���� || map.m_nArrMap[m_core.X + 2][m_core.Y + 1] == ����))
//		{
//			return true;
//		}
//		//�Ƿ������Ҽ�Ȫˮ
//		if (map.m_nArrMap[this->m_core.X][this->m_core.Y] == Ȫˮ)
//		{
//			return true;
//		}
//		//�Ƿ�ײ�ҷ�̹��
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
//		//�Ƿ�ײ�����з�̹��
//		for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
//		{
//			if (this->m_core.X == pEnemyTank[i].m_core.X && this->m_core.Y == pEnemyTank[i].m_core.Y)//�ų��Լ�
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
		//�Ƿ�ײ�߽�
		if (this->m_core.Y <= 2)
		{
			return true;
		}
		//�Ƿ�ײ�ϰ���
		if ((map.m_nArrMap[m_core.X][m_core.Y - 2] == ���� || map.m_nArrMap[m_core.X - 1][m_core.Y - 2] == ���� || map.m_nArrMap[m_core.X + 1][m_core.Y - 2] == ����) ||
			(map.m_nArrMap[m_core.X][m_core.Y - 2] == ʯ�� || map.m_nArrMap[m_core.X - 1][m_core.Y - 2] == ʯ�� || map.m_nArrMap[m_core.X + 1][m_core.Y - 2] == ʯ��) ||
			(map.m_nArrMap[m_core.X][m_core.Y - 2] == ���� || map.m_nArrMap[m_core.X - 1][m_core.Y - 2] == ���� || map.m_nArrMap[m_core.X + 1][m_core.Y - 2] == ����))
		{
			return true;
		}
		//�Ƿ�ײ�ҷ�̹��
		for (int i = 0; i < MY_TANK_AMOUNT; i++)
		{
			//������̹���������Լ�
			if (m_who != �з�̹��)
			{
				if (this->m_core.X == pMyTank[i].m_core.X && this->m_core.Y == pMyTank[i].m_core.Y)//�ų��Լ�
					continue;
			}
			// ����̹�����������赲
			if (pMyTank[i].m_isAlive == false) continue;
			if (
				((this->m_core.X == pMyTank[i].m_core.X - 0) && (this->m_core.Y - pMyTank[i].m_core.Y == 3)) ||
				((this->m_core.X == pMyTank[i].m_core.X - 1) && (this->m_core.Y - pMyTank[i].m_core.Y == 3)) ||
				((this->m_core.X == pMyTank[i].m_core.X - 2) && (this->m_core.Y - pMyTank[i].m_core.Y == 3)) ||
				((this->m_core.X == pMyTank[i].m_core.X + 1) && (this->m_core.Y - pMyTank[i].m_core.Y == 3)) ||
				((this->m_core.X == pMyTank[i].m_core.X + 2) && (this->m_core.Y - pMyTank[i].m_core.Y == 3))
				)//Ҫ==3,����<=��ֻ���ڰ��ŵ�ʱ��ɱ��������С�ڣ���û���ŵ�̹1��������ȴС��2����2����
			{
				return true;
			}
		}
		//�Ƿ�ײ�з�̹��
		for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
		{
			//���ǵ�̹���������Լ�
			if (m_who == �з�̹��)
			{
				if (this->m_core.X == pEnemyTank[i].m_core.X && this->m_core.Y == pEnemyTank[i].m_core.Y)//�ų��Լ�
					continue;
			}
			// ����̹�����������赲
			if (pEnemyTank[i].m_isAlive == false) continue;
			if (
				((this->m_core.X == pEnemyTank[i].m_core.X) && (this->m_core.Y - pEnemyTank[i].m_core.Y == 3)) ||
				((this->m_core.X == pEnemyTank[i].m_core.X - 1) && (this->m_core.Y - pEnemyTank[i].m_core.Y == 3)) ||
				((this->m_core.X == pEnemyTank[i].m_core.X - 2) && (this->m_core.Y - pEnemyTank[i].m_core.Y == 3)) ||
				((this->m_core.X == pEnemyTank[i].m_core.X + 1) && (this->m_core.Y - pEnemyTank[i].m_core.Y == 3)) ||
				((this->m_core.X == pEnemyTank[i].m_core.X + 2) && (this->m_core.Y - pEnemyTank[i].m_core.Y == 3))
				)//Ҫ==3,����<=��ֻ���ڰ��ŵ�ʱ��ɱ��������С�ڣ���û���ŵ�̹1��������ȴС��2����2����
			{
				return true;
			}
		}
		break;
	case DOWN:
		//�Ƿ�ײ�߽�
		if (this->m_core.Y >= MAP_Y - 3)
		{
			return true;
		}
		//�Ƿ�ײ�ϰ���
		if ((map.m_nArrMap[m_core.X][m_core.Y + 2] == ���� || map.m_nArrMap[m_core.X - 1][m_core.Y + 2] == ���� || map.m_nArrMap[m_core.X + 1][m_core.Y + 2] == ����) ||
			(map.m_nArrMap[m_core.X][m_core.Y + 2] == ʯ�� || map.m_nArrMap[m_core.X - 1][m_core.Y + 2] == ʯ�� || map.m_nArrMap[m_core.X + 1][m_core.Y + 2] == ʯ��) ||
			(map.m_nArrMap[m_core.X][m_core.Y + 2] == ���� || map.m_nArrMap[m_core.X - 1][m_core.Y + 2] == ���� || map.m_nArrMap[m_core.X + 1][m_core.Y + 2] == ����))
		{
			return true;
		}
		//�Ƿ������Ҽ�Ȫˮ
		if (map.m_nArrMap[this->m_core.X][this->m_core.Y] == Ȫˮ)
		{
			return true;
		}
		//�Ƿ�ײ�ҷ�̹��
		for (int i = 0; i < MY_TANK_AMOUNT; i++)
		{
			//������̹���������Լ�
			if (m_who != �з�̹��)
			{
				if (this->m_core.X == pMyTank[i].m_core.X && this->m_core.Y == pMyTank[i].m_core.Y)//�ų��Լ�
					continue;
			}
			// ����̹�����������赲
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
		//�Ƿ�ײ�����з�̹��
		for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
		{
			//���ǵ�̹���������Լ�
			if (m_who == �з�̹��)
			{
				if (this->m_core.X == pEnemyTank[i].m_core.X && this->m_core.Y == pEnemyTank[i].m_core.Y)//�ų��Լ�
					continue;
			}
			// ����̹�����������赲
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
		//�Ƿ�ײ�߽�
		if (this->m_core.X <= 2)
		{
			return true;
		}
		//�Ƿ�ײ�ϰ���
		if ((map.m_nArrMap[m_core.X - 2][m_core.Y] == ���� || map.m_nArrMap[m_core.X - 2][m_core.Y - 1] == ���� || map.m_nArrMap[m_core.X - 2][m_core.Y + 1] == ����) ||
			(map.m_nArrMap[m_core.X - 2][m_core.Y] == ʯ�� || map.m_nArrMap[m_core.X - 2][m_core.Y - 1] == ʯ�� || map.m_nArrMap[m_core.X - 2][m_core.Y + 1] == ʯ��) ||
			(map.m_nArrMap[m_core.X - 2][m_core.Y] == ���� || map.m_nArrMap[m_core.X - 2][m_core.Y - 1] == ���� || map.m_nArrMap[m_core.X - 2][m_core.Y + 1] == ����))
		{
			return true;
		}
		//�Ƿ������Ҽ�Ȫˮ
		if (map.m_nArrMap[this->m_core.X][this->m_core.Y] == Ȫˮ)
		{
			return true;
		}
		//�Ƿ�ײ�ҷ�̹��
		for (int i = 0; i < MY_TANK_AMOUNT; i++)
		{
			//������̹���������Լ�
			if (m_who != �з�̹��)
			{
				if (this->m_core.X == pMyTank[i].m_core.X && this->m_core.Y == pMyTank[i].m_core.Y)//�ų��Լ�
					continue;
			}
			// ����̹�����������赲
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
		//�Ƿ�ײ�����з�̹��
		for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
		{
			//���ǵ�̹���������Լ�
			if (m_who == �з�̹��)
			{
				if (this->m_core.X == pEnemyTank[i].m_core.X && this->m_core.Y == pEnemyTank[i].m_core.Y)//�ų��Լ�
					continue;
			}
			// ����̹�����������赲
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
		//�Ƿ�ײ�߽�
		if (this->m_core.X >= MAP_X_WALL / 2 - 2)
		{
			return true;
		}
		//�Ƿ�ײ�ϰ���
		if ((map.m_nArrMap[m_core.X + 2][m_core.Y] == ���� || map.m_nArrMap[m_core.X + 2][m_core.Y - 1] == ���� || map.m_nArrMap[m_core.X + 2][m_core.Y + 1] == ����) ||
			(map.m_nArrMap[m_core.X + 2][m_core.Y] == ʯ�� || map.m_nArrMap[m_core.X + 2][m_core.Y - 1] == ʯ�� || map.m_nArrMap[m_core.X + 2][m_core.Y + 1] == ʯ��) ||
			(map.m_nArrMap[m_core.X + 2][m_core.Y] == ���� || map.m_nArrMap[m_core.X + 2][m_core.Y - 1] == ���� || map.m_nArrMap[m_core.X + 2][m_core.Y + 1] == ����))
		{
			return true;
		}
		//�Ƿ������Ҽ�Ȫˮ
		if (map.m_nArrMap[this->m_core.X][this->m_core.Y] == Ȫˮ)
		{
			return true;
		}
		//�Ƿ�ײ�ҷ�̹��
		for (int i = 0; i < MY_TANK_AMOUNT; i++)
		{
			//������̹���������Լ�
			if (m_who != �з�̹��)
			{
				if (this->m_core.X == pMyTank[i].m_core.X && this->m_core.Y == pMyTank[i].m_core.Y)//�ų��Լ�
					continue;
			}
			// ����̹�����������赲
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
		//�Ƿ�ײ�����з�̹��
		for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
		{
			//���ǵ�̹���������Լ�
			if (m_who == �з�̹��)
			{
				if (this->m_core.X == pEnemyTank[i].m_core.X && this->m_core.Y == pEnemyTank[i].m_core.Y)//�ų��Լ�
					continue;
			}
			// ����̹�����������赲
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
	if (this->m_who != �з�̹��)
	{
		setColor(10, 0);
		if(m_who == �ҷ�̹��A)
			GotoxyAndPrint(this->m_core.X, this->m_core.Y, "��");//���ĵ�
		else if(m_who == �ҷ�̹��B)
			GotoxyAndPrint(this->m_core.X, this->m_core.Y, "��");//���ĵ�
		for (int i = 0; i < 5; i++)//������
			GotoxyAndPrint(this->m_body[i].X, this->m_body[i].Y, "��");
		setColor(7, 0);
	}
	else
	{
		setColor(11, 0);//����ɫ
		if (this->m_blood == 2)
		{
			GotoxyAndPrint(this->m_core.X, this->m_core.Y, "��");//���ĵ�
			for (int i = 0; i < 5; i++)//������
				GotoxyAndPrint(this->m_body[i].X, this->m_body[i].Y, "��");//���ĵ�
		}
		else if (this->m_blood == 1)
		{
			GotoxyAndPrint(this->m_core.X, this->m_core.Y, "��");//���ĵ�
			for (int i = 0; i < 5; i++)//������
				GotoxyAndPrint(this->m_body[i].X, this->m_body[i].Y, "��");
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