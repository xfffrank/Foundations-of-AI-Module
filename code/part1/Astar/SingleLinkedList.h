// SingleLinkedList.h
// An implementation of a single linked list,
// which is used for store the unexpanded nodes in A* Search

#ifndef SLL_H
#define SLL_H

#include<iostream>
using namespace std;

template <class T>
class LinkedNode {
public:
	LinkedNode(T element) {
		value = element;
		next = NULL;
	};
	~LinkedNode();
	T value;
	LinkedNode* next;
};

template <class T>
class SingleLinkedList {
public:
	SingleLinkedList() {
		head = NULL;
	};
	// ~SingleLinkedList();
	void AddNode(T value);
	void DeleteNode(LinkedNode<T>* node); 
	void TraverseList();
	bool IsEmpty();
	LinkedNode<T>* head;
};

template<class T>
bool SingleLinkedList<T>::IsEmpty() {
	return head == NULL;
}

template<class T>
void SingleLinkedList<T>::DeleteNode(LinkedNode<T>* node) {
	// delete the node with minimal value
	LinkedNode<T>*current = head;
	if (current == node) {
		head = current -> next;
	} else {
		while (current -> next != NULL) {
			if (current -> next == node) {
				current -> next = current -> next -> next;
				break;
			} else {
				current = current -> next;
			}
		}
	}
}

template<class T>
void SingleLinkedList<T>::TraverseList() {
	LinkedNode<T>* tmp = head;
	while (tmp != NULL) {
		cout << tmp -> value << endl;
		tmp = tmp -> next;
	}
}

template <class T>
void SingleLinkedList<T>::AddNode(T value) {
	LinkedNode<T>* new_node = new LinkedNode<T>(value);
	if (head == NULL) {
		head = new_node;
	} else {
		LinkedNode<T>* tmp = head;
		while (tmp -> next != NULL) {
			tmp = tmp -> next;
		}
		tmp -> next = new_node;
	}
}

#endif