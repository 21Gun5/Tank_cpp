#pragma once
#include "Func.h"

class CTank;
class CMap;

class CMap
{
public:
	int m_nArrMap[MAP_X][MAP_Y] = { �յ� };
public:
	char* ShowMapFile();			//��ʾ��ͼ�ļ�
	void SetDefaultMap();			//ϵͳĬ�ϵ�ͼ
	void LoadMapFile(char* str, CMap &map);	//�����ͼ�ļ�
	void CustomizeMap(CTank tank, CTank * penemytank, CMap& map);//�Զ����ͼ

	void DrawBorder();						//��ӡ�߽�
	void DrawBarr();						//��ӡ�ϰ�
};

