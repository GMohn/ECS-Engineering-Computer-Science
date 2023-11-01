
def oskaplayer(board,turnPiece, depth):
    if turnPiece == 'w':
        return minimax(board,True,depth)[1]
    else:
        return minimax(board,False,depth)[1]
"""
returns an integer value of game state
Keeps track of number of pieces, number of pieces at the end, and gives a score based on number of pieces and a bonus if at end"""
def staticEval(board):
    numWhite = 0
    numEndWhite = 0
    scoreWhite = 0
    scoreBlack = 0
    numBlack = 0
    numEndBlack = 0
    numRows = len(board)
    for y in range(numRows):
        numCols = len(board[y])
        for x in range(numCols):
            if board[y][x] == 'w':
                scoreWhite += 1
                numWhite += 1
                if y == numRows-1:
                    scoreWhite += .5
                    numEndWhite += 1
            elif board[y][x] == 'b':
                scoreBlack += 1
                numBlack += 1        
                if y == 0:
                    scoreBlack += .5
                    numEndBlack += 1
    #all pieces are at the end therefore has won
    if numWhite == numEndWhite:
        return 1e500
    if numBlack == numEndBlack:
        return -1e500
    #no more pieces then other player has won
    if scoreWhite == 0:
        return -1e500
    elif scoreBlack == 0:
        return 1e500
    
    return (scoreWhite - scoreBlack)

"""this function checks if a player has won based on the current evaluation of the board"""
def checkWinner(board):
    if staticEval(board) == abs(1e500):
        return True
    return False

"""
This function is the recursive minimax algorithm """
def minimax(board, maxPlayer, depth):
    if depth == 0 or checkWinner(board):
        #print(staticEval(board), board)
        return staticEval(board), board
    if maxPlayer:
        piece = 'w'
        maxEval = -1e500
        bestMove = None
        possibleMoves = movegen(board,piece)
        #if no possible moves for player then skip their move
        if not possibleMoves:
            piece = 'b'
            minEval = 1e500
            bestMove = None
            for move in movegen(board,piece):
                evaluation = minimax(move, True, depth-1)[0]
                minEval = min(minEval,evaluation)
                if minEval == evaluation:
                    bestMove = move
            return minEval, bestMove

        for move in possibleMoves:
            #only return maxEval for recursive call
            evaluation = minimax(move, False, depth-1)[0]
            maxEval = max(maxEval,evaluation)
            if maxEval == evaluation:
                bestMove = move

        return maxEval, bestMove

    else:
        piece = 'b'
        minEval = 1e500
        bestMove = None
        possibleMoves = movegen(board,piece)
        if not possibleMoves:
            maxEval = -1e500
            for move in possibleMoves:
                #only return maxEval for recursive call
                evaluation = minimax(move, False, depth-1)[0]
                maxEval = max(maxEval,evaluation)
                if maxEval == evaluation:
                    bestMove = move
            return maxEval, bestMove

        for move in possibleMoves:
            evaluation = minimax(move, True, depth-1)[0]
            minEval = min(minEval,evaluation)
            if minEval == evaluation:
                bestMove = move

        return minEval, bestMove
"""
This function was created due to previous flaws on left moves by the black pieces
It keeps track of the focused rows length and does string manipulation accordingly """
def moveLeftBlack(board,col,row,piece):
    tempRow = ""
    tempBoard = board[:]

    topRowLen = len(board[row-1])
    currRowLen = len(board[row])
    #row above is k+1
    if (topRowLen > currRowLen):
        #check if left diag is empty then create move 
        if (board[row-1][col] == "-"):
            tempBoard[row] = board[row][:col]+"-"+board[row][col+1:]
            tempBoard[row-1] = board[row-1][:col]+"b"+board[row-1][col+1:]
            return tempBoard

    #row above is k-1
    else:
        if (board[row-1][col-1] == "-"):
            tempBoard[row] = board[row][:col]+"-"+board[row][col+1:]
            tempBoard[row-1] = board[row-1][:col-1]+"b"+board[row-1][col:]
            return tempBoard
 
    #function has not returned; try jump
    #check if jump would exceed bound
    if (row+1 > 2):
        #3 cases here where the row to jump to is either k, k+2 or k-2
        jumpRowLen = len(board[row-2])
        # row is k
        if (currRowLen == jumpRowLen):
            #print("k jump")
            if (board[row-2][col-1] == '-'):
                tempBoard[row] = board[row][:col]+"-"+board[row][col+1:]
                tempBoard[row-1] = board[row-1][:col-1]+"-"+board[row-1][col:]
                tempBoard[row-2] = board[row-2][:col-1]+"b"+board[row-2][col:]
                return tempBoard
        #row is k+2
        elif (currRowLen+2 == jumpRowLen):
            if (board[row-2][col] == '-'):
                tempBoard[row] = board[row][:col]+"-"+board[row][col+1:]
                tempBoard[row-1] = board[row-1][:col]+"-"+board[row-1][col+1:]
                tempBoard[row-2] = board[row-2][:col]+"b"+board[row-2][col+1:]
                return tempBoard
        # row is k-2 
        else:
            #check if pos of piece would not hit the wall
            if(col >= topRowLen-1):
                if (board[row-2][col-2] == '-'):
                    tempBoard[row] = board[row][:col]+"-"+board[row][col+1:]
                    tempBoard[row-1] = board[row-1][:col-1]+"-"+board[row-1][col+1:]
                    tempBoard[row-2] = board[row-2][:col-2]+"b"+board[row-2][col+1:]
                    return tempBoard


