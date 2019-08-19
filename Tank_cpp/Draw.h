#pragma once
#include "Tank.h"


//打印相关
void DrawLogo();						//打印图标
void DrawBorder();						//打印边界
void DrawGameHelp();					//打印帮助
void DrawBarr();						//打印障碍
void DrawTank(CTank tank, int who);	//打印坦克
void DrawBullet(CBullet bullet, CTank tank);				//打印子弹
void DrawGameInfo(CTank ptank, CTank* penemytank);			//打印游戏信息
void DrawMenu(const char** menu, int size, int index);		//打印各种菜单
