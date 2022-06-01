#pragma once
#include "QHeader.h"

class HardQ
{
public:
	HardQ();
	~HardQ();
	int findKthNumber(int m, int n, int k);
	int cutOffTree(vector<vector<int>>& forest);
	vector<int> fallingSquares(vector<vector<int>>& positions);
	string alienOrder(vector<string>& words);
};

