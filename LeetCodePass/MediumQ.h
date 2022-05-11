#pragma once
#include "QHeader.h"

class NestedInteger {
public:
	// Constructor initializes an empty nested list.
	NestedInteger() {};

	// Constructor initializes a single integer.
	NestedInteger(int value);

	// Return true if this NestedInteger holds a single integer, rather than a nested list.
	bool isInteger() const;

	// Return the single integer that this NestedInteger holds, if it holds a single integer
	// The result is undefined if this NestedInteger holds a nested list
	int getInteger() const;

	// Set this NestedInteger to hold a single integer.
	void setInteger(int value) {};

	// Set this NestedInteger to hold a nested list and adds a nested integer to it.
	void add(const NestedInteger &ni) {};

	// Return the nested list that this NestedInteger holds, if it holds a nested list
	// The result is undefined if this NestedInteger holds a single integer
	const vector<NestedInteger> &getList() const;
};

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

// Definition for a QuadTree node.
class Node {
public:
	bool val;
	bool isLeaf;
	Node* topLeft;
	Node* topRight;
	Node* bottomLeft;
	Node* bottomRight;

	Node() {
		val = false;
		isLeaf = false;
		topLeft = NULL;
		topRight = NULL;
		bottomLeft = NULL;
		bottomRight = NULL;
	}

	Node(bool _val, bool _isLeaf) {
		val = _val;
		isLeaf = _isLeaf;
		topLeft = NULL;
		topRight = NULL;
		bottomLeft = NULL;
		bottomRight = NULL;
	}

	Node(bool _val, bool _isLeaf, Node* _topLeft, Node* _topRight, Node* _bottomLeft, Node* _bottomRight) {
		val = _val;
		isLeaf = _isLeaf;
		topLeft = _topLeft;
		topRight = _topRight;
		bottomLeft = _bottomLeft;
		bottomRight = _bottomRight;
	}
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
};