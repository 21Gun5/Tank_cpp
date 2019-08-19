#pragma once
#include "Tank.h"

class CMap;
class CTank;

class CGame
{
public:
	bool g_isRunning = false;
	int g_levelEneTank = 200;
	int g_levelEneBul = 70;

	const char* menuPlay[3] = { "��ʼ��Ϸ","��ȡ��Ϸ","�˳���Ϸ" };
	const char* menuWhoMap[3] = { "ϵͳĬ��","����ṩ","������ҳ" };
	const char* menuWhenMap[3] = { "�½���ͼ","���е�ͼ","������ҳ" };
	const char* menuLevel[3] = { "��","һ��","����" };
public:
	void GameInit(CMap& map);				//��ʼ������
	//char* ShowGameFile();					//��ʾ�浵
	void GameOver(CTank* penemytank);		//�ƺ���
	//int SelectMenu(int size, int* pindex);  //ѡ��˵���
	//void SaveGame(PTANK ptank, PTANK penemytank);				//�浵
	//void LoadGame(PTANK ptank, PTANK penemytank, char* str);	//����

	void DrawLogo();						//��ӡͼ��
	void DrawGameHelp();					//��ӡ����
	void DrawGameInfo(CTank ptank, CTank* penemytank);			//��ӡ��Ϸ��Ϣ
	void DrawMenu(const char** menu, int size, int index);		//��ӡ���ֲ˵�
};


