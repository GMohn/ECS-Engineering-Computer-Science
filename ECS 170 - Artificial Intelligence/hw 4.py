

"""
Copyright (C) 2022 "ECS 170 Spring 2022"
All rights reserved.
Do not distribute or open-source.
"""

import math
from collections import defaultdict
def print_board(state):
    """
    A function to print your board
    """
    output_str = "\n"
    j=1
    output_str += '--' * len(state)
    output_str += "\n"
    for i,row in enumerate(state):
        if i<=len(state)//2 and i>0: j+=1
        else: j-=1
        output_str+= ' '*j
        for c in row:
            output_str+='|'+c
        output_str+='|\n'
        output_str+='--' * len(state)
        output_str+= "\n" 
    print(output_str)
    return output_str

def movegen(state, player):
    """
    A function to get a list of next states
    """
    
    # Find locations of all pieces and store it in dictionary
    location = defaultdict(list)
    for x,row in enumerate(state):
        for y,char in enumerate(row):
            location[char].append([x,y])
    # Go through all of player's pieces to look for possible moves.
    opponent = 'b' if player=='w' else 'w'
    next_states = []
    for piece in location[player]:
        # Make a copy of current state and remove the piece at current position.
        next_state = [[c for c in row] for row in state]
        next_state[piece[0]][piece[1]] = '-'
        next_row = piece[0]+1 if player=='w' else piece[0]-1
        if next_row<len(state) and next_row>=0:
            # Figure out what the next moves are for this current piece.
            # Two different cases: Next row is longer or it is shorter.
            if len(state[next_row])>len(state[piece[0]]):
                neighbors = [x for x in [piece[1]+1,piece[1]] if x>=0 and x<len(state[next_row])]
            else:
                neighbors = [x for x in [piece[1]-1,piece[1]] if x>=0 and x<len(state[next_row])]
            # Go through possible moves for this current piece
            for n in neighbors:
                tmp = [[c for c in row] for row in next_state]
                # If there is a opponent's piece in our way, then we need to check if we can jump
                if [next_row,n] in location[opponent]:
                    diag_row = next_row+1 if player=='w' else next_row-1
                    if diag_row<len(state) and diag_row>=0:
                        # Where are we landing?
                        # Three cases: Jumping at the middle rows, jumping into longer row, jumping into shorter row
                        if len(state[piece[0]])==len(state[diag_row]):
                            diag = piece[1]+1 if n==piece[1] else n
                        elif len(state[diag_row])>len(state[next_row]):
                            diag = n+1 if n>piece[1] else piece[1]
                        else:
                            diag = n-1 if n<piece[1] else piece[1]
                        # Now we check if the landing spot is empty.
                        if [diag_row,diag] in location['-']:
                            tmp[next_row][n] = '-'
                            tmp[diag_row][diag] = player
                            next_states.append(tmp)
                # If the next move is empty, then this move is possible.
                elif [next_row,n] in location['-']:
                    tmp[next_row][n] = player
                    next_states.append(tmp)
    # Convert all next states into correct format
    return [[''.join(row) for row in next_state] for next_state in next_states]

"""
Tester (in case you want to test your code):

states = [['----', '-w-', 'bw', '-b-', '----'],
          ['w-ww', '---', 'w-', 'b--', 'b-bb'],
          ['-b---', 'wwww', 'bbb', 'w-', '---', '----', '-----'],
          ['-----', '----', '-w-', 'wb', '-b-', '----', '-----'],
          ['-----', '----', '-w-', 'bw', '-b-', '----', '-----'],
          ['-----', '----', '---', 'b-', 'www', 'bbbb', '-w---'],
          ['------', 'wwwww', 'bbbb', '---', '--', 'www', 'bbbb', '-----', '------'],
          ['--b----', '---w--', '--w--', '-b--', 'ww-', 'bw', '-b-', '----', '-----', '------', '-w-----'],
          ['---------------', '-w--------b---', '-------------', '----w------b', '----w---b--', '------w-b-', '---w-----', '--b-----', '--b----', '--b---', '-----', '-bww', '---', '--', '---', '---w', '----w', '-----b', '------w', '------b-', '--w----w-', '------b---', '--w--------', '------------', '-----b------b', '--b-----------', '---------------']
          ]

def test(movegen, state):
    error = ""
    for player in ['w','b']:
        for s in movegen(state,player):
            if s not in solution(state,player):
                error+="\nFor state:"+str(state)
                error+="\nMade impossible state: "+ str(s)
        for s in solution(state,player):
            if s not in movegen(state,player):
                error+="\nFor state:"+str(state)
                error+="\nMissing possible state: "+ str(s)
    return error

from oska import movegen as my_movegen #import your file

for state in states:
    print(test(my_movegen, state))
    print()
"""

