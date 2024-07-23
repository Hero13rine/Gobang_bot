#include "TerminalMonitor.h"

//Board[y][x]


TerminalMonitor::TerminalMonitor()
{
	this->AI = new(Game);
	Size = 15;
	Depth = 1;
	AIfirst = false;
	Player1 = -1; //初始化 player指的是什么？
	Player2 = -1;
	Player1Color = -1;  //初始化clolr 类似
	Player2Color = -1;
	this->Board = new (Chessboard);
}

TerminalMonitor::~TerminalMonitor()
{

}

void TerminalMonitor::destroyInstance()
{
	// 由于构造函数是私有的，不能直接销毁单例实例
}

int TerminalMonitor::PretreatMassage(const string& input)
{
	// 在这里实现对输入消息的预处理逻辑
	// 返回处理后的结果或者标志信息
	if (input.find("AI Set BoardSize") != std::string::npos)
	{
		return 0; // AI Set BoardSize:棋盘大小设置，需要提供的大小有13*13，15*15和19*19。返回0
	}
	else if (input.find("AI Set AIdepth") != std::string::npos)
	{
		return 1; // AI Set AIdepth：AI难度选择，一般情况下需要设置有2种难度，0为娱乐难度，1为比赛难度。返回1
	}
	else if (input.find("AI Set AIfirst") != std::string::npos)
	{
		return 2; // AI Set AIfirst：AI是否先手，0为先手，执黑；1为后手执白。返回2
	}
	else if (input.find("AI Reset") != std::string::npos)
	{
		return 3; // AI ReSet：清空本地记录，重置上方参数。返回3
	}
	else if (input.find("AI Game Start") != std::string::npos)
	{
		return 4; // AI Game Start：游戏开始。返回4
	}
	else if (input.find("AI Game P1LuoZI") != std::string::npos)
	{
		return 5; // AI Game P1LuoZI：P1（对方）落子信息，后两位数字为坐标。返回5
	}
	else if (input.find("AI Game AILuoZI") != std::string::npos)
	{
		return 6; // AI Game AILuoZI：请求AI落子，返回6
	}
	else if (input.find("AI Game BBP2Num") != std::string::npos) return 7;     // Banggame Blcakchess Free Putting Num,请求作为P2的黑方N打的数目，返回7

	else if (input.find("AI Game BBP2Pos") != std::string::npos) return 8;     // Banggame Blcakchess Free Putting Pos,请求作为P2的黑方N打的位置，返回8

	else if (input.find("AI Game BBP2Rec") != std::string::npos) return 9;     // Banggame Blcakchess Free Putting Record,请求作为P2的黑方记录白方选择留下的黑子，返回9

	else if (input.find("AI Game BWP1Pos") != std::string::npos) return 10;    // Banggame Whitechess Free Putting Pos,对方P1的黑方N打的位置，返回10

	else if (input.find("AI Game BWP2Sav") != std::string::npos) return 11;    // Banggame Whitechess Free Putting Save,请求作为P2的白方选择黑方N打留下的位置，返回11

	else if (input.find("Quit") != std::string::npos)
	{
		return -1; // Quit：，返回-1
	}
	else if (input.find("Board") != std::string::npos)
	{
		return -2; // Quit：，返回-1
	}
	// 如果没有匹配的内容，返回-100
	return -100;
}

void TerminalMonitor::HandleMassage(const int& mode, const string& input)
{
	switch (mode)
	{
	case 0:
	{
		Size = ExtractNumInMassage(input)[0];

		cout << "BoardSzie OK";
		break;
	}
	case 1:
	{
		Depth = ExtractNumInMassage(input)[0];
		cout << "AIDepth OK";
		break;
	}
	case 2:
	{
		AIfirst = ExtractNumInMassage(input)[0];
		cout << "AIfirst OK";
		break;
	}
	case 3:
	{
		// 我取消了

		cout << "ReSet OK";
		break;
	}
	case 4:
	{
		//通知后台游戏开始，这里将所有的设置在这个事件中完成，您也可以在单独的事件中完成。
		//再此构造game类
			// 初始化五手n打
		this->AI->setFiveStepsWay(2);

		if (AIfirst == 0)//###################AI是否先手
		{
			//###################本方执黑
			AI->s = 2;
			AI->m_computercolor = black;
			AI->m_personcolor = white;
			//初始化攻击防守系数
			AI->attack = 5;
			AI->defense = 1;
			AI->first = "Com";
			AI->next = "Per";
			//this->Board->printboard();
			//AI->AIGo();
		}
		else
		{
			//###################对方执黑
			//this->Board->printboard();
			AI->m_computercolor = white;
			AI->m_personcolor = black;
			AI->attack = 3;
			AI->defense = 1;
			AI->first = "Per";
			AI->next = "Com";

		}
		this->Board->resetboard();
		cout << "AIStart OK";
		break;
	}
	case 5:
	{
		//确认对方落子并记录playergo
		vector<int> numbers = ExtractNumInMassage(input);//###################从信息中解析出对方落子位置
		int x = numbers[0]; int y = numbers[1];
		AI->PlayerGo(x, y);
		cout << "P1LuoZI OK";
		break;
	}
	case 6:
	{
		//根据棋谱查询本方落子
		AI->AIGo();
		//cout << "AILuoZI"<<" "<< pos.second<<" "<< pos.first;
		break;
	}
	case 7://BBP2Num
	{
		//获取n打数目
		int num = GetBBP2LuoZINum();
		cout << "BBP2Num" << " " << num;
		break;
	}
	case 8://BBP2Pos
	{
		//获取n打位置
		Point pos = GetBBP2LuoZI();
		cout << "BBP2Pos" << " " << pos.x << " " << pos.y;
		break;
	}
	case 9://BBP2Rec
	{
		//获取留下的黑子坐标
		vector<int> numbers = ExtractNumInMassage(input);
		//处理这个坐标，更新棋谱和手数
		if (SetBBP2Record(numbers[0], numbers[1])) cout << "BBP2Rec" << " " << "true";
		else                                       cout << "BBP2Rec" << " " << "wrong";
		break;
	}
	case 10://BWP1Pos
	{
		vector<int> numbers = ExtractNumInMassage(input);
		int x = numbers[0]; int y = numbers[1];
		SetBWP1LuoZI(x, y);
		cout << "BWP1Pos" << " " << "OK";
		break;
	}
	case 11://BWP2Sav
	{
		//选择留下的坐标
		Point pos = GetBWP2Selct();
		SetBBP2Record(pos.x, pos.y);
		cout << "BWP2Sav" << " " << pos.x << " " << pos.y;
		break;
	}
	case -1:
	{
		cout << "Handling message with mode: " << mode << endl;
		break;
	}
	case -2:
	{
		//打印当前棋谱
		int i, j;
		for (i = 0; i < Size; i++)
		{
			for (j = 0; j < Size; j++)
				cout << Board->Board[i][j] << " ";
			cout << endl;
		}
		break;
	}

	case -100:
	{
		break;
	}
	default:
	{
		cout << "Handling message with mode: " << mode << endl;
		break;
	}
	}
}


