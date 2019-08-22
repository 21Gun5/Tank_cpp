#include <conio.h>
#include "Tank.h"
#include "Map.h"
#include "Game.h"

//̹�����
CTank::CTank(COORD core, enum direction dir, int blood, int who,int power)
{
	m_core = core;
	m_dir = dir;
	m_blood = blood;
	m_isAlive = true;
	m_who = who;
	m_isHided = false;//Ĭ�Ϸ����ص�
	m_power = power;
	SetTankShape();
}

void CTank::CleanTankTail(COORD oldCore, PCOORD oldBody)
{
	//if (this->m_isAlive == false) return;//�����ڲݴ���������һֱ�������˺�ʬ�岻��ʧ���ۺϣ����ǲ���
	GotoxyAndPrint(oldCore.X, oldCore.Y, "  ");//���ĵ�
	for (int i = 0; i < 5; i++)//������
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
	if (this->m_who == �ҷ�̹��A)
	{
		if (KEYDOWN('W'))//Сд���ɣ��ɴ�д��ASCII��
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
			// ������״̬�ſɿ���
			if (!m_isHided)
			{
				if (this->m_bullet.m_state != �Ѹ�ֵ)
				{
					this->m_bullet.m_state = δ��ֵ;//�Ѹ�ֵ������ʱ���ٿ��𣬲��ɸ�ֵΪ1��Ӧ����ʧΪ0ʱ����������Ч
				}
			}
		}
		else if (KEYDOWN('Q'))
		{
			//��ͣ���ָ�
			mciSendString("pause bgm", NULL, 0, NULL);	//��ͣbgm
			GotoxyAndPrint(MAP_X_WALL / 2 + 1, 1, "       ");//�Ȱѽϳ���running���
			GotoxyAndPrint(MAP_X_WALL / 2 + 1, 1, "PAUSE", ��ʾ��ɫ);
			GotoxyAndPrint(MAP_X_WALL / 2 + 1, 2, "1. �ص���Ϸ", ��ʾ��ɫ);
			GotoxyAndPrint(MAP_X_WALL / 2 + 1, 3, "2. �˳���Ϸ", ��ʾ��ɫ);
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
				GotoxyAndPrint(MAP_X_WALL / 2 + 1, 1, "RUNNING", ��ʾ��ɫ);
				GotoxyAndPrint(MAP_X_WALL / 2 + 1, 2, "Q: ��ͣ��Ϸ", ��ʾ��ɫ);
				GotoxyAndPrint(MAP_X_WALL / 2 + 1, 3, "           ");
				GotoxyAndPrint(MAP_X_WALL / 2 + 1, 4, "           ");
				break;
			}
			case '2'://�˳���Ϸ
			{
				GotoxyAndPrint(MAP_X_WALL / 2 + 1, 1, "������˳�?", ��ʾ��ɫ);
				GotoxyAndPrint(MAP_X_WALL / 2 + 1, 2, "1. �����˳�", ��ʾ��ɫ);
				GotoxyAndPrint(MAP_X_WALL / 2 + 1, 3, "2. ֱ���˳�", ��ʾ��ɫ);
				char op = _getch();
				if (op == '1')		//�����˳�
				{
					game.SaveGameFile(myTank, enemyTank, map);
					game.GameOver(enemyTank);
					game.m_isRunning = false;
					break;
				}
				else if (op == '2')	//ֱ���˳�
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
	else if (this->m_who == �ҷ�̹��B)
	{
		if (KEYDOWN('I'))//Сд���ɣ��ɴ�д��ASCII��
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
			// ������״̬�ſɿ���
			if (!m_isHided)
			{
				if (this->m_bullet.m_state != �Ѹ�ֵ)
				{
					this->m_bullet.m_state = δ��ֵ;//�Ѹ�ֵ������ʱ���ٿ��𣬲��ɸ�ֵΪ1��Ӧ����ʧΪ0ʱ����������Ч
				}
			}
		}
	}
	else if (this->m_who == �з�̹��)
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
			// ������״̬�ſɿ���
			if (!m_isHided)
			{
				if (this->m_bullet.m_state != �Ѹ�ֵ)
				{
					this->m_bullet.m_state = δ��ֵ;//�Ѹ�ֵ������ʱ���ٿ��𣬲��ɸ�ֵΪ1��Ӧ����ʧΪ0ʱ����������Ч
				}
			}
			break;
		default:
			break;
		}
	}

	SetTankShape();//ÿ���ƶ���Ҫ����������̬
}

