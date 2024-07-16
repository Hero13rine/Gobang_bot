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
	int Size;
	int Depth;
	int Player1;
	int Player2;
	int Player1Color;
	int Player2Color;
	bool AIfirst;
	Chessboard* Board;
};

