#include "Bullet.h"
#include "Tank.h"
#include "Map.h"
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
void CBullet::IsBulMeetOther(CTank tank, CTank* pMyTank, CTank* pEnemyTank, CMap& map)
{
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
	//������
	if (map.m_nArrMap[m_core.X][m_core.Y] == ����)
	{
		m_state = ������;
		map.m_nArrMap[m_core.X][m_core.Y] = �յ�;
	}
	//���ݴ�

	//������

	//���ӵ�

	if (m_who != �з�̹��)
	{
		//��Ȫˮ
		if (map.m_nArrMap[m_core.X][m_core.Y] == Ȫˮ)
			m_state = ������;
		// ���ҷ�����
		for (int i = 0; i < MY_TANK_AMOUNT; i++)
		{
			// ��̹�˲��ж�
			if (pMyTank[i].m_isAlive == false) continue;
			// �������ӵ���̹�˲��жϣ��Ա�body����core����Ϊ�ӵ��Ѿ���ǰ����һ����C�汾δ�жϵ�������Ҳ��ĳЩʵ�ֲ�һ��
			if (m_core.X == pMyTank[i].m_body[0].X && m_core.Y == pMyTank[i].m_body[0].Y) continue;
			if (
				(m_core.X == pMyTank[i].m_core.X) && (m_core.Y == pMyTank[i].m_core.Y) ||
				(m_core.X == pMyTank[i].m_body[0].X) && (m_core.Y == pMyTank[i].m_body[0].Y) ||
				(m_core.X == pMyTank[i].m_body[1].X) && (m_core.Y == pMyTank[i].m_body[1].Y) ||
				(m_core.X == pMyTank[i].m_body[2].X) && (m_core.Y == pMyTank[i].m_body[2].Y) ||
				(m_core.X == pMyTank[i].m_body[3].X) && (m_core.Y == pMyTank[i].m_body[3].Y) ||
				(m_core.X == pMyTank[i].m_body[4].X) && (m_core.Y == pMyTank[i].m_body[4].Y)
				)
			{
				m_state = ������;
			}
		}
		// ���з�̹��
		for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
		{
			// ��̹�˲��ж�
			if (pEnemyTank[i].m_isAlive == false) continue;
			if (
				(m_core.X == pEnemyTank[i].m_core.X) && (m_core.Y == pEnemyTank[i].m_core.Y) ||
				(m_core.X == pEnemyTank[i].m_body[0].X) && (m_core.Y == pEnemyTank[i].m_body[0].Y) ||
				(m_core.X == pEnemyTank[i].m_body[1].X) && (m_core.Y == pEnemyTank[i].m_body[1].Y) ||
				(m_core.X == pEnemyTank[i].m_body[2].X) && (m_core.Y == pEnemyTank[i].m_body[2].Y) ||
				(m_core.X == pEnemyTank[i].m_body[3].X) && (m_core.Y == pEnemyTank[i].m_body[3].Y) ||
				(m_core.X == pEnemyTank[i].m_body[4].X) && (m_core.Y == pEnemyTank[i].m_body[4].Y)
				)
			{
				PlaySound(TEXT("C:\\Users\\ry1yn\\source\\repos\\15PB\\Tank_cpp\\conf\\duang.wav"), NULL, SND_FILENAME | SND_ASYNC);//������Ч
				m_state = ������;
				pEnemyTank[i].m_blood--;
				if (pEnemyTank[i].m_blood == 0)//��Ѫ��Ϊ0������
					pEnemyTank[i].m_isAlive = false;
				if (!pEnemyTank[i].m_isAlive && (ENEMY_TANK_AMOUNT - GetLiveEnemyAmount(pEnemyTank)) % 3 == 0)//ÿ������������ֵ+1
					(tank.m_blood)++;//Ҫ��!penemytank[i].isAlive��Ҫ���򵽶������ĵ�̹Ҳ����
			}
		}
	}
	else if (m_who == �з�̹��)
	{
		//��Ȫˮ
		if (map.m_nArrMap[m_core.X][m_core.Y] == Ȫˮ)
		{
			m_state = ������;
			pMyTank[0].m_blood = 0;//Ȫˮ�򵽣��ҷ�̹�˵���ȥ��
			pMyTank[1].m_blood = 0;//Ȫˮ�򵽣��ҷ�̹�˵���ȥ��
		}
		//�����ҷ�̹��
		for (int i = 0; i < MY_TANK_AMOUNT; i++)
		{
			// ��̹�˲��ж�
			if (pMyTank[i].m_isAlive == false) continue;
			if (
				(m_core.X == pMyTank[i].m_core.X) && (m_core.Y == pMyTank[i].m_core.Y) ||
				(m_core.X == pMyTank[i].m_body[0].X) && (m_core.Y == pMyTank[i].m_body[0].Y ) ||
				(m_core.X == pMyTank[i].m_body[1].X) && (m_core.Y == pMyTank[i].m_body[1].Y ) ||
				(m_core.X == pMyTank[i].m_body[2].X) && (m_core.Y == pMyTank[i].m_body[2].Y ) ||
				(m_core.X == pMyTank[i].m_body[3].X) && (m_core.Y == pMyTank[i].m_body[3].Y ) ||
				(m_core.X == pMyTank[i].m_body[4].X) && (m_core.Y == pMyTank[i].m_body[4].Y )
				)
			{
				PlaySound(TEXT("conf/duang.wav"), NULL, SND_FILENAME | SND_ASYNC);//������Ч
				m_state = ������;
				(pMyTank[i].m_blood)--;
				if (pMyTank[i].m_blood == 0)//�����Ѫ��Ϊ0
					pMyTank[i].m_isAlive = false;//����Ϊ����
			}

		}
		//�������з�̹��
		for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
		{
			// ��̹�˲��ж�
			if (pEnemyTank[i].m_isAlive == false) continue;
			//�������ӵ���̹�˲��ж�
			if (m_core.X == pEnemyTank[i].m_body[0].X && m_core.Y == pEnemyTank[i].m_body[0].Y) continue;

			if (
				(m_core.X == pEnemyTank[i].m_core.X) && (m_core.Y == pEnemyTank[i].m_core.Y) ||
				(m_core.X == pEnemyTank[i].m_body[0].X) && (m_core.Y == pEnemyTank[i].m_body[0].Y ) ||
				(m_core.X == pEnemyTank[i].m_body[1].X) && (m_core.Y == pEnemyTank[i].m_body[1].Y ) ||
				(m_core.X == pEnemyTank[i].m_body[2].X) && (m_core.Y == pEnemyTank[i].m_body[2].Y ) ||
				(m_core.X == pEnemyTank[i].m_body[3].X) && (m_core.Y == pEnemyTank[i].m_body[3].Y ) ||
				(m_core.X == pEnemyTank[i].m_body[4].X) && (m_core.Y == pEnemyTank[i].m_body[4].Y )
				)
			{
				m_state = ������;
			}

		}
	}
}
void CBullet::DrawBullet(CMap map)
{

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
	//�����飬��Ϊ�ո�
	else if (map.m_nArrMap[m_core.X][m_core.Y] == ����)
	{
		GotoxyAndPrint(m_core.X, m_core.Y, "  ",Ĭ����ɫ);
	}

	//���ݴ�
	else if (map.m_nArrMap[m_core.X][m_core.Y] == �ݴ�)
	{
		//GotoxyAndPrint(m_core.X, m_core.Y, "��", ʯ����ɫ);
	}
	//������
	else if (map.m_nArrMap[m_core.X][m_core.Y] == ����)
	{
		//GotoxyAndPrint(m_core.X, m_core.Y, "  ", Ĭ����ɫ);
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