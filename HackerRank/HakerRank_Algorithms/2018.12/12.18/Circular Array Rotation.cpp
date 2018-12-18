// ConsoleApplication3.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
using namespace std;

vector<string> split_string(string);

// Complete the circularArrayRotation function below.
vector<int> circularArrayRotation(vector<int> a, int k, vector<int> queries) {
	queue<int> numberQueue;
	for (int i = a.size()-1; i>=0; i--)numberQueue.push(a[i]);
	for (int i = 0; i < k; i++)
	{
		int frontValue = numberQueue.front();
		numberQueue.pop();
		numberQueue.push(frontValue);
	}
	for (int i = a.size()-1; i >=0; i--)
	{
		a[i] = numberQueue.front();
		numberQueue.pop();
	}
	for (int i = 0; i < queries.size(); i++)
	{
		int index = queries[i];
		queries[i] = a[index];
	}
	return queries;
}

int main()
{

	vector<int> result = circularArrayRotation({ 1,2,3 }, 2, { 0,1,2 });

	//for (int i = 0; i < result.size(); i++) {
	//	fout << result[i];

	//	if (i != result.size() - 1) {
	//		fout << "\n";
	//	}
	//}

	//fout << "\n";

	//fout.close();

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