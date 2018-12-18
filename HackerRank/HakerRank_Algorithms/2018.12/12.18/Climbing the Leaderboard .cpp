// ConsoleApplication3.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

vector<string> split_string(string);

int lower_bound(vector<int> arr, int target, int size)
{
	int mid;
	int start = 0;
	int end = size -1;

	while (end > start)
	{
		mid = (start + end) / 2;
		if (arr[mid] >= target)
			start = mid + 1;
		else end = mid ;
	}
	return end;
}
vector <int> climbingLeaderboard(vector <int> scores, vector <int> alice) {
	// Complete this function
	int h_rank = 1;
	for (int i = scores.size() - 1; i > 0; i--) {
		if (scores[i] < scores[i - 1]) {
			h_rank++;
		}
	}
	h_rank++;	//h_rank는 score에 있는 점수의 갯수 +1 의 값을 가진다.

	vector<int>ranks(alice.size());
	int j = scores.size() - 1;	//j는 score의 값 보다 1 작은 값을 가진다.(값을 뒤에서 부터 검색할거라)
	for (int i = 0; i < alice.size(); i++) {
		while (alice[i] >= scores[j]) {	//alice의 값이 socre보다 커지는 순간
			if (h_rank == 1) {//h_rank가 1이 되면 모두 검색을 마쳤다는 뜻
				break;
			}
			if (scores[j] == scores[j - 1]) {//겹치는 값이 있는 경우 j를 하나 줄인다.rank값은 줄이지 않는다
				j--;
			}
			else {
				j--;		//rank값과 j값을 모두 줄인다.
				h_rank--;
			}
		}
		ranks[i] = h_rank;
	}
	return ranks;
}
vector<int> climbingLeaderboard2(vector<int> scores, vector<int> alice) {
	vector<int> answer;
	vector<int>scoreBoard;
	int curScore = scores[0];
	scoreBoard.push_back(curScore);
	for (int i = 0; i < scores.size(); i++)
	{
		if (curScore != scores[i])
		{
			curScore = scores[i];
			scoreBoard.push_back(curScore);
		}
	}
	for (int i = 0; i < alice.size(); i++)
	{
		int value =lower_bound(scoreBoard,alice[i],scoreBoard.size());
		
		if (value > 0 && alice[i] == scoreBoard[value - 1])
		{
			value--;
		}
		if (scoreBoard[value] > alice[i])
		{
			value++;
		}
		answer.push_back(value+1);
	}
	return answer;
}




int main()
{
	climbingLeaderboard({ 100,100,50,40,40,20,10 }, { 5,25,50,120 });
	return 0;
}
