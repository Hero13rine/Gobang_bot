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
	int score;//���ӵ÷�,����÷�Ŀ�����жϵ�ǰ�Լ���������ʽ
	int allScore = 0;//��¼������Լ��Ͷ���ͬʱ�жϵ��ܺͷ֣�����÷�Ŀ�����ж�����λ�õ�����
	int stateScore = 0;//��¼����֣�����÷�����minimax���жϾ�����ʽ
	int color; //��������
};

