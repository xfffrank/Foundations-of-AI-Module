// bfs.cpp
// An implementation of Breadth-first Search

#include "Node.h"
#include <iostream>
#include <queue>
#include <fstream>

using namespace std;

// the number of nodes generated is a way to measure time complexity
int nodes_generated;

// an iterative way to implement breadth first search
// Breadth first search
// return a node which contains the goal state
Node* Bfs(Node* root) {
	queue<Node*> fringe_list;
	if (root -> IsGoal()) {
		return root;
	} else {
		fringe_list.push(root);
	}
	while(!fringe_list.empty()) {
		Node* front = fringe_list.front();
		fringe_list.pop();
		// expand the node, add its children to fringe_list
		for (int i = 1; i <= 4; i++) {
			if (IsValidMove(i, front)) {
				nodes_generated ++;  // update time complexity
				Node* child = MoveAgent(i, front);
				if (child -> IsGoal()) {
					return child;
				}
				fringe_list.push(child);
			} 
		}
	}
	return NULL;
}


int main() {
	int puzzle[4][4] = {
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{1, 2, 3, -1}
	};
	Node* root = new Node(puzzle, 0);
	// Run bfs.
	nodes_generated = 1;
	Node* solution = Bfs(root);
	cout << "Breadth-first Search:" << endl;
	if (solution != NULL) {
		// cout << "Action sequence: ";
		PrintResult(solution);
		cout << endl;
		cout << "Path cost: " << solution -> path_cost_ << endl;
		printf("Nodes expanded: %d\n", nodes_generated);
	}
	
	/* Run bfs by controling the depth of the solution
	and output the numbers of nodes to a file. */
	// int op_action_path[] = {1, 3, 3, 2, 3, 1, 4, 2, 4, 1, 1, 3, 2, 3};
	// ofstream nodes_log;
	// nodes_log.open("bfs.txt");
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
	// 	Node* tmp_solution = Bfs(tmp_root);
	// 	printf("Nodes generated: %d\n", nodes_generated);
	// 	nodes_log << nodes_generated << endl;
	// }
	// nodes_log.close();
	return 0;
	
}





