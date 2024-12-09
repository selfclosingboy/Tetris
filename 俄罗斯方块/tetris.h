#pragma once
#include<vector>
#include <graphics.h>
#include "block.h"

using namespace std;
class tetris
{
public:
	tetris(int rows, int cols, int left, int top, int sizes);
	void init();
	void play();

private:
	void shuru();
	void xuanran();
	int shijianjiange();
	void drop();
	void clearline();

	void moveLeftRight(int offset);
	void rotate();
	void fenshuxianshi();
	void co();
	void youxijieshu();


private:
	int yanshi;
	bool update;
	bool go;

	vector<vector<int>> shuzu;
	int rowss;
	int colss;
	int leftmargin;
	int topmargin;
	int blocksize;
	IMAGE BEIJING;
	int dai;

	block* cb;
	block* nb;
	block bb;  //????

	int fengshu;
	int zuigaofen;

};

