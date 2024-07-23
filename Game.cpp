#include"Game.h"

bool cmpAllScore(const Point a, const Point b)
{
	return a.allScore > b.allScore;
}

bool cmpScore(const Point a, const Point b)
{
	return a.score > b.score;
}

bool cmpStateScore(const Point a, const Point b)
{
	return a.stateScore > b.stateScore;
}

Game::Game()
{
}

vector<Point> Game::randomPoint(int type, int num)
{
	vector<Point> pointList;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (Board[i][j] == EMPTY) {
				Point P(i, j);
				pointList.push_back(P);
			}
		}
	}
	srand(time(NULL));
	random_shuffle(pointList.begin(), pointList.end());
	int sizemax = 10 > pointList.size() ? 10 : pointList.size();
	pointList.assign(pointList.begin(), pointList.begin() + sizemax);
	return pointList;
}

bool Game::checkHighPriorityPoint(state st)
{
	if (st.four1count > 0)
	{
		return true;
	}
	else if (st.four2count > 1)//双四
	{
		return true;
	}
	else if (st.four2count > 0 && st.three1count + st.three12count > 0) //四三
	{
		return true;
	}
	else if (st.three1count + st.three12count > 1)
	{
		return true;
	}
	else if (st.three1count > 0 && st.two1count > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

Point Game::best()
{
	Point b(-1, -1);
	// 初始分值为最小
	int score = -99999999;
	/* 遍历所有能下棋的点位，评估各个点位的分值，选择分值最大的点位 */
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15.; j++) {
			if (Board[i][j] != 0) {
				// 该点已有棋子，跳过
				continue;
			}
			Board[i][j] = m_computercolor;
			// 该点得分 = AI落子得分 + 对手落子得分
			int val = evaluateAIPoint(i, j) + evaluatePlayerPoint(i, j);
			Board[i][j] = EMPTY;
			// 选择得分最高的点位
			if (val > score) {
				// 最高分被刷新
				score = val;
				// 更新最佳点位
				b.x = i;
				b.y = j;
			}
		}
	}

	return b;
}

Point Game::getBestPointformList(vector<Point> PointList)
{
	Point BP;
	int bestScore = -99999999;
	for (vector<Point>::iterator it = PointList.begin(); it != PointList.end(); it++)
	{
		Point p = (*it);
		int score = (*it).stateScore;
		if (score > bestScore)
		{
			bestScore = score;
			BP = p;
		}
	}
	return BP;
}

void Game::go(int nx, int ny, int color) //仅仅是落子，不负责判断棋盘，判断棋盘在AIgo 和 Player go 里
{;
	Board[nx][ny] = color;
	if (nx > mx)//确定棋盘有效最大范围
		mx = nx;
	if (ny > my)
		my = ny;
	if (nx < minx)
		minx = nx;
	if (ny < miny)
		miny = ny;
	//printboard();
	Point np(nx, ny);
	np.color = color;
	manual.push_back(np);
	if (Game::StateCheck(np, Board[nx][ny]) == THREE_THREE_BAN ||
		Game::StateCheck(np, Board[nx][ny]) == FOUR_FOUR_BAN ||
		Game::StateCheck(np, Board[nx][ny]) == LONG_BAN)
	{
		cout << "--------禁手点！！----------" << endl;
		cout << "--------------禁手点--------------" << endl;
		winner = 2;
		SaveChessboard();
		system("pause");
		//exit(0);
	}
	if (Game::StateCheck(np, Board[nx][ny]) == BWIN)
	{
		cout << "--------------黑棋胜利-----------------" << endl;
		winner = m_computercolor == black ? 1 : 2;
		SaveChessboard();
		system("pause");
		//exit(0);
	}
	else if (Game::StateCheck(np, Board[nx][ny]) == WWIN)
	{
		cout << "--------------白棋胜利-----------------" << endl;
		winner = 2;
		SaveChessboard();
		system("pause");
		//exit(0);
	}
}

