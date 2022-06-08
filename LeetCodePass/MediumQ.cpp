#include "stdafx.h"
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

/*
 *	Question : 字典序排数
 *	给你一个整数 n ，按字典序返回范围 [1, n] 内所有整数。
 *	你必须设计一个时间复杂度为 O(n) 且使用 O(1) 额外空间的算法。
 *
 *	Date	 : [ 2022/04/18 16:28:50 ]
 */
// @NOPASS
vector<int> MediumQ::lexicalOrder(int n) {
	vector<int> ans(n, 0);
	int num = 1;
	for (int i = 0; i < n; i++)
	{
		ans[i] = num;
		if (num*10 <= n)
		{
			num *= 10;
		}
		else
		{
			while (num % 10 == 9 || num + 1 > n)
			{
				num /= 10;
			}
			num++;
		}
	}
	return ans;
}

/*
 *	Question : 旋转函数
 *	给定一个长度为 n 的整数数组 nums 。
 *	假设 arrk 是数组 nums 顺时针旋转 k 个位置后的数组，我们定义 nums 的 旋转函数  F 为：
 *	F(k) = 0 * arrk[0] + 1 * arrk[1] + ... + (n - 1) * arrk[n - 1]
 *	返回 F(0), F(1), ..., F(n-1)中的最大值 。
 *	生成的测试用例让答案符合 32 位 整数。
 *
 *	Date	 : [ 2022/04/22 10:51:01 ]
 */
// @OverTime
int MediumQ::maxRotateFunction(vector<int>& nums) {
	int ans = INT_MIN;
	int n = nums.size(), peak = 0;
	if (n == 1)
	{
		return 0;
	}
	for (int i = 0; i < n; i++)
	{
		if (i == 0 || nums.at(i) < nums.at(i - 1))
		{
			peak = i - 1;
			int num = 0, j = 0;
			for (int k = i; k < n && j < n; k++, j++)
			{
				num += j * nums[k];
			}
			for (int k = 0; k <= peak && j < n; k++, j++)
			{
				num += j * nums[k];
			}
			ans = ans < num ? num : ans;
		}
	}
	return ans;
}

/*
 *	Question : 太平洋大西洋水流问题
 *	有一个 m × n 的矩形岛屿，与 太平洋 和 大西洋 相邻。
 *	 “太平洋” 处于大陆的左边界和上边界，而 “大西洋” 处于大陆的右边界和下边界。
 *	这个岛被分割成一个由若干方形单元格组成的网格。
 *	给定一个 m x n 的整数矩阵 heights ， heights[r][c] 表示坐标 (r, c) 上单元格 高于海平面的高度 。
 *	岛上雨水较多，如果相邻单元格的高度 小于或等于 当前单元格的高度，雨水可以直接向北、南、东、西流向相邻单元格。
 *	水可以从海洋附近的任何单元格流入海洋。
 *	返回 网格坐标 result 的 2D列表 ，其中 result[i] = [ri, ci] 表示雨水可以从单元格 (ri, ci) 流向 太平洋和大西洋 。
 *
 *	Date	 : [ 2022/04/27 14:00:22 ]
 */
