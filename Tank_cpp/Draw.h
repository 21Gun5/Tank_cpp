#pragma once
#include "Tank.h"


//打印相关
void DrawLogo();						//打印图标

void DrawGameHelp();					//打印帮助



void DrawGameInfo(CTank ptank, CTank* penemytank);			//打印游戏信息
void DrawMenu(const char** menu, int size, int index);		//打印各种菜单
