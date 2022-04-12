#include "Tools.h"

/*
Content: 二维数组
[in] strFile 文件路径
[out] vec
[out] num
*/
bool readStream(string strFile, vector<vector<int>> &vec, int &num)
{
	ifstream in;
	in.open(strFile);
	if (!in.is_open())
	{
		cout << "open File Failed." << endl;
		return false;
	}
	vector<int> temp;
	int n = 0;
	char ch;
	stack<char> s;
	while (in.get(ch))
	{
		if (ch == '[')
		{
			s.push(ch);
		}
		else if (ch == ']')
		{
			s.pop();
			if (s.size() == 1)
			{
				vec.push_back(temp);
				temp.clear();
			}
			else if (s.empty())
			{
				in >> num;
			}
		}
		else if (ch >= '0' && ch <= '9')
		{
			in.putback(ch);
			in >> n;
			temp.push_back(n);
		}
	}
	in.close();
	return true;
}

/*
@overload: 一维数组
[in] strFile 文件路径
[out] vec
*/
bool readStream(string strFile, vector<int> &vec)
{
	ifstream in;
	in.open(strFile);
	if (!in.is_open())
	{
		cout << "open File Failed." << endl;
		return false;
	}
	int n = 0;
	char ch;
	while (in.get(ch))
	{
		if (ch >= '0' && ch <= '9')
		{
			in.putback(ch);
			in >> n;
			vec.push_back(n);
		}
	}
	in.close();
	return true;
}