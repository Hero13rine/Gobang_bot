#include "TerminalMonitor.h"
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
		AI->PlayerGo( x,y);
		cout << "P1LuoZI OK" ;
		break;
	}
	case 6: 
	{	
		//根据棋谱查询本方落子
		AI->AIGo();
		//cout << "AILuoZI"<<" "<< pos.second<<" "<< pos.first;
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