void Game::PlayerGo(int nx, int ny)
{
	int row = nx, col = ny;
	//if (this->step == 4)
	//{
	//	Point np = FiveSteps(setFiveStepsWay(N5));
	//	go(np.x, np.y, m_personcolor);
	//	LastPlayerStep.x = row;
	//	LastPlayerStep.y = col;
	//	//AIGo();
	//}
	/*else
	{*/
		if (CanPut(row, col))
		{
			go(row, col, m_personcolor);
			//AIGo();
		}
		//else
		//{
		//	return PlayerGo();
		//}
	//}
	//else if (m2.message == WM_LBUTTONDOWN && m2.x >= 500 && m2.x <= 550 && m2.y >= 80 && m2.y <= 130)//悔棋
	//{
	//	Board[LastPlayerStep.x][LastPlayerStep.y] = EMPTY;
	//	Board[LastComStep.x][LastComStep.y] = EMPTY;
	//	clearcircle((LastPlayerStep.y + 1) * 30, (LastPlayerStep.x + 1) * 30, 13);
	//	clearcircle((LastComStep.y + 1) * 30, (LastComStep.x + 1) * 30, 13);
	//	line((LastPlayerStep.y + 1) * 30 - 13, (LastPlayerStep.x + 1) * 30, (LastPlayerStep.y + 1) * 30 + 13, (LastPlayerStep.x + 1) * 30);//将去除的横线补上
	//	line((LastPlayerStep.y + 1) * 30 , (LastPlayerStep.x + 1) * 30 - 13, (LastPlayerStep.y + 1) * 30 , (LastPlayerStep.x + 1) * 30 + 13);//将去除的竖线补上
	//	line((LastComStep.y + 1) * 30 - 13, (LastComStep.x + 1) * 30, (LastComStep.y + 1) * 30 + 13, (LastComStep.x + 1) * 30);//将去除的横线补上
	//	line((LastComStep.y + 1) * 30, (LastComStep.x + 1) * 30 - 13, (LastComStep.y + 1) * 30, (LastComStep.x + 1) * 30 + 13);//将去除的竖线补上
	//	step -= 2;
	//	manual.pop_back();
	//	manual.pop_back();
	//	return PlayerGo();
	//}
	////打谱
	//else if (m2.message == WM_LBUTTONDOWN && m2.x >= 560 && m2.x <= 610 && m2.y >= 20 && m2.y <= 70)
	//{

	//	SaveChessboard();
	//}
	////pass
	//else if (m2.message == WM_LBUTTONDOWN && m2.x >= 560 && m2.x <= 610 && m2.y >= 80 && m2.y <= 130)
	//{
	//	 AIGo();
	//}

}

