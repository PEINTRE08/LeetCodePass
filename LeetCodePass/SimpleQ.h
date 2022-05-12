#pragma once
#include "QHeader.h"


/*
 *	Question : 剑指 Offer 09. 用两个栈实现队列
 *	用两个栈实现一个队列。队列的声明如下，请实现它的两个函数 appendTail 和 deleteHead ，
 *	分别完成在队列尾部插入整数和在队列头部删除整数的功能。(若队列中没有元素，deleteHead 操作返回 -1 )
 *	
 *	Date	 : [ 2022/04/28 10:27:36 ]
 */
/**
* Your CQueue object will be instantiated and called as such:
* CQueue* obj = new CQueue();
* obj->appendTail(value);
* int param_2 = obj->deleteHead();
*/
class CQueue {
public:
	CQueue() {

	}

	void appendTail(int value) {
		sAppend.push(value);
	}

	int deleteHead() {
		if (sDelete.size() == 0)
		{
			while (!sAppend.empty())
			{
				sDelete.push(sAppend.top());
				sAppend.pop();
			}
		}
		if (sDelete.size() == 0)
		{
			return -1;
		}
		int head = sDelete.top();
		sDelete.pop();
		return head;
	}
private:
	stack<int> sAppend, sDelete;
};

class SimpleQ
{
public:
	SimpleQ();
	~SimpleQ();
	vector<int> numberOfLines(vector<int>& widths, string s);
	int maximumWealth(vector<vector<int>>& accounts);
	uint32_t reverseBits(uint32_t n);
	int hammingWeight(uint32_t n);
	string mostCommonWord(string paragraph, vector<string>& banned);
	vector<int> shortestToChar(string s, char c);
	string toGoatLatin(string sentence);
	int binaryGap(int n);
	int projectionArea(vector<vector<int>>& grid);
	vector<int> sortArrayByParity(vector<int>& nums);
	bool containsDuplicate(vector<int>& nums);
	int findRepeatNumber(vector<int>& nums);
	bool isUnique(string astr);
	vector<int> diStringMatch(string s);
	int minDeletionSize(vector<string>& strs);
};

