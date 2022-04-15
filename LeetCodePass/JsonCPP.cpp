#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <string>
#include <set>
#include <queue>
#include <functional>
#include <unordered_map>
#include <math.h>
#include <stdio.h>
#include "Tools.h"

using namespace std;

int numWays(int n, vector<vector<int>>& relation, int k) {
	vector<vector<int>> dp(k + 1, vector<int>(n, 0));
	dp[0][0] = 1;
	for (int i = 0; i < k; i++)
	{
		for (auto& edge : relation)
		{
			int src = edge[0], drc = edge[1];
			dp[i + 1][drc] += dp[i][src];
		}
	}
	return dp[k][n - 1];
}

int maxIceCream(vector<int>& costs, int coins) {
	int ans = 0;
	sort(costs.begin(), costs.end());
	unsigned int i = 0;
	while (i < costs.size() && coins >= costs[i])
	{
		ans++;
		coins -= costs[i];
		i++;
	}
	return ans;
}

int maxIceCreamDP(vector<int>& costs, int coins)
{
	int n = costs.size();
	vector<vector<int>> dp(n + 1, vector<int>(coins + 1, 0));
	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; j <= coins; j++)
		{
			if (j < costs[i - 1]) dp[i][j] = dp[i - 1][j];
			else
			{
				dp[i][j] = max(dp[i - 1][j - costs[i - 1]] + 1, dp[i - 1][j]);
			}
		}
	}
	return dp[n][coins];
}

int reverse(int x) {
	string  strBuffer = to_string(x);
	if (x < 0) strBuffer.erase(0, 1);
	int i = 0, n = strBuffer.length();
	for (; i < n / 2; i++)
	{
		swap(strBuffer[i], strBuffer[n - i - 1]);
	}
	if (x < 0) strBuffer = '-' + strBuffer;
	int ans = 0;
	try {
		ans = stoi(strBuffer);
	}
	catch (exception e){

	}
	return ans;
}

bool isPalindrome(int x) {
	string str = to_string(x);
	string strCompare = str;
	int n = str.length();
	for (int i = 0; i < n / 2; i++)
	{
		swap(str[i], str[n - i - 1]);
	}
	return (str.compare(strCompare) == 0);
}

bool isPalindrome_No_String(int x) {
	if (x < 0) return false;
	long long num = 0, temp = x;
	do
	{
		int mod = temp % 10;
		num = num * 10 + mod;
	}while (temp /= 10);
	return (num == x);
}

int romanToInt(string s) {
	enum roman {
		I = 1, V = 5, X = 10, L = 50, C = 100, D = 500, M = 1000
	};
	auto to_int = [&](char ch) -> int {
		switch (ch)
		{
		case 'I': return I;
		case 'V': return V;
		case 'X': return X;
		case 'L': return L;
		case 'C': return C;
		case 'D': return D;
		case 'M': return M;
		default:
			break;
		}
		return 0;
	};
	int i = 0, sum = 0;
	while (i < s.length())
	{
		if (i == s.length() - 1)
		{
			sum += to_int(s[i]);
			return sum;
		}
		int temp = to_int(s[i]);
		if (temp < to_int(s[i + 1])) temp = -temp;
		sum += temp;
		i++;
	}
	return sum;
}

string longestCommonPrefix(vector<string>& strs) {
	string ans = "";
	string comp = strs[0];
	for (int i = 0; i < comp.length(); i++)
	{
		char ch = comp.at(i);
		for (int j = 1; j < strs.size(); j++)
		{
			if (i >= strs[j].length()) return ans;
			if (ch != strs[j].at(i)) return ans;
		}
		ans += ch;
	}
	return ans;
}

string countOfAtoms(string formula) {
	vector<vector<string>> atoms;
	function<void(string, int)> recursion = [&](string str, int times)
	{
		string subStr = "";
		int signal = 0, subTimes = 0;
		bool is_number = false, is_ready = false;
		for (int i = 0; i < str.length(); i++)
		{
			if (str[i] == '(') signal++;
			else if (str[i] == ')')
			{
				signal--;
				if (signal == 0) is_ready = true;
			}
			if (is_ready)
			{
				if (i + 1 < str.length() && str.at(i + 1) >= '0' && str.at(i + 1) <= '9')
				{
					subTimes = (str.at(i + 1) - '0') + subTimes * 10;
					continue;
				}
				else if (subTimes == 0) subTimes = 1;
				subTimes *= times;
				recursion(subStr, subTimes);
				is_ready = false;
				subTimes = 0;
				subStr = "";
				continue;
			}
			if (signal > 1 || (signal == 1 && str[i] != '(')) subStr += str[i];
			else
			{
				if (str[i] >= 'A' && str[i] <= 'Z')
				{
					vector<string> temp;
					string s = "";
					s += str[i];
					temp.push_back(s);
					int count = 1 * times; 
					temp.push_back(to_string(count));
					atoms.push_back(temp);
					is_number = false;
				}
				else if (str[i] >= 'a' && str[i] <= 'z')
				{
					atoms[atoms.size() - 1][0] += str[i];
					is_number = false;
				}
				else if (str[i] >= '0' && str[i] <= '9')
				{
					if (is_number) atoms[atoms.size() - 1][2] += str[i];
					else
					{
						string s = "";
						s += str[i];
						atoms[atoms.size() - 1].push_back(s);
						is_number = true;
					}
				}
			}
		}
		return;
	};
	recursion(formula, 1);
	std::sort(atoms.begin(), atoms.end());
	string ans = "";
	int num = 0;
	for (int i = 0; i < atoms.size(); i++)
	{
		if (i != 0 && atoms[i][0] != atoms[i - 1][0])
		{
			if (num > 1) ans += to_string(num);
			num = 0;
		}
		if (atoms[i].size() > 2) { num += stoi(atoms[i][1]) * stoi(atoms[i][2]); }
		else { num += stoi(atoms[i][1]); }
		if (i != 0 && atoms[i][0] == atoms[i - 1][0]) continue;
		ans += atoms[i][0];
	}
	if (num > 1) ans += to_string(num);
	return ans;
}

