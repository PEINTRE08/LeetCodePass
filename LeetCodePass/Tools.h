#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <stack>

using namespace std;

#define INT_INI_PLUS 2147483647
#define INT_INI_MINUS -2147483648

bool readStream(string strFile, vector<vector<int>> &vec, int &num);
bool readStream(string strFile, vector<int> &vec);