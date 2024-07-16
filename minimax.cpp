#include"Game.h"

Point Game::minimax(vector<Point> PointList)
{
	Point BestMove(-1, -1);//最好的招法
	int depth = 4;
	int BestValue = 999999999;
	//BestMove.x = -1;//初始化为非法的点
	m_nodes = 0;//调试
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

//minSearch的功能是：当人方走出一招棋后，评价计算机的局面。

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

//maxSearch的功能是：当计算机方走出一招棋后，评价计算机自己的局面。

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
	//初始化
	HighPoint.clear();
	MidPoint.clear();
	LowPoint.clear();
	killPoint.clear();
	//记录高级、中级、低级的落点
	const int max = 10;
	// 局势危险等级 0.不危险 1.有危险 2.很危险
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
				// 这一步也要记录当前分数
				// 目前我的想法是，暂时完全改编完全不使用局面判断
				//  此处的type需要改进
				int AIPoint = evaluateAIPoint(i, j);
				int PlayerPoint = evaluatePlayerPoint(i, j);
				np.allScore = AIPoint + PlayerPoint;
				if (type == m_computercolor)//如果是电脑的颜色,
				{
					np.score = AIPoint;
					//PosScore[i][j] = np.score;
				}
				else
				{
					np.score = PlayerPoint;
					//PosScore[i][j] = np.score;
				}
				//先分析 自己的棋(AI)
				if ((type1_state == BWIN && type == black) || (type1_state == WWIN && type == white))//优先检查能否连五
				{
					HighPoint.clear();
					HighPoint.push_back(np);
					return HighPoint;
				}
				if (dangerLevel == 2)
				{
					// 局势很危险，只检查自己可以连五的落子点
					continue;
				}
				//必杀棋
				//if (score >= RiskScore.MEDIUM_RISK.score) {
					// 必杀棋
				//killPointList.add(point);

				if (np.score >= 70000)
				{
					killPoint.push_back(np);
				}

				//checkSituation(point, ChessModel.CHONGSI, ChessModel.HUOSI)
				// 
				//后分析player
				Point fnp(i, j);
				int type2_state = StateCheck(fnp, 3 - type);
				state st_type2 = st1;
				//得分
				fnp.allScore = PlayerPoint + AIPoint;
				if (type == m_computercolor)//如果是电脑的颜色,
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
					// 对手连五了，局势很危险！！
					level = 2;
				}
				else if (fnp.score >= 70000)
				{
					// 对手有活四、双冲四、冲四活三. 双活三的点位了，局势有危险！(中风险以上)
					level = 1;
				}
				if (level > 0) {
					// 当前局势存在危险
					if (dangerLevel < level)
					{
						// 危险升级
						dangerLevel = level;
						// 局势危险等级如果上升，则清空之前选择的高优先级节点，防止AI误入歧途
						HighPoint.clear();
					}
					// 将此节点加入到高优先级队列
					HighPoint.push_back(np);
				}
			
				// 高优先级落子点：多活三，需考虑对手
				if ((np.score <= 70000 && np.score >= 20000) || (fnp.score <= 70000 && fnp.score >= 20000))
				{
					HighPoint.push_back(np);
					continue;
				}
				if (np.score >= 5000 || fnp.score >= 5000) {
					// 中先级落子点：冲四、活三，需考虑对手
					MidPoint.push_back(np);
					continue;
				}
				if (dangerLevel > 0)
				{
					// 局势有危险，下面的检查逻辑不用走了
					continue;
				}
				if (np.score >= 900 || fnp.score >= 900) {
					// 低优先级落子点：冲四、活三，需考虑对手
					MidPoint.push_back(np);
					continue;
				}
				if (np.score >= 1)
				{
					// 候补落子点：活二、活一、眠三、眠二、眠一，不用考虑对手
					LowPoint.push_back(np);
				}
			}
		}
	}
	if (dangerLevel < 2 && !killPoint.empty())
	{
		// 局势不是特别危险，且杀棋队列不为空，直接进攻就好
		return killPoint;
	}
	/*if (dangerLevel > 0)
	{
		sort(HighPoint.begin(), HighPoint.end(), cmpAllScore);
		return HighPoint;
	}*/
	vector<Point> returnPointList;
	//对returnPointList列表进行排序
	//将所有的点加入returnPointList容器
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
			// 找到最优解了，结束搜索
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
		 * 评估每棵博弈树的叶子结点的局势
		 * 比如：depth=2时，表示从AI开始走两步棋之后的局势评估，AI(走第一步) -> 玩家(走第二步)，然后对局势进行评估
		 * 注意：局势评估是以AI角度进行的，分值越大对AI越有利，对玩家越不利
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
				// AI要选对自己最有利的节点（分最高的）
				if (score >= alpha) {
					if (isboot) {
						if (score > alpha)
						{
							bestPointList.clear();
						}
						// 根节点处更新AI最好的棋位
						bestPointList.push_back((*it));
					}
					// 最高值被刷新，更新alpha值
					alpha = score;
				}
			}
			else {
				// 对手要选对AI最不利的节点（分最低的）
				if (score < beta) {
					// 最低值被刷新，更新beta值
					beta = score;
				}
			}

			if (alpha >= beta) {
				/*
				 AlphaBeta剪枝

				 解释：
				 AI当前最大分数为：alpha 搜索区间 (alpha, +∞]
				 对手当前最小分数为：beta 搜索区间 [-∞, beta)

				 因为对手要选择分数小于beta的分支，AI要从对手给的分支里面选最大的分支，这个最大的分支要和当前的分支(alpha)做比较，
				 现在alpha都比beta大了，下面搜索给出的分支也都是小于alpha的，所以搜索下去没有意义，剪掉提高搜索效率。
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
		 * 评估每棵博弈树的叶子结点的局势
		 * 比如：depth=2时，表示从AI开始走两步棋之后的局势评估，AI(走第一步) -> 玩家(走第二步)，然后对局势进行评估
		 * 注意：局势评估是以AI角度进行的，分值越大对AI越有利，对玩家越不利
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
				// AI要选对自己最有利的节点（分最高的）
				if (score >= alpha) {
					if (isboot) {
						if (score > alpha)
						{
							bestPointList.clear();
						}
						// 根节点处更新AI最好的棋位
						bestPointList.push_back((*it));
					}
					// 最高值被刷新，更新alpha值
					alpha = score;
				}
			}
			else {
				// 对手要选对AI最不利的节点（分最低的）
				if (score < beta) {
					// 最低值被刷新，更新beta值
					beta = score;
				}
			}

			if (alpha >= beta) {
				/*
				 AlphaBeta剪枝

				 解释：
				 AI当前最大分数为：alpha 搜索区间 (alpha, +∞]
				 对手当前最小分数为：beta 搜索区间 [-∞, beta)

				 因为对手要选择分数小于beta的分支，AI要从对手给的分支里面选最大的分支，这个最大的分支要和当前的分支(alpha)做比较，
				 现在alpha都比beta大了，下面搜索给出的分支也都是小于alpha的，所以搜索下去没有意义，剪掉提高搜索效率。
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