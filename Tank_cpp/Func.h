#pragma once

//�߽��С
enum MapSize
{
	MAP_X = 120,
	MAP_Y = 40,
	MAP_X_WALL = 80
};
//��ô��
enum howToPlay
{
	��ʼ��Ϸ,
	��ȡ��Ϸ,
	�˳���Ϸ
};
//ѡ��ͼ
enum whoMap
{
	ϵͳĬ��,
	����ṩ,
	������ҳ
};
//ѡ��ͼ
enum whenMap
{
	�½���ͼ,
	���е�ͼ,
	//������ҳ
};
//�Ѷ�
enum level
{
	��,
	һ��,
	����
};
//̹�����
enum tankType
{
	�ҷ�̹��A,
	�ҷ�̹��B,
	�з�̹��
};
// ̹������
enum tankAmount
{
	MY_TANK_AMOUNT = 2,
	ENEMY_TANK_AMOUNT = 4,
};
//�ӵ�״̬
enum bulState
{
	������,
	δ��ֵ,
	�Ѹ�ֵ
};
//��ͼ״̬
enum mapState
{
	�յ�,
	�߽�,
	����,
	ʯ��,
	�ݴ�,
	����,
	Ȫˮ,
};
//��ɫ
enum color
{
	Ĭ����ɫ = 7,
	��ʾ��ɫ = 12,
	��̹��ɫ = 10,
	��̹��ɫ = 11,
	������ɫ = 6,
	ʯ����ɫ = 8,
	�ݴ���ɫ = 2,
	������ɫ = 9,
	Ȫˮ��ɫ = 12
};
//����
enum key
{
	UP_KEY = 72, DOWN_KEY = 80, ENTER_KEY = 13
};
//����
enum direction
{
	UP, DOWN, LEFT, RIGHT
};

// �����̰���
#define KEYDOWN(key) ((GetAsyncKeyState(key) & 0x8000)?1:0)

//ϵͳ����
void SetCursorState(bool b);								//���ù��״̬
void GotoxyAndPrint(unsigned x, unsigned y, const char* str, int ForeColor = Ĭ����ɫ);//��굽ָ��λ��