# Geoffrey Mohn gmohn@ucdavis.edu
from Node import Node
# Problem 1

def findSmallest(items): #cleaned up version after removing trivial variables as placeholders
	if len(items) == 1: #base case 
		return items[0]
	return min(items[0],findSmallest(items[1:])) #recursive call/reduction step/recursive case 


# Problem 2

def findValue(value, linkedList):
    if linkedList is None: #base case
    	return False
    if linkedList.getData() == value: #call getData module to see if inputted value is found
    	return True
    else:
    	return findValue(value, linkedList.getNext()) #recursively check for the value of linked list then go to next node 
# Problems 3 and 5

def ladder(rungs, knownResults = {}):
    if rungs in knownResults: #memoization that returns a cached value from dict knownResults back into the recursive function
    	return knownResults[rungs]
    if rungs == 1 or rungs == 0: #base case
    	return 1
    elif rungs == 2: #base case 
    	return 2
    else:
    	knownResults[rungs] = ladder(rungs-2) + ladder(rungs-1) #store the value into the dict to cache
    	return ladder(rungs-2) + ladder(rungs-1) #recrusive call that checks for climbing 1 rung and then 2 rungs

# Problem 4

def recPal(str):
    if len(str) < 2: #base case 
    	return True
    if str[0] != str[-1]: #if string is not string backwards then false 
    	return False
    return recPal(str[1:-1])

