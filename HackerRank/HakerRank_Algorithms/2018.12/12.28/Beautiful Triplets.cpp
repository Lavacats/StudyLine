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

vector<string> split_string(string);

// Complete the beautifulTriplets function below.

int SearchAddNum(int index,int num,int d, vector<int> arr) {
	int answer = -1;
	for (int i = 0; i < arr.size(); i++)
	{
		if ((num + d) == arr[i])
		{
			answer = i+index;
			break;
		}
	}
	return answer;
}

int beautifulTriplets(int d, vector<int> arr) {
	int answer = 0;
	for (int i = 0; i < arr.size()-2; i++)
	{
		vector<int> firstTub;
		for (int j = i; j < arr.size() - 1; j++)firstTub.push_back(arr[j]);
		int first = SearchAddNum(i,arr[i], d, firstTub);
		if (first != -1)
		{
			vector<int> secondTub;
			for (int k = first; k < arr.size(); k++)secondTub.push_back(arr[k]);
			int second = SearchAddNum(first,arr[first], d, secondTub);
			if (second != -1)
			{
				answer++;
			}
		}
	}
	return answer;
}

int beautifulTriplets2(int d, vector<int> arr){
	int count = 0;
	if (arr.size() < 3)return 0;

	for (int i = 0; i < arr.size()-2; i++)
	{
		int value1 = arr[i];
		int value2 = value1 + d;
		int value3 = value2 + d;
		bool check = false;
		bool check2 = false;

		for (int j = i + 1; j < arr.size(); j++)
		{
			if (value2 == arr[j])check = true;
			if (check == true && value3 == arr[j])check2 = true;
		}
		if (check2 == true)count++;
	}
	return count;
}

int main()
{
	beautifulTriplets2(1, { 1 ,1 });

	return 0;
}
