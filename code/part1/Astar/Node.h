// Node.h
// the head file for A* Search

#ifndef NODE_H
#define NODE_H 

class Node {
	public:
		Node(){};
		Node(int puzzle[4][4], int depth);
		int* GetAgentLocation();
		bool IsGoal();
		int GetH1Cost();
		int state_[4][4];
		Node* parent;
		int depth_;
		int action_;
		int g_;
		int h_;
};

void PrintAction(const Node* node);
void PrintResult(Node* node);
void PrintPuzzle(const int puzzle[4][4]);
bool IsValidMove(int direction, Node *current);
Node* MoveAgent(int direction, Node* current);
void Swap(int&, int&);

#endif