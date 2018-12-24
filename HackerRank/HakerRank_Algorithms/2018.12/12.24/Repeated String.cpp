// ConsoleApplication3.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>

using namespace std;

// Complete the repeatedString function below.
long repeatedString(string s, long n) {
	char firstS = 'a';
	long Scount = 0;
	for (long i = 0; i < s.size(); i++)
		if (s[i] == firstS)Scount++;
	long nsCount = n / s.size();
	nsCount -= nsCount % 1;
	Scount *= nsCount;
	long least = n % s.size();
	for (long i = 0; i < least; i++)
		if (s[i] == firstS)Scount++;
	return Scount;
}

int main()
{
	//ofstream fout(getenv("OUTPUT_PATH"));

	string s;
	getline(cin, s);

	long n;
	cin >> n;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	long result = repeatedString(s, n);

	//fout << result << "\n";

	//fout.close();

	return 0;
}
