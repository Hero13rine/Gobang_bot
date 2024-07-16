#include"Game.h"

//��һ��vcx----------------------------------------

vector<Point> Game::getVcxPoints(int type, bool isVcf)
{
	bool isAI = type == m_computercolor;
	// �������б�
	vector<Point> attackPointList;
	// ���ص��б�
	vector<Point> defensePointList;
	// VCX�б�
	vector<Point> vcxPointList;

	bool isDanger = false;
	bool isLDanger = false;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if(Board[i][j] != 0) {
				// �ô��������ӣ�����
				continue;
			}
			// �����Լ����������
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
			if (type == m_computercolor)//����ǵ��Ե���ɫ,
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
				// �Լ��������壬ֱ�ӷ���
				//attackPointList.clear();
				attackPointList.push_back(np);
				return attackPointList;
			}
			
			if (isDanger) {
				// ����Σ�գ��������Լ��������������
				continue;
			}

			// ���Ƕ��ֵ��������
			Point fnp(i, j);
			fnp.color = 3 - type;
			int type2_state = StateCheck(np, 3 - type);
			state st_type2 = st1;
			if (3 - type == m_computercolor)//���s����ɫ,
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
				// ���������ˣ����ƺ�Σ�գ����Ͻ����Լ���������ĵ�λ�����оͷ���
				isDanger = true;
				defensePointList.clear();
				defensePointList.push_back(fnp);
				continue;
			}
			// �����Լ���û�д��ڵ����з��շ�ֵ�ĵ�λ
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
				// AI�Ž���VCX
				if (st_type1.four2count > 0) {
					// ������VCF����VCT��AI������ѡ�����
					vcxPointList.push_back(np);
				}
				else if (!isVcf && (st_type1.three12count > 0 || st_type1.three1count > 0))
				{
					// ��¼VCT��λ
					vcxPointList.push_back(np);
				}
			}
			else {
				// ���������VCT
				if (!isVcf) {
					if (st_type1.four2count > 0 || fnp.score >= 100000)
					{
						// ѡ����Ļ���ضԷ��Ļ���
						defensePointList.push_back(np);
					}
				}
			}
		}
	}
	// �������Ӵ�С����
	sort(attackPointList.begin(), attackPointList.end(), cmpAllScore);
	sort(defensePointList.begin(), defensePointList.end(), cmpAllScore);
	vector<Point> pointList;
	// �������û�г�������
	if (!isDanger) {
		// ����ǿ����
		// ���û�з�����Ϊvcf���Ƚ���
		if (isVcf)
		{	
			if (!attackPointList.empty())
			{
				if (isAI) {
					// AI��ǿ������λ�ˣ��Ͳ��ÿ��Ǻ���ĵ�λ��
					return attackPointList;
				}
				// ���ֿ���ѡ������ͷ���
				//pointList.addAll(attackPointList);
				for (vector<Point>::iterator it = attackPointList.begin(); it != attackPointList.end(); it++)
				{
					pointList.push_back(*it);//��!ai�Ľ�������������б�
				}
			}
		}
		//�����vct ���Ҷ���û�б�ʤ����
		else if (!isVcf && !isLDanger)
		{
			if (!attackPointList.empty())
			{
				if (isAI) {
					// AI��ǿ������λ�ˣ��Ͳ��ÿ��Ǻ���ĵ�λ��
					return attackPointList;
				}
				// ���ֿ���ѡ������ͷ���
				//pointList.addAll(attackPointList);
				for (vector<Point>::iterator it = attackPointList.begin(); it != attackPointList.end(); it++)
				{
					pointList.push_back(*it);
				}
			}
		}
		// �����vct ���Ҷ�����ǿ������
		// ѡ�����
		else if (!isVcf && isLDanger)
		{
			//��˫���ȸ�Σ�ռ��ķ��ص�λ���з���
			if (!defensePointList.empty()) {
				// ���з���
				if (isAI) {
					// AI����ѡ��������ѷ��ص�λ�ź���
					//pointList.addAll(defensePointList);
					for (vector<Point>::iterator it = defensePointList.begin(); it != defensePointList.end(); it++)
					{
						pointList.push_back(*it);
					}
				}
				else {
					// �������ȿ��Ƿ��أ��ѷ��ص�λ��ǰ��
					//pointList.addAll(0, defensePointList);
					for (vector<Point>::iterator it = defensePointList.begin(); it != defensePointList.end(); it++)
					{
						pointList.insert(pointList.begin(), (*it));
					}
				}
			}
		}


		// VCX����
		if (!vcxPointList.empty()) {
			//pointList.addAll(vcxPointList);
			for (vector<Point>::iterator it = vcxPointList.begin(); it != vcxPointList.end(); it++)
			{
				pointList.push_back(*it);
			}
		}
	}

	if (!defensePointList.empty()) {
		// ���з���
		if (isAI) {
			// AI����ѡ��������ѷ��ص�λ�ź���
			//pointList.addAll(defensePointList);
			for (vector<Point>::iterator it = defensePointList.begin(); it != defensePointList.end(); it++)
			{
				pointList.push_back(*it);
			}
		}
		else {
			// �������ȿ��Ƿ��أ��ѷ��ص�λ��ǰ��
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
  * ��ɱ��VCF��VCT��
  *
  * @param type  ��ǰ���巽 0.���ڵ��ʾAI���� 1.AI 2.���
  * @param depth �������
  * @param isVcf true:VCF false:VCT
  * @return
  */
Point Game::vcx(int type, int depth, bool isVcf)
{
	Point pp(-1, -1);
	if (depth == 0) {
		// ��ɱʧ��

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
			// �Ѿ������γɱ�ʤ�����ˣ������AI���ӣ��ͷ��ص�ǰ�ڵ㣬���򷵻ؿ�
			return isAI ? point : pp;	
		}

		Board[point.x][point.y] = type;
		best = vcx(3 - type, depth - 1, isVcf);
		Board[point.x][point.y] = EMPTY;

		if (best.x == pp.x) {
			if (isAI) {
				// AI��û�ҵ�������ɱ�ɹ������ӣ�������...
				continue;
			}

			// �������سɹ��ˣ�ֱ�ӷ��ؿճ�ȥ����ʾ��ɱʧ����
			return pp;
		}

		// ��¼��ǰ�ڵ�
		best = point;

		if (isAI) {
			// AI�Ѿ��ҵ�������ɱ�������ˣ�ͬ������Ľڵ㶼���ÿ���
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
	// �������б�, ֻ��������ĵ�
	vector<Point> attackPointList;
	// ���ص��б� �������ֱ�ʤ�ĵ�
	vector<Point> defensePointList;
	// VCF�б� 
	vector<Point> vcfPointList;
	bool isDanger = false;
	bool isLDanger = false;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (Board[i][j] != 0) {
				// �ô��������ӣ�����
				continue;
			}
			Point np(i, j);//���ǵ�ǰ����
			np.color = type;
			int type1_state = StateCheck(np, type);
			state st_type1 = st1;
			if (type == black &&//���ֵ�ֱ������
				(type1_state == THREE_THREE_BAN ||
					type1_state == FOUR_FOUR_BAN ||
					type1_state == LONG_BAN))
			{
				continue;
			}
			if (type == m_computercolor)//����ǵ��Ե���ɫ,
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
				// �Լ��������壬ֱ�ӷ���
				attackPointList.clear();
				attackPointList.push_back(np);
				return attackPointList;
			}

			if (isDanger) {
				// ����Σ�գ��������Լ��������������
				continue;
			}

			// ���Ƕ��ֵ��������
			Point fnp(i, j);
			fnp.color = 3 - type;
			int type2_state = StateCheck(np, 3 - type);
			state st_type2 = st1;
			if (3 - type == m_computercolor)//���s����ɫ,
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
				// ���������ˣ����ƺ�Σ�գ����Ͻ����Լ���������ĵ�λ�����оͷ���
				isDanger = true;
				defensePointList.clear();
				defensePointList.push_back(np);
				continue;
			}

			if (np.score >= 80000) {
				attackPointList.push_back(np);
				continue;
			}
			// �����Լ��ĳ��Ľ��м�¼
			if (isAI) {
				// AI�Ž���VCf
				if (st_type1.four2count > 0) {
					
					vcfPointList.push_back(np);
				}
			}
		}
	}
	// �������Ӵ�С����
	vector<Point> pointList;
	if (!isDanger) {
		// ����ǿ����
		// ���û�з�����Ϊvcf���Ƚ���		
		if (!attackPointList.empty())
		{
			if (isAI) {
				// AI��ǿ������λ�ˣ��Ͳ��ÿ��Ǻ���ĵ�λ��
				return attackPointList;
			}
			// ���ֿ���ѡ������ͷ���
			//pointList.addAll(attackPointList);
			for (vector<Point>::iterator it = attackPointList.begin(); it != attackPointList.end(); it++)
			{
				pointList.push_back(*it);//��!ai�Ľ�������������б�
			}
		}
		
		// VCX����
		if (!vcfPointList.empty()) {
			//pointList.addAll(vcxPointList);
			for (vector<Point>::iterator it = vcfPointList.begin(); it != vcfPointList.end(); it++)
			{
				pointList.push_back(*it);
			}
		}
	}

	if (!defensePointList.empty()) {
		// ���з���
		if (isAI) {
			// AI����ѡ��������ѷ��ص�λ�ź���
			//pointList.addAll(defensePointList);
			for (vector<Point>::iterator it = defensePointList.begin(); it != defensePointList.end(); it++)
			{
				pointList.push_back(*it);
			}
		}
		else {
			// �������ȿ��Ƿ��أ��ѷ��ص�λ��ǰ��
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
	// �������б�
	vector<Point> attackPointList;
	// ���ص��б�
	vector<Point> defensePointList;
	// VCX�б�
	vector<Point> vctPointList;

	bool isDanger = false;
	bool isLDanger = false;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (Board[i][j] != 0) {
				// �ô��������ӣ�����
				continue;
			}
			// �����Լ����������
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
			if (type == m_computercolor)//����ǵ��Ե���ɫ,
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
				// �Լ��������壬ֱ�ӷ���
				attackPointList.clear();
				attackPointList.push_back(np);
				return attackPointList;
			}

			if (isDanger) {
				// ����Σ�գ��������Լ��������������
				continue;
			}

			// ���Ƕ��ֵ��������
			Point fnp(i, j);
			fnp.color = 3 - type;
			int type2_state = StateCheck(np, 3 - type);
			state st_type2 = st1;
			if (3 - type == m_computercolor)//���s����ɫ,
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
				// ���������ˣ����ƺ�Σ�գ����Ͻ����Լ���������ĵ�λ�����оͷ���
				isDanger = true;
				defensePointList.clear();
				defensePointList.push_back(np);
				continue;
			}
			// �����Լ���û�д��ڵ����з��շ�ֵ�ĵ�λ
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
				// AI�Ž���VCX
				if ((st_type1.four2count > 0)|| (st_type1.three12count > 0 || st_type1.three1count > 0)) {
					//��¼vct��λ
					vctPointList.push_back(np);
				}
			}
			else {
				// ���������VCT
				if (st_type1.four2count > 0 || fnp.score >= 10000)
				{
					// ѡ����Ļ���ضԷ��Ļ���
					defensePointList.push_back(np);
				}
			}
		}
	}
	// �������Ӵ�С����
	sort(attackPointList.begin(), attackPointList.end(), cmpAllScore);
	sort(defensePointList.begin(), defensePointList.end(), cmpAllScore);
	vector<Point> pointList;
	// �������û�г�������
	if (!isDanger) {
		// ����ǿ����
		// ���û�з�����Ϊvcf���Ƚ���
		// 
		//�����vct ���Ҷ���û�б�ʤ����
		if (!isLDanger)
		{
			if (!attackPointList.empty())
			{
				if (isAI) {
					// AI��ǿ������λ�ˣ��Ͳ��ÿ��Ǻ���ĵ�λ��
					return attackPointList;
				}
				// ���ֿ���ѡ������ͷ���
				//pointList.addAll(attackPointList);
				for (vector<Point>::iterator it = attackPointList.begin(); it != attackPointList.end(); it++)
				{
					pointList.push_back(*it);
				}
			}

			// VCT����
			if (!vctPointList.empty()) {
				//pointList.addAll(vcxPointList);
				for (vector<Point>::iterator it = vctPointList.begin(); it != vctPointList.end(); it++)
				{
					pointList.push_back(*it);
				}
			}
		}
		// �����vct ���Ҷ�����ǿ������
		// ѡ�����
	}

	if (!defensePointList.empty()) {
		// ���з���
		if (isAI) {
			// AI����ѡ��������ѷ��ص�λ�ź���
			//pointList.addAll(defensePointList);
			for (vector<Point>::iterator it = defensePointList.begin(); it != defensePointList.end(); it++)
			{
				pointList.push_back(*it);
			}
		}
		else {
			// �������ȿ��Ƿ��أ��ѷ��ص�λ��ǰ��
			//pointList.addAll(0, defensePointList);
			for (vector<Point>::iterator it = defensePointList.begin(); it != defensePointList.end(); it++)
			{
				pointList.insert(pointList.begin(), (*it));
			}
		}
	}

	return pointList;
}