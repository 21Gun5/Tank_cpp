#pragma once
#include "Tank.h"
//障碍物相关
char* ShowMapFile();			//显示地图文件
void LoadMapFile(char* str);	//导入地图文件
void SetDefaultMap();			//系统默认地图
void CustomizeMap(PTANK ptank, PTANK penemytank);//自定义地图
