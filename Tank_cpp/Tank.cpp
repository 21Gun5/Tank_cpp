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

//̹�����
void CTank::CleanTankTail(COORD oldCore, PCOORD oldBody)
{
	GotoxyAndPrint(oldCore.X, oldCore.Y, "  ");//���ĵ�
	for (int i = 0; i < 5; i++)//������
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
	if (this->m_who == �ҷ�̹��)
	{
		char ch = 0;
		if (_kbhit())				//���������� 
		{
			ch = _getch();			//�޻��Խ�������
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
				if (this->bullet.state != �Ѹ�ֵ)
					this->bullet.state = δ��ֵ;//�Ѹ�ֵ������ʱ���ٿ��𣬲��ɸ�ֵΪ1��Ӧ����ʧΪ0ʱ����������Ч
				break;
			case 'q':
			//{
			//	//��ͣ���ָ�
			//	mciSendString("pause bgm", NULL, 0, NULL);	//��ͣbgm
			//	setColor(12, 0);
			//	GotoxyAndPrint(MAP_X / 2 - 14, 1, "       ");//�Ȱѽϳ���running���
			//	GotoxyAndPrint(MAP_X / 2 - 14, 1, "PAUSE");
			//	GotoxyAndPrint(MAP_X / 2 - 14, 2, "1. �ص���Ϸ");
			//	GotoxyAndPrint(MAP_X / 2 - 14, 3, "2. �˳���Ϸ");
			//	char tmp;
			//	do
			//	{
			//		tmp = _getch();	//��������������ͣ��Ϸ
			//	} while (!(tmp == '1' || tmp == '2' || tmp == '3'));//ֻ������123�ſ�
			//	switch (tmp)
			//	{
			//	case '1'://�ָ���Ϸ
			//	{
			//		mciSendString("resume bgm", NULL, 0, NULL);//�ָ�bgm
			//		GotoxyAndPrint(MAP_X / 2 - 14, 1, "RUNNING");
			//		GotoxyAndPrint(MAP_X / 2 - 14, 2, "Q: ��ͣ��Ϸ");
			//		GotoxyAndPrint(MAP_X / 2 - 14, 3, "           ");
			//		GotoxyAndPrint(MAP_X / 2 - 14, 4, "           ");
			//		break;
			//	}
			//	case '2'://�˳���Ϸ
			//	{
			//		GotoxyAndPrint(MAP_X / 2 - 14, 1, "������˳�?");
			//		GotoxyAndPrint(MAP_X / 2 - 14, 2, "1. �����˳�");
			//		GotoxyAndPrint(MAP_X / 2 - 14, 3, "2. ֱ���˳�");
			//		char op = _getch();
			//		if (op == '1')		//�����˳�
			//		{
			//			SaveGame(this, penemytank);
			//			GameOver(penemytank);
			//			g_isRunning = false;
			//			break;
			//		}
			//		else if (op == '2')	//ֱ���˳�
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
	SetTankShape();//ÿ���ƶ���Ҫ����������̬
}

bool CTank::IsMyTankMeetOther(int dir, CTank * penemytank)
{
	switch (dir)
	{
	case UP:
		//�Ƿ�ײ�߽�
		if (this->core.Y <= 2)
		{
			return true;
		}
		//�Ƿ�ײ�ϰ���
		if ((g_MAP[this->core.X][this->core.Y - 2] == �����ϰ� ||
			g_MAP[this->core.X - 1][this->core.Y - 2] == �����ϰ� ||
			g_MAP[this->core.X + 1][this->core.Y - 2] == �����ϰ�) ||
			(g_MAP[this->core.X][this->core.Y - 2] == ʯ���ϰ� ||
			g_MAP[this->core.X - 1][this->core.Y - 2] == ʯ���ϰ� ||
			g_MAP[this->core.X + 1][this->core.Y - 2] == ʯ���ϰ�))
		{
			return true;
		}
		//�Ƿ�ײ�з�̹��
		for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
		{
			if (penemytank[i].isAlive == false) continue;
			if (
				((this->core.X == penemytank[i].core.X) && (this->core.Y - penemytank[i].core.Y == 3)) ||
				((this->core.X == penemytank[i].core.X - 1) && (this->core.Y - penemytank[i].core.Y == 3)) ||
				((this->core.X == penemytank[i].core.X - 2) && (this->core.Y - penemytank[i].core.Y == 3)) ||
				((this->core.X == penemytank[i].core.X + 1) && (this->core.Y - penemytank[i].core.Y == 3)) ||
				((this->core.X == penemytank[i].core.X + 2) && (this->core.Y - penemytank[i].core.Y == 3))
				)//Ҫ==3,����<=��ֻ���ڰ��ŵ�ʱ��ɱ��������С�ڣ���û���ŵ�̹1��������ȴС��2����2����
			{
				return true;
			}
		}
		break;
	case DOWN:
		//�Ƿ�ײ�߽�
		if (this->core.Y >= MAP_Y - 3)
		{
			return true;
		}
		//�Ƿ�ײ�ϰ���
		if ((g_MAP[this->core.X][this->core.Y + 2] == �����ϰ� ||
			g_MAP[this->core.X - 1][this->core.Y + 2] == �����ϰ� ||
			g_MAP[this->core.X + 1][this->core.Y + 2] == �����ϰ�) ||
			(g_MAP[this->core.X][this->core.Y + 2] == ʯ���ϰ� ||
				g_MAP[this->core.X - 1][this->core.Y + 2] == ʯ���ϰ� ||
				g_MAP[this->core.X + 1][this->core.Y + 2] == ʯ���ϰ�))
		{
			return true;
		}
		//�Ƿ������Ҽ�Ȫˮ
		if (g_MAP[this->core.X][this->core.Y] == �Ҽ�Ȫˮ)
		{
			return true;
		}
		//�Ƿ�ײ�з�̹��
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
		//�Ƿ�ײ�߽�
		if (this->core.X <= 2)
		{
			return true;
		}
		//�Ƿ�ײ�ϰ���
		if ((g_MAP[this->core.X - 2][this->core.Y] == �����ϰ� ||
			g_MAP[this->core.X - 2][this->core.Y - 1] == �����ϰ� ||
			g_MAP[this->core.X - 2][this->core.Y + 1] == �����ϰ�) ||
			(g_MAP[this->core.X - 2][this->core.Y] == ʯ���ϰ� ||
				g_MAP[this->core.X - 2][this->core.Y - 1] == ʯ���ϰ� ||
				g_MAP[this->core.X - 2][this->core.Y + 1] == ʯ���ϰ�))
		{
			return true;
		}
		//�Ƿ������Ҽ�Ȫˮ
		if (g_MAP[this->core.X][this->core.Y] == �Ҽ�Ȫˮ)
		{
			return true;
		}
		//�Ƿ�ײ�з�̹��
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
		//�Ƿ�ײ�߽�
		if (this->core.X >= MAP_X_WALL / 2 - 2)
		{
			return true;
		}
		//�Ƿ�ײ�ϰ���
		if ((g_MAP[this->core.X + 2][this->core.Y] == �����ϰ� ||
			g_MAP[this->core.X + 2][this->core.Y - 1] == �����ϰ� ||
			g_MAP[this->core.X + 2][this->core.Y + 1] == �����ϰ�) ||
			(g_MAP[this->core.X + 2][this->core.Y] == ʯ���ϰ� ||
				g_MAP[this->core.X + 2][this->core.Y - 1] == ʯ���ϰ� ||
				g_MAP[this->core.X + 2][this->core.Y + 1] == ʯ���ϰ�))
		{
			return true;
		}
		//�Ƿ������Ҽ�Ȫˮ
		if (g_MAP[this->core.X][this->core.Y] == �Ҽ�Ȫˮ)
		{
			return true;
		}
		//�Ƿ�ײ�з�̹��
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
	if (this->m_who == �з�̹��)
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
			if (this->bullet.state != �Ѹ�ֵ)
				this->bullet.state = δ��ֵ;
			break;
		default:
			break;
		}
	}
	SetTankShape();//ÿ���ƶ���Ҫ����������̬
}

bool CTank::IsEneTankMeetOther(int dir, CTank pmytank, CTank* penemytank)
{
	switch (dir)
	{
	case UP:
		//�Ƿ�ײ�߽�
		if (this->core.Y <= 2)
		{
			return true;
		}
		//�Ƿ�ײ�ϰ���
		if ((g_MAP[this->core.X][this->core.Y - 2] == �����ϰ� ||
			g_MAP[this->core.X - 1][this->core.Y - 2] == �����ϰ� ||
			g_MAP[this->core.X + 1][this->core.Y - 2] == �����ϰ�) ||
			(g_MAP[this->core.X][this->core.Y - 2] == ʯ���ϰ� ||
				g_MAP[this->core.X - 1][this->core.Y - 2] == ʯ���ϰ� ||
				g_MAP[this->core.X + 1][this->core.Y - 2] == ʯ���ϰ�))
		{
			return true;
		}
		//�Ƿ�ײ�ҷ�̹��
		if (
			((this->core.X == pmytank.core.X - 0) && (this->core.Y - pmytank.core.Y == 3)) ||
			((this->core.X == pmytank.core.X - 1) && (this->core.Y - pmytank.core.Y == 3)) ||
			((this->core.X == pmytank.core.X - 2) && (this->core.Y - pmytank.core.Y == 3)) ||
			((this->core.X == pmytank.core.X + 1) && (this->core.Y - pmytank.core.Y == 3)) ||
			((this->core.X == pmytank.core.X + 2) && (this->core.Y - pmytank.core.Y == 3))
			)//Ҫ==3,����<=��ֻ���ڰ��ŵ�ʱ��ɱ��������С�ڣ���û���ŵ�̹1��������ȴС��2����2����
		{
			return true;
		}
		//�Ƿ�ײ�����з�̹��
		for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
		{
			if (this->core.X == penemytank[i].core.X && this->core.Y == penemytank[i].core.Y)//�ų��Լ�
				continue;
			if (
				((this->core.X == penemytank[i].core.X) && (this->core.Y - penemytank[i].core.Y == 3)) ||
				((this->core.X == penemytank[i].core.X - 1) && (this->core.Y - penemytank[i].core.Y == 3)) ||
				((this->core.X == penemytank[i].core.X - 2) && (this->core.Y - penemytank[i].core.Y == 3)) ||
				((this->core.X == penemytank[i].core.X + 1) && (this->core.Y - penemytank[i].core.Y == 3)) ||
				((this->core.X == penemytank[i].core.X + 2) && (this->core.Y - penemytank[i].core.Y == 3))
				)//Ҫ==3,����<=��ֻ���ڰ��ŵ�ʱ��ɱ��������С�ڣ���û���ŵ�̹1��������ȴС��2����2����
			{
				return true;
			}
		}
		break;
	case DOWN:
		//�Ƿ�ײ�߽�
		if (this->core.Y >= MAP_Y - 3)
		{
			return true;
		}
		//�Ƿ�ײ�ϰ���
		if ((g_MAP[this->core.X][this->core.Y + 2] == �����ϰ� ||
			g_MAP[this->core.X - 1][this->core.Y + 2] == �����ϰ� ||
			g_MAP[this->core.X + 1][this->core.Y + 2] == �����ϰ�) ||
			(g_MAP[this->core.X][this->core.Y + 2] == ʯ���ϰ� ||
				g_MAP[this->core.X - 1][this->core.Y + 2] == ʯ���ϰ� ||
				g_MAP[this->core.X + 1][this->core.Y + 2] == ʯ���ϰ�))
		{
			return true;
		}
		//�Ƿ������Ҽ�Ȫˮ
		if (g_MAP[this->core.X][this->core.Y] == �Ҽ�Ȫˮ)
		{
			return true;
		}
		//�Ƿ�ײ�ҷ�̹��
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
		//�Ƿ�ײ�����з�̹��
		for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
		{
			if (this->core.X == penemytank[i].core.X && this->core.Y == penemytank[i].core.Y)//�ų��Լ�
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
		//�Ƿ�ײ�߽�
		if (this->core.X <= 2)
		{
			return true;
		}
		//�Ƿ�ײ�ϰ���
		if ((g_MAP[this->core.X - 2][this->core.Y] == �����ϰ� ||
			g_MAP[this->core.X - 2][this->core.Y - 1] == �����ϰ� ||
			g_MAP[this->core.X - 2][this->core.Y + 1] == �����ϰ�) ||
			(g_MAP[this->core.X - 2][this->core.Y] == ʯ���ϰ� ||
				g_MAP[this->core.X - 2][this->core.Y - 1] == ʯ���ϰ� ||
				g_MAP[this->core.X - 2][this->core.Y + 1] == ʯ���ϰ�))
		{
			return true;
		}
		//�Ƿ������Ҽ�Ȫˮ
		if (g_MAP[this->core.X][this->core.Y] == �Ҽ�Ȫˮ)
		{
			return true;
		}
		//�Ƿ�ײ�ҷ�̹��
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
		//�Ƿ�ײ�����з�̹��
		for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
		{
			if (this->core.X == penemytank[i].core.X && this->core.Y == penemytank[i].core.Y)//�ų��Լ�
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
		//�Ƿ�ײ�߽�
		if (this->core.X >= MAP_X_WALL / 2 - 2)
		{
			return true;
		}
		//�Ƿ�ײ�ϰ���
		if ((g_MAP[this->core.X + 2][this->core.Y] == �����ϰ� ||
			g_MAP[this->core.X + 2][this->core.Y - 1] == �����ϰ� ||
			g_MAP[this->core.X + 2][this->core.Y + 1] == �����ϰ�) ||
			(g_MAP[this->core.X + 2][this->core.Y] == ʯ���ϰ� ||
				g_MAP[this->core.X + 2][this->core.Y - 1] == ʯ���ϰ� ||
				g_MAP[this->core.X + 2][this->core.Y + 1] == ʯ���ϰ�))
		{
			return true;
		}
		//�Ƿ������Ҽ�Ȫˮ
		if (g_MAP[this->core.X][this->core.Y] == �Ҽ�Ȫˮ)
		{
			return true;
		}
		//�Ƿ�ײ�ҷ�̹��
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
		//�Ƿ�ײ�����з�̹��
		for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
		{
			if (this->core.X == penemytank[i].core.X && this->core.Y == penemytank[i].core.Y)//�ų��Լ�
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