## prog67.py - miniChess
## Nhi Vo
## December 8, 2017



def move_maker(board,color):
    """ Expects a list os lists representing the current board and the color of the current player.
The functions returns a list of possible new boards that can result in a new board. """
    if color == 1:
        moves= white(board)
    elif color == 2:
        moves = black(board)                                   
    return(moves)

def move_chooser(list_of_boards, color):
    """ Expects a list of possible next moves returned by move_maker function and evaluates
the different options and determines the best board and chooses that board as the main board. """
    if color == 1:
        board = bestboard_w(list_of_boards)
    if color == 2:
        board = bestboard_b(list_of_boards)
    return board

def black(board):
    """ If the number inputed into movemaker is 2, this function runs and creates the
possible scenerios for the black pawns. """
    import copy
    new = []
    for i in range(len(board)):
        for j in range(len(board[0])):
            board2=copy.deepcopy(board)
            board3=copy.deepcopy(board)
            board4=copy.deepcopy(board)
            if board[i][j]==2:  ## If the pawn on the board is black
                try:
                    if i>0:   ## Only applies when the black pawn is not on the first row
                        if board[i-1][j]==0: ## If the empty space in front of the black is 0
                           board2[i][j]=0  
                           board2[i-1][j]=2  ## black pawn moves ahead to empty space
                           new.append(board2)
                except:
                    pass
                try:
                    if j<len(board[0]) and i>0:  ## Makes sure the positions does not go out of bound
                        if board[i-1][j+1]==1:  ## If right diagonal of black is white
                            board3[i][j]=0
                            board3[i-1][j+1]=2  ## black pawn moves to the right diagonal space
                            new.append(board3)
                except:
                    pass
                try:
                    if j>0 and i>0:  ## Makes sure the positions does not go out of bound
                        if board[i-1][j-1]==1:  ## If the left diagonal of black is white
                            board4[i][j]=0
                            board4[i-1][j-1]=2  ## black pawn moves to the left diagonal space
                            new.append(board4)
                except:
                    pass
    return new


def white(board):
    """ If the number inputed into movemaker is 1, this function runs and creates the
possible scenerios for the white pawns. """
    import copy
    new=[]
    for i in range(len(board)):
        for j in range(len(board[0])):
            board2=copy.deepcopy(board)
            board3=copy.deepcopy(board)
            board4=copy.deepcopy(board)
            if board[i][j]==1:  ## If the pawn on the board is white
                try:
                    if i <len(board):  ## Makes sure the positions does not go out of bound
                        if board[i+1][j]==0:  ## If the empty space in front of the white is 0
                            board2[i][j]=0
                            board2[i+1][j]=1  ## white pawn moves ahead to empty space
                            new.append(board2)
                except:
                    pass
                try:
                    if j>0 and i <len(board):  ## Makes sure the positions does not go out of bound
                        if board[i+1][j-1]==2:  ## If the left diagonal of white is black
                                board3[i][j]=0
                                board3[i+1][j-1]=1 ## white pawn moves to the left diagonal space
                                new.append(board3)
                except:
                    pass
                try:
                    if j<len(board[0]) and i <len(board):  ## Makes sure the positions does not go out of bound
                        if board[i+1][j+1]==2:   ## If the right diagonal of white is black
                                board4[i][j]=0
                                board4[i+1][j+1]=1  ## white pawn moves to the right diagonal space
                                new.append(board4)
                except:
                    pass
    return new


def bestboard_b(choices):
    """ If the number inputed into move_choose is 2, it evaluates the board and
chooses the best board at the black pawn's advantage. My function ultimately chooses the board with the least
number of white pawns. """
    least_w=0
    chosenboard=choices[0]
    for board in choices:
        if board == choices[0]:  ## Count number of white pawns in the first board
            count = 0
            for sublist in range(len(board)):
                for num in range(len(board[0])):
                    if board[sublist][num]==1:
                        count = count + 1  
                        least_w=count
        else:   ## Count the number of white pawns in the boards that follow the first one and determine the board with the least white pawns
            count = 0
            for sublist in range(len(board)):
                for num in range(len(board[0])):
                    if board[sublist][num]==1:
                        count = count + 1
            if count<least_w: ## If the current board has fewer white pawns than the previous boards, the current board is chosen as the main boaard.
                least_w=count  
                chosenboard=board
                            
    return chosenboard

def bestboard_w(choices):
    """ If the number inputed into move_choose is 1, it evaluates the board and
chooses the best board at the white pawn's advantage. My function ultimately chooses the board with the least
number of black pawns. """
    least_w=0
    chosenboard=choices[0]
    for board in choices:
        if board == choices[0]:  ## Count number of white pawns in the first board
            count = 0
            for sublist in range(len(board)):
                for num in range(len(board[0])):
                    if board[sublist][num]==2:
                        count = count + 1
                        least_w=count
        else:  ## Count the number of black pawns in the boards that follow the first one and determine the board with the least black pawns
            count = 0
            for sublist in range(len(board)):
                for num in range(len(board[0])):
                    if board[sublist][num]==2:
                        count = count + 1
            if count<least_w:  ## If the current board has fewer black pawns than the previous boards, the current board is chosen as the main boaard.
                least_w=count
                chosenboard=board
                            
    return chosenboard
    
