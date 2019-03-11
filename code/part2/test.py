"""
Filename: test.py

Run tests with the trained neural networks models which will be used in A* search.
"""

import pickle
from Astar import *
import numpy as np
from itertools import permutations
from random import shuffle
import matplotlib.pyplot as plt
from construct_training_set import check_solvable


def test(number_of_test):
    '''
    Generate a number of random 8-puzzles that are solvable
    and apply them to the new A* search with heuristic functions learned by neural networks
    and the normal A* search which uses the sum of Manhattan distances as the heuristic value.

    :param int number_of_test: the number of randomly generated 8-puzzle
    '''
    # generate some 8-puzzles and store them in a list
    puzzle_l = np.arange(9)
    perms = list(permutations(puzzle_l))
    shuffle(perms)
    test_puzzles = []
    while(len(perms) > 0):
        eg = perms.pop()
        if check_solvable(eg):
            puzzle = np.array(eg).reshape([3, 3])
            test_puzzles.append(puzzle)
            if len(test_puzzles) == number_of_test:
                break
    # test the normal A* search
    nodes_list1 = []
    for puzzle in test_puzzles:
        root = Node(puzzle)
        num_of_nodes = Astar(root)[1]
        nodes_list1.append(num_of_nodes)
    # test the A* search which used one-feature neural networks model
    nodes_list2 = []
    load_nn_model(choice=1)
    for puzzle in test_puzzles:
        root = Node(puzzle)
        num_of_nodes = Astar(root)[1]
        nodes_list2.append(num_of_nodes)
    # test the A* search which used two-features neural networks model
    nodes_list3 = []
    load_nn_model(choice=2)
    for puzzle in test_puzzles:
        root = Node(puzzle)
        num_of_nodes = Astar(root)[1]
        nodes_list3.append(num_of_nodes)
    # plot and compare the results
    plt.figure(figsize=[10,5])
    plt.plot(nodes_list1, label='Manhattan')
    plt.plot(nodes_list2, label='OneFeature')
    plt.plot(nodes_list3, label='TwoFeatures')
    plt.xlabel('the instances of 8-puzzles')
    plt.ylabel('the number of nodes expanded')
    plt.legend()
    plt.show()


test(200)
        
