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

class SinglyLinkedListNode {
public:
	int data;
	SinglyLinkedListNode *next;

	SinglyLinkedListNode(int node_data) {
		this->data = node_data;
		this->next = nullptr;
	}
};

class SinglyLinkedList {
public:
	SinglyLinkedListNode *head;

	SinglyLinkedList() {
		this->head = nullptr;
	}

};

void print_singly_linked_list(SinglyLinkedListNode* node, string sep, ofstream& fout) {
	while (node) {
		fout << node->data;

		node = node->next;

		if (node) {
			fout << sep;
		}
	}
}

void free_singly_linked_list(SinglyLinkedListNode* node) {
	while (node) {
		SinglyLinkedListNode* temp = node;
		node = node->next;

		free(temp);
	}
}


SinglyLinkedListNode {
    int data;
    SinglyLinkedListNode* next;
};


SinglyLinkedListNode* insertNodeAtTail(SinglyLinkedListNode* head, int data) {
	SinglyLinkedListNode* newNode = new SinglyLinkedListNode(data);
	newNode->data = data;
	newNode->next = nullptr;

	if (head == nullptr) {
		head = newNode;
	}
	else {
		SinglyLinkedListNode* dummy = new SinglyLinkedListNode(data);
		dummy = head;
		while (dummy->next != nullptr) {
			dummy = dummy->next;
		}
		dummy->next = newNode;
	}

	return head;

}