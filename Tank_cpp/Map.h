#pragma once
#include "Func.h"

class CMap
{
public:
	int m_nArrMap[MAP_X][MAP_Y] = { 空地 };
public:
	char* ShowMapFile();			//显示地图文件
	//void LoadMapFile(char* str);	//导入地图文件
	void SetDefaultMap();			//系统默认地图
	//void CustomizeMap(PTANK ptank, PTANK penemytank);//自定义地图

	void DrawBorder();						//打印边界
	void DrawBarr();						//打印障碍
};

