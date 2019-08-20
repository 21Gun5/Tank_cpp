#pragma once

//边界大小
#define MAP_X 120	
#define MAP_Y 40
#define MAP_X_WALL 80

//怎么玩
#define 开始游戏 0
#define 读取游戏 1
#define 退出游戏 2
//选地图
#define 系统默认 0
#define 玩家提供 1
#define 返回上页 2
//选地图
#define 新建地图 0
#define 已有地图 1
#define 返回上页 2
//难度
#define 简单 0
#define 一般 1
#define 困难 2
//坦克相关
#define 我方坦克 0
#define 敌方坦克 1
#define ENEMY_TANK_AMOUNT 2//敌军数量
//子弹状态
#define 不存在 0
#define 未赋值 1
#define 已赋值 2
//地图状态
#define 空地 0
#define 边界 1
#define 土块 2
#define 石块 3
#define 草丛 4
#define 河流 5
#define 泉水 6

//枚举
enum { UP_KEY = 72, DOWN_KEY = 80, ENTER_KEY = 13 };//按键枚举
enum direction { UP, DOWN, LEFT, RIGHT };//方向枚举

//系统功能
void SetCursorState(bool b);								//设置光标状态
void setColor(int ForeColor, int BackGroundColor);			//设置颜色
void GotoxyAndPrint(unsigned x, unsigned y, const char* str);//光标到指定位置






