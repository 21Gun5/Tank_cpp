#pragma once

//边界大小
enum MapSize
{
	MAP_X = 120,
	MAP_Y = 40,
	MAP_X_WALL = 80
};
//怎么玩
enum howToPlay
{
	开始游戏,
	读取游戏,
	退出游戏
};
//选地图
enum whoMap
{
	系统默认,
	玩家提供,
	返回上页
};
//选地图
enum whenMap
{
	新建地图,
	已有地图,
	//返回上页
};
//难度
enum level
{
	简单,
	一般,
	困难
};
//坦克相关
enum tankType
{
	我方坦克A,
	我方坦克B,
	敌方坦克
};
// 坦克数量
enum tankAmount
{
	MY_TANK_AMOUNT = 2,
	ENEMY_TANK_AMOUNT = 4,
};
//子弹状态
enum bulState
{
	不存在,
	未赋值,
	已赋值
};
//地图状态
enum mapState
{
	空地,
	边界,
	土块,
	石块,
	草丛,
	河流,
	泉水,
};
//颜色
enum color
{
	默认颜色 = 7,
	提示颜色 = 12,
	我坦颜色 = 10,
	敌坦颜色 = 11,
	土块颜色 = 6,
	石块颜色 = 8,
	草丛颜色 = 2,
	河流颜色 = 9,
	泉水颜色 = 12
};
//按键
enum key
{
	UP_KEY = 72, DOWN_KEY = 80, ENTER_KEY = 13
};
//方向
enum direction
{
	UP, DOWN, LEFT, RIGHT
};

// 检测键盘按下
#define KEYDOWN(key) ((GetAsyncKeyState(key) & 0x8000)?1:0)

//系统功能
void SetCursorState(bool b);								//设置光标状态
void GotoxyAndPrint(unsigned x, unsigned y, const char* str, int ForeColor = 默认颜色);//光标到指定位置