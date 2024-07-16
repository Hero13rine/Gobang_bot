#include"Game.h"

Point Game::minimax(vector<Point> PointList)
{
	Point BestMove(-1, -1);//��õ��з�
	int depth = 4;
	int BestValue = 999999999;
	//BestMove.x = -1;//��ʼ��Ϊ�Ƿ��ĵ�
	m_nodes = 0;//����
	vector<Point> BestPointList;
	for (vector<Point>::iterator it = PointList.begin(); it != PointList.end(); it++)
	{
		if (Board[(*it).x][(*it).y] == EMPTY)
		{
			//m_nodes++;
			Board[(*it).x][(*it).y] = m_personcolor;
			(*it).stateScore = maxSearch(BestValue, depth);
			BestPointList.push_back(*it);
			Board[(*it).x][(*it).y] = EMPTY;
		}
	}
	BestMove = getBestPointformList(BestPointList);
	return BestMove;
}

//minSearch�Ĺ����ǣ����˷��߳�һ��������ۼ�����ľ��档

int Game::minSearch(int LastBestValue, int depth)
{
	depth--;
	if (depth <= 0) return EvaluateALL();
	/*if (positionValue == 0) return 0;
	if (positionValue != 1) return positionValue;*/
	int BestValue = +99999999;
	vector<Point> PointList = GetBPointList(m_personcolor);
	for (vector<Point>::iterator it = PointList.begin(); it != PointList.end(); it++)
	{
		if (Board[(*it).x][(*it).y] == EMPTY)
		{
			Board[(*it).x][(*it).y] = m_personcolor;
			int value = maxSearch(BestValue, depth);
			if (value < BestValue)
				BestValue = value;
			Board[(*it).x][(*it).y] = EMPTY;
			if (BestValue < LastBestValue)
				return LastBestValue;
		}
	}

	return BestValue;
}

//maxSearch�Ĺ����ǣ�����������߳�һ��������ۼ�����Լ��ľ��档

int Game::maxSearch(int LastBestValue, int depth)
{
	depth--;
	if (depth <= 0) return EvaluateALL();
	//if (positionValue == 0) return 0;
	//if (positionValue != 1) return positionValue;
	int BestValue = -99999999;
	m_nodes++;

	vector<Point> PointList = GetBPointList(m_computercolor);
	for (vector<Point>::iterator it = PointList.begin(); it != PointList.end(); it++)
	{
		if (Board[(*it).x][(*it).y] == EMPTY)
		{
			Board[(*it).x][(*it).y] = m_computercolor;
			int value = minSearch(BestValue, depth);
			if (value > BestValue)
				BestValue = value;
			Board[(*it).x][(*it).y] = EMPTY;
			if (BestValue > LastBestValue)
				return LastBestValue;
		}
	}
	return BestValue;
}

