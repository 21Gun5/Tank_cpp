#pragma once
#include "Func.h"

class CMap
{
public:
	int m_nArrMap[MAP_X][MAP_Y] = { �յ� };
public:
	char* ShowMapFile();			//��ʾ��ͼ�ļ�
	//void LoadMapFile(char* str);	//�����ͼ�ļ�
	void SetDefaultMap();			//ϵͳĬ�ϵ�ͼ
	//void CustomizeMap(PTANK ptank, PTANK penemytank);//�Զ����ͼ

	void DrawBorder();						//��ӡ�߽�
	void DrawBarr();						//��ӡ�ϰ�
};

