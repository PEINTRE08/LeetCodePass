#pragma once
#include "QHeader.h"
#include "QStruct.h"



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
	/*
	*	Question : 随机数索引
	*	给定一个可能含有重复元素的整数数组，要求随机输出给定的数字的索引。 您可以假设给定的数字一定存在于数组中。
	*	Date	 : [ 2022/04/25 13:37:48 ]
	*/
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

	/*
	 *	Question : 非重叠矩形中的随机点
	 *	给定一个由非重叠的轴对齐矩形的数组 rects ，
	 *	其中 rects[i] = [ai, bi, xi, yi] 表示 (ai, bi) 是第 i 个矩形的左下角点，
	 *	(xi, yi) 是第 i 个矩形的右上角角点。设计一个算法来随机挑选一个被某一矩形覆盖的整数点。
	 *	矩形周长上的点也算做是被矩形覆盖。所有满足要求的点必须等概率被返回。
	 *	在一个给定的矩形覆盖的空间内任何整数点都有可能被返回。
	 *	请注意 ，整数点是具有整数坐标的点。
	 *	实现 Solution 类:
	 *	Solution(int[][] rects) 用给定的矩形数组 rects 初始化对象。
	 *	int[] pick() 返回一个随机的整数点 [u, v] 在给定的矩形所覆盖的空间内。
	 *
	 *	Date	 : [ 2022/06/09 10:02:45 ]
	 */
	Solution(vector<vector<int>>& rects) {
		srand(time(NULL));
		this->nums = rects;
// 		this->rects = rects;
// 		preS.push_back(0);
// 		for (auto& rec : rects)
// 		{
// 			int x1 = rec[0], y1 = rec[1], x2 = rec[2], y2 = rec[3];
// 			preS.push_back(preS.back() + (x2 - x1 + 1) * (y2 - y1 + 1));
// 		}
	}
	vector<int> pick() {
// 		int w = rand() % preS.back() + 1;
// 		int l = 0, r = preS.size() - 1;
// 		while (l < r)
// 		{
// 			int mid = (l + r) >> 1;
// 			if (preS[mid] < w)
// 				l = mid + 1;
// 			else
// 				r = mid;
// 		}
// 		--l;
// 		int x1 = rects[l][0], y1 = rects[l][1], x2 = rects[l][2], y2 = rects[l][3];
// 		return{ x1 + rand() % (x2 - x1 + 1), y1 + rand() % (y2 - y1 + 1) };
		int len = this->nums.size();
		int index = -1, cur = 0, curSum = 0;
		for (int i = 0; i < len; ++i)
		{
			int x1 = this->nums[i][0], y1 = this->nums[i][1], x2 = this->nums[i][2], y2 = this->nums[i][3];
			cur = (x2 - x1 + 1) * (y2 - y1 + 1);
			curSum += cur;
			if (rand() % curSum < cur)
				index = i;
		}
		vector<int> ans(2);
		ans[0] = rand() % (this->nums[index][2] - this->nums[index][0] + 1) + this->nums[index][0];
		ans[1] = rand() % (this->nums[index][3] - this->nums[index][1] + 1) + this->nums[index][1];
		return ans;
	}
private:
	vector<int> preS;
	vector<vector<int>> nums;
	unordered_map<int, vector<int>> mp;
};

// Definition for a binary tree node.
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

/*
*	Question : 序列化和反序列化二叉搜索树
*	序列化是将数据结构或对象转换为一系列位的过程，以便它可以存储在文件或内存缓冲区中，或通过网络连接链路传输，以便稍后在同一个或另一个计算机环境中重建。
*	设计一个算法来序列化和反序列化 二叉搜索树 。 对序列化/反序列化算法的工作方式没有限制。 您只需确保二叉搜索树可以序列化为字符串，并且可以将该字符串反序列化为最初的二叉搜索树。
*	编码的字符串应尽可能紧凑。
*
*	Date	 : [ 2022/05/11 14:37:48 ]
*/
class Codec {
public:

	// Encodes a tree to a single string.
	string serialize(TreeNode* root) {
		string ans = "";
		function<void(TreeNode*)> PreOrder = [&](TreeNode* node)
		{
			if (node == NULL)
			{
				return;
			}

			PreOrder(node->left);
			PreOrder(node->right);

			ans += to_string(node->val);
			ans += ",";
		};
		PreOrder(root);
		return ans;
	}

	// Decodes your encoded data to tree.
	TreeNode* deserialize(string data) {
		int nlen = data.length();
		int nIndex = 0, nSeparate = 0;
		stack<int> st;
		while (nIndex < nlen)
		{
			nSeparate = data.find(',', nIndex);
			s.assign(data.begin() + nIndex, data.begin() + nSeparate);
			nIndex = nSeparate + 1;
			st.push(stoi(s));
		}
		return construct(INT_MIN, INT_MAX, st);
	}

	TreeNode* construct(int lower, int upper, stack<int>& st) {
		if (st.size() == 0 || st.top() < lower || st.top() > upper) {
			return nullptr;
		}
		int val = st.top();
		st.pop();
		TreeNode* root = new TreeNode(val);
		root->right = construct(val, upper, st);
		root->left = construct(lower, val, st);
		return root;
	}
};

class MediumQ
{
	friend class NestedInteger;
	friend class Solution;
	friend class Node;
	friend class Codec;
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
	vector<int> findDiagonalOrder(vector<vector<int>>& mat);
	int findPairs(vector<int>& nums, int k);
	int findBottomLeftValue(TreeNode * root);
	vector<int> largestValues(TreeNode * root);
	TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p);
};