﻿// ConsoleApplication3.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
#include <math.h>

using namespace std;

vector<string> split_string(string);



// Complete the fairRations function below.
int fairRations(vector<int> B) {
	int sumNum = 0;
	for (int i = 0; i < B.size(); i++)sumNum += B[i];
	if (sumNum % 2 == 1)return 0;
	int answer = 0;
	for (int i = 0; i < B.size(); i++){
		if (B[i] % 2 == 1) {
			B[i]++;
			B[i + 1]++;
			answer+=2;
		}
	}
	return answer;
}

int main()
{
	ofstream fout(getenv("OUTPUT_PATH"));

	int N;
	cin >> N;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	string B_temp_temp;
	getline(cin, B_temp_temp);

	vector<string> B_temp = split_string(B_temp_temp);

	vector<int> B(N);

	for (int i = 0; i < N; i++) {
		int B_item = stoi(B_temp[i]);

		B[i] = B_item;
	}

	int result = fairRations(B);


	if(result==0)fout << "NO" << "\n";
	else fout << result << "\n";

	fout.close();

	return 0;
}

vector<string> split_string(string input_string) {
	string::iterator new_end = unique(input_string.begin(), input_string.end(), [](const char &x, const char &y) {
		return x == y and x == ' ';
	});

	input_string.erase(new_end, input_string.end());

	while (input_string[input_string.length() - 1] == ' ') {
		input_string.pop_back();
	}

	vector<string> splits;
	char delimiter = ' ';

	size_t i = 0;
	size_t pos = input_string.find(delimiter);

	while (pos != string::npos) {
		splits.push_back(input_string.substr(i, pos - i));

		i = pos + 1;
		pos = input_string.find(delimiter, i);
	}

	splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

	return splits;
}