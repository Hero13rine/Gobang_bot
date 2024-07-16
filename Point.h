#pragma once
#include"chessBoard.h"
#include"Initdata.h"
class Point : public Chessboard
{
public:
	Point()
	{
		this->x = -1;
		this->y = -1;
		score = 0;
		color = EMPTY;
	}
	Point(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
	int x;
	int y;
	int score;//棋子得分,这个得分目的是判断当前自己的棋子形式
	int allScore = 0;//记录点对于自己和对手同时判断的总和分，这个得分目的是判断下子位置的优劣
	int stateScore = 0;//记录局面分，这个得分是再minimax中判断局面形式
	int color; //棋子类型
};

