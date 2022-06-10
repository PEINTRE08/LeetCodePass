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
///	★★★★★ ★
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

/*
 *	Question : 外星文字典
 *	现有一种使用英语字母的外星文语言，这门语言的字母顺序与英语顺序不同。
 *	给定一个字符串列表 words ，作为这门语言的词典，words 中的字符串已经 按这门新语言的字母顺序进行了排序 。
 *	请你根据该词典还原出此语言中已知的字母顺序，并 按字母递增顺序 排列。若不存在合法字母顺序，
 *	返回 "" 。若存在多种可能的合法字母顺序，返回其中 任意一种 顺序即可。
 *	字符串 s 字典顺序小于 字符串 t 有两种情况：
 *	在第一个不同字母处，如果 s 中的字母在这门外星语言的字母顺序中位于 t 中字母之前，那么 s 的字典顺序小于 t 。
 *	如果前面 min(s.length, t.length) 字母都相同，那么 s.length < t.length 时，s 的字典顺序也小于 t 。
 *
 *	Date	 : [ 2022/05/31 14:14:45 ]
 */
/*
 *	class Solution {
public:
    const int VISITING = 1, VISITED = 2;
    unordered_map<char, vector<char>> edges;
    unordered_map<char, int> states;
    bool valid = true;
    string order;
    int index;

    string alienOrder(vector<string>& words) {
        int length = words.size();
        for (string & word : words) {
            int wordLength = word.size();
            for (int j = 0; j < wordLength; j++) {
                char c = word[j];
                if (!edges.count(c)) {
                    edges[c] = vector<char>();
                }
            }
        }
        for (int i = 1; i < length && valid; i++) {
            addEdge(words[i - 1], words[i]);
        }
        order = string(edges.size(), ' ');
        index = edges.size() - 1;
        for (auto [u, _] : edges) {
            if (!states.count(u)) {
                dfs(u);
            }
        }
        if (!valid) {
            return "";
        }
        return order;
    }

    void addEdge(string before, string after) {
        int length1 = before.size(), length2 = after.size();
        int length = min(length1, length2);
        int index = 0;
        while (index < length) {
            char c1 = before[index], c2 = after[index];
            if (c1 != c2) {
                edges[c1].emplace_back(c2);
                break;
            }
            index++;
        }
        if (index == length && length1 > length2) {
            valid = false;
        }
    }

    void dfs(char u) {
        states[u] = VISITING;
        for (char v : edges[u]) {
            if (!states.count(v)) {
                dfs(v);
                if (!valid) {
                    return;
                }
            } else if (states[v] == VISITING) {
                valid = false;
                return;
            }
        }
        states[u] = VISITED;
        order[index] = u;
        index--;
    }
};
 */
/*
 *	class Solution {
public:
    unordered_map<char, vector<char>> edges;
    unordered_map<char, int> indegrees;
    bool valid = true;

    string alienOrder(vector<string>& words) {
        int length = words.size();
        for (auto word : words) {
            int wordLength = word.size();
            for (int j = 0; j < wordLength; j++) {
                char c = word[j];
                if (!edges.count(c)) {
                    edges[c] = vector<char>();
                }
            }
        }
        for (int i = 1; i < length && valid; i++) {
            addEdge(words[i - 1], words[i]);
        }
        if (!valid) {
            return "";
        }
        queue<char> qu;
        for (auto [u, _] : edges) {
            if (!indegrees.count(u)) {
                qu.emplace(u);
            }
        }
        string order;
        while (!qu.empty()) {
            char u = qu.front();
            qu.pop();
            order.push_back(u);
            for (char v : edges[u]) {
                indegrees[v]--;
                if (indegrees[v] == 0) {
                    qu.emplace(v);
                }
            }
        }
        return order.size() == edges.size() ? order : "";
    }

    void addEdge(string before, string after) {
        int length1 = before.size(), length2 = after.size();
        int length = min(length1, length2);
        int index = 0;
        while (index < length) {
            char c1 = before[index], c2 = after[index];
            if (c1 != c2) {
                edges[c1].emplace_back(c2);
                indegrees[c2] += 1;
                break;
            }
            index++;
        }
        if (index == length && length1 > length2) {
            valid = false;
        }
    }
};
 */
