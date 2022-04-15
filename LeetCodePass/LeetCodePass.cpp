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
// 	int length = 0;
// 	readStream(strFilePath, nums, length);
// 	vector<int> nums;
// 	readStream(strFilePath, nums);
// 	string s = "[-324,[552],223]";
	uint32_t n = 4294967293;

	SimpleQ Spl;
	Spl.reverseBits(n);
// 	Spl.maximumWealth(nums);
// 	Spl.numberOfLines(nums, s);

// 	MediumQ Mdm;
// 	Mdm.deserialize(s);
	system("pause");
    return 0;
}

