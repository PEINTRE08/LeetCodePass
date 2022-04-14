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

/*
 *	Question : 最富有客户的资产总量
 *	给你一个 m x n 的整数网格 accounts ，其中 accounts[i][j] 是第 i​​​​​​​​​​​​ 位客户在第 j 家银行托管的资产数量。
 *	返回最富有客户所拥有的 资产总量 。
 *	客户的 资产总量 就是他们在各家银行托管的资产数量之和。最富有客户就是 资产总量 最大的客户。
 *
 *	Date	 : [ 2022/04/14 16:28:17 ]
 */
int SimpleQ::maximumWealth(vector<vector<int>>& accounts) {
	int m = accounts.size(); // m customer
	int n = accounts[0].size(); // n bank
	int nMaxBank = 100;
	int nMaxW = 0, nSum = 0;
	for (auto& customer : accounts)
	{
// 		nMaxW = max(nMaxW, accumulate(customer.begin(), customer.end(), 0));
		nSum = 0;
		for (int i = 0; i < n; i++)
		{
			nSum += customer[i];
			if (nSum + (n - 1 - i) * 100 < nMaxW)
			{
				break;
			}
		}
		nMaxW = nMaxW < nSum ? nSum : nMaxW;
	}
	return nMaxW;
}