vector<vector<string>> displayTable(vector<vector<string>>& orders) {
	vector<vector<string>> ans;
	//function of sort and cut duplicate units
	auto compare = [](string a, string b)
	{
		return stoi(a) < stoi(b);
	};
	auto sort_and_cut_dup = [&](vector<string>& vec)
	{
		set<string> s(vec.begin(), vec.end());
		vec.assign(s.begin(), s.end());
		if (vec[0][0] >= '0' && vec[0][0] <= '9') sort(vec.begin(), vec.end(), compare);
		else sort(vec.begin(), vec.end());
		return vec;
	};
	// push title and sort number
	vector<string> title, vec;
	for (auto order : orders)
	{
		title.push_back(order[2]);
		vec.push_back(order[1]);
	}
	vector<string> number = vec;
	sort_and_cut_dup(title);
	sort_and_cut_dup(number);
	title.insert(title.begin(), "Table");
	ans.push_back(title);
	// push digit
	for (auto str : number)
	{
		vector<string> digit(title.size(), "0");
		digit[0] = str;
		vector<string>::iterator it;
		int index = 0;
		while ((it = find(vec.begin() + index, vec.end(), str)) != vec.end())
		{
			index = distance(vec.begin(), it);
			vector<string>::iterator it2 = find(title.begin(), title.end(), orders[index][2]);
			int i = distance(title.begin(), it2);
			int num = stoi(digit[i]) + 1;
			digit[i] = to_string(num);
			index += 1;
		}
		ans.push_back(digit);
	}
	return ans;
}

///Overtime
int countPairs(vector<int>& deliciousness) {
	int ans = 0;
	set<int> s(deliciousness.begin(), deliciousness.end());
	vector<int> set(s.begin(), s.end());
	vector<int> counts;
	for (auto i : s)
	{
		int num = count(deliciousness.begin(), deliciousness.end(), i);
		counts.push_back(num);
	}
	for (int i = 0; i < set.size(); i++)
	{
		for (int j = i; j < set.size(); j++)
		{
			int n = set[i] + set[j];
			if (n && (n & (n - 1)) == 0)
			{
				if (i == j && counts[i] > 1)
				{
					ans += ((counts[i] - 1) * counts[i]) / 2;
				}
				else if (i != j)
				{
					ans += counts[i] * counts[j];
				}
			}
		}
	}
	return ans % 1000000007;
} 

int numSubarraysWithSum(vector<int>& nums, int goal) {
	//  1 <= nums.length <= 3 * 104
	//	nums[i] 不是 0 就是 1
	//	0 <= goal <= nums.length
	int ans = 0;
	function<void(vector<int>)> recursion = [&](vector<int> nums)
	{
		int sum = 0;
		for (auto& i : nums)
		{
			sum += i;
			if (sum == goal) ans++;
			if (sum > goal) break;
		}
		if (nums.begin() + 1 >= nums.end()) return;
		vector<int> temp(nums.begin() + 1, nums.end());
		recursion(temp);
	};
	recursion(nums);
	return ans;
}
///HashMap

vector<int> findErrorNums(vector<int>& nums) {
	vector<int> ans;
	int loss = 0, more = 0;
	unordered_map<int, int> mp;
	for (auto& i : nums)
	{
		mp[i]++;
	}
	for (int i = 1; i <= nums.size(); i++)
	{
		if (mp.count(i) == 0) loss = i;
		else if (mp[i] == 2) more = i;
	}
	ans.push_back(more);
	ans.push_back(loss);
	return ans;
}

bool isValid(string s) {
	stack<char> st;
	for (auto& ch : s)
	{
		if (st.empty()) st.push(ch);
		else if (st.top() == '(' && ch == ')' || st.top() == '{' && ch == '}' || st.top() == '[' && ch == ']') st.pop();
		else st.push(ch);
	}
	if (st.empty()) return true;
	return false;
}

int hIndex(vector<int>& citations) {
	int n = citations.size();
	int sum = 0;
	for (int i = n; i > 0; i--)
	{
		if (citations[i - 1] < n - i + 1) break;
		sum++;
	}
	return sum;
}

int removeDuplicates(vector<int>& nums) {
	for (int i = 1; i < nums.size(); i++)
	{
		if (nums[i] == nums[i - 1])
		{
			nums.erase(nums.begin() + i);
			i--;
		}
	}
	return nums.size();
}

int removeElement(vector<int>& nums, int val) {
	int fast = 0, slow = 0;
	while (fast < nums.size())
	{
		if (nums[fast] != val)
		{
			nums[slow] = nums[fast];
			slow++;
		}
		fast++;
	}
	return slow;
}

