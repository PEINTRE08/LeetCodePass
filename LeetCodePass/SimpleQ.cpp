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

/*
 *	Question : 颠倒二进制位
 *	颠倒给定的 32 位无符号整数的二进制位。
 *
 *	Date	 : [ 2022/04/15 15:23:10 ]
 */
/*	与或（^）：使特定位翻转。将要翻转的位与1异或运算，如翻转1010的1:0位：1010^0011=1001
 *	位运算分治
 *	const uint32_t M1 = 0x55555555; // 01010101010101010101010101010101
 *	const uint32_t M2 = 0x33333333; // 00110011001100110011001100110011
 *	const uint32_t M4 = 0x0f0f0f0f; // 00001111000011110000111100001111
 *	const uint32_t M8 = 0x00ff00ff; // 00000000111111110000000011111111
 *	 n = n >> 1 & M1 | (n & M1) << 1;
 *	 n = n >> 2 & M2 | (n & M2) << 2;
 *	 n = n >> 4 & M4 | (n & M4) << 4;
 *	 n = n >> 8 & M8 | (n & M8) << 8;
 *	 return n >> 16 | n << 16;
 */
uint32_t SimpleQ::reverseBits(uint32_t n) {
	int i = 1;
	uint32_t ans = 0;
	int nindex = 0;
	while (nindex < 32)
	{
		ans = ans | (n & i);
		if (nindex < 31)
		{
			n >>= 1;
			ans <<= 1;
		}
		nindex++;
	}
	return ans;
}

/*
 *	Question : 位1的个数
 *	编写一个函数，输入是一个无符号整数（以二进制串的形式），返回其二进制表达式中数字位数为 '1' 的个数（也被称为汉明重量）。
 *
 *	Date	 : [ 2022/04/15 16:03:45 ]
 */
/*
 *	// 计算32位二进制的汉明重量
 *	int32_t swar(int32_t i)
 *	{
 *		i = (i & 0x55555555) + ((i >> 1) & 0x55555555);
 *		i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
 *		i = (i & 0x0F0F0F0F) + ((i >> 4) & 0x0F0F0F0F);
 *		i = (i * (0x01010101) >> 24);
 *		return i
 *	}
 */
int SimpleQ::hammingWeight(uint32_t n) {
	int ans = 0;
	for (int i = 0; i < 32 && n > 0; i++)
	{
		if (n & 1 == 1)
		{
			ans++;
		}
		n >>= 1;
	}
	return ans;
}

/*
 *	Question : 最常见的单词
 *	给定一个段落 (paragraph) 和一个禁用单词列表 (banned)。返回出现次数最多，同时不在禁用列表中的单词。
 *	题目保证至少有一个词不在禁用列表中，而且答案唯一。
 *	禁用列表中的单词用小写字母表示，不含标点符号。段落中的单词不区分大小写。答案都是小写字母。
 *
 *	Date	 : [ 2022/04/18 15:36:44 ]
 */
string SimpleQ::mostCommonWord(string paragraph, vector<string>& banned) {
	string ans = "";
	unordered_map<string, int> mp;
	string s = "", strbanned = "";
	int nMax = 0;
	for (auto& str : banned)
	{
		strbanned += str;
		strbanned += " ";
	}
	paragraph += ".";
	for (auto& ch : paragraph)
	{
		if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
		{
			s += tolower(ch);
		}
		else
		{
			if (s != "" && strbanned.find(s) == -1)
			{
				mp[s]++;
				if (nMax < mp[s])
				{
					nMax = mp[s];
					ans = s;
				}
			}
			s = "";
		}
	}
	return ans;
}

/*
 *	Question : 字符的最短距离
 *	给你一个字符串 s 和一个字符 c ，且 c 是 s 中出现过的字符。
 *	返回一个整数数组 answer ，其中 answer.length == s.length 且 answer[i] 是 s 中从下标 i 到离它 最近 的字符 c 的 距离 。
 *	两个下标 i 和 j 之间的 距离 为 abs(i - j) ，其中 abs 是绝对值函数。
 *
 *	Date	 : [ 2022/04/19 14:59:53 ]
 */
vector<int> SimpleQ::shortestToChar(string s, char c) {
	int nlen = s.length();
	vector<int> answer(nlen, 0);
	vector<int> vec;
	for (int i = 0; i < nlen; i++)
	{
		if (s[i] == c)
		{
			vec.push_back(i);
		}
	}
	for (int i = 0, k = 0; i < vec.back() && k < vec.size(); i++)
	{
		if (i == vec[k])
		{
			k++;
			continue;
		}
		answer[i] = abs(vec[k] - i);
	}
	for (int i = nlen - 1, k = vec.size() - 1; i >= 0 && k >= 0; i--)
	{
		if (i == vec[k])
		{
			k--;
			continue;
		}
		if (k == vec.size() - 1)
		{
			answer[i] = abs(vec[k] - i);
		}
		else
		{
			answer[i] = abs(vec[k] - i) < answer[i] ? abs(vec[k] - i) : answer[i];
		}
	}
	return answer;
}

