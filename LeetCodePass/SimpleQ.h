#pragma once
#include "QHeader.h"

class SimpleQ
{
public:
	SimpleQ();
	~SimpleQ();
	vector<int> numberOfLines(vector<int>& widths, string s);
	int maximumWealth(vector<vector<int>>& accounts);
	uint32_t reverseBits(uint32_t n);
	int hammingWeight(uint32_t n);
	string mostCommonWord(string paragraph, vector<string>& banned);
	vector<int> shortestToChar(string s, char c);
	string toGoatLatin(string sentence);
	int binaryGap(int n);
	int projectionArea(vector<vector<int>>& grid);
};

