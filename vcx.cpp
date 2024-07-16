#include"Game.h"

//第一代vcx----------------------------------------

vector<Point> Game::getVcxPoints(int type, bool isVcf)
{
	bool isAI = type == m_computercolor;
	// 进攻点列表
	vector<Point> attackPointList;
	// 防守点列表
	vector<Point> defensePointList;
	// VCX列表
	vector<Point> vcxPointList;

	bool isDanger = false;
	bool isLDanger = false;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if(Board[i][j] != 0) {
				// 该处已有棋子，跳过
				continue;
			}
			// 考虑自己的落子情况
			Point np(i, j);
			np.color = type;
			int type1_state = StateCheck(np, type);
			state st_type1 = st1;
			if (/*type == black &&*/
				(type1_state == THREE_THREE_BAN ||
					type1_state == FOUR_FOUR_BAN ||
					type1_state == LONG_BAN))
			{
				continue;
			}
			if (type == m_computercolor)//如果是电脑的颜色,
			{
				np.score = evaluateAIPoint(i, j);
				//PosScore[i][j] = np.score;
			}
			else
			{
				np.score = evaluatePlayerPoint(i, j);
				//PosScore[i][j] = np.score;
			}
			np.allScore = evaluatePlayerPoint(i, j) + evaluateAIPoint(i, j);
			if ((type1_state == BWIN && type == black) || (type1_state == WWIN && type == white)) {
				// 自己可以连五，直接返回
				//attackPointList.clear();
				attackPointList.push_back(np);
				return attackPointList;
			}
			
			if (isDanger) {
				// 存在危险，继续找自己可以连五的棋子
				continue;
			}

			// 考虑对手的落子情况
			Point fnp(i, j);
			fnp.color = 3 - type;
			int type2_state = StateCheck(np, 3 - type);
			state st_type2 = st1;
			if (3 - type == m_computercolor)//如果s的颜色,
			{
				fnp.score = evaluateAIPoint(i, j);
				//PosScore[i][j] = np.score;
			}
			else
			{
				fnp.score = evaluatePlayerPoint(i, j);
				//PosScore[i][j] = np.score;
			}
			fnp.allScore = evaluateAIPoint(i, j) + evaluatePlayerPoint(i, j);
			if ((type2_state == BWIN && 3 - type == black) || (type2_state == WWIN && 3 - type == white)) {
				// 对手连五了，局势很危险！！赶紧找自己可以连五的点位，不行就防守
				isDanger = true;
				defensePointList.clear();
				defensePointList.push_back(fnp);
				continue;
			}
			// 看看自己有没有大于等于中风险分值的点位
			if (np.score >= 500000) {
				attackPointList.push_back(np);
				continue;
			}

			if (fnp.score >= 500000)
			{
				isLDanger = true;
				//defensePointList.clear();
				defensePointList.push_back(fnp);
				continue;
			}


			if (isAI) {
				// AI才进行VCX
				if (st_type1.four2count > 0) {
					// 不论是VCF还是VCT，AI都可先选择冲四
					vcxPointList.push_back(np);
				}
				else if (!isVcf && (st_type1.three12count > 0 || st_type1.three1count > 0))
				{
					// 记录VCT点位
					vcxPointList.push_back(np);
				}
			}
			else {
				// 对手需防守VCT
				if (!isVcf) {
					if (st_type1.four2count > 0 || fnp.score >= 100000)
					{
						// 选择冲四或防守对方的活四
						defensePointList.push_back(np);
					}
				}
			}
		}
	}
	// 按分数从大到小排序
	sort(attackPointList.begin(), attackPointList.end(), cmpAllScore);
	sort(defensePointList.begin(), defensePointList.end(), cmpAllScore);
	vector<Point> pointList;
	// 如果对面没有成五棋形
	if (!isDanger) {
		// 优先强进攻
		// 如果没有风险且为vcf优先进攻
		if (isVcf)
		{	
			if (!attackPointList.empty())
			{
				if (isAI) {
					// AI有强进攻点位了，就不用考虑后面的点位了
					return attackPointList;
				}
				// 对手可以选择进攻和防守
				//pointList.addAll(attackPointList);
				for (vector<Point>::iterator it = attackPointList.begin(); it != attackPointList.end(); it++)
				{
					pointList.push_back(*it);//将!ai的进攻点放入搜索列表
				}
			}
		}
		//如果是vct 并且对面没有必胜棋形
		else if (!isVcf && !isLDanger)
		{
			if (!attackPointList.empty())
			{
				if (isAI) {
					// AI有强进攻点位了，就不用考虑后面的点位了
					return attackPointList;
				}
				// 对手可以选择进攻和防守
				//pointList.addAll(attackPointList);
				for (vector<Point>::iterator it = attackPointList.begin(); it != attackPointList.end(); it++)
				{
					pointList.push_back(*it);
				}
			}
		}
		// 如果是vct 并且对手有强进攻点
		// 选择防守
		else if (!isVcf && isLDanger)
		{
			//对双三等高危险级的防守点位进行防守
			if (!defensePointList.empty()) {
				// 进行防守
				if (isAI) {
					// AI优先选择进攻，把防守点位放后面
					//pointList.addAll(defensePointList);
					for (vector<Point>::iterator it = defensePointList.begin(); it != defensePointList.end(); it++)
					{
						pointList.push_back(*it);
					}
				}
				else {
					// 对手优先考虑防守，把防守点位放前面
					//pointList.addAll(0, defensePointList);
					for (vector<Point>::iterator it = defensePointList.begin(); it != defensePointList.end(); it++)
					{
						pointList.insert(pointList.begin(), (*it));
					}
				}
			}
		}


		// VCX进攻
		if (!vcxPointList.empty()) {
			//pointList.addAll(vcxPointList);
			for (vector<Point>::iterator it = vcxPointList.begin(); it != vcxPointList.end(); it++)
			{
				pointList.push_back(*it);
			}
		}
	}

	if (!defensePointList.empty()) {
		// 进行防守
		if (isAI) {
			// AI优先选择进攻，把防守点位放后面
			//pointList.addAll(defensePointList);
			for (vector<Point>::iterator it = defensePointList.begin(); it != defensePointList.end(); it++)
			{
				pointList.push_back(*it);
			}
		}
		else {
			// 对手优先考虑防守，把防守点位放前面
			//pointList.addAll(0, defensePointList);
			for (vector<Point>::iterator it = defensePointList.begin(); it != defensePointList.end(); it++)
			{
				pointList.insert(pointList.begin(), (*it));
			}
		}
	}

	return pointList;
}

