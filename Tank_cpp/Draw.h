#pragma once
#include "Tank.h"


//��ӡ���
void DrawLogo();						//��ӡͼ��
void DrawBorder();						//��ӡ�߽�
void DrawGameHelp();					//��ӡ����
void DrawBarr();						//��ӡ�ϰ�
void DrawTank(CTank tank, int who);	//��ӡ̹��
void DrawBullet(CBullet bullet, CTank tank);				//��ӡ�ӵ�
void DrawGameInfo(CTank ptank, CTank* penemytank);			//��ӡ��Ϸ��Ϣ
void DrawMenu(const char** menu, int size, int index);		//��ӡ���ֲ˵�
