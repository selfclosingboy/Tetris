#include "block.h"
#include <stdlib.h>

IMAGE* block::xiaos[9] = { NULL , };
int block::size = 50;

block::block()
{
	if (xiaos[0] == NULL) {
		IMAGE xiaoxiao;
		loadimage(&xiaoxiao, "2.jpg");
		int a = 0;
		SetWorkingImage(&xiaoxiao);
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				xiaos[a] = new IMAGE;
				getimage(xiaos[a], 3+i*size, 3 + j*size, size, size);
				a++;
			}


		}
		SetWorkingImage();

	}
	int blocks[9][4] = {
		0,2,4,6,
		1,3,5,7, // I
		2,4,5,7, // Z 1型
		3,5,4,6, // Z 2型
		3,5,4,7, // T
		2,3,5,7, // L
		3,5,7,6, // J
		2,3,4,5, // 田
		0,1,2,3,
	};
	fangkuai = 1 + rand() % 9;

	for (int i = 0; i < 4; i++) {
		int value = blocks[fangkuai - 1][i];
		xiaokuai[i].row = value / 2;
		xiaokuai[i].col = value % 2;

	}
	xiao = xiaos[fangkuai - 1];

}

void block::drop()
{
	for (int i = 0; i < 4; i++) {
		xiaokuai[i].col++;
	}
}

void block::movelr(int offset)
{
	for (int i = 0; i < 4; i++) {
		xiaokuai[i].row += offset;
	}

}


void block::retate()
{
	Point p = xiaokuai[1];
	for (int i = 0; i < 4; i++) {
		Point tmp = xiaokuai[i];
		xiaokuai[i].col = p.col - tmp.row + p.row;
		xiaokuai[i].row = p.row + tmp.col - p.col;
	}
}

void block::draw(int leftmargin, int topmargin)
{

	for (int i = 0; i < 4; i++) {
		int x = leftmargin + xiaokuai[i].row*size;
		int y = topmargin + xiaokuai[i].col*size;
		putimage(x, y, xiao);
	}
}

IMAGE** block::getim()
{
	return xiaos;
}

int block::gbt()
{
	return fangkuai;
}

block& block::operator=(const block& other)
{
	if (this == &other) return *this;

	this->fangkuai = other.fangkuai;
	for (int i = 0; i < 4; i++) {
		this->xiaokuai[i] = other.xiaokuai[i];
	}
}

bool block::finshuzu(const vector<vector<int>>& shuzu)
{
	int rows = shuzu.size();
	int cols = shuzu[0].size();
	for (int i=0; i < 4; i++) {
		if (xiaokuai[i].col < 0 || xiaokuai[i].col >= cols || xiaokuai[i].row < 0 || xiaokuai[i].row >= rows || shuzu[xiaokuai[i].row][xiaokuai[i].col]) {
			return false;
		}
	}
	return true;
}

void block::guhua(vector<vector<int>>& shuzu)
{
	for (int i = 0; i < 4; i++) {
		shuzu[xiaokuai[i].row][xiaokuai[i].col] = fangkuai;
	}
}
