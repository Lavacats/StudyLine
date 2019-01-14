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

// Complete the alternatingCharacters function below.
int alternatingCharacters(string s) {
	int answer = 0;
	char curS = s[0];
	for (int i = 1; i < s.size(); i++) {
		if (curS == s[i])answer++;
		else curS = s[i];
	}
	return answer;
}

int main()
{
	ofstream fout(getenv("OUTPUT_PATH"));

	int q;
	cin >> q;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	for (int q_itr = 0; q_itr < q; q_itr++) {
		string s;
		getline(cin, s);

		int result = alternatingCharacters(s);

		fout << result << "\n";
	}

	fout.close();

	return 0;
}