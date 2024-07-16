#include"Open.h"
 //五手两打black方必胜
int Open::isHuayue(int x1, int y1, int x2, int y2, int x3, int y3) {
	x1++;
	x2++;
	x3++;
	y1++;
	y2++;
	y3++;
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 8 && x3 == 7 && y3 == 9) {      // 四种等效情况
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 8 && x3 == 7 && y3 == 7) {      // 四种等效情况
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 8 && x3 == 9 && y3 == 9) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 8 && x3 == 9 && y3 == 7) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 8 && y2 == 9 && x3 == 7 && y3 == 9) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 8 && y2 == 9 && x3 == 9 && y3 == 9) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 8 && x3 == 7 && y3 == 7) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 8 && x3 == 7 && y3 == 9) {
		return 1;
	}
	return 0;
}
int Open::isPuyue(int x1, int y1, int x2, int y2, int x3, int y3) {
	x1++;
	x2++;
	x3++;
	y1++;
	y2++;
	y3++;
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 7 && x3 == 9 && y3 == 9) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 7 && x3 == 7 && y3 == 7) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 9 && x3 == 7 && y3 == 9) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 9 && x3 == 9 && y3 == 7) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 9 && x3 == 7 && y3 == 7) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 9 && x3 == 9 && y3 == 9) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 7 && x3 == 7 && y3 == 9) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 7 && x3 == 9 && y3 == 7) {
		return 1;
	}
	return 0;
}
int Open::isYunyue(int x1, int y1, int x2, int y2, int x3, int y3) {
	x1++;
	x2++;
	x3++;
	y1++;
	y2++;
	y3++;
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 7 && x3 == 9 && y3 == 8) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 7 && x3 == 8 && y3 == 7) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 9 && x3 == 8 && y3 == 9) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 9 && x3 == 9 && y3 == 8) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 9 && x3 == 7 && y3 == 8) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 9 && x3 == 8 && y3 == 9) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 7 && x3 == 8 && y3 == 7) {
		return 1;
	}if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 7 && x3 == 7 && y3 == 8) {
		return 1;
	}
	return 0;
}
int Open::isYuyue(int x1, int y1, int x2, int y2, int x3, int y3) {
	x1++;
	x2++;
	x3++;
	y1++;
	y2++;
	y3++;
	if (x1 == 8 && y1 == 8 && x2 == 8 && y2 == 7 && x3 == 9 && y3 == 8) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 8 && y2 == 7 && x3 == 7 && y3 == 8) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 8 && x3 == 8 && y3 == 9) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 8 && x3 == 8 && y3 == 7) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 8 && y2 == 9 && x3 == 7 && y3 == 8) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 8 && y2 == 9 && x3 == 9 && y3 == 8) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 8 && x3 == 8 && y3 == 7) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 8 && x3 == 8 && y3 == 9) {
		return 1;
	}
	return 0;
}
int Open::isXiyue(int x1, int y1, int x2, int y2, int x3, int y3) {
	x1++;
	x2++;
	x3++;
	y1++;
	y2++;
	y3++;
	if (x1 == 8 && y1 == 8 && x2 == 8 && y2 == 7 && x3 == 9 && y3 == 6) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 8 && y2 == 7 && x3 == 7 && y3 == 6) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 8 && x3 == 10 && y3 == 9) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 8 && x3 == 10 && y3 == 7) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 8 && y2 == 9 && x3 == 7 && y3 == 10) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 8 && y2 == 9 && x3 == 9 && y3 == 10) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 8 && x3 == 6 && y3 == 7) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 8 && x3 == 6 && y3 == 10) {
		return 1;
	}
	return 0;
}
int Open::isXiayue(int x1, int y1, int x2, int y2, int x3, int y3) {
	x1++;
	x2++;
	x3++;
	y1++;
	y2++;
	y3++;
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 7 && x3 == 10 && y3 == 7) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 7 && x3 == 9 && y3 == 6) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 9 && x3 == 9 && y3 == 10) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 9 && x3 == 10 && y3 == 9) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 9 && x3 == 6 && y3 == 9) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 9 && x3 == 7 && y3 == 10) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 7 && x3 == 7 && y3 == 6) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 7 && x3 == 6 && y3 == 7) {
		return 1;
	}
	return 0;
}
int Open::isShuiyue(int x1, int y1, int x2, int y2, int x3, int y3) {
	x1++;
	x2++;
	x3++;
	y1++;
	y2++;
	y3++;
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 7 && x3 == 10 && y3 == 9) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 7 && x3 == 7 && y3 == 6) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 9 && x3 == 7 && y3 == 10) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 9 && x3 == 10 && y3 == 7) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 9 && x3 == 6 && y3 == 7) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 9 && x3 == 9 && y3 == 10) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 7 && x3 == 9 && y3 == 6) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 7 && x3 == 6 && y3 == 9) {
		return 1;
	}
	return 0;
}
int Open::isLanyue(int x1, int y1, int x2, int y2, int x3, int y3) {
	x1++;
	x2++;
	x3++;
	y1++;
	y2++;
	y3++;
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 7 && x3 == 9 && y3 == 10) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 7 && x3 == 6 && y3 == 7) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 9 && x3 == 6 && y3 == 9) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 9 && x3 == 9 && y3 == 6) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 9 && x3 == 7 && y3 == 6) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 9 && x3 == 10 && y3 == 9) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 7 && x3 == 10 && y3 == 7) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 7 && x3 == 7 && y3 == 10) {
		return 1;
	}
	return 0;
}
int Open::isJinxing(int x1, int y1, int x2, int y2, int x3, int y3) {
	x1++;
	x2++;
	x3++;
	y1++;
	y2++;
	y3++;
	if (x1 == 8 && y1 == 8 && x2 == 8 && y2 == 7 && x3 == 10 && y3 == 8) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 8 && y2 == 7 && x3 == 6 && y3 == 8) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 8 && x3 == 8 && y3 == 10) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 8 && x3 == 8 && y3 == 6) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 8 && y2 == 9 && x3 == 6 && y3 == 8) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 8 && y2 == 9 && x3 == 10 && y3 == 8) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 8 && x3 == 8 && y3 == 6) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 8 && x3 == 8 && y3 == 10) {
		return 1;
	}
	return 0;
}
int Open::isHengxing(int x1, int y1, int x2, int y2, int x3, int y3) {
	x1++;
	x2++;
	x3++;
	y1++;
	y2++;
	y3++;
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 7 && x3 == 10 && y3 == 8) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 7 && x3 == 8 && y3 == 6) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 9 && x3 == 8 && y3 == 10) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 9 && x3 == 10 && y3 == 8) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 9 && x3 == 6 && y3 == 8) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 9 && x3 == 8 && y3 == 10) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 7 && x3 == 8 && y3 == 6) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 7 && x3 == 6 && y3 == 8) {
		return 1;
	}
	return 0;
}
int Open::isHanxing(int x1, int y1, int x2, int y2, int x3, int y3) {
	x1++;
	x2++;
	x3++;
	y1++;
	y2++;
	y3++;
	if (x1 == 8 && y1 == 8 && x2 == 8 && y2 == 7 && x3 == 8 && y3 == 6) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 8 && x3 == 10 && y3 == 8) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 8 && y2 == 9 && x3 == 8 && y3 == 10) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 8 && x3 == 6 && y3 == 8) {
		return 1;
	}
	return 0;
}
int Open::isMingxing(int x1, int y1, int x2, int y2, int x3, int y3) {
	x1++;
	x2++;
	x3++;
	y1++;
	y2++;
	y3++;
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 7 && x3 == 8 && y3 == 10) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 7 && x3 == 6 && y3 == 8) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 9 && x3 == 6 && y3 == 8) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 9 && x3 == 8 && y3 == 6) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 9 && x3 == 8 && y3 == 6) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 9 && x3 == 10 && y3 == 8) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 7 && x3 == 10 && y3 == 8) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 7 && x3 == 8 && y3 == 10) {
		return 1;
	}
	return 0;
}
//五手两打白方必胜
int Open::isYouxing(int x1, int y1, int x2, int y2, int x3, int y3) {
	x1++;
	x2++;
	x3++;
	y1++;
	y2++;
	y3++;
	if (x1 == 8 && y1 == 8 && x2 == 8 && y2 == 7 && x3 == 10 && y3 == 10) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 8 && y2 == 7 && x3 == 6 && y3 == 10) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 8 && x3 == 6 && y3 == 10) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 8 && x3 == 6 && y3 == 10) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 8 && x3 == 6 && y3 == 6) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 8 && y2 == 9 && x3 == 6 && y3 == 6) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 8 && y2 == 9 && x3 == 10 && y3 == 6) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 8 && x3 == 10 && y3 == 6) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 8 && x3 == 10 && y3 == 10) {
		return 1;
	}
	return 0;
}
int Open::isHuixing(int x1, int y1, int x2, int y2, int x3, int y3) {
	x1++;
	x2++;
	x3++;
	y1++;
	y2++;
	y3++;
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 7 && x3 == 6 && y3 == 10) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 9 && x3 == 6 && y3 == 6) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 9 && x3 == 10 && y3 == 6) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 7 && x3 == 10 && y3 == 10) {
		return 1;
	}
	return 0;
}
//五手两打平衡
int Open::isRuixing(int x1, int y1, int x2, int y2, int x3, int y3) {
	x1++;
	x2++;
	x3++;
	y1++;
	y2++;
	y3++;
	if (x1 == 8 && y1 == 8 && x2 == 8 && y2 == 7 && x3 == 8 && y3 == 10) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 8 && x3 == 6 && y3 == 8) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 8 && y2 == 9 && x3 == 8 && y3 == 6) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 8 && x3 == 10 && y3 == 8) {
		return 1;
	}
	return 0;
}
int Open::isChangxing(int x1, int y1, int x2, int y2, int x3, int y3) {
	x1++;
	x2++;
	x3++;
	y1++;
	y2++;
	y3++;
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 7 && x3 == 10 && y3 == 6) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 9 && x3 == 10 && y3 == 10) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 9 && x3 == 6 && y3 == 10) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 7 && x3 == 6 && y3 == 6) {
		return 1;
	}
	return 0;
}
int Open::isShuxing(int x1, int y1, int x2, int y2, int x3, int y3) {
	x1++;
	x2++;
	x3++;
	y1++;
	y2++;
	y3++;
	if (x1 == 8 && y1 == 8 && x2 == 8 && y2 == 7 && x3 == 10 && y3 == 6) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 8 && y2 == 7 && x3 == 6 && y3 == 6) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 8 && x3 == 10 && y3 == 10) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 8 && x3 == 10 && y3 == 6) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 8 && y2 == 9 && x3 == 6 && y3 == 10) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 8 && x3 == 6 && y3 == 6) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 8 && x3 == 6 && y3 == 10) {
		return 1;
	}
	return 0;
}
//五手两打黑优
int Open::isXieyue(int x1, int y1, int x2, int y2, int x3, int y3) {
	x1++;
	x2++;
	x3++;
	y1++;
	y2++;
	y3++;
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 7 && x3 == 7 && y3 == 9) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 9 && x3 == 7 && y3 == 7) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 9 && x3 == 9 && y3 == 7) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 7 && x3 == 9 && y3 == 9) {
		return 1;
	}
	return 0;
}
int Open::isQiuyue(int x1, int y1, int x2, int y2, int x3, int y3) {
	x1++;
	x2++;
	x3++;
	y1++;
	y2++;
	y3++;
	if (x1 == 8 && y1 == 8 && x2 == 8 && y2 == 7 && x3 == 9 && y3 == 9) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 8 && y2 == 7 && x3 == 7 && y3 == 9) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 8 && x3 == 7 && y3 == 9) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 8 && x3 == 7 && y3 == 7) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 8 && y2 == 9 && x3 == 7 && y3 == 7) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 8 && y2 == 9 && x3 == 9 && y3 == 7) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 8 && x3 == 9 && y3 == 7) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 8 && x3 == 9 && y3 == 9) {
		return 1;
	}
	return 0;
}
int Open::isSongyue(int x1, int y1, int x2, int y2, int x3, int y3) {
	x1++;
	x2++;
	x3++;
	y1++;
	y2++;
	y3++;
	if (x1 == 8 && y1 == 8 && x2 == 8 && y2 == 7 && x3 == 8 && y3 == 9) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 8 && x3 == 7 && y3 == 8) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 8 && y2 == 9 && x3 == 8 && y3 == 7) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 8 && x3 == 9 && y3 == 8) {
		return 1;
	}
	return 0;
}
int Open::isMingyue(int x1, int y1, int x2, int y2, int x3, int y3) {
	x1++;
	x2++;
	x3++;
	y1++;
	y2++;
	y3++;
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 7 && x3 == 7 && y3 == 10) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 7 && x3 == 6 && y3 == 9) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 9 && x3 == 6 && y3 == 7) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 9 && x3 == 7 && y3 == 6) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 9 && x3 == 9 && y3 == 6) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 9 && x3 == 10 && y3 == 7) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 7 && x3 == 10 && y3 == 9) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 7 && x3 == 9 && y3 == 10) {
		return 1;
	}
	return 0;
}
int Open::isYinyue(int x1, int y1, int x2, int y2, int x3, int y3) {
	x1++;
	x2++;
	x3++;
	y1++;
	y2++;
	y3++;
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 7 && x3 == 8 && y3 == 9) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 7 && x3 == 7 && y3 == 8) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 9 && x3 == 7 && y3 == 8) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 9 && x3 == 8 && y3 == 7) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 9 && x3 == 8 && y3 == 7) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 9 && x3 == 9 && y3 == 8) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 7 && x3 == 9 && y3 == 8) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 7 && x3 == 8 && y3 == 9) {
		return 1;
	}
	return 0;
}
int Open::isCanyue(int x1, int y1, int x2, int y2, int x3, int y3) {
	x1++;
	x2++;
	x3++;
	y1++;
	y2++;
	y3++;
	if (x1 == 8 && y1 == 8 && x2 == 8 && y2 == 7 && x3 == 10 && y3 == 7) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 8 && y2 == 7 && x3 == 6 && y3 == 7) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 8 && x3 == 9 && y3 == 10) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 8 && x3 == 9 && y3 == 6) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 8 && y2 == 9 && x3 == 6 && y3 == 9) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 8 && y2 == 9 && x3 == 10 && y3 == 9) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 8 && x3 == 7 && y3 == 6) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 8 && x3 == 7 && y3 == 10) {
		return 1;
	}
	return 0;
}
int Open::isXinyue(int x1, int y1, int x2, int y2, int x3, int y3) {
	x1++;
	x2++;
	x3++;
	y1++;
	y2++;
	y3++;
	if (x1 == 8 && y1 == 8 && x2 == 8 && y2 == 7 && x3 == 10 && y3 == 9) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 8 && y2 == 7 && x3 == 6 && y3 == 9) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 8 && x3 == 7 && y3 == 10) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 8 && x3 == 7 && y3 == 6) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 8 && y2 == 9 && x3 == 6 && y3 == 7) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 8 && y2 == 9 && x3 == 10 && y3 == 7) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 8 && x3 == 9 && y3 == 6) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 8 && x3 == 9 && y3 == 10) {
		return 1;
	}
	return 0;
}
int Open::isShanyue(int x1, int y1, int x2, int y2, int x3, int y3) {
	x1++;
	x2++;
	x3++;
	y1++;
	y2++;
	y3++;
	if (x1 == 8 && y1 == 8 && x2 == 8 && y2 == 7 && x3 == 9 && y3 == 10) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 8 && y2 == 7 && x3 == 7 && y3 == 10) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 8 && x3 == 6 && y3 == 9) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 8 && x3 == 6 && y3 == 7) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 8 && y2 == 9 && x3 == 7 && y3 == 6) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 8 && y2 == 9 && x3 == 9 && y3 == 6) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 8 && x3 == 10 && y3 == 7) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 8 && x3 == 10 && y3 == 9) {
		return 1;
	}
	return 0;
}
//五手两打白优
int Open::isLiuxing(int x1, int y1, int x2, int y2, int x3, int y3) {
	x1++;
	x2++;
	x3++;
	y1++;
	y2++;
	y3++;
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 7 && x3 == 10 && y3 == 10) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 7 && x3 == 6 && y3 == 6) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 9 && x3 == 6 && y3 == 10) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 9 && y2 == 9 && x3 == 10 && y3 == 6) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 9 && x3 == 6 && y3 == 6) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 9 && x3 == 10 && y3 == 10) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 7 && x3 == 10 && y3 == 6) {
		return 1;
	}
	if (x1 == 8 && y1 == 8 && x2 == 7 && y2 == 7 && x3 == 6 && y3 == 10) {
		return 1;
	}
	return 0;
}