void Game::AIGo()
{
	BestPoint.x = 0;
	BestPoint.y = 0;
	Point np;
	clock_t begin, end;
	begin = clock();//计时起点
	/*if (step == 3 && isThreeSteps)
	{
		ThreeSteps();
	}*/
	if (step < 9 && step != 4)
	{
		Point vcfPoint = deepening(14, 14, 1);//vcf
		Point vctPoint = deepening(10, 10, 0);//vct
		if (vctPoint.x == -1)
		{
			if (vcfPoint.x == -1)
			{
				deepeningMinimax(5, 5);
				np = BestPoint;
			}
			else
			{
				np = vcfPoint;
			}
		}
		else
		{
			np = vctPoint;
		}
	}
	/*else if (step == 4 && isFiveSteps)
	{
		FiveSteps(setFiveStepsWay(N5));
	}*/
	else if(step <= 150)
	{

		Point vcfPoint = deepening(15, 15, 1);//vcf
		Point vctPoint = deepening(10, 10, 0);//vct
		if (vcfPoint.x == -1)
		{
			if (vctPoint.x == -1)
			{
				deepeningMinimax(MAXDepth, MAXDepth);
				np = BestPoint;
			}
			else
			{
				//settextcolor(RED);
				//outtextxy(180, 550, "算杀命中!");
				np = vctPoint;
			}
		}
		else
		{
			//settextcolor(RED);
			//outtextxy(180, 550, "算杀命中!");
			np = vcfPoint;
		}
	}
	else if(step <= 200)
	{
		Point vcfPoint = deepening(10, 10, 1);//vcf
		Point vctPoint = deepening(5, 5, 0);//vct
		if (vcfPoint.x == -1)
		{
			if (vctPoint.x == -1)
			{
				deepeningMinimax(DEPTH2, DEPTH2);
				np = BestPoint;
			}
			else
			{
				//settextcolor(RED);
				//outtextxy(180, 550, "算杀命中!");
				np = vctPoint;
			}
		}
		else
		{
			//settextcolor(RED);
			//outtextxy(180, 550, "算杀命中!");
			np = vcfPoint;
		}
	}
	else
	{
		Point vcfPoint = deepening(5, 5, 1);//vcf
		Point vctPoint = deepening(5, 5, 0);//vct
		if (vcfPoint.x == -1)
		{
			if (vctPoint.x == -1)
			{
				deepeningMinimax(DEPTH1, DEPTH1);
				np = BestPoint;
			}
			else
			{
				//settextcolor(RED);
				//outtextxy(180, 550, "算杀命中!");
				np = vctPoint;
			}
		}
		else
		{
			//settextcolor(RED);
			//outtextxy(180, 550, "算杀命中!");
			np = vcfPoint;
		}
	}
	//Point np = minimax();
	end = clock();//计时终点
	//CalculateTime(begin, end);
	LastComStep.x = np.x;
	LastComStep.y = np.y;
	/*clearrectangle(460, 250, 620, 300);
	outtextxy(460, 250, "智障落子坐标");
	char xy[20];
	sprintf(xy, "【%c,%d】", np.y + 65, 15 - np.x);
	outtextxy(560, 250, xy);
	DrawPiece(m_computercolor, (np.y + 1) * 30, (np.x + 1) * 30);*/
	std::cout << "AILuoZI" << " " << np.x << " " << np.y;
	go(np.x, np.y, m_computercolor);
	//PlayerGo();
}

