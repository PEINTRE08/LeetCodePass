// LeetCodePass.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SimpleQ.h"
#include "MediumQ.h"
#include "Tools.h"

int main()
{
	string strFilePath = "C:/Users/aryay/Desktop/Data.txt";

	vector<vector<int>> nums;
	int length = 0;
	readStream(strFilePath, nums, length);
// 	vector<int> nums;
// 	readStream(strFilePath, nums);
// 	string s = "bbbcccdddaaa";

	SimpleQ Spl;
	Spl.maximumWealth(nums);
// 	Spl.numberOfLines(nums, s);

	system("pause");
    return 0;
}

