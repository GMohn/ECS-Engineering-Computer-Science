#This program finds the best solution for the game Rush Hour by ThinkFun
'''
I struggled a lot just trying to get the correct states. I am not sure why, but my mind has been very jumbled these past two weeks.
I hope to see you in office hours soon. 
'''

# Take in game_state array to print and return true if solved
from cmath import inf
from queue import PriorityQueue
from collections import deque
import re
visited_nodes = []

def print_board(game_state):
    for i in game_state:
        print(i)
    #check to see if X car is at the end of board
    row_xcar = game_state[2]
    if (row_xcar[-2:] == "XX"):
        return True
    else:
        return False
#remove nested lists
def formatting(some_list):
    return [val for sublist in some_list for val in sublist]
#count number of blocking pieces minus the open spaces in front car X this implies distance from goal
def get_heuristic(game_state):
    pos_carX = game_state[2].index("X")
    goal_row = game_state[2]
    h_val = 0
    block_count = 0
    for i in range(pos_carX+2,len(goal_row)):
        if goal_row[i].isalpha():
            h_val += 1

    #print("blocking pieces: ",block_count)
    return h_val

def move_right(row_piece,len_sub,index):

    Rfirst = row_piece[0][0 : index] 
    Rsecond = row_piece[0][index+len_sub : ]
    Rthird = row_piece[0][index:index+len_sub]
    return Rfirst+Rsecond+Rthird

def move_left(row_piece,len_sub,index):
    Lfirst = row_piece[0][0 : index-1] 
    Lsecond = row_piece[0][index:index+len_sub]
    Lthird = row_piece[0][index-1:index]
    return Lfirst+Lsecond+Lthird+Lthird

#get the column to move, shift it, and rebuild the game state
'''  def move_up(col_board,temp_state,vert_piece,col):
    shift_board = deque(col_board)
    #print("col:", col_board)
    
    shift_board.rotate(-1)
    new_move = []
    #print(temp_state[0])
    for i in range(len(temp_state)):
        temp_state[i] = temp_state[i][:col]+shift_board[i]+temp_state[i][col+1:]
        new_move.append(temp_state[i])
    #print("new move up:",new_move)
    return new_move

def move_down(col_board,temp_state,vert_piece,col):
    shift_board = deque(col_board)
    #print("col:", col_board)
    
    shift_board.rotate(1)
    new_move = []
    #print(temp_state[0])
    for i in range(len(temp_state)):
        temp_state[i] = temp_state[i][:col]+shift_board[i]+temp_state[i][col+1:]
        new_move.append(temp_state[i])
    #print("new move down:",new_move)
    return new_move

'''  


def move_horizontal(game_state, horizontal_piece):
    move_counter = 0
    temp_game_state = game_state[:]
    new_moves = []

    while horizontal_piece:
        move_piece = horizontal_piece.pop(0)
        row_piece = [string for string in game_state if move_piece in string]
        row_idx = [idx for idx, s in enumerate(temp_game_state) if move_piece in s][0]
        index_piece = row_piece[0].index(move_piece)
        
        len_row = len(row_piece)
        len_piece = len(move_piece)
        #car is against the left edge, check right
        if (index_piece == 0):
            if (row_piece[index_piece+len_piece:] == "-"):
                temp_game_state[row_idx] = move_right(row_piece,len_piece,index_piece)
                new_moves.append(temp_game_state)
                temp_game_state = game_state[:]
       
        #index is against the right  check left
        elif (index_piece+len_piece - 1 >= 5):
            if (row_piece[0][index_piece-1] == "-"):
                temp_game_state[row_idx] = move_left(row_piece,len_piece,index_piece)
                new_moves.append(temp_game_state)
                temp_game_state = game_state[:]
                #print("game_state: \n",game_state)

        #not against edge, check both left and right
        else:
            if (row_piece[0][index_piece-1] == "-"):
                temp_game_state[row_idx] = move_left(row_piece,len_piece,index_piece)
                new_moves.append(temp_game_state)
                temp_game_state = game_state[:] 

            if (row_piece[0][index_piece+len_piece] == "-"):
                temp_game_state[row_idx] = move_right(row_piece,len_piece,index_piece)
                new_moves.append(temp_game_state)
                temp_game_state = game_state[:]
    
    return new_moves