//Point Game::FiveSteps(int n) //五手n打
//{
//	if (m_computercolor == black)//如果电脑执黑，则输出n个点交给对手判断
//	{
//		clock_t begin, end;
//		begin = clock();//计时起点
//		Point BestMove(-1, -1);//最好的招法
//		int depth = DEPTH1;
//		int BestValue = -99999999;
//		//BestMove.x = -1;//初始化为非法的点
//		vector<Point> Nlist;
//		//瑞星五手n打
//		if (Board[7][7] == black && Board[6][7] == white && Board[9][7] == black && N5 == 2)
//		{
//			if (Board[5][8] == white)
//			{
//				Point p1(8, 8);
//				Nlist.push_back(p1);
//				Point p2(9, 8);
//				Nlist.push_back(p2);
//			}
//			else if (Board[5][6] == white)
//			{
//				Point p1(8, 6);
//				Nlist.push_back(p1);
//				Point p2(9, 6);
//				Nlist.push_back(p2);
//			}
//			else if (Board[6][8] == white)
//			{
//				Point p1(8, 8);
//				Nlist.push_back(p1);
//				Point p2(6, 6);
//				Nlist.push_back(p2);
//			}
//			else if (Board[6][6] == white)
//			{
//				Point p1(6, 8);
//				Nlist.push_back(p1);
//				Point p2(8, 6);
//				Nlist.push_back(p2);
//			}
//			else if (Board[7][8] == white)
//			{
//				Point p1(8, 8);
//				Nlist.push_back(p1);
//				Point p2(8, 9);
//				Nlist.push_back(p2);
//			}
//			else if (Board[7][6] == white)
//			{
//				Point p1(8, 6);
//				Nlist.push_back(p1);
//				Point p2(8, 5);
//				Nlist.push_back(p2);
//			}
//			else if (Board[8][8] == white)
//			{
//				Point p1(8, 6);
//				Nlist.push_back(p1);
//				Point p2(10, 7);
//				Nlist.push_back(p2);
//			}
//			else if (Board[8][6] == white)
//			{
//				Point p1(8, 8);
//				Nlist.push_back(p1);
//				Point p2(10, 7);
//				Nlist.push_back(p2);
//			}
//			else
//			{
//				for (int i = 5; i < 10; i++)
//				{
//					for (int j = 5; j < 10; j++)
//					{
//						if (Board[i][j] == EMPTY)
//						{
//							m_nodes++;
//							Board[i][j] = m_computercolor;
//							Point ap(i, j);
//							int value = minSearch(BestValue, depth);
//							ap.stateScore = value;
//							Nlist.push_back(ap);
//							Board[i][j] = EMPTY;
//						}
//					}
//				}
//				sort(Nlist.begin(), Nlist.end(), cmpStateScore);
//				Nlist.assign(Nlist.begin(), Nlist.begin() + n);
//			}
//		}
//		else
//		{
//			for (int i = 5; i < 10; i++)
//			{
//				for (int j = 5; j < 10; j++)
//				{
//					if (Board[i][j] == EMPTY)
//					{
//						m_nodes++;
//						Board[i][j] = m_computercolor;
//						Point ap(i, j);
//						int value = minSearch(BestValue, depth);
//						ap.stateScore = value;
//						Nlist.push_back(ap);
//						Board[i][j] = EMPTY;
//					}
//				}
//			}
//			sort(Nlist.begin(), Nlist.end(), cmpStateScore);
//			Nlist.assign(Nlist.begin(), Nlist.begin() + n);
//		}
//		
//
//		/*minimax3(0, 6, -99999999, 99999999, n);
//
//		Nlist = FiveBestPointList;*/
//		//输出n个点,让玩家选择
//		for (vector<Point>::iterator it = Nlist.begin(); it != Nlist.end(); it++)
//		{
//			setfillcolor(BLACK);
//			solidcircle(((*it).y + 1) * 30, ((*it).x + 1) * 30, 13);//下棋
//		}
//		end = clock();//计时终点
//		CalculateTime(begin, end);
//		int fx, fy;
//		HWND hWnd = GetHWnd();
//		outtextxy(460, 250, "请选择您要下的棋");
//		ExMessage m2;//鼠标(新版)
//		while (1)
//		{
//		here:
//			m2 = getmessage(EM_MOUSE);//检测鼠标信息
//			if (m2.message == WM_LBUTTONDOWN && m2.x <= 450 && m2.y <= 450)//左键
//			{
//				IdentifyPoint(m2.x, m2.y);
//				fy = xx / 30 - 1;
//				fx = yy / 30 - 1;
//				//合法判断
//				int flag = 0;
//				for (vector<Point>::iterator it = Nlist.begin(); it != Nlist.end(); it++)
//				{
//					if ((*it).x == fx && (*it).y == fy)
//					{
//						flag = 1;
//						break;
//					}
//				}
//				if (flag == 0)
//				{
//					HWND hWnd = GetHWnd();
//					MessageBox(hWnd, "该点不可下", "警告", MB_OK);//设置模态对话框
//					goto here;
//				}
//				DrawPiece(black, xx, yy);
//				for (vector<Point>::iterator it = Nlist.begin(); it != Nlist.end(); it++)
//				{
//					if ((*it).x == fx && (*it).y == fy)
//					{
//						continue;
//					}
//					clearcircle(((*it).y + 1) * 30, ((*it).x + 1) * 30, 13);
//					line(((*it).y + 1) * 30 - 13, ((*it).x + 1) * 30, ((*it).y + 1) * 30 + 13, ((*it).x + 1) * 30);//将去除的横线补上
//					line(((*it).y + 1) * 30, ((*it).x + 1) * 30 - 13, ((*it).y + 1) * 30, ((*it).x + 1) * 30 + 13);//将去除的竖线补上
//				}
//				break;
//			}
//		}
//		clearrectangle(460, 250, 600, 350);
//		go(fx, fy, black);
//		LastComStep.x = fx;
//		LastComStep.y = fy;
//		PlayerGo();
//	}
//	else//如果电脑执白，则输入n个点交给电脑判断
//	{
//		vector<Point> pointList;
//		HWND hWnd = GetHWnd();
//		outtextxy(460, 280, "请进行打点");
//		for (int i = 0; i < n; i++)
//		{
//			int row = 0, col = 0;
//			ExMessage m2;//鼠标
//			while (1)
//			{
//				m2 = getmessage(EM_MOUSE);//检测鼠标信息
//				if (m2.message == WM_LBUTTONDOWN && m2.x <= 450 && m2.y <= 450)//左键
//				{
//					IdentifyPoint(m2.x, m2.y);
//					col = xx / 30 - 1;
//					row = yy / 30 - 1;
//					setfillcolor(BLACK);
//					solidcircle(xx, yy, 13);//下棋
//					break;
//				}
//			}
//			Point np(row, col);
//			pointList.push_back(np);
//		}
//		clearrectangle(460, 220, 700, 320);
//		// 进入minimax;
//		Point p = minimax(pointList);
//		for (int i = 0; i < n; i++)
//		{
//			if (p.x == pointList[i].x && p.y == pointList[i].y)
//			{
//				continue;
//			}
//			clearcircle((pointList[i].y + 1) * 30, (pointList[i].x + 1) * 30, 13);
//			line((pointList[i].y + 1) * 30 - 13, (pointList[i].x + 1) * 30, (pointList[i].y + 1) * 30 + 13, (pointList[i].x + 1) * 30);//将去除的横线补上
//			line((pointList[i].y + 1) * 30, (pointList[i].x + 1) * 30 - 13, (pointList[i].y + 1) * 30, (pointList[i].x + 1) * 30 + 13);//将去除的竖线补上
//		}
//		return p;
//	}
//
//}

