//��cppĿ���Ǵ�Ŷ��ھ���������Լ�������ȷ��
#include"Game.h"

int Game::StateCheck(const Point& a, int color)
{
	if (a.x > mx)//ȷ��������Ч���Χ
		mx = a.x;
	if (a.y > my)
		my = a.y;
	if (a.x < minx)
		minx = a.x;
	if (a.y < miny)
		miny = a.y;
	int nvisx = 14 - mx;//��ǰ���������ķ�Χ(minx miny)
	int nvisy = 14 - my ;
	//�����±������
	int adjsame[8] = { 0 }; //��¼�루x,y�����ڵ�������������
	int adjempty[8] = { 0 }; //��¼adjsame�������������λ��
	int jumpsame[8] = { 0 };//��¼��λ����������������
	int jumpempty[8] = { 0 };//��¼jumpsame��Ŀ�λ��
	int jumpjumpsame[8] = { 0 };//��¼jumpempty�������ĺ�����
	int jumpjumpempty[8] = { 0 };//��¼jumpjumpsame�������Ŀո���
	//��ʼ��
	/*for (int i = 0; i < 8; i++)
	{
		adjsame[i] = adjempty[i] = jumpsame[i] = 0;
		jumpempty[i] = jumpjumpsame[i] = jumpjumpempty[i] = 0;
	}*/
	//----------------------��ʼ���ṹ��----------------------
	st1.isfour1 = false;//����
	st1.isfour2 = false;//����
	st1.isthree = false;//����
	st1.fivecount = 0;
	st1.four1count = 0;
	st1.four21count = 0;
	st1.four2count = 0;
	st1.three1count = 0;
	st1.three12count = 0;
	st1.three2count = 0;
	st1.two1count = 0;//�������ͳ��
	st1.two2count = 0;//�߶�����ͳ��
	st1.mian1 = 0;
	//st1.huo1 = 0;
	// ------------------------------------------------
	// p [����][����]
	//������������-------------------------------------------------------------
	int _x, _y;

	//��������  ��
	{
		for (_y = a.y - 1; _y >= miny && Board[a.x][_y] == color; _y--, adjsame[6]++);
		for (; _y >= miny && Board[a.x][_y] == EMPTY; _y--, adjempty[6]++);
		for (; _y >= miny && Board[a.x][_y] == color; _y--, jumpsame[6]++);
		for (; _y >= miny && Board[a.x][_y] == EMPTY; _y--, jumpempty[6]++);
		for (; _y >= miny && Board[a.x][_y] == color; _y--, jumpjumpsame[6]++);
		for (; _y >= miny && Board[a.x][_y] == EMPTY; _y--, jumpjumpempty[6]++);
		//��������
		for (_x = a.x + 1, _y = a.y - 1; _x < mx && _y >= miny && Board[_x][_y] == color; _x++, _y--, adjsame[5]++);
		for (; _x < mx && _y >= miny && Board[_x][_y] == EMPTY; _x++, _y--, adjempty[5]++);
		for (; _x < mx && _y >= miny && Board[_x][_y] == color; _x++, _y--, jumpsame[5]++);
		for (; _x < mx && _y >= miny && Board[_x][_y] == EMPTY; _x++, _y--, jumpempty[5]++);
		for (; _x < mx && _y >= miny && Board[_x][_y] == color; _x++, _y--, jumpjumpsame[5]++);
		for (; _x < mx && _y >= miny && Board[_x][_y] == EMPTY; _x++, _y--, jumpjumpempty[5]++);
		//��������
		for (_x = a.x + 1; _x < mx && Board[_x][a.y] == color; _x++, adjsame[4]++);
		for (; _x < mx && Board[_x][a.y] == EMPTY; _x++, adjempty[4]++);
		for (; _x < mx && Board[_x][a.y] == color; _x++, jumpsame[4]++);
		for (; _x < mx && Board[_x][a.y] == EMPTY; _x++, jumpempty[4]++);
		for (; _x < mx && Board[_x][a.y] == color; _x++, jumpjumpsame[4]++);
		for (; _x < mx && Board[_x][a.y] == EMPTY; _x++, jumpjumpempty[4]++);
		//����������
		for (_x = a.x + 1, _y = a.y + 1; _x < mx && _y < my && Board[_x][_y] == color; _x++, _y++, adjsame[3]++);
		for (; _x < mx && _y < my && Board[_x][_y] == EMPTY; _x++, _y++, adjempty[3]++);
		for (; _x < mx && _y < my && Board[_x][_y] == color; _x++, _y++, jumpsame[3]++);
		for (; _x < mx && _y < my && Board[_x][_y] == EMPTY; _x++, _y++, jumpempty[3]++);
		for (; _x < mx && _y < my && Board[_x][_y] == color; _x++, _y++, jumpjumpsame[3]++);
		for (; _x < mx && _y < my && Board[_x][_y] == EMPTY; _x++, _y++, jumpjumpempty[3]++);
		//��������
		for (_y = a.y + 1; _y < my && Board[a.x][_y] == color; _y++, adjsame[2]++);
		for (; _y < my && Board[a.x][_y] == EMPTY; _y++, adjempty[2]++);
		for (; _y < my && Board[a.x][_y] == color; _y++, jumpsame[2]++);
		for (; _y < my && Board[a.x][_y] == EMPTY; _y++, jumpempty[2]++);
		for (; _y < my && Board[a.x][_y] == color; _y++, jumpjumpsame[2]++);
		for (; _y < my && Board[a.x][_y] == EMPTY; _y++, jumpjumpempty[2]++);
		//����������
		for (_x = a.x - 1, _y = a.y + 1; _x >= minx && _y < my && Board[_x][_y] == color; _x--, _y++, adjsame[1]++);
		for (; _x >= minx && _y < my && Board[_x][_y] == EMPTY; _x--, _y++, adjempty[1]++);
		for (; _x >= minx && _y < my && Board[_x][_y] == color; _x--, _y++, jumpsame[1]++);
		for (; _x >= minx && _y < my && Board[_x][_y] == EMPTY; _x--, _y++, jumpempty[1]++);
		for (; _x >= minx && _y < my && Board[_x][_y] == color; _x--, _y++, jumpjumpsame[1]++);
		for (; _x >= minx && _y < my && Board[_x][_y] == EMPTY; _x--, _y++, jumpjumpempty[1]++);
		//��������
		for (_x = a.x - 1; _x >= minx && Board[_x][a.y] == color; _x--, adjsame[0]++);
		for (; _x >= minx && Board[_x][a.y] == EMPTY; _x--, adjempty[0]++);
		for (; _x >= minx && Board[_x][a.y] == color; _x--, jumpsame[0]++);
		for (; _x >= minx && Board[_x][a.y] == EMPTY; _x--, jumpempty[0]++);
		for (; _x >= minx && Board[_x][a.y] == color; _x--, jumpjumpsame[0]++);	
		for (; _x >= minx && Board[_x][a.y] == EMPTY; _x--, jumpjumpempty[0]++);
		//����������
		for (_x = a.x - 1, _y = a.y - 1; _x >= minx && _y >= miny && Board[_x][_y] == color; _x--, _y--, adjsame[7]++);
		for (; _x >= minx && _y >= miny && Board[_x][_y] == EMPTY; _x--, _y--, adjempty[7]++);
		for (; _x >= minx && _y >= miny && Board[_x][_y] == color; _x--, _y--, jumpsame[7]++);
		for (; _x >= minx && _y >= miny && Board[_x][_y] == EMPTY; _x--, _y--, jumpempty[7]++);
		for (; _x >= minx && _y >= miny && Board[_x][_y] == color; _x--, _y--, jumpjumpsame[7]++);
		for (; _x >= minx && _y >= miny && Board[_x][_y] == EMPTY; _x--, _y--, jumpjumpempty[7]++);
		// ----------------------------------------------------------------------------------------------------------------
		int ii = 0;
		if (jumpsame[ii] == 0 && adjsame[ii] != 0)//��
			adjempty[ii] = minx;
		else if (jumpsame[ii] != 0 && jumpjumpsame[ii] == 0)
			jumpempty[ii] = minx;
		else if (jumpjumpsame[ii] != 0)
			jumpjumpempty[ii] = minx;
		ii++;//1
		if (jumpsame[ii] == 0 && adjsame[ii] != 0)//����
			adjempty[ii] = min(minx, 14 - my);
		else if (jumpsame[ii] != 0 && jumpjumpsame[ii] == 0)
			jumpempty[ii] = min(minx, 14 - my);
		else if (jumpjumpsame[ii] != 0)
			jumpjumpempty[ii] = min(minx, 14 - my);
		ii++;//2
		if (jumpsame[ii] == 0 && adjsame[ii] != 0)//��
			adjempty[ii] = 14 - my;
		else if (jumpsame[ii] != 0 && jumpjumpsame[ii] == 0)
			jumpempty[ii] = 14 - my;
		else if (jumpjumpsame[ii] != 0)
			jumpjumpempty[ii] = 14 - my;
		ii++;//3
		if (jumpsame[ii] == 0 && adjsame[ii] != 0)//����
			adjempty[ii] = min(14 - mx, 14 - my);
		else if (jumpsame[ii] != 0 && jumpjumpsame[ii] == 0)
			jumpempty[ii] = min(14 - mx, 14 - my);
		else if (jumpjumpsame[ii] != 0)
			jumpjumpempty[ii] = min(14 - mx, 14 - my);
		ii++;//4
		if (jumpsame[ii] == 0 && adjsame[ii] != 0)//��
			adjempty[ii] = 14-mx;
		else if (jumpsame[ii] != 0 && jumpjumpsame[ii] == 0)
			jumpempty[ii] = 14 - mx;
		else if (jumpjumpsame[ii] != 0)
			jumpjumpempty[ii] = 14 - mx;
		ii++;//5
		if (jumpsame[ii] == 0 && adjsame[ii] != 0)//����
			adjempty[ii] = min(my, 14 - mx);
		else if (jumpsame[ii] != 0 && jumpjumpsame[ii] == 0)
			jumpempty[ii] = min(my, 14 - mx);
		else if (jumpjumpsame[ii] != 0)
			jumpjumpempty[ii] = min(my, 14 - mx);
		ii++;//6
		if (jumpsame[ii] == 0 && adjsame[ii] != 0)//��
			adjempty[ii] = miny;
		else if (jumpsame[ii] != 0 && jumpjumpsame[ii] == 0)
			jumpempty[ii] = miny;
		else if (jumpjumpsame[ii] != 0)
			jumpjumpempty[ii] = miny;
		ii++;//7
		if (jumpsame[ii] == 0 && adjsame[ii] != 0)//����
			adjempty[ii] = min(miny, minx);
		else if (jumpsame[ii] != 0 && jumpjumpsame[ii] == 0)
			jumpempty[ii] = min(miny, minx);
		else if (jumpjumpsame[ii] != 0)
			jumpjumpempty[ii] = min(miny, minx);
		
	
	}
	if (color == black)
	{
		for (int i = 0; i < 4; i++)
		{
			if (adjsame[i] + adjsame[i + 4] >= 5)//���Ӽ���������
			{
				return LONG_BAN;//��������
			}
			if (adjsame[i] + adjsame[i + 4] >= 4)
			{
				return BWIN;
			}
			if (adjsame[i] + adjsame[i + 4] == 3)//�������� ?1111?
			{
				//���ĳ����ж�
				//bool isfour1 = false;//����
				//bool isfour2 = false;//����
				if (adjempty[i] > 0 && adjempty[i + 4] > 0)//011110
				{
					st1.four1count++;
				}
				if (adjempty[i + 4] > 0 && adjempty[i] == 0 || adjempty[i] > 0 && adjempty[i + 4] == 0) //211110
				{
					st1.four2count++;
				}

			}
			else if (adjsame[i] + adjsame[i + 4] == 2)//�������� ?000?    1000_01, _000_0_, 1000_0_1
			{
				//101��1��101ͬ�������Ľ���
				if (adjempty[i] == 1 && jumpsame[i] == 1 && adjempty[i + 4] == 1 && jumpsame[i + 4] == 1)
				{
					return FOUR_FOUR_BAN;
				}
				//���ĳ��ļ��
				//_T("10111"), _T("11101"), 
				if (adjempty[i] == 1 && jumpsame[i] == 1 || adjempty[i + 4] == 1 && jumpsame[i + 4] == 1)// ?0+000?  10+000_
				{
					st1.four21count++;
				}
				//�������
				//-----------------------------------------
				// x__OOO_x
				if ((adjempty[i] >= 2 && jumpsame[i] == 0) && (adjempty[i + 4] >= 1 && jumpsame[i + 4] == 0)
					|| (adjempty[i + 4] >= 2 && jumpsame[i + 4] == 0) && (adjempty[i] >= 1 && jumpsame[i] == 0))
				{
					st1.isthree = true;
					st1.three1count++;
				}

				//-----------------------------------------
				//�������   X_OOO_X    211100  001112
				if ((adjempty[i] == 2 && jumpsame[i] == 0 && adjempty[i + 4] == 0 && jumpsame[i + 4] == 0)
					|| ((adjempty[i + 4] == 2 && jumpsame[i + 4] == 0) && (adjempty[i] == 0 && jumpsame[i] == 0))
					|| (adjempty[i] == 1 && jumpsame[i] == 0) && (adjempty[i + 4] == 1 && jumpsame[i + 4] == 0))
				{
					st1.three2count++;
				}
			}
			else if (adjsame[i] + adjsame[i + 4] == 1)  //�������� ?00?
			{
				//0101[1]010 ͬ������������(Ŀǰ������û������涨)
				/*if (adjempty[i] == 1 && jumpsame[i] == 1 && jumpempty[i] >= 1 && adjempty[i + 4] == 1 && jumpsame[i + 4] == 1 && jumpempty[i + 4] >= 1)
				{
					return THREE_THREE_BAN;
				}*/

				//21101[1]0112 ͬ�������Ľ���
				if (adjempty[i] == 1 && jumpsame[i] == 2 && adjempty[i + 4] == 1 && jumpsame[i + 4] == 2)
				{
					return FOUR_FOUR_BAN;
				}
				//���ĳ����ж�
				//_T("11011"),
				if (adjempty[i] == 1 && jumpsame[i] == 2 || adjempty[i + 4] == 1 && jumpsame[i + 4] == 2)  // ?00+00?
				{
					st1.four21count++;
				}
				//���� X_00_0__X
				if ((adjempty[i] == 1 && jumpsame[i] == 1 && (jumpempty[i] > 1 || jumpempty[i] == 1 && jumpjumpsame[i] == 0) && (adjempty[i + 4] > 1 || adjempty[i + 4] == 1 && jumpsame[i + 4] == 0))
					|| (adjempty[i + 4] == 1 && jumpsame[i + 4] == 1 && (jumpempty[i + 4] > 1 || jumpempty[i + 4] == 1 && jumpjumpsame[i + 4] == 0) && (adjempty[i] > 1 || adjempty[i] == 1 && jumpsame[i] == 0)))
				{
					st1.three12count++;
				}
				//����   X00_0__X    X__00_0X    _OO__O_
				if (((adjempty[i] == 1 && jumpsame[i] == 1 && jumpempty[i] >= 2 && jumpjumpsame[i] == 0 && (adjempty[i + 4] == 0 && jumpsame[i + 4] == 0))
					|| (adjempty[i + 4] == 1 && jumpsame[i + 4] == 1 && jumpempty[i + 4] >= 2 && jumpjumpsame[i + 4] == 0 && (adjempty[i] == 0 && jumpsame[i] == 0)))
					|| ((adjempty[i] == 1 && jumpsame[i] == 1 && (jumpempty[i] == 0 && jumpjumpsame[i] == 0) && adjempty[i + 4] >= 2 && jumpsame[i + 4] == 0)
						|| ((adjempty[i + 4] == 1 && jumpsame[i + 4] == 1 && (jumpempty[i + 4] == 0 && jumpjumpsame[i + 4] == 0) && adjempty[i] >= 2 && jumpsame[i] == 0)))
					|| ((adjempty[i] == 2 && jumpsame[i] == 1 && jumpempty[i] >= 1 && adjempty[i + 4] >= 1)
						|| (adjempty[i + 4] == 2 && jumpsame[i + 4] == 1 && jumpempty[i + 4] >= 1 && adjempty[i] >= 1)))
				{
					st1.three2count++;
					//cout << "��������";
				}
				//����ж� _T("0001100"),_T("0011000")
				if ((adjempty[i] >= 2 && adjempty[i + 4] >= 3) || (adjempty[i + 4] >= 2 && adjempty[i] >= 3))
				{
					st1.two1count++;
				}
				//�߶��ж� _T("000112"),_T("211000")_T("2011002"),_T("2001102")
				if ((adjempty[i] == 0 && adjempty[i + 4] >= 3) || (adjempty[i + 4] == 0 && adjempty[i] >= 3)
					|| (adjempty[i] == 1 && jumpsame[i] == 0 && adjempty[i + 4] >= 2 && jumpsame[i + 4] == 0)
					|| (adjempty[i + 4] == 1 && jumpsame[i + 4] == 0 && adjempty[i] >= 2 && jumpsame[i] == 0))
				{
					st1.two2count++;
				}
			}
			else if (adjsame[i] + adjsame[i + 4] == 0)  // һ��  ?0?
			{
				//1110��1��0111 ͬ�������Ľ���
				if (adjempty[i] == 1 && jumpsame[i] == 3 && adjempty[i + 4] == 1 && jumpsame[i + 4] == 3)
				{
					return FOUR_FOUR_BAN;
				}
				if (adjempty[i] == 1 && jumpsame[i] == 3) //?000+0?
				{
					st1.four21count++;
				}
				if (adjempty[i + 4] == 1 && jumpsame[i + 4] == 3)//?0+000?
				{
					st1.four21count++;
				}
				//����     x_0_00__x
				if ((adjempty[i] == 1 && jumpsame[i] == 2 && jumpempty[i] >= 1 && adjempty[i + 4] >= 1)
					|| (adjempty[i + 4] == 1 && jumpsame[i + 4] == 2 && jumpempty[i + 4] >= 1 && adjempty[i] >= 1))
				{
					st1.three12count++;
					//cout << "1���� ";
					//cout << i << endl;
				}
				//�������    x0_00__x  x__0_00x  _[O]_O_O_    _O_[O]_O_ 
				if (((adjempty[i] == 1 && jumpsame[i] == 2 && (jumpempty[i] >= 2 && jumpjumpsame[i] == 0) && (adjempty[i + 4] == 0 && jumpsame[i + 4] == 0))
					|| (adjempty[i + 4] == 1 && jumpsame[i + 4] == 2 && (jumpempty[i + 4] >= 2 && jumpjumpsame[i + 4] == 0) && (adjempty[i] == 0 && jumpsame[i] == 0)))
					|| (adjempty[i] == 1 && jumpsame[i] == 2 && (jumpempty[i] == 0 && jumpjumpsame[i] == 0) && adjempty[i + 4] >= 2 && jumpsame[i + 4] == 0)
					|| (adjempty[i + 4] == 1 && jumpsame[i + 4] == 2 && (jumpempty[i + 4] == 0 && jumpjumpsame[i + 4] == 0) && adjempty[i] >= 2 && jumpsame[i] == 0)
					|| ((adjempty[i] == 1 && jumpsame[i] == 1 && jumpempty[i] == 1 && jumpjumpsame[i] == 1 && jumpjumpempty[i] >= 1 && (adjempty[i + 4] >= 1))
						|| (adjempty[i + 4] == 1 && jumpsame[i + 4] == 1 && jumpempty[i + 4] == 1 && jumpjumpsame[i + 4] == 1 && jumpjumpempty[i] >= 1 && (adjempty[i + 4] >= 1))
						|| (adjempty[i] == 1 && jumpsame[i] == 1 && jumpempty[i] >= 1 && (adjempty[i + 4] == 1 && jumpsame[i + 4] == 1 && jumpempty[i + 4] >= 1))))
				{
					st1.three2count++;
					//cout << "һ������";
				}
				//����ж� 010[1]0 ->  0[1]010  01010
				if ((adjempty[i] == 1 && jumpsame[i] == 1 && jumpempty[i] >= 1 && adjempty[i + 4] >= 1) || (adjempty[i + 4] == 1 && jumpsame[i + 4] == 1 && jumpempty[i + 4] >= 1 && adjempty[i] >= 1))
				{
					st1.two1count++;
					//cout << "һ�ӻ��";
				}
				//010010
				if ((adjempty[i] == 2 && jumpsame[i] == 1 && jumpempty[i] >= 1 && adjempty[i + 4] >= 1) || (adjempty[i + 4] == 2 && jumpsame[i + 4] == 1 && jumpempty[i + 4] >= 1 && adjempty[i] >= 1))
				{
					st1.two1count++;
					//cout << "һ�ӻ��";
				}
				//�߶��ж�_T("00101 2"),_T("210100"),_T("010012"),_T("210010"),_T("10001"),_T("2010102")
				if ((adjempty[i] == 1 && jumpsame[i] == 1 && jumpempty[i] == 0 && adjempty[i + 4] >= 2) || (adjempty[i + 4] == 1 && jumpsame[i + 4] == 1 && jumpempty[i + 4] == 0 && adjempty[i] >= 2)
					|| (adjempty[i] == 0 && adjempty[i + 4] == 1 && jumpsame[i + 4] == 1 && jumpempty[i + 4] >= 2) || (adjempty[i + 4] == 0 && adjempty[i] == 1 && jumpsame[i] == 1 && jumpempty[i] >= 2)
					|| (adjempty[i] == 2 && jumpsame[i] == 1 && jumpempty[i] >= 0 && adjempty[i + 4] == 0) || (adjempty[i + 4] == 2 && jumpsame[i + 4] == 1 && jumpempty[i + 4] >= 0 && adjempty[i] == 0)
					|| (adjempty[i] == 0 && adjempty[i + 4] == 2 && jumpsame[i] == 1 && jumpempty[i] >= 1) || (adjempty[i + 4] == 0 && adjempty[i] == 2 && jumpsame[i + 4] == 1 && jumpempty[i + 4] >= 1)
					|| (adjempty[i] == 1 && jumpsame[i] == 1 && jumpempty[i] == 1 && jumpjumpsame[i] == 0) || (adjempty[i + 4] == 1 && jumpsame[i + 4] == 1 && jumpempty[i + 4] == 1 && jumpjumpsame[i + 4] == 0))
				{
					st1.two2count++;
				}
				//��һ��"001200", "002100", "020100", "000210", "000120", "210000", "000012"��
				if ((adjempty[i] == 0 && jumpempty[i] >= 2 && jumpsame[i + 4] == 0) || (adjempty[i + 4] == 0 && jumpempty[i + 4] >= 2 && jumpsame[i] == 0)
					|| (adjempty[i] >= 2 && adjempty[i + 4] == 1 && jumpsame[i + 4] == 0) || (adjempty[i + 4] >= 2 && adjempty[i] == 1 && jumpsame[i] == 0)
					|| (adjempty[i] >= 4 && adjempty[i + 4] == 0) || (adjempty[i + 4] >= 4 && adjempty[i] == 0))
				{
					st1.mian1++;
				}
				//��һ"010200", "002010", "020100", "001020", "201000", "000102", "000201"
				if (adjempty[i] >= 1 && adjempty[i + 4] >= 1)
				{
					//st1.huo1++;
				}

			}
		}
		if (st1.four1count + st1.four2count + st1.four21count > 1)
		{
			return FOUR_FOUR_BAN;
		}
		if (st1.three1count + st1.three12count > 1)
		{
			return THREE_THREE_BAN;
		}
		//����Ƿ������ӣ����޽��������ӣ���ֱ�ӻ�ʤ��
		for (int i = 0; i < 4; i++)
		{
			if (adjsame[i] + adjsame[i + 4] == 4)
			{
				return BWIN;
			}
		}
	}
	//////////////////////////////////////////////bai//////////////////////////////////////////////////
	else
	{
		for (int i = 0; i < 4; i++)
		{
			if (adjsame[i] + adjsame[i + 4] >= 4)//����ʤ
			{
				return WWIN;
			}
		}
		for (int i = 0; i < 4; i++)
		{
			if (adjsame[i] + adjsame[i + 4] == 3)//�������� ?1111?
			{
				//���ĳ����ж�
				//bool isfour1 = false;//����
				//bool isfour2 = false;//����
				if (adjempty[i] > 0 && adjempty[i + 4] > 0)//011110
				{
					st1.four1count++;
				}
				if (adjempty[i + 4] > 0 && adjempty[i] == 0 || adjempty[i] > 0 && adjempty[i + 4] == 0) //211110
				{
					st1.four2count++;
				}
			}
			else if (adjsame[i] + adjsame[i + 4] == 2)//�������� ?000?    1000_01, _000_0_, 1000_0_1
			{
				//������ ?[000]_00?
				if ((adjempty[i] == 1 && jumpsame[i] == 2)
					|| adjempty[i + 4] == 1 && jumpsame[i + 4] == 2)
				{
					st1.fivecount++;
				}
				//���ĳ��ļ��
				//_T("10111"), _T("11101"), 
				if (adjempty[i] == 1 && jumpsame[i] == 1 || adjempty[i + 4] == 1 && jumpsame[i + 4] == 1)// ?0+000?  10+000_
				{
					st1.four21count++;
				}
				//�������
				//-----------------------------------------
				// x__OOO_x
				if ((adjempty[i] >= 2 && jumpsame[i] == 0) && (adjempty[i + 4] >= 1 && jumpsame[i + 4] == 0)
					|| (adjempty[i + 4] >= 2 && jumpsame[i + 4] == 0) && (adjempty[i] >= 1 && jumpsame[i] == 0))
				{
					st1.isthree = true;
					st1.three1count++;
				}
				//-----------------------------------------
				//�������   X_OOO_X    211100  001112
				if ((adjempty[i] == 2 && jumpsame[i] == 0 && adjempty[i + 4] == 0 && jumpsame[i + 4] == 0)
					|| ((adjempty[i + 4] == 2 && jumpsame[i + 4] == 0) && (adjempty[i] == 0 && jumpsame[i] == 0))
					|| (adjempty[i] == 1 && jumpsame[i] == 0) && (adjempty[i + 4] == 1 && jumpsame[i + 4] == 0))
				{
					st1.three2count++;
				}
			}
			else if (adjsame[i] + adjsame[i + 4] == 1)  //�������� ?00?
			{
				//������ ?[00]_000?
				if ((adjempty[i] == 1 && jumpsame[i] == 3)
					|| adjempty[i + 4] == 1 && jumpsame[i + 4] == 3)
				{
					st1.fivecount++;
				}
				//���ĳ����ж�
				//_T("11011"),
				if (adjempty[i] == 1 && jumpsame[i] == 2 || adjempty[i + 4] == 1 && jumpsame[i + 4] == 2)  // ?00+00?
				{
					st1.four21count++;
				}
				//���� X_00_0__X
				if ((adjempty[i] == 1 && jumpsame[i] == 1 && (jumpempty[i] > 1 || jumpempty[i] == 1 && jumpjumpsame[i] == 0) && (adjempty[i + 4] > 1 || adjempty[i + 4] == 1 && jumpsame[i + 4] == 0))
					|| (adjempty[i + 4] == 1 && jumpsame[i + 4] == 1 && (jumpempty[i + 4] > 1 || jumpempty[i + 4] == 1 && jumpjumpsame[i + 4] == 0) && (adjempty[i] > 1 || adjempty[i] == 1 && jumpsame[i] == 0)))
				{
					st1.three12count++;
				}
				//����   X00_0__X    X__00_0X    _OO__O_
				if (((adjempty[i] == 1 && jumpsame[i] == 1 && jumpempty[i] >= 2 && jumpjumpsame[i] == 0 && (adjempty[i + 4] == 0 && jumpsame[i + 4] == 0))
					|| (adjempty[i + 4] == 1 && jumpsame[i + 4] == 1 && jumpempty[i + 4] >= 2 && jumpjumpsame[i + 4] == 0 && (adjempty[i] == 0 && jumpsame[i] == 0)))
					|| ((adjempty[i] == 1 && jumpsame[i] == 1 && (jumpempty[i] == 0 && jumpjumpsame[i] == 0) && adjempty[i + 4] >= 2 && jumpsame[i + 4] == 0)
						|| ((adjempty[i + 4] == 1 && jumpsame[i + 4] == 1 && (jumpempty[i + 4] == 0 && jumpjumpsame[i + 4] == 0) && adjempty[i] >= 2 && jumpsame[i] == 0)))
					|| ((adjempty[i] == 2 && jumpsame[i] == 1 && jumpempty[i] >= 1 && adjempty[i + 4] >= 1)
						|| (adjempty[i + 4] == 2 && jumpsame[i + 4] == 1 && jumpempty[i + 4] >= 1 && adjempty[i] >= 1)))
				{
					st1.three2count++;
					//cout << "��������";
				}
				//����ж� _T("0001100"),_T("0011000")
				if ((adjempty[i] >= 2 && adjempty[i + 4] >= 3) || (adjempty[i + 4] >= 2 && adjempty[i] >= 3))
				{
					st1.two1count++;
				}
				//�߶��ж� _T("000112"),_T("211000")_T("2011002"),_T("2001102")
				if ((adjempty[i] == 0 && adjempty[i + 4] >= 3)
					|| (adjempty[i + 4] == 0 && adjempty[i] >= 3) || (adjempty[i] == 1 && jumpsame[i] == 0 && adjempty[i + 4] >= 2 && jumpsame[i + 4] == 0)
					|| (adjempty[i + 4] == 1 && jumpsame[i + 4] == 0 && adjempty[i] >= 2 && jumpsame[i] == 0))
				{
					st1.two2count++;
				}
			}
			else if (adjsame[i] + adjsame[i + 4] == 0)  // һ��  ?0?
			{
				if (adjempty[i] == 1 && jumpsame[i] == 3) //?000+0?
				{
					st1.four21count++;
				}
				if (adjempty[i + 4] == 1 && jumpsame[i + 4] == 3)//?0+000?
				{
					st1.four21count++;
				}
				//����     x_0_00_x
				if ((adjempty[i] == 1 && jumpsame[i] == 2 && jumpempty[i] >= 1 && adjempty[i + 4] >= 1)
					|| (adjempty[i + 4] == 1 && jumpsame[i + 4] == 2 && jumpempty[i + 4] >= 1 && adjempty[i] >= 1))
				{
					st1.three12count++;
					//cout << "1���� ";
					//cout << i << endl;
				}
				//�������    x0_00__x  x__0_00x  _[O]_O_O_    _O_[O]_O_ 
				if (((adjempty[i] == 1 && jumpsame[i] == 2 && (jumpempty[i] >= 2 && jumpjumpsame[i] == 0) && (adjempty[i + 4] == 0 && jumpsame[i + 4] == 0))
					|| (adjempty[i + 4] == 1 && jumpsame[i + 4] == 2 && (jumpempty[i + 4] >= 2 && jumpjumpsame[i + 4] == 0) && (adjempty[i] == 0 && jumpsame[i] == 0)))
					|| (adjempty[i] == 1 && jumpsame[i] == 2 && (jumpempty[i] == 0 && jumpjumpsame[i] == 0) && adjempty[i + 4] >= 2 && jumpsame[i + 4] == 0)
					|| (adjempty[i + 4] == 1 && jumpsame[i + 4] == 2 && (jumpempty[i + 4] == 0 && jumpjumpsame[i + 4] == 0) && adjempty[i] >= 2 && jumpsame[i] == 0)
					|| ((adjempty[i] == 1 && jumpsame[i] == 1 && jumpempty[i] == 1 && jumpjumpsame[i] == 1 && jumpjumpempty[i] >= 1 && (adjempty[i + 4] >= 1))
						|| (adjempty[i + 4] == 1 && jumpsame[i + 4] == 1 && jumpempty[i + 4] == 1 && jumpjumpsame[i + 4] == 1 && jumpjumpempty[i] >= 1 && (adjempty[i + 4] >= 1))
						|| (adjempty[i] == 1 && jumpsame[i] == 1 && jumpempty[i] >= 1 && (adjempty[i + 4] == 1 && jumpsame[i + 4] == 1 && jumpempty[i + 4] >= 1))))
				{
					st1.three2count++;
					//cout << "һ������";
				}
				//����ж� 010[1]0 ->  0[1]010  01010
				if ((adjempty[i] == 1 && jumpsame[i] == 1 && jumpempty[i] >= 1 && adjempty[i + 4] >= 1) || (adjempty[i + 4] == 1 && jumpsame[i + 4] == 1 && jumpempty[i + 4] >= 1 && adjempty[i] >= 1))
				{
					st1.two1count++;
					//cout << "һ�ӻ��";
				}
				//010010
				if ((adjempty[i] == 2 && jumpsame[i] == 1 && jumpempty[i] >= 1 && adjempty[i + 4] >= 1) || (adjempty[i + 4] == 2 && jumpsame[i + 4] == 1 && jumpempty[i + 4] >= 1 && adjempty[i] >= 1))
				{
					st1.two1count++;
					//cout << "һ�ӻ��";

				}
				//�߶��ж�_T("00101 2"),_T("210100"),_T("010012"),_T("210010"),_T("10001"),_T("2010102")
				if ((adjempty[i] == 1 && jumpsame[i] == 1 && jumpempty[i] == 0 && adjempty[i + 4] >= 2) || (adjempty[i + 4] == 1 && jumpsame[i + 4] == 1 && jumpempty[i + 4] == 0 && adjempty[i] >= 2)
					|| (adjempty[i] == 0 && adjempty[i + 4] == 1 && jumpsame[i + 4] == 1 && jumpempty[i + 4] >= 2) || (adjempty[i + 4] == 0 && adjempty[i] == 1 && jumpsame[i] == 1 && jumpempty[i] >= 2)
					|| (adjempty[i] == 2 && jumpsame[i] == 1 && jumpempty[i] >= 0 && adjempty[i + 4] == 0) || (adjempty[i + 4] == 2 && jumpsame[i + 4] == 1 && jumpempty[i + 4] >= 0 && adjempty[i] == 0)
					|| (adjempty[i] == 0 && adjempty[i + 4] == 2 && jumpsame[i] == 1 && jumpempty[i] >= 1) || (adjempty[i + 4] == 0 && adjempty[i] == 2 && jumpsame[i + 4] == 1 && jumpempty[i + 4] >= 1)
					|| (adjempty[i] == 1 && jumpsame[i] == 1 && jumpempty[i] == 1 && jumpjumpsame[i] == 0) || (adjempty[i + 4] == 1 && jumpsame[i + 4] == 1 && jumpempty[i + 4] == 1 && jumpjumpsame[i + 4] == 0))
				{
					st1.two2count++;
				}
				//��һ��"001200", "002100", "020100", "000210", "000120", "210000", "000012"��
				if ((adjempty[i] == 0 && jumpempty[i] >= 2 && jumpsame[i + 4] == 0) || (adjempty[i + 4] == 0 && jumpempty[i + 4] >= 2 && jumpsame[i] == 0)
					|| (adjempty[i] >= 2 && adjempty[i + 4] == 1 && jumpsame[i + 4] == 0) || (adjempty[i + 4] >= 2 && adjempty[i] == 1 && jumpsame[i] == 0)
					|| (adjempty[i] >= 4 && adjempty[i + 4] == 0) || (adjempty[i + 4] >= 4 && adjempty[i] == 0))
				{
					st1.mian1++;
				}
				//��һ"010200", "002010", "020100", "001020", "201000", "000102", "000201"
				if (adjempty[i] >= 1 && adjempty[i + 4] >= 1)
				{
					//st1.huo1++;
				}
			}
		}
	}
	return NO_BAN;
}