// @ga
vector<vector<int>> MediumQ::pacificAtlantic(vector<vector<int>>& heights) {
	vector<vector<int>> result;
	int m = heights.size(), n = heights[0].size();
	stack<vector<int>> s;
	vector<vector<bool>> leaf(m, vector<bool>(n, false));
	for (int i = 0; i < m; i++)
	{
		vector<int> temp;
		temp.push_back(i);
		temp.push_back(0);
		s.push(temp);
		leaf[i][0] = true;
	}
	for (int i = 1; i < n; i++)
	{
		vector<int> temp;
		temp.push_back(0);
		temp.push_back(i);
		s.push(temp);
		leaf[0][i] = true;
	}
	while (s.size() > 0)
	{
		vector<int> temp = s.top();
		s.pop();
		int x = temp[0], y = temp[1];
		if (x + 1 < m && (heights[x][y] <= heights[x + 1][y]))
		{
			if (heights[x][y] == heights[x + 1][y])
			{
				leaf[x][y] = true;
			}
			vector<int> tempp;
			tempp.push_back(x + 1);
			tempp.push_back(y);
			s.push(tempp);
		}
		if (y + 1 < n && (heights[x][y] <= heights[x][y + 1]))
		{
			if (heights[x][y] == heights[x][y + 1])
			{
				leaf[x][y] = true;
			}
			vector<int> tempp;
			tempp.push_back(x);
			tempp.push_back(y + 1);
			s.push(tempp);
			continue;
		}
		leaf[x][y] = true;
	}
	for (int i = 0; i < m; i++)
	{
		vector<int> temp;
		temp.push_back(i);
		temp.push_back(n - 1);
		s.push(temp);
		if (leaf[i][n - 1] == true)
		{
			result.push_back(temp);
			leaf[i][n - 1] = false;
		}
	}
	for (int i = 0; i < n - 1; i++)
	{
		vector<int> temp;
		temp.push_back(m - 1);
		temp.push_back(i);
		s.push(temp);
		if (leaf[m - 1][i] == true)
		{
			result.push_back(temp);
			leaf[m - 1][i] = false;
		}
	}
	while (s.size() > 0)
	{
		vector<int> temp = s.top();
		s.pop();
		int x = temp[0], y = temp[1];
		if (x -	1 >= 0 && (heights[x][y] <= heights[x - 1][y]))
		{
			if (heights[x][y] == heights[x - 1][y])
			{
				if (leaf[x][y] == true)
				{
					result.push_back(temp);
					leaf[x][y] = false;
				}
			}
			vector<int> tempp;
			tempp.push_back(x - 1);
			tempp.push_back(y);
			s.push(tempp);
		}
		if (y - 1 >= 0 && (heights[x][y] <= heights[x][y - 1]))
		{
			if (heights[x][y] == heights[x][y - 1])
			{
				if (leaf[x][y] == true)
				{
					result.push_back(temp);
					leaf[x][y] = false;
				}
			}
			vector<int> tempp;
			tempp.push_back(x);
			tempp.push_back(y - 1);
			s.push(tempp);
			continue;
		}
		if (leaf[x][y] == true)
		{
			result.push_back(temp);
			leaf[x][y] = false;
		}
	}
	return result;
}

/*
 *	Question : 建立四叉树
 *	给你一个 n * n 矩阵 grid ，矩阵由若干 0 和 1 组成。请你用四叉树表示该矩阵 grid 。
 *	你需要返回能表示矩阵的 四叉树 的根结点。
 *	注意，当 isLeaf 为 False 时，你可以把 True 或者 False 赋值给节点，两种值都会被判题机制 接受 。
 *	四叉树数据结构中，每个内部节点只有四个子节点。此外，每个节点都有两个属性：
 *		val：储存叶子结点所代表的区域的值。1 对应 True，0 对应 False；
 *		isLeaf: 当这个节点是一个叶子结点时为 True，如果它有 4 个子节点则为 False 。
 *
 *	Date	 : [ 2022/04/29 10:35:47 ]
 */
Node* MediumQ::construct(vector<vector<int>>& grid) {
	int n = grid.size();
	Node* root = NULL;
	function<Node*(int, int, int, int)> fun = [&](int nX, int nY, int nCol, int nRow) -> Node*
	{
		bool bSome = true, nVal = grid[nX][nY];
		for (int i = 0; i < nCol; i++)
		{
			for (int j = 0; j < nRow; j++)
			{
				if (grid[i + nX][j + nY] != nVal)
				{
					bSome = false;
					break;
				}
			}
			if (bSome == false)
			{
				break;
			}
		}
		Node* node = new Node();
		node->isLeaf = bSome;
		node->val = nVal;
		if (node->isLeaf != true)
		{
			node->topLeft = fun(nX, nY, nCol / 2, nRow / 2);
			node->bottomLeft = fun(nX + (nCol / 2), nY, nCol - (nCol / 2), nRow / 2);
			node->topRight = fun(nX, nY + (nRow / 2), nCol / 2, nRow - (nRow / 2));
			node->bottomRight = fun(nX + (nCol / 2), nY + (nRow / 2), nCol - (nCol / 2), nRow - (nRow / 2));
		}
		return node;
	};
// 	root = fun(0, 0, n, n);
	return root;
}

/*
 *	Question : 一次编辑
 *	字符串有三种编辑操作:插入一个字符、删除一个字符或者替换一个字符。 
 *	给定两个字符串，编写一个函数判定它们是否只需要一次(或者零次)编辑。
 *
 *	Date	 : [ 2022/05/13 14:03:40 ]
 */
