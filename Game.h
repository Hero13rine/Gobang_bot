#pragma once
#include"chessBoard.h"
#include"Point.h"
#include"Initdata.h"
#include"Open.h"
#include<fstream>
#include<iostream>
#include <unordered_map>

class Game :public Open
{
public:
	typedef struct state {
		bool isfour1 = false;//活四
		bool isfour2 = false;//冲四
		bool isthree = false;//活三
		int four1count = 0;
		int four21count = 0;//0111010
		int four2count = 0;
		int three1count = 0;
		int three12count = 0;
		int three2count = 0;
		int two1count = 0;
		int two2count = 0;
		int mian1 = 0;
		int huo1 = 0;
		int fivecount = 0;
	}state;

	Game();

	int StateCheck(const Point& a, int color);

	int EvaluateALL();//局面打分函数

	int evaluateAIPoint(int x, int y);//点的打分函数

	int evaluatePlayerPoint(int x, int y);

	void go(int x, int y, int color);//下子

	Point best();

	Point minimax(vector<Point> PointList);

	int minSearch(int LastBestValue, int depth);//参数分别是横坐标、纵坐标、剪枝参数

	int maxSearch(int LastBestValue, int depth);

	int minimax2(int type, int depth, int alpha, int beta);

	Point deepeningMinimax(int depth, int maxDepth);

	Point BestPoint;

	int minimax3(int type, int depth, int alpha, int beta, int n);

	vector<Point> FiveBestPointList;

	Point getBestPointformList(vector<Point> PointList);

	vector<Point> GetBPointList(int type);

	vector<Point> randomPoint(int type, int num); //随机取点

	bool checkHighPriorityPoint(state st);

	bool CheckWin(int nx, int ny);

	bool CanPut(int nx, int ny);//能否落子

	bool inboard(int nx, int ny);//判断(x,y)是否在棋盘内

	void PlayerGo(int nx, int ny);//玩家行棋

	void AIGo();// 电脑行棋

	Point FiveSteps(int n);

	int setFiveStepsWay(int n)
	{
		N5 = n;
		return N5;
	}

	bool exchange();//判断是否换手

	void ThreeSteps();

	vector<Point> getVcxPoints(int type, bool isVcf);//isVcf 是否是连续冲四

	Point vcx(int type, int depth, bool isVcf);

	Point deepening(int depth, int maxDepth, bool isVcf);

	//第二种算杀方式

	vector<Point> getVcfPoints(int type);

	vector<Point> getVctPoints(int type);

	Point vcxMax(int type, int depth);

	Point vcxMin(int type, int depth);

	void SaveChessboard();

	state st1;//记录局面
	int isBoardEnd = false;
	int m_computercolor = -1;
	int m_personcolor = -1;
	int m_nodes = 0;
	int s;//下棋方
	Point LastPlayerStep;
	Point LastComStep;
	float attack = 0;
	float defense = 0;
	vector<Point> HighPoint;
	vector<Point> MidPoint;
	vector<Point> LowPoint;
	vector<Point> killPoint;
	bool isThreeSteps = true;
	bool isFiveSteps = true;
	int N5 = 2;//五手N打
	int winner = 0;
	string first, next; //悔棋
	int step = 0;
	int minx = 0, miny = 0, mx = 0, my = 0;//记录当前棋盘最大有效范围



	vector<Point> manual;
};

bool cmpAllScore(const Point a, const Point b);

bool cmpScore(const Point a, const Point b);

bool cmpStateScore(const Point a, const Point b);