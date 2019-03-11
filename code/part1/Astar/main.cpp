// main.cpp
// An implementation of A* Search

#include "SingleLinkedList.h"
#include "Node.h"
#include <iostream>
#include <fstream>

using namespace std;

Node* AStar(Node* root);
// the number of nodes generated is a way to measure time complexity
int nodes_generated;


// A-star search
Node* AStar(Node* root) {
	SingleLinkedList<Node*> list;
	list.AddNode(root);
	while(!list.IsEmpty()) {
		LinkedNode<Node*>* min = list.head;
		LinkedNode<Node*>* tmp = list.head;
		// get the LinkedNode with minimal value
		while(tmp -> next != NULL) {
			tmp = tmp -> next;
			if ((tmp -> value -> h_ + tmp -> value -> g_) < (min -> value -> h_ + min -> value -> g_)) {
				min = tmp;
			}
		}
		// delete the LinkedNode with the minimal value from the list
		list.DeleteNode(min);
		Node* current_min_node = min -> value;
		if (current_min_node -> IsGoal()) {
			return current_min_node;
		}  else {
			// expand the node, add its children to fringe_list
			for (int i = 1; i <= 4; i++) {
				if (IsValidMove(i, current_min_node)) {
					nodes_generated ++;  // update time complexity
					Node* child = MoveAgent(i, current_min_node);
					list.AddNode(child);
				} 
			}
		}
	}
	return NULL;
}


int main() {
	/*
	direction:
	1: up
	2: down
	3: left
	4: right
	*/
	
	// 0: white tiles; -1: the agent;
	// 1: block A; 2: block B; 3: block C
	int puzzle[4][4] = {
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{1, 2, 3, -1}
	};

	Node* root = new Node(puzzle, 0);
	// run Astar
	nodes_generated = 1;
	Node* solution = AStar(root);
	if (solution != NULL) {
		cout << "A* Heuristic Search:" << endl;
		// cout << "Action sequence: ";
		PrintResult(solution);
		cout << endl;
		printf("Path cost: %d\n", solution -> g_);
		printf("Nodes generated: %d\n", nodes_generated);
	}

	/* Find the optimal action path by experiments
	and use it to control the depth of the solution. */
	/* Run Astar by controling the depth of the solution
	and output the numbers of nodes to a file. */
	// int op_action_path[] = {1, 3, 3, 2, 3, 1, 4, 2, 4, 1, 1, 3, 2, 3};
	// ofstream nodes_log;
	// nodes_log.open("nodes.txt");
	// Node* tmp_root;
	// for (int i = -1; i < 14; i++) {
	// 	if (i == -1) {
	// 		// stay at the original location
	// 		tmp_root = root;
	// 	} else {
	// 		// take a step to the goal state
	// 		tmp_root = MoveAgent(op_action_path[i], tmp_root);
	// 	}
	// 	nodes_generated = 1;  // nodes_generated is a global variable
	// 	Node* tmp_solution = AStar(tmp_root);
	// 	printf("Nodes generated: %d\n", nodes_generated);
	// 	nodes_log << nodes_generated << endl;
	// 	// root = tmp_root;
	// }
	// nodes_log.close();

	return 0;
}
