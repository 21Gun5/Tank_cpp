#pragma once
#include "Tank.h"


//��ӡ���
void DrawLogo();						//��ӡͼ��

void DrawGameHelp();					//��ӡ����



void DrawGameInfo(CTank ptank, CTank* penemytank);			//��ӡ��Ϸ��Ϣ
void DrawMenu(const char** menu, int size, int index);		//��ӡ���ֲ˵�
