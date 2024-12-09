#pragma once
#include <graphics.h>
#include <vector>
using namespace std;

struct Point {
	int row;
	int col;
};

class block
{
public:
	block();
	void drop();
	void movelr(int offset);
	void retate();
	void draw(int leftmargin,int topmargin);
	static IMAGE** getim();
	int gbt();

	block& operator =(const block& other);

	bool finshuzu(const vector<vector<int >> &shuzu);

	void guhua(vector<vector<int >>& shuzu);

private:
	int fangkuai;
	Point xiaokuai[4];

	IMAGE *xiao;

	static IMAGE* xiaos[9];
	static int size;

};

