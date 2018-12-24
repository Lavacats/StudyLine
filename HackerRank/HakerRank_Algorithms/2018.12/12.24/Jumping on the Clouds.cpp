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

int jumpingOnClouds(vector<int> c) {
	int JumpCount = 0;
	int startPoint = 0;
	for (int i = 0; i < c.size(); i++)
	{
		if ((startPoint + 2) >= c.size() - 1 || (startPoint + 2) >= c.size() - 1)
		{
			JumpCount++;
			break;
		}
		else
		{
			if (c[startPoint + 2] == 0)
			{
				JumpCount++;
				i++;
				startPoint += 2;
			}
			else if (c[startPoint + 1] == 0)
			{
				JumpCount++;
				startPoint++;
			}
		}
	}
	return JumpCount;
}

int main()
{
	ofstream fout(getenv("OUTPUT_PATH"));

	int n;
	cin >> n;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	string c_temp_temp;
	getline(cin, c_temp_temp);

	vector<string> c_temp = split_string(c_temp_temp);

	vector<int> c(n);

	for (int i = 0; i < n; i++) {
		int c_item = stoi(c_temp[i]);

		c[i] = c_item;
	}

	int result = jumpingOnClouds(c);

	fout << result << "\n";

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