bool Game::exchange() {
	int i, j, x1, y1, x2, y2, x3, y3;
	int ret = 0;
	//找到开局落的三个子
	for (i = 0; i < 15; i++)
	{
		for (j = 0; j < 15; j++)
		{
			if (Board[i][j] == black && i == 7 && j == 7)
			{
				x1 = i; y1 = j;

			}
			if (Board[i][j] == black && (i != 7 || j != 7))
			{
				x3 = i; y3 = j;
			}
			if (Board[i][j] == white)
			{
				x2 = i; y2 = j;
			}
		}
	}
	if (isShuxing(x1, y1, x2, y2, x3, y3) && N5 == 2)
	{
		return 0;
	}
	 if ((isHuayue(x1, y1, x2, y2, x3, y3) ||
		isPuyue(x1, y1, x2, y2, x3, y3) ||
		isYunyue(x1, y1, x2, y2, x3, y3) ||
		isYuyue(x1, y1, x2, y2, x3, y3) ||
		isXiyue(x1, y1, x2, y2, x3, y3) ||
		isXiayue(x1, y1, x2, y2, x3, y3) ||
		isShuiyue(x1, y1, x2, y2, x3, y3) ||
		isLanyue(x1, y1, x2, y2, x3, y3) ||
		isJinxing(x1, y1, x2, y2, x3, y3) ||
		isHengxing(x1, y1, x2, y2, x3, y3) ||
		isHanxing(x1, y1, x2, y2, x3, y3) ||
		isMingxing(x1, y1, x2, y2, x3, y3)) && N5 <= 4)
	{
		//换手
		return 1;
	}
	else if ((isXieyue(x1, y1, x2, y2, x3, y3) ||
		isQiuyue(x1, y1, x2, y2, x3, y3) ||
		isSongyue(x1, y1, x2, y2, x3, y3) ||
		isMingyue(x1, y1, x2, y2, x3, y3) ||
		isYinyue(x1, y1, x2, y2, x3, y3) ||
		isCanyue(x1, y1, x2, y2, x3, y3) ||
		isXinyue(x1, y1, x2, y2, x3, y3) ||
		isShanyue(x1, y1, x2, y2, x3, y3)) && N5 <= 3)
	{
		//换手
		return 1;
	}
	else if ((isYouxing(x1, y1, x2, y2, x3, y3) ||
		isHuixing(x1, y1, x2, y2, x3, y3)) && N5 == 1)
	{
		//换手
		return 1;
	}
	else if ((isLiuxing(x1, y1, x2, y2, x3, y3) ||
		isChangxing(x1, y1, x2, y2, x3, y3)) && N5 == 1)
	{
		//换手
		return 1;
	}
	else if ((isRuixing(x1, y1, x2, y2, x3, y3) ||
		isShuxing(x1, y1, x2, y2, x3, y3)) && N5 <= 2)
	{
		//换手
		return 1;
	}
	else {
		//不换手
		return 0;
	}

}

