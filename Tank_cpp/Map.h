#pragma once
#include "Func.h"

class CTank;
class CMap;

class CMap
{
public:
	int m_nArrMap[MAP_X][MAP_Y] = { 空地 };
public:
	char* ShowMapFile();			//显示地图文件
	void SetDefaultMap();			//系统默认地图
	void LoadMapFile(char* str, CMap &map);	//导入地图文件
	void CustomizeMap(CTank tank, CTank * penemytank, CMap& map);//自定义地图

	void DrawBorder();						//打印边界
	void DrawBarr();						//打印障碍
};

