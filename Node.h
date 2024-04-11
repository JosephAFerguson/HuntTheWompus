#pragma once
template<class T>
class Node {
public:
	Node<T>* next;
	T data;
	Node(T in) {
		data = in;
		next = nullptr;
	}
};