vector<Point> Game::GetBPointList(int type)
{
	//��ʼ��
	HighPoint.clear();
	MidPoint.clear();
	LowPoint.clear();
	killPoint.clear();
	//��¼�߼����м����ͼ������
	const int max = 10;
	// ����Σ�յȼ� 0.��Σ�� 1.��Σ�� 2.��Σ��
	int dangerLevel = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (Board[i][j] == EMPTY)
			{

				Point np(i, j);
				np.color = type;
				int type1_state = StateCheck(np, type);
				state st_type1 = st1;
				if (type1_state == THREE_THREE_BAN ||
					type1_state == FOUR_FOUR_BAN ||
					type1_state == LONG_BAN && type == black)
				{
					continue;
				}
				// ��һ��ҲҪ��¼��ǰ����
				// Ŀǰ�ҵ��뷨�ǣ���ʱ��ȫ�ı���ȫ��ʹ�þ����ж�
				//  �˴���type��Ҫ�Ľ�
				int AIPoint = evaluateAIPoint(i, j);
				int PlayerPoint = evaluatePlayerPoint(i, j);
				np.allScore = AIPoint + PlayerPoint;
				if (type == m_computercolor)//����ǵ��Ե���ɫ,
				{
					np.score = AIPoint;
					//PosScore[i][j] = np.score;
				}
				else
				{
					np.score = PlayerPoint;
					//PosScore[i][j] = np.score;
				}
				//�ȷ��� �Լ�����(AI)
				if ((type1_state == BWIN && type == black) || (type1_state == WWIN && type == white))//���ȼ���ܷ�����
				{
					HighPoint.clear();
					HighPoint.push_back(np);
					return HighPoint;
				}
				if (dangerLevel == 2)
				{
					// ���ƺ�Σ�գ�ֻ����Լ�������������ӵ�
					continue;
				}
				//��ɱ��
				//if (score >= RiskScore.MEDIUM_RISK.score) {
					// ��ɱ��
				//killPointList.add(point);

				if (np.score >= 70000)
				{
					killPoint.push_back(np);
				}

				//checkSituation(point, ChessModel.CHONGSI, ChessModel.HUOSI)
				// 
				//�����player
				Point fnp(i, j);
				int type2_state = StateCheck(fnp, 3 - type);
				state st_type2 = st1;
				//�÷�
				fnp.allScore = PlayerPoint + AIPoint;
				if (type == m_computercolor)//����ǵ��Ե���ɫ,
				{
					fnp.score = PlayerPoint;
					//PosScore[i][j] = np.score;
				}
				else
				{
					fnp.score = AIPoint;
					//PosScore[i][j] = np.score;
				}
				int level = 0;
				if ((type2_state == BWIN && 3 - type == black) || (type2_state == WWIN && 3 - type == white))
				{
					// ���������ˣ����ƺ�Σ�գ���
					level = 2;
				}
				else if (fnp.score >= 70000)
				{
					// �����л��ġ�˫���ġ����Ļ���. ˫�����ĵ�λ�ˣ�������Σ�գ�(�з�������)
					level = 1;
				}
				if (level > 0) {
					// ��ǰ���ƴ���Σ��
					if (dangerLevel < level)
					{
						// Σ������
						dangerLevel = level;
						// ����Σ�յȼ���������������֮ǰѡ��ĸ����ȼ��ڵ㣬��ֹAI������;
						HighPoint.clear();
					}
					// ���˽ڵ���뵽�����ȼ�����
					HighPoint.push_back(np);
				}
			
				// �����ȼ����ӵ㣺��������迼�Ƕ���
				if ((np.score <= 70000 && np.score >= 20000) || (fnp.score <= 70000 && fnp.score >= 20000))
				{
					HighPoint.push_back(np);
					continue;
				}
				if (np.score >= 5000 || fnp.score >= 5000) {
					// ���ȼ����ӵ㣺���ġ��������迼�Ƕ���
					MidPoint.push_back(np);
					continue;
				}
				if (dangerLevel > 0)
				{
					// ������Σ�գ�����ļ���߼���������
					continue;
				}
				if (np.score >= 900 || fnp.score >= 900) {
					// �����ȼ����ӵ㣺���ġ��������迼�Ƕ���
					MidPoint.push_back(np);
					continue;
				}
				if (np.score >= 1)
				{
					// �����ӵ㣺�������һ���������߶�����һ�����ÿ��Ƕ���
					LowPoint.push_back(np);
				}
			}
		}
	}
	if (dangerLevel < 2 && !killPoint.empty())
	{
		// ���Ʋ����ر�Σ�գ���ɱ����в�Ϊ�գ�ֱ�ӽ����ͺ�
		return killPoint;
	}
	/*if (dangerLevel > 0)
	{
		sort(HighPoint.begin(), HighPoint.end(), cmpAllScore);
		return HighPoint;
	}*/
	vector<Point> returnPointList;
	//��returnPointList�б��������
	//�����еĵ����returnPointList����
	returnPointList.insert(returnPointList.end(), HighPoint.begin(), HighPoint.end());
	returnPointList.insert(returnPointList.end(), MidPoint.begin(), MidPoint.end());
	returnPointList.insert(returnPointList.end(), LowPoint.begin(), LowPoint.end());

	sort(returnPointList.begin(), returnPointList.end(), cmpAllScore);

	int sizemax = 10 < returnPointList.size() ? 10 : returnPointList.size();

	returnPointList.assign(returnPointList.begin(), returnPointList.begin() + sizemax);

	return returnPointList;
}

Point Game::deepeningMinimax(int depth, int maxDepth)
{
	Point best;
	for (; depth <= maxDepth; depth += 2) {
		int fscore = EvaluateALL();
		int score = minimax2(0, depth, -99999999, 99999999);
		best = BestPoint;

		if (abs(score) >= 99999998)
		{
			// �ҵ����Ž��ˣ���������
			break;
		}
	}

	return best;
}

