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

// Complete the permutationEquation function below.
vector<int> permutationEquation(vector<int> p) {

	vector<int> answer;
	for (int i = 1; i <= p.size(); i++)
	{
		for (int j = 0; j < p.size(); j++)
		{
			if (i == p[j])
			{
				int index = j + 1;
				for (int k = 0; k < p.size(); k++)
				{
					if (index == p[k])
					{
						answer.push_back(k+1);
						break;
					}
				}
				break;
			}
		}
	}
	return answer;
}

int main()
{
	permutationEquation({ 4,3,5,1,2 });
	//ofstream fout(getenv("OUTPUT_PATH"));

	int n;
	cin >> n;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	string p_temp_temp;
	getline(cin, p_temp_temp);

	vector<string> p_temp = split_string(p_temp_temp);

	vector<int> p(n);

	for (int i = 0; i < n; i++) {
		int p_item = stoi(p_temp[i]);

		p[i] = p_item;
	}

	vector<int> result = permutationEquation(p);

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
