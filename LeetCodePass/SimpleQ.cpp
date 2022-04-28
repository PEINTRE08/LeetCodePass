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

/*
 *	Question : 山羊拉丁文
 *	给你一个由若干单词组成的句子 sentence ，单词间由空格分隔。每个单词仅由大写和小写英文字母组成。
 *	请你将句子转换为 “山羊拉丁文（Goat Latin）”（一种类似于 猪拉丁文 - Pig Latin 的虚构语言）。山羊拉丁文的规则如下：
 *	如果单词以元音开头（'a', 'e', 'i', 'o', 'u'），在单词后添加"ma"。
 *	例如，单词 "apple" 变为 "applema" 。
 *	如果单词以辅音字母开头（即，非元音字母），移除第一个字符并将它放到末尾，之后再添加"ma"。
 *	例如，单词 "goat" 变为 "oatgma" 。
 *	根据单词在句子中的索引，在单词最后添加与索引相同数量的字母'a'，索引从 1 开始。
 *	例如，在第一个单词后添加 "a" ，在第二个单词后添加 "aa" ，以此类推。
 *	返回将 sentence 转换为山羊拉丁文后的句子。
 *
 *	Date	 : [ 2022/04/21 14:22:49 ]
 */
string SimpleQ::toGoatLatin(string sentence) {
	string ans = "";
	int num = 1, nstart = 0;
	unordered_map<char, int> mp;
	mp['a'] = 1;	mp['e'] = 1;	mp['i'] = 1;
	mp['o'] = 1;	mp['u'] = 1;
	for (int i = 0; i < sentence.size(); i++)
	{
		if (sentence[i] == ' ' || i == sentence.size() - 1)
		{
			num++;
			if (i == sentence.size() - 1)
			{
				i++;
			}
			if (mp.count(tolower(sentence[nstart])) <= 0)
			{
				ans += sentence.substr(nstart + 1, i - nstart - 1);
				ans += sentence[nstart];
			}
			else
			{
				ans += sentence.substr(nstart, i - nstart);
			}
			ans += 'm';
			for (int j = 0; j < num; j++)
			{
				ans += 'a';
			}
			ans += ' ';
			nstart = i + 1;
		}
	}
	ans.erase(ans.size() - 1);
	return ans;
}

/*
 *	Question : 二进制间距
 *	给定一个正整数 n，找到并返回 n 的二进制表示中两个 相邻 1 之间的 最长距离 。如果不存在两个相邻的 1，返回 0 。
 *	如果只有 0 将两个 1 分隔开（可能不存在 0 ），则认为这两个 1 彼此 相邻 。
 *	两个 1 之间的距离是它们的二进制表示中位置的绝对差。例如，"1001" 中的两个 1 的距离为 3 。
 *
 *	Date	 : [ 2022/04/24 15:39:37 ]
 */
int SimpleQ::binaryGap(int n) {
	int ans = 0;
	int num = n, ncount = 0;
	while ((num & 1) != 1)
	{
		num >>= 1;
	}
	while (num > 0)
	{
		if (num & 1 == 1)
		{
			ans = ans < ncount ? ncount : ans;
			ncount = 0;
		}
		ncount++;
		num >>= 1;
	}
	return ans;
}

/*
 *	Question : 三维形体投影面积
 *	在 n x n 的网格 grid 中，我们放置了一些与 x，y，z 三轴对齐的 1 x 1 x 1 立方体。
 *	每个值 v = grid[i][j] 表示 v 个正方体叠放在单元格 (i, j) 上。
 *	现在，我们查看这些立方体在 xy 、yz 和 zx 平面上的投影。
 *	投影 就像影子，将 三维 形体映射到一个 二维 平面上。从顶部、前面和侧面看立方体时，我们会看到“影子”。
 *	返回 所有三个投影的总面积 。
 *
 *	Date	 : [ 2022/04/26 13:32:34 ]
 */
int SimpleQ::projectionArea(vector<vector<int>>& grid) {
	int ans = 0;
	for (int i = 0; i < grid.size(); i++)
	{
		int colMax = 0;
		for (int j = 0; j < grid.size(); j++)
		{
			if (grid[i][j] != 0)
			{
				ans++;
			}
			colMax = colMax < grid[i][j] ? grid[i][j] : colMax;
		}
		ans += colMax;
		int rowMax = 0;
		for (int j = 0; j < grid.size(); j++)
		{
			rowMax = rowMax < grid[j][i] ? grid[j][i] : rowMax;
		}
		ans += rowMax;
	}
	return ans;
}

/*
 *	Question : 按奇偶排序数组
 *	给你一个整数数组 nums，将 nums 中的的所有偶数元素移动到数组的前面，后跟所有奇数元素。
 *
 *	Date	 : [ 2022/04/28 09:22:05 ]
 */
vector<int> SimpleQ::sortArrayByParity(vector<int>& nums) {
	int nodd = -1;
	for (int i = 0; i < nums.size(); i++)
	{
		if (nums[i] % 2 != 0 && nodd == -1)
		{
			nodd = i;
		}
		if (nums[i] % 2 == 0 && nodd != -1)
		{
			int temp = nums[i];
			nums[i] = nums[nodd];
			nums[nodd] = temp;
			nodd++;
		}
	}
	return nums;
}

/*
 *	Question : 存在重复元素
 *	给你一个整数数组 nums 。如果任一值在数组中出现 至少两次 ，返回 true ；如果数组中每个元素互不相同，返回 false 。
 *
 *	Date	 : [ 2022/04/28 13:24:30 ]
 */
bool SimpleQ::containsDuplicate(vector<int>& nums) {
	unordered_map<int, int> mp;
	for (auto& num : nums)
	{
		if (mp.count(num) > 0)
		{
			return true;
		}
		mp[num]++;
	}
	return false;
}

/*
 *	Question : 剑指 Offer 03. 数组中重复的数字
 *	在一个长度为 n 的数组 nums 里的所有数字都在 0～n-1 的范围内。
 *	数组中某些数字是重复的，但不知道有几个数字重复了，也不知道每个数字重复了几次。请找出数组中任意一个重复的数字。
 *
 *	Date	 : [ 2022/04/28 13:33:13 ]
 */
int SimpleQ::findRepeatNumber(vector<int>& nums) {
	unordered_map<int, int> mp;
	for (auto& num : nums)
	{
		if (mp.count(num) > 0)
		{
			return num;
		}
		mp[num]++;
	}
	return -1;
}

/*
 *	Question : 判定字符是否唯一
 *	实现一个算法，确定一个字符串 s 的所有字符是否全都不同。
 *
 *	Date	 : [ 2022/04/28 14:24:23 ]
 */
bool SimpleQ::isUnique(string astr) {
	unordered_map<int, int> mp;
	for (auto& ch : astr)
	{
		if (mp.count(ch) > 0)
		{
			return false;
		}
		mp[ch]++;
	}
	return true;
}