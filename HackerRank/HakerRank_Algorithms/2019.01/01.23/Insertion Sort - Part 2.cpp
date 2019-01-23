// ConsoleApplication3.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
#include <list>
#include <math.h>
using namespace std;


// Complete the insertionSort1 function below.
void insertionSort1(int n, vector<int> arr) {
	for (int i = 1; i < arr.size(); i++) {
		vector<int> value;
		for (int j = 0; j <= i; j++) {
			value.push_back(arr[j]);
		}
		sort(value.begin(), value.end());
		for (int j = i + 1; j < arr.size(); j++) {
			value.push_back(arr[j]);
		}
		for (int i = 0; i < value.size(); i++)cout << value[i] << " ";
		cout << endl;
	}
}

int main()
{
	insertionSort1(6, { 1,4,3,5,6,2 });

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
