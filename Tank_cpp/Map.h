#pragma once
#include "Tank.h"
//�ϰ������
char* ShowMapFile();			//��ʾ��ͼ�ļ�
void LoadMapFile(char* str);	//�����ͼ�ļ�
void SetDefaultMap();			//ϵͳĬ�ϵ�ͼ
void CustomizeMap(PTANK ptank, PTANK penemytank);//�Զ����ͼ
