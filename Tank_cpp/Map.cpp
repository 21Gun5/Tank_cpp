#include <io.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <string>
#include "Map.h"
#include "Tank.h"


int CMap::GetArrMap(int x,int y)
{
	return m_nArrMap[x][y];
}

void CMap::SetArrMap(int x, int y, int i)
{
	m_nArrMap[x][y] = i;
}




char* CMap::ShowMapFile()
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

void CMap::LoadDefaultMap()
{
	std::string filename = "conf/map/default.i";
	//std::string filename = "conf/map/Stage2.i";
	FILE* pFile = NULL;
	errno_t err = fopen_s(&pFile, filename.c_str(), "rb");
	for (int x = 0; x < MAP_X_WALL; x++)
	{
		for (int y = 0; y < MAP_Y; y++)
		{
			fread(&m_nArrMap[x][y], sizeof(int), 1, pFile);
		}
	}
	fclose(pFile);
}

void CMap::LoadMapFile(char* str,CMap &map)
{
	char* filename = (char*)malloc(40);
	sprintf_s(filename, 40, "%s%s", "conf/map/", str);
	FILE* pFile = NULL;
	errno_t err = fopen_s(&pFile, filename, "rb");
	for (int x = 0; x < MAP_X_WALL; x++)
	{
		for (int y = 0; y < MAP_Y; y++)
		{
			fread(&map.m_nArrMap[x][y], sizeof(int), 1, pFile);
		}
	}
	fclose(pFile);
}