int Game::EvaluateALL()//�����ֺ���   �����������һ�����ܣ���ÿһ������֮�󶼿��Ը���һ�¸�����ķ���
{
	int AIStateScore = 0;
	int PlayerStateScore = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (Board[i][j] != EMPTY)
			{
				if (Board[i][j] == m_computercolor)
				{
					PosScore[i][j] = evaluateAIPoint(i, j);
					AIStateScore = AIStateScore + evaluateAIPoint(i, j);
				}
				else if (Board[i][j] == m_personcolor)
				{
					PosScore[i][j] = evaluatePlayerPoint(i, j);
					PlayerStateScore = PlayerStateScore + evaluatePlayerPoint(i, j);
				}
				else
					continue;
			}
		}
	}
	return AIStateScore * attack - PlayerStateScore * defense;
}

int Game::evaluateAIPoint(int x, int y)
{
	Point np(x, y);
	int score_AI = 0;
	int AI_state = StateCheck(np, m_computercolor);
	state st_AI = st1;
	if ((AI_state == BWIN && m_computercolor == black) || (AI_state == WWIN && m_computercolor == white))
	{
		score_AI += 99999999;
	}
	if (m_computercolor == black && AI_state == THREE_THREE_BAN || AI_state == FOUR_FOUR_BAN || AI_state == LONG_BAN)
	{
		return  -99999999;
	}
	else if (AI_state == NO_BAN)
	{
		score_AI = st_AI.four1count * 100000 + st_AI.four21count * 10000 + st_AI.four2count * 5000 + st_AI.fivecount * 9000
			+ st_AI.three1count * 1000 + st_AI.three12count * 900 + st_AI.three2count * 50
			+ st_AI.two1count * 100 + st_AI.two2count * 10
			+ st_AI.mian1 * 1;

		if ((st_AI.four2count + st_AI.four21count) > 0 && st_AI.two1count > 0) {
			// �����ֻ��
			score_AI += 10000;
		}
		if (st_AI.two1count > 1) {
			// ˫���
			score_AI += 500;
		}
		if (m_computercolor == white && (st_AI.three1count + st_AI.three12count > 1)) {
			// ����������1
			score_AI += 50000;
		}
		if ((st_AI.four2count + st_AI.four21count + st_AI.fivecount > 0) && st_AI.three1count + st_AI.three12count > 0) {
			// ����(����)�ֻ���  �����и߷���
			score_AI += 70000;
		}
		if (st_AI.four2count + st_AI.four21count + st_AI.fivecount > 1) {
			// ����� ���ڸ�Σ�ռ�
			score_AI += 80000;
		}
		if (st_AI.fivecount > 1) {
			// ����� ���ڸ�Σ�ռ�
			//��Ȼ����û�л��ᵫ�ǻ���д����
			score_AI += 80000;
		}

		return score_AI;
	}
	return score_AI;
}