string HardQ::alienOrder(vector<string>& words) {
	vector<pair<char, int>> vec;
	unordered_map<char, int> mp;
	int len = 1;
	vec.emplace_back(words[0][0], 0);
	mp[words[0][0]] = len;
	for (int i = 0; i < words[0].size(); i++)
	{
		int cmp = 0;
		for (int j = 1; j < words.size(); j++)
		{
			if (i >= words[j].size())
			{
				continue;
			}
			char ch = words[j][i];
			if (ch != words[cmp][i])
			{
				if (mp.count(ch) > 0)
				{
					vec[mp[ch]].second = vec[mp[ch]].second > vec[mp[words[cmp][i]]].second + 1 ? \
						vec[mp[ch]].second : vec[mp[words[cmp][i]]].second + 1;
				}
				else
				{
					vec.emplace_back(words[j][i], vec[mp[words[cmp][i]] - 1].second + 1);
					len++;
					mp[words[j][i]] = len;
				}
			}
			cmp++;
		}
	}
	string ans("");
	sort(vec.begin(), vec.end(), [&](pair<char, int> p1, pair<char, int> p2) {
		return p1.second < p2.second;
	});
	for (auto& v : vec)
	{
		ans += v.first;
	}
	return ans;
}

/*
 *	Question : 统计不同回文子序列
 *	给定一个字符串 s，返回 s 中不同的非空「回文子序列」个数 。
 *	通过从 s 中删除 0 个或多个字符来获得子序列。
 *	如果一个字符序列与它反转后的字符序列一致，那么它是「回文字符序列」。
 *	如果有某个 i , 满足 ai != bi ，则两个序列 a1, a2, ... 和 b1, b2, ... 不同。
 *	注意：
 *	结果可能很大，你需要对 109 + 7 取模 。
 *
 *	Date	 : [ 2022/06/10 09:17:43 ]
 */
///	★★★★★ : dynamic / running timeout
/*
	public int countPalindromicSubsequences(String s) {
        int mod = 1000000007;
        int n = s.length();
        int[][] dp = new int[n][n];
        for (int i = 0; i < n; i++) {
            dp[i][i] = 1;
        }
        for (int len = 2; len <= n; len++) {
            for (int i = 0; i + len <= n; i++) {
                int j = i + len - 1;
                if (s.charAt(i) == s.charAt(j)) {
                    int left = i + 1;
                    int right = j - 1;
                    while (left <= right && s.charAt(left) != s.charAt(i)) {
                        left++;
                    }
                    while (left <= right && s.charAt(right) != s.charAt(j)) {
                        right--;
                    }
                    if (left > right) {
                        dp[i][j] = 2 * dp[i + 1][j - 1] + 2;
                    } else if (left == right) {
                        dp[i][j] = 2 * dp[i + 1][j - 1] + 1;
                    } else {
                        dp[i][j] = 2 * dp[i + 1][j - 1] - dp[left + 1][right - 1];
                    }
                } else {
                    dp[i][j] = dp[i][j - 1] + dp[i + 1][j] - dp[i + 1][j - 1];
                }
                dp[i][j] = (dp[i][j] >= 0) ? dp[i][j] % mod : dp[i][j] + mod;
            }
        }
        return dp[0][n - 1];
    }
*/
int HardQ::countPalindromicSubsequences(string s) {
	unordered_map<string, int> mp;
	int ans = 0;
	int mod = 1e9 + 7;
	function<bool(string)> isPalindromic = [&](string str) -> bool {
		bool is_Palindromic = true;
		int n = str.length();
		for (int i = 0; i < n / 2; i++)
		{
			if (str[i] != str[n - i - 1])
			{
				is_Palindromic = false;
				return is_Palindromic;
			}
		}
		return is_Palindromic;
	};
	queue<string> q;
	q.push(s);
	mp[s]++;
	while (!q.empty())
	{
		string temp(q.front());
		int n = temp.length();
		q.pop();
		if (isPalindromic(temp))
		{
			ans++;
		}
		if (n == 1)
		{
			continue;
		}
		for (int i = 0; i < n; i++)
		{
			string sub = temp.substr(0, i) + temp.substr(i + 1, n - 1);
			if (mp.count(sub) <= 0)
			{
				q.push(sub);
				if (sub[0] == sub[sub.length() - 1])
				{
					mp[sub]++;
				}
			}
		}
		ans %= mod;
	}
	return ans;
}