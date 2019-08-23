#pragma once

#include <vector>

using namespace std;

class CMap;
class CTank;

class CGame
{
//public:
	//bool m_isRunning = false;
	//int m_levelEneTank = 200;
	//int m_levelEneBul = 70;
	//int m_stage = 1;//��Ϸ�ؿ�
	//bool m_isOver = 0;
	//int m_maxStage = 3;
	//bool m_needLoadNewStage = 0;//�Ƿ���Ҫ�����¹ؿ�
	//int m_myTankAmount;
	//int m_enemyTankAmount;
private:
	bool m_isRunning = false;
	int m_levelEneTank = 200;
	int m_levelEneBul = 70;
	int m_stage = 1;//��Ϸ�ؿ�
	bool m_isOver = 0;
	int m_maxStage = 3;
	bool m_needLoadNewStage = 0;//�Ƿ���Ҫ�����¹ؿ�
	int m_myTankAmount;
	int m_enemyTankAmount;
public:
	const char* menuPlay[3] = { "��ʼ��Ϸ","��ȡ��Ϸ","�˳���Ϸ" };
	const char* menuWhoMap[3] = { "ϵͳĬ��","����ṩ","������ҳ" };
	const char* menuWhenMap[3] = { "�½���ͼ","���е�ͼ","������ҳ" };
	const char* menuLevel[3] = { "��","һ��","����" };
public:

	bool GetisRunning () ;
	int GetlevelEneTank () ;
	int GetlevelEneBul () ;
	int Getstage () ;//��Ϸ�ؿ�
	bool GetisOver () ;
	int GetmaxStage () ;
	bool GetneedLoadNewStage () ;//�Ƿ���Ҫ�����¹ؿ�
	int GetmyTankAmount();
	int GetenemyTankAmount();

	void SetisRunning(bool isRunning);
	void SetlevelEneTank(int levelEneTank);
	void SetlevelEneBul(int levelEneBul);
	void Setstage(int stage);//��Ϸ�ؿ�
	void  SetisOver(bool isOver);
	void SetmaxStage(int maxStage);
	void  SetneedLoadNewStage(bool needLoadNewStage);//�Ƿ���Ҫ�����¹ؿ�
	void SetmyTankAmount(int myTankAmount);
	void SetenemyTankAmount(int enemyTankAmount);


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


