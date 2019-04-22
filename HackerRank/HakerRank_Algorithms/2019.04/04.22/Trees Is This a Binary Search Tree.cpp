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

struct Node {
	int data;
	Node* left;
	Node* right;
};


void InorderTraversal(Node* root, vector<int>* dataVector) {

	if (root->left) InorderTraversal(root->left, dataVector);
	// 왼쪽 노드 검사

	dataVector->push_back(root->data);
	// 값을 저장합니다.

	if (root->right) InorderTraversal(root->right, dataVector);
	//오른쪽 노드 검사
}

bool checkBST(Node* root) {
	bool answer = true;
	vector<int> dataValue;

	InorderTraversal(root, &dataValue);
	// 중위순회를 사용해 데이터값을 저장한뒤 값을 비교하는 방법
	// 중위순회는 좌측-중앙-우측 순으로 순회하기 때문에
	// 값이 순서대로 적용되는지를 비교하면 답을 알 수 있다.

	for (int i = 0; i < dataValue.size() - 1; i++) {
		for (int j = i + 1; j < dataValue.size(); j++) {
			if (dataValue[i] >= dataValue[j]) {
				answer = false;
				break;
			}
		}
	}
	// 값이 같은 경우도 성립이 안되기 때문에 >=를 사용해 검사합니다.
	return answer;
}