int Game::minimax2(int type, int depth, int alpha, int beta)
{
	bool isboot = type == 0;
	
	if (isboot)
	{
		type = m_computercolor;
	}
	bool isAI = type == m_computercolor;

	if (depth == 0) {
		/**
		 * ����ÿ�ò�������Ҷ�ӽ��ľ���
		 * ���磺depth=2ʱ����ʾ��AI��ʼ��������֮��ľ���������AI(�ߵ�һ��) -> ���(�ߵڶ���)��Ȼ��Ծ��ƽ�������
		 * ע�⣺������������AI�ǶȽ��еģ���ֵԽ���AIԽ�����������Խ����
		 */
		return EvaluateALL();
	}
	if (1)
	{
		vector<Point> PointList = GetBPointList(type);
		vector<Point> bestPointList;
		for (vector<Point>::iterator it = PointList.begin(); it != PointList.end(); it++)
		{
			int score;
			int nx = (*it).x;
			int ny = (*it).y;
			if (StateCheck(*it, type) == BWIN || StateCheck(*it, type) == WWIN)
			{
				score = type == m_computercolor ? 99999998 : -99999998;
				depth = 1;
			}
			else
			{
				Board[nx][ny] = type;
				score = minimax2(3 - type, depth - 1, alpha, beta);
				(*it).stateScore = score;
				Board[nx][ny] = EMPTY;
			}
			if (isAI) {
				// AIҪѡ���Լ��������Ľڵ㣨����ߵģ�
				if (score >= alpha) {
					if (isboot) {
						if (score > alpha)
						{
							bestPointList.clear();
						}
						// ���ڵ㴦����AI��õ���λ
						bestPointList.push_back((*it));
					}
					// ���ֵ��ˢ�£�����alphaֵ
					alpha = score;
				}
			}
			else {
				// ����Ҫѡ��AI����Ľڵ㣨����͵ģ�
				if (score < beta) {
					// ���ֵ��ˢ�£�����betaֵ
					beta = score;
				}
			}

			if (alpha >= beta) {
				/*
				 AlphaBeta��֦

				 ���ͣ�
				 AI��ǰ������Ϊ��alpha �������� (alpha, +��]
				 ���ֵ�ǰ��С����Ϊ��beta �������� [-��, beta)

				 ��Ϊ����Ҫѡ�����С��beta�ķ�֧��AIҪ�Ӷ��ָ��ķ�֧����ѡ���ķ�֧��������ķ�֧Ҫ�͵�ǰ�ķ�֧(alpha)���Ƚϣ�
				 ����alpha����beta���ˣ��������������ķ�֧Ҳ����С��alpha�ģ�����������ȥû�����壬�����������Ч�ʡ�
				 */
				break;
			}
		}

		if (isboot)
		{
 			BestPoint = bestPointList.size() > 1 ? getBestPointformList(bestPointList) : *bestPointList.begin();
		}
		return isAI ? alpha : beta;
	}
}

int Game::minimax3(int type, int depth, int alpha, int beta, int n)

{
	bool isboot = type == 0;
	if (isboot)
	{
		type = m_computercolor;
	}
	bool isAI = type == m_computercolor;

	if (depth == 0) {
		/**
		 * ����ÿ�ò�������Ҷ�ӽ��ľ���
		 * ���磺depth=2ʱ����ʾ��AI��ʼ��������֮��ľ���������AI(�ߵ�һ��) -> ���(�ߵڶ���)��Ȼ��Ծ��ƽ�������
		 * ע�⣺������������AI�ǶȽ��еģ���ֵԽ���AIԽ�����������Խ����
		 */
		return EvaluateALL();
	}
	if (1)
	{
		vector<Point> PointList = GetBPointList(type);
		vector<Point> bestPointList;
		for (vector<Point>::iterator it = PointList.begin(); it != PointList.end(); it++)
		{
			int score;
			int nx = (*it).x;
			int ny = (*it).y;
			if (StateCheck(*it, type) == BWIN || StateCheck(*it, type) == WWIN)
			{
				score = type == m_computercolor ? 99999998 : -99999998;
				depth = 1;
			}
			else
			{
				Board[nx][ny] = type;
				score = minimax3(3 - type, depth - 1, alpha, beta, n);
				(*it).stateScore = score;
				(*it).score = evaluateAIPoint((*it).x, (*it).y);
				(*it).allScore = evaluateAIPoint((*it).x, (*it).y) + evaluatePlayerPoint((*it).x, (*it).y);
				Board[nx][ny] = EMPTY;
			}
			if (isAI) {
				// AIҪѡ���Լ��������Ľڵ㣨����ߵģ�
				if (score >= alpha) {
					if (isboot) {
						if (score > alpha)
						{
							bestPointList.clear();
						}
						// ���ڵ㴦����AI��õ���λ
						bestPointList.push_back((*it));
					}
					// ���ֵ��ˢ�£�����alphaֵ
					alpha = score;
				}
			}
			else {
				// ����Ҫѡ��AI����Ľڵ㣨����͵ģ�
				if (score < beta) {
					// ���ֵ��ˢ�£�����betaֵ
					beta = score;
				}
			}

			if (alpha >= beta) {
				/*
				 AlphaBeta��֦

				 ���ͣ�
				 AI��ǰ������Ϊ��alpha �������� (alpha, +��]
				 ���ֵ�ǰ��С����Ϊ��beta �������� [-��, beta)

				 ��Ϊ����Ҫѡ�����С��beta�ķ�֧��AIҪ�Ӷ��ָ��ķ�֧����ѡ���ķ�֧��������ķ�֧Ҫ�͵�ǰ�ķ�֧(alpha)���Ƚϣ�
				 ����alpha����beta���ˣ��������������ķ�֧Ҳ����С��alpha�ģ�����������ȥû�����壬�����������Ч�ʡ�
				 */
				break;
			}
		}

		if (isboot)
		{
			//sort(bestPointList.begin(), bestPointList.end(), cmpScore);
			//sort(bestPointList.begin(), bestPointList.end(), cmpAllScore);
			sort(bestPointList.begin(), bestPointList.end(), cmpStateScore);

			bestPointList.assign(bestPointList.begin(), bestPointList.begin() + n);

			FiveBestPointList = bestPointList;
		}
		return isAI ? alpha : beta;
	}
}