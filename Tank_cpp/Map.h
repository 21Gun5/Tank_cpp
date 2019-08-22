#pragma once
#include "Func.h"
#include <vector>
using namespace std;

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
	void SaveMapFile(vector<CTank>& myTank, vector<CTank>& enemyTank);//�Զ����ͼ

	void DrawStaticMap();						//��ӡ�߽�
	void DrawDynamicMap();						//��ӡ�ϰ�
};

