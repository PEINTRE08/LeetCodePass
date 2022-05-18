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