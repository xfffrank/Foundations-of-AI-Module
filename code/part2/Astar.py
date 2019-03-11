"""
Astar.py

The implementation of A* search for the problem of 8-puzzle.
"""

import numpy as np
import pickle
from queue import PriorityQueue

'''
goal:
    [[0, 1, 2],
    [3, 4, 5],
    [6, 7, 8]]
'''
goal_state = {1:[0, 1], 2:[0, 2], 3:[1, 0],
              4:[1, 1], 5:[1, 2], 6:[2, 0],
              7:[2, 1], 8:[2, 2]}
goal = np.arange(9).reshape([3, 3])


class Node:
        
    # the neural networks model used to predict the heuristic value
    model = None 
    # the flag that implied which heuristic function will be used
    # heuristic = 1 --- use the one-feature neural networks model
    # heuristic = 2 --- use the two-features neural networks model
    # heuristic = None --- use the sum of Manhattan distances
    heuristic = None

    def __init__(self, puzzle):
        '''
        goal:
        [[0, 1, 2],
         [3, 4, 5],
         [6, 7, 8]]
        '''
        self.state = puzzle
        self.action = 0
        self.parent = None
        if Node.heuristic == 1:
            self.h = Node.model.predict(self.get_H1())
        elif Node.heuristic == 2:
            self.h = Node.model.predict([self.get_H1(), self.get_H2()])
        else:
            self.h = self.get_H1()
        self.g = 0

    def __lt__(self, other):
        '''
        Used for sorts the nodes in the priority queue
        '''
        return (self.g + self.h) < (other.g + other.h)

    def get_H1(self):
        '''
        compute the sum of manhattan distances
        '''
        distances_sum = 0
        for i in range(3):
            for j in range(3):
                if self.state[i][j] != 0:
                    x, y = goal_state[self.state[i][j]]
                    distances_sum += abs(x-i) + abs(y-j)
        return distances_sum

    def get_H2(self):
        '''
        compute the number of misplaced tiles
        '''
        count = 0
        for tile, loc in goal_state.items():
            if self.state[loc[0]][loc[1]] != tile:
                count += 1
        return count

    def is_goal(self):
        return np.array_equal(self.state, goal)

    def get_blank_tile_loc(self):
        '''
        get the location of the blank tile
        '''
        for i in range(3):
            for j in range(3):
                if self.state[i][j] == 0:
                    return i, j


def is_valid_move(node, direction):
    '''
    1 up, 2 down, 3 left, 4 right

    The move is valid when the blank tile will not cross the boundaries 
    and it will not go back to the position it last visited.
    '''
    x, y = node.get_blank_tile_loc()
    if_last_visited = direction + node.action
    if direction == 1:
        change = x - 1
    elif direction == 2:
        change = x + 1
    elif direction == 3:
        change = y - 1
    elif direction == 4:
        change = y + 1
    if node.action == 0:  #  action = 0 means it is the root node
        return change >=0 and change < 3
    else:
        return if_last_visited != 3 and if_last_visited != 7 and change >=0 and change < 3

def move(node, direction):
    '''
    Move the node to the specified direction.
    Return a new node.
    '''
    state = node.state.copy()  # make a copy of the state
    x, y = node.get_blank_tile_loc()
    if direction == 1:
        state[x][y], state[x - 1][y] = state[x - 1][y], state[x][y]
    elif direction == 2:
        state[x][y], state[x + 1][y] = state[x + 1][y], state[x][y]
    elif direction == 3:
        state[x][y], state[x][y - 1] = state[x][y - 1], state[x][y]
    elif direction == 4:
        state[x][y], state[x][y + 1] = state[x][y + 1], state[x][y]
    new_node = Node(state)
    new_node.parent = node
    new_node.action = direction
    new_node.g = node.g + 1
    return new_node

def Astar(root):
    '''
    The A* search.

    :return: the node with the goal state and the number of nodes expanded.
    '''
    queue = PriorityQueue()
    nodes_expanded = 1
    queue.put(root)
    while(not queue.empty()):
        min_f_node = queue.get()
        if min_f_node.is_goal():
            # print(nodes_expanded)
            return min_f_node, nodes_expanded
        for i in range(1, 5):
            if is_valid_move(min_f_node, i):
                nodes_expanded += 1
                child = move(min_f_node, i)
                queue.put(child)
    return None

def load_nn_model(choice):
    '''
    Load a neural networks model that has been trained.
    The training process is in the file of "train.py".
    '''
    if choice == 1:
        Node.heuristic = 1
        with open('model_1', 'rb') as f:
            model = pickle.load(f)
    elif choice == 2:
        Node.heuristic = 2
        with open('model_2', 'rb') as f:
            model = pickle.load(f)
    Node.model = model