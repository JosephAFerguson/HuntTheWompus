#pragma once
#include "Node.h"
template<class t>
class LL {
	Node<t>* root = nullptr;
	int len;
public:
	LL(t in) {
		root = new Node<t>(in);
		len = 0;
	}
	LL() {
		root = nullptr;
		len = 0;
	}
	bool isEmpty() {
		return root == nullptr;
	}
	void add(t in) { 
		if (isEmpty()) {
			root = new Node<t>(in);
			len++;
			return;
		}
		Node<t>* temp = root;
		while (temp->next != nullptr) {
			temp = temp->next;
		}
		temp->next = new Node<t>(in);
		len++;
	}
	t* get(t in) { 
		Node<t>* temp = root;
		while (temp->next != nullptr && temp->data != in) {
			temp = temp->next;
		}
		if (temp->data == in) {
			return &temp->data;
		}
		else {
			return nullptr;
		}
	}
	int getLen() {
		return len;
	}
	t* convToArr() {
		Node<t>* temp = root;
		t* ret = new t[len];
		int i = 0;
		while (temp != nullptr) {
			ret[i] = temp->data;
			temp = temp->next;
			i++;
		}
		return ret;
		//work here
	}
	void printContents() {
		Node<t>* temp = root;
		if (temp != nullptr) {
			std::cout << std::string(temp->data);
		}
		while (temp->next != nullptr) {
			temp = temp->next;
			std::cout << ", and " << std::string(temp->data);
		}
	}
};