bool CTank::IsTankMeetOther(int dir, vector<CTank>& myTank, vector<CTank>& enemyTank, CMap map)
{
	switch (dir)
	{
	case UP:
		//���߽�
		if (this->m_core.Y <= 2)
		{
			return true;
		}
		//�������Ȳ���ͨ���ϰ�
		if ((map.m_nArrMap[m_core.X][m_core.Y - 2] == ���� || map.m_nArrMap[m_core.X - 1][m_core.Y - 2] == ���� || map.m_nArrMap[m_core.X + 1][m_core.Y - 2] == ����) ||
			(map.m_nArrMap[m_core.X][m_core.Y - 2] == ʯ�� || map.m_nArrMap[m_core.X - 1][m_core.Y - 2] == ʯ�� || map.m_nArrMap[m_core.X + 1][m_core.Y - 2] == ʯ��) ||
			(map.m_nArrMap[m_core.X][m_core.Y - 2] == ���� || map.m_nArrMap[m_core.X - 1][m_core.Y - 2] == ���� || map.m_nArrMap[m_core.X + 1][m_core.Y - 2] == ����))
		{
			return true;
		}
		//���ݴԿ�����
		if (map.m_nArrMap[m_core.X][m_core.Y ] == �ݴ� || map.m_nArrMap[m_core.X - 1][m_core.Y ] == �ݴ� || map.m_nArrMap[m_core.X + 1][m_core.Y ] == �ݴ�)
		{
			
			m_isHided = true;
		}
		// ���ݴ�����ʾ��if ��else if ����������ģ�������
		if (map.m_nArrMap[m_core.X][m_core.Y -2] == �յ� || map.m_nArrMap[m_core.X - 1][m_core.Y -2] == �յ� || map.m_nArrMap[m_core.X + 1][m_core.Y -2] == �յ�)
		{
			
			m_isHided = false;
		}

		//���ҷ�̹��
		for (vector<CTank>::iterator it = myTank.begin(); it != myTank.end(); it++)
		//for (int i = 0; i < MY_TANK_AMOUNT; i++)
		{
			//������̹���������Լ�
			if (m_who != �з�̹��)
			{
				if (this->m_core.X == it->m_core.X && this->m_core.Y == it->m_core.Y)//�ų��Լ�
					continue;
			}
			// ����̹�����������赲
			//if (it->m_isAlive == false) continue;
			if (
				((this->m_core.X == it->m_core.X - 0) && (this->m_core.Y - it->m_core.Y == 3)) ||
				((this->m_core.X == it->m_core.X - 1) && (this->m_core.Y - it->m_core.Y == 3)) ||
				((this->m_core.X == it->m_core.X - 2) && (this->m_core.Y - it->m_core.Y == 3)) ||
				((this->m_core.X == it->m_core.X + 1) && (this->m_core.Y - it->m_core.Y == 3)) ||
				((this->m_core.X == it->m_core.X + 2) && (this->m_core.Y - it->m_core.Y == 3))
				)//Ҫ==3,����<=��ֻ���ڰ��ŵ�ʱ��ɱ��������С�ڣ���û���ŵ�̹1��������ȴС��2����2����
			{
				return true;
			}
		}
		//���з�̹��
		for (vector<CTank>::iterator it = enemyTank.begin(); it != enemyTank.end(); it++)
		{
			//���ǵ�̹���������Լ�
			if (m_who == �з�̹��)
			{
				if (this->m_core.X == it->m_core.X && this->m_core.Y == it->m_core.Y)//�ų��Լ�
					continue;
			}
			// ����̹�����������赲
			//if (it->m_isAlive == false) continue;
			if (
				((this->m_core.X == it->m_core.X) && (this->m_core.Y - it->m_core.Y == 3)) ||
				((this->m_core.X == it->m_core.X - 1) && (this->m_core.Y - it->m_core.Y == 3)) ||
				((this->m_core.X == it->m_core.X - 2) && (this->m_core.Y - it->m_core.Y == 3)) ||
				((this->m_core.X == it->m_core.X + 1) && (this->m_core.Y - it->m_core.Y == 3)) ||
				((this->m_core.X == it->m_core.X + 2) && (this->m_core.Y - it->m_core.Y == 3))
				)//Ҫ==3,����<=��ֻ���ڰ��ŵ�ʱ��ɱ��������С�ڣ���û���ŵ�̹1��������ȴС��2����2����
			{
				return true;
			}
		}
		break;
	case DOWN:
		//���߽�
		if (this->m_core.Y >= MAP_Y - 3)
		{
			return true;
		}
		//�������Ȳ���ͨ���ϰ�
		if ((map.m_nArrMap[m_core.X][m_core.Y + 2] == ���� || map.m_nArrMap[m_core.X - 1][m_core.Y + 2] == ���� || map.m_nArrMap[m_core.X + 1][m_core.Y + 2] == ����) ||
			(map.m_nArrMap[m_core.X][m_core.Y + 2] == ʯ�� || map.m_nArrMap[m_core.X - 1][m_core.Y + 2] == ʯ�� || map.m_nArrMap[m_core.X + 1][m_core.Y + 2] == ʯ��) ||
			(map.m_nArrMap[m_core.X][m_core.Y + 2] == ���� || map.m_nArrMap[m_core.X - 1][m_core.Y + 2] == ���� || map.m_nArrMap[m_core.X + 1][m_core.Y + 2] == ����))
		{
			return true;
		}
		
		// ���ݴԿ�����
		if (map.m_nArrMap[m_core.X][m_core.Y ] == �ݴ� || map.m_nArrMap[m_core.X - 1][m_core.Y ] == �ݴ� || map.m_nArrMap[m_core.X + 1][m_core.Y ] == �ݴ�)
		{
			
			m_isHided = true;
		}
		// ���ݴ�����ʾ
		if (map.m_nArrMap[m_core.X][m_core.Y + 2] == �յ� || map.m_nArrMap[m_core.X - 1][m_core.Y + 2] == �յ� || map.m_nArrMap[m_core.X + 1][m_core.Y + 2] == �յ�)
		{
			
			m_isHided = false;
		}

		//��Ȫˮ
		if (map.m_nArrMap[this->m_core.X][this->m_core.Y+2] == Ȫˮ)
		{
			return true;
		}
		//���ҷ�̹��
		for (vector<CTank>::iterator it = myTank.begin(); it != myTank.end(); it++)
		{
			//������̹���������Լ�
			if (m_who != �з�̹��)
			{
				if (this->m_core.X == it->m_core.X && this->m_core.Y == it->m_core.Y)//�ų��Լ�
					continue;
			}
			// ����̹�����������赲
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
		//���з�̹��
		for (vector<CTank>::iterator it = enemyTank.begin(); it != enemyTank.end(); it++)
		{
			//���ǵ�̹���������Լ�
			if (m_who == �з�̹��)
			{
				if (this->m_core.X == it->m_core.X && this->m_core.Y == it->m_core.Y)//�ų��Լ�
					continue;
			}
			// ����̹�����������赲
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
		//���߽�
		if (this->m_core.X <= 2)
		{
			return true;
		}
		//�������Ȳ���ͨ���ϰ�
		if ((map.m_nArrMap[m_core.X - 2][m_core.Y] == ���� || map.m_nArrMap[m_core.X - 2][m_core.Y - 1] == ���� || map.m_nArrMap[m_core.X - 2][m_core.Y + 1] == ����) ||
			(map.m_nArrMap[m_core.X - 2][m_core.Y] == ʯ�� || map.m_nArrMap[m_core.X - 2][m_core.Y - 1] == ʯ�� || map.m_nArrMap[m_core.X - 2][m_core.Y + 1] == ʯ��) ||
			(map.m_nArrMap[m_core.X - 2][m_core.Y] == ���� || map.m_nArrMap[m_core.X - 2][m_core.Y - 1] == ���� || map.m_nArrMap[m_core.X - 2][m_core.Y + 1] == ����))
		{
			return true;
		}

		// ���ݴԿ�����
		if (map.m_nArrMap[m_core.X ][m_core.Y] == �ݴ� || map.m_nArrMap[m_core.X ][m_core.Y - 1] == �ݴ� || map.m_nArrMap[m_core.X ][m_core.Y + 1] == �ݴ�)
		{
			
			m_isHided = true;
		}
		// ���ݴ�����ʾ
		if (map.m_nArrMap[m_core.X - 2][m_core.Y] == �յ� || map.m_nArrMap[m_core.X - 2][m_core.Y - 1] == �յ� || map.m_nArrMap[m_core.X - 2][m_core.Y + 1] == �յ�)
		{
			m_isHided = false;
		}

		//��Ȫˮ
		if (map.m_nArrMap[this->m_core.X-2][this->m_core.Y] == Ȫˮ)
		{
			return true;
		}
		//���ҷ�̹��
		for (vector<CTank>::iterator it = myTank.begin(); it != myTank.end(); it++)
		{
			//������̹���������Լ�
			if (m_who != �з�̹��)
			{
				if (this->m_core.X == it->m_core.X && this->m_core.Y == it->m_core.Y)//�ų��Լ�
					continue;
			}
			// ����̹�����������赲
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
		//���з�̹��
		for (vector<CTank>::iterator it = enemyTank.begin(); it != enemyTank.end(); it++)
		//for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
		{
			//���ǵ�̹���������Լ�
			if (m_who == �з�̹��)
			{
				if (this->m_core.X == it->m_core.X && this->m_core.Y == it->m_core.Y)//�ų��Լ�
					continue;
			}
			// ����̹�����������赲
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
		//���߽�
		if (this->m_core.X >= MAP_X_WALL / 2 - 2)
		{
			return true;
		}
		//�������Ȳ���ͨ���ϰ�
		if ((map.m_nArrMap[m_core.X + 2][m_core.Y] == ���� || map.m_nArrMap[m_core.X + 2][m_core.Y - 1] == ���� || map.m_nArrMap[m_core.X + 2][m_core.Y + 1] == ����) ||
			(map.m_nArrMap[m_core.X + 2][m_core.Y] == ʯ�� || map.m_nArrMap[m_core.X + 2][m_core.Y - 1] == ʯ�� || map.m_nArrMap[m_core.X + 2][m_core.Y + 1] == ʯ��) ||
			(map.m_nArrMap[m_core.X + 2][m_core.Y] == ���� || map.m_nArrMap[m_core.X + 2][m_core.Y - 1] == ���� || map.m_nArrMap[m_core.X + 2][m_core.Y + 1] == ����))
		{
			return true;
		}

		// ���ݴԿ�����
		if (map.m_nArrMap[m_core.X ][m_core.Y] == �ݴ� || map.m_nArrMap[m_core.X ][m_core.Y - 1] == �ݴ� || map.m_nArrMap[m_core.X][m_core.Y + 1] == �ݴ�)
		{
			m_isHided = true;
		}
		// ���ݴ�����ʾ
		if (map.m_nArrMap[m_core.X + 2][m_core.Y] == �յ� || map.m_nArrMap[m_core.X + 2][m_core.Y - 1] == �յ� || map.m_nArrMap[m_core.X +2][m_core.Y + 1] == �յ�)
		{
			m_isHided = false;
		}

		//��Ȫˮ
		if (map.m_nArrMap[this->m_core.X+2][this->m_core.Y] == Ȫˮ)
		{
			return true;
		}
		//���ҷ�̹��
		for (vector<CTank>::iterator it = myTank.begin(); it != myTank.end(); it++)
		{
			//������̹���������Լ�
			if (m_who != �з�̹��)
			{
				if (this->m_core.X == it->m_core.X && this->m_core.Y == it->m_core.Y)//�ų��Լ�
					continue;
			}
			// ����̹�����������赲
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
		//���з�̹��
		for (vector<CTank>::iterator it = enemyTank.begin(); it != enemyTank.end(); it++)
		//for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
		{
			//���ǵ�̹���������Լ�
			if (m_who == �з�̹��)
			{
				if (this->m_core.X == it->m_core.X && this->m_core.Y == it->m_core.Y)//�ų��Լ�
					continue;
			}
			// ����̹�����������赲
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
	// ���������򲻻���������̹ʬ���Դ���
	if (this->m_isAlive == false) return;
	if (this->m_who != �з�̹��)
	{
		if (m_who == �ҷ�̹��A)
		{
			GotoxyAndPrint(this->m_core.X, this->m_core.Y, "��", ��̹��ɫ);//���ĵ�

		}
		else if (m_who == �ҷ�̹��B)
		{
			GotoxyAndPrint(this->m_core.X, this->m_core.Y, "��", ��̹��ɫ);//���ĵ�
		}
		for (int i = 0; i < 5; i++)//������
		{
			GotoxyAndPrint(this->m_body[i].X, this->m_body[i].Y, "��", ��̹��ɫ);
		}
	}
	else if (m_who == �з�̹��)
	{
		// ������
		if (this->m_blood == 2)
		{
			GotoxyAndPrint(this->m_core.X, this->m_core.Y, "��", ��̹��ɫ);//���ĵ�
			for (int i = 0; i < 5; i++)//������
			{
				GotoxyAndPrint(this->m_body[i].X, this->m_body[i].Y, "��", ��̹��ɫ);//���ĵ�
			}
		}
		// һ����
		else if (this->m_blood == 1)
		{
			// һ�㹥����
			if (m_power == 1)
			{
				GotoxyAndPrint(this->m_core.X, this->m_core.Y, "��", ��̹��ɫ);//���ĵ�
				for (int i = 0; i < 5; i++)//������
				{
					GotoxyAndPrint(this->m_body[i].X, this->m_body[i].Y, "��", ��̹��ɫ);
				}
			}
			// ���㹥����
			else if (m_power == 2)
			{
				GotoxyAndPrint(this->m_core.X, this->m_core.Y, "��", ��̹��ɫ);//���ĵ�
				for (int i = 0; i < 5; i++)//������
				{
					GotoxyAndPrint(this->m_body[i].X, this->m_body[i].Y, "��", ��̹��ɫ);
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