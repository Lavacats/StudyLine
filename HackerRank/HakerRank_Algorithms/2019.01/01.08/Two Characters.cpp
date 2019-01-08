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

bool doubleNumS(string s) {
	bool answer = false;
	for (int i = 0; i < s.size() - 1; i++) {
		if (s[i] == s[i + 1]) {
			answer = true;
			break;
		}
	}
	return answer;
}

// Complete the alternate function below.
int alternate(string s) {
	string alphaVector;
	string dummy = s;
	sort(dummy.begin(), dummy.end());
	char curChar = dummy[0];
	alphaVector.push_back(curChar);
	for(int i=0; i<dummy.size()-1;i++){
		if (dummy[i] != dummy[i + 1])alphaVector.push_back(dummy[i + 1]);
	}
	int maxCount = 0;
	for (int i = 0; i < alphaVector.size() - 1; i++) {
		string twoCharactor;
		for (int j = 0; j < s.size(); j++) {
			if (s[j] == alphaVector[i] || s[j] == alphaVector[i + 1])twoCharactor.push_back(s[j]);
		}
		if (!doubleNumS(twoCharactor)) {
			if (maxCount <twoCharactor.size())maxCount = twoCharactor.size();
		}
	}
	return maxCount;
}

int main()
{
	alternate("cobmjdczpffbxputsaqrwnfcweuothoygvlzugazulgjdbdbarnlffzpogdprjxvtvbmxjujeubiofecvmjmxvofejdvovtjulhhfyadr");
	// addaddfanfghbsfdab
	return 0;
}
