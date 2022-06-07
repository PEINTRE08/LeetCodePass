#pragma once
#include "QHeader.h"
#include "QStruct.h"


/*
*	Question : ���������
*	����һ�����ܺ����ظ�Ԫ�ص��������飬Ҫ�����������������ֵ������� �����Լ������������һ�������������С�
*	Date	 : [ 2022/04/25 13:37:48 ]
*/
//ˮ������x
/*	ƽ�������㷨 ���ʣ�1/k
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