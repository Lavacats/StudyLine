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

// Complete the cutTheSticks function below.
vector<int> cutTheSticks(vector<int> arr) {
	sort(arr.begin(), arr.end());
	vector<int> answer;
	for (int i = 0; i < arr.size(); i++)
	{
		int count = 0;
		if (arr[i] != 0)
		{
			int value = arr[i];
			for (int j = i; j < arr.size(); j++)
			{
				if (arr[j] != 0)
				{
					count++;
					arr[j] -= value;
				}
			}
			if (count != 0)
			{
				answer.push_back(count);
			}
		}
	}
	return answer;
}

int main()
{
	cutTheSticks({ 5,4,4,2,2,8 });

	return 0;
}