//void Game::ThreeSteps() // 三步换手
//{
//	if (m_computercolor == black)
//	{
//		//让白方选择是否换手
//		HWND hWnd = GetHWnd();//获取窗口句柄
//		int ok = MessageBox(hWnd, "您要选择换手吗？", "提示", MB_YESNO);//设置模态对话框
//		switch (ok)
//		{
//		case IDYES:
//			m_computercolor = white;
//			m_personcolor = black;
//			isThreeSteps = false;
//			AIGo();
//
//		case IDNO:
//			isThreeSteps = false;
//			PlayerGo();
//		}
//	}
//	else
//	{
//		//AI 判断是否换手
//		bool ex = exchange();
//		if (ex)//根据26种开局确定是否换手
//		{
//			settextcolor(BLACK);
//			outtextxy(460, 220, "电脑选择换手");
//			m_computercolor = black;
//			m_personcolor = white;
//			isThreeSteps = false;
//			PlayerGo();
//		}
//		else
//		{
//			BestPoint.x = 0;
//			BestPoint.y = 0;
//			Point np;
//			minimax2(0, DEPTH2, -99999999, 99999999);
//			np = BestPoint;
//			LastComStep.x = np.x;
//			LastComStep.y = np.y;
//			DrawPiece(m_computercolor, (np.y + 1) * 30, (np.x + 1) * 30);
//			go(np.x, np.y, m_computercolor);
//			outtextxy(460, 220, "电脑选择不换手");
//			PlayerGo();
//		}
//
//	}
//}

void Game::SaveChessboard()
{
    char first1[10];
	//string first = wideCharToMultiByte(first1);
	char second2[10];
	//InputBox(second2, 10, "请输入后手");
	//string second = wideCharToMultiByte(second2);
	//获取时间------------------------------------------
	time_t rawtime;
	struct tm* ptminfo;
	time(&rawtime);
	ptminfo = localtime(&rawtime);
	//---------------------------------------------------
	string whowin;
	if (winner == 1)
	{
		whowin = "先手胜";
	}
	else if (winner == 2)
	{
		whowin = "后手胜";
	}
	else
	{
		whowin = " ";
	}
	// 以写模式打开文件
	ofstream outfile;
	outfile.open("./file.txt", ios::out);
	outfile << "{[C5][" << first1 << "][" << second2 << "][" << whowin << "][" 
		<< ptminfo->tm_year + 1900 << "-" << ptminfo->tm_mon + 1 << "-" << ptminfo->tm_mday
		<< " " << ptminfo->tm_hour << ":" << ptminfo->tm_min << "][]";
	for (Point np : manual)
	{
		//转换过程
		char c;
		c = np.y + 'A';
		
		if (np.color == black)
		{
			outfile << ";B(" << c << "," << 15 - np.x << ")";
		}
		else
		{
			outfile << ";W(" << c << "," << 15 - np.x << ")";
		}
		
		
	}
	outfile << "}";
	// 关闭打开的文件
	outfile.close();

	//HWND hWnd = GetHWnd();
	//MessageBox(hWnd, "打谱成功", "提示", MB_OK);//设置模态对话框

}