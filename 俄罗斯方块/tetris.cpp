#include "tetris.h"
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <iostream>
#include "block.h"
#include <fstream>

#include <mmsystem.h>
#pragma comment (lib , "winmm.lib")


#define RECORDER_FILE "ZUIGAO.txt"

int q = 100;
int n = 400;
int h = 200;
int e = 600;
int sh = 50;

tetris::tetris(int rows, int cols, int left, int top, int sizes)
{
	rowss = rows;
	colss = cols;
	leftmargin = left;
	topmargin = top;
	blocksize = sizes;
	for (int i = 0; i < rows; i++) {
		vector<int> xiaomap;
		for (int j = 0; j < cols; j++) {
			xiaomap.push_back(0);

		}
		shuzu.push_back(xiaomap);
	}
}

void tetris::init()
{
	mciSendString("play b.mp3 repeat", 0, 0, 0);
	fengshu = 0;
	dai = e;
	yanshi = dai;
	zuigaofen = 0;
	srand(time(NULL));

	loadimage(&BEIJING, "1.JPG");

	char data[13][7];
	for (int i = 0; i < rowss; i++) {
		for (int j = 0; j < colss; j++) {
			shuzu[i][j] = 0;
		}
	}
	go = false;
	ifstream file(RECORDER_FILE);

	 

}

void tetris::play()
{
	int t = 0;
	init();
	nb = new block; 
	cb = nb;
	nb = new block;

	while (1) {
		shuru();
		t += shijianjiange(); 
		if (t > yanshi) {
			
			t = 0;
			drop();
			update = true;
			

		}
		if (update) {
			update = false;
			xuanran();
			clearline();

		}
		if (go) {
			youxijieshu();
			system("pause");
			init();
		}
	}
}

void tetris::shuru()
{
	int dx = 0;
	bool rotateFlag = false;
	unsigned char ch = 0;
	

	if (_kbhit()) {
		ch = _getch();
		if (ch == 224) {
			ch = _getch();
			switch (ch) {
			case 72:
				rotateFlag = true;
				break;
			case 80:
				yanshi = 10;
				break;
			case 75:
				dx = -1;
				break;
			case 77:
				dx = 1;
				break;
			default:
				break;
			}
		}
	}

	if (dx != 0) {
		moveLeftRight(dx);
		update = true;
	}

	if (rotateFlag) {
		rotate();
		update = true;
	}
}

void tetris::xuanran()
{
	putimage(0, 0, &BEIJING);
	IMAGE** imgs = block::getim();

	BeginBatchDraw();
	for (int i = 0; i < rowss; i++) {
		for (int j = 0; j < colss; j++) {
			if (shuzu[i][j] == 0) continue;
			int x = i * blocksize + leftmargin;
			int y = j * blocksize + topmargin;
			putimage(x, y, imgs[shuzu[i][j] - 1]);
		}
	}


	cb->draw(100, 150);
	nb->draw(100, 0);

	fenshuxianshi();
	EndBatchDraw();
}

int tetris::shijianjiange()
{
	static unsigned long long lt = 0;
	unsigned long long ct = GetTickCount();
	if (lt == 0) {
		lt = ct;
		return 0;
	}
	else {
		int ret = ct - lt;
		lt = ct;
		return ret;
	}
	return 0;
}

void tetris::drop()
{	
	bb = *cb;
	cb->drop();
	if (!cb->finshuzu(shuzu)) {
		bb.guhua(shuzu);
		delete cb;
		cb = nb;
		nb = new block;
		co();
	

	}
	yanshi = dai;

}

void tetris::clearline()
{
	int a = colss - 1;
	int lines = 0;
	for (int i = colss - 1; i >= 0; i--) {
		int count = 0;
		for (int j = 0; j < rowss; j++) {
			if (shuzu[j][i]) {
				count++;
			}
			shuzu[j][a] = shuzu[j][i];
		}
		if (count < rowss) {
			a--;
		}
		else {
			lines++;
		}
	}
	if (lines > 0) {

		mciSendString("play a.mp3", 0, 0, 0);
		int fen[5] = { 10,30,60,100,150 };
		fengshu += fen[lines-1];
		update = true;
		if (fengshu > 100 && fengshu <= 400) {
			dai = n;
			zuigaofen = 1;
		}if (fengshu > 400 && fengshu <= 700) {
			dai = h;
			zuigaofen = 2;
		}if (fengshu > 700 && fengshu <= 1000) {
			dai = q;
			zuigaofen = 3;
		}if (fengshu > 1000) {
			dai = sh;
			zuigaofen = 4;
		}
	}
}

void tetris::moveLeftRight(int offset)
{
	bb = *cb;
	cb->movelr(offset);


	if (!cb->finshuzu(shuzu)) {
		*cb = bb;
	}

}

void tetris::rotate()
{	
	cb->gbt();
	bb = *cb;
	cb->retate();
	if (!cb->finshuzu(shuzu)) {
		*cb = bb;
	}
}

void tetris::fenshuxianshi()
{
	char fs[128];
	char zuigao[128];
	sprintf_s(fs, sizeof(fs), "%d", fengshu);
	sprintf_s(zuigao, sizeof(zuigao), "%d", zuigaofen);
	setbkmode(TRANSPARENT);
	settextstyle(30, 0, _T("Segoe UI Black"),0,0,0,0,0,0,0,0,ANTIALIASED_QUALITY,0,0);
	settextcolor(RGB(51, 255, 153));
	outtextxy(588, 73, fs);
	outtextxy(716, 73, zuigao);

	
}

void tetris::co()
{
	go = (cb->finshuzu(shuzu) == false);

}

void tetris::youxijieshu()
{
	IMAGE OVER;
	loadimage(&OVER, "g.JPG");
	putimage(0, 0, &OVER);
	mciSendString("stop b.mp3", 0, 0, 0);
	mciSendString("play c.mp3", 0, 0, 0);
}
