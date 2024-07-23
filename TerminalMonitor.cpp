#include "TerminalMonitor.h"

//Board[y][x]


TerminalMonitor::TerminalMonitor()
{
	this->AI = new(Game);
	Size = 15;
	Depth = 1;
	AIfirst = false;
	Player1 = -1; //��ʼ�� playerָ����ʲô��
	Player2 = -1;
	Player1Color = -1;  //��ʼ��clolr ����
	Player2Color = -1;
	this->Board = new (Chessboard);
}

TerminalMonitor::~TerminalMonitor()
{

}

void TerminalMonitor::destroyInstance()
{
	// ���ڹ��캯����˽�еģ�����ֱ�����ٵ���ʵ��
}

int TerminalMonitor::PretreatMassage(const string& input)
{
	// ������ʵ�ֶ�������Ϣ��Ԥ�����߼�
	// ���ش����Ľ�����߱�־��Ϣ
	if (input.find("AI Set BoardSize") != std::string::npos)
	{
		return 0; // AI Set BoardSize:���̴�С���ã���Ҫ�ṩ�Ĵ�С��13*13��15*15��19*19������0
	}
	else if (input.find("AI Set AIdepth") != std::string::npos)
	{
		return 1; // AI Set AIdepth��AI�Ѷ�ѡ��һ���������Ҫ������2���Ѷȣ�0Ϊ�����Ѷȣ�1Ϊ�����Ѷȡ�����1
	}
	else if (input.find("AI Set AIfirst") != std::string::npos)
	{
		return 2; // AI Set AIfirst��AI�Ƿ����֣�0Ϊ���֣�ִ�ڣ�1Ϊ����ִ�ס�����2
	}
	else if (input.find("AI Reset") != std::string::npos)
	{
		return 3; // AI ReSet����ձ��ؼ�¼�������Ϸ�����������3
	}
	else if (input.find("AI Game Start") != std::string::npos)
	{
		return 4; // AI Game Start����Ϸ��ʼ������4
	}
	else if (input.find("AI Game P1LuoZI") != std::string::npos)
	{
		return 5; // AI Game P1LuoZI��P1���Է���������Ϣ������λ����Ϊ���ꡣ����5
	}
	else if (input.find("AI Game AILuoZI") != std::string::npos)
	{
		return 6; // AI Game AILuoZI������AI���ӣ�����6
	}
	else if (input.find("AI Game BBP2Num") != std::string::npos) return 7;     // Banggame Blcakchess Free Putting Num,������ΪP2�ĺڷ�N�����Ŀ������7

	else if (input.find("AI Game BBP2Pos") != std::string::npos) return 8;     // Banggame Blcakchess Free Putting Pos,������ΪP2�ĺڷ�N���λ�ã�����8

	else if (input.find("AI Game BBP2Rec") != std::string::npos) return 9;     // Banggame Blcakchess Free Putting Record,������ΪP2�ĺڷ���¼�׷�ѡ�����µĺ��ӣ�����9

	else if (input.find("AI Game BWP1Pos") != std::string::npos) return 10;    // Banggame Whitechess Free Putting Pos,�Է�P1�ĺڷ�N���λ�ã�����10

	else if (input.find("AI Game BWP2Sav") != std::string::npos) return 11;    // Banggame Whitechess Free Putting Save,������ΪP2�İ׷�ѡ��ڷ�N�����µ�λ�ã�����11

	else if (input.find("Quit") != std::string::npos)
	{
		return -1; // Quit��������-1
	}
	else if (input.find("Board") != std::string::npos)
	{
		return -2; // Quit��������-1
	}
	// ���û��ƥ������ݣ�����-100
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
		// ��ȡ����

		cout << "ReSet OK";
		break;
	}
	case 4:
	{
		//֪ͨ��̨��Ϸ��ʼ�����ｫ���е�����������¼�����ɣ���Ҳ�����ڵ������¼�����ɡ�
		//�ٴ˹���game��
			// ��ʼ������n��
		this->AI->setFiveStepsWay(2);

		if (AIfirst == 0)//###################AI�Ƿ�����
		{
			//###################����ִ��
			AI->s = 2;
			AI->m_computercolor = black;
			AI->m_personcolor = white;
			//��ʼ����������ϵ��
			AI->attack = 5;
			AI->defense = 1;
			AI->first = "Com";
			AI->next = "Per";
			//this->Board->printboard();
			//AI->AIGo();
		}
		else
		{
			//###################�Է�ִ��
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
		//ȷ�϶Է����Ӳ���¼playergo
		vector<int> numbers = ExtractNumInMassage(input);//###################����Ϣ�н������Է�����λ��
		int x = numbers[0]; int y = numbers[1];
		AI->PlayerGo(x, y);
		cout << "P1LuoZI OK";
		break;
	}
	case 6:
	{
		//�������ײ�ѯ��������
		AI->AIGo();
		//cout << "AILuoZI"<<" "<< pos.second<<" "<< pos.first;
		break;
	}
	case 7://BBP2Num
	{
		//��ȡn����Ŀ
		int num = GetBBP2LuoZINum();
		cout << "BBP2Num" << " " << num;
		break;
	}
	case 8://BBP2Pos
	{
		//��ȡn��λ��
		Point pos = GetBBP2LuoZI();
		cout << "BBP2Pos" << " " << pos.x << " " << pos.y;
		break;
	}
	case 9://BBP2Rec
	{
		//��ȡ���µĺ�������
		vector<int> numbers = ExtractNumInMassage(input);
		//����������꣬�������׺�����
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
		//ѡ�����µ�����
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
		//��ӡ��ǰ����
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
	//��ȡ��������
	//pair<int, int> pos ��ʽ���ܸĶ���AI->findBestChess(Board, Player2);��Ҫ�Ķ���
	Game a;
	Point pos = a.best();
	//������䲻�ܸĶ�
	Board[pos.y][pos.x] = Player2;

	//��Ҫ�Ķ���
	a.go(pos.y, pos.x, Player2);
	a.StateCheck(pos, black);
	BangP2ChessStep += 1;
	return pos;
}


//==================================================�������5��N��===================================================//

int TerminalMonitor::GetBBP2LuoZINum()
{
	int num = 2;
	//������n����Ŀ2-4��demo�й̶�����2
	BBP2NPNum = num;
	//������n������,�ŵ�һ�������У�����demo��ע��Ĳ���Ϊ  BBP2NPPos
	CreatBBP2Pos(BBP2NPNum);
	if (num > 1 && num < 5) return BBP2NPNum;
	return 2;
}

void TerminalMonitor::CreatBBP2Pos(int num)
{
	//������n������,�ŵ�һ�������У�����demo��ע��Ĳ���Ϊ  BBP2NPPos
	Point pt1(1,1), pt2(1,2);

	BBP2NPPos.push_back(pt1);

	BBP2NPPos.push_back(pt2);
}

Point TerminalMonitor::GetBBP2LuoZI()
{
	//����n�����꣬����һ����Ŀ��1��ֱ��0�������������ʽ�����ⲿ����Ҫ�޸�
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
	//�ں�̨�����ϼ�¼���µĺ��ӣ�gomoku::MAP_PLAYER_ONE���Ըĳ���ĺ��ӱ�־
	Board[y][x] = black;
	//֪ͨ�㷨�ļ������µĺ��ӣ�gomoku::MAP_PLAYER_ONE���Ըĳ���ĺ��ӱ�־
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
	//�׷�����ѡ��ĺ�������
	Point a;
	a.x = -1; a.y = -1;
	BangP2ChessStep += 1;
	if (BWP1NPPos.size() > 1) return BWP1NPPos[1];
	else return  a;
}

vector<int> TerminalMonitor::ExtractNumInMassage(const string& str)
{
	//���ַ����н������Է�����λ��
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
	//������ѭ�������������Ϣ������Ӧ�Զ�����Ϣ
	while (true)
	{
		std::string command;
		// �����ʾ��
		std::getline(std::cin, command);
		int i = PretreatMassage(command);// �ȴ��û���������
		HandleMassage(i, command);
		if (command == "Quit")
		{
			break; // ����û��������˳�����˳�ѭ��
		}
	}
}
