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
	void LoadDefaultMap();			//ϵͳĬ�ϵ�ͼ
	void LoadMapFile(char* str, CMap &map);	//�����ͼ�ļ�
	void SaveMapFile(CTank *pMyTank, CTank * penemytank);//�Զ����ͼ

	void DrawStaticMap();						//��ӡ�߽�
	void DrawDynamicMap();						//��ӡ�ϰ�
};

