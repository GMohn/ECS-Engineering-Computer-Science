def printBoard(n):
    numRows = (2*n)-3
    board = [["-"]*(n-i) for i in range(numRows) if (n-i)>=2]

    print(board)

#printBoard(5)
#[www,--,]

def movegen(boardState,pieceTurn):
    print(boardState)
    tempBoard = boardState[:]
    tempRow = ""
    numRows = len(boardState)
    for y in range(numRows):
        numCols = len(boardState[y])
        for x in range(numCols):
            if boardState[y][x] == pieceTurn:
                if ((pieceTurn == "w") and (y == numRows-1)):
                    print("game is over white wins")
                    break
                elif ((pieceTurn == "b") and (y == 0)):
                    print("game is over black wins")
                    break
                #first index of row is most left
                elif (x == 0):
                    print("piece at left end")
                    if (boardState[y+1][x] != pieceTurn):
                        print("the square at: ",y+1,",",x,"is not the same as moving piece")
                        tempRow = tempBoard[y].replace(pieceTurn,"-",1)
                        print(tempRow)

                elif(x == numCols-1):
                    print("w at right end")
                else:
                    print("w can go left or right")
            else:
                continue


movegen(['www','--','bbb'],'w')
'''def oskaplayer(boardState,pieceTurn,maxDepth):
    
oskaplayer(['www','--','bbb'],'w',2)'''