// LeetCodePass.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SimpleQ.h"
#include "MediumQ.h"
#include "Tools.h"

int main()
{
	string strFilePath = "C:/Users/aryay/Desktop/Data.txt";

	vector<int> nums;
	readStream(strFilePath, nums);
	string s = "bbbcccdddaaa";

	SimpleQ Spl;
	Spl.numberOfLines(nums, s);

	system("pause");
    return 0;
}

