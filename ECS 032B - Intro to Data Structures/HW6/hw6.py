# ECS32B Spring 2019 Homework 6
# Geoffrey Mohn 912568148


# Grab some helper functions into the current namespace
from hw6_tools import *


# Problem 1
expTree = None
expTree = ExpTree("*")
node1 = ExpTree("+")
node2 = ExpTree("-")
node3 = ExpTree(3)
node4 = ExpTree("/")
node5 = ExpTree(1)
node6 = ExpTree(2)
node7 = ExpTree(5)
node8 = ExpTree(2)
expTree.setLeftChild(node1)     ### *      
expTree.setRightChild(node2)    ###/ \
node1.setLeftChild(node3)       ##+   -  
node1.setRightChild(node4)
node4.setLeftChild(node5)
node4.setRightChild(node6)
node2.setLeftChild(node7)
node2.setRightChild(node8)

print(printexp(expTree))
# Problem 2

def postorder(tree):
    if tree != None:
    	postorder(tree.getLeftChild())
    	postorder(tree.getRightChild())
    	print(tree.getRootVal(), ' ')

def preorder(tree):
    print(tree.getRootVal(), ' ')
    if tree.getLeftChild():
    	preorder(tree.getLeftChild())
    if tree.getRightChild():
    	preorder(tree.getRightChild())

def inorder(tree):
    if tree != None:
    	inorder(tree.getLeftChild())
    	print(tree.getRootVal(), ' ')
    	inorder(tree.getRightChild())

# Problem 3
def printexp(tree):
    sVal = ""
    if tree:
        sVal = printexp(tree.getLeftChild())
        sVal = sVal + str(tree.getRootVal())
        sVal = sVal + printexp(tree.getRightChild())
        if not str(tree.getRootVal()).isnumeric():
            sVal = '(' + sVal + ')'
    return sVal

# Problem 4

problem4_breadth_first_traversal = [0,1,2,5,3,4,6,8,7]
problem4_depth_first_traversal = [0,1,3,4,8,7,2,6,5]

# Problem 5

flights = Graph()
smf = flights.addVertex('SMF')
#sfo = flights.addVertex('SFO')
flights.addEdge('SMF', 'SFO', 47)
flights.addEdge('SMF', 'LAX', 98)
#flights.addVertex('LAX')
#flights.addVertex('LAS')
#flights.addEdge('SMF', 'LAS', 198)
#flights.addVertex('PHX')
flights.addEdge('SFO', 'LAX', 49)
flights.addEdge('SFO', 'PHX', 198)
flights.addEdge('SFO', 'LAS', 98)
flights.addEdge('LAX', 'PHX', 98)
dijkstra(flights, smf)
