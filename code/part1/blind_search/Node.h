// Node.h
// The head file for blind search(BFS, DFS, IDS)

#ifndef NODE_H
#define NODE_H

class Node {
	public:
		// Node(){};
		Node(int puzzle[4][4], int depth);
		int* GetAgentLocation();
		bool IsGoal();
		int state_[4][4];
		Node* parent;
		int path_cost_;
		int depth_;
		int action_;
};


void Swap(int& a, int& b);
void PrintPuzzle(int puzzle[4][4]);
Node* MoveAgent(int direction, Node *current);
bool IsValidMove(int direction, Node *current);
void PrintResult(Node* node);
void PrintAction(const Node* node);

#endif