"""
This function really just drives the minimax algorithm and simply changes the bool based on turnPiece
"""
def oskaplayer(board,turnPiece, depth):
    if turnPiece == 'w':
        # [1] of minimax is the board and [0] is the evaluation number
        return minimax(board,True,depth)[1]
    else:
        return minimax(board,False,depth)[1]

"""
staticEval returns an integer value of game state
Keeps track of number of pieces,
number of pieces at the end, 
gives a score based on number of pieces and a bonus if at end
checks if all pieces are at the end, then eval inf or -inf based on piece type
"""
def staticEval(board):
    numWhite = 0
    numEndWhite = 0
    scoreWhite = 0
    scoreBlack = 0
    numBlack = 0
    numEndBlack = 0
    numRows = len(board)
    #iterate through the board
    for y in range(numRows):
        numCols = len(board[y])
        for x in range(numCols):
            # give point for white piece
            if board[y][x] == 'w':
                scoreWhite += 1
                numWhite += 1
                # give bonus if at end and count number of end pieces
                if y == numRows-1:
                    scoreWhite += .5
                    numEndWhite += 1
            # give point for the black piece
            elif board[y][x] == 'b':
                scoreBlack += 1
                numBlack += 1
                # bonus point if at the end and keep track of pieces at the end        
                if y == 0:
                    scoreBlack += .5
                    numEndBlack += 1

    #all pieces are at the end therefore has won
    if numWhite == numEndWhite:
        scoreWhite = 1e500
    if numBlack == numEndBlack:
        scoreBlack = -1e500
    # one player has no more pieces, then other has won
    if scoreWhite == 0:
        scoreBlack = -1e500
    if scoreBlack == 0:
        scoreWhite = 1e500
    # if draw return 0 inf-inf = nan
    if (math.isnan(scoreWhite+scoreBlack)):
        return 0
    return (scoreWhite - scoreBlack)

"""
this function checks if a player has won based on the current evaluation of the board
"""
def checkWinner(board):
    if abs(staticEval(board)) == abs(1e500):
        return True
    return False

"""
This function is the recursive minimax algorithm
the depth is decremented by one and turn is changed until
return back up the evaluations when: depth is reached, winner is found, or no move is available
 """
def minimax(board, maxPlayer, depth):
    # check if at depth or if it is a winner then return current evaluation and board
    if depth == 0 or checkWinner(board):
        #print(staticEval(board), board)
        return staticEval(board), board
    #evaluate for white
    if maxPlayer:
        piece = 'w'
        maxEval = -1e500
        bestMove = None
        possibleMoves = movegen(board,piece)
        #if no possible moves for player then skip their move and return same state
        if not possibleMoves:
            return staticEval(board),board
        #now evaluating for white
        for move in possibleMoves:
            #only return maxEval for recursive call
            evaluation = minimax(move, False, depth-1)[0]
            maxEval = max(maxEval,evaluation)
            if maxEval == evaluation:
                bestMove = move

        return maxEval, bestMove
    #everything is the same in the else statement as the if
    else:
        piece = 'b'
        minEval = 1e500
        bestMove = None
        possibleMoves = movegen(board,piece)
        #check for possible moves if none, return board
        if not possibleMoves:
            return staticEval(board),board
            maxEval = -1e500
            for move in possibleMoves:
                #only return maxEval for recursive call
                evaluation = minimax(move, False, depth-1)[0]
                maxEval = max(maxEval,evaluation)
                if maxEval == evaluation:
                    bestMove = move
            return maxEval, bestMove
        #recursive call for black
        for move in possibleMoves:
            #pass board,change turn, decrement depth get staticEval
            evaluation = minimax(move, True, depth-1)[0]
            # get min oof two values
            minEval = min(minEval,evaluation)
            #update best move based on eval
            if minEval == evaluation:
                bestMove = move

        return minEval, bestMove
        
#print(oskaplayer(['w---','bbb','--','b--','-w--'],'w',5))