bool MediumQ::oneEditAway(string first, string second) {
	int lenf = first.length(), lens = second.length();
	if (abs(lenf - lens) > 1)
	{
		return false;
	}
	int nf = 0, ns = 0, ndiff = 0;
	while (nf < lenf || ns < lens)
	{
		if (nf >= lenf || ns >= lens || (nf < lenf && ns < lens && first.at(nf) != second.at(ns)))
		{
			ndiff++;
			if (ndiff >= 2)
			{
				return false;
			}
			if (lenf < lens)
			{
				nf--;
			}
			else if (lenf > lens)
			{
				ns--;
			}
		}
		nf++; ns++;
	}
	return true;
}

/*
 *	Question : 最少移动次数使数组元素相等 II
 *	给你一个长度为 n 的整数数组 nums ，返回使所有数组元素相等需要的最少移动数。
 *	在一步操作中，你可以使数组中的一个元素加 1 或者减 1 。

 *	Date	 : [ 2022/05/19 14:12:47 ]
 */
///	★★★★★
int MediumQ::minMoves2(vector<int>& nums) {
	function<int(vector<int>, int, int)> partition = [&](vector<int>& num, int left, int right) -> int
	{
		int x = nums[right], i = left - 1;
		for (int j = left; j < right; ++j) {
			if (nums[j] <= x) {
				swap(nums[++i], nums[j]);
			}
		}
		swap(nums[i + 1], nums[right]);
		return i + 1;
	};
	function<int(vector<int>, int, int)> randomSelect = [&](vector<int>& num, int left, int right) -> int
	{
		int index = rand() % (right - left + 1) + left;
		swap(num.at(index), num.at(right));
		return partition(num, left, right);
	};
	function<int(vector<int>, int, int, int)> quickSelect = [&](vector<int>& num, int left, int right, int k) -> int
	{
		int q = randomSelect(num, left, right);
		if (q == k)
		{
			return num[q];
		}
		return q < k ? quickSelect(num, q + 1, right, k) : quickSelect(num, left, q - 1, k);
	};

	srand(time(0));
	int n = nums.size(), x = quickSelect(nums, 0, n - 1, n / 2), ret = 0;
	for (int i = 0; i < n; ++i) {
		ret += abs(nums[i] - x);
	}
	return ret;
}

/*
 *	Question : Find Right Interval
 *	You are given an array of intervals, where intervals[i] = [starti, endi] and each starti is unique.
 *	The right interval for an interval i is an interval j such that startj >= endi and startj is minimized. 
 *	Note that i may equal j.
 *	Return an array of right interval indices for each interval i. 
 *	If no right interval exists for interval i, then put -1 at index i.
 *
 *	Date	 : [ 2022/05/20 14:14:38 ]
 */
vector<int> MediumQ::findRightInterval(vector<vector<int>>& intervals) {
	unordered_map<int, int> mp;
	vector<int> ans(intervals.size(), -1);
	int nMax = intervals.at(0).at(1);
	for (int i = 0; i < intervals.size(); i++)
	{
		int num = intervals.at(i).at(0);
		if (mp.count(num) <= 0)
		{
			mp[num] = i;
			nMax = nMax > num ? nMax : num;
		}
	}
	for (int i = 0; i < intervals.size(); i++)
	{
		int num = intervals.at(i).at(1);
		for (int j = num; j <= nMax; j++)
		{
			if (mp.count(j) > 0)
			{
				ans[i] = mp[j];
				break;
			}
		}
	}
	return ans;
}

/*
 *	Question : 环绕字符串中唯一的子字符串
 *	把字符串 s 看作是 “abcdefghijklmnopqrstuvwxyz” 的无限环绕字符串，所以 s 看起来是这样的：
 *	"...zabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcd...." . 
 *	现在给定另一个字符串 p 。返回 s 中 唯一 的 p 的 非空子串 的数量 。 
 *
 *	Date	 : [ 2022/05/25 11:42:57 ]
 */
///	★★★★★
int MediumQ::findSubstringInWraproundString(string p) {
	vector<int> dp(26);
	int k = 0;
	for (int i = 0; i < p.length(); ++i) {
		if (i && (p[i] - p[i - 1] + 26) % 26 == 1) { // 字符之差为 1 或 -25
			++k;
		}
		else {
			k = 1;
		}
		dp[p[i] - 'a'] = max(dp[p[i] - 'a'], k);
	}
	return accumulate(dp.begin(), dp.end(), 0);
}

/*
 *	Question : 火柴拼正方形
 *	你将得到一个整数数组 matchsticks ，其中 matchsticks[i] 是第 i 个火柴棒的长度。
 *	你要用 所有的火柴棍 拼成一个正方形。你 不能折断 任何一根火柴棒，
 *	但你可以把它们连在一起，而且每根火柴棒必须 使用一次 。
 *	如果你能使这个正方形，则返回 true ，否则返回 false 。
 *
 *	Date	 : [ 2022/06/01 09:20:13 ]
 */
