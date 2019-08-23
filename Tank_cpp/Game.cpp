#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <io.h>
#include "Game.h"
#include "Func.h"
#include "Map.h"
#include "Tank.h"
#pragma comment(lib,"winmm.lib")

// ��ȡ˽�г�Ա
bool CGame::GetIsRunning()
{
	return m_isRunning;
}
int CGame::GetLevelEneTank()
{
	return m_levelEneTank;
}
int CGame::GetLevelEneBul()
{
	return m_levelEneBul;
}
int CGame::GetStage()
{
	return m_stage;
}
bool CGame::GetIsOver()
{
	return m_isOver;
}
int CGame::GetMaxStage()
{
	return m_maxStage;
}
bool CGame::GetNeedLoadNewStage()
{
	return m_needLoadNewStage;
}
int CGame::GetMyTankAmount()
{
	return m_myTankAmount;
}
int CGame::GetEnemyTankAmount()
{
	return m_enemyTankAmount;
}
// �޸�˽�г�Ա
void CGame::SetIsRunning(bool isRunning)
{
	m_isRunning = isRunning;
}
void CGame::SetLevelEneTank(int levelEneTank)
{
	m_levelEneTank = levelEneTank;
}
void CGame::SetLevelEneBul(int levelEneBul)
{
	m_levelEneBul = levelEneBul;
}
void CGame::SetStage(int stage)
{
	m_stage = stage;
}
void  CGame::SetIsOver(bool isOver)
{
	m_isOver = isOver;
}
void CGame::SetMaxStage(int maxStage)
{
	m_maxStage = maxStage;
}
void  CGame::SetNeedLoadNewStage(bool needLoadNewStage)
{
	m_needLoadNewStage = needLoadNewStage;
}
void CGame::SetMyTankAmount(int myTankAmount)
{
	m_myTankAmount = myTankAmount;
}
void CGame::SetEnemyTankAmount(int enemyTankAmount)
{
	m_enemyTankAmount = enemyTankAmount;
}
// ���ܺ���
void CGame::GameInit(CMap& map)
{
	//���õ�ͼ����̬��
	for (int x = 0; x < MAP_X / 2; x++)
	{
		for (int y = 0; y < MAP_Y; y++)
		{
			//��ͼ�߽�
			if (x == 0 || x == MAP_X / 2 - 1 || x == MAP_X_WALL / 2 ||	//������
				y == 0 || y == MAP_Y - 1 ||							//�����
				(x > MAP_X_WALL / 2 && y == MAP_Y / 2))				//������Ϣ����Ϸ��Ϣ�ָ���
			{
				map.SetArrMap(x, y, �߽�);
			}
			//Ȫˮ
			if (x >= MAP_X_WALL / 4 - 2 && x <= MAP_X_WALL / 4 + 3 && y >= MAP_Y - 2 - 3 && y <= MAP_Y - 2)
			{
				if (x >= MAP_X_WALL / 4 && x <= MAP_X_WALL / 4 + 1 && y >= MAP_Y - 2 - 1 && y <= MAP_Y - 2)
					map.SetArrMap(x, y, Ȫˮ);
				//else
				//	map.m_nArrMap[x][y] = ����;
			}
		}
	}

	// ����̨�������
	SetCursorState(false);				//���ع��
	system("title Tank");				//���ñ���

	// ���ڴ�С
	char strCmd[50];
	sprintf_s(strCmd, 50, "mode con cols=%d lines=%d", MAP_X, MAP_Y);
	system(strCmd);

	//��ʼ�����������
	srand((unsigned int)time(0));

	//���ű�������(�Ȳ��ţ�����һ��
	mciSendString("open conf/BGM.mp3 alias bgm", NULL, 0, NULL);//���ļ�
	mciSendString("play bgm repeat", NULL, 0, NULL);			  // ѭ������
}
char* CGame::ShowGameFile()
{
	//����ָ��Ŀ¼����׺���ļ�������������
	char* gameFiles[10] = { nullptr };
	long Handle;
	struct _finddata_t FileInfo;
	int count = 0;
	if ((Handle = _findfirst("conf/game/*.i", &FileInfo)) == -1L)
		printf("Not Found\n");
	else
	{
		gameFiles[count] = (char*)malloc(20);
		strcpy_s(gameFiles[count], 20, FileInfo.name);
		//g_Maps[count] = FileInfo.name;
		count++;
		while (_findnext(Handle, &FileInfo) == 0)
		{
			gameFiles[count] = (char*)malloc(20);
			strcpy_s(gameFiles[count], 20, FileInfo.name);
			//g_Maps[count] = FileInfo.name;
			count++;
		}
		_findclose(Handle);
	}
	//��ʾ�浵�ļ�
	system("cls");
	GotoxyAndPrint(MAP_X / 4 - 5, MAP_Y / 2 - 8, "��ѡ��浵");
	int i = 0;								//ѭ��������for�ⶨ��
	for (; i < count; i++)
	{
		GotoxyAndPrint(MAP_X / 4 - 5, MAP_Y / 2 - 6 + i, "");
		printf("%d.%s", i + 1, gameFiles[i]);
	}
	//ѡ��
	GotoxyAndPrint(MAP_X / 4 - 5, MAP_Y / 2 - 6 + i, "������ѡ��-> ");
	SetCursorState(true);
	int input = _getch() - '0';				//��֤0-9����ASCII
	SetCursorState(false);
	char* _file = (char*)malloc(15);
	strcpy_s(_file, 15, gameFiles[input - 1]);//����ʼ��1�����±�ʼ��0	
	return _file;
}
void CGame::GameOver(vector<CTank>& enemyTank)
{
	//����̹����
	int eneTankCount = enemyTank.size();
	//�ر������ļ�
	mciSendString("close bgm", NULL, 0, NULL);	//close�رն���stopֹͣ
	//��ʾ��Ϣ
	GotoxyAndPrint(MAP_X_WALL / 4 - 2, MAP_Y / 2 - 7, "GAME OVER! ", ��ʾ��ɫ);
	if (eneTankCount == 0)
		GotoxyAndPrint(MAP_X_WALL / 4 - 2, MAP_Y / 2 - 5, "A Winner!", ��ʾ��ɫ);
	else
		GotoxyAndPrint(MAP_X_WALL / 4 - 2, MAP_Y / 2 - 5, "A Loser!", ��ʾ��ɫ);
	GotoxyAndPrint(MAP_X_WALL / 4 - 2, MAP_Y / 2 - 3, "", ��ʾ��ɫ);
	printf("Scores: %d", ENEMY_TANK_AMOUNT - eneTankCount);
}
void CGame::NextStage()
{
	m_stage++;
	m_needLoadNewStage = true;
}
int  CGame::SelectMenu(int size, int* pindex)
{
	int input = _getch();			//�޻��Խ���
	switch (input)
	{
	case UP_KEY:
		if (*pindex > 0)
			* pindex -= 1;
		break;
	case DOWN_KEY:
		if (*pindex < size - 1)//���һ��
			* pindex += 1;
		break;
	case ENTER_KEY:
		return ENTER_KEY;
		break;
	default:
		break;
	}
	return 0;
}
void CGame::SaveGameFile(vector<CTank>& myTank, vector<CTank>& enemyTank, CMap map)
{
	//��ʾ��Ϣ
	system("cls");
	GotoxyAndPrint(MAP_X / 2 - 12, 12, "������浵����", ��ʾ��ɫ);
	GotoxyAndPrint(MAP_X / 2 - 12, 14, "");
	//�����ļ���
	char str[15];
	char* filename = (char*)malloc(40);
	SetCursorState(true);
	scanf_s("%s", str, 15);
	SetCursorState(false);
	sprintf_s(filename, 40, "%s%s%s", "conf/game/", str, ".i");
	//���ļ�
	FILE* pFile = NULL;
	errno_t err = fopen_s(&pFile, filename, "wb");
	//д����Ϸ����
	fwrite(&this->m_isRunning, sizeof(int), 1, pFile);		//��Ϸ����״̬
	fwrite(&this->m_levelEneTank, sizeof(int), 1, pFile);	//д���Ѷȣ����Ƶз�̹���ٶ�
	fwrite(&this->m_levelEneBul, sizeof(int), 1, pFile);	//д���Ѷȣ����Ƶз��ӵ��ٶ�
	fwrite(&this->m_stage, sizeof(int), 1, pFile);//д��ؿ���
	fwrite(&this->m_isOver, sizeof(bool), 1, pFile);//�Ƿ����
	fwrite(&this->m_maxStage, sizeof(int), 1, pFile);//���ؿ�
	fwrite(&this->m_needLoadNewStage, sizeof(bool), 1, pFile);//�Ƿ���Ҫ�����¹ؿ�
	m_myTankAmount = myTank.size();
	fwrite(&this->m_myTankAmount, sizeof(int), 1, pFile);//�ҵ�̹����������ȡʱ��
	m_enemyTankAmount = enemyTank.size();
	fwrite(&this->m_enemyTankAmount, sizeof(int), 1, pFile);//�о�̹��������
	// д���ϰ�
	for (int x = 0; x < MAP_X_WALL; x++)
	{
		for (int y = 0; y < MAP_Y; y++)
		{
			int map_point_tmp = map.GetArrMap(x, y);
			fwrite(&map_point_tmp, sizeof(int), 1, pFile);
		}
	}
	// д���ҷ�
	for (vector<CTank>::iterator it = myTank.begin(); it != myTank.end(); it++)
	{
		//д���ҷ�̹��
		COORD core_tmp = it->GetCore();
		fwrite(&core_tmp, sizeof(COORD), 1, pFile);//���Ľڵ�
		for (int i = 0; i < 5; i++)
		{
			COORD body_coor_tmp = it->GetBody(i);
			fwrite(&body_coor_tmp, sizeof(COORD), 1, pFile);//�����ڵ�
		}
		int dir_tmp = it->GetDir();
		fwrite(&dir_tmp, sizeof(int), 1, pFile);//����
		int blood_tmp = it->GetBlood();
		fwrite(&blood_tmp, sizeof(int), 1, pFile);//Ѫ��
		bool isAlve_tmp = it->GetIsAlive();
		fwrite(&isAlve_tmp, sizeof(bool), 1, pFile);//�Ƿ���
		int who_tmp = it->GetWho();
		fwrite(&who_tmp, sizeof(int), 1, pFile);//���
		bool isHidden_tmp = it->GetIsHidden();
		fwrite(&isHidden_tmp, sizeof(bool), 1, pFile);//�Ƿ�����
		int killCount_tmp = it->GetKillCount();
		fwrite(&killCount_tmp, sizeof(int), 1, pFile);//ɱ����
		int power_tmp = it->GetPower();
		fwrite(&power_tmp, sizeof(int), 1, pFile);//�˺�

		//д���ҷ��ӵ�
		COORD bul_core_tmp = it->m_bullet.GetCore();
		fwrite(&bul_core_tmp, sizeof(COORD), 1, pFile);//����
		int bul_dir_tmp = it->m_bullet.GetDir();
		fwrite(&bul_dir_tmp, sizeof(int), 1, pFile);//����
		int bul_state_tmp = it->m_bullet.GetState();
		fwrite(&bul_state_tmp, sizeof(int), 1, pFile);//״̬
		int bul_who_tmp = it->m_bullet.GetWho();
		fwrite(&bul_who_tmp, sizeof(int), 1, pFile);//��һ�����ӵ�
	}
	// д��з�
	for (vector<CTank>::iterator it = enemyTank.begin(); it != enemyTank.end(); it++)
	{
		//д��з�̹��
		COORD core_tmp = it->GetCore();
		fwrite(&core_tmp, sizeof(COORD), 1, pFile);//���Ľڵ�
		for (int j = 0; j < 5; j++)
		{
			COORD body_coor_tmp = it->GetBody(j);
			fwrite(&body_coor_tmp, sizeof(COORD), 1, pFile);//�����ڵ�
		}

		int dir_tmp = it->GetDir();
		fwrite(&dir_tmp, sizeof(int), 1, pFile);//����
		int blood_tmp = it->GetBlood();
		fwrite(&blood_tmp, sizeof(int), 1, pFile);//Ѫ��
		bool isAlve_tmp = it->GetIsAlive();
		fwrite(&isAlve_tmp, sizeof(bool), 1, pFile);//�Ƿ���
		int who_tmp = it->GetWho();
		fwrite(&who_tmp, sizeof(int), 1, pFile);//���
		bool isHidden_tmp = it->GetIsHidden();
		fwrite(&isHidden_tmp, sizeof(bool), 1, pFile);//�Ƿ�����
		int killCount_tmp = it->GetKillCount();
		fwrite(&killCount_tmp, sizeof(int), 1, pFile);//ɱ����
		int power_tmp = it->GetPower();
		fwrite(&power_tmp, sizeof(int), 1, pFile);//�˺�

		//д��з��ӵ�
		COORD bul_core_tmp = it->m_bullet.GetCore();
		fwrite(&bul_core_tmp, sizeof(COORD), 1, pFile);//����
		int bul_dir_tmp = it->m_bullet.GetDir();
		fwrite(&bul_dir_tmp, sizeof(int), 1, pFile);//����
		int bul_state_tmp = it->m_bullet.GetState();
		fwrite(&bul_state_tmp, sizeof(int), 1, pFile);//״̬
		int bul_who_tmp = it->m_bullet.GetWho();
		fwrite(&bul_who_tmp, sizeof(int), 1, pFile);//��һ�����ӵ�

	}

	fclose(pFile);
}
void CGame::LoadGameFile(vector<CTank>& myTank, vector<CTank>& enemyTank, CMap& map, char* str)
{
	char* filename = (char*)malloc(40);
	sprintf_s(filename, 40, "%s%s", "conf/game/", str);
	FILE* pFile = NULL;
	errno_t err = fopen_s(&pFile, filename, "rb");
	//��ȡ��Ϸ����
	fread(&this->m_isRunning, sizeof(int), 1, pFile);		//��Ϸ����״̬
	fread(&this->m_levelEneTank, sizeof(int), 1, pFile);	//��ȡ�Ѷȣ����Ƶз�̹���ٶ�
	fread(&this->m_levelEneBul, sizeof(int), 1, pFile);	//��ȡ�Ѷȣ����Ƶз��ӵ��ٶ�
	fread(&this->m_stage, sizeof(int), 1, pFile);//д��ؿ���
	fread(&this->m_isOver, sizeof(bool), 1, pFile);//�Ƿ����
	fread(&this->m_maxStage, sizeof(int), 1, pFile);//���ؿ�
	fread(&this->m_needLoadNewStage, sizeof(bool), 1, pFile);//�Ƿ���Ҫ�����¹ؿ�
	fread(&this->m_myTankAmount, sizeof(int), 1, pFile);//�ҵ�̹����������ȡʱ��
	fread(&this->m_enemyTankAmount, sizeof(int), 1, pFile);//�о�̹��������
	//��ȡ�ϰ�
	for (int x = 0; x < MAP_X_WALL; x++)
	{
		for (int y = 0; y < MAP_Y; y++)
		{
			int map_point_tmp;
			fread(&map_point_tmp, sizeof(int), 1, pFile);
			map.SetArrMap(x, y, map_point_tmp);
		}
	}
	//��ȡ�ҷ�
	CTank mytankTmp;

	for (int i = 0; i < this->m_myTankAmount; i++)
	{
		//��ȡ�ҷ�̹��
		COORD core_tmp;
		fread(&core_tmp, sizeof(COORD), 1, pFile);//���Ľڵ�
		mytankTmp.SetCore(core_tmp);
		for (int i = 0; i < 5; i++)
		{
			COORD body_coor_tmp;
			fread(&body_coor_tmp, sizeof(COORD), 1, pFile);//�����ڵ�
			mytankTmp.SetBody(i, body_coor_tmp);
		}
		int dir_tmp;
		fread(&dir_tmp, sizeof(int), 1, pFile);//����
		mytankTmp.SetDir(dir_tmp);
		int blood_tmp;
		fread(&blood_tmp, sizeof(int), 1, pFile);//Ѫ��
		mytankTmp.SetBlood(blood_tmp);
		bool isAlve_tmp;
		fread(&isAlve_tmp, sizeof(bool), 1, pFile);//�Ƿ���
		mytankTmp.SetIsAlive(isAlve_tmp);
		int who_tmp;
		fread(&who_tmp, sizeof(int), 1, pFile);//���
		mytankTmp.SetWho(who_tmp);
		bool isHidden_tmp;
		fread(&isHidden_tmp, sizeof(bool), 1, pFile);//�Ƿ�����
		mytankTmp.SetIsHidden(isHidden_tmp);
		int killCount_tmp;
		fread(&killCount_tmp, sizeof(int), 1, pFile);//ɱ����
		mytankTmp.SetKillCount(killCount_tmp);
		int power_tmp;
		fread(&power_tmp, sizeof(int), 1, pFile);//�˺�
		mytankTmp.SetPower(power_tmp);

		//��ȡ�ҷ��ӵ�		
		COORD bul_core_tmp;
		fread(&bul_core_tmp, sizeof(COORD), 1, pFile);//����
		mytankTmp.m_bullet.SetCore(bul_core_tmp);
		int bul_dir_tmp;
		fread(&bul_dir_tmp, sizeof(int), 1, pFile);//����
		mytankTmp.m_bullet.SetDir(bul_dir_tmp);
		int bul_state_tmp;
		fread(&bul_state_tmp, sizeof(int), 1, pFile);//״̬
		mytankTmp.m_bullet.SetState(bul_state_tmp);
		int bul_who_tmp;
		fread(&bul_who_tmp, sizeof(int), 1, pFile);//��һ�����ӵ�
		mytankTmp.m_bullet.SetWho(bul_who_tmp);
		// ��ʱ̹�˼�������
		myTank.push_back(mytankTmp);
	}
	//��ȡ�з�
	CTank enemytankTmp;
	for (int i = 0; i < this->m_enemyTankAmount; i++)
	{
		//��ȡ�з�̹��
		COORD core_tmp;
		fread(&core_tmp, sizeof(COORD), 1, pFile);//���Ľڵ�
		enemytankTmp.SetCore(core_tmp);
		for (int i = 0; i < 5; i++)
		{
			COORD body_coor_tmp;
			fread(&body_coor_tmp, sizeof(COORD), 1, pFile);//�����ڵ�
			enemytankTmp.SetBody(i, body_coor_tmp);
		}
		int dir_tmp;
		fread(&dir_tmp, sizeof(int), 1, pFile);//����
		enemytankTmp.SetDir(dir_tmp);
		int blood_tmp;
		fread(&blood_tmp, sizeof(int), 1, pFile);//Ѫ��
		enemytankTmp.SetBlood(blood_tmp);
		bool isAlve_tmp;
		fread(&isAlve_tmp, sizeof(bool), 1, pFile);//�Ƿ���
		enemytankTmp.SetIsAlive(isAlve_tmp);
		int who_tmp;
		fread(&who_tmp, sizeof(int), 1, pFile);//���
		enemytankTmp.SetWho(who_tmp);
		bool isHidden_tmp;
		fread(&isHidden_tmp, sizeof(bool), 1, pFile);//�Ƿ�����
		enemytankTmp.SetIsHidden(isHidden_tmp);
		int killCount_tmp;
		fread(&killCount_tmp, sizeof(int), 1, pFile);//ɱ����
		enemytankTmp.SetKillCount(killCount_tmp);
		int power_tmp;
		fread(&power_tmp, sizeof(int), 1, pFile);//�˺�
		enemytankTmp.SetPower(power_tmp);

		//fread(&enemytankTmp.m_core, sizeof(COORD), 1, pFile);//���Ľڵ�
		//for (int j = 0; j < 5; j++)
		//{
		//	fread(&enemytankTmp.m_body[j], sizeof(COORD), 1, pFile);//�����ڵ�
		//}
		//fread(&enemytankTmp.m_dir, sizeof(int), 1, pFile);//����
		//fread(&enemytankTmp.m_blood, sizeof(int), 1, pFile);//Ѫ��
		//fread(&enemytankTmp.m_isAlive, sizeof(bool), 1, pFile);//�Ƿ���
		//fread(&enemytankTmp.m_who, sizeof(int), 1, pFile);//���
		//fread(&enemytankTmp.m_isHidden, sizeof(bool), 1, pFile);//�Ƿ�����
		//fread(&enemytankTmp.m_killCount, sizeof(int), 1, pFile);//ɱ����
		//fread(&enemytankTmp.m_power, sizeof(int), 1, pFile);//�˺�

		//��ȡ�з��ӵ�		
		COORD bul_core_tmp;
		fread(&bul_core_tmp, sizeof(COORD), 1, pFile);//����
		enemytankTmp.m_bullet.SetCore(bul_core_tmp);
		int bul_dir_tmp;
		fread(&bul_dir_tmp, sizeof(int), 1, pFile);//����
		enemytankTmp.m_bullet.SetDir(bul_dir_tmp);
		int bul_state_tmp;
		fread(&bul_state_tmp, sizeof(int), 1, pFile);//״̬
		enemytankTmp.m_bullet.SetState(bul_state_tmp);
		int bul_who_tmp;
		fread(&bul_who_tmp, sizeof(int), 1, pFile);//��һ�����ӵ�
		enemytankTmp.m_bullet.SetWho(bul_who_tmp);

		// ��ʱ�о�̹����ӽ�����
		enemyTank.push_back(enemytankTmp);
	}


	fclose(pFile);
}
// ���ִ�ӡ
void CGame::DrawLogo()
{
	GotoxyAndPrint(MAP_X / 4 - 9, MAP_Y / 2 - 15, "MMP\"\"MM\"\"YMM                      `7MM      ");
	GotoxyAndPrint(MAP_X / 4 - 9, MAP_Y / 2 - 14, "P'   MM   `7                        MM      ");
	GotoxyAndPrint(MAP_X / 4 - 9, MAP_Y / 2 - 13, "     MM       ,6\"Yb.  `7MMpMMMb.    MM, MP'");
	GotoxyAndPrint(MAP_X / 4 - 9, MAP_Y / 2 - 12, "     MM      8)   MM    MM    MM    MM ;Y   ");
	GotoxyAndPrint(MAP_X / 4 - 9, MAP_Y / 2 - 11, "     MM       ,pm9MM    MM    MM    MM;Mm   ");
	GotoxyAndPrint(MAP_X / 4 - 9, MAP_Y / 2 - 10, "     MM      8M   MM    MM    MM    MM `Mb. ");
	GotoxyAndPrint(MAP_X / 4 - 9, MAP_Y / 2 - 9, "   .JMML.    `Moo9^Yo..JMML  JMML..JMML. YA.");
}
void CGame::DrawGameHelp()
{
	GotoxyAndPrint((MAP_X + MAP_X_WALL) / 4 - 3, 24, " ��  ��  ˵  ��", ��ʾ��ɫ);
	GotoxyAndPrint((MAP_X + MAP_X_WALL) / 4 - 3, 26, "W/I: ��  S/K: ��", ��ʾ��ɫ);
	GotoxyAndPrint((MAP_X + MAP_X_WALL) / 4 - 3, 28, "A/J: ��  D/L: ��", ��ʾ��ɫ);
	GotoxyAndPrint((MAP_X + MAP_X_WALL) / 4 - 3, 30, "Q:  ��ͣ��Ϸ", ��ʾ��ɫ);
	GotoxyAndPrint((MAP_X + MAP_X_WALL) / 4 - 3, 32, "�ո�/H: ����", ��ʾ��ɫ);
}
void CGame::DrawGameInfo(vector<CTank>& myTank, vector<CTank>& enemyTank)
{
	//��ȡ����̹����
	int eneTankCount = enemyTank.size();
	//��ȡ��ǰ�Ѷ�
	char level[10];
	if (m_levelEneTank == 300) strcpy_s(level, 10, "��\0");
	else if (m_levelEneTank == 200) strcpy_s(level, 10, "һ��\0");
	else if (m_levelEneTank == 100)strcpy_s(level, 10, "����\0");
	//����or��ͣ״̬
	GotoxyAndPrint(MAP_X_WALL / 2 + 1, 1, "RUNNING", ��ʾ��ɫ);
	GotoxyAndPrint(MAP_X_WALL / 2 + 1, 2, "Q: ��ͣ��Ϸ", ��ʾ��ɫ);
	// ��ǰ�ؿ�
	if (m_stage <= m_maxStage)
	{
		GotoxyAndPrint((MAP_X + MAP_X_WALL) / 4 - 3, 5, "", ��ʾ��ɫ);
		printf("��ǰ�ؿ�: %2d", m_stage);
	}
	else
	{
		GotoxyAndPrint((MAP_X + MAP_X_WALL) / 4 - 3, 5, "��ǰ�ؿ�: ȫ��ͨ��", ��ʾ��ɫ);
	}
	// ̹������ֵ
	if (myTank.size() == 2)
	{
		GotoxyAndPrint((MAP_X + MAP_X_WALL) / 4 - 3, 7, "", ��ʾ��ɫ);
		printf("A ����ֵ: %2d", myTank[0].GetBlood());
		GotoxyAndPrint((MAP_X + MAP_X_WALL) / 4 - 3, 9, "", ��ʾ��ɫ);
		printf("B ����ֵ: %2d", myTank[1].GetBlood());
	}
	else if (myTank.size() == 1)
	{
		if (myTank[0].GetWho() == �ҷ�̹��A)
		{
			GotoxyAndPrint((MAP_X + MAP_X_WALL) / 4 - 3, 7, "", ��ʾ��ɫ);
			printf("A ����ֵ: %2d", myTank[0].GetBlood());
			GotoxyAndPrint((MAP_X + MAP_X_WALL) / 4 - 3, 9, "B ����ֵ: ����", ��ʾ��ɫ);
		}
		else if (myTank[0].GetWho() == �ҷ�̹��B)
		{
			GotoxyAndPrint((MAP_X + MAP_X_WALL) / 4 - 3, 7, "A ����ֵ: ����", ��ʾ��ɫ);
			GotoxyAndPrint((MAP_X + MAP_X_WALL) / 4 - 3, 9, "", ��ʾ��ɫ);
			printf("B ����ֵ: %2d", myTank[0].GetBlood());
		}
	}
	else if (myTank.size() == 0)
	{
		GotoxyAndPrint((MAP_X + MAP_X_WALL) / 4 - 3, 7, "A ����ֵ: ����", ��ʾ��ɫ);
		GotoxyAndPrint((MAP_X + MAP_X_WALL) / 4 - 3, 9, "B ����ֵ: ����", ��ʾ��ɫ);
	}
	//��Ϸ��Ϣ��ӡ
	GotoxyAndPrint((MAP_X + MAP_X_WALL) / 4 - 3, 11, "", ��ʾ��ɫ);
	printf("��ǰ����: %2d", ENEMY_TANK_AMOUNT - eneTankCount);
	GotoxyAndPrint((MAP_X + MAP_X_WALL) / 4 - 3, 13, "", ��ʾ��ɫ);
	printf("��̹����: %2d", eneTankCount);
	GotoxyAndPrint((MAP_X + MAP_X_WALL) / 4 - 3, 15, "", ��ʾ��ɫ);
	printf("��ǰ�Ѷ�: %s", level);
}
void CGame::DrawMenu(const char** menu, int size, int index)
{
	system("cls");
	DrawLogo();
	//��ʾ��Ϣ
	for (int i = 0; i < size; i++)//�˵�����
	{
		if (i == index)
		{
			GotoxyAndPrint(MAP_X / 4 - 5, MAP_Y / 2 - 6 + 2 * i, menu[i], ��ʾ��ɫ);
		}
		else
			GotoxyAndPrint(MAP_X / 4 - 5, MAP_Y / 2 - 6 + 2 * i, menu[i], Ĭ����ɫ);
	}
}