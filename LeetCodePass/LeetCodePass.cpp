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
	vector<int> nums;
// 	vector<string> s;
// 	s.push_back("hit");
// 	int length = 22;
// 	readStream(strFilePath, nums, length);
	readStream(strFilePath, nums);
// 	string s = "I speak Goat Latin";
// 	uint32_t n = 4294967293;

// 	SimpleQ Spl;
	Solution s(nums);
	s.pick(3);
	s.pick(1);
	s.pick(3);
// 	MediumQ Mdm;

	system("pause");
    return 0;
}

