#pragma once
#include "Tank.h"

//��Ϸ���
void GameInit(CMap &map);				        //��ʼ������
char* ShowGameFile();					//��ʾ�浵
void GameOver(CTank * penemytank);		//�ƺ���
int SelectMenu(int size, int* pindex);  //ѡ��˵���
void SaveGame(PTANK ptank, PTANK penemytank);				//�浵
void LoadGame(PTANK ptank, PTANK penemytank, char* str);	//����
