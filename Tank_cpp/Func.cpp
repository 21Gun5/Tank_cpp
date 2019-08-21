#include "Func.h"
#include <iostream>
#include <windows.h>

//ϵͳ����
void SetCursorState(bool b)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);	//��ȡ����̨�����Ϣ
	CursorInfo.bVisible = b;					//��ʾ/���ؿ���̨���
	SetConsoleCursorInfo(handle, &CursorInfo);	//���ÿ���̨���״̬
}

void GotoxyAndPrint(unsigned x, unsigned y, const char* str, int ForeColor)
{
	COORD cur;
	cur.X = x * 2;
	cur.Y = y;

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(handle, cur);
	SetConsoleTextAttribute(handle, ForeColor);//������ɫ
	std::cout << str;
}