int strStr(string haystack, string needle) {
	auto getNextval = [&](string needle, vector<int>& nextval)
	{
		int i = 0, j = -1;
		nextval[0] = -1;
		while (i < needle.length() - 1)
		{
			if (j == -1 || needle.at(i) == needle.at(j))
			{
				i++; j++;
				if (needle.at(i) != needle.at(j)) 
					nextval[i] = j;
				else 
					nextval[i] = nextval[j];
			}
			else 
				j = nextval[j];
		}
	};

	int haystackLen = haystack.length(), needleLen = needle.length();
	if (haystackLen < needleLen) return -1;
	if (needleLen == 0) return 0;
	vector<int> nextval(needleLen, 0);
	getNextval(needle, nextval);

	int i = 0, j = 0;
	while (i < haystackLen && j < needleLen)
	{
		if (j == -1 || haystack.at(i) == needle.at(j))
		{
			i++; j++;
		}
		else
		{
			j = nextval[j];
		}
	}
	if (j >= needleLen)
		return i - needleLen;
	return -1;
}

int searchInsert(vector<int>& nums, int target) {
	int index = 0;
	for (index = 0; index < nums.size(); index++)
	{
		if (nums[index] >= target) break;
	}
	return index;
}

///Overtime :)
int minAbsoluteSumDiff(vector<int>& nums1, vector<int>& nums2) {
	int sum = 0;
	static int MOD = 1e9 + 7;
	int n = nums1.size();
	vector<vector<int>> diff(n, vector<int>(2, 0));
	for (int i = 0; i < n; i++)
	{
		int temp = abs(nums1[i] - nums2[i]);
		sum = (sum + temp) % MOD;
		vector<int> vec;
		vec.push_back(temp);
		vec.push_back(nums2[i]);
		diff[i] = vec;
	}
	auto comp = [](vector<int> a, vector<int> b)
	{
		return a[0] > b[0];
	};
	sort(diff.begin(), diff.end(), comp);
	int max = 0;
	for (auto& vec : diff)
	{
		int dis = 0;
		for (int i = 0; i < nums1.size() + 1 / 2; i++)
		{
			int temp = abs(nums1[i] - vec[1]) < abs(nums1[n - i - 1] - vec[1]) ? abs(nums1[i] - vec[1]) : abs(nums1[n - i - 1] - vec[1]);
			dis = vec[0] - temp;
			max = max < dis ? dis : max;
			if (temp <= 0)
			{
				sum -= max;
				return sum % MOD;
			}
		}
	}
	sum -= max;
	return sum % MOD;
}

int maxProfit(vector<int>& prices) {
	int nMax = 0;
	for (int i = 0; i < prices.size(); i++)
	{
		for (int j = i + 1; j < prices.size(); j++)
		{
			int temp = prices[j] - prices[i];
			nMax = max(nMax, temp);
		}
	}
	return nMax;
}

int climbStairs(int n) {
	int sum = 0;
	function<void(int)> dps = [&](int n)
	{
		if (n == 0)
		{
			sum++;
			return;
		}
		else if (n < 0) return;
		dps(n - 1);
		dps(n - 2);
	};
	dps(n);
	return sum;
}

int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
	int n = profits.size();
	int times = k > n ? n : k;
	int nIndex = 0;
	vector<bool> b_has(n, false);
	vector<vector<int>> dp(times, vector<int>(n + 1, w));
	for (int i = 0; i < times; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (w >= capital[j - 1] && !b_has[j - 1])
			{
				if (w + profits[j - 1] > dp[i][j - 1])
				{
					dp[i][j] = w + profits[j - 1];
					nIndex = j - 1;
				}
				else
				{
					dp[i][j] = dp[i][j - 1];
				}
			}
			else
			{
				dp[i][j] = dp[i][j - 1];
			}
		}
		b_has[nIndex] = true;
		w = dp[i][n] > w ? dp[i][n] : w;
	}
	return w;
}
///DP
int maxSubArray(vector<int>& nums) {
	int iMax = -100'000, iMaxIndex = 0, iMin = 1000'000'000, iMinIndex = 0, sum = 0;
	unordered_map<int, int> mp;
	for (int i = 0; i < nums.size(); i++)
	{
		sum += nums[i];
		mp[i] = sum;
		//iMax = iMax < mp[i] ? mp[i] : iMax;
		//for (int j = 0; j < i; j++)
		//{
		//	iMax = mp[i] - mp[j] > iMax ? mp[i] - mp[j] : iMax;
		//}
	}
	return iMax;
}
///

int maximumElementAfterDecrementingAndRearranging(vector<int>& arr) {
	sort(arr.begin(), arr.end());
	arr[0] = 1;
	for (int i = 1; i < arr.size(); i++)
	{
		if (abs(arr[i] - arr[i - 1]) > 1) arr[i] = arr[i - 1] + 1;
	}
	return arr[arr.size() - 1];
}

int rob(vector<int>& nums) {
	vector<int> dp(nums.size() + 2, 0);
	for (int i = 0; i < nums.size(); i++)
	{
		dp[i + 2] = max(dp[i] + nums[i], dp[i + 1]);
	}
	return dp[dp.size() - 1];
}

int search(vector<int>& nums, int target) {
	int low = 0, up = 0;
	low = lower_bound(nums.begin(), nums.end(), target) - nums.begin();
	up = upper_bound(nums.begin(), nums.end(), target) - nums.begin();
	if (low >= nums.size() || nums[low] != target) return 0;
	else return up - low;
}

int minPairSum(vector<int>& nums) {
	sort(nums.begin(), nums.end());
	vector<int> sum;
	int n = nums.size();
	for (int i = 0; i < n / 2; i++)
	{
		sum.push_back(nums[i] + nums[n - i - 1]);
	}
	sort(sum.begin(), sum.end());
	return sum[sum.size() - 1];
}

int lengthOfLastWord(string s) {
	while (s.length() >= 1 && s[s.length() - 1] == ' ') s.erase(s.end() - 1);
	int index = s.rfind(" ");
	return s.length() - index - 1;
}

