#pragma once
#include "Func.h"
#include <vector>
using namespace std;

class CTank;
class CMap;

class CMap
{
private:
	int m_nArrMap[MAP_X][MAP_Y] = { �յ� };		// ��ͼ����
public:
	int GetArrMap(int x, int y);
	void SetArrMap(int x, int y, int i);
	void LoadDefaultMap();						// ����Ĭ�ϵ�ͼ
	void DrawStaticMap();						// ��ӡ�߽磨��̬
	void DrawDynamicMap();						// ��ӡ�ϰ�����̬
	char* ShowMapFile();						// ��ʾ��ͼ�ļ�
	void LoadMapFile(char* str, CMap& map);		// ���붨�Ƶ�ͼ
	void SaveMapFile(vector<CTank>& myTank, vector<CTank>& enemyTank);// �Զ����ͼ
};