// LeetCodePass.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SimpleQ.h"
#include "MediumQ.h"
#include "Tools.h"

int main()
{
	string strFilePath = "C:/Users/aryay/Desktop/Data.txt";

// 	vector<vector<int>> nums;
// 	vector<int> nums;
	vector<string> s;
	s.push_back("hit");
// 	int length = 0;
// 	readStream(strFilePath, nums, length);
// 	readStream(strFilePath, nums);
// 	string s = "[-324,[552],223]";
// 	uint32_t n = 4294967293;

	SimpleQ Spl;
	Spl.mostCommonWord("Bob hit a ball, the hit BALL flew far after it was hit", s);

// 	MediumQ Mdm;
// 	Mdm.deserialize(s);
	system("pause");
    return 0;
}

