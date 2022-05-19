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