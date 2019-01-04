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


//

// Complete the stones function below.
string gridSearch(vector<string> G, vector<string> P) {
	bool answer = false;
	for (int i = 0; i < G.size() - P.size()+1; i++) {
		for (int j = 0; j < G[0].size() - P[0].size()+1; j++) {
			bool check = false;
			if (G[i][j] == P[0][0]){
				check = true;
				for (int a = 0; a < P.size(); a++) {
					for (int b = 0; b < P[a].size(); b++) {
						if (G[i + a][j + b] != P[a][b]) {
							check = false;
							break;
						}
					}
				}
			}
			if (check) {
				answer = true;
				break;
			}
		}
	}
	if (answer)return "YES";
	else return "NO";
}

int main()
{
	gridSearch(
		{
"123412",
"561212",
"123634",
"781288"
		},
		{ 
"12",
"34"
		});
	return 0;
}