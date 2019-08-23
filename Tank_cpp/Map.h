#pragma once
#include "Func.h"
#include <vector>
using namespace std;

class CTank;
class CMap;

class CMap
{
private:
	int m_nArrMap[MAP_X][MAP_Y] = { 空地 };		// 地图数组
public:
	int GetArrMap(int x, int y);
	void SetArrMap(int x, int y, int i);
	void LoadDefaultMap();						// 导入默认地图
	void DrawStaticMap();						// 打印边界（静态
	void DrawDynamicMap();						// 打印障碍（动态
	char* ShowMapFile();						// 显示地图文件
	void LoadMapFile(char* str, CMap& map);		// 导入定制地图
	void SaveMapFile(vector<CTank>& myTank, vector<CTank>& enemyTank);// 自定义地图
};