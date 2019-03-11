// ids.cpp
// An implementation of Iterative Deepening Search

#include "Node.h"
#include <iostream>
#include <queue>
#include <fstream>
using namespace std;

// the number of nodes generated is a way to measure time complexity
int nodes_generated;

// an recursive way to implement limited-depth first search
Node* DfsLimited(Node *node, int limit) {
	if (node -> IsGoal())
		return node;   // the solution is found
	if (limit == 0)
		return NULL;   // the limited depth is reached while no solution is found
	for (int i = 1; i <= 4; i++) {
		if (IsValidMove(i, node)) {
			nodes_generated ++;  // update time complexity
			Node* child = MoveAgent(i, node);
			Node* result = DfsLimited(child, limit - 1);
			if (result != NULL) {
                return result;  // return the solution
            }
		}
	} 
	return NULL;  // the moves of all directions are invalid
}


int main() {
	int puzzle[4][4] = {
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{1, 2, 3, -1}
	};
	Node* root = new Node(puzzle, 0);
	// /* dfs iterative */
	nodes_generated = 1;
	for (int i = 0; ;i++) {
		Node* solution = DfsLimited(root, i);
		if (solution != NULL) {
			cout << "Iterative Deepening Search:" << endl;
			// cout << "Action sequence: ";
			PrintResult(solution);
			cout << endl;
            printf("Path cost: %d\n", solution -> path_cost_);
			// printf("Current depth: %d\n", i);
			printf("Nodes generated: %d\n", nodes_generated);
            // the solution has been found
            // the depth stopped increasing
            break;  
		}
	}

	
	/*Run idfs by controling the depth of the solution
	and output the numbers of nodes to a file.
	*/
	// int op_action_path[] = {1, 3, 3, 2, 3, 1, 4, 2, 4, 1, 1, 3, 2, 3};
	// ofstream nodes_log;
	// nodes_log.open("idfs.txt");
	// Node* tmp_root;
	// for (int i = -1; i < 14; i++) {
	// 	if (i == -1) {
	// 		// stay at the original location
	// 		tmp_root = root;
	// 	} else {
	// 		// take a step to the goal state
	// 		tmp_root = MoveAgent(op_action_path[i], tmp_root);
	// 	}
	// 	nodes_generated = 1;   // nodes_generated is a global variable
	// 	for (int j = 0; ;j++) {
	// 		Node* solution = DfsLimited(tmp_root, j);
	// 		if (solution != NULL) {
	// 			nodes_log << nodes_generated << endl;
	// 			printf("Current depth: %d\n", solution -> path_cost_);
	// 			printf("Nodes generated: %d\n", nodes_generated);
	// 	        // the solution has been found
	// 	        // the depth stopped increasing
	// 	        break;  
	// 		}
	// 	}
	// }
	// nodes_log.close();

	return 0;
}