#this function is called if a left move is available
def moveLeft(board,col,row,piece):
    tempRow = ""
    tempBoard = board[:]
    currRowLen = len(board[row])
    #piece is white move down and left
    if (piece == "w"):
        # if the row size is less than next then we know size of next is k+1 
        if (len(board[row]) < len(board[row+1])) and board[row+1][col] == "-":
            tempBoard[row] =  board[row][:col]+"-"+board[row][col+1:]
            tempBoard[row+1] = board[row+1][:col]+piece+board[row+1][col+1:]
            return tempBoard
        #if the piece can move to empty square, create move k-1
        if (board[row+1][col-1] == "-") and len(board[row]) > len(board[row+1]):
            tempBoard[row] = board[row][:col]+"-"+board[row][col+1:]
            tempBoard[row+1] = board[row+1][:col-1]+piece+board[row+1][col:]
            return(tempBoard)
        #the piece is blocked by opponent
        elif (board[row+1][col-1] == "b"):
            #check if not at end of board as white by getting difference
            #check if jump would exceed bound
            if (row+2 <= len(board)):
                #3 cases here where the row to jump to is either k, k+2 or k-2
                if row+2 == len(board):
                    jumpRowLen = len(board[row+1])
                else:
                    jumpRowLen = len(board[row+2])
                # row is k
                if (currRowLen == jumpRowLen):
                    if (board[row+2][col-1] == '-'):
                        tempBoard[row] = board[row][:col]+"-"+board[row][col+1:]
                        tempBoard[row+1] = board[row+1][:col-1]+"-"+board[row+1][col:]
                        tempBoard[row+2] = board[row+2][:col-1]+piece+board[row+2][col:]
                        return tempBoard
                #row is k+2
                elif (currRowLen+2 == jumpRowLen):
                    if (board[row+2][col] == '-'):
                        tempBoard[row] = board[row][:col]+"-"+board[row][col+1:]
                        tempBoard[row+1] = board[row+1][:col]+"-"+board[row+1][col+1:]
                        tempBoard[row+2] = board[row+2][:col]+piece+board[row+2][col+1:]
                        return tempBoard
                # row is k-2 
                else:
                    #check if pos of piece would not hit the wall
                    if(col-2 >= 0 ):
                        if (board[row+2][col-2] == '-'):
                            tempBoard[row] = board[row][:col]+"-"+board[row][col+1:]
                            tempBoard[row+1] = board[row+1][:col-1]+"-"+board[row+1][col:]
                            tempBoard[row+2] = board[row+2][:col-2]+piece+board[row+2][col-1:]
                            return tempBoard
    #piece is black move up and left
    else:
        return moveLeftBlack(board,col,row,piece)
        if (len(board[row]) > len(board[row-1])):
            if (board[row-1][col-1] == "-"):
                tempBoard[row] = board[row][:col]+"-"+board[row][col+1:]
                tempBoard[row-1] = board[row-1][:col-1]+piece+board[row-1][col:]
                return(tempBoard)
            #Jump Piece
            elif (board[row-1][col-1] == "w"):
                #check if not at end of board
                if (len(board)>= row-2):
                    if (board[row-2][col-2] == "-"):
                        tempBoard[row] = board[row][:col]+"-"+board[row][col+1:]
                        tempBoard[row-1] = board[row-1][:col]+"-"+board[row-1][col+1:]
                        tempBoard[row-2] = board[row-2][:col]+piece+board[row-2][col+1:]
                        return(tempBoard)
        #the current row is smaller than the next row
        else:
            if (board[row-1][col] == "-"):
                tempBoard[row] = board[row][:col]+"-"+board[row][col+1:]
                tempBoard[row-1] = piece+board[row-1][col+1:]
                return(tempBoard)
            #Jump Piece
            elif (board[row-1][col] == "w"):
                #check if not at end of board
                if (len(board)>= row+2):
                    if (board[row-2][col] == "-"):
                        tempBoard[row] = board[row][:col+1]+"-"+board[row][col+2:]
                        tempBoard[row-1] = board[row-1][:col+1]+"-"+board[row-1][col+2:]
                        tempBoard[row-2] = board[row-2][:col+1]+piece+board[row-2][col+2:]
                        return(tempBoard)