'''  #this function expands vertical moves
def move_vert(game_state, vertical_piece,row,col):
    temp_game_state = game_state[:]
    col_piece = []
    new_moves = []
    for i in range(len(game_state)):
        col_piece.append(game_state[i][col])
        
    
        
    while vertical_piece:
        move_piece = vertical_piece.pop(0)
        move_piece_len = len(move_piece)
        
        #if at the top of board, only try move down
        if (row == 0) :
            if game_state[move_piece_len][col] == "-":
                new_moves.append(move_down(col_piece,temp_game_state,move_piece,col))
               
        #if at bottom of board, only try move up
        if ((row+move_piece_len-1) == 5) :
            if game_state[row-1][col] == "-":
                new_moves.append(move_up(col_piece,temp_game_state,move_piece,col))
        
        else:
            if (row == 0):
                continue
            #row above car is empty try move up
            elif game_state[row-1][col] == "-":
                new_moves.append(move_up(col_piece,temp_game_state,move_piece,col))
    
            #row below car is empty try move down
            elif game_state[row-1+move_piece_len][col] == "-":
                new_moves.append(move_down(col_piece,temp_game_state,move_piece,col))
                
        return new_moves
#this function classifies the vertical pieces as trucks or cars based on length in order to call a move action
def get_vert(game_state):
    vertical_car = []
    vertical_truck = []
    vertical_moves = []
    #nested loop to keep track of row,col
    for i in range(len(game_state)):
        for j in range(len(game_state[i])-1):
            #check if piece
            if game_state[i][j].isalpha():
                #check top of row only search down
                if (i == 0) and game_state[i][j] == game_state[i+1][j]:
                    #check if 3 align
                    if (game_state[i+2][j] ==  game_state[i][j]):
                        if (game_state[i][j]*3 not in vertical_truck):
                            vertical_truck.append(game_state[i][j]*3)
                            vertical_moves.append(move_vert(game_state,vertical_truck,i,j))
                            #print("i: ",i,"j: ",j,"@ truck append")
                    #only 2 therefore car
                    else:
                        if (game_state[i][j]*2 not in vertical_car):
                            vertical_car.append(game_state[i][j]*2)
                            vertical_moves.append(move_vert(game_state,vertical_car,i,j))
                            #print("i: ",i,"j: ",j,"@ car append")
                #check bottom of board
                elif (i == 5) and game_state[i][j] == game_state[i-1][j]:
                    #check if 3 align
                    if (game_state[i-2][j] == game_state[i][j]):
                        if (game_state[i][j]*3 not in vertical_truck):
                            vertical_truck.append(game_state[i][j]*3)
                            vertical_moves.append(move_vert(game_state,vertical_truck,i,j))
                            #print("i: ",i,"j: ",j,"@ truck append2")
                    else: 
                        if (game_state[i][j]*2 not in vertical_truck):
                            vertical_car.append(game_state[i][j]*2)
                            vertical_moves.append(move_vert(game_state,vertical_car,i,j))
                            #print("i: ",i,"j: ",j,"@ car append2")
                #not at the bottom or top of the board
                



            #check if at bottom of board
            if ((i != 5) and (game_state[i][j].isalpha() == True) and (game_state[i+1][j] == game_state[i][j])):
                if((i-1 > 0) and (game_state[i][j] == game_state[i-1][j])):
                    vertical_truck.append(game_state[i][j]*3)
                    
                else:
                    
                    )

    #print("truck:",vertical_truck)
    #print("car: ",vertical_car)
    #remove None
    new_move = [i for i in vertical_moves if i is not None]
    

    
        
    
        

    return formatting(new_move)
'''  

def move_vert(col_piece, vert_piece):
    piece_len = len(vert_piece[0])
    str_col = []
    new_move = []
    temp_arr = col_piece[:]
    while vert_piece:
        vert_index = [index for index, s in enumerate(col_piece) if vert_piece[0] in s][0]
        print(vert_index)
        
        #find first instance of vert_piece and check if empty space
        # find last vert_piece and check if empty
        str_col = col_piece[vert_index]
        index_piece = str_col.index(vert_piece[0])
        
        for i in range(len(str_col)):
            if (i+piece_len > 5):
                continue
            elif(i-1 < 0):
                continue
            #check right and create move if empty space
            if (str_col[i+piece_len-1] == "-"):
                Rfirst = "-"
                Rsecond = str_col[index_piece:piece_len ]
                Rthird = str_col[index_piece+piece_len+1:]
                new_move.append(Rfirst+Rsecond+Rthird)
            if(str_col[i-1] == "-"):
                Lfirst = str_col[:index_piece-1] 
                Lsecond = str_col[index_piece:index_piece+piece_len]
                Lthird = str_col[index_piece+piece_len:]+"-"
                new_move.append(Lfirst+Lsecond+Lthird)
    temp_arr[index_piece] = new_move
    return new_move   


