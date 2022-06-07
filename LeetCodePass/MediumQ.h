#pragma once
#include "QHeader.h"
#include "QStruct.h"


/*
*	Question : 随机数索引
*	给定一个可能含有重复元素的整数数组，要求随机输出给定的数字的索引。 您可以假设给定的数字一定存在于数组中。
*	Date	 : [ 2022/04/25 13:37:48 ]
*/
//水塘抽样x
/*	平均抽样算法 概率：1/k
 *	if (nums[i] == target) {
 *		++cnt;
 *		if (rand() % cnt == 0) {
 *			ans = i;
 *		}
 *	}
*/
class Solution {
public:
	Solution(vector<int>& nums) {
// 		this->nums = nums;
		srand(time(NULL));
		for (int i = 0; i < nums.size(); i++)
		{
			mp[nums[i]].push_back(i);
		}
	}

	int pick(int target) {
		return mp[target].at(rand() % mp[target].size());
	}
private:
// 	vector<int> nums;
	unordered_map<int, vector<int>> mp;
};

class MediumQ
{
	friend class NestedInteger;
	friend class Solution;
	friend class Node;
public:
	MediumQ();
	~MediumQ();
	NestedInteger deserialize(string s);
	vector<int> lexicalOrder(int n);
	int maxRotateFunction(vector<int>& nums);
	vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights);
	Node * construct(vector<vector<int>>& grid);
	bool oneEditAway(string first, string second);
	int minMoves2(vector<int>& nums);
	vector<int> findRightInterval(vector<vector<int>>& intervals);
	int findSubstringInWraproundString(string p);
	bool makesquare(vector<int>& matchsticks);
	TreeNode * deleteNode(TreeNode * root, int key);
	int minEatingSpeed(vector<int>& piles, int h);
};