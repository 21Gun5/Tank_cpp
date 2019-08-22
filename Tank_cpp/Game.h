#pragma once

#include <vector>

using namespace std;

class CMap;
class CTank;

class CGame
{
public:
	bool m_isRunning = false;
	int m_levelEneTank = 200;
	int m_levelEneBul = 70;
	int m_stage = 1;//��Ϸ�ؿ�
	int m_isOver = 0;

	const char* menuPlay[3] = { "��ʼ��Ϸ","��ȡ��Ϸ","�˳���Ϸ" };
	const char* menuWhoMap[3] = { "ϵͳĬ��","����ṩ","������ҳ" };
	const char* menuWhenMap[3] = { "�½���ͼ","���е�ͼ","������ҳ" };
	const char* menuLevel[3] = { "��","һ��","����" };
public:
	void GameInit(CMap& map);				//��ʼ������
	char* ShowGameFile();					//��ʾ�浵
	void GameOver(vector<CTank>& enemyTank);		//�ƺ���
	void NextStage();//��һ��

	int SelectMenu(int size, int* pindex);  //ѡ��˵���
	void SaveGameFile(vector<CTank>& myTank, vector<CTank>& enemyTank,CMap map);	//�浵
	void LoadGameFile(vector<CTank>& myTank, vector<CTank>& enemyTank, CMap &map, char* str);	//����

	// ��ӡ���
	void DrawLogo();						//��ӡͼ��
	void DrawGameHelp();					//��ӡ����
	void DrawGameInfo(vector<CTank>& myTank, vector<CTank>& enemyTank);			//��ӡ��Ϸ��Ϣ
	void DrawMenu(const char** menu, int size, int index);		//��ӡ���ֲ˵�
};


