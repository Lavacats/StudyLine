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


 SinglyLinkedListNode {
     int data;
     SinglyLinkedListNode* next;
 };

 SinglyLinkedListNode* deleteNode(SinglyLinkedListNode* head, int position) {
	 SinglyLinkedListNode* basehead=head;
	 SinglyLinkedListNode* preNode;
	 for (int i = 0; i < position; i++) {
		 preNode = head;
		 head = head->next;
	 }
	 preNode->next = head->next;
	 return basehead;
 }