///	★★★★★
bool MediumQ::makesquare(vector<int>& matchsticks) {
	int len = matchsticks.size();
	if (len < 4)
	{
		return false;
	}
	function<bool(vector<int>, vector<int>&, int, int)> divide = [&](vector<int> nums, vector<int>& vec, int index, int value) -> bool
	{
		if (index == len) 
		{
			return true;
		}
		for (int i = 0; i < vec.size(); i++) 
		{
			vec[i] += matchsticks[index];
			if (vec[i] <= value && divide( matchsticks, vec, index + 1, value)) 
			{
				return true;
			}
			vec[i] -= matchsticks[index];
		}
		return false;
	};
	int edge = accumulate(matchsticks.begin(), matchsticks.end(), 0);
	if (edge % 4 != 0)
	{
		return false;
	}
	sort(matchsticks.begin(), matchsticks.end(), greater<int>());
	vector<int> edges(4);
	if (divide(matchsticks, edges, 0, edge / 4))
	{
		return true;
	}
	return false;
}

/*
 *	Question : 删除二叉搜索树中的节点
 *	给定一个二叉搜索树的根节点 root 和一个值 key，删除二叉搜索树中的 key 对应的节点，并保证二叉搜索树的性质不变。
 *	返回二叉搜索树（有可能被更新）的根节点的引用。
 *	一般来说，删除节点可分为两个步骤：
 *	首先找到需要删除的节点；
 *	如果找到了，删除它。
 *
 *	Date	 : [ 2022/06/02 13:52:56 ]
 */
///	★★★★★
TreeNode* MediumQ::deleteNode(TreeNode* root, int key) {
	TreeNode *cur = root, *curParent = nullptr;
	while (cur && cur->val != key) {
		curParent = cur;
		if (cur->val > key) {
			cur = cur->left;
		}
		else {
			cur = cur->right;
		}
	}
	if (!cur) {
		return root;
	}
	if (!cur->left && !cur->right) {
		cur = nullptr;
	}
	else if (!cur->right) {
		cur = cur->left;
	}
	else if (!cur->left) {
		cur = cur->right;
	}
	else {
		TreeNode *successor = cur->right, *successorParent = cur;
		while (successor->left) {
			successorParent = successor;
			successor = successor->left;
		}
		if (successorParent->val == cur->val) {
			successorParent->right = successor->right;
		}
		else {
			successorParent->left = successor->right;
		}
		successor->right = cur->right;
		successor->left = cur->left;
		cur = successor;
	}
	if (!curParent) {
		return cur;
	}
	else {
		if (curParent->left && curParent->left->val == key) {
			curParent->left = cur;
		}
		else {
			curParent->right = cur;
		}
		return root;
	}
}

/*
 *	Question : 爱吃香蕉的珂珂
 *	珂珂喜欢吃香蕉。这里有 n 堆香蕉，第 i 堆中有 piles[i] 根香蕉。警卫已经离开了，将在 h 小时后回来。
 *	珂珂可以决定她吃香蕉的速度 k （单位：根/小时）。每个小时，她将会选择一堆香蕉，从中吃掉 k 根。
 *	如果这堆香蕉少于 k 根，她将吃掉这堆的所有香蕉，然后这一小时内不会再吃更多的香蕉。  
 *	珂珂喜欢慢慢吃，但仍然想在警卫回来前吃掉所有的香蕉。
 *	返回她可以在 h 小时内吃掉所有香蕉的最小速度 k（k 为整数）。

 *	Date	 : [ 2022/06/07 14:19:10 ]
 */
///	★★★★★
int MediumQ::minEatingSpeed(vector<int>& piles, int h) {
	function<long(const vector<int>&, int)> getTime = [&](const vector<int>& piles, int speed) -> long {
		long time = 0;
		for (int pile : piles) {
			int curTime = (pile + speed - 1) / speed;
			time += curTime;
		}
		return time;
	};

	int low = 1;
	int high = 0;
	for (int pile : piles) {
		high = max(high, pile);
	}
	int k = high;
	while (low < high) {
		int speed = (high - low) / 2 + low;
		long time = getTime(piles, speed);
		if (time <= h) {
			k = speed;
			high = speed;
		}
		else {
			low = speed + 1;
		}
	}
	return k;
}
