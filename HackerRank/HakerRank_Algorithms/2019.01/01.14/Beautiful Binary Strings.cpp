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

int beautifulBinaryString(string b) {
	int answer = 0;
	for (int i = 2; i < b.size(); i++) {
		string curChar;
		curChar.push_back(b[i - 2]);
		curChar.push_back(b[i - 1]);
		curChar.push_back(b[i]);
		if (curChar == "010") {
			if (b[i] == '0')b[i] = '1';
			else if (b[i - 1] == '0')b[i - 1] = '1';
			else if (b[i - 2] == '0')b[i - 2] = '1';
			answer++;
		}
	}
	return answer;
}

int main()
{
	ofstream fout(getenv("OUTPUT_PATH"));

	int n;
	cin >> n;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	string b;
	getline(cin, b);

	int result = beautifulBinaryString(b);

	fout << result << "\n";

	fout.close();

	return 0;
}
