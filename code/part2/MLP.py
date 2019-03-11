"""
Filename: MLP.py

An implementation of Multi-layer Perceptrons.

"""

import numpy as np
import pickle


def neuron_layer(number_of_neurons, number_of_inputs):
    '''
    Generate initial weights which are sampled
    from a uniform distribution in the range of [-0.5, 0.5].
    '''
    return 1 * np.random.rand(number_of_neurons, number_of_inputs) - 0.5


class MLP:

    def __init__(self, hidden1, hidden2, output, learning_rate=0.0005):
        self.hidden1_w = hidden1
        self.hidden2_w = hidden2
        self.output_w =  output
        self.bias_1, self.bias_2, self.bias_3 = 1 * np.random.rand(3) - 0.5
        self.lr = learning_rate

    def feed_forward(self, inputs):
        self.layer_1 = self.sigmoid(np.dot(inputs, self.hidden1_w.T) + self.bias_1)
        self.layer_2 = self.sigmoid(np.dot(self.layer_1, self.hidden2_w.T) + self.bias_2)
        self.output = np.dot(self.layer_2, self.output_w.T) + self.bias_3 

    def back_propagate(self, inputs, targets):
        output_err = -(targets - self.output)
        layer_2_err = output_err.dot(self.output_w)
        layer_2_delta = layer_2_err * self.sigmoid_derivative(self.layer_2)
        layer_1_err = layer_2_delta.dot(self.hidden2_w)
        layer_1_delta = layer_1_err * self.sigmoid_derivative(self.layer_1)
        # compute the gradients of weights
        w_output_grad = output_err.T.dot(self.layer_2)
        w_2_grad = layer_2_delta.T.dot(self.layer_1)
        w_1_grad = layer_1_delta.T.dot(inputs)
        # compute the gradients of bias
        b3_g = np.sum(output_err, axis=0)
        b2_g = np.sum(layer_2_delta, axis=0)
        b1_g = np.sum(layer_1_delta, axis=0)
        return w_1_grad, w_2_grad, w_output_grad, b1_g, b2_g, b3_g

    def sigmoid(self, x):
        return 1 / (1 + np.exp(-x))

    def sigmoid_derivative(self, x):
        return x * (1 - x)

    def train(self, train_X, train_y, test_X, test_y, epoch=5000):
        '''
        Train with a part of the dataset and test with the rest.
        Record the train loss and test loss.
        '''
        alpha = self.lr
        # record the train errors and test errors
        train_loss_history = []
        test_loss_history = []
        for _ in range(epoch):
            self.feed_forward(train_X)
            # compute the quadratic cost
            train_loss_history.append(0.5 * np.square(train_y - self.output).sum())
            test_loss_history.append(0.5 * np.square(test_y - self.predict(test_X)).sum())
            w_1_grad, w_2_grad, w_output_grad, b1_g, b2_g, b3_g = self.back_propagate(train_X, train_y)
            # update the weights and bias
            self.hidden1_w -= alpha * w_1_grad
            self.hidden2_w -= alpha * w_2_grad
            self.output_w -= alpha * w_output_grad
            self.bias_1 -= alpha * b1_g
            self.bias_2 -= alpha * b2_g
            self.bias_3 -= alpha * b3_g
        return train_loss_history, test_loss_history

    def train_all(self, train_X, train_y, file_name, epoch=5000):
        '''
        Train with the whole dataset
        and store the model as a local file for further use.
        '''
        alpha = self.lr
        train_loss_history = []
        for _ in range(epoch):
            self.feed_forward(train_X)
            # compute the quadratic cost
            train_loss_history.append(0.5 * np.square(train_y - self.output).sum())
            w_1_grad, w_2_grad, w_output_grad, b1_g, b2_g, b3_g = self.back_propagate(train_X, train_y)
            self.hidden1_w -= alpha * w_1_grad
            self.hidden2_w -= alpha * w_2_grad
            self.output_w -= alpha * w_output_grad
            self.bias_1 -= alpha * b1_g
            self.bias_2 -= alpha * b2_g
            self.bias_3 -= alpha * b3_g
        with open(file_name, 'wb') as f:
            pickle.dump(self, f)
        return train_loss_history

    def predict(self, x):
        '''
        Predict the output using the trained model.
        '''
        layer_1 = self.sigmoid(np.dot(x, self.hidden1_w.T) + self.bias_1)
        layer_2 = self.sigmoid(np.dot(layer_1, self.hidden2_w.T) + self.bias_2)
        output = np.dot(layer_2, self.output_w.T) + self.bias_3 
        # print(output.shape)
        return output

