# Christian Poon 79555434

import othello_game_logic

def user_interface():
    '''
    Implements a user-friendly interface to play the game of Othello.
    It asks the user for particular conditions so they can play the game
    to their liking.
    '''
    game = othello_game_logic.Othello()

    print(game._turn + ' will go first.')

    while True:
        try:
            row = int(input('Which row would you like to place your piece? '))
            column = int(input('Which column would you like to place your piece? '))
            
            if game._board[row - 1][column - 1] == '-' and len(game.is_valid_move(row, column, game._turn)) != 0:
                game.flip_all(row, column, game._turn, game.is_valid_move(row, column, game._turn))
                game.print_board(game._board)               
            elif game._board[row - 1][column - 1] != '-' or len(game.is_valid_move(row, column, game._turn)) == 0:
                print('Error: Invalid Move')
            
            if len(game.show_flipped_pieces(game._turn)) == 0:
                break
            
            print('It is ' + game._turn + '\'s turn.')
           
        except:
            print('Error: Invalid move')
            print('It is ' + game._turn + '\'s turn.')

    print(game.winner())




    
if __name__ == '__main__':
    user_interface()







    