int Game::evaluatePlayerPoint(int x, int y)
{
	Point np(x, y);
	int score_Player = 0;
	int Player_state = StateCheck(np, m_personcolor);
	state st_Player = st1;
	if ((Player_state == BWIN && m_personcolor == black) || (Player_state == WWIN && m_personcolor == white))
	{
		score_Player += 99999999;
	}
	if (m_personcolor == black && Player_state == THREE_THREE_BAN || Player_state == FOUR_FOUR_BAN || Player_state == LONG_BAN)
	{
		return -99999999;
	}
	else if (Player_state == NO_BAN)
	{
		score_Player = st_Player.four1count * 100000 + st_Player.four21count * 10000 + st_Player.four2count * 5000 + st_Player.fivecount * 9000
			+ st_Player.three1count * 1000 + st_Player.three12count * 900 + st_Player.three2count * 50
			+ st_Player.two1count * 100 + st_Player.two2count * 10
			+ st_Player.mian1 * 1;
		if ((st_Player.four2count + st_Player.four21count > 0) && st_Player.two1count > 0) {
			// �����ֻ��
			score_Player += 10000;
		}
		if (st_Player.two1count > 1) {
			// ˫���
			score_Player += 500;
		}
		if (m_personcolor == white && (st_Player.three1count + st_Player.three12count > 1)) {
			// ����������1
			score_Player += 50000;
		}
		if ((st_Player.four2count + st_Player.four21count + st_Player.fivecount > 0) && (st_Player.three1count + st_Player.three12count > 0)) {
			// ����(����)�ֻ���
			score_Player += 70000;
		}
		if (st_Player.four2count + st_Player.four21count + st_Player.fivecount > 1) {
			// �����
			score_Player += 80000;
		}
		if (st_Player.fivecount > 1) {
			// ����� ���ڸ�Σ�ռ�
			//��Ȼ����û�л��ᵫ�ǻ���д����
			score_Player += 80000;
		}
		return score_Player;
	}
	return score_Player;
}

bool Game::CheckWin(int nx, int ny)
{
	Point np(nx, ny);
	int gen = Game::StateCheck(np, Board[nx][ny]);
	if (gen == THREE_THREE_BAN ||
		gen == FOUR_FOUR_BAN ||
		gen == LONG_BAN)
	{
		isBoardEnd = true;
	}
	else if (gen == WWIN || gen == BWIN)
	{
		isBoardEnd = true;
	}
	return isBoardEnd;
}

bool Game::CanPut(int nx, int ny)
{
	return inboard(nx, ny) && (Board[nx][ny] == 0);
}

bool Game::inboard(int nx, int ny)
{
	if (nx <0 || nx > N || ny <0 || ny > N)
		return false;
	else
		return true;
}