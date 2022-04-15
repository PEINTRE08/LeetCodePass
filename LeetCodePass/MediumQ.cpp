﻿#include "stdafx.h"
#include "MediumQ.h"


MediumQ::MediumQ()
{
}
MediumQ::~MediumQ()
{
}


/*
 *	Question : 
 *	实现RandomizedSet 类：
 *
 *	RandomizedSet() 初始化 RandomizedSet 对象
 *	bool insert(int val) 当元素 val 不存在时，向集合中插入该项，并返回 true ；否则，返回 false 。
 *	bool remove(int val) 当元素 val 存在时，从集合中移除该项，并返回 true ；否则，返回 false 。
 *	int getRandom() 随机返回现有集合中的一项（测试用例保证调用此方法时集合中至少存在一个元素）。每个元素应该有 相同的概率 被返回。
 *	你必须实现类的所有函数，并满足每个函数的 平均 时间复杂度为 O(1) 。
 *
 *	Date	 : [ 2022/04/13 14:44:38 ]
 */
/**
* Your RandomizedSet object will be instantiated and called as such:
* RandomizedSet* obj = new RandomizedSet();
* bool param_1 = obj->insert(val);
* bool param_2 = obj->remove(val);
* int param_3 = obj->getRandom();
*/
class RandomizedSet {
public:
	RandomizedSet() {
		srand((unsigned)time(NULL));
	}

	bool insert(int val) {
		if (mp.count(val) != 0) return false;
		vec.push_back(val);
		mp[val] = vec.size() - 1;
		return true;
	}

	bool remove(int val) {
		if (mp.count(val) == 0) return false;
		int last = vec[vec.size() - 1];
		vec[mp[val]] = last;
		mp[last] = mp[val];
		vec.pop_back();
		mp.erase(val);
		return true;
	}

	int getRandom() {
		return vec[rand() % vec.size()];
	}
private:
	unordered_map<int, int> mp;
	vector<int> vec;
};

/**
* // This is the interface that allows for creating nested lists.
* // You should not implement it, or speculate about its implementation
* class NestedInteger {
*   public:
*     // Constructor initializes an empty nested list.
*     NestedInteger();
*
*     // Constructor initializes a single integer.
*     NestedInteger(int value);
*
*     // Return true if this NestedInteger holds a single integer, rather than a nested list.
*     bool isInteger() const;
*
*     // Return the single integer that this NestedInteger holds, if it holds a single integer
*     // The result is undefined if this NestedInteger holds a nested list
*     int getInteger() const;
*
*     // Set this NestedInteger to hold a single integer.
*     void setInteger(int value);
*
*     // Set this NestedInteger to hold a nested list and adds a nested integer to it.
*     void add(const NestedInteger &ni);
*
*     // Return the nested list that this NestedInteger holds, if it holds a nested list
*     // The result is undefined if this NestedInteger holds a single integer
*     const vector<NestedInteger> &getList() const;
* };
*/
/*
 *	Question : 迷你语法分析器
 *	给定一个字符串 s 表示一个整数嵌套列表，实现一个解析它的语法分析器并返回解析的结果 NestedInteger 。
 *	列表中的每个元素只可能是整数或整数嵌套列表
 *
 *	Date	 : [ 2022/04/15 13:41:37 ]
 */
NestedInteger MediumQ::deserialize(string s) {
	NestedInteger ans;
	int nindex = 0;
	function<void(NestedInteger&)> fun = [&](NestedInteger &list)
	{
		string subs = "";
		int num = 0;
		while (nindex < s.length())
		{
			if (s[nindex] == ']')
			{
				if (subs == "")
				{
					return;
				}
				NestedInteger child;
				num = stoi(subs);
				child.setInteger(num);
				subs = "";
				list.add(child);
				return;
			}
			if (s[nindex] == '[')
			{
				NestedInteger child;
				nindex++;
				fun(child);
				list.add(child);
			}
			else if (s[nindex] == ',')
			{
				if (subs == "")
				{
					nindex++;
					continue;
				}
				NestedInteger child;
				num = stoi(subs);
				child.setInteger(num);
				subs = "";
				list.add(child);
			}
			else
			{
				subs += s[nindex];
			}
			nindex++;
		}
	};

	if (s[nindex] != '[')
	{
		ans.setInteger(stoi(s));
	}
	else
	{
		nindex++;
		fun(ans);
	}
	return ans;
}