#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include "Game.h"
#include "chessBoard.h"
using namespace std;
class TerminalMonitor
{
public:
	static TerminalMonitor& getinstance()
	{
		static TerminalMonitor instance;
		return instance;
	}
	TerminalMonitor(const TerminalMonitor&) = delete;
	TerminalMonitor& operator=(const TerminalMonitor&) = delete;

	void destroyInstance();

public:
	int PretreatMassage(const string& input);

	void HandleMassage(const int& mode, const string& input);

	void ListenMassage();

private:
	TerminalMonitor();
	~TerminalMonitor();
	vector<int> ExtractNumInMassage(const string& massage);
	Game* AI;

private:
	void SetBoard();
	void SetDepth();
	void SetFirst();
	void ReSet();

	void SetP1LuoZI(int x, int y);
	Point GetP2LuoZI();

	int GetBBP2LuoZINum();
	void CreatBBP2Pos(int num);
	Point GetBBP2LuoZI();
	bool SetBBP2Record(int x, int y);

	void SetBWP1LuoZI(int x, int y);
	Point GetBWP2Selct();


private:
	int Size;
	int Depth;
	int Player1;
	int Player2;
	int Player1Color;
	int Player2Color;
	int BangP1ChessStep;
	int BangP2ChessStep;
	bool AIfirst;
	Chessboard* Board;

	int BBP2NPNum;
	std::vector<Point> BBP2NPPos;
	std::vector<Point> BWP1NPPos;

private:
	const std::unordered_map<std::string, int> command_map = {
		{"AI Set BoardSize",   0},
		{"AI Set AIdepth",     1},
		{"AI Set AIfirst",     2},
		{"AI Reset",           3},
		{"AI Game Start",      4},
		{"AI Game P1LuoZI",    5},
		{"AI Game AILuoZI",    6},
		{"AI Game BBP2Num",    7},
		{"AI Game BBP2Pos",    8},
		{"AI Game BBP2Rec",    9},
		{"AI Game BWP1Pos",    10},
		{"AI Game BWP2Sav",    11},
		{"Quit",              -1},
		{"Board",             -2}
	};
};
