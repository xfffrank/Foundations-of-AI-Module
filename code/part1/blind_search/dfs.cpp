// dfs.cpp
// An implementation of Depth-first Search

#include "Node.h"
#include <iostream>
#include <stack>

using namespace std;

// the number of nodes generated is a way to measure time complexity
int nodes_generated;

// an recursive way to implement depth first search
Node* Dfs(Node *node) {
	if (node -> IsGoal())
		return node;
	for (int i = 1; i <= 4; i++) {
		if (IsValidMove(i, node)) {
			nodes_generated ++;
			Node* child = MoveAgent(i, node);
			// Call the depth first search recursively,
			// and in this problem, this will be an endless loop.
			// There is not a chance that i will change from 1 to 2
			// in the outermost layer. 
			Node* solution = Dfs(child);
			if (solution != NULL)
				return solution;
		} 
	}
	return NULL;
}

// an iterative way to implement depth first search
// Node* Dfs(Node *root) {
// 	stack<Node*> fringe_list;
// 	fringe_list.push(root);
// 	while(!fringe_list.empty()) {
// 		Node* top = fringe_list.top();
// 		fringe_list.pop();
// 		if (top -> IsGoal()) {
// 			return top;  // find the solution
// 		} else {
// 			// expand the node, add its children to fringe_list
// 			for (int i = 1; i <= 4; i++) {
// 				if (IsValidMove(i, top)) {
// 					nodes_generated ++;  // update time complexity
// 					Node* child = MoveAgent(i, top);
// 					fringe_list.push(child);
// 				} 
// 			}
// 		}
// 	}
// 	return NULL;
// }

int main() {
	// uncomment this state to make dfs work
	// int puzzle[4][4] = {
	// 	{0, 1, 0, 0},
	// 	{0, 2, 0, 0},
	// 	{0, 3, 0, 0},
	// 	{0, -1, 0, 0}
	// };
	int puzzle[4][4] = {
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{1, 2, 3, -1}
	};
	Node* root = new Node(puzzle, 0);
	nodes_generated = 1;
	Node* solution = Dfs(root);
    if (solution != NULL) {
        cout << "Path cost: " << solution -> path_cost_ << endl;
		printf("Nodes expanded: %d\n", nodes_generated);
    }
	
	return 0;
}





