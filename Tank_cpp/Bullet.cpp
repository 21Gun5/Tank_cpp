#include "Bullet.h"
#include "Tank.h"
#include "Map.h"
#include "Game.h"
#pragma comment(lib,"winmm.lib")

CBullet::CBullet()
{
	m_core = { 0,0 };
	m_dir = UP;
	m_state = ������;
	m_who = -1;
}
void CBullet::SetBullet(CTank tank)
{
	m_core = tank.m_core;
	m_dir = tank.m_dir;
	m_who = tank.m_who;
}
void CBullet::MoveBullet()
{
	// ������״̬ʱ���ƶ�
	if (m_state == ������) return;

	switch (m_dir)
	{
	case UP:
		m_core.Y--;
		break;
	case DOWN:
		m_core.Y++;
		break;
	case LEFT:
		m_core.X--;
		break;
	case RIGHT:
		m_core.X++;
		break;
	default:
		break;
	}
}
void CBullet::CleanBullet(COORD oldBulCore)
{
	GotoxyAndPrint(oldBulCore.X, oldBulCore.Y, "  ");
}
void CBullet::IsBulMeetOther(CTank &tank, vector<CTank>& myTank, vector<CTank>& enemyTank, CMap& map,CGame &game)
{
	//tank ������Ϊ�˻�ȡ����ֵ

	//���߽�
	if (m_core.X <= 0 || m_core.X >= MAP_X_WALL / 2 || m_core.Y <= 0 || m_core.Y >= MAP_Y - 1)
	{
		m_state = ������;
	}	
	//��ʯ��
	if (map.m_nArrMap[m_core.X][m_core.Y] == ʯ��)
	{
		m_state = ������;
	}
	//�����飨���ݴԡ������򴩹�
	if (map.m_nArrMap[m_core.X][m_core.Y] == ����)
	{
		m_state = ������;
		map.m_nArrMap[m_core.X][m_core.Y] = �յ�;
	}
	//���ӵ�
	if (m_who != �з�̹��)
	{
		//��Ȫˮ
		if (map.m_nArrMap[m_core.X][m_core.Y] == Ȫˮ)
			m_state = ������;
		// ���ҷ�����
		for (vector<CTank>::iterator it = myTank.begin(); it != myTank.end(); it++)
		{
			// ��̹�˲��ж�
			//if (it->m_isAlive == false) continue;
			// �������ӵ���̹�˲��жϣ��Ա�body����core����Ϊ�ӵ��Ѿ���ǰ����һ����C�汾δ�жϵ�������Ҳ��ĳЩʵ�ֲ�һ��
			if (m_core.X == it->m_body[0].X && m_core.Y == it->m_body[0].Y) continue;
			if (
				(m_core.X == it->m_core.X) && (m_core.Y == it->m_core.Y) ||
				(m_core.X == it->m_body[0].X) && (m_core.Y == it->m_body[0].Y) ||
				(m_core.X == it->m_body[1].X) && (m_core.Y == it->m_body[1].Y) ||
				(m_core.X == it->m_body[2].X) && (m_core.Y == it->m_body[2].Y) ||
				(m_core.X == it->m_body[3].X) && (m_core.Y == it->m_body[3].Y) ||
				(m_core.X == it->m_body[4].X) && (m_core.Y == it->m_body[4].Y)
				)
			{
				m_state = ������;
			}
		}
		// ���з�̹�˼��ӵ�
		for (vector<CTank>::iterator it = enemyTank.begin(); it != enemyTank.end();it++)
		{
			
			//if (it->m_isAlive == false) continue;// ��̹�˲��ж�
			
			// ��̹��
			if (
				(m_core.X == it->m_core.X) && (m_core.Y == it->m_core.Y) ||
				(m_core.X == it->m_body[0].X) && (m_core.Y == it->m_body[0].Y) ||
				(m_core.X == it->m_body[1].X) && (m_core.Y == it->m_body[1].Y) ||
				(m_core.X == it->m_body[2].X) && (m_core.Y == it->m_body[2].Y) ||
				(m_core.X == it->m_body[3].X) && (m_core.Y == it->m_body[3].Y) ||
				(m_core.X == it->m_body[4].X) && (m_core.Y == it->m_body[4].Y) 
				)
			{
				PlaySound(TEXT("C:\\Users\\ry1yn\\source\\repos\\15PB\\Tank_cpp\\conf\\duang.wav"), NULL, SND_FILENAME | SND_ASYNC);//������Ч
				m_state = ������;
				it->m_blood--;
				//��Ѫ��Ϊ0������
				if (it->m_blood == 0)
				{
					it->m_isAlive = false;//����
					tank.m_killCount++;//ɱ����+1
				}
				// ÿ������������һ������ֵ
				if (tank.m_killCount == 3)
				{
					tank.m_blood++;
					tank.m_killCount = 0;
				}
			}
			// ���ӵ�
			if ((m_core.X == it->m_bullet.m_core.X) && (m_core.Y == it->m_bullet.m_core.Y))
			{
				// �����ӵ�״̬
				m_state = ������;
				it->m_bullet.m_state = ������;
				// Ĩ���ӵ�
				GotoxyAndPrint(m_core.X, m_core.Y, " ");
				GotoxyAndPrint(it->m_bullet.m_core.X, it->m_bullet.m_core.Y, " ");
				// �ƻ���ȵ�����
				m_core = { 0 };
				it->m_bullet.m_core = { -1 };
			}
		}
	}

	else if (m_who == �з�̹��)
	{
		//��Ȫˮ
		if (map.m_nArrMap[m_core.X][m_core.Y] == Ȫˮ)
		{
			m_state = ������;
			game.m_isOver = 1;
			//myTank[0].m_blood = 0;//Ȫˮ�򵽣��ҷ�̹�˵���ȥ��
			//myTank[1].m_blood = 0;//Ȫˮ�򵽣��ҷ�̹�˵���ȥ��
		}
		//�����ҷ�̹�˼��ӵ�
		for (vector<CTank>::iterator it = myTank.begin(); it != myTank.end(); it++)
		{
			
			//if (it->m_isAlive == false) continue;// ��̹�˲��ж�
			
			// ����̹��
			if (
				(m_core.X == it->m_core.X) && (m_core.Y == it->m_core.Y) ||
				(m_core.X == it->m_body[0].X) && (m_core.Y == it->m_body[0].Y ) ||
				(m_core.X == it->m_body[1].X) && (m_core.Y == it->m_body[1].Y ) ||
				(m_core.X == it->m_body[2].X) && (m_core.Y == it->m_body[2].Y ) ||
				(m_core.X == it->m_body[3].X) && (m_core.Y == it->m_body[3].Y ) ||
				(m_core.X == it->m_body[4].X) && (m_core.Y == it->m_body[4].Y )
				)
			{
				PlaySound(TEXT("conf/duang.wav"), NULL, SND_FILENAME | SND_ASYNC);//������Ч
				m_state = ������;
				// ̹��������״̬���򵽲���Ѫ
				if (!it->m_isHided)
				{
					if (tank.m_power == 1)
						it->m_blood--;
					else if (tank.m_power == 2)
						it->m_blood -= 2;
				}
				//�����Ѫ��Ϊ0
				if (it->m_blood == 0)
				{
					it->m_isAlive = false;//����Ϊ����
				}
					
			}

			// ���ӵ�
			if ((m_core.X == it->m_bullet.m_core.X) && (m_core.Y == it->m_bullet.m_core.Y))
			{
				// �����ӵ�״̬
				m_state = ������;
				it->m_bullet.m_state = ������;
				// Ĩ���ӵ�
				GotoxyAndPrint(m_core.X, m_core.Y, " ");// Ĩ�����ӵ�
				GotoxyAndPrint(it->m_bullet.m_core.X, it->m_bullet.m_core.Y, " ");// Ĩ�����ӵ�
				// �ƻ���ȵ�����
				m_core = { 0 };
				it->m_bullet.m_core = { -1 };
			}

		}

		//�������з�̹��
		for (vector<CTank>::iterator it = enemyTank.begin(); it != enemyTank.end(); it++)
		{
			// ��̹�˲��ж�
			if (it->m_isAlive == false) continue;
			//�������ӵ���̹�˲��ж�
			if (m_core.X == it->m_body[0].X && m_core.Y == it->m_body[0].Y) continue;

			if (
				(m_core.X == it->m_core.X) && (m_core.Y == it->m_core.Y) ||
				(m_core.X == it->m_body[0].X) && (m_core.Y == it->m_body[0].Y ) ||
				(m_core.X == it->m_body[1].X) && (m_core.Y == it->m_body[1].Y ) ||
				(m_core.X == it->m_body[2].X) && (m_core.Y == it->m_body[2].Y ) ||
				(m_core.X == it->m_body[3].X) && (m_core.Y == it->m_body[3].Y ) ||
				(m_core.X == it->m_body[4].X) && (m_core.Y == it->m_body[4].Y )
				)
			{
				m_state = ������;
			}

		}
	}
}
void CBullet::DrawBullet(CMap map)
{
	// ������״̬ʱ�򲻻�
	if (m_state == ������) return;
	//���߽磬����Ϊ����ɫ
	if (m_core.X <= 0 ||m_core.X >= MAP_X_WALL / 2 ||m_core.Y <= 0 ||m_core.Y >= MAP_Y - 1)
	{
		GotoxyAndPrint(m_core.X, m_core.Y, "��",Ĭ����ɫ);
	}
	//��ʯ�飬����Ϊ����ɫ
	else if (map.m_nArrMap[m_core.X][m_core.Y] == ʯ��)
	{
		GotoxyAndPrint(m_core.X, m_core.Y, "��", ʯ����ɫ);
	}
	//�����飬��Ϊ�ո����ݴԡ������򲻱�
	else if (map.m_nArrMap[m_core.X][m_core.Y] == ����)
	{
		GotoxyAndPrint(m_core.X, m_core.Y, "  ",Ĭ����ɫ);
	}
	//����Ȫˮ������Ϊ����ɫ����״
	else if (map.m_nArrMap[m_core.X][m_core.Y] == Ȫˮ)
	{
		GotoxyAndPrint(m_core.X, m_core.Y, "��",Ȫˮ��ɫ);
	}
	//һ���˶�״̬
	else
	{
		if (m_who != �з�̹��)
			GotoxyAndPrint(m_core.X, m_core.Y, "��",��̹��ɫ);
		else
			GotoxyAndPrint(m_core.X, m_core.Y, "��", ��̹��ɫ);		
	}
}