Point TerminalMonitor::GetP2LuoZI()
{
	//获取最新落子
	//pair<int, int> pos 格式不能改动；AI->findBestChess(Board, Player2);需要改动。
	Game a;
	Point pos = a.best();
	//下面这句不能改动
	Board[pos.y][pos.x] = Player2;

	//需要改动：
	a.go(pos.y, pos.x, Player2);
	a.StateCheck(pos, black);
	BangP2ChessStep += 1;
	return pos;
}


//==================================================规则相关5手N打===================================================//

int TerminalMonitor::GetBBP2LuoZINum()
{
	int num = 2;
	//添加你的n打数目2-4，demo中固定返回2
	BBP2NPNum = num;
	//添加你的n打坐标,放到一个向量中，我在demo中注册的参数为  BBP2NPPos
	CreatBBP2Pos(BBP2NPNum);
	if (num > 1 && num < 5) return BBP2NPNum;
	return 2;
}

void TerminalMonitor::CreatBBP2Pos(int num)
{
	//添加你的n打坐标,放到一个向量中，我在demo中注册的参数为  BBP2NPPos
	Point pt1(1,1), pt2(1,2);

	BBP2NPPos.push_back(pt1);

	BBP2NPPos.push_back(pt2);
}

Point TerminalMonitor::GetBBP2LuoZI()
{
	//返回n打坐标，返回一次数目减1，直到0，理论上如果格式不变这部不需要修改
	Point a(-1, -1);
	if (BBP2NPNum > 0) BBP2NPNum -= 1;
	else return a;
	return BBP2NPPos[BBP2NPNum];
}

bool TerminalMonitor::SetBBP2Record(int x, int y)
{
	Point P2(x,y);
	Game a;
	if (!std::count(BBP2NPPos.begin(), BBP2NPPos.end(), P2)) return false;
	//在后台棋盘上记录留下的黑子，gomoku::MAP_PLAYER_ONE可以改成你的黑子标志
	Board[y][x] = black;
	//通知算法文件，留下的黑子，gomoku::MAP_PLAYER_ONE可以改成你的黑子标志
	a.go(y, x, black);
	a.StateCheck(P2, black);
	BangP2ChessStep += 1;
	return true;
}

void TerminalMonitor::SetBWP1LuoZI(int x, int y)
{
	Point Lz;
	Lz.x = x; Lz.y = y;
	BWP1NPPos.push_back(Lz);
}

Point TerminalMonitor::GetBWP2Selct()
{
	//白方返回选择的黑子坐标
	Point a;
	a.x = -1; a.y = -1;
	BangP2ChessStep += 1;
	if (BWP1NPPos.size() > 1) return BWP1NPPos[1];
	else return  a;
}

vector<int> TerminalMonitor::ExtractNumInMassage(const string& str)
{
	//从字符串中解析出对方落子位置
	std::vector<int> numbers;
	std::istringstream iss(str);
	std::string word;
	while (iss >> word) {
		if (std::isdigit(word[0])) {
			numbers.push_back(std::stoi(word));
		}
	}
	return numbers;
}

void TerminalMonitor::ListenMassage()
{
	//监听主循环，最好设置消息队列来应对多条信息
	while (true)
	{
		std::string command;
		// 输出提示符
		std::getline(std::cin, command);
		int i = PretreatMassage(command);// 等待用户输入命令
		HandleMassage(i, command);
		if (command == "Quit")
		{
			break; // 如果用户输入了退出命令，退出循环
		}
	}
}