vector<int> plusOne(vector<int>& digits) {
	/* 1<= digits.size() <= 100
	int num = 0;
	for (int i = 0; i < digits.size(); i++)
	{
		num = num * 10 + digits[i];
	}
	num += 1;
	vector<int> plus;
	while (num)
	{
		plus.push_back(num % 10);
		num /= 10;
	}
	reverse(plus.begin(), plus.end());
	return plus;
	*/
	int n = digits.size();
	int i = n - 1;
	while (i >= 0)
	{
		digits[i] += 1;
		if (digits[i] != 10)
		{
			break;
		}
		digits[i] = 0;
		i--;
	}
	if (i < 0)
	{
		digits.insert(digits.begin(), 1);
	}
	return digits;
}

//Definition for singly-linked list.
 struct ListNode {
     int val;
     ListNode *next;
	 ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(NULL) {}
	 ListNode(int x, ListNode *next) : val(x), next(next) {}
 };

ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
	int lenA = 0, lenB = 0;
	for (ListNode* head = headA; head != NULL; head = head->next)
		lenA++;
	for (ListNode* head = headB; head != NULL; head = head->next)
		lenB++;
	int len = min(lenA, lenB);
	ListNode *pA = headA, *pB = headB;
	for (int i = lenA - len; i > 0; i--)
		pA = pA->next;
	for (int i = lenB - len; i > 0; i--)
		pB = pB->next;
	for (int i = 0; i < len; i++)
	{
		if (pA == pB) break;
		pA = pA->next;
		pB = pB->next;
	}
	return pA;
}

ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
	ListNode *head = new ListNode(-1), *p3 = head;
	ListNode *p1 = l1;
	ListNode *p2 = l2;
	while (p1 && p2)
	{
		if (p1->val < p2->val)
		{
			p3->next = p1;
			p1 = p1->next;
		}
		else
		{
			p3->next = p2;
			p2 = p2->next;
		}
		p3 = p3->next;
	}
	if (p1) p3->next = p1;
	if (p2) p3->next = p2;
	return head->next;
}

ListNode* deleteDuplicates(ListNode* head) {
	unordered_map<int, int> mp;
	if (head == NULL)
	{
		return head;
	}
	ListNode* p = head;
	mp[p->val]++;
	while (p && p->next)
	{
		if(mp[p->next->val] <= 0)
		{
			mp[p->next->val]++;
			p = p->next;
		}
		else 
		{
			ListNode* tp = p->next;
			p->next = tp->next;
		}
	}
	return head;
}

ListNode* getKthFromEnd(ListNode* head, int k) {
	ListNode *p1 = head;
	int nlen = 0;
	while (p1 != nullptr)
	{
		p1 = p1->next;
		nlen++;
	}
	p1 = head;
	for (int i = 0; i < nlen - k; i++)
	{
		p1 = p1->next;
	}
	return p1;
}
////////////////////////////////////

string addBinary(string a, string b) {
	string ans = "";
	int na = a.length(), nb = b.length();
	int i = na - 1, j = nb - 1, plus = 0;
	char ch;
	while (i >= 0 && j >= 0)
	{
		if (a.at(i) == '1' && b.at(j) == '1')
		{
			ch = '0' + plus;
			ans = ch + ans;
			plus = 1;
		}
		else if (a.at(i) == '0' && b.at(j) == '1' || a.at(i) == '1' && b.at(j) == '0')
		{
			if (plus) ch = '0';
			else ch = '1';
			ans = ch + ans;
		}
		else if (a.at(i) == '0' && b.at(j) == '0')
		{
			ch = '0' + plus;
			ans = ch + ans;
			if (plus) plus = 0;
		}
		i--; j--;
	}
	while (i >= 0)
	{
		ch = a.at(i) + plus;
		if (ch == '2') ch = '0';
		else plus = 0;
		ans = ch + ans;
		i--;
	}
	while (j >= 0)
	{
		ch = b.at(j) + plus;
		if (ch == '2') ch = '0';
		else plus = 0;
		ans = ch + ans;
		j--;
	}
	if (plus > 0) ans = '1' + ans;
	return ans;
}

int mySqrt(int x) {
	int i = 0;
	while ((long long)i * i < x) i++;
	if ((long long)i * i == x) return i;
	return i - 1;
}

// Definition for a Node.
class Node {
	public:
	int val;
	Node* next;
	Node* random;

	Node(int _val) {
	val = _val;
	next = NULL;
	random = NULL;
	}
};
Node* copyRandomList(Node* head) {
	Node* ans = new Node(-1);
	Node* p2 = ans;
	vector<Node*> dic;
	Node* p1 = head;
	int i = 0;
	while (p1)
	{
		Node* temp = new Node(p1->val);
		p2->next = temp;
		p2 = p2->next;
		dic.push_back(p2);
		p1->val = i;
		i++;
		p1 = p1->next;
	}
	vector<int> index;
	p1 = head;
	while (p1)
	{
		if (p1->random == NULL)
			index.push_back(-1);
		else
			index.push_back(p1->random->val);
		p1 = p1->next;
	}
	p2 = ans->next;
	i = 0;
	while (p2)
	{
		if (index[i] != -1)
			p2->random = dic[index[i]];
		p2 = p2->next;
		i++;
	}
	return ans->next;
}
////////////////////////

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
	vector<int> ans;
	return ans;
}

vector<int> pathInZigZagTree(int label) {
	vector<int> ans;
	int h = 0;
	int leaf = 1;
	while (label > leaf)
	{
		h++;
		leaf <<= 1;
		leaf += 1;
	}
	ans.push_back(1);
	while (label)
	{
		if (label - pow(2, h - 1) + 1 > pow(2, h - 2))
		{

		}
	}
	return ans;
}

