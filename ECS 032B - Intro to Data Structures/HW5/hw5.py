
# Problem 1
#   http://interactivepython.org/courselib/static/pythonds/SortSearch/TheInsertionSort.html

def insertionSort(alist):
    for index in range(1,len(alist)):

        currentvalue = alist[index]
        position = index

        while position>0 and alist[position-1]<currentvalue:
            alist[position]=alist[position-1]
            position = position-1

        alist[position]=currentvalue

# Problem 2
#   http://interactivepython.org/courselib/static/pythonds/SortSearch/TheBubbleSort.html

def bubbleSort(alist):
    for passnum in range(len(alist)-1,0,-1):
        for i in range(passnum):
            if alist[i]<alist[i+1]:
                alist[i], alist[i+1] = alist[i+1], alist[i]

# Problem 3
#   Selection Sort as shown in class: Lecture 19, Slide 45

def selectionSortK(alist, k):
    for i in range(0,k):
        min = i
        for j in range(i + 1, len(alist)):
            if alist[j] < alist[min]:
                min = j
        temp = alist[i]
        alist[i] = alist[min]
        alist[min] = temp

# Problem 4
#   http://interactivepython.org/courselib/static/pythonds/SortSearch/TheMergeSort.html
def mergeSort(alist, workspace=None, start=None, end=None):

    #### You can change this code if you want to, but it sufficient to implement a solution.
    if workspace is None:
        workspace = [None] * len(alist)
        start = 0
        end = len(alist) #### Note that end is not a valid index into the array -- it's one past the last element!

    if end-start <= 1:
        return

    midpoint = (start+end)//2

    subvar_1 = midpoint - start ### midpoint is 2 start is 0 
    subvar_2 = end - midpoint ###[1,2,3,4]  end = 4 midpoint is 2
    left_side = [0 for i in range(subvar_1)]  
    right_side = [0 for i in range(subvar_2)]
    #left side temp array
    for i in range(0, subvar_1):
        left_side[i] = alist[start + i]

    for j in range(0, subvar_2):
        right_side[j] = alist[midpoint + j]

    i = j = 0
    k = start
    
    #merge temp lists
    
    while i < subvar_1 and j < subvar_2:
        
        if left_side[i] <= right_side[j]:
            workspace[k] = left_side[i]
            i += 1
        else:
            workspace[k] = right_side[j]
            j += 1
        k += 1
    while i < subvar_1:
        workspace[k] = left_side[i]
        i += 1 
        k += 1
    while j < subvar_2:
        workspace[k] = right_side[j]
        j += 1 
        k += 1 
    
    for i in range(end):
        alist[i] = workspace[i]

    
       
    mergeSort(alist, workspace, start, midpoint)
    mergeSort(alist, workspace, midpoint, end)
     
    #### From here on, the code will look very similar to the code from the textbook
    ####    Be sure you understand what the code is doing before you copy it over!
    ####    Remember to copy the data back from the workspace!

