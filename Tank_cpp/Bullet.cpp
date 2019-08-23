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

COORD CBullet::GetCore()
{
	return m_core;
}
int CBullet::GetDir()
{
	return m_dir;
}
int CBullet::GetState()
{
	return m_state;
}
int CBullet::GetWho()
{
	return m_who;
}

void CBullet::SetCore(COORD core)
{
	m_core = core;
}
void CBullet::SetDir(int dir)
{
	m_dir = dir;
}
void CBullet::SetState(int state)
{
	m_state = state;
}
void CBullet::SetWho(int who)
{
	m_who = who;
}





void CBullet::SetBullet(CTank tank)
{
	m_core = tank.GetCore();
	m_dir = tank.GetDir();
	m_who = tank.GetWho();
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
	if (map.GetArrMap(m_core.X, m_core.Y) == ʯ��)
	{
		m_state = ������;
	}
	//�����飨���ݴԡ������򴩹�
	if (map.GetArrMap(m_core.X, m_core.Y) == ����)
	{
		m_state = ������;
		map.SetArrMap(m_core.X, m_core.Y, �յ�);
	}
	//���ӵ�
	if (m_who != �з�̹��)
	{
		//��Ȫˮ
		if (map.GetArrMap(m_core.X, m_core.Y) == Ȫˮ)
			m_state = ������;
		// ���ҷ�����
		for (vector<CTank>::iterator it = myTank.begin(); it != myTank.end(); it++)
		{
			// ��̹�˲��ж�
			//if (it->m_isAlive == false) continue;
			// �������ӵ���̹�˲��жϣ��Ա�body����core����Ϊ�ӵ��Ѿ���ǰ����һ����C�汾δ�жϵ�������Ҳ��ĳЩʵ�ֲ�һ��
			if (m_core.X == it->GetBody(0).X && m_core.Y == it->GetBody(0).Y) continue;
			if (
				(m_core.X == it->GetCore().X) && (m_core.Y == it->GetCore().Y) ||
				(m_core.X == it->GetBody(0).X) && (m_core.Y == it->GetBody(0).Y) ||
				(m_core.X == it->GetBody(1).X) && (m_core.Y == it->GetBody(1).Y) ||
				(m_core.X == it->GetBody(2).X) && (m_core.Y == it->GetBody(2).Y) ||
				(m_core.X == it->GetBody(3).X) && (m_core.Y == it->GetBody(3).Y) ||
				(m_core.X == it->GetBody(4).X) && (m_core.Y == it->GetBody(4).Y)
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
				(m_core.X == it->GetCore().X) && (m_core.Y == it->GetCore().Y) ||
				(m_core.X == it->GetBody(0).X) && (m_core.Y == it->GetBody(0).Y) ||
				(m_core.X == it->GetBody(1).X) && (m_core.Y == it->GetBody(1).Y) ||
				(m_core.X == it->GetBody(2).X) && (m_core.Y == it->GetBody(2).Y) ||
				(m_core.X == it->GetBody(3).X) && (m_core.Y == it->GetBody(3).Y) ||
				(m_core.X == it->GetBody(4).X) && (m_core.Y == it->GetBody(4).Y) 
				)
			{
				PlaySound(TEXT("C:\\Users\\ry1yn\\source\\repos\\15PB\\Tank_cpp\\conf\\duang.wav"), NULL, SND_FILENAME | SND_ASYNC);//������Ч
				m_state = ������;

				//it->m_blood--;
				int blood = it->GetBlood() - 1;
				it->SetBlood(blood);
				
				//��Ѫ��Ϊ0������
				if (it->GetBlood() == 0)
				{
					it->SetIsAlive(false);//����
					int killCount = tank.GetKillCount() + 1;
					tank.SetKillCount(killCount);//ɱ����+1
				}
				// ÿ������������һ������ֵ
				if (tank.GetKillCount() == 3)
				{
					int blood = tank.GetBlood() + 1;
					tank.SetBlood(blood);
					tank.SetKillCount(0);
				}
			}
			// ���ӵ�
			if ((m_core.X == it->m_bullet.GetCore().X) && (m_core.Y == it->m_bullet.GetCore().Y))
			{
				// �����ӵ�״̬
				m_state = ������;
				it->m_bullet.SetState(������);
				// Ĩ���ӵ�
				GotoxyAndPrint(m_core.X, m_core.Y, " ");
				GotoxyAndPrint(it->m_bullet.GetCore().X, it->m_bullet.GetCore().Y, " ");
				// �ƻ���ȵ�����(��������Ϊ����ĳ�հ״������踺�������߳�ʱ�䲻һ�������ܻ������(0,0��
				m_core = { MAP_X_WALL / 2 + 1, MAP_Y / 2 + 1 };
				COORD coor = { MAP_X_WALL / 2 + 1, MAP_Y / 2 + 2 };
				it->m_bullet.SetCore(coor);
			}
		}
	}

	else if (m_who == �з�̹��)
	{
		//��Ȫˮ
		if (map.GetArrMap(m_core.X, m_core.Y) == Ȫˮ)
		{
			m_state = ������;
			game.SetisOver(true);
			//myTank[0].m_blood = 0;//Ȫˮ�򵽣��ҷ�̹�˵���ȥ��
			//myTank[1].m_blood = 0;//Ȫˮ�򵽣��ҷ�̹�˵���ȥ��
		}
		//�����ҷ�̹�˼��ӵ�
		for (vector<CTank>::iterator it = myTank.begin(); it != myTank.end(); it++)
		{
			
			//if (it->m_isAlive == false) continue;// ��̹�˲��ж�
			
			// ����̹��
			if (
				(m_core.X == it->GetCore().X) && (m_core.Y == it->GetCore().Y) ||
				(m_core.X == it->GetBody(0).X) && (m_core.Y == it->GetBody(0).Y) ||
				(m_core.X == it->GetBody(1).X) && (m_core.Y == it->GetBody(1).Y) ||
				(m_core.X == it->GetBody(2).X) && (m_core.Y == it->GetBody(2).Y) ||
				(m_core.X == it->GetBody(3).X) && (m_core.Y == it->GetBody(3).Y) ||
				(m_core.X == it->GetBody(4).X) && (m_core.Y == it->GetBody(4).Y)
				)
			{
				PlaySound(TEXT("conf/duang.wav"), NULL, SND_FILENAME | SND_ASYNC);//������Ч
				m_state = ������;
				// ̹��������״̬���򵽲���Ѫ
				if (!it->GetIsHidden())
				{
					if (tank.GetPower() == 1)
					{
						int blood = it->GetBlood() - 1;
						it->SetBlood(blood);
					}
						
					else if (tank.GetPower() == 2)
					{
						int blood = it->GetBlood() - 2;
						it->SetBlood(blood);
					}
						
				}
				//�����Ѫ��Ϊ0
				if (it->GetBlood() == 0)
				{
					it->SetIsAlive(false) ;//����Ϊ����
				}
					
			}

			// ���ӵ�
			if ((m_core.X == it->m_bullet.GetCore().X) && (m_core.Y == it->m_bullet.GetCore().Y))
			{
				// �����ӵ�״̬
				m_state = ������;
				it->m_bullet.SetState(������)  ;
				// Ĩ���ӵ�
				GotoxyAndPrint(m_core.X, m_core.Y, " ");// Ĩ�����ӵ�
				GotoxyAndPrint(it->m_bullet.GetCore().X, it->m_bullet .GetCore().Y, " ");// Ĩ�����ӵ�
				// �ƻ���ȵ�����(��������Ϊ����ĳ�հ״������踺�������߳�ʱ�䲻һ�������ܻ������(0,0��
				m_core = { MAP_X_WALL / 2 + 1, MAP_Y / 2 - 1 };
				COORD coor = { MAP_X_WALL / 2 + 1, MAP_Y / 2 - 2 };
				it->m_bullet.SetCore(coor);
			}

		}

		//�������з�̹��
		for (vector<CTank>::iterator it = enemyTank.begin(); it != enemyTank.end(); it++)
		{
			// ��̹�˲��ж�
			if (it->GetIsAlive() == false) continue;
			//�������ӵ���̹�˲��ж�
			if (m_core.X == it->GetBody(0).X && m_core.Y == it->GetBody(0).Y) continue;

			if (
				(m_core.X == it->GetCore().X) && (m_core.Y == it->GetCore().Y) ||
				(m_core.X == it->GetBody(0).X) && (m_core.Y == it->GetBody(0).Y) ||
				(m_core.X == it->GetBody(1).X) && (m_core.Y == it->GetBody(1).Y) ||
				(m_core.X == it->GetBody(2).X) && (m_core.Y == it->GetBody(2).Y) ||
				(m_core.X == it->GetBody(3).X) && (m_core.Y == it->GetBody(3).Y) ||
				(m_core.X == it->GetBody(4).X) && (m_core.Y == it->GetBody(4).Y)
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
	else if (map.GetArrMap(m_core.X, m_core.Y) == ʯ��)
	{
		GotoxyAndPrint(m_core.X, m_core.Y, "��", ʯ����ɫ);
	}
	//�����飬��Ϊ�ո����ݴԡ������򲻱�
	else if (map.GetArrMap(m_core.X, m_core.Y) == ����)
	{
		GotoxyAndPrint(m_core.X, m_core.Y, "  ",Ĭ����ɫ);
	}
	//����Ȫˮ������Ϊ����ɫ����״
	else if (map.GetArrMap(m_core.X, m_core.Y) == Ȫˮ)
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