#pragma once

//�߽��С
#define MAP_X 120	
#define MAP_Y 40
#define MAP_X_WALL 80

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
#define ENEMY_TANK_AMOUNT 2//�о�����
//�ӵ�״̬
#define ������ 0
#define δ��ֵ 1
#define �Ѹ�ֵ 2
//��ͼ״̬
#define �յ� 0
#define �߽� 1
#define ���� 2
#define ʯ�� 3
#define �ݴ� 4
#define ���� 5
#define Ȫˮ 6

//ö��
enum { UP_KEY = 72, DOWN_KEY = 80, ENTER_KEY = 13 };//����ö��
enum direction { UP, DOWN, LEFT, RIGHT };//����ö��

//ϵͳ����
void SetCursorState(bool b);								//���ù��״̬
void setColor(int ForeColor, int BackGroundColor);			//������ɫ
void GotoxyAndPrint(unsigned x, unsigned y, const char* str);//��굽ָ��λ��






