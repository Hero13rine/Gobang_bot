//此cpp目的是存放对于局面的评估以及分数的确定
#include"Game.h"

int Game::StateCheck(const Point& a, int color)
{
	//数组下标代表方向
	int adjsame[8]; //记录与（x,y）相邻的连续黑棋子数
	int adjempty[8]; //记录adjsame后的相邻连续空位数
	int jumpsame[8]; //记录空位数后连续黑棋子数
	int jumpempty[8]; //记录jumpsame后的空位数
	int jumpjumpsame[8]; //记录jumpempty后连续的黑棋数
	int jumpjumpempty[8];//记录jumpjumpsame后连续的空格数
	//初始化
	for (int i = 0; i < 8; i++)
	{
		adjsame[i] = adjempty[i] = jumpsame[i] = 0;
		jumpempty[i] = jumpjumpsame[i] = jumpjumpempty[i] = 0;
	}
	//----------------------初始化结构体----------------------
	st1.isfour1 = false;//活四
	st1.isfour2 = false;//冲四
	st1.isthree = false;//活三
	st1.fivecount = 0;
	st1.four1count = 0;
	st1.four21count = 0;
	st1.four2count = 0;
	st1.three1count = 0;
	st1.three12count = 0;
	st1.three2count = 0;
	st1.two1count = 0;//活二数量统计
	st1.two2count = 0;//眠二数量统计
	st1.mian1 = 0;
	//st1.huo1 = 0;
	// ------------------------------------------------
	// p [横轴][纵轴]
	//棋盘盘面搜索-------------------------------------------------------------
	int _x, _y;

	//向左搜索  左
	{
		for (_y = a.y - 1; _y >= 0 && Board[a.x][_y] == color; _y--, adjsame[6]++);
		for (; _y >= 0 && Board[a.x][_y] == EMPTY; _y--, adjempty[6]++);
		for (; _y >= 0 && Board[a.x][_y] == color; _y--, jumpsame[6]++);
		for (; _y >= 0 && Board[a.x][_y] == EMPTY; _y--, jumpempty[6]++);
		for (; _y >= 0 && Board[a.x][_y] == color; _y--, jumpjumpsame[6]++);
		for (; _y >= 0 && Board[a.x][_y] == EMPTY; _y--, jumpjumpempty[6]++);
		//左下搜索
		for (_x = a.x + 1, _y = a.y - 1; a.x < 15 && _y >= 0 && Board[_x][_y] == color; _x++, _y--, adjsame[5]++);
		for (; _x < 15 && _y >= 0 && Board[_x][_y] == EMPTY; _x++, _y--, adjempty[5]++);
		for (; _x < 15 && _y >= 0 && Board[_x][_y] == color; _x++, _y--, jumpsame[5]++);
		for (; _x < 15 && _y >= 0 && Board[_x][_y] == EMPTY; _x++, _y--, jumpempty[5]++);
		for (; _x < 15 && _y >= 0 && Board[_x][_y] == color; _x++, _y--, jumpjumpsame[5]++);
		for (; _x < 15 && _y >= 0 && Board[_x][_y] == EMPTY; _x++, _y--, jumpjumpempty[5]++);
		//向下搜索
		for (_x = a.x + 1; _x < 15 && Board[_x][a.y] == color; _x++, adjsame[4]++);
		for (; _x < 15 && Board[_x][a.y] == EMPTY; _x++, adjempty[4]++);
		for (; _x < 15 && Board[_x][a.y] == color; _x++, jumpsame[4]++);
		for (; _x < 15 && Board[_x][a.y] == EMPTY; _x++, jumpempty[4]++);
		for (; _x < 15 && Board[_x][a.y] == color; _x++, jumpjumpsame[4]++);
		for (; _x < 15 && Board[_x][a.y] == EMPTY; _x++, jumpjumpempty[4]++);
		//向右下搜索
		for (_x = a.x + 1, _y = a.y + 1; _x < 15 && _y < 15 && Board[_x][_y] == color; _x++, _y++, adjsame[3]++);
		for (; _x < 15 && _y < 15 && Board[_x][_y] == EMPTY; _x++, _y++, adjempty[3]++);
		for (; _x < 15 && _y < 15 && Board[_x][_y] == color; _x++, _y++, jumpsame[3]++);
		for (; _x < 15 && _y < 15 && Board[_x][_y] == EMPTY; _x++, _y++, jumpempty[3]++);
		for (; _x < 15 && _y < 15 && Board[_x][_y] == color; _x++, _y++, jumpjumpsame[3]++);
		for (; _x < 15 && _y < 15 && Board[_x][_y] == EMPTY; _x++, _y++, jumpjumpempty[3]++);
		//向右搜索
		for (_y = a.y + 1; _y < 15 && Board[a.x][_y] == color; _y++, adjsame[2]++);
		for (; _y < 15 && Board[a.x][_y] == EMPTY; _y++, adjempty[2]++);
		for (; _y < 15 && Board[a.x][_y] == color; _y++, jumpsame[2]++);
		for (; _y < 15 && Board[a.x][_y] == EMPTY; _y++, jumpempty[2]++);
		for (; _y < 15 && Board[a.x][_y] == color; _y++, jumpjumpsame[2]++);
		for (; _y < 15 && Board[a.x][_y] == EMPTY; _y++, jumpjumpempty[2]++);
		//向右上搜索
		for (_x = a.x - 1, _y = a.y + 1; _x >= 0 && _y < 15 && Board[_x][_y] == color; _x--, _y++, adjsame[1]++);
		for (; _x >= 0 && _y < 15 && Board[_x][_y] == EMPTY; _x--, _y++, adjempty[1]++);
		for (; _x >= 0 && _y < 15 && Board[_x][_y] == color; _x--, _y++, jumpsame[1]++);
		for (; _x >= 0 && _y < 15 && Board[_x][_y] == EMPTY; _x--, _y++, jumpempty[1]++);
		for (; _x >= 0 && _y < 15 && Board[_x][_y] == color; _x--, _y++, jumpjumpsame[1]++);
		for (; _x >= 0 && _y < 15 && Board[_x][_y] == EMPTY; _x--, _y++, jumpjumpempty[1]++);
		//向上搜索
		for (_x = a.x - 1; _x >= 0 && Board[_x][a.y] == color; _x--, adjsame[0]++);
		for (; _x >= 0 && Board[_x][a.y] == EMPTY; _x--, adjempty[0]++);
		for (; _x >= 0 && Board[_x][a.y] == color; _x--, jumpsame[0]++);
		for (; _x >= 0 && Board[_x][a.y] == EMPTY; _x--, jumpempty[0]++);
		for (; _x >= 0 && Board[_x][a.y] == color; _x--, jumpjumpsame[0]++);
		for (; _x >= 0 && Board[_x][a.y] == EMPTY; _x--, jumpjumpempty[0]++);
		//向左上搜索
		for (_x = a.x - 1, _y = a.y - 1; _x >= 0 && _y >= 0 && Board[_x][_y] == color; _x--, _y--, adjsame[7]++);
		for (; _x >= 0 && _y >= 0 && Board[_x][_y] == EMPTY; _x--, _y--, adjempty[7]++);
		for (; _x >= 0 && _y >= 0 && Board[_x][_y] == color; _x--, _y--, jumpsame[7]++);
		for (; _x >= 0 && _y >= 0 && Board[_x][_y] == EMPTY; _x--, _y--, jumpempty[7]++);
		for (; _x >= 0 && _y >= 0 && Board[_x][_y] == color; _x--, _y--, jumpjumpsame[7]++);
		for (; _x >= 0 && _y >= 0 && Board[_x][_y] == EMPTY; _x--, _y--, jumpjumpempty[7]++);
		// ----------------------------------------------------------------------------------------------------------------
	}
	if (color == black)
	{
		for (int i = 0; i < 4; i++)
		{
			if (adjsame[i] + adjsame[i + 4] >= 5)//五子及以上相连
			{
				return LONG_BAN;//长连禁手
			}
			if (adjsame[i] + adjsame[i + 4] >= 4)
			{
				return BWIN;
			}
			if (adjsame[i] + adjsame[i + 4] == 3)//四子相连 ?1111?
			{
				//活四冲四判断
				//bool isfour1 = false;//活四
				//bool isfour2 = false;//冲四
				if (adjempty[i] > 0 && adjempty[i + 4] > 0)//011110
				{
					st1.four1count++;
				}
				if (adjempty[i + 4] > 0 && adjempty[i] == 0 || adjempty[i] > 0 && adjempty[i + 4] == 0) //211110
				{
					st1.four2count++;
				}

			}
			else if (adjsame[i] + adjsame[i + 4] == 2)//三子相连 ?000?    1000_01, _000_0_, 1000_0_1
			{
				//101【1】101同方向四四禁手
				if (adjempty[i] == 1 && jumpsame[i] == 1 && adjempty[i + 4] == 1 && jumpsame[i + 4] == 1)
				{
					return FOUR_FOUR_BAN;
				}
				//活四冲四检查
				//_T("10111"), _T("11101"), 
				if (adjempty[i] == 1 && jumpsame[i] == 1 || adjempty[i + 4] == 1 && jumpsame[i + 4] == 1)// ?0+000?  10+000_
				{
					st1.four21count++;
				}
				//活三检查
				//-----------------------------------------
				// x__OOO_x
				if ((adjempty[i] >= 2 && jumpsame[i] == 0) && (adjempty[i + 4] >= 1 && jumpsame[i + 4] == 0)
					|| (adjempty[i + 4] >= 2 && jumpsame[i + 4] == 0) && (adjempty[i] >= 1 && jumpsame[i] == 0))
				{
					st1.isthree = true;
					st1.three1count++;
				}

				//-----------------------------------------
				//眠三检查   X_OOO_X    211100  001112
				if ((adjempty[i] == 2 && jumpsame[i] == 0 && adjempty[i + 4] == 0 && jumpsame[i + 4] == 0)
					|| ((adjempty[i + 4] == 2 && jumpsame[i + 4] == 0) && (adjempty[i] == 0 && jumpsame[i] == 0))
					|| (adjempty[i] == 1 && jumpsame[i] == 0) && (adjempty[i + 4] == 1 && jumpsame[i + 4] == 0))
				{
					st1.three2count++;
				}
			}
			else if (adjsame[i] + adjsame[i + 4] == 1)  //二子相连 ?00?
			{
				//0101[1]010 同方向三三禁手(目前看好像没有这个规定)
				/*if (adjempty[i] == 1 && jumpsame[i] == 1 && jumpempty[i] >= 1 && adjempty[i + 4] == 1 && jumpsame[i + 4] == 1 && jumpempty[i + 4] >= 1)
				{
					return THREE_THREE_BAN;
				}*/

				//21101[1]0112 同方向四四禁手
				if (adjempty[i] == 1 && jumpsame[i] == 2 && adjempty[i + 4] == 1 && jumpsame[i + 4] == 2)
				{
					return FOUR_FOUR_BAN;
				}
				//活四冲四判断
				//_T("11011"),
				if (adjempty[i] == 1 && jumpsame[i] == 2 || adjempty[i + 4] == 1 && jumpsame[i + 4] == 2)  // ?00+00?
				{
					st1.four21count++;
				}
				//活三 X_00_0__X
				if ((adjempty[i] == 1 && jumpsame[i] == 1 && (jumpempty[i] > 1 || jumpempty[i] == 1 && jumpjumpsame[i] == 0) && (adjempty[i + 4] > 1 || adjempty[i + 4] == 1 && jumpsame[i + 4] == 0))
					|| (adjempty[i + 4] == 1 && jumpsame[i + 4] == 1 && (jumpempty[i + 4] > 1 || jumpempty[i + 4] == 1 && jumpjumpsame[i + 4] == 0) && (adjempty[i] > 1 || adjempty[i] == 1 && jumpsame[i] == 0)))
				{
					st1.three12count++;
				}
				//眠三   X00_0__X    X__00_0X    _OO__O_
				if (((adjempty[i] == 1 && jumpsame[i] == 1 && jumpempty[i] >= 2 && jumpjumpsame[i] == 0 && (adjempty[i + 4] == 0 && jumpsame[i + 4] == 0))
					|| (adjempty[i + 4] == 1 && jumpsame[i + 4] == 1 && jumpempty[i + 4] >= 2 && jumpjumpsame[i + 4] == 0 && (adjempty[i] == 0 && jumpsame[i] == 0)))
					|| ((adjempty[i] == 1 && jumpsame[i] == 1 && (jumpempty[i] == 0 && jumpjumpsame[i] == 0) && adjempty[i + 4] >= 2 && jumpsame[i + 4] == 0)
						|| ((adjempty[i + 4] == 1 && jumpsame[i + 4] == 1 && (jumpempty[i + 4] == 0 && jumpjumpsame[i + 4] == 0) && adjempty[i] >= 2 && jumpsame[i] == 0)))
					|| ((adjempty[i] == 2 && jumpsame[i] == 1 && jumpempty[i] >= 1 && adjempty[i + 4] >= 1)
						|| (adjempty[i + 4] == 2 && jumpsame[i + 4] == 1 && jumpempty[i + 4] >= 1 && adjempty[i] >= 1)))
				{
					st1.three2count++;
					//cout << "二子眠三";
				}
				//活二判断 _T("0001100"),_T("0011000")
				if ((adjempty[i] >= 2 && adjempty[i + 4] >= 3) || (adjempty[i + 4] >= 2 && adjempty[i] >= 3))
				{
					st1.two1count++;
				}
				//眠二判断 _T("000112"),_T("211000")_T("2011002"),_T("2001102")
				if ((adjempty[i] == 0 && adjempty[i + 4] >= 3) || (adjempty[i + 4] == 0 && adjempty[i] >= 3)
					|| (adjempty[i] == 1 && jumpsame[i] == 0 && adjempty[i + 4] >= 2 && jumpsame[i + 4] == 0)
					|| (adjempty[i + 4] == 1 && jumpsame[i + 4] == 0 && adjempty[i] >= 2 && jumpsame[i] == 0))
				{
					st1.two2count++;
				}
			}
			else if (adjsame[i] + adjsame[i + 4] == 0)  // 一子  ?0?
			{
				//1110【1】0111 同方向四四禁手
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
				//活三     x_0_00__x
				if ((adjempty[i] == 1 && jumpsame[i] == 2 && jumpempty[i] >= 1 && adjempty[i + 4] >= 1)
					|| (adjempty[i + 4] == 1 && jumpsame[i + 4] == 2 && jumpempty[i + 4] >= 1 && adjempty[i] >= 1))
				{
					st1.three12count++;
					//cout << "1活三 ";
					//cout << i << endl;
				}
				//眠三检查    x0_00__x  x__0_00x  _[O]_O_O_    _O_[O]_O_ 
				if (((adjempty[i] == 1 && jumpsame[i] == 2 && (jumpempty[i] >= 2 && jumpjumpsame[i] == 0) && (adjempty[i + 4] == 0 && jumpsame[i + 4] == 0))
					|| (adjempty[i + 4] == 1 && jumpsame[i + 4] == 2 && (jumpempty[i + 4] >= 2 && jumpjumpsame[i + 4] == 0) && (adjempty[i] == 0 && jumpsame[i] == 0)))
					|| (adjempty[i] == 1 && jumpsame[i] == 2 && (jumpempty[i] == 0 && jumpjumpsame[i] == 0) && adjempty[i + 4] >= 2 && jumpsame[i + 4] == 0)
					|| (adjempty[i + 4] == 1 && jumpsame[i + 4] == 2 && (jumpempty[i + 4] == 0 && jumpjumpsame[i + 4] == 0) && adjempty[i] >= 2 && jumpsame[i] == 0)
					|| ((adjempty[i] == 1 && jumpsame[i] == 1 && jumpempty[i] == 1 && jumpjumpsame[i] == 1 && jumpjumpempty[i] >= 1 && (adjempty[i + 4] >= 1))
						|| (adjempty[i + 4] == 1 && jumpsame[i + 4] == 1 && jumpempty[i + 4] == 1 && jumpjumpsame[i + 4] == 1 && jumpjumpempty[i] >= 1 && (adjempty[i + 4] >= 1))
						|| (adjempty[i] == 1 && jumpsame[i] == 1 && jumpempty[i] >= 1 && (adjempty[i + 4] == 1 && jumpsame[i + 4] == 1 && jumpempty[i + 4] >= 1))))
				{
					st1.three2count++;
					//cout << "一子眠三";
				}
				//活二判断 010[1]0 ->  0[1]010  01010
				if ((adjempty[i] == 1 && jumpsame[i] == 1 && jumpempty[i] >= 1 && adjempty[i + 4] >= 1) || (adjempty[i + 4] == 1 && jumpsame[i + 4] == 1 && jumpempty[i + 4] >= 1 && adjempty[i] >= 1))
				{
					st1.two1count++;
					//cout << "一子活二";
				}
				//010010
				if ((adjempty[i] == 2 && jumpsame[i] == 1 && jumpempty[i] >= 1 && adjempty[i + 4] >= 1) || (adjempty[i + 4] == 2 && jumpsame[i + 4] == 1 && jumpempty[i + 4] >= 1 && adjempty[i] >= 1))
				{
					st1.two1count++;
					//cout << "一子活二";
				}
				//眠二判断_T("00101 2"),_T("210100"),_T("010012"),_T("210010"),_T("10001"),_T("2010102")
				if ((adjempty[i] == 1 && jumpsame[i] == 1 && jumpempty[i] == 0 && adjempty[i + 4] >= 2) || (adjempty[i + 4] == 1 && jumpsame[i + 4] == 1 && jumpempty[i + 4] == 0 && adjempty[i] >= 2)
					|| (adjempty[i] == 0 && adjempty[i + 4] == 1 && jumpsame[i + 4] == 1 && jumpempty[i + 4] >= 2) || (adjempty[i + 4] == 0 && adjempty[i] == 1 && jumpsame[i] == 1 && jumpempty[i] >= 2)
					|| (adjempty[i] == 2 && jumpsame[i] == 1 && jumpempty[i] >= 0 && adjempty[i + 4] == 0) || (adjempty[i + 4] == 2 && jumpsame[i + 4] == 1 && jumpempty[i + 4] >= 0 && adjempty[i] == 0)
					|| (adjempty[i] == 0 && adjempty[i + 4] == 2 && jumpsame[i] == 1 && jumpempty[i] >= 1) || (adjempty[i + 4] == 0 && adjempty[i] == 2 && jumpsame[i + 4] == 1 && jumpempty[i + 4] >= 1)
					|| (adjempty[i] == 1 && jumpsame[i] == 1 && jumpempty[i] == 1 && jumpjumpsame[i] == 0) || (adjempty[i + 4] == 1 && jumpsame[i + 4] == 1 && jumpempty[i + 4] == 1 && jumpjumpsame[i + 4] == 0))
				{
					st1.two2count++;
				}
				//眠一（"001200", "002100", "020100", "000210", "000120", "210000", "000012"）
				if ((adjempty[i] == 0 && jumpempty[i] >= 2 && jumpsame[i + 4] == 0) || (adjempty[i + 4] == 0 && jumpempty[i + 4] >= 2 && jumpsame[i] == 0)
					|| (adjempty[i] >= 2 && adjempty[i + 4] == 1 && jumpsame[i + 4] == 0) || (adjempty[i + 4] >= 2 && adjempty[i] == 1 && jumpsame[i] == 0)
					|| (adjempty[i] >= 4 && adjempty[i + 4] == 0) || (adjempty[i + 4] >= 4 && adjempty[i] == 0))
				{
					st1.mian1++;
				}
				//活一"010200", "002010", "020100", "001020", "201000", "000102", "000201"
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
		//检查是否连五子，若无禁手连五子，则直接获胜。
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
			if (adjsame[i] + adjsame[i + 4] >= 4)//白子胜
			{
				return WWIN;
			}
		}
		for (int i = 0; i < 4; i++)
		{
			if (adjsame[i] + adjsame[i + 4] == 3)//四子相连 ?1111?
			{
				//活四冲四判断
				//bool isfour1 = false;//活四
				//bool isfour2 = false;//冲四
				if (adjempty[i] > 0 && adjempty[i + 4] > 0)//011110
				{
					st1.four1count++;
				}
				if (adjempty[i + 4] > 0 && adjempty[i] == 0 || adjempty[i] > 0 && adjempty[i + 4] == 0) //211110
				{
					st1.four2count++;
				}
			}
			else if (adjsame[i] + adjsame[i + 4] == 2)//三子相连 ?000?    1000_01, _000_0_, 1000_0_1
			{
				//冲五检查 ?[000]_00?
				if ((adjempty[i] == 1 && jumpsame[i] == 2)
					|| adjempty[i + 4] == 1 && jumpsame[i + 4] == 2)
				{
					st1.fivecount++;
				}
				//活四冲四检查
				//_T("10111"), _T("11101"), 
				if (adjempty[i] == 1 && jumpsame[i] == 1 || adjempty[i + 4] == 1 && jumpsame[i + 4] == 1)// ?0+000?  10+000_
				{
					st1.four21count++;
				}
				//活三检查
				//-----------------------------------------
				// x__OOO_x
				if ((adjempty[i] >= 2 && jumpsame[i] == 0) && (adjempty[i + 4] >= 1 && jumpsame[i + 4] == 0)
					|| (adjempty[i + 4] >= 2 && jumpsame[i + 4] == 0) && (adjempty[i] >= 1 && jumpsame[i] == 0))
				{
					st1.isthree = true;
					st1.three1count++;
				}
				//-----------------------------------------
				//眠三检查   X_OOO_X    211100  001112
				if ((adjempty[i] == 2 && jumpsame[i] == 0 && adjempty[i + 4] == 0 && jumpsame[i + 4] == 0)
					|| ((adjempty[i + 4] == 2 && jumpsame[i + 4] == 0) && (adjempty[i] == 0 && jumpsame[i] == 0))
					|| (adjempty[i] == 1 && jumpsame[i] == 0) && (adjempty[i + 4] == 1 && jumpsame[i + 4] == 0))
				{
					st1.three2count++;
				}
			}
			else if (adjsame[i] + adjsame[i + 4] == 1)  //二子相连 ?00?
			{
				//冲五检查 ?[00]_000?
				if ((adjempty[i] == 1 && jumpsame[i] == 3)
					|| adjempty[i + 4] == 1 && jumpsame[i + 4] == 3)
				{
					st1.fivecount++;
				}
				//活四冲四判断
				//_T("11011"),
				if (adjempty[i] == 1 && jumpsame[i] == 2 || adjempty[i + 4] == 1 && jumpsame[i + 4] == 2)  // ?00+00?
				{
					st1.four21count++;
				}
				//活三 X_00_0__X
				if ((adjempty[i] == 1 && jumpsame[i] == 1 && (jumpempty[i] > 1 || jumpempty[i] == 1 && jumpjumpsame[i] == 0) && (adjempty[i + 4] > 1 || adjempty[i + 4] == 1 && jumpsame[i + 4] == 0))
					|| (adjempty[i + 4] == 1 && jumpsame[i + 4] == 1 && (jumpempty[i + 4] > 1 || jumpempty[i + 4] == 1 && jumpjumpsame[i + 4] == 0) && (adjempty[i] > 1 || adjempty[i] == 1 && jumpsame[i] == 0)))
				{
					st1.three12count++;
				}
				//眠三   X00_0__X    X__00_0X    _OO__O_
				if (((adjempty[i] == 1 && jumpsame[i] == 1 && jumpempty[i] >= 2 && jumpjumpsame[i] == 0 && (adjempty[i + 4] == 0 && jumpsame[i + 4] == 0))
					|| (adjempty[i + 4] == 1 && jumpsame[i + 4] == 1 && jumpempty[i + 4] >= 2 && jumpjumpsame[i + 4] == 0 && (adjempty[i] == 0 && jumpsame[i] == 0)))
					|| ((adjempty[i] == 1 && jumpsame[i] == 1 && (jumpempty[i] == 0 && jumpjumpsame[i] == 0) && adjempty[i + 4] >= 2 && jumpsame[i + 4] == 0)
						|| ((adjempty[i + 4] == 1 && jumpsame[i + 4] == 1 && (jumpempty[i + 4] == 0 && jumpjumpsame[i + 4] == 0) && adjempty[i] >= 2 && jumpsame[i] == 0)))
					|| ((adjempty[i] == 2 && jumpsame[i] == 1 && jumpempty[i] >= 1 && adjempty[i + 4] >= 1)
						|| (adjempty[i + 4] == 2 && jumpsame[i + 4] == 1 && jumpempty[i + 4] >= 1 && adjempty[i] >= 1)))
				{
					st1.three2count++;
					//cout << "二子眠三";
				}
				//活二判断 _T("0001100"),_T("0011000")
				if ((adjempty[i] >= 2 && adjempty[i + 4] >= 3) || (adjempty[i + 4] >= 2 && adjempty[i] >= 3))
				{
					st1.two1count++;
				}
				//眠二判断 _T("000112"),_T("211000")_T("2011002"),_T("2001102")
				if ((adjempty[i] == 0 && adjempty[i + 4] >= 3)
					|| (adjempty[i + 4] == 0 && adjempty[i] >= 3) || (adjempty[i] == 1 && jumpsame[i] == 0 && adjempty[i + 4] >= 2 && jumpsame[i + 4] == 0)
					|| (adjempty[i + 4] == 1 && jumpsame[i + 4] == 0 && adjempty[i] >= 2 && jumpsame[i] == 0))
				{
					st1.two2count++;
				}
			}
			else if (adjsame[i] + adjsame[i + 4] == 0)  // 一子  ?0?
			{
				if (adjempty[i] == 1 && jumpsame[i] == 3) //?000+0?
				{
					st1.four21count++;
				}
				if (adjempty[i + 4] == 1 && jumpsame[i + 4] == 3)//?0+000?
				{
					st1.four21count++;
				}
				//活三     x_0_00_x
				if ((adjempty[i] == 1 && jumpsame[i] == 2 && jumpempty[i] >= 1 && adjempty[i + 4] >= 1)
					|| (adjempty[i + 4] == 1 && jumpsame[i + 4] == 2 && jumpempty[i + 4] >= 1 && adjempty[i] >= 1))
				{
					st1.three12count++;
					//cout << "1活三 ";
					//cout << i << endl;
				}
				//眠三检查    x0_00__x  x__0_00x  _[O]_O_O_    _O_[O]_O_ 
				if (((adjempty[i] == 1 && jumpsame[i] == 2 && (jumpempty[i] >= 2 && jumpjumpsame[i] == 0) && (adjempty[i + 4] == 0 && jumpsame[i + 4] == 0))
					|| (adjempty[i + 4] == 1 && jumpsame[i + 4] == 2 && (jumpempty[i + 4] >= 2 && jumpjumpsame[i + 4] == 0) && (adjempty[i] == 0 && jumpsame[i] == 0)))
					|| (adjempty[i] == 1 && jumpsame[i] == 2 && (jumpempty[i] == 0 && jumpjumpsame[i] == 0) && adjempty[i + 4] >= 2 && jumpsame[i + 4] == 0)
					|| (adjempty[i + 4] == 1 && jumpsame[i + 4] == 2 && (jumpempty[i + 4] == 0 && jumpjumpsame[i + 4] == 0) && adjempty[i] >= 2 && jumpsame[i] == 0)
					|| ((adjempty[i] == 1 && jumpsame[i] == 1 && jumpempty[i] == 1 && jumpjumpsame[i] == 1 && jumpjumpempty[i] >= 1 && (adjempty[i + 4] >= 1))
						|| (adjempty[i + 4] == 1 && jumpsame[i + 4] == 1 && jumpempty[i + 4] == 1 && jumpjumpsame[i + 4] == 1 && jumpjumpempty[i] >= 1 && (adjempty[i + 4] >= 1))
						|| (adjempty[i] == 1 && jumpsame[i] == 1 && jumpempty[i] >= 1 && (adjempty[i + 4] == 1 && jumpsame[i + 4] == 1 && jumpempty[i + 4] >= 1))))
				{
					st1.three2count++;
					//cout << "一子眠三";
				}
				//活二判断 010[1]0 ->  0[1]010  01010
				if ((adjempty[i] == 1 && jumpsame[i] == 1 && jumpempty[i] >= 1 && adjempty[i + 4] >= 1) || (adjempty[i + 4] == 1 && jumpsame[i + 4] == 1 && jumpempty[i + 4] >= 1 && adjempty[i] >= 1))
				{
					st1.two1count++;
					//cout << "一子活二";
				}
				//010010
				if ((adjempty[i] == 2 && jumpsame[i] == 1 && jumpempty[i] >= 1 && adjempty[i + 4] >= 1) || (adjempty[i + 4] == 2 && jumpsame[i + 4] == 1 && jumpempty[i + 4] >= 1 && adjempty[i] >= 1))
				{
					st1.two1count++;
					//cout << "一子活二";

				}
				//眠二判断_T("00101 2"),_T("210100"),_T("010012"),_T("210010"),_T("10001"),_T("2010102")
				if ((adjempty[i] == 1 && jumpsame[i] == 1 && jumpempty[i] == 0 && adjempty[i + 4] >= 2) || (adjempty[i + 4] == 1 && jumpsame[i + 4] == 1 && jumpempty[i + 4] == 0 && adjempty[i] >= 2)
					|| (adjempty[i] == 0 && adjempty[i + 4] == 1 && jumpsame[i + 4] == 1 && jumpempty[i + 4] >= 2) || (adjempty[i + 4] == 0 && adjempty[i] == 1 && jumpsame[i] == 1 && jumpempty[i] >= 2)
					|| (adjempty[i] == 2 && jumpsame[i] == 1 && jumpempty[i] >= 0 && adjempty[i + 4] == 0) || (adjempty[i + 4] == 2 && jumpsame[i + 4] == 1 && jumpempty[i + 4] >= 0 && adjempty[i] == 0)
					|| (adjempty[i] == 0 && adjempty[i + 4] == 2 && jumpsame[i] == 1 && jumpempty[i] >= 1) || (adjempty[i + 4] == 0 && adjempty[i] == 2 && jumpsame[i + 4] == 1 && jumpempty[i + 4] >= 1)
					|| (adjempty[i] == 1 && jumpsame[i] == 1 && jumpempty[i] == 1 && jumpjumpsame[i] == 0) || (adjempty[i + 4] == 1 && jumpsame[i + 4] == 1 && jumpempty[i + 4] == 1 && jumpjumpsame[i + 4] == 0))
				{
					st1.two2count++;
				}
				//眠一（"001200", "002100", "020100", "000210", "000120", "210000", "000012"）
				if ((adjempty[i] == 0 && jumpempty[i] >= 2 && jumpsame[i + 4] == 0) || (adjempty[i + 4] == 0 && jumpempty[i + 4] >= 2 && jumpsame[i] == 0)
					|| (adjempty[i] >= 2 && adjempty[i + 4] == 1 && jumpsame[i + 4] == 0) || (adjempty[i + 4] >= 2 && adjempty[i] == 1 && jumpsame[i] == 0)
					|| (adjempty[i] >= 4 && adjempty[i + 4] == 0) || (adjempty[i + 4] >= 4 && adjempty[i] == 0))
				{
					st1.mian1++;
				}
				//活一"010200", "002010", "020100", "001020", "201000", "000102", "000201"
				if (adjempty[i] >= 1 && adjempty[i + 4] >= 1)
				{
					//st1.huo1++;
				}
			}
		}
	}
	return NO_BAN;
}

int Game::EvaluateALL()//局面打分函数   这个函数还有一个功能，在每一次下子之后都可以更新一下各个点的分数
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
			// 冲四又活二
			score_AI += 10000;
		}
		if (st_AI.two1count > 1) {
			// 双活二
			score_AI += 500;
		}
		if (m_computercolor == white && (st_AI.three1count + st_AI.three12count > 1)) {
			// 活三数大于1
			score_AI += 50000;
		}
		if ((st_AI.four2count + st_AI.four21count + st_AI.fivecount > 0) && st_AI.three1count + st_AI.three12count > 0) {
			// 冲四(冲五)又活三  属于中高风险
			score_AI += 70000;
		}
		if (st_AI.four2count + st_AI.four21count + st_AI.fivecount > 1) {
			// 多冲四 属于高危险级
			score_AI += 80000;
		}
		if (st_AI.fivecount > 1) {
			// 多冲五 属于高危险级
			//虽然几乎没有机会但是还是写上了
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
			// 冲四又活二
			score_Player += 10000;
		}
		if (st_Player.two1count > 1) {
			// 双活二
			score_Player += 500;
		}
		if (m_personcolor == white && (st_Player.three1count + st_Player.three12count > 1)) {
			// 活三数大于1
			score_Player += 50000;
		}
		if ((st_Player.four2count + st_Player.four21count + st_Player.fivecount > 0) && (st_Player.three1count + st_Player.three12count > 0)) {
			// 冲四(冲五)又活三
			score_Player += 70000;
		}
		if (st_Player.four2count + st_Player.four21count + st_Player.fivecount > 1) {
			// 多冲四
			score_Player += 80000;
		}
		if (st_Player.fivecount > 1) {
			// 多冲五 属于高危险级
			//虽然几乎没有机会但是还是写上了
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