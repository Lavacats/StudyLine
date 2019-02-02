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

vector<int> jimOrders(vector<vector<int>> orders) {
	vector<int> sumOrders;
	for (int i = 0; i < orders.size(); i++) {
		sumOrders.push_back(orders[i][0] + orders[i][1]);
	}
	vector<int>sortOrders;
	sortOrders = sumOrders;
	vector<int> answer;
	sort(sortOrders.begin(), sortOrders.end());
	for (int i = 0; i < sortOrders.size(); i++) {
		for (int j = 0; j < sumOrders.size(); j++) {
			if (sortOrders[i] == sumOrders[j]) {
				answer.push_back(j);
				sumOrders[j] = -1;
				break;
			}
		}
	}
	return answer;
}

int main()
{
	return 0;
}
