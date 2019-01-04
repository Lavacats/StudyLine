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

// Complete the happyLadybugs function below.
string happyLadybugs(string b) {
	if (b.size() < 2){
		if (b[0] == '_')return "YES";
		else return "NO";
	}
	bool underBalCheck = false;
	bool answerCheck = false;
	for (int i = 0; i < b.size(); i++) {
		if (b[i] == '_')underBalCheck = true;
	}
	if (!underBalCheck)
	{
		bool check = true;

		for (int i = 1; i < b.size()-1; i++) {
			if (b[i] != b[i - 1] && b[i] != b[i + 1])check = false;
		}
		if (b.size() < 2)return "NO";

		if (b[0] != b[1])return "NO";
		if (b[b.size() - 1] != b[b.size() - 2])return"NO";

		if (check)return "YES";
		else return "NO";
	}
	else{
		sort(b.begin(), b.end());
		int count = 0;
		char curB = b[0];
		for (int i = 0; i < b.size(); i++) {
			if (curB == b[i])count++;
			else {
				curB = b[i];
				if (count <= 1) {
					answerCheck = true;
					break;
				}
				count =1;
				if (curB == '_')break;
			}
		}
	}
	if (answerCheck)return "NO";
	else return "YES";
}

int main()
{
	happyLadybugs("RRGGBBXX");

	return 0;
}
