#pragma once
#include"Point.h"
class Open : public Point
{
public:
	//----------------------五子棋26种开局----------------------
	int isHuayue(int x1, int y1, int x2, int y2, int x3, int y3);
	int isPuyue(int x1, int y1, int x2, int y2, int x3, int y3);
	int isYunyue(int x1, int y1, int x2, int y2, int x3, int y3);
	int isYuyue(int x1, int y1, int x2, int y2, int x3, int y3);
	int isXiyue(int x1, int y1, int x2, int y2, int x3, int y3);
	int isXiayue(int x1, int y1, int x2, int y2, int x3, int y3);
	int isShuiyue(int x1, int y1, int x2, int y2, int x3, int y3);
	int isLanyue(int x1, int y1, int x2, int y2, int x3, int y3);
	int isJinxing(int x1, int y1, int x2, int y2, int x3, int y3);
	int isHengxing(int x1, int y1, int x2, int y2, int x3, int y3);
	int isHanxing(int x1, int y1, int x2, int y2, int x3, int y3);
	int isMingxing(int x1, int y1, int x2, int y2, int x3, int y3);
	int isYouxing(int x1, int y1, int x2, int y2, int x3, int y3);
	int isHuixing(int x1, int y1, int x2, int y2, int x3, int y3);
	int isRuixing(int x1, int y1, int x2, int y2, int x3, int y3);
	int isChangxing(int x1, int y1, int x2, int y2, int x3, int y3);
	int isShuxing(int x1, int y1, int x2, int y2, int x3, int y3);
	int isXieyue(int x1, int y1, int x2, int y2, int x3, int y3);
	int isQiuyue(int x1, int y1, int x2, int y2, int x3, int y3);
	int isSongyue(int x1, int y1, int x2, int y2, int x3, int y3);
	int isMingyue(int x1, int y1, int x2, int y2, int x3, int y3);
	int isYinyue(int x1, int y1, int x2, int y2, int x3, int y3);
	int isCanyue(int x1, int y1, int x2, int y2, int x3, int y3);
	int isXinyue(int x1, int y1, int x2, int y2, int x3, int y3);
	int isShanyue(int x1, int y1, int x2, int y2, int x3, int y3);
	int isLiuxing(int x1, int y1, int x2, int y2, int x3, int y3);
	//-----------------------------------------------------------
	
};