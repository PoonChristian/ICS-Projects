# Christian Poon 79555434

class Othello:
    def __init__(self):
        '''
        Initializes a new customized Othello game by asking for the number of rows
        and columns on the board, the player that starts the game first,
        and the winning condition of the game. Once all of these conditions are met,
        a board will be printed for the user to see.
        '''
        
        self._row = self.get_row()
        self._column = self.get_column()
        self._turn = self.first_turn()
        self._board = self.make_board()
        self._winning_condition = self.winning_condition()
        self._print_board = self.print_board(self._board)



        
    def get_row(self) -> int:
        '''
        Asks for a user input on the number of rows on the board.
        The number of rows must be even and between 4 and 16.
        '''
        
        while True:
            try:
                rows = int(input('Enter an even number between 4 and 16 for the rows: '))

                if rows >= 4 and rows <= 16 and rows % 2 == 0:
                    break
                
            except:
                print('Invalid number.')
                print()
            else:
                if rows < 4 or rows > 16:
                    print('Row number is not between 4 and 16')
                    print()
                elif rows % 2 != 0:
                    print('The row number is not even.')
                    print()

        return rows



    
    def get_column(self) -> int:
        '''
        Asks for a user input on the number of columns on the board.
        The number of rows must be even and between 4 and 16.
        '''

        while True:
            try:
                columns = int(input('Enter an even number between 4 and 16 for the columns: '))

                if columns >= 4 and columns <= 16 and columns % 2 == 0:
                    break
                
            except:
                print('Invalid number.')
                print()
            else:
                if columns < 4 or columns > 16:
                    print('Column number is not between 4 and 16')
                    print()
                elif columns % 2 != 0:
                    print('The column number is not even.')
                    print()

        return columns



    
    def make_board(self) -> [list]:
        '''
        Makes the board for the Othello game based on the number of rows and columns
        inputted and places the four starting pieces in the center of the board based
        on what piece the user wants on the top left center position.
        '''
        
        board = []
        
        for row in range(self._row):
            board.append(['-']*self._column)

        while True:
            top_left_choice = input('What color on the top left center position? W or B ').upper()
            if top_left_choice == 'W':
                board[int(self._row / 2)][int(self._column / 2)] = 'W'
                board[int(self._row / 2)][int(self._column / 2) - 1] = 'B'
                board[int(self._row / 2) - 1][int(self._column / 2)] = 'B'
                board[int(self._row / 2) - 1][int(self._column / 2) - 1] = 'W'
                break
            elif top_left_choice == 'B':
                board[int(self._row / 2)][int(self._column / 2)] = 'B'
                board[int(self._row / 2)][int(self._column / 2) - 1] = 'W'
                board[int(self._row / 2) - 1][int(self._column / 2)] = 'W'
                board[int(self._row / 2) - 1][int(self._column / 2) - 1] = 'B'
                break
            else:
                print('Invalid color')

        return board




    def score(self) -> list:
        '''
        Calculates the score of the Othello game between the White player
        and Black player and stores both scores in a list.
        '''
        white_score = 0
        black_score = 0
        for row in self._board:
            for col in row:
                if col == 'W':
                    white_score += 1
                elif col == 'B':
                    black_score += 1

        return [white_score, black_score]



    
    def winning_condition(self):
        '''
        Determines the winning condition of the Othello game. A player can
        either win by having the fewest tiles or most tiles.
        '''
        
        while True:
            how_to_win = input('What does it mean to win? (Fewest/Most) ').upper()

            if how_to_win != 'FEWEST' and how_to_win != 'MOST':
                print('Not a valid meaning of determining the winner')
            else:
                break

        return how_to_win



    
    def print_board(self, board: [list]) -> None:
        '''
        Prints out a visual display of the board for the customized Othello game.
        '''
        
        [white, black] = self.score()
        
        print('White: {}, Black: {}'.format(white, black))
        for i in range(self._column):
            print('{:2}'.format(i + 1), end = '  ')
        print()
        for row in range(len(board)):
            for col in range(len(board[0])):
                print(' {:2}'.format(board[row][col]), end = ' ')
            print(row + 1)



            
    def first_turn(self) -> str:
        '''
        Determines the first player's turn through a user input, either White or Black.
        '''
        
        while True:
            first_player = input('Who starts first? W or B? ').upper()
            if first_player == 'B':
                return 'B'
            elif first_player == 'W':
                return 'W'
            else:
                print('Invalid player')



                
    def switch_turn(self, turn: str) -> str:
        '''
        Switches the player turn after a move has been made.
        '''
        
        if turn == 'W':
            return 'B'
        else:
            return 'W'



        
    def make_move(self, row: int, column: int, turn: str) -> None:
        '''
        Makes a player move for the Othello game by taking the row, column, and turn;
        and updates the board with the new move.
        '''
        
        self._board[row - 1][column - 1] = turn



        
    def flip_piece(self, row: int, column: int, turn: str) -> None:
        '''
        Flips the color of the given piece (turn) in the designated row and column.  
        '''
        
        self._board[row - 1][column - 1] = self.switch_turn(turn)



        
    def on_board(self, row: int, column: int) -> bool:
        '''
        Checks the board to make sure the inputted row number and column number are within the board.
        '''
        
        if row >= 0 and row < self._row and column >= 0 and column < self._column:
            return True
        else:
            return False



        
    def is_valid_move(self, row: int, column: int, turn: str) -> list:
        '''
        Checks all eight directions from where the piece was placed to validate the move.
        If a move is valid, the function will return a list of the coordinates of all the
        pieces that could be flipped. If a move is invalid, the function will return an empty list.
        '''
        
        row -= 1
        column -= 1
        pieces_to_flip = []
        
        while True:
            if self._board[row][column] != '-' or not self.on_board(row, column):
                break
            
            if turn == 'W':
                opposite = 'B'
            else:
                opposite = 'W'
            
            for vert, hori in [[0, 1], [0, -1], [1, 1], [1, -1], [1, 0], [-1, -1], [-1, 0], [-1, 1]]:
                x, y = row, column
                x += vert
                y += hori
                if not self.on_board(x,y):
                    continue
                else:
                    if self.on_board(x, y) and self._board[x][y] == opposite:
                        while self._board[x][y] == opposite:
                            x += vert
                            y += hori
                            if not self.on_board(x, y):
                                break
                        if not self.on_board(x, y):
                            continue
                        if self._board[x][y] == turn:
                            while True:
                                x -= vert
                                y -= hori
                                if x == row and y == column:
                                    break
                                pieces_to_flip.append([x, y])
            break

        if len(pieces_to_flip) == 0:
            return pieces_to_flip
        else:
            return pieces_to_flip



        
    def flip_all(self, row, column, turn, pieces_to_flip: list):
        '''
        Takes the list of all the coordinates of the pieces to flip
        from the is_valid_move function and flips each piece respectively.
        '''
        
        self._board[row - 1][column - 1] = turn
        self._turn = self.switch_turn(turn)
        for coordinate in pieces_to_flip:
            self._board[coordinate[0]][coordinate[1]] = self.switch_turn(self._turn)



            
    def show_flipped_pieces(self, turn: str) -> list:
        '''
        Determines when a game ends by returning a list of all the possible pieces
        that can be flipped. If the list is empty, the game ends because no valid
        moves can be made if no pieces can be flipped.
        '''
        
        flipped_pieces = []
        for row in range(1, self._row + 1):
            for col in range(1, self._column + 1):
                if len(self.is_valid_move(row, col, turn)) != 0:
                    flipped_pieces.append(self.is_valid_move(row, col, turn))
                    
        return flipped_pieces




    def winner(self) -> str:
        '''
        Considers the winning condition and returns the winner of the Othello game
        based on that winning condition.
        '''

        [white, black] = self.score()
        
        while True:
            if self._winning_condition == "MOST":
                if white > black:
                    return 'Winner is White!'
                elif black > white:
                    return 'Winner is Black!'
                else:
                    return 'It is a draw!'
            elif self._winning_condition == "FEWEST":
                if white < black:
                    return 'Winner is White!'
                elif black < white:
                    return 'Winner is Black!'
                else:
                    return 'It is a draw!'











