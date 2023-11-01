# Your name and email here
from Node import Node
# Problem 1

def findSmallest(items):
	listValue = items
	if len(listValue) == 1: #base case 
		return listValue[0]
	else: #recursive case
		itemsTail = listValue[1:] #reduction step
		smallestInTail = findSmallest(itemsTail) #recursive call
		smallestValue = min(items[0],smallestInTail)
		return smallestValue


# Problem 2

def findValue(value, linkedList):
    raise NotImplementedError

# Problems 3 and 5

def ladder(rungs):
    raise NotImplementedError

# Problem 4

def recPal(str):
    raise NotImplementedError

