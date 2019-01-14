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

// Complete the pangrams function below.
string pangrams(string s) {
	string answer_Small;
	for (int i = 0; i < 26; i++)answer_Small.push_back('a' + i);
	string answer_Big;
	for (int i = 0; i < 26; i++)answer_Big.push_back('A' + i);
	vector<bool> smallCheck(26);


	for (int i = 0; i < s.size(); i++) {
		if (s[i] >= 'a' && s[i] <= 'z') {
			smallCheck[s[i] - 'a'] = true;
		}
		else if (s[i] >= 'A' && s[i] <= 'Z') {
			smallCheck[s[i] - 'A'] = true;
		}
	}
	bool answer = true;
	for (int i = 0; i < smallCheck.size(); i++) {
		if (!smallCheck[i]) {
			answer = smallCheck[i];
			break;
		}
	}
	
	if (answer)return "Panrgram";

	return "not Pangram";
}

int main()
{

	pangrams("We promptly judged antique ivory buckles for the next prize");

	return 0;
}
