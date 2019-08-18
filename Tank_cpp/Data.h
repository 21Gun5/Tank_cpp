#pragma once
#include <Windows.h>

//�߽��С
#define MAP_X 90		
#define MAP_Y 30
#define MAP_X_WALL 60
//��ô��
#define ��ʼ��Ϸ 0
#define ��ȡ��Ϸ 1
#define �˳���Ϸ 2
//ѡ��ͼ
#define ϵͳĬ�� 0
#define ����ṩ 1
#define ������ҳ 2
//ѡ��ͼ
#define �½���ͼ 0
#define ���е�ͼ 1
#define ������ҳ 2
//�Ѷ�
#define �� 0
#define һ�� 1
#define ���� 2
//̹�����
#define �ҷ�̹�� 0
#define �з�̹�� 1
#define ENEMY_TANK_AMOUNT 7//�о�����
//�ӵ�״̬
#define ������ 0
#define δ��ֵ 1
#define �Ѹ�ֵ 2
//��ͼ״̬
#define �յ� 0
#define ��ͼ�߽� 1
#define �����ϰ� 2
#define ʯ���ϰ� 3
#define �Ҽ�Ȫˮ 4

//ȫ�ֱ���
extern int g_MAP[MAP_X][MAP_Y];	//��ͼ����
extern bool g_isRunning;		//�Ƿ�����
extern int g_levelEneTank;		//��̹�ٶ�
extern int g_levelEneBul;		//�е��ٶ�

//���ֲ˵�
extern const char* menuPlay[3];
extern const char* menuWhoMap[3];
extern const char* menuWhenMap[3];
extern const char* menuLevel[3];

//ö��
enum { _UP = 72, _DOWN = 80, ENTER = 13 };//����ö��
enum direction { UP, DOWN, LEFT, RIGHT };//����ö��

//�ӵ��ṹ��
typedef struct _BULLET
{
	COORD core;			//����
	enum  direction dir;//����
	int state;			//�ӵ�״̬
}BULLET, * PBULLET;
//̹�˽ṹ��
typedef struct _TANK
{
	COORD core;			//���ĵ�
	COORD body[5];		//�����ڵ�
	enum direction dir;	//����
	unsigned blood;		//Ѫ��
	bool isAlive;		//�Ƿ���
	int who;			//��һ��
	BULLET bullet;		//�ӵ�
}TANK, * PTANK;