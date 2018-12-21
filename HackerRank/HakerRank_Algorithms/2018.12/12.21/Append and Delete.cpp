// ConsoleApplication3.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>

using namespace std;

// Complete the appendAndDelete function below.
string appendAndDelete(string s, string t, int k) {
	int minNum;
	if (s.size() < t.size())minNum = s.size();
	else minNum = t.size();

	int sameNum = 0;
	for (int i = 0; i < minNum; i++)
	{
		if (s[i] == t[i])sameNum = i+1;
		else break;
	}
	int answer = ((s.size() - sameNum) + (t.size() - sameNum));
	
	if (answer > k)return "No";
	else if (answer % 2 == k % 2)return "Yes";
	else if (s.size() + t.size() < k)return "Yes";
	else return "No";
}
int main()
{
	appendAndDelete("y","yu")
}