"""
This function was created due to previous flaws on right moves by the black pieces
It keeps track of the focused rows length and does string manipulation accordingly """
def moveRightBlack(board,col,row,piece):
    tempRow = ""
    tempBoard = board[:]

    topRowLen = len(board[row-1])
    currRowLen = len(board[row])

    #row above is k+1
    if (topRowLen > currRowLen):
        #check if right diag is empty then create move 
        if (board[row-1][col+1] == "-"):
            tempBoard[row] = board[row][:col]+"-"+board[row][col+1:]
            tempBoard[row-1] = board[row-1][:col+1]+"b"+board[row-1][col+2:]
            return tempBoard

    #row above is k-1
    else:
        if (board[row-1][col] == "-"):
            tempBoard[row] = board[row][:col]+"-"+board[row][col+1:]
            tempBoard[row-1] = board[row-1][:col]+"b"+board[row-1][col+1:]
            return tempBoard
 
    #function has not returned try jump
    #check if jump would exceed bound
    if (row+1 > 2):
        #3 cases here where the row to jump to is either k, k+2 or k-2
        jumpRowLen = len(board[row-2])
        # row is k
        if (currRowLen == jumpRowLen):
            if (board[row-2][col+1] == '-'):
                tempBoard[row] = board[row][:col]+"-"+board[row][col+1:]
                tempBoard[row-1] = board[row-1][:col]+"-"+board[row-1][col+1:]
                tempBoard[row-2] = board[row-2][:col+1]+"b"+board[row-2][col+2:]
                return tempBoard
        #row is k+2
        elif (currRowLen+2 == jumpRowLen):
            if (board[row-2][col+2] == '-'):
                tempBoard[row] = board[row][:col]+"-"+board[row][col+1:]
                tempBoard[row-1] = board[row-1][:col+1]+"-"+board[row-1][col+2:]
                tempBoard[row-2] = board[row-2][:col+2]+"b"+board[row-2][col+3:]
                return tempBoard
        # row is k-2 
        else:
            #check if pos of piece would not hit the wall
            if(col < topRowLen-1):
                if (board[row-2][col] == '-'):
                    tempBoard[row] = board[row][:col]+"-"+board[row][col+1:]
                    tempBoard[row-1] = board[row-1][:col]+"-"+board[row-1][col+1:]
                    tempBoard[row-2] = board[row-2][:col]+"b"+board[row-2][col+1:]
                    return tempBoard






"""
This function attempts to move the piece diagonally
it modifies placements based on piece and position
returns the legal right move in a list 
"""  
def moveRight(board,col,row,piece):
    tempRow = ""
    tempBoard = board[:]
    topRowLen = len(board[row-1])
    currRowLen = len(board[row])
    if (piece == "w"):
        # if the row size is less than next then we know size of next is k+1 
        if (len(board[row]) < len(board[row+1])) and board[row+1][col+1] == "-":
            tempBoard[row] =  board[row][:col]+"-"+board[row][col+1:]
            tempBoard[row+1] = board[row+1][:col+1]+piece+board[row+1][col+2:]
            return tempBoard
        #if the piece can move to empty square, create move k-1
        if (board[row+1][col] == "-") and len(board[row]) > len(board[row+1]):
            tempBoard[row] = board[row][:col]+"-"+board[row][col+1:]
            tempBoard[row+1] = board[row+1][:col]+piece+board[row+1][col+1:]
            return(tempBoard)
        #the piece is blocked by opponent
        elif (board[row+1][col-1] == "b"):
            #check if not at end of board as white by getting difference
            #check if jump would exceed bound
            if (row+2 <= len(board)):
                #3 cases here where the row to jump to is either k, k+2 or k-2
                jumpRowLen = len(board[row+2])
                # row is k
                if (currRowLen == jumpRowLen):
                    if (board[row+2][col-1] == '-'):
                        tempBoard[row] = board[row][:col]+"-"+board[row][col+1:]
                        tempBoard[row+1] = board[row+1][:col]+"-"+board[row+1][col+1:]
                        tempBoard[row+2] = board[row+2][:col+1]+piece+board[row+2][col+2:]
                        return tempBoard
                #row is k+2
                elif (currRowLen+2 == jumpRowLen):
                     if (board[row+2][col+2] == '-'):
                        tempBoard[row] = board[row][:col]+"-"+board[row][col+1:]
                        tempBoard[row+1] = board[row+1][:col+1]+"-"+board[row+1][col+2:]
                        tempBoard[row+2] = board[row+2][:col+2]+piece+board[row+2][col+3:]
                        return tempBoard
                # row is k-2 
                else:
                    #check if pos of piece would not hit the wall
                    if(col < currRowLen-2 ):
                        if (board[row+2][col] == '-'):
                            tempBoard[row] = board[row][:col]+"-"+board[row][col+1:]
                            tempBoard[row+1] = board[row+1][:col]+"-"+board[row+1][col+1:]
                            tempBoard[row+2] = board[row+2][:col]+piece+board[row+2][col+1:]
                            return tempBoard

    # Move up right for black piece                    
    else:
        return moveRightBlack(board,col,row,piece)
        '''#if the x pos of row is greater than the next row len then position is at the edge
        if (col+1 >= len(board[row-1])):
            tempBoard[row] = tempBoard[row] = board[row][:col]+"-"+board[row][col+1:]
            tempBoard[row-1] = board[row-1][:col]+piece
            return tempBoard
        # if top right diag is not same piece and next row is k+1
        if (board[row-1][col+1] != piece) and (len(board[row-1]> len(board[row]))):
            #Jump Piece as black 
            if (board[row-1][col+1] == "w"):
                #check if not at end of board
                if ((len(board)-(len(board)-row))>= 2):
                    if (board[row-2][col] == "-") and (len(board[row] == len(board[row-2]))):
                        tempBoard[row] = board[row][:col]+"-"+board[row][col+1:]
                        tempBoard[row-1] = board[row-1][:col]+"-"+board[row-1][col+1:]
                        tempBoard[row-2] = board[row-2][:col]+piece+board[row-2][col+1:]
                        return(tempBoard)   
            tempBoard[row] = board[row][:col]+"-"+board[row][col+1:]
            tempBoard[row-1] = board[row-1][:col+1]+piece+board[row-1][col+2:]
            return(tempBoard)
'''
        


