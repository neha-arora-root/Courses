import numpy as np
from random import shuffle
from past.builtins import xrange

def softmax_loss_naive(W, X, y, reg):
  """
  Softmax loss function, naive implementation (with loops)

  Inputs have dimension D, there are C classes, and we operate on minibatches
  of N examples.

  Inputs:
  - W: A numpy array of shape (D, C) containing weights.
  - X: A numpy array of shape (N, D) containing a minibatch of data.
  - y: A numpy array of shape (N,) containing training labels; y[i] = c means
    that X[i] has label c, where 0 <= c < C.
  - reg: (float) regularization strength

  Returns a tuple of:
  - loss as single float
  - gradient with respect to weights W; an array of same shape as W
  """
  # Initialize the loss and gradient to zero.
  loss = 0.0
  dW = np.zeros_like(W)

  #############################################################################
  # TODO: Compute the softmax loss and its gradient using explicit loops.     #
  # Store the loss in loss and the gradient in dW. If you are not careful     #
  # here, it is easy to run into numeric instability. Don't forget the        #
  # regularization!                                                           #
  #############################################################################
  num_train = X.shape[0]
  num_classes = W.shape[1]

  for i in xrange(num_train):
    scores = X[i].dot(W)
    scores -= np.max(scores)
    expScores = np.exp(scores)
    normalizedScores = expScores/np.sum(expScores)
    loss += -np.log(normalizedScores[y[i]])
    dW[:,y[i]] -= X[i]
    for j in xrange(num_classes):
      dW[:,j] += X[i] * normalizedScores[j]
        
  loss /= num_train
  dW /= num_train
  loss += 0.5 * reg * np.sum(W * W)
  dW += reg * W
  #############################################################################
  #                          END OF YOUR CODE                                 #
  #############################################################################

  return loss, dW


def softmax_loss_vectorized(W, X, y, reg):
  """
  Softmax loss function, vectorized version.

  Inputs and outputs are the same as softmax_loss_naive.
  """
  # Initialize the loss and gradient to zero.
  num_train = X.shape[0]
  loss = 0.0
  dW = np.zeros_like(W)

  #############################################################################
  # TODO: Compute the softmax loss and its gradient using no explicit loops.  #
  # Store the loss in loss and the gradient in dW. If you are not careful     #
  # here, it is easy to run into numeric instability. Don't forget the        #
  # regularization!                                                           #
  #############################################################################
  scores = X.dot(W)
  scores -= np.max(scores, axis=1, keepdims=True)
  expScores = np.exp(scores)
  sumExpScores = np.sum(expScores, axis=1, keepdims=True)
  normalizedScores = expScores/sumExpScores

  loss = np.sum(-np.log(normalizedScores[np.arange(num_train), y]))/num_train
  loss += 0.5 * reg * np.sum(W * W)
  
  gradLossByScore = normalizedScores
    
  ## gradient update = dL/df * df/dw
  ## dL/df(k) = gradLossByScore = d/df(-score(K) + log(summation(normalizedScores(k)) )) [NxC]
  ## [K belongs to k], i.e., K is the correct class label
  ## Hence for k = K, dL/df = -1 + normalizedScore(k)
  ## and for k != K, dL/df = normalizedScore(k)
  gradLossByScore[np.arange(num_train), y] -= 1
  
  ## df/dw(k) = X [NxD]
  
  dW = X.T.dot(gradLossByScore)/num_train
  dW += reg * W
  #############################################################################
  #                          END OF YOUR CODE                                 #
  #############################################################################

  return loss, dW

