"""
construct_training_set.py

Construct a training set for neural networks.
"""

import numpy as np
import pickle
import time
from itertools import permutations
from random import shuffle
from Astar import Astar, Node

def check_solvable(puzzle):
    '''
    The 8-puzzle is solvable when the number of inversions is not odd.
    '''
    puzzle = list(puzzle)
    puzzle.remove(0)  # remove the blank tile
    sum_inversion = 0
    for i in np.arange(8):
        for j in np.arange(i + 1, 8):
            if puzzle[i] > puzzle[j]:
                sum_inversion += 1
    return sum_inversion % 2 == 0

def construct_training_set(n_try):
    '''
    Build a tranining set which is sampled from the instances of 8-puzzle.

    :param int n_try: the number of 8-puzzle instances to be solved.
    '''
    start = time.time()
    print('Total:', n_try)
    puzzle_l = np.arange(9)
    # get all the possible states of 8-puzzle
    perms = list(permutations(puzzle_l))
    # shuffel the permutations
    shuffle(perms)
    data = dict()
    count = 0  # count the number of tries when the puzzle is solvable
    for _ in range(len(perms)):
        if count % 100 == 0:
            print('Current process:', count)
        if count == n_try: break
        element = perms.pop()  # get an initial state of 8 puzzle
        if check_solvable(element):
            count += 1
            puzzle = np.array(element).reshape([3, 3])
            root = Node(puzzle) 
            solution = Astar(root)[0]
            if solution != None:
                # record the path cost of the solution
                full_cost = solution.g
                while(solution.parent != None):
                    # record the features of the states of the solution path
                    solution = solution.parent
                    sum_of_mattan_dis = solution.get_H1()
                    number_of_misplaced = solution.get_H2()
                    if data.get((sum_of_mattan_dis, number_of_misplaced)):
                        if len(data[(sum_of_mattan_dis, number_of_misplaced)]) > 20:
                            continue
                    cost = full_cost - solution.g
                    try:
                        data[(sum_of_mattan_dis, number_of_misplaced)].append(cost)
                    except:
                        data[(sum_of_mattan_dis, number_of_misplaced)] = [cost]
    # get the average cost of same initial heuristic values
    for key, value in data.items():
        data[key] = np.average(value)
    print(data)
    # save the dataset as a dictionary
    with open('dataset', 'wb') as f:
        pickle.dump(data, f)
    print(len(data.keys()))
    print('Dataset completed! Time elapsed: %.2f s' % (time.time() - start))

        
if __name__ == '__main__':
    construct_training_set(1000)
    


    

        