'''
This function returns a list of all available moves 
it iterates through the board and calls either moveRight or moveLeft 
appends return to a list of new board states
'''
def movegen(boardState,pieceTurn):
    #print(boardState)
    tempBoard = []
    
    numRows = len(boardState)
    for y in range(numRows):
        numCols = len(boardState[y])
        for x in range(numCols):
            if boardState[y][x] == pieceTurn:

                if ((pieceTurn == "w") and (y == numRows-1)):
                    #TODO add functionality when the white piece is at the goal
                    break

                elif ((pieceTurn == "b") and (y == 0)):
                    #TODO add functionality when the black piece is at the goal
                    break
                
                #white piece on left edge and the next row is -1 of current size
                if (x == 0) and (pieceTurn == "w") and (numCols > len(boardState[y+1])):
                   
                    #white piece at left end try to move right
                    if (boardState[y+1][x] != pieceTurn):                        
                        tempBoard.append(moveRight(boardState,x,y,pieceTurn))

                #black piece in left corner
                elif (x == 0) and (pieceTurn == "b") and (numCols > len(boardState[y-1])):

                    if (boardState[y-1][x] != pieceTurn):
                        tempBoard.append(moveRight(boardState,x,y,pieceTurn))    
                
                #piece at right end try move left
                elif(x == numCols-1) and (pieceTurn == "w") and (numCols > len(boardState[y+1])):

                    if (boardState[y+1][x-1] != pieceTurn):
                        tempBoard.append(moveLeft(boardState,x,y,pieceTurn))
                #black piece at right end try to move left
                elif(x == numCols-1) and (pieceTurn == "b") and (numCols > len(boardState[y-1])):

                    if (boardState[y-1][x-1] != pieceTurn):
                        tempBoard.append(moveLeft(boardState,x,y,pieceTurn))
                # piece is not at the ends try both
                else:
                    tempBoard.append(moveRight(boardState,x,y,pieceTurn))
                    tempBoard.append(moveLeft(boardState,x,y,pieceTurn))
    result = [k for k in tempBoard if k]
    return result


#testing
board = ['---b', 'ww-', 'bb', '---', '-b--']
turn = 'b'
depth = 8
value, newMove = minimax(board,False,depth)
print(oskaplayer(['wwww','---','--','---','bbbb'],'w',2))

