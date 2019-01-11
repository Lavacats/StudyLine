// ConsoleApplication3.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
#include <math.h>

using namespace std;


vector<string> weightedUniformStrings(string s, vector<int> queries) {
	vector<int> stringNum;
	vector<string> answer;
	int count = s[0]-96;
	char curChar = s[0];

	stringNum.push_back(count);
	for (int i = 1; i < s.size(); i++) {
		if (curChar != s[i]) {
			count = (s[i] - 96);
			curChar = s[i];
			stringNum.push_back(count);
		}
		else {
			count += (s[i] - 96);
			stringNum.push_back(count);
		}
	}
	for (int i = 0; i < queries.size(); i++) {
		if (find(stringNum.begin(), stringNum.end(), queries[i]) == stringNum.end())answer.push_back("No");
		else answer.push_back("Yes");
	}
	
	return answer;
}

int main()
{
	weightedUniformStrings("aaabbbbcccddd", { 9,7,8,12,5 });
}