/**
  * 算杀（VCF、VCT）
  *
  * @param type  当前走棋方 0.根节点表示AI走棋 1.AI 2.玩家
  * @param depth 搜索深度
  * @param isVcf true:VCF false:VCT
  * @return
  */
Point Game::vcx(int type, int depth, bool isVcf)
{
	Point pp(-1, -1);
	if (depth == 0) {
		// 算杀失败

		return pp;
	}

	bool isRoot = type == 0;
	if (isRoot) {
		type = m_computercolor;
	}
	bool isAI = type == m_computercolor;

	Point best;
	vector<Point> pointList = isVcf ? getVcfPoints(type) : getVctPoints(type);
	/*if (isRoot) {
		sort(pointList.begin(), pointList.end(), cmpScore);
	}*/
	for (Point point : pointList) {
		if (point.score >= 700000) {
			// 已经可以形成必胜棋型了，如果是AI落子，就返回当前节点，否则返回空
			return isAI ? point : pp;	
		}

		Board[point.x][point.y] = type;
		best = vcx(3 - type, depth - 1, isVcf);
		Board[point.x][point.y] = EMPTY;

		if (best.x == pp.x) {
			if (isAI) {
				// AI还没找到可以算杀成功的棋子，继续找...
				continue;
			}

			// 对手拦截成功了，直接返回空出去，表示算杀失败了
			return pp;
		}

		// 记录当前节点
		best = point;

		if (isAI) {
			// AI已经找到可以算杀的棋子了，同层后续的节点都不用看了
			break;
		}
	}

	return best;
}

Point Game::deepening(int depth, int maxDepth, bool isVcf) {
	Point point;
	Point pp;
	for (; depth <= maxDepth; depth += 2) {
		point = vcx(0, depth, isVcf);
		if (point.x != pp.x) {
			
			break;
		}
	}

	return point;
}

