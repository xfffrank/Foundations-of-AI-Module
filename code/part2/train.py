"""
Filename: train.py

Train the neural networks models
"""

from MLP import *
import pickle
import matplotlib.pyplot as plt
import numpy as np

# The dataset will be built
# after running the file of "construct_training_set.py".
with open('dataset', 'rb') as f:
    dataset = pickle.load(f)

def train_test_split(features, targets):
    '''
    split 1/5 of dataset for testing and the rest for training
    '''
    split = int(1/5 * len(features))
    # print(split)
    train_X = features[split:]
    train_y = targets[split:]
    test_X = features[:split]
    test_y = targets[:split]
    return train_X, train_y, test_X, test_y

def train(num_of_features, alpha, refit=False, filename=None):
    '''
    Train neural networks.

    :param int num_of_features:
        num_of_features = 1: use the sum of Manhattan distances as features in the input layer;
        num_of_features = 2: use the sum of Manhattan distances and the number of misplaced tiles 
                             as features in the input layer;
    :param float alpha: learning rate
    :param boolean refit: if refit = True, the model will be trained with the whole dataset.
    :param str filename: if refit = True, a filename is needed to store the trained model.
    '''
    hidden_layer1 = neuron_layer(number_of_neurons=4, number_of_inputs=num_of_features)
    hidden_layer2 = neuron_layer(number_of_neurons=4, number_of_inputs=4)
    output_layer =  neuron_layer(number_of_neurons=1, number_of_inputs=4)
    features = []
    targets = []
    if num_of_features == 1:
        for key, value in dataset.items():
            features.append(key[0])
            targets.append(value)
        features = np.atleast_2d(features).T
        targets = np.atleast_2d(targets).T
    elif num_of_features == 2:
        for key, value in dataset.items():
            features.append(np.array(key))
            targets.append(value)
        features = np.array(features)
        targets = np.atleast_2d(targets).T
    if refit:
        nn_model = MLP(hidden_layer1, hidden_layer2, output_layer, learning_rate=alpha)
        loss_hist = nn_model.train_all(features, targets, filename)
        print(loss_hist[0], loss_hist[-1])
    else:
        # split the dataset into two parts 
        # for training the model and evaluating the model performance
        train_X, train_y, test_X, test_y = train_test_split(features, targets)
        print(train_X.shape, train_y.shape)
        print(test_X.shape, test_y.shape)
        mlp = MLP(hidden_layer1, hidden_layer2, output_layer, learning_rate=alpha)
        train_loss, test_loss = mlp.train(train_X, train_y, test_X, test_y)
        plot_train_test_loss(train_loss, test_loss, alpha)

def plot_train_test_loss(train_loss, test_loss, alpha):
    '''
    Plot the train loss and test loss as the epoch increases
    with the given alpha(learning rate).
    '''
    print(train_loss[0], train_loss[-1])
    print(test_loss[0], test_loss[-1])
    plt.plot(train_loss, label='train_loss')
    plt.plot(test_loss, label='test_loss')
    plt.xlabel('epoch')
    plt.ylabel('Quadratic cost')
    plt.title('learning rate: ' + str(alpha))
    plt.yticks(np.arange(0,2000, 200))
    plt.ylim([0, 2000])
    plt.legend()
    plt.show()


if __name__ == '__main__':
    # Compare train loss with test loss given different learning rates
    # learning_rates = [1e-3, 5e-4, 1e-5]
    # for lr in learning_rates:
    #     print(lr)
    #     train(num_of_features=2, alpha=lr)
    #     train(num_of_features=1, alpha=lr)

    # train and save the model with the best learning rate
    lr = 5e-4
    # print(lr)
    train(num_of_features=1, alpha=lr, refit=True, filename='model_1')
    train(num_of_features=2, alpha=lr, refit=True, filename='model_2')
    
    