def get_vert(game_state):
    col_piece = []
    tempstr =""
    vert_piece =[]
    row_len = len(game_state)
    vert_index = 0
    vert_moves=[]
    #create transposed array of game_state
    for i in range(row_len):
        curr_count = 1
        vert_piece_index = 0
        for j in range(len(game_state[i])):
            tempstr+=(game_state[j][i])
        col_piece.append(tempstr)
        #find all repeating characters
        found_repeat = re.findall(r'((\w)\2{1,})', tempstr)
        if (found_repeat):
            vert_piece.append(found_repeat[0][0])
            found_repeat.pop(0)
        tempstr =""
        print("column piece: ",col_piece)
        print("vert piece: ", vert_piece)
    vert_moves = move_vert(col_piece,vert_piece) #+ move_up(col_piece,vert_piece)
    return vert_moves

    '''
    piece_len = len(vert_piece[0])
    vert_index = [index for index, s in enumerate(col_piece) if vert_piece[0] in s][0]
    print(vert_index)  

    for k in range(i+1,row_len):
            if(col_piece[i][vert_piece_index] == col_piece[i][k])and (col_piece[i][k].isalpha()):
                curr_count += 1
            else:
                break
            if (curr_count > 2):
                vert_piece_index +=1
        if (curr_count > 1):
            print(col_piece[i][vert_piece_index])
        vert_piece_index +=1

    shift_board = deque(col_board)
    #print("col:", col_board)
    
    shift_board.rotate(1)
    new_move = []
    #print(temp_state[0])
    for i in range(len(temp_state)):
        temp_state[i] = temp_state[i][:col]+shift_board[i]+temp_state[i][col+1:]
        new_move.append(temp_state[i])
    #print("new move down:",new_move)'''
    #return new_move
# this function takes in the current game state and expands that node by creating new moves.
# calls get_heuristic in order to populate the frontier with correct priority.
#returns a list of available moves
def get_moves(game_state):
    #classify each game piece
    horizontal_car = []
    horizontal_truck = []
    
    #print_board(game_state)
    new_states = []
    k = 0
    #iterate through each row
    #this needs to be redone.
    for i in game_state:
        #keep track of adjacent piece to tell if it is a horizontal car
        prev_piece = ""
        prev_col = ""
        #for each char in row
        for j in i:
            horz_count = 1
            #if char is not empty then there is a car
            if (j!= "-"):
                #if the previous piece is the same then append to horizontal car list if it dne
                if (prev_piece == j) and (j not in horizontal_car):
                    horizontal_car.append(j*2)
                    #keep track of length of car
                    horz_count += 1
                    if ((horz_count > 2) and (j not in horizontal_truck)):
                        horizontal_truck.append(j*3)
                        horizontal_car.remove(j*2)
                                              
                    #move_horizontal(initial_state,horizontal_car,row_count,col_count)
                     
                #assign prev_piece
                prev_piece = j
                        
            else:
                prev_piece = j
        #row count
        k += 1
    tempvert_state = get_vert(game_state)
    temphorz_state = (move_horizontal(game_state,horizontal_car)) + (move_horizontal(game_state,horizontal_truck))

    for i in range(len(tempvert_state)):
        new_states.append(tempvert_state)
    for i in range(len(temphorz_state)):
        new_states.append(temphorz_state)
    #print("new_states after vert and horz moveset: ",new_states)
    #remove None values
    return new_states

    #print ("horizontal cars: ", horizontal_car)
    #print ("horizontal trucks: ", horizontal_truck)
# main function that creates a frontier and calls for next states as well as assigning heuristic
def rush_hour(h, initial_state):
    curr_state = initial_state[:]
    frontier = PriorityQueue()
    frontier.put(curr_state,h)
    total_moves = 1
    states_explored = 1
    new_move = []

    vert_count = 0
    horz_count = 0
    row_count = 0
    
    
    

    while frontier:
        next_state = frontier.get()
        print("Current Working State: ")
        print_board(next_state)
        #last 2 chars of goal row to check if finished
        last_two_goal = next_state[0][2][len(next_state[0][2])-2:]
        if last_two_goal == "XX":
            print("total  moves: ",total_moves,"\n","Total states explored: ",states_explored)
            break
        else:
            temp_move = get_moves(next_state)
            #return a list of next moves
            if (temp_move not in visited_nodes):
                visited_nodes.append(temp_move) 
                new_move = formatting(temp_move)
            #print(new_move)
            #new_heuristics = get_heuristic(new_move)

            for i in range(len(new_move)):

                states_explored +=1
                frontier.put(new_move[i],get_heuristic(new_move[i]))   
        total_moves += 1       
            
    # iterate through board and count pieces


    
    
    if (print_board(curr_state) == True):
        print("total  moves: ",total_moves,"\n","Total states explored: ",states_explored)
    

def driver():
    initial_state = ["------","--B---","XXB---","--BAA-","------","------"]

    blocking_hurestic = 0
    rush_hour(blocking_hurestic, initial_state)
driver()