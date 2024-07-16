#include "TerminalMonitor.h"
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
		AI->PlayerGo( x,y);
		cout << "P1LuoZI OK" ;
		break;
	}
	case 6: 
	{	
		//�������ײ�ѯ��������
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

