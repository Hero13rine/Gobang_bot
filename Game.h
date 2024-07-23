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
		bool isfour1 = false;//����
		bool isfour2 = false;//����
		bool isthree = false;//����
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

	int EvaluateALL();//�����ֺ���

	int evaluateAIPoint(int x, int y);//��Ĵ�ֺ���

	int evaluatePlayerPoint(int x, int y);

	void go(int x, int y, int color);//����

	Point best();

	Point minimax(vector<Point> PointList);

	int minSearch(int LastBestValue, int depth);//�����ֱ��Ǻ����ꡢ�����ꡢ��֦����

	int maxSearch(int LastBestValue, int depth);

	int minimax2(int type, int depth, int alpha, int beta);

	Point deepeningMinimax(int depth, int maxDepth);

	Point BestPoint;

	int minimax3(int type, int depth, int alpha, int beta, int n);

	vector<Point> FiveBestPointList;

	Point getBestPointformList(vector<Point> PointList);

	vector<Point> GetBPointList(int type);

	vector<Point> randomPoint(int type, int num); //���ȡ��

	bool checkHighPriorityPoint(state st);

	bool CheckWin(int nx, int ny);

	bool CanPut(int nx, int ny);//�ܷ�����

	bool inboard(int nx, int ny);//�ж�(x,y)�Ƿ���������

	void PlayerGo(int nx, int ny);//�������

	void AIGo();// ��������

	Point FiveSteps(int n);

	int setFiveStepsWay(int n)
	{
		N5 = n;
		return N5;
	}

	bool exchange();//�ж��Ƿ���

	void ThreeSteps();

	vector<Point> getVcxPoints(int type, bool isVcf);//isVcf �Ƿ�����������

	Point vcx(int type, int depth, bool isVcf);

	Point deepening(int depth, int maxDepth, bool isVcf);

	//�ڶ�����ɱ��ʽ

	vector<Point> getVcfPoints(int type);

	vector<Point> getVctPoints(int type);

	Point vcxMax(int type, int depth);

	Point vcxMin(int type, int depth);

	void SaveChessboard();

	state st1;//��¼����
	int isBoardEnd = false;
	int m_computercolor = -1;
	int m_personcolor = -1;
	int m_nodes = 0;
	int s;//���巽
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
	int N5 = 2;//����N��
	int winner = 0;
	string first, next; //����
	int step = 0;
	int minx = 0, miny = 0, mx = 0, my = 0;//��¼��ǰ���������Ч��Χ



	vector<Point> manual;
};

bool cmpAllScore(const Point a, const Point b);

bool cmpScore(const Point a, const Point b);

bool cmpStateScore(const Point a, const Point b);