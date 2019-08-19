#include "Func.h"

#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#pragma comment(lib,"winmm.lib")

//ϵͳ����
void SetCursorState(bool b)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);	//��ȡ����̨�����Ϣ
	CursorInfo.bVisible = b;					//��ʾ/���ؿ���̨���
	SetConsoleCursorInfo(handle, &CursorInfo);	//���ÿ���̨���״̬
}
void setColor(int ForeColor, int BackGroundColor)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);					 //��ȡ��ǰ���ھ��
	SetConsoleTextAttribute(handle, ForeColor + BackGroundColor * 0x10);//������ɫ
}
void GotoxyAndPrint(unsigned x, unsigned y, const char* str)
{
	COORD cur;
	cur.X = x * 2;
	cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);
	printf(str);
}



