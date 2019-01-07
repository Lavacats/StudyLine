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

// Complete the camelcase function below.
int camelcase(string s) {
	int answer = 0;
	answer++;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] < 'a')answer++;
	}
	return answer;
}

int main()
{
	ofstream fout(getenv("OUTPUT_PATH"));

	string s;
	getline(cin, s);

	int result = camelcase(s);

	fout << result << "\n";

	fout.close();

	return 0;
}
