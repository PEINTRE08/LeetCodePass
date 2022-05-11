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
*	Question : ���л��ͷ����л�����������
*	���л��ǽ����ݽṹ�����ת��Ϊһϵ��λ�Ĺ��̣��Ա������Դ洢���ļ����ڴ滺�����У���ͨ������������·���䣬�Ա��Ժ���ͬһ������һ��������������ؽ���
*	���һ���㷨�����л��ͷ����л� ���������� �� �����л�/�����л��㷨�Ĺ�����ʽû�����ơ� ��ֻ��ȷ�������������������л�Ϊ�ַ��������ҿ��Խ����ַ��������л�Ϊ����Ķ�����������
*	������ַ���Ӧ�����ܽ��ա�
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