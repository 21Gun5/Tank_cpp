#pragma once
class CMap;
class CTank;

class CGame
{
public:
	bool m_isRunning = false;
	int m_levelEneTank = 200;
	int m_levelEneBul = 70;

	const char* menuPlay[3] = { "��ʼ��Ϸ","��ȡ��Ϸ","�˳���Ϸ" };
	const char* menuWhoMap[3] = { "ϵͳĬ��","����ṩ","������ҳ" };
	const char* menuWhenMap[3] = { "�½���ͼ","���е�ͼ","������ҳ" };
	const char* menuLevel[3] = { "��","һ��","����" };
public:
	void GameInit(CMap& map);				//��ʼ������
	char* ShowGameFile();					//��ʾ�浵
	void GameOver(CTank* penemytank);		//�ƺ���
	int SelectMenu(int size, int* pindex);  //ѡ��˵���
	void SaveGameFile(CTank *pMyTank, CTank* PEnemyTank,CMap map);	//�浵
	void LoadGameFile(CTank * pMyTank, CTank * pEnemyTank, CMap &map, char* str);	//����

	// ��ӡ���
	void DrawLogo();						//��ӡͼ��
	void DrawGameHelp();					//��ӡ����
	void DrawGameInfo(CTank * pMyTank, CTank* pEnemyTank);			//��ӡ��Ϸ��Ϣ
	void DrawMenu(const char** menu, int size, int index);		//��ӡ���ֲ˵�
};


