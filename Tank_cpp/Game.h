#pragma once
#include <vector>
using namespace std;

class CMap;
class CTank;

class CGame
{
private:
	bool m_isRunning = false;		//�Ƿ�����
	int m_levelEneTank = 300;		//�Ѷȣ���̹�ٶ�
	int m_levelEneBul = 90;			//�Ѷȣ��е��ٶ�
	int m_stage = 1;				//��Ϸ�ؿ�
	bool m_isOver = false;			//�Ƿ����
	int m_maxStage = 3;				//���ؿ�
	bool m_needLoadNewStage = false;//�Ƿ���Ҫ�����¹ؿ�
	int m_myTankAmount;				//�ִ���̹��������
	int m_enemyTankAmount;			//�ִ��̹������������
public:
	// ѡ��˵�
	const char* menuPlay[3] = { "��ʼ��Ϸ","��ȡ��Ϸ","�˳���Ϸ" };
	const char* menuWhoMap[3] = { "ϵͳĬ��","����ṩ","������ҳ" };
	const char* menuWhenMap[3] = { "�½���ͼ","���е�ͼ","������ҳ" };
	const char* menuLevel[3] = { "��","һ��","����" };
public:
	//��ȡ����
	bool GetIsRunning();
	int GetLevelEneTank();
	int GetLevelEneBul();
	int GetStage();
	bool GetIsOver();
	int GetMaxStage();
	bool GetNeedLoadNewStage();
	int GetMyTankAmount();
	int GetEnemyTankAmount();
	// ��������
	void SetIsRunning(bool isRunning);
	void SetLevelEneTank(int levelEneTank);
	void SetLevelEneBul(int levelEneBul);
	void SetStage(int stage);
	void SetIsOver(bool isOver);
	void SetMaxStage(int maxStage);
	void SetNeedLoadNewStage(bool needLoadNewStage);
	void SetMyTankAmount(int myTankAmount);
	void SetEnemyTankAmount(int enemyTankAmount);
	// ���ܺ���
	void GameInit(CMap& map);				//��ʼ������
	char* ShowGameFile();					//��ʾ�浵
	void GameOver(vector<CTank>& enemyTank);//�ƺ���
	void NextStage();						//��һ��
	int SelectMenu(int size, int* pindex);  //ѡ��˵���
	void SaveGameFile(vector<CTank>& myTank, vector<CTank>& enemyTank, CMap map);				//�浵
	void LoadGameFile(vector<CTank>& myTank, vector<CTank>& enemyTank, CMap& map, char* str);	//����
	// ��ӡ���
	void DrawLogo();						//��ӡͼ��
	void DrawGameHelp();					//��ӡ����
	void DrawMenu(const char** menu, int size, int index);				//��ӡ���ֲ˵�
	void DrawGameInfo(vector<CTank>& myTank, vector<CTank>& enemyTank);	//��ӡ��Ϸ��Ϣ
};
