from UnorderedList import UnorderedList
from UnorderedList import Node

# Problem 1

class QueueFE:
    def __init__(self):
        self.items = []

    def isEmpty(self):
        return self.items == []

    def enqueue(self, item):
        self.items.append(item)

    def dequeue(self):
        return self.items.pop(0)

    def size(self):
        return len(self.items)

# Problem 2
#LIFO

class Stack:
     def __init__(self):
        ulist = UnorderedList()
        print(ulist.head)
        ulist.head = None


        

     def isEmpty(self):
        ulist = UnorderedList()
        return ulist.isEmpty()



     def push(self, item):
        ulist = UnorderedList()
        if ulist.head is None:
            ulist.insert()
        else:
            new_node = Node(item)
            new_node.next = ulist.head
            ulist.head = new_node
            ulist.insert()


     def pop(self):
        ulist = UnorderedList()
        if ulist.head is None:
            return None
        else:
            popped = ulist.head.data
            ulist.head = ulist.head.next
            return popped


     def peek(self):
        ulist = UnorderedList()
        if ulist.head is None:
            return None
        else:
            return ulist.head.data

     def size(self):
        ulist = UnorderedList()
        current = ulist.head
        count = 0
        while current:
            count+= 1
            current = current.getNext()
        return count

# Problem 3
#FIFO
class Queue:
    def __init__(self):
        self.head = None
        self.tail = None

    def isEmpty(self):
        ulist = UnorderedList()
        return self.head == None

    def enqueue(self, item):
        new_node = Node(item)
        if self.tail == None:
            self.head = new_node
            self.tail = self.head
        else:
            self.tail.next = new_node
            self.tail = self.tail.next


    def dequeue(self):
        if self.head is None:
            return None
        else:
            temp = self.head.data
            self.head = self.head.next
        return temp

    def size(self):
        current = self.head
        count = 0
        while current:
            count+= 1
            current = current.getNext()
        return count

# Problem 4

class Deque:
    def __init__(self):
        self.head = None
        self.tail = None

    def isEmpty(self):
        return self.head == None

    def addFront(self, item): #works
        if self.head is None:
            self.head = Node(item)
        else:
            new_node = Node(item)
            new_node.next = self.head
            self.head = new_node


    
    def addRear(self, item): #works
        new_node = Node(item)
        if self.head is None:
            self.head = new_node
            return
        last_node = self.head 
        while last_node.next:
            last_node = last_node.next
        last_node.next = new_node

    def removeFront(self): #works
        curr_node = self.head
        if curr_node and curr_node.data is not None:
            self.head = curr_node.next
            curr_node = None
            return curr_node

    def removeRear(self): #does not work
        curr_node = self.head
        prev_node = curr_node 
       # print(curr_node.data)
        if self.head is None:
            return None
        else:
            if self.head.next is None:
                curr_node = self.head.data
                self.head = self.head.next
                #print("second if statement")
                return curr_node
            while curr_node.next is not None: # A - > B -> C -> None
                prev_node = curr_node
                #print("prev_node while statement ", prev_node.data)
                curr_node = curr_node.next
                #print("curr_node while statement ", curr_node.data)
            prev_node.next = None
        #print("prev_node before return ", prev_node.data)
            return prev_node


    def size(self):
        current = self.head
        #print(current)
        count = 0
        while current:
            count+= 1
            current = current.getNext()
            #print(count)
        return count
    def print_list(self):
        curr_node = self.head
        while curr_node:
           # print(curr_node.data)
            curr_node = curr_node.next

Stack()
llist = Deque()
llist.addFront("3")
llist.addFront("2") 
llist.addFront("1")
llist.addRear("4")
llist.addRear("5")
llist.addRear("6")  
print("printing list ") 
llist.print_list()
print("removing Front ")
llist.removeFront()
llist.removeFront()
llist.removeFront()
llist.removeFront()
print("printing list ") 
llist.print_list()
print("removing Front x2 ")
llist.removeFront()
print("printing list ")
llist.print_list()
#print("removing Rearx3 ")
#llist.removeRear()
print("size ")
llist.size()
print("printing list ") 
llist.print_list()
print("is empty?")
print(llist.isEmpty())
llist.addRear("69")
print("empty again?")
print(llist.isEmpty())

input('Press ENTER to exit')
