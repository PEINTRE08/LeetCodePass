#include "stdafx.h"
#include "SimpleQ.h"


SimpleQ::SimpleQ()
{
}
SimpleQ::~SimpleQ()
{
}

/*
 *	Question :	写字符串需要的行数
 *	我们要把给定的字符串 S 从左到右写到每一行上，每一行的最大宽度为100个单位，
 *	如果我们在写某个字母的时候会使这行超过了100 个单位，那么我们应该把这个字母写到下一行。
 *	我们给定了一个数组 widths ，
 *	这个数组 widths[0] 代表 'a' 需要的单位， widths[1] 代表 'b' 需要的单位，...， widths[25] 代表 'z' 需要的单位。
 *	现在回答两个问题：至少多少行能放下S，以及最后一行使用的宽度是多少个单位？
 *
 *	Date	 : [ 2022/04/12 15:40:21]
 */
vector<int> SimpleQ::numberOfLines(vector<int>& widths, string s) {
	vector<int> ans(2, 0);
	int sum = 0;
	int nMax = 100;
	for (auto& ch : s)
	{
		int width = widths[ch - 'a'];
		if (sum + width > nMax)
		{
			ans[0]++;
			sum = width;
		}
		else
		{
			sum += width;
		}
	}
	ans[0] += 1;
	ans[1] = sum;
	return ans;
}