void CMap::SaveMapFile(vector<CTank>& myTank, vector<CTank>& enemyTank)
{
	DrawStaticMap();		//地图边界
	//提示信息
	GotoxyAndPrint((MAP_X + MAP_X_WALL) / 4 - 5, 5, "左键单击：绘制地图",提示颜色);
	GotoxyAndPrint((MAP_X + MAP_X_WALL) / 4 - 5, 7, "滚轮单击：选择种类",提示颜色);
	GotoxyAndPrint((MAP_X + MAP_X_WALL) / 4 - 5, 9, "右键单击：消除种类", 提示颜色);
	GotoxyAndPrint((MAP_X + MAP_X_WALL) / 4 - 5, 11, "界外双击：退出编辑",提示颜色);

	GotoxyAndPrint((MAP_X + MAP_X_WALL) / 4 - 5, 26, "点我选择土块: ■",土块颜色);
	GotoxyAndPrint((MAP_X + MAP_X_WALL) / 4 - 5, 28, "点我选择石块: ■",石块颜色);
	GotoxyAndPrint((MAP_X + MAP_X_WALL) / 4 - 5, 30, "点我选择草丛: ■",草丛颜色);
	GotoxyAndPrint((MAP_X + MAP_X_WALL) / 4 - 5, 32, "点我选择河流: ■",河流颜色);

	//鼠标事件相关
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD ir = {};
	DWORD dwCount = 0;
	SetConsoleMode(hInput, ENABLE_MOUSE_INPUT);

	//捕获鼠标事件并反馈给屏幕
	int barType = 空地;//障碍类别
	bool isSelectedType = 0;//是否选择了种类
	while (true)
	{
		ReadConsoleInput(hInput, &ir, 1, &dwCount);
		if (ir.EventType == MOUSE_EVENT)
		{
			// 滚轮键选择种类
			if (ir.Event.MouseEvent.dwButtonState == FROM_LEFT_2ND_BUTTON_PRESSED)
			{
				COORD pos = ir.Event.MouseEvent.dwMousePosition;
				if ((pos.X >= (MAP_X + MAP_X_WALL) / 4 - 5 && pos.Y == 26))
				{
					barType = 土块;
					isSelectedType = 1;
				}
				else if ((pos.X >= (MAP_X + MAP_X_WALL) / 4 - 5 && pos.Y == 28))
				{
					barType = 石块;
					isSelectedType = 1;
				}
				else if ((pos.X >= (MAP_X + MAP_X_WALL) / 4 - 5 && pos.Y == 30))
				{
					barType = 草丛;
					isSelectedType = 1;
				}
				else if ((pos.X >= (MAP_X + MAP_X_WALL) / 4 - 5 && pos.Y == 32))
				{
					barType = 河流;
					isSelectedType = 1;
				}
			}

			//左键绘制各种障碍（种类选择完成才可绘制
			if (isSelectedType  && ir.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			{
				COORD pos = ir.Event.MouseEvent.dwMousePosition;//获取按键的位置
				
				//不可在我方坦克处绘制
				int flagMy = 0;
				for (vector<CTank>::iterator it = myTank.begin(); it != myTank.end(); it++)
				{
					if (pos.X / 2 >= it->GetCore().X - 1 && pos.X / 2 <= it->GetCore().X + 1 && pos.Y >= it->GetCore().Y - 1 && pos.Y <= it->GetCore().Y + 1)
						flagMy = 1;
				}
				if(flagMy == 1) continue;
				//不可在敌方坦克绘制
				int flagEne = 0;
				for (vector<CTank>::iterator it = enemyTank.begin(); it != enemyTank.end(); it++)
				{
					if (pos.X / 2 >= it->GetCore().X - 1 &&
						pos.X / 2 <= it->GetCore().X + 1 &&
						pos.Y >= it->GetCore().Y - 1 &&
						pos.Y <= it->GetCore().Y + 1)
						flagEne = 1;
				}
				if (flagEne == 1) continue;
				//不可在泉水绘制
				if (pos.X / 2 >= MAP_X_WALL / 4 &&
					pos.X / 2 <= MAP_X_WALL / 4 + 1 &&
					pos.Y >= MAP_Y - 2 - 1 &&
					pos.Y <= MAP_Y - 2) continue;
				//可绘制处（除边界、坦克、泉水）
				if (pos.X > 1 && pos.X < MAP_X_WALL && pos.Y >0 && pos.Y < MAP_Y - 1)
				{
					// 存进地图
					m_nArrMap[pos.X / 2][pos.Y] = barType;
					// 实时绘制
					switch (barType)
					{
					case 土块:
						GotoxyAndPrint(pos.X / 2, pos.Y, "■", 土块颜色);
						break;
					case 石块:
						GotoxyAndPrint(pos.X / 2, pos.Y, "■",石块颜色);
						break;
					case 草丛:
						GotoxyAndPrint(pos.X / 2, pos.Y, "■", 草丛颜色);
						break;
					case 河流:
						GotoxyAndPrint(pos.X / 2, pos.Y, "■", 河流颜色);
						break;
					default:
						break;
					}
					//GotoxyAndPrint(pos.X / 2, pos.Y, "■");
				}
			}


			// 右键消除障碍
			if (ir.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
			{
				COORD pos = ir.Event.MouseEvent.dwMousePosition;
				if (pos.X > 1 && pos.X < MAP_X_WALL && pos.Y >0 && pos.Y < MAP_Y - 1)
				{
					m_nArrMap[pos.X / 2][pos.Y] = 空地;
					GotoxyAndPrint(pos.X / 2, pos.Y, "  ");
				}
			}
			// 界外双击退出
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
	GotoxyAndPrint(MAP_X / 2 - 12, 12, "请输入地图名字:",提示颜色);
	GotoxyAndPrint(MAP_X - 24, 14, "");
	//输入文件名
	char str[15];
	char* filename = (char*)malloc(40);
	SetCursorState(true);
	scanf_s("%s", str, 15);
	SetCursorState(false);
	sprintf_s(filename, 40, "%s%s%s", "conf/map/", str, ".i");
	//数据写入文件
	FILE* pFile = NULL;
	errno_t err = fopen_s(&pFile, filename, "wb");
	for (int x = 0; x < MAP_X_WALL; x++)
	{
		for (int y = 0; y < MAP_Y; y++)
		{
			fwrite(&m_nArrMap[x][y], sizeof(int), 1, pFile);
		}
	}
	fclose(pFile);
}

void CMap::DrawDynamicMap()
{
	for (int x = 0; x < MAP_X_WALL; x++)
	{
		for (int y = 0; y < MAP_Y; y++)
		{
			switch (m_nArrMap[x][y])
			{
			case 土块:
				GotoxyAndPrint(x, y, "■", 土块颜色);
				break;
			case 石块:
				GotoxyAndPrint(x, y, "■", 石块颜色);
				break;
			case 草丛:
				GotoxyAndPrint(x, y, "■", 草丛颜色);
				break;
			case 河流:
				GotoxyAndPrint(x, y, "■", 河流颜色);
				break;
			default:
				break;
			}
		}
	}
}

void CMap::DrawStaticMap()
{
	system("cls");						//换页则清屏
	for (int x = 0; x < MAP_X; x++)
	{
		for (int y = 0; y < MAP_Y; y++)
		{
			if (m_nArrMap[x][y] == 边界)
			{
				GotoxyAndPrint(x, y, "■",默认颜色);
			}
			else if(m_nArrMap[x][y] == 泉水)
			{
				GotoxyAndPrint(x, y, "★", 泉水颜色);
			}
		}
	}
}