//================================================================
vector<Point> Game::getVcfPoints(int type)
{
	bool isAI = type == m_computercolor;
	// 进攻点列表, 只包含成五的点
	vector<Point> attackPointList;
	// 防守点列表 包含对手必胜的点
	vector<Point> defensePointList;
	// VCF列表 
	vector<Point> vcfPointList;
	bool isDanger = false;
	bool isLDanger = false;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (Board[i][j] != 0) {
				// 该处已有棋子，跳过
				continue;
			}
			Point np(i, j);//这是当前棋子
			np.color = type;
			int type1_state = StateCheck(np, type);
			state st_type1 = st1;
			if (type == black &&//禁手点直接跳过
				(type1_state == THREE_THREE_BAN ||
					type1_state == FOUR_FOUR_BAN ||
					type1_state == LONG_BAN))
			{
				continue;
			}
			if (type == m_computercolor)//如果是电脑的颜色,
			{
				np.score = evaluateAIPoint(i, j);
				//PosScore[i][j] = np.score;
			}
			else
			{
				np.score = evaluatePlayerPoint(i, j);
				//PosScore[i][j] = np.score;
			}
			np.allScore = evaluatePlayerPoint(i, j) + evaluateAIPoint(i, j);
			if ((type1_state == BWIN && type == black) || (type1_state == WWIN && type == white)) {
				// 自己可以连五，直接返回
				attackPointList.clear();
				attackPointList.push_back(np);
				return attackPointList;
			}

			if (isDanger) {
				// 存在危险，继续找自己可以连五的棋子
				continue;
			}

			// 考虑对手的落子情况
			Point fnp(i, j);
			fnp.color = 3 - type;
			int type2_state = StateCheck(np, 3 - type);
			state st_type2 = st1;
			if (3 - type == m_computercolor)//如果s的颜色,
			{
				fnp.score = evaluateAIPoint(i, j);
				//PosScore[i][j] = np.score;
			}
			else
			{
				fnp.score = evaluatePlayerPoint(i, j);
				//PosScore[i][j] = np.score;
			}
			fnp.allScore = evaluateAIPoint(i, j) + evaluatePlayerPoint(i, j);
			
			if ((type2_state == BWIN && 3 - type == black) || (type2_state == WWIN && 3 - type == white)) {
				// 对手连五了，局势很危险！！赶紧找自己可以连五的点位，不行就防守
				isDanger = true;
				defensePointList.clear();
				defensePointList.push_back(np);
				continue;
			}

			if (np.score >= 80000) {
				attackPointList.push_back(np);
				continue;
			}
			// 对于自己的冲四进行记录
			if (isAI) {
				// AI才进行VCf
				if (st_type1.four2count > 0) {
					
					vcfPointList.push_back(np);
				}
			}
		}
	}
	// 按分数从大到小排序
	vector<Point> pointList;
	if (!isDanger) {
		// 优先强进攻
		// 如果没有风险且为vcf优先进攻		
		if (!attackPointList.empty())
		{
			if (isAI) {
				// AI有强进攻点位了，就不用考虑后面的点位了
				return attackPointList;
			}
			// 对手可以选择进攻和防守
			//pointList.addAll(attackPointList);
			for (vector<Point>::iterator it = attackPointList.begin(); it != attackPointList.end(); it++)
			{
				pointList.push_back(*it);//将!ai的进攻点放入搜索列表
			}
		}
		
		// VCX进攻
		if (!vcfPointList.empty()) {
			//pointList.addAll(vcxPointList);
			for (vector<Point>::iterator it = vcfPointList.begin(); it != vcfPointList.end(); it++)
			{
				pointList.push_back(*it);
			}
		}
	}

	if (!defensePointList.empty()) {
		// 进行防守
		if (isAI) {
			// AI优先选择进攻，把防守点位放后面
			//pointList.addAll(defensePointList);
			for (vector<Point>::iterator it = defensePointList.begin(); it != defensePointList.end(); it++)
			{
				pointList.push_back(*it);
			}
		}
		else {
			// 对手优先考虑防守，把防守点位放前面
			//pointList.addAll(0, defensePointList);
			for (vector<Point>::iterator it = defensePointList.begin(); it != defensePointList.end(); it++)
			{
				pointList.insert(pointList.begin(), (*it));
			}
		}
	}

	return pointList;
}

