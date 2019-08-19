#pragma once
#include "Tank.h"

//游戏相关
void GameInit(CMap &map);				        //初始化工作
char* ShowGameFile();					//显示存档
void GameOver(CTank * penemytank);		//善后工作
int SelectMenu(int size, int* pindex);  //选择菜单项
void SaveGame(PTANK ptank, PTANK penemytank);				//存档
void LoadGame(PTANK ptank, PTANK penemytank, char* str);	//读档
