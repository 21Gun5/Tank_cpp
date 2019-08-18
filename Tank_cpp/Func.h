#pragma once
#include "Data.h"

//ϵͳ����
void SetCursorState(bool b);								//���ù��״̬
void setColor(int ForeColor, int BackGroundColor);			//������ɫ
void GotoxyAndPrint(unsigned x, unsigned y, const char* str);//��굽ָ��λ��

//��Ϸ���
void GameInit();				        //��ʼ������
char* ShowGameFile();					//��ʾ�浵
void GameOver(PTANK penemytank);		//�ƺ���
int SelectMenu(int size, int* pindex);  //ѡ��˵���
void SaveGame(PTANK ptank, PTANK penemytank);				//�浵
void LoadGame(PTANK ptank, PTANK penemytank, char* str);	//����

//��ӡ���
void DrawLogo();						//��ӡͼ��
void DrawBorder();						//��ӡ�߽�
void DrawGameHelp();					//��ӡ����
void DrawBarr();						//��ӡ�ϰ�
void DrawTank(PTANK ptank, int who);	//��ӡ̹��
void DrawBullet(PBULLET pbullet, PTANK ptank);				//��ӡ�ӵ�
void DrawGameInfo(PTANK ptank, PTANK penemytank);			//��ӡ��Ϸ��Ϣ
void DrawMenu(const char** menu, int size, int index);		//��ӡ���ֲ˵�

//̹�����
void SetTankShape(PTANK ptank);								  //����̹����̬
int  GetLiveEnemyAmount(PTANK penemytank);					  //���о�����	
void CleanTankTail(COORD oldCore, PCOORD oldBody);			  //�����̹��
void ManipulateMyTank(PTANK ptank, int who, PTANK penemytank); //�����ҷ�̹��
bool IsMyTankMeetOther(PTANK ptank, int dir, PTANK penemytank);//�赲�ҷ�̹��
void ManipulateEneTank(PTANK ptank, int who, PTANK pmytank, PTANK penemytank);//���ݵз�̹��
bool IsEneTankMeetOther(PTANK ptank, int dir, PTANK pmytank, PTANK penemytank);//�赲�з�̹��

//�ӵ����
void MoveBullet(PBULLET pbullet);	//�ƶ��ӵ�
void CleanBullet(COORD oldBulCore);	//������ӵ�
void IsMyBulMeetOther(PBULLET pbullet, PTANK penemytank, PTANK ptank); //�ҷ��ӵ���ײ
void IsEneBulMeetOther(PBULLET pbullet, PTANK penemytank, PTANK ptank);//�з��ӵ���ײ

//�ϰ������
char* ShowMapFile();			//��ʾ��ͼ�ļ�
void LoadMapFile(char* str);	//�����ͼ�ļ�
void SetDefaultMap();			//ϵͳĬ�ϵ�ͼ
void CustomizeMap(PTANK ptank, PTANK penemytank);//�Զ����ͼ