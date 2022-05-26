#include "stdafx.h"
#include "HardQ.h"


HardQ::HardQ()
{
}


HardQ::~HardQ()
{
}

/*
 *	Question : 乘法表中第k小的数
 *	几乎每一个人都用 乘法表。但是你能在乘法表中快速找到第k小的数字吗？
 *	给定高度m 、宽度n 的一张 m * n的乘法表，以及正整数k，你需要返回表中第 k 小的数字。
 *	
 *	Date	 : [ 2022/05/18 09:24:09 ]
 */
///	★★★★★
int HardQ::findKthNumber(int m, int n, int k) {
	//二分查找
	int left = 1, right = m*n;
	while (left < right)
	{
		int x = (right + left) / 2;
		int count = x / n *n;
		for (int i = x / n + 1; i < m; i++)
		{
			count += x / i;
		}
		if (count >= k)
		{
			right = x;
		}
		else
		{
			left = x + 1;
		}
	}
	return left;
}

/*
 *	Question : 为高尔夫比赛砍树
 *	你被请来给一个要举办高尔夫比赛的树林砍树。树林由一个 m x n 的矩阵表示， 在这个矩阵中：
 *	0 表示障碍，无法触碰
 *	1 表示地面，可以行走
 *	比 1 大的数 表示有树的单元格，可以行走，数值表示树的高度
 *	每一步，你都可以向上、下、左、右四个方向之一移动一个单位，如果你站的地方有一棵树，那么你可以决定是否要砍倒它。
 *	你需要按照树的高度从低向高砍掉所有的树，每砍过一颗树，该单元格的值变为 1（即变为地面）。
 *	你将从 (0, 0) 点开始工作，返回你砍完所有树需要走的最小步数。 如果你无法砍完所有的树，返回 -1 。
 *	可以保证的是，没有两棵树的高度是相同的，并且你至少需要砍倒一棵树。
 *
 *	Date	 : [ 2022/05/23 10:24:21 ]
 */
///	★★★★★
int HardQ::cutOffTree(vector<vector<int>>& forest) {
	int dirs[4][2] = { { -1, 0 },{ 1, 0 },{ 0, -1 },{ 0, 1 } };

	vector<pair<int, int>> trees;

	int row = forest.size();
	int col = forest[0].size();

	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			if (forest[i][j] > 1) {
				trees.emplace_back(i, j);
			}
		}
	}

	sort(trees.begin(), trees.end(), [&](const pair<int, int> & a, const pair<int, int> & b) {
		return forest[a.first][a.second] < forest[b.first][b.second];
	});

	int cx = 0;
	int cy = 0;
	int ans = 0;

	function<int(vector<vector<int>>, int, int, int, int)> bfs = [&](vector<vector<int>>& forest, int sx, int sy, int tx, int ty) -> int
	{
		if (sx == tx && sy == ty) {
			return 0;
		}

		int row = forest.size();
		int col = forest[0].size();
		int step = 0;
		queue<pair<int, int>> qu;
		vector<vector<bool>> visited(row, vector<bool>(col, false));
		qu.emplace(sx, sy);
		visited[sx][sy] = true;
		while (!qu.empty()) {
			step++;
			int sz = qu.size();
			for (int i = 0; i < sz; ++i) {
				cx = qu.front().first;
				cy = qu.front().second;
				qu.pop();
				for (int j = 0; j < 4; ++j) {
					int nx = cx + dirs[j][0];
					int ny = cy + dirs[j][1];
					if (nx >= 0 && nx < row && ny >= 0 && ny < col) {
						if (!visited[nx][ny] && forest[nx][ny] > 0) {
							if (nx == tx && ny == ty) {
								return step;
							}
							qu.emplace(nx, ny);
							visited[nx][ny] = true;
						}
					}
				}
			}
		}
		return -1;
	};
	
	for (int i = 0; i < trees.size(); ++i) {
		int steps = bfs(forest, cx, cy, trees[i].first, trees[i].second);
		if (steps == -1) {
			return -1;
		}
		ans += steps;
		cx = trees[i].first;
		cy = trees[i].second;
	}
	return ans;
}

/*
 *	Question : 掉落的方块
 *	俄罗斯方块：在每个方块掉落后，你必须记录目前所有已经落稳的 方块堆叠的最高高度 。
 *	返回一个整数数组 ans ，其中 ans[i] 表示在第 i 块方块掉落后堆叠的最高高度。
 *
 *	Date	 : [ 2022/05/26 14:35:53 ]
 */
///	★★★★★★★★★★
vector<int> HardQ::fallingSquares(vector<vector<int>>& positions) {
	const int len = positions.size();
	vector<int> ans(len);
	for (int i = 0; i < len; i++)
	{
		int left = positions[i][0], right = positions[i][1] + left - 1;
		ans[i] = positions[i][1];
		for (int j = 0; j < i; j++)
		{
			int jleft = positions[j][0], jright = positions[j][1] + jleft - 1;
			if (right >= jleft && jright >= left)
			{
				ans[i] = max(ans[i], ans[j] + positions[i][1]);
			}
		}
	}
	for (int i = 1; i < len; i++) {
		ans[i] = max(ans[i], ans[i - 1]);
	}
	return ans;
}