# ['-------', '-bb---', '--w-b', 'w-b-', '--b', '--', '---', '--bw', '-----', '--ww--', '-w-----']
'''def printBoard(n):
    numRows = (2*n)-3
    board = [["-"]*(n-i) for i in range(numRows) if (n-i)>=2]vbnm

    print(board)

def oskaplayer(boardState,pieceTurn,maxDepth):
    
oskaplayer(['www','--','bbb'],'w',2)


#testing
def testCases(expectedRes, actualRes, passed, failed):
    expectedSet, actualSet = set(), set()
    for state in expectedRes:
        expectedSet.add(tuple(state))
    for state in actualRes:
        actualSet.add(tuple(state))
    if expectedSet == actualSet:
        passed += 1
    else:
        failed += 1
    return passed, failed

passed = failed = 0

expectedRes1 = movegen(['w-ww', '---', 'w-', 'b--', 'b-bb'], 'w')
actualRes1 = [['--ww', 'w--', 'w-', 'b--', 'b-bb'], ['w--w', '-w-', 'w-', 'b--', 'b-bb'], ['w--w', '--w', 'w-', 'b--', 'b-bb'], ['w-w-', '--w', 'w-', 'b--', 'b-bb'], ['w-ww', '---', '--', 'bw-', 'b-bb']]
expectedRes2 = movegen(['w-ww', '---', 'w-', 'b--', 'b-bb'], 'b')
actualRes2 = [['w-ww', '-b-', '--', '---', 'b-bb'], ['w-ww', '---', 'w-', 'bb-', 'b--b'], ['w-ww', '---', 'w-', 'b-b', 'b--b'], ['w-ww', '---', 'w-', 'b-b', 'b-b-']]
expectedRes3 = movegen( ['-------', '-bb---', '--w-b', 'w-b-', '--b', '--', '---', '--bw', '--w--', '---w--', '-w-----'], 'w')
actualRes3 = [['-------', '-bb---', '----b', 'wwb-', '--b', '--', '---', '--bw', '--w--', '---w--', '-w-----'], ['-------', '-bb---', '--w-b', '--b-', 'w-b', '--', '---', '--bw', '--w--', '---w--', '-w-----'], ['-------', '-bb---', '--w-b', 'w-b-', '--b', '--', '---', '--b-', '--w-w', '---w--', '-w-----'], ['-------', '-bb---', '--w-b', 'w-b-', '--b', '--', '---', '--b-', '--ww-', '---w--', '-w-----'], ['-------', '-bb---', '--w-b', 'w-b-', '--b', '--', '---', '--bw', '-----', '--ww--', '-w-----'], ['-------', '-bb---', '--w-b', 'w-b-', '--b', '--', '---', '--bw', '--w--', '------', '-w--w--'], ['-------', '-bb---', '--w-b', 'w-b-', '--b', '--', '---', '--bw', '--w--', '------', '-w-w---']]
expectedRes4 = movegen(['-------', '-bb---', '--w-b', 'w-b-', '--b', '--', '---', '--bw', '--w--', '---w--', '-w-----'], 'b')
actualRes4 = [['--b----', '--b---', '--w-b', 'w-b-', '--b', '--', '---', '--bw', '--w--', '---w--', '-w-----'], ['-b-----', '--b---', '--w-b', 'w-b-', '--b', '--', '---', '--bw', '--w--', '---w--', '-w-----'], ['---b---', '-b----', '--w-b', 'w-b-', '--b', '--', '---', '--bw', '--w--', '---w--', '-w-----'], ['--b----', '-b----', '--w-b', 'w-b-', '--b', '--', '---', '--bw', '--w--', '---w--', '-w-----'], ['-------', '-bb--b', '--w--', 'w-b-', '--b', '--', '---', '--bw', '--w--', '---w--', '-w-----'], ['-------', '-bb-b-', '--w--', 'w-b-', '--b', '--', '---', '--bw', '--w--', '---w--', '-w-----'], ['-------', '-bb---', '--wbb', 'w---', '--b', '--', '---', '--bw', '--w--', '---w--', '-w-----'], ['-------', '-bb---', '--w-b', 'w-bb', '---', '--', '---', '--bw', '--w--', '---w--', '-w-----'], ['-------', '-bb---', '--w-b', 'w-b-', '--b', '--', '-b-', '---w', '--w--', '---w--', '-w-----'], ['-------', '-bb---', '--w-b', 'w-b-', '--b', '--', '--b', '---w', '--w--', '---w--', '-w-----']]
expectedRes5 = movegen(['-b---', 'wwww', 'bbb', 'w-', '---', '----', '-----'], 'w')
actualRes5 = [['-b---', 'w-ww', 'b-b', 'ww', '---', '----', '-----'], ['-b---', 'www-', 'bb-', 'ww', '---', '----', '-----'], ['-b---', 'wwww', 'bbb', '--', '-w-', '----', '-----'], ['-b---', 'wwww', 'bbb', '--', 'w--', '----', '-----']]
expectedRes6 = movegen(['-b---', 'wwww', 'bbb', 'w-', '---', '----', '-----'], 'b')
actualRes6 = [['-bb--', 'w-ww', '-bb', 'w-', '---', '----', '-----'], ['bb---', '-www', '-bb', 'w-', '---', '----', '-----'], ['-b-b-', 'ww-w', 'b-b', 'w-', '---', '----', '-----'], ['-b--b', 'www-', 'bb-', 'w-', '---', '----', '-----'], ['-bb--', 'ww-w', 'bb-', 'w-', '---', '----', '-----']]
expectedRes7 = movegen(['-----', '----', '---', 'b-', 'www', 'bbbb', '-w---'], 'w')
actualRes7 =  [['-----', '----', '---', 'b-', '-ww', 'b-bb', '-ww--'], ['-----', '----', '---', 'b-', '-ww', '-bbb', 'ww---'], ['-----', '----', '---', 'b-', 'w-w', 'bb-b', '-w-w-'], ['-----', '----', '---', 'b-', 'ww-', 'bbb-', '-w--w'], ['-----', '----', '---', 'b-', 'ww-', 'bb-b', '-ww--']]
expectedRes8 = movegen(['-----', '----', '---', 'b-', 'www', 'bbbb', '-w---'], 'b')
actualRes8 = [['-----', '----', '-b-', '--', 'www', 'bbbb', '-w---'], ['-----', '----', 'b--', '--', 'www', 'bbbb', '-w---'], ['-----', '----', '---', 'bb', 'w-w', 'b-bb', '-w---'], ['-----', '----', '---', 'bb', 'ww-', 'bbb-', '-w---']]
expectedRes9 = movegen(['---------------', '-w--------b---', '-------------', '----w------b', '----w---b--', '------w-b-', '---w-----', '--b-----', '--b----', '--b---', '-----', '-bww', '---', '--', '---', '---w', '----w', '-----b', '------w', '------b-', '--w----w-', '------b---', '--w--------', '------------', '-----b------b', '--b-----------', '---------------'], 'w')
actualRes9 =  [['---------------', '----------b---', 'w------------', '----w------b', '----w---b--', '------w-b-', '---w-----', '--b-----', '--b----', '--b---', '-----', '-bww', '---', '--', '---', '---w', '----w', '-----b', '------w', '------b-', '--w----w-', '------b---', '--w--------', '------------', '-----b------b', '--b-----------', '---------------'], ['---------------', '----------b---', '-w-----------', '----w------b', '----w---b--', '------w-b-', '---w-----', '--b-----', '--b----', '--b---', '-----', '-bww', '---', '--', '---', '---w', '----w', '-----b', '------w', '------b-', '--w----w-', '------b---', '--w--------', '------------', '-----b------b', '--b-----------', '---------------'], ['---------------', '-w--------b---', '-------------', '-----------b', '---ww---b--', '------w-b-', '---w-----', '--b-----', '--b----', '--b---', '-----', '-bww', '---', '--', '---', '---w', '----w', '-----b', '------w', '------b-', '--w----w-', '------b---', '--w--------', '------------', '-----b------b', '--b-----------', '---------------'], ['---------------', '-w--------b---', '-------------', '----w------b', '--------b--', '---w--w-b-', '---w-----', '--b-----', '--b----', '--b---', '-----', '-bww', '---', '--', '---', '---w', '----w', '-----b', '------w', '------b-', '--w----w-', '------b---', '--w--------', '------------', '-----b------b', '--b-----------', '---------------'], ['---------------', '-w--------b---', '-------------', '----w------b', '--------b--', '----w-w-b-', '---w-----', '--b-----', '--b----', '--b---', '-----', '-bww', '---', '--', '---', '---w', '----w', '-----b', '------w', '------b-', '--w----w-', '------b---', '--w--------', '------------', '-----b------b', '--b-----------', '---------------'], ['---------------', '-w--------b---', '-------------', '----w------b', '----w---b--', '--------b-', '---w-w---', '--b-----', '--b----', '--b---', '-----', '-bww', '---', '--', '---', '---w', '----w', '-----b', '------w', '------b-', '--w----w-', '------b---', '--w--------', '------------', '-----b------b', '--b-----------', '---------------'], ['---------------', '-w--------b---', '-------------', '----w------b', '----w---b--', '--------b-', '---w--w--', '--b-----', '--b----', '--b---', '-----', '-bww', '---', '--', '---', '---w', '----w', '-----b', '------w', '------b-', '--w----w-', '------b---', '--w--------', '------------', '-----b------b', '--b-----------', '---------------'], ['---------------', '-w--------b---', '-------------', '----w------b', '----w---b--', '------w-b-', '---------', '--------', '-wb----', '--b---', '-----', '-bww', '---', '--', '---', '---w', '----w', '-----b', '------w', '------b-', '--w----w-', '------b---', '--w--------', '------------', '-----b------b', '--b-----------', '---------------'], ['---------------', '-w--------b---', '-------------', '----w------b', '----w---b--', '------w-b-', '---------', '--bw----', '--b----', '--b---', '-----', '-bww', '---', '--', '---', '---w', '----w', '-----b', '------w', '------b-', '--w----w-', '------b---', '--w--------', '------------', '-----b------b', '--b-----------', '---------------'], ['---------------', '-w--------b---', '-------------', '----w------b', '----w---b--', '------w-b-', '---w-----', '--b-----', '--b----', '--b---', '-----', '-b-w', '-w-', '--', '---', '---w', '----w', '-----b', '------w', '------b-', '--w----w-', '------b---', '--w--------', '------------', '-----b------b', '--b-----------', '---------------'], ['---------------', '-w--------b---', '-------------', '----w------b', '----w---b--', '------w-b-', '---w-----', '--b-----', '--b----', '--b---', '-----', '-b-w', '--w', '--', '---', '---w', '----w', '-----b', '------w', '------b-', '--w----w-', '------b---', '--w--------', '------------', '-----b------b', '--b-----------', '---------------'], ['---------------', '-w--------b---', '-------------', '----w------b', '----w---b--', '------w-b-', '---w-----', '--b-----', '--b----', '--b---', '-----', '-bw-', '--w', '--', '---', '---w', '----w', '-----b', '------w', '------b-', '--w----w-', '------b---', '--w--------', '------------', '-----b------b', '--b-----------', '---------------'], ['---------------', '-w--------b---', '-------------', '----w------b', '----w---b--', '------w-b-', '---w-----', '--b-----', '--b----', '--b---', '-----', '-bww', '---', '--', '---', '----', '---ww', '-----b', '------w', '------b-', '--w----w-', '------b---', '--w--------', '------------', '-----b------b', '--b-----------', '---------------'], ['---------------', '-w--------b---', '-------------', '----w------b', '----w---b--', '------w-b-', '---w-----', '--b-----', '--b----', '--b---', '-----', '-bww', '---', '--', '---', '---w', '-----', '----wb', '------w', '------b-', '--w----w-', '------b---', '--w--------', '------------', '-----b------b', '--b-----------', '---------------'], ['---------------', '-w--------b---', '-------------', '----w------b', '----w---b--', '------w-b-', '---w-----', '--b-----', '--b----', '--b---', '-----', '-bww', '---', '--', '---', '---w', '----w', '-----b', '-------', '------bw', '--w----w-', '------b---', '--w--------', '------------', '-----b------b', '--b-----------', '---------------'], ['---------------', '-w--------b---', '-------------', '----w------b', '----w---b--', '------w-b-', '---w-----', '--b-----', '--b----', '--b---', '-----', '-bww', '---', '--', '---', '---w', '----w', '-----b', '-------', '--------', '--w---ww-', '------b---', '--w--------', '------------', '-----b------b', '--b-----------', '---------------'], ['---------------', '-w--------b---', '-------------', '----w------b', '----w---b--', '------w-b-', '---w-----', '--b-----', '--b----', '--b---', '-----', '-bww', '---', '--', '---', '---w', '----w', '-----b', '------w', '------b-', '-------w-', '---w--b---', '--w--------', '------------', '-----b------b', '--b-----------', '---------------'], ['---------------', '-w--------b---', '-------------', '----w------b', '----w---b--', '------w-b-', '---w-----', '--b-----', '--b----', '--b---', '-----', '-bww', '---', '--', '---', '---w', '----w', '-----b', '------w', '------b-', '-------w-', '--w---b---', '--w--------', '------------', '-----b------b', '--b-----------', '---------------'], ['---------------', '-w--------b---', '-------------', '----w------b', '----w---b--', '------w-b-', '---w-----', '--b-----', '--b----', '--b---', '-----', '-bww', '---', '--', '---', '---w', '----w', '-----b', '------w', '------b-', '--w------', '------b-w-', '--w--------', '------------', '-----b------b', '--b-----------', '---------------'], ['---------------', '-w--------b---', '-------------', '----w------b', '----w---b--', '------w-b-', '---w-----', '--b-----', '--b----', '--b---', '-----', '-bww', '---', '--', '---', '---w', '----w', '-----b', '------w', '------b-', '--w------', '------bw--', '--w--------', '------------', '-----b------b', '--b-----------', '---------------'], ['---------------', '-w--------b---', '-------------', '----w------b', '----w---b--', '------w-b-', '---w-----', '--b-----', '--b----', '--b---', '-----', '-bww', '---', '--', '---', '---w', '----w', '-----b', '------w', '------b-', '--w----w-', '------b---', '-----------', '---w--------', '-----b------b', '--b-----------', '---------------'], ['---------------', '-w--------b---', '-------------', '----w------b', '----w---b--', '------w-b-', '---w-----', '--b-----', '--b----', '--b---', '-----', '-bww', '---', '--', '---', '---w', '----w', '-----b', '------w', '------b-', '--w----w-', '------b---', '-----------', '--w---------', '-----b------b', '--b-----------', '---------------']]
expectedRes10 = movegen(['---------------', '-w--------b---', '-------------', '----w------b', '----w---b--', '------w-b-', '---w-----', '--b-----', '--b----', '--b---', '-----', '-bww', '---', '--', '---', '---w', '----w', '-----b', '------w', '------b-', '--w----w-', '------b---', '--w--------', '------------', '-----b------b', '--b-----------', '---------------'], 'b')
actualRes10 = [['-----------b---', '-w------------', '-------------', '----w------b', '----w---b--', '------w-b-', '---w-----', '--b-----', '--b----', '--b---', '-----', '-bww', '---', '--', '---', '---w', '----w', '-----b', '------w', '------b-', '--w----w-', '------b---', '--w--------', '------------', '-----b------b', '--b-----------', '---------------'], ['----------b----', '-w------------', '-------------', '----w------b', '----w---b--', '------w-b-', '---w-----', '--b-----', '--b----', '--b---', '-----', '-bww', '---', '--', '---', '---w', '----w', '-----b', '------w', '------b-', '--w----w-', '------b---', '--w--------', '------------', '-----b------b', '--b-----------', '---------------'], ['---------------', '-w--------b---', '------------b', '----w-------', '----w---b--', '------w-b-', '---w-----', '--b-----', '--b----', '--b---', '-----', '-bww', '---', '--', '---', '---w', '----w', '-----b', '------w', '------b-', '--w----w-', '------b---', '--w--------', '------------', '-----b------b', '--b-----------', '---------------'], ['---------------', '-w--------b---', '-----------b-', '----w-------', '----w---b--', '------w-b-', '---w-----', '--b-----', '--b----', '--b---', '-----', '-bww', '---', '--', '---', '---w', '----w', '-----b', '------w', '------b-', '--w----w-', '------b---', '--w--------', '------------', '-----b------b', '--b-----------', '---------------'], ['---------------', '-w--------b---', '-------------', '----w----b-b', '----w------', '------w-b-', '---w-----', '--b-----', '--b----', '--b---', '-----', '-bww', '---', '--', '---', '---w', '----w', '-----b', '------w', '------b-', '--w----w-', '------b---', '--w--------', '------------', '-----b------b', '--b-----------', '---------------'], ['---------------', '-w--------b---', '-------------', '----w---b--b', '----w------', '------w-b-', '---w-----', '--b-----', '--b----', '--b---', '-----', '-bww', '---', '--', '---', '---w', '----w', '-----b', '------w', '------b-', '--w----w-', '------b---', '--w--------', '------------', '-----b------b', '--b-----------', '---------------'], ['---------------', '-w--------b---', '-------------', '----w------b', '----w---bb-', '------w---', '---w-----', '--b-----', '--b----', '--b---', '-----', '-bww', '---', '--', '---', '---w', '----w', '-----b', '------w', '------b-', '--w----w-', '------b---', '--w--------', '------------', '-----b------b', '--b-----------', '---------------'], ['---------------', '-w--------b---', '-------------', '----w------b', '----w---b--', '----b-w-b-', '---------', '--------', '--b----', '--b---', '-----', '-bww', '---', '--', '---', '---w', '----w', '-----b', '------w', '------b-', '--w----w-', '------b---', '--w--------', '------------', '-----b------b', '--b-----------', '---------------'], ['---------------', '-w--------b---', '-------------', '----w------b', '----w---b--', '------w-b-', '--bw-----', '--------', '--b----', '--b---', '-----', '-bww', '---', '--', '---', '---w', '----w', '-----b', '------w', '------b-', '--w----w-', '------b---', '--w--------', '------------', '-----b------b', '--b-----------', '---------------'], ['---------------', '-w--------b---', '-------------', '----w------b', '----w---b--', '------w-b-', '---w-----', '--bb----', '-------', '--b---', '-----', '-bww', '---', '--', '---', '---w', '----w', '-----b', '------w', '------b-', '--w----w-', '------b---', '--w--------', '------------', '-----b------b', '--b-----------', '---------------'], ['---------------', '-w--------b---', '-------------', '----w------b', '----w---b--', '------w-b-', '---w-----', '--b-----', '--bb---', '------', '-----', '-bww', '---', '--', '---', '---w', '----w', '-----b', '------w', '------b-', '--w----w-', '------b---', '--w--------', '------------', '-----b------b', '--b-----------', '---------------'], ['---------------', '-w--------b---', '-------------', '----w------b', '----w---b--', '------w-b-', '---w-----', '--b-----', '--b----', '--b---', '--b--', '--ww', '---', '--', '---', '---w', '----w', '-----b', '------w', '------b-', '--w----w-', '------b---', '--w--------', '------------', '-----b------b', '--b-----------', '---------------'], ['---------------', '-w--------b---', '-------------', '----w------b', '----w---b--', '------w-b-', '---w-----', '--b-----', '--b----', '--b---', '-b---', '--ww', '---', '--', '---', '---w', '----w', '-----b', '------w', '------b-', '--w----w-', '------b---', '--w--------', '------------', '-----b------b', '--b-----------', '---------------'], ['---------------', '-w--------b---', '-------------', '----w------b', '----w---b--', '------w-b-', '---w-----', '--b-----', '--b----', '--b---', '-----', '-bww', '---', '--', '---', '---w', '----w', '-----b', '-----bw', '--------', '--w----w-', '------b---', '--w--------', '------------', '-----b------b', '--b-----------', '---------------'], ['---------------', '-w--------b---', '-------------', '----w------b', '----w---b--', '------w-b-', '---w-----', '--b-----', '--b----', '--b---', '-----', '-bww', '---', '--', '---', '---w', '----w', '-----b', '------w', '------b-', '--w--b-w-', '----------', '--w--------', '------------', '-----b------b', '--b-----------', '---------------'], ['---------------', '-w--------b---', '-------------', '----w------b', '----w---b--', '------w-b-', '---w-----', '--b-----', '--b----', '--b---', '-----', '-bww', '---', '--', '---', '---w', '----w', '-----b', '------w', '------b-', '--w---bw-', '----------', '--w--------', '------------', '-----b------b', '--b-----------', '---------------'], ['---------------', '-w--------b---', '-------------', '----w------b', '----w---b--', '------w-b-', '---w-----', '--b-----', '--b----', '--b---', '-----', '-bww', '---', '--', '---', '---w', '----w', '-----b', '------w', '------b-', '--w----w-', '------b---', '--w--------', '----b-------', '------------b', '--b-----------', '---------------'], ['---------------', '-w--------b---', '-------------', '----w------b', '----w---b--', '------w-b-', '---w-----', '--b-----', '--b----', '--b---', '-----', '-bww', '---', '--', '---', '---w', '----w', '-----b', '------w', '------b-', '--w----w-', '------b---', '--w--------', '-----b------', '------------b', '--b-----------', '---------------'], ['---------------', '-w--------b---', '-------------', '----w------b', '----w---b--', '------w-b-', '---w-----', '--b-----', '--b----', '--b---', '-----', '-bww', '---', '--', '---', '---w', '----w', '-----b', '------w', '------b-', '--w----w-', '------b---', '--w--------', '-----------b', '-----b-------', '--b-----------', '---------------'], ['---------------', '-w--------b---', '-------------', '----w------b', '----w---b--', '------w-b-', '---w-----', '--b-----', '--b----', '--b---', '-----', '-bww', '---', '--', '---', '---w', '----w', '-----b', '------w', '------b-', '--w----w-', '------b---', '--w--------', '------------', '-b---b------b', '--------------', '---------------'], ['---------------', '-w--------b---', '-------------', '----w------b', '----w---b--', '------w-b-', '---w-----', '--b-----', '--b----', '--b---', '-----', '-bww', '---', '--', '---', '---w', '----w', '-----b', '------w', '------b-', '--w----w-', '------b---', '--w--------', '------------', '--b--b------b', '--------------', '---------------']]

print(actualRes9)


def write_data_matrix(filename, in_list):
    outfile = open(filename, "w")

    for listitem in in_list:
        outfile.write(f"{' '.join(list(map(str, listitem)))}\n")       #Works
                                          
    outfile.close()

write_data_matrix("sol9.txt",actualRes9)
write_data_matrix("ans9.txt",expectedRes9)
passed, failed = testCases(expectedRes1, actualRes1, passed, failed)
passed, failed = testCases(expectedRes2, actualRes2, passed, failed)
passed, failed = testCases(expectedRes3, actualRes3, passed, failed)
passed, failed = testCases(expectedRes4, actualRes4, passed, failed)
passed, failed = testCases(expectedRes5, actualRes5, passed, failed)
passed, failed = testCases(expectedRes6, actualRes6, passed, failed)
passed, failed = testCases(expectedRes7, actualRes7, passed, failed)
passed, failed = testCases(expectedRes8, actualRes8, passed, failed)
passed, failed = testCases(expectedRes9, actualRes9, passed, failed)
passed, failed = testCases(expectedRes10, actualRes10, passed, failed)
expectedRes9.sort()
actualRes9.sort()
print("Number of test cases passed: ", passed)
print("Number of test cases failed: ", failed)
'''