vector<int> inorderTraversal(TreeNode* root) {
	vector<int> ans;
	function<void(TreeNode*)> dps = [&](TreeNode* root)
	{
		if (root == NULL)
		{
			return;
		}
		if (root->left != NULL)
		{
			dps(root->left);
		}
		ans.push_back(root->val);
		if (root->right != NULL)
		{
			dps(root->right);
		}
	};
	dps(root);
	return ans;
}

bool isSameTree(TreeNode* p, TreeNode* q) {
	if (p == nullptr && q == nullptr) return true;
	if (p == nullptr || q == nullptr) return false;
	TreeNode* null = new TreeNode();
	queue<TreeNode*> pQ, qQ;
	pQ.push(p); qQ.push(q);
	while (!pQ.empty() && !qQ.empty())
	{
		if (pQ.front() == null)
		{
			if (qQ.front() != null) return false;
			pQ.pop(); qQ.pop();
			continue;
		}
		if (pQ.front()->val != qQ.front()->val) return false;
		if (pQ.front()->left != NULL)
		{
			pQ.push(pQ.front()->left);
		}
		else
		{
			pQ.push(null);
		}
		if (pQ.front()->right != NULL)
		{
			pQ.push(pQ.front()->right);
		}
		else
		{
			pQ.push(null);
		}
		if (qQ.front()->left != NULL)
		{
			qQ.push(qQ.front()->left);
		}
		else
		{
			qQ.push(null);
		}
		if (qQ.front()->right != NULL)
		{
			qQ.push(qQ.front()->right);
		}
		else
		{
			qQ.push(null);
		}
		pQ.pop(); qQ.pop();
	}
	return true;
}

int maxDepth(TreeNode* root) {
	int max = 0;
	function<void(int, TreeNode*)> dps = [&](int depth, TreeNode* p)
	{
		if (p == nullptr)
		{
			max = max < depth ? depth : max;
			return;
		}
		dps(depth + 1, p->left);
		dps(depth + 1, p->right);
	};
	dps(0, root);
	return max;
}

bool isSymmetric(TreeNode* root) {
	function<bool(TreeNode*, TreeNode*)> check = [&](TreeNode *p, TreeNode *q) {
		if (!p && !q) return true;
		if (!p || !q) return false;
		return p->val == q->val && check(p->left, q->right) && check(p->right, q->left);
	};
	return check(root->left, root->right);
}

TreeNode* sortedArrayToBST(vector<int>& nums) {
	function<TreeNode*(int, int)> bst = [&](int start, int end) -> TreeNode*
	{
		if (start >= end) return NULL;
		int mid = (end + start) / 2;
		TreeNode* p = new TreeNode(nums[mid]);
		p->left = bst(start, mid);
		p->right = bst(mid + 1, end);
		return p;
	};
	TreeNode* root = bst(0, nums.size());
	return root;
}

bool isBalanced(TreeNode* root) {
	function<int(TreeNode*)> dps = [&](TreeNode* p) -> int
	{
		if (p == NULL) {
			return 0;
		}
		else {
			return max(dps(p->left), dps(p->right)) + 1;
		}
	};
	function<bool(TreeNode*)> balanced = [&](TreeNode* p) -> bool
	{
		if (p == NULL) {
			return true;
		}
		else {
			return abs(dps(p->left) - dps(p->right)) <= 1 && balanced(p->left) && balanced(p->right);
		}
	};
	return balanced(root);
}

int minDepth(TreeNode* root) {
	int minDep = 1e9;
	function<void(int, TreeNode*)> dps = [&](int h, TreeNode* p)
	{
		if (p == NULL)
		{
			return;
		}
		if (p->left == NULL && p->right == NULL) {
			minDep = minDep < h ? minDep : h;
			return;
		}
		dps(h + 1, p->left);
		dps(h + 1, p->right);
	};
	if (root == NULL)
	{
		return 0;
	}
	dps(1, root);
	return minDep;
}

bool hasPathSum(TreeNode* root, int targetSum) {
	bool has_path = false;
	function<void(int, TreeNode*)> dps = [&](int sum, TreeNode* p)
	{
		if (p == NULL)
		{
			return;
		}
		if (p->left == NULL && p->right == NULL)
		{
			sum += p->val;
			if (sum == targetSum)
			{
				has_path = true;
				return;
			}
		}
		dps(sum + p->val, p->left);
		dps(sum + p->val, p->right);
	};
	dps(0, root);
	return has_path;
}

vector<int> preorderTraversal(TreeNode* root) {
	vector<int> ans;
	function<void(TreeNode*)> dps = [&](TreeNode *p)
	{
		if (p == NULL)
		{
			return;
		}
		ans.push_back(p->val);
		dps(p->left);
		dps(p->right);
	};
	dps(root);
	return ans;
}

vector<int> postorderTraversal(TreeNode* root) {
	vector<int> ans;
	function<void(TreeNode*)> dps = [&](TreeNode *p)
	{
		if (p == NULL)
		{
			return;
		}
		dps(p->left);
		dps(p->right);
		ans.push_back(p->val);
	};
	dps(root);
	return ans;
}

////////////////////////////////////

bool isCovered(vector<vector<int>>& ranges, int left, int right) {
	auto comp = [](vector<int> a, vector<int> b)
	{
		return a[0] < b[0];
	};
	sort(ranges.begin(), ranges.end(), comp);
	for (auto vec : ranges)
	{
		if (vec[0] <= left && vec[1] >= left)
		{
			left = vec[1] + 1;
		}
		if (left > right)
		{
			return true;
		}
	}
	return false;
}

