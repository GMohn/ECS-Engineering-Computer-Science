#Geoffrey Mohn ID 912568148
# Problem 1

def sequentialSearchRec(alist, item, index=0):
    if index < len(alist):
    	if item == alist[index]:
    		return True
    	else:
    		return sequentialSearchRec(alist, item, index + 1)
    return False

# Problem 2

def binarySearchRec(alist, item, first=None, last=None):

    if first is None:
    	first = 0
    if last is None:
    	last = len(alist)-1

    if len(alist) == 0:
    	return False
    else: 	
    	mid = (first + last) // 2
    	if item == alist[mid]:
    		return True
    	elif item < alist[mid]:
    		if mid <= first:
    			return False 
    		return binarySearchRec(alist, item, first, mid-1)
    	else:
    		if mid >= last:
    			return False
    		return binarySearchRec(alist, item, mid+1, last)