vector<Point> Game::getVctPoints(int type)
{
	bool isAI = type == m_computercolor;
	// 进攻点列表
	vector<Point> attackPointList;
	// 防守点列表
	vector<Point> defensePointList;
	// VCX列表
	vector<Point> vctPointList;

	bool isDanger = false;
	bool isLDanger = false;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (Board[i][j] != 0) {
				// 该处已有棋子，跳过
				continue;
			}
			// 考虑自己的落子情况
			Point np(i, j);
			np.color = type;
			int type1_state = StateCheck(np, type);
			state st_type1 = st1;
			if (/*type == black &&*/
				(type1_state == THREE_THREE_BAN ||
					type1_state == FOUR_FOUR_BAN ||
					type1_state == LONG_BAN))
			{
				continue;
			}
			if (type == m_computercolor)//如果是电脑的颜色,
			{
				np.score = evaluateAIPoint(i, j);
				//PosScore[i][j] = np.score;
			}
			else
			{
				np.score = evaluatePlayerPoint(i, j);
				//PosScore[i][j] = np.score;
			}
			np.allScore = evaluatePlayerPoint(i, j) + evaluateAIPoint(i, j);
			if ((type1_state == BWIN && type == black) || (type1_state == WWIN && type == white)) {
				// 自己可以连五，直接返回
				attackPointList.clear();
				attackPointList.push_back(np);
				return attackPointList;
			}

			if (isDanger) {
				// 存在危险，继续找自己可以连五的棋子
				continue;
			}

			// 考虑对手的落子情况
			Point fnp(i, j);
			fnp.color = 3 - type;
			int type2_state = StateCheck(np, 3 - type);
			state st_type2 = st1;
			if (3 - type == m_computercolor)//如果s的颜色,
			{
				fnp.score = evaluateAIPoint(i, j);
				//PosScore[i][j] = np.score;
			}
			else
			{
				fnp.score = evaluatePlayerPoint(i, j);
				//PosScore[i][j] = np.score;
			}
			fnp.allScore = evaluateAIPoint(i, j) + evaluatePlayerPoint(i, j);
			if ((type2_state == BWIN && 3 - type == black) || (type2_state == WWIN && 3 - type == white)) {
				// 对手连五了，局势很危险！！赶紧找自己可以连五的点位，不行就防守
				isDanger = true;
				defensePointList.clear();
				defensePointList.push_back(np);
				continue;
			}
			// 看看自己有没有大于等于中风险分值的点位
			if (np.score >= 50000) {
				attackPointList.push_back(np);
				continue;
			}

			if (fnp.score >= 70000)
			{
				isLDanger = true;
				//defensePointList.clear();
				defensePointList.push_back(np);
				continue;
			}


			if (isAI) {
				// AI才进行VCX
				if ((st_type1.four2count > 0)|| (st_type1.three12count > 0 || st_type1.three1count > 0)) {
					//记录vct点位
					vctPointList.push_back(np);
				}
			}
			else {
				// 对手需防守VCT
				if (st_type1.four2count > 0 || fnp.score >= 10000)
				{
					// 选择冲四或防守对方的活四
					defensePointList.push_back(np);
				}
			}
		}
	}
	// 按分数从大到小排序
	sort(attackPointList.begin(), attackPointList.end(), cmpAllScore);
	sort(defensePointList.begin(), defensePointList.end(), cmpAllScore);
	vector<Point> pointList;
	// 如果对面没有成五棋形
	if (!isDanger) {
		// 优先强进攻
		// 如果没有风险且为vcf优先进攻
		// 
		//如果是vct 并且对面没有必胜棋形
		if (!isLDanger)
		{
			if (!attackPointList.empty())
			{
				if (isAI) {
					// AI有强进攻点位了，就不用考虑后面的点位了
					return attackPointList;
				}
				// 对手可以选择进攻和防守
				//pointList.addAll(attackPointList);
				for (vector<Point>::iterator it = attackPointList.begin(); it != attackPointList.end(); it++)
				{
					pointList.push_back(*it);
				}
			}

			// VCT进攻
			if (!vctPointList.empty()) {
				//pointList.addAll(vcxPointList);
				for (vector<Point>::iterator it = vctPointList.begin(); it != vctPointList.end(); it++)
				{
					pointList.push_back(*it);
				}
			}
		}
		// 如果是vct 并且对手有强进攻点
		// 选择防守
	}

	if (!defensePointList.empty()) {
		// 进行防守
		if (isAI) {
			// AI优先选择进攻，把防守点位放后面
			//pointList.addAll(defensePointList);
			for (vector<Point>::iterator it = defensePointList.begin(); it != defensePointList.end(); it++)
			{
				pointList.push_back(*it);
			}
		}
		else {
			// 对手优先考虑防守，把防守点位放前面
			//pointList.addAll(0, defensePointList);
			for (vector<Point>::iterator it = defensePointList.begin(); it != defensePointList.end(); it++)
			{
				pointList.insert(pointList.begin(), (*it));
			}
		}
	}

	return pointList;
}