int titleToNumber(string columnTitle) {
	int x = 26, y = 0;
	int sum = 0;
	for (int i = columnTitle.length() - 1; i >= 0; i--)
	{
		sum += (columnTitle[i] - 'A' + 1) * pow(x, y);
		y++;
	}
	return sum;
}

void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
	if (n == 0) return;
	if (m == 0)
	{
		nums1 = nums2;
		return;
	}
	while (nums1.back() == 0 && nums1.size() > m) nums1.erase(nums1.end() - 1);
	for (auto& i : nums2)
	{
		vector<int>::iterator it;
		it = lower_bound(nums1.begin(), nums1.end(), i);
		nums1.insert(it, i);
	}
}

int nthSuperUglyNumber(int n, vector<int>& primes) {
	int goal = 1, num = primes[0];
	for (int i = 2; i <= n; i++)
	{
		int j = 0, temp = num;
		while (j < primes.size())
		{
			if (temp == 1)
			{
				goal = num;
				break;
			}
			if (temp % primes[j] == 0)
			{
				temp /= primes[j];
			}
			else {
				j++;
			}
		}
		num++;
	}
	return goal;
}

int getMaximumGenerated(int n) {
	vector<int> dp;
	dp.push_back(0); dp.push_back(1);
	if (n == 0)
	{
		return dp[0];
	}
	int i = 1, imax = 1;
	while (n)
	{
		if (2 * i <= n)
		{
			dp.push_back(dp[i]);
			imax = max(imax, dp[dp.size() - 1]);
		}
		else
		{
			break;
		}
		if (2 * i + 1 <= n)
		{
			dp.push_back(dp[i] + dp[i + 1]);
			imax = max(imax, dp[dp.size() - 1]);
		}
		else
		{
			break;
		}
		i++;
	}
	return imax;
}

vector<int> getConcatenation(vector<int>& nums) {
	vector<int> ans = nums;
	for (auto i : nums)
	{
		ans.push_back(i);
	}
	return ans;
}

vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
	vector<vector<int>> ans;
	vector<int> path;
	int n = graph.size();
	path.push_back(0);
	function<void(vector<int>)> dfs = [&](vector<int> path)
	{
		int point = path[path.size() - 1];
		if (point == n - 1)
		{
			ans.push_back(path);
			return;
		}
		for (auto i : graph[point])
		{
			path.push_back(i);
			dfs(path);
			path.pop_back();
		}
	};
	dfs(path);
	return ans;
}

int singleNumber(vector<int>& nums) {
	int flag = 0;
	for (auto i : nums)
	{
		flag ^= i;
	}
	return flag;
}

int numRescueBoats(vector<int>& people, int limit) {
	int ans = 0;
	sort(people.begin(), people.end());
	int i = 0, j = people.size() - 1;
	while (i <= j)
	{
		if (people[i] + people[j] <= limit)
		{
			ans++;
			i++;
			j--;
		}
		else
		{
			ans++;
			j--;
		}
	}
	return ans;
}

int maxProfitPlus(vector<int>& prices) {
	int sum = 0;
	for (int i = 1; i < prices.size(); i++)
	{
		if (prices[i - 1] < prices[i])
		{
			sum += prices[i] - prices[i - 1];
		}
	}
	return sum;
}

int compareVersion(string version1, string version2) {
	version1 += ".";
	version2 += ".";
	int nEnd1 = version1.find('.'), nEnd2 = version2.find('.'), nStart1 = 0, nStart2 = 0;
	string str;
	int num1 = 0, num2 = 0;
	while (nEnd1 != -1 && nEnd2 != -1)
	{
		str.assign(version1.begin() + nStart1, version1.begin() + nEnd1);
		num1 = stoi(str);
		str.assign(version2.begin() + nStart2, version2.begin() + nEnd2);
		num2 = stoi(str);
		if (num1 > num2)
		{
			return 1;
		}
		else if (num1 < num2)
		{
			return -1;
		}
		nStart1 = nEnd1 + 1;
		nStart2 = nEnd2 + 1;
		nEnd1 = version1.find('.', nStart1);
		nEnd2 = version2.find('.', nStart2);
	}
	while (nEnd1 != -1)
	{
		str.assign(version1.begin() + nStart1, version1.begin() + nEnd1);
		num1 = stoi(str);
		if (num1 != 0)
		{
			return 1;
		}
		nStart1 = nEnd1 + 1;
		nEnd1 = version1.find('.', nStart1);
	}
	while (nEnd2 != -1)
	{
		str.assign(version2.begin() + nStart2, version2.begin() + nEnd2);
		num2 = stoi(str);
		if (num2 != 0)
		{
			return -1;
		}
		nStart2 = nEnd2 + 1;
		nEnd2 = version2.find('.', nStart2);
	}
	return 0;
}

vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
	vector<int> ans;
	unordered_map<int, int> mp;
	int j = 0;
	bool bn = false;
	for (auto i : nums1)
	{
		bn = false;
		if (mp.count(i) > 0)
		{
			j = mp[i] + 1;
			bn = true;
		}
		for (; j < nums2.size(); j++)
		{
			mp[nums2[j]] = j;
			if (nums2[j] == i)
			{
				bn = true;
			}
			else if (nums2[j] > i && bn)
			{
				ans.push_back(nums2[j]);
				break;
			}
		}
		if (j >= nums2.size())
		{
			ans.push_back(-1);
		}
	}
	return ans;
}

