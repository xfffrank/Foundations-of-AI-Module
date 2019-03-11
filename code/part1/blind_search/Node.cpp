// Node.cpp
// An implementation file for "Node.h"
// Blind search

#include "Node.h"
#include <iostream>
using namespace std;

// initialize a node with the state of the puzzle
// and its depth in the tree structure
Node::Node(int puzzle[4][4], int depth) {
	parent = NULL;
	depth_ = depth;
	action_ = 0;
	path_cost_ = 0;
	for (int i = 0; i < 4; i++) 
	{
		for (int j = 0; j < 4; j++)
		{
			state_[i][j] = puzzle[i][j];
		}
	}
}

// return true if the node contains the goal state
bool Node::IsGoal() {
	// goal state:
	// 	{0, 0, 0, 0},
	// 	{0, 1, 0, 0},
	// 	{0, 2, 0, 0},
	// 	{0, 3, 0, 0}
	return (state_[1][1] == 1 && state_[2][1] == 2 && state_[3][1] == 3);
}

int* Node::GetAgentLocation() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (state_[i][j] == -1) {
				int *res = new int[2];
				res[0] = i;
				res[1] = j;
				return res;
			}
		}
	}
	return NULL;
}

// Move the agent according to the current position and the direction.
// Return a new node after the move.
Node* MoveAgent(int direction, Node* current) {
	int* agent_loc = current -> GetAgentLocation();
	// Initial the representation of the new state
	// using the current state.
	int new_state_[4][4];
	for (int i = 0; i < 4; i++)	{
		for (int j = 0; j < 4; j++)
		{
			new_state_[i][j] = current -> state_[i][j];
		}
	}
	// Move the position of the agent.
	switch(direction) {
		case 1:
			Swap(new_state_[agent_loc[0]][agent_loc[1]], new_state_[agent_loc[0] - 1][agent_loc[1]]);
			break;
		case 2:
			Swap(new_state_[agent_loc[0]][agent_loc[1]], new_state_[agent_loc[0] + 1][agent_loc[1]]);
			break;
		case 3:
			Swap(new_state_[agent_loc[0]][agent_loc[1]], new_state_[agent_loc[0]][agent_loc[1] - 1]);
			break;
		case 4:
			Swap(new_state_[agent_loc[0]][agent_loc[1]], new_state_[agent_loc[0]][agent_loc[1] + 1]);
			break;
	}
	Node* new_node = new Node(new_state_, current -> depth_ + 1);
	new_node -> parent = current;  // Parent logged.
	new_node -> action_ = direction; // Action logged.
	new_node -> path_cost_ = current -> path_cost_ + 1;
	return new_node;
}

// A move is valid as long as the agent will not cross the boundaries.
bool IsValidMove(int direction, Node *current) {
	/*
	direction:
	1: up
	2: down
	3: left
	4: right
	*/
	int* agent = current -> GetAgentLocation();
	int result;
	// In the normal way, we don't fix anything,
	// even the agent will go back and forth between and current node
	// and the node it just visited.
	// int is_visited = direction + current -> action_;
	switch(direction)
	{
		case 1:
			result = agent[0] - 1;
			break;
		case 2:
			result = agent[0] + 1;
			break;
		case 3:
			result = agent[1] - 1;
			break;
		case 4:
			result = agent[1] + 1;
			break;
	}
	return (result >= 0 && result < 4);
}

void PrintPuzzle(int puzzle[4][4]) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			printf("%d ", puzzle[i][j]);
		}
		printf("\n");
	}
}

void Swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}

void PrintAction(const Node* node) {
	int act = node -> action_;
	cout << "Action: ";
	switch(act) {
		case 0: break;
		case 1: 
			cout << "up";
			break;
		case 2:
			cout << "down";
			break;
		case 3:
			cout << "left";
			break;
		case 4:
			cout << "right";
			break;
	}
	cout << endl << endl;
}

void PrintResult(Node* node) {
	// An recursive way to 
	// print the result of a solution.
	if (node != NULL) {
		PrintResult(node -> parent);
		PrintAction(node);
		PrintPuzzle(node -> state_);  // print the puzzle state
	}
}