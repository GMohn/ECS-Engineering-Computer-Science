class Stack:
     def __init__(self):
         self.items = []

     def isEmpty(self):
         return self.items == []

     def push(self, item):
         self.items.append(item)

     def pop(self):
         return self.items.pop()

     def peek(self):
         return self.items[len(self.items)-1]

     def size(self):
         return len(self.items)


def balanced(inStr):
    s = Stack()
    for symbol in inStr:
        if symbol == "(":
            s.push(symbol)
        else:
            if s.isEmpty():
                return False
            else: s.pop()
    if s.isEmpty():
        return True
    else:
        return False

def recbalanced(inStr):
    #s = stack()
    paren_end = inStr.find(')')
    if paren_end == -1:
        return '(' not in inStr
    paren_start = inStr[:paren_end].rfind('(')
    if paren_start == -1:
        return False
    return recbalanced(inStr[:paren_start]+inStr[paren_end+1:])

print(balanced("()()(())"))
print(recbalanced("()()(())"))
input("enter to exit.")