int Search(vector<int>& nums, int target) {
	int nLen = nums.size();
	int nStart = 0, nEnd = nLen, nMid = (nEnd + nStart) / 2;
	while (nStart < nEnd)
	{
		if (nums[nMid] == target) return nMid;
		else if (nums[nMid] > target)
		{
			nEnd = nMid;
			nMid = (nEnd + nStart) / 2;
		}
		else if (nums[nMid] < target)
		{
			nStart = nMid + 1;
			nMid = (nEnd + nStart) / 2;
		}
	}
	return -1;
}

int dayOfYear(string date) {
	int monthDay[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	int ans = 0;
	string strYear, strMonth, strDay;
	int nYear = 2021, nMonth = 9, nDay = 6;
	strYear.append(date, 0, 4);
	strMonth.append(date, 5, 2);
	strDay.append(date, 8, 2);
	nYear = stoi(strYear);
	nMonth = stoi(strMonth);
	nDay = stoi(strDay);
	for (int i = 0; i < nMonth; i++)
	{
		if (nYear % 4 == 0 && i == 2)
		{
			ans += 1;
		}
		ans += monthDay[i];
	}
	ans += nDay;
	return ans;
}

int countCharacters(vector<string>& words, string chars) {
	int ans = 0;
	unordered_map<char, int> mp, mpw;
	bool is_membery = true;
	for (auto ch : chars)
	{
		mp[ch]++;
	}
	for (auto str : words)
	{
		is_membery = true;
		mpw.clear();
		for (auto ch : str)
		{
			mpw[ch]++;
			if (mpw[ch] > mp[ch])
			{
				is_membery = false;
				break;
			}
		}
		if (is_membery)
		{
			ans += str.length();
		}
	}
	return ans;
}

int distanceBetweenBusStops(vector<int>& distance, int start, int destination) {
	int clockwise = 0, anti = 0;
	int n = distance.size();
	int i = 0;
	for (i = start; (i + 1) % n != destination; i++)
	{
		clockwise += distance[i % n];
	}
	clockwise += distance[i % n];
	for (i = start; (i - 1 + n) % n != destination; i--)
	{
		anti += distance[(i - 1 + n) % n];
	}
	anti += distance[(i - 1 + n) % n];
	return min(clockwise, anti);
}

string dayOfTheWeek(int day, int month, int year) {
	string week[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
	function<int(int, int, int)> dayOfYear = [&](int day, int month, int year) -> int
	{
		if (month == 1 || month == 2) {
			month += 12;
			year--;
		}
		int iWeek = (day + 2 * month + 3 * (month + 1) / 5 + year + year / 4 - year / 100 + year / 400) % 7;
		return iWeek + 1;
	};
	return week[dayOfYear(day, month, year) % 7];
}

int balancedStringSplit(string s) {
	int balance = 0;
	int ans = 0;
	for (auto ch : s)
	{
		if (ch == 'L')
		{
			balance++;
		}
		else if (ch == 'R')
		{
			balance--;
		}
		if (balance == 0)
		{
			ans++;
		}
	}
	return ans;
}

vector<vector<int>> generate(int numRows) {
	vector<vector<int>> ans;
	for (int i = 0; i < numRows; i++)
	{
		vector<int> row(i + 1, 1);
		for (int j = 1; j < row.size() - 1; j++)
		{
			row[j] = ans[i - 1][j - 1] + ans[i - 1][j];
		}
		ans.push_back(row);
	}
	return ans;
}

vector<int> getRow(int rowIndex) {
	vector<int> ans;
	for (int i = 0; i <= rowIndex; i++)
	{
		vector<int> row(i + 1, 1);
		for (int j = 1; j < row.size() - 1; j++)
		{
			row[j] = ans[j - 1] + ans[j];
		}
		ans = row;
	}
	return ans;
}

bool isPalindrome(string s) {
	string str;
	for (auto ch : s)
	{
		if (isalnum(ch)) // isalnum - Check if character is alphanumeric
		{
			str += tolower(ch);
		}
	}
	string temp(str.rbegin(), str.rend());
	return temp == str;
}

vector<string> fullJustify(vector<string>& words, int maxWidth) {
	vector<string> ans;
	string row = "";
	int width = 0, num = 0;
	for (int i = 0; i < words.size();)
	{
		if (width + words[i].size() + num - 1 < maxWidth)
		{
			if (row != "")
			{
				row += " ";
			}
			row += words[i];
			width += words[i].length();
			num++;
			i++;
		}
		else
		{
			width = row.size();
			int div = maxWidth - width;
			if (num != 1)
			{
				int avr = div / (num - 1);
				int plus = div % (num - 1);
				int index = -1;
				if (div != 0)
				{
					string space = " ";
					for (int j = 0; j < avr; j++)
					{
						space += " ";
					}
					for (int j = 0; j < num - 1; j++)
					{
						index = row.find(" ", index + 1);
						row.replace(index, 1, space);
						if (plus > 0)
						{
							row.insert(index, " ");
							index += 1;
							plus--;
						}
						index += avr;
					}
				}
			}
			else
			{
				row.append(div, ' ');
			}
			ans.push_back(row);
			row = "";
			width = 0;
			num = 0;
		}
	}
	width = row.length();
	for (int i = 0; i < maxWidth - width; i++)
	{
		row += " ";
	}
	ans.push_back(row);
	return ans;
}

int chalkReplacer(vector<int>& chalk, int k) {
	long long sum = 0;
	for (auto i : chalk)
	{
		sum += i;
	}
	int last = k % sum;
	for (int i = 0; i < chalk.size(); i++)
	{
		if (last < chalk[i])
		{
			return i;
		}
		last -= chalk[i];
	}
	return 0;
}

int findComplement(int num) {
	int bit = 0, temp = 0;
	bit = log2((double)num);
	bit += 1;
	for (int i = 0; i < bit; i++)
	{
		temp <<= 1;
		temp += 1;
	}
	return temp^num;
}

int minMoves(vector<int>& nums) {
	sort(nums.begin(), nums.end());
	int ans = 0, nlen = nums.size();
	int a = 0, b = 0, nMax = 1;
	int aStep = 0;
	for (int i = nlen - 1; i > 0; i--)
	{
		b = (nums[nlen - 1] + aStep - nums[i - 1] - ans) * nMax;
		a = b - (b / nMax);
		ans += b;
		aStep += a;
		nMax++;
	}
	return ans;
}

class MinStack {
public:
	MinStack() {
		nMin = 0;
		nlength = 0;
	}

	void push(int val) {
		stack.push_back(val);
		nlength++;
		if (stack[nMin] > val)
		{
			nMin = nlength - 1;
		}
	}

	void pop() {
		stack.pop_back();
		nlength--;
		if (nMin == stack.size())
		{
			nMin = 0;
			for (int i = 0; i <= nlength /2 && i <= nlength - i - 1; i++)
			{
				int val = stack[i] < stack[nlength - i - 1] ? i : nlength - i - 1;
				nMin = stack[nMin] > stack[val] ? val : nMin;
			}
		}
	}

	int top() {
		return stack.back();
	}

	int getMin() {
		return stack[nMin];
	}
private:
	vector<int> stack;
	int nlength;
	int nMin;
};

vector<int> majorityElement(vector<int>& nums) {
	vector<int> ans;
	int n = nums.size();
	int line = n / 3;
	unordered_map<int, int> mp;
	for (auto i : nums)
	{
		mp[i]++;
		if (mp[i] == line + 1)
		{
			ans.push_back(i);
		}
	}
	return ans;
}

vector<int> twoSum(vector<int>& numbers, int target) {
	vector<int> ans;
	int front = 0, rear = numbers.size() - 1;
	while (front < rear)
	{
		int nFront = numbers[front], nRear = numbers[rear];
		if (nFront + nRear == target)
		{
			ans.push_back(front + 1);
			ans.push_back(rear + 1);
			break;
		}
		else if (nFront + nRear < target)
		{
			front++;
		}
		else if (nFront + nRear > target)
		{
			rear--;
		}
	}
	return ans;
}

bool searchMatrix(vector<vector<int>>& matrix, int target) {
	/*
	int m = matrix.size(), n = matrix[0].size();
	for (auto i : matrix)
	{
		if (target < i[0])
		{
			return false;
		}
		for (; n > 0; n--)
		{
			cout << i[n - 1] << ' ';
			if (target == i[n - 1])
			{
				return true;
			}
			else if (target > i[n - 1])
			{
				break;
			}
		}
	}
	return false;

	*/
	int m = matrix.size(), n = matrix[0].size();
	int x = 0, y = n - 1;
	while (x < m && y >= 0) {
		cout << matrix[x][y] << ' ';
		if (matrix[x][y] == target) {
			return true;
		}
		if (matrix[x][y] > target) {
			--y;
		}
		else {
			++x;
		}
	}
	return false;
}

vector<string> removeInvalidParentheses(string s) {
	vector<string> res;
	function<bool(string)> is_valid = [&](string s) -> bool
	{
		int bCount = 0;
		for (auto a : s)
		{
			if (a == '(')
			{
				bCount++;
			}
			else if (a == ')')
			{
				bCount--;
			}
			if (bCount < 0)
			{
				return false;
			}
		}
		return true;
	};
	function<void(string, int, int, int)> Backtracking = [&](string str, int start, int l, int r)
	{
		if (l == 0 && r == 0) {
			if (is_valid(str)) {
				res.push_back(str);
			}
			return;
		}
		for (int i = start; i < str.size(); i++) {
			if (i != start && str[i] == str[i - 1]) {
				continue;
			}
			if (l + r > str.size() - i) {
				return;
			}
			if (l > 0 && str[i] == '(') {
				Backtracking(str.substr(0, i) + str.substr(i + 1), i, l - 1, r);
			}
			if (r > 0 && str[i] == ')') {
				Backtracking(str.substr(0, i) + str.substr(i + 1), i, l, r - 1);
			}
		}
	};
	int lr = 0, rr = 0;
	for (auto ch : s)
	{
		if (ch == '(')
		{
			lr++;
		}
		else if (ch == ')')
		{
			if (lr <= 0)
			{
				rr++;
			}
			else
			{
				lr--;
			}
		}
	}
	Backtracking(s, 0, lr, rr);
	return res;
}

int majorityElement2(vector<int>& nums) {
	int n = nums[0], nCount = 1;
	for (int i = 1; i < nums.size(); i++)
	{
		if (nCount == 0)
		{
			n = nums[i];
		}
		if (nums[i] != n)
		{
			nCount--;
		}
		else
		{
			nCount++;
		}
	}
	nCount = 0;
	for (auto i : nums)
	{
		if (i == n)
		{
			nCount++;
		}
	}
	if (nCount > nums.size()/2)
	{
		return n;
	}
	return -1;
}

//int main()
//{
//	string strFilePath = "C:/Users/aryay/Desktop/Data.txt";
//	vector<int> nums;
//	//vector<vector<int>> nums;
//	//int target = 0;
//	readStream(strFilePath, nums);
//	majorityElement2(nums);
//	system("pause");
//	return 0;
//}
