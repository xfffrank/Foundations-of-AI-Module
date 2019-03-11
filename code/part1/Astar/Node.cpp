// Node.cpp
// An implementation file for "Node.h"
// A* search

#include <iostream>
#include <cmath>
#include "Node.h"
using namespace std;

// initialize a node with the state of the puzzle
// and its depth in the tree structure
Node::Node(int puzzle[4][4], int depth) {
	parent = NULL;
	depth_ = depth;
	action_ = 0;   // action is set to 0 when a Node is initialized
	g_ = 0;
	for (int i = 0; i < 4; i++) 
	{
		for (int j = 0; j < 4; j++)
		{
			state_[i][j] = puzzle[i][j];
		}
	}
	h_ = GetH1Cost();  // get the heuristic cost after the state is set
}

// use the sum of manhattan distances 
// as the cost from the current state to the goal
int Node::GetH1Cost() {
	// The goal location of block A, B and C:
	// A: {1, 1}
	// B: {2, 1}
	// C: {3, 1}
	// The current location of A, B and C:
	int A_loc[2];
	int B_loc[2];
	int C_loc[2];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if(state_[i][j] == 1) {
				A_loc[0] = i;
				A_loc[1] = j;
			} else if (state_[i][j] == 2) {
				B_loc[0] = i;
				B_loc[1] = j;
			} else if (state_[i][j] == 3) {
				C_loc[0] = i;
				C_loc[1] = j;
			}
		}
	}
	int h_cost = abs(A_loc[0] - 1) + abs(A_loc[1] - 1) + abs(B_loc[0] - 2) + abs(B_loc[1] - 1)
			+ abs(C_loc[0] - 3) + abs(C_loc[1] - 1);
	return h_cost;
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
	if (node != NULL) {
		PrintResult(node -> parent);
		PrintAction(node);
		PrintPuzzle(node -> state_);
	}
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

void PrintPuzzle(const int puzzle[4][4]) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			printf("%d ", puzzle[i][j]);
		}
		printf("\n");
	}
	// printf("\n");
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
	new_node -> g_ = current -> g_ + 1;
	return new_node;
}

void Swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}