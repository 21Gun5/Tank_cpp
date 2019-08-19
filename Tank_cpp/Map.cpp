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


//��ͼ���
char* ShowMapFile()
{
	//����ָ��Ŀ¼����׺���ļ�������������
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
	//��ʾ��ͼ�ļ�
	system("cls");
	GotoxyAndPrint(MAP_X / 4 - 5, MAP_Y / 2 - 8, "��ѡ���ͼ");
	int i = 0;								//ѭ��������for�ⶨ��
	for (; i < count; i++)
	{
		GotoxyAndPrint(MAP_X / 4 - 5, MAP_Y / 2 - 6 + i, "");
		printf("%d.%s", i + 1, mapFiles[i]);
	}
	//ѡ��
	GotoxyAndPrint(MAP_X / 4 - 5, MAP_Y / 2 - 6 + i, "������ѡ��-> ");
	SetCursorState(true);
	int input = _getch() - '0';				//��֤0-9����ASCII
	SetCursorState(false);
	char* _file = (char*)malloc(15);
	strcpy_s(_file, 15, mapFiles[input - 1]);//����ʼ��1�����±�ʼ��0	
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
				g_MAP[x][y] = �����ϰ�;
			}
			if (
				(x > MAP_X_WALL / 4 - 9 && x < MAP_X_WALL / 4 - 5 && y > MAP_Y / 2 - 9 && y < MAP_Y / 2 - 7) ||
				(x < MAP_X_WALL / 4 + 9 && x > MAP_X_WALL / 4 + 5 && y > MAP_Y / 2 - 9 && y < MAP_Y / 2 - 7) ||
				(x > MAP_X_WALL / 4 - 9 && x < MAP_X_WALL / 4 - 5 && y < MAP_Y / 2 + 7 && y > MAP_Y / 2 + 5) ||
				(x < MAP_X_WALL / 4 + 9 && x > MAP_X_WALL / 4 + 5 && y < MAP_Y / 2 + 7 && y > MAP_Y / 2 + 5)
				)
			{
				g_MAP[x][y] = ʯ���ϰ�;
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
	DrawBorder();		//��ͼ�߽�
	//��ʾ��Ϣ
	setColor(12, 0);
	GotoxyAndPrint(MAP_X / 2 - 12, 2, "     �༭��ͼ");
	GotoxyAndPrint(MAP_X / 2 - 12, 4, "�����������������");
	GotoxyAndPrint(MAP_X / 2 - 12, 6, "���ֵ���������ʯ��");
	GotoxyAndPrint(MAP_X / 2 - 12, 8, "�Ҽ������������ϰ�");
	GotoxyAndPrint(MAP_X / 2 - 12, 10, "����˫�����˳��༭");
	setColor(7, 0);
	//����¼����
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD ir = {};
	DWORD dwCount = 0;
	SetConsoleMode(hInput, ENABLE_MOUSE_INPUT);
	//��������¼�����������Ļ
	while (true)
	{
		ReadConsoleInput(hInput, &ir, 1, &dwCount);
		if (ir.EventType == MOUSE_EVENT)
		{
			//������������ϰ�
			if (ir.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			{
				COORD pos = ir.Event.MouseEvent.dwMousePosition;//��ȡ������λ��
				//�������ҷ�̹�˴�����
				if (pos.X / 2 >= ptank->core.X - 1 &&
					pos.X / 2 <= ptank->core.X + 1 &&
					pos.Y >= ptank->core.Y - 1 &&
					pos.Y <= ptank->core.Y + 1)
					continue;
				//�������ҷ�̹�˻���
				int flag = 0;
				for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
				{
					if (pos.X / 2 >= penemytank[i].core.X - 1 &&
						pos.X / 2 <= penemytank[i].core.X + 1 &&
						pos.Y >= penemytank[i].core.Y - 1 &&
						pos.Y <= penemytank[i].core.Y + 1)
						flag = 1;
					//continue;//�������Ǵ�for
				}
				if (flag == 1) continue;
				//������Ȫˮ����
				if (pos.X / 2 >= MAP_X_WALL / 4 &&
					pos.X / 2 <= MAP_X_WALL / 4 + 1 &&
					pos.Y >= MAP_Y - 2 - 1 &&
					pos.Y <= MAP_Y - 2) continue;
				//�ɻ��ƴ������߽硢̹�ˡ�Ȫˮ��
				if (pos.X > 1 && pos.X < MAP_X_WALL && pos.Y >0 && pos.Y < MAP_Y - 1)
				{
					g_MAP[pos.X / 2][pos.Y] = �����ϰ�;
					GotoxyAndPrint(pos.X / 2, pos.Y, "��");
				}
			}
			//���ֻ���ʯ���ϰ�
			if (ir.Event.MouseEvent.dwButtonState == FROM_LEFT_2ND_BUTTON_PRESSED)
			{
				COORD pos = ir.Event.MouseEvent.dwMousePosition;//��ȡ������λ��
				//�������ҷ�̹�˴�����
				if (pos.X / 2 >= ptank->core.X - 1 &&
					pos.X / 2 <= ptank->core.X + 1 &&
					pos.Y >= ptank->core.Y - 1 &&
					pos.Y <= ptank->core.Y + 1)
					continue;
				//�������ҷ�̹�˻���
				int flag = 0;
				for (int i = 0; i < ENEMY_TANK_AMOUNT; i++)
				{
					if (pos.X / 2 >= penemytank[i].core.X - 1 &&
						pos.X / 2 <= penemytank[i].core.X + 1 &&
						pos.Y >= penemytank[i].core.Y - 1 &&
						pos.Y <= penemytank[i].core.Y + 1)
						flag = 1;
					//continue;//�������Ǵ�for
				}
				if (flag == 1) continue;
				//������Ȫˮ����
				if (pos.X / 2 >= MAP_X_WALL / 4 - 2 &&
					pos.X / 2 <= MAP_X_WALL / 4 + 3 &&
					pos.Y >= MAP_Y - 2 - 3 &&
					pos.Y <= MAP_Y - 2) continue;
				//�ɻ��ƴ������߽硢̹�ˡ�Ȫˮ��
				if (pos.X > 1 && pos.X < MAP_X_WALL && pos.Y >0 && pos.Y < MAP_Y - 1)
				{
					g_MAP[pos.X / 2][pos.Y] = ʯ���ϰ�;
					GotoxyAndPrint(pos.X / 2, pos.Y, "��");
				}
			}
			//�Ҽ�����
			if (ir.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
			{
				COORD pos = ir.Event.MouseEvent.dwMousePosition;
				if (pos.X > 1 && pos.X < MAP_X_WALL && pos.Y >0 && pos.Y < MAP_Y - 1)
				{
					g_MAP[pos.X / 2][pos.Y] = �յ�;
					GotoxyAndPrint(pos.X / 2, pos.Y, "  ");
				}
			}
			//˫���˳�
			if (ir.Event.MouseEvent.dwEventFlags == DOUBLE_CLICK)
			{
				COORD pos = ir.Event.MouseEvent.dwMousePosition;
				if (!(pos.X > 1 && pos.X < MAP_X_WALL && pos.Y >0 && pos.Y < MAP_Y - 1))
				{
					//��ͼ��˫�����˳�
					break;
				}
			}
		}
	}
	//��ʾ��Ϣ
	system("cls");
	setColor(12, 0);
	GotoxyAndPrint(MAP_X / 2 - 12, 12, "�������ͼ����:");
	GotoxyAndPrint(MAP_X - 24, 14, "");
	//�����ļ���
	char str[15];
	char* filename = (char*)malloc(40);
	SetCursorState(true);
	scanf_s("%s", str, 15);
	SetCursorState(false);
	setColor(7, 0);
	sprintf_s(filename, 40, "%s%s%s", "conf/map/", str, ".i");
	//����д���ļ�
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