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

// Complete the flatlandSpaceStations function below.
int flatlandSpaceStations(int n, vector<int> c) {
	vector<int> city(n);
	int maxlength = 0;
	int curlength = 0;
	for (int i = 0; i < c.size(); i++)city[c[i]] = 1;
	for (int i = 0; i < city.size(); i++) {
		if (city[i] == 1){
			int value = i - curlength - 1;
			if (value < 0)value = 0;
			if (city[value] == 1) {
				if (curlength % 2 == 1)curlength = curlength / 2 + 1;
				else curlength /= 2;
			}
			if (curlength > maxlength){
				maxlength = curlength;
			}
			curlength = 0;
		}
		else curlength++;
		if (i == city.size() - 1 && city[i] == 0) {
			if (curlength > maxlength) {
				maxlength = curlength;
			}
		}
	}
	return maxlength;
}
//int flatlandSpaceStations(int n, vector<int> c) {
//	vector<int> city(n);
//	int maxlength = 0;
//	for (int i = 0; i < c.size(); i++)city[c[i]] = 1;
//	for (int i = 0; i < city.size(); i++) {
//		if (city[i] == 0) {
//			int count = 0;
//			// 1. 왼쪽 끝자락
//			if (i < 1) {
//				// 1-1. 오른쪽으로만 이동
//				for (int j = i; j < city.size(); j++) {
//					if (city[j] == 1)break;
//					else count++;
//				}
//				if (maxlength < count) {
//					maxlength = count;
//				}
//			}
//			// 2. 오른쪽 끝자락
//			else if (i > (city.size() - 2)) {
//				// 2-1. 왼쪽으로만 이동
//				for (int j = i; j >= 0; j--) {
//					if (city[j] == 1)break;
//					else count++;
//				}
//				if (maxlength < count) {
//					maxlength = count;
//				}
//			}
//			else {
//				//3. 오른쪽 왼쪽 다이동
//				int firstCount = 0;
//				int secondCount = 0;
//				for (int j = i; j < city.size(); j++) {
//					if (city[j] == 1)break;
//					else firstCount++;
//				}
//				for (int j = i; j >= 0; j--) {
//					if (city[j] == 1)break;
//					else secondCount++;
//				}
//				if (firstCount < secondCount) {
//					if (maxlength < firstCount) {
//						maxlength = firstCount;
//					}
//				}
//				else {
//					if (maxlength < secondCount) {
//						maxlength = secondCount;
//					}
//				}
//			}
//		}
//	}
//	return maxlength;
//}
int main()
{

	//flatlandSpaceStations(90, { 4, 76, 16, 71 ,56, 7 ,77, 31 ,2, 66 ,12, 32, 57, 11 ,19 ,14 ,42 });
	flatlandSpaceStations(20, { 13,1,11,10,6});
	return 0;
}
