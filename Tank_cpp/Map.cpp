#include <Windows.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include "Data.h"
#include "Func.h"
#include "Map.h"
#include "Draw.h"


//地图相关
char* ShowMapFile()
{
	//遍历指定目录及后缀的文件名并存入数组
	char* mapFiles[10] = { nullptr };
	long Handle;
	struct _finddata_t FileInfo;
	int count = 0;
	if ((Handle = _findfirst("conf/map/*.i", &FileInfo)) == -1L)
		printf("Not Found\n");
	else
	{
		mapFiles[count] = (char*)malloc(20);
		strcpy_s(mapFiles[count], 20, FileInfo.name);
		//g_Maps[count] = FileInfo.name;
		count++;
		while (_findnext(Handle, &FileInfo) == 0)
		{
			mapFiles[count] = (char*)malloc(20);
			strcpy_s(mapFiles[count], 20, FileInfo.name);
			//g_Maps[count] = FileInfo.name;
			count++;
		}
		_findclose(Handle);
	}
	//显示地图文件
	system("cls");
	GotoxyAndPrint(MAP_X / 4 - 5, MAP_Y / 2 - 8, "请选择地图");
	int i = 0;								//循环变量在for外定义
	for (; i < count; i++)
	{
		GotoxyAndPrint(MAP_X / 4 - 5, MAP_Y / 2 - 6 + i, "");
		printf("%d.%s", i + 1, mapFiles[i]);
	}
	//选择
	GotoxyAndPrint(MAP_X / 4 - 5, MAP_Y / 2 - 6 + i, "请输入选择-> ");
	SetCursorState(true);
	int input = _getch() - '0';				//保证0-9而非ASCII
	SetCursorState(false);
	char* _file = (char*)malloc(15);
	strcpy_s(_file, 15, mapFiles[input - 1]);//数字始于1，而下标始于0	
	return _file;
}
void SetDefaultMap()
{
	for (int x = 0; x < MAP_X_WALL; x++)
	{
		for (int y = 0; y < MAP_Y; y++)
		{
			if (
				(x > MAP_X_WALL / 4 - 9 && x < MAP_X_WALL / 4 - 5 && y > MAP_Y / 2 - 8 && y < MAP_Y / 2 - 4) ||
				(x < MAP_X_WALL / 4 + 9 && x > MAP_X_WALL / 4 + 5 && y > MAP_Y / 2 - 8 && y < MAP_Y / 2 - 4) ||
				(x > MAP_X_WALL / 4 - 9 && x < MAP_X_WALL / 4 - 5 && y < MAP_Y / 2 + 6 && y > MAP_Y / 2 + 2) ||
				(x < MAP_X_WALL / 4 + 9 && x > MAP_X_WALL / 4 + 5 && y < MAP_Y / 2 + 6 && y > MAP_Y / 2 + 2)
				)
			{
				g_MAP[x][y] = 土块障碍;
			}
			if (
				(x > MAP_X_WALL / 4 - 9 && x < MAP_X_WALL / 4 - 5 && y > MAP_Y / 2 - 9 && y < MAP_Y / 2 - 7) ||
				(x < MAP_X_WALL / 4 + 9 && x > MAP_X_WALL / 4 + 5 && y > MAP_Y / 2 - 9 && y < MAP_Y / 2 - 7) ||
				(x > MAP_X_WALL / 4 - 9 && x < MAP_X_WALL / 4 - 5 && y < MAP_Y / 2 + 7 && y > MAP_Y / 2 + 5) ||
				(x < MAP_X_WALL / 4 + 9 && x > MAP_X_WALL / 4 + 5 && y < MAP_Y / 2 + 7 && y > MAP_Y / 2 + 5)
				)
			{
				g_MAP[x][y] = 石块障碍;
			}
		}
	}
}
void LoadMapFile(char* str)
{
	char* filename = (char*)malloc(40);
	sprintf_s(filename, 40, "%s%s", "conf/map/", str);
	FILE* pFile = NULL;
	errno_t err = fopen_s(&pFile, filename, "rb");
	for (int x = 0; x < MAP_X_WALL; x++)
	{
		for (int y = 0; y < MAP_Y; y++)
		{
			fread(&g_MAP[x][y], sizeof(int), 1, pFile);
		}
	}
	fclose(pFile);
}
void CustomizeMap(PTANK ptank, PTANK penemytank)
{
	DrawBorder();		//地图边界
	//提示信息
	setColor(12, 0);
	GotoxyAndPrint(MAP_X / 2 - 12, 2, "     编辑地图");
	GotoxyAndPrint(MAP_X / 2 - 12, 4, "左键单击：创建土块");
	GotoxyAndPrint(MAP_X / 2 - 12, 6, "滚轮单击：创建石块");
	GotoxyAndPrint(MAP_X / 2 - 12, 8, "右键单击：消除障碍");
	GotoxyAndPrint(MAP_X / 2 - 12, 10, "界外双击：退出编辑");
	setColor(7, 0);
	//鼠标事件相关
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD ir = {};
	DWORD dwCount = 0;
	SetConsoleMode(hInput, ENABLE_MOUSE_INPUT);
	//捕获鼠标事件并反馈给屏幕
	while (true)
	{
		ReadConsoleInput(hInput, &ir, 1, &dwCount);
		if (ir.EventType == MOUSE_EVENT)
		{
			//左键绘制土块障碍
			if (ir.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			{
				COORD pos = ir.Event.MouseEvent.dwMousePosition;//获取按键的位置
				//不可在我方坦克处绘制
				if (pos.X / 2 >= ptank->core.X - 1 &&
					pos.X / 2 <= ptank->core.X + 1 &&
					pos.Y >= ptank->core.Y - 1 &&
					pos.Y <= ptank->core.Y + 1)
					continue;
				//不可在我方坦克绘制
				int flag = 0;
				for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
				{
					if (pos.X / 2 >= penemytank[i].core.X - 1 &&
						pos.X / 2 <= penemytank[i].core.X + 1 &&
						pos.Y >= penemytank[i].core.Y - 1 &&
						pos.Y <= penemytank[i].core.Y + 1)
						flag = 1;
					//continue;//作用域是此for
				}
				if (flag == 1) continue;
				//不可在泉水绘制
				if (pos.X / 2 >= MAP_X_WALL / 4 &&
					pos.X / 2 <= MAP_X_WALL / 4 + 1 &&
					pos.Y >= MAP_Y - 2 - 1 &&
					pos.Y <= MAP_Y - 2) continue;
				//可绘制处（除边界、坦克、泉水）
				if (pos.X > 1 && pos.X < MAP_X_WALL && pos.Y >0 && pos.Y < MAP_Y - 1)
				{
					g_MAP[pos.X / 2][pos.Y] = 土块障碍;
					GotoxyAndPrint(pos.X / 2, pos.Y, "※");
				}
			}
			//滚轮绘制石块障碍
			if (ir.Event.MouseEvent.dwButtonState == FROM_LEFT_2ND_BUTTON_PRESSED)
			{
				COORD pos = ir.Event.MouseEvent.dwMousePosition;//获取按键的位置
				//不可在我方坦克处绘制
				if (pos.X / 2 >= ptank->core.X - 1 &&
					pos.X / 2 <= ptank->core.X + 1 &&
					pos.Y >= ptank->core.Y - 1 &&
					pos.Y <= ptank->core.Y + 1)
					continue;
				//不可在我方坦克绘制
				int flag = 0;
				for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
				{
					if (pos.X / 2 >= penemytank[i].core.X - 1 &&
						pos.X / 2 <= penemytank[i].core.X + 1 &&
						pos.Y >= penemytank[i].core.Y - 1 &&
						pos.Y <= penemytank[i].core.Y + 1)
						flag = 1;
					//continue;//作用域是此for
				}
				if (flag == 1) continue;
				//不可在泉水绘制
				if (pos.X / 2 >= MAP_X_WALL / 4 - 2 &&
					pos.X / 2 <= MAP_X_WALL / 4 + 3 &&
					pos.Y >= MAP_Y - 2 - 3 &&
					pos.Y <= MAP_Y - 2) continue;
				//可绘制处（除边界、坦克、泉水）
				if (pos.X > 1 && pos.X < MAP_X_WALL && pos.Y >0 && pos.Y < MAP_Y - 1)
				{
					g_MAP[pos.X / 2][pos.Y] = 石块障碍;
					GotoxyAndPrint(pos.X / 2, pos.Y, "■");
				}
			}
			//右键消除
			if (ir.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
			{
				COORD pos = ir.Event.MouseEvent.dwMousePosition;
				if (pos.X > 1 && pos.X < MAP_X_WALL && pos.Y >0 && pos.Y < MAP_Y - 1)
				{
					g_MAP[pos.X / 2][pos.Y] = 空地;
					GotoxyAndPrint(pos.X / 2, pos.Y, "  ");
				}
			}
			//双击退出
			if (ir.Event.MouseEvent.dwEventFlags == DOUBLE_CLICK)
			{
				COORD pos = ir.Event.MouseEvent.dwMousePosition;
				if (!(pos.X > 1 && pos.X < MAP_X_WALL && pos.Y >0 && pos.Y < MAP_Y - 1))
				{
					//地图外双击才退出
					break;
				}
			}
		}
	}
	//提示信息
	system("cls");
	setColor(12, 0);
	GotoxyAndPrint(MAP_X / 2 - 12, 12, "请输入地图名字:");
	GotoxyAndPrint(MAP_X - 24, 14, "");
	//输入文件名
	char str[15];
	char* filename = (char*)malloc(40);
	SetCursorState(true);
	scanf_s("%s", str, 15);
	SetCursorState(false);
	setColor(7, 0);
	sprintf_s(filename, 40, "%s%s%s", "conf/map/", str, ".i");
	//数据写入文件
	FILE* pFile = NULL;
	errno_t err = fopen_s(&pFile, filename, "wb");
	for (int x = 0; x < MAP_X_WALL; x++)
	{
		for (int y = 0; y < MAP_Y; y++)
		{
			fwrite(&g_MAP[x][y], sizeof(int), 1, pFile);
		}
	}
	fclose(pFile);
}