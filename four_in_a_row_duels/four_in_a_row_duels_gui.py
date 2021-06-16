"""
  connectFour game using the duels package

 * ECN Project (2020/2021 - Semester II)
 * Oluwapelumi WILLIAMS (IMARO II)
 * Adedamola SODE (IMARO I)
 *
 * Supervisor : Professor Olivier Kermogant
 *
 *
 * GUI File of the four_in_a_row game 
 * File Name: "four_in_a_row_gui.py"
"""

#!/usr/bin/env python
import sys
sys.path.insert(1, sys.argv[1])
from duels import Subscriber
game = Subscriber(20000)
init_msg = game.get_init()

# init_msg.name1
# init_msg.name2
# init_msg.<other fields>

# add other imports here /(e.g. pygame)
import pygame
import time

# Define constants for the rows and columns sent from the C++
ROWS = init_msg.rows
COLUMNS = init_msg.columns

# Define Colors for the players
WHITE = (255, 255, 255) # Background color for the grid
BLACK = (0, 0, 0) # Background color for the entire window
RED = (255, 0, 0)
BLUE = (0, 0, 255)

BACKGROUND_COLOR = (253, 254, 254)
GRID_CONTAINER_COLOR = (229, 232, 232)
CELL_COLOR = (247, 249, 249)
TOKEN_1_COLOR = (203, 67, 53)
TOKEN_2_COLOR = (52, 152, 219)

# Define constants for the screen width and height
SIDE_SIZE = 800
WINDOW_WIDTH = SIDE_SIZE
WINDOW_HEIGHT = SIDE_SIZE

MARGIN = SIDE_SIZE//80 # pixels
GRID_SCALE_FACTOR = 0.75


# prepare initial state / display

# Define the container which holds the grid and cells (where the token squares are housed)
class Container(pygame.sprite.Sprite):
    def __init__(self, width, height, color):

        super(Container, self).__init__()
        self.width = width
        self.height = height
        self.color = color
        
        self.coordinates = (0,0)
        
        self.surf = pygame.Surface((self.width, self.height))
        self.surf.fill(self.color)
        self.rect = self.surf.get_rect()


# Define the cell which houses the tokens
class Cell(pygame.sprite.Sprite):
    def __init__(self, row, column, width, height, color):
        super(Cell, self).__init__()
        self.row = row
        self.column = column
        self.width = width
        self.height = height

        self.coordinates = (0,0)

        self.surf = pygame.Surface((int(self.width), int(self.height)))
        self.surf.fill(color)
        self.rect = self.surf.get_rect()

# Define a token, which indicates which player has played, and where
class Token(pygame.sprite.Sprite):
    def __init__(self, row, column, player):
        super(Token, self).__init__
        self.row = row
        self.column = column
        if player == 0:
            self.color = TOKEN_1_COLOR
        elif player == 1:
            self.color = TOKEN_2_COLOR


def initBoardDisplay():
    block_1 = Container(int(WINDOW_WIDTH - MARGIN * 2), int(WINDOW_HEIGHT * GRID_SCALE_FACTOR - MARGIN), GRID_CONTAINER_COLOR)
    block_1.coordinates = (MARGIN, int(WINDOW_HEIGHT - WINDOW_HEIGHT * GRID_SCALE_FACTOR))

    block_2 = Container(int(block_1.width-2*MARGIN), int(block_1.height-2*MARGIN), BACKGROUND_COLOR)
    block_2.coordinates = (block_1.coordinates[0]+MARGIN, block_1.coordinates[1]+MARGIN)

    title_block = Container(int(WINDOW_WIDTH - MARGIN * 2), int(WINDOW_HEIGHT * (1 - GRID_SCALE_FACTOR) - 2 * MARGIN), WHITE)
    title_block.coordinates = (MARGIN, MARGIN)

    player_1_title_block = Container(title_block.width//4, title_block.height, BACKGROUND_COLOR)
    player_1_title_block.coordinates = (title_block.coordinates[0], title_block.coordinates[1])

    player_2_title_block = Container(title_block.width//4, title_block.height, BACKGROUND_COLOR)
    player_2_title_block.coordinates = (title_block.coordinates[0]+title_block.width-player_2_title_block.width, title_block.coordinates[1])

    center_title_block = Container(title_block.width//2, title_block.height, BACKGROUND_COLOR)
    center_title_block.coordinates = (title_block.coordinates[0]+player_1_title_block.width, title_block.coordinates[1])

    cell_width = block_2.width//COLUMNS
    cell_height = block_2.height//ROWS
    
    cell_margin_1 = max(cell_width, cell_height) - min(cell_width, cell_height)
    cell_margin_2 = MARGIN // 2

    cell_width_margin = 0
    cell_height_margin = 0

    if cell_width != cell_height:
        if cell_width > cell_height:
            #cell_margin_1 = cell_margin_1+cell_margin_1//COLUMNS
            #cell_margin_2 = cell_margin_2+cell_margin_2//ROWS

            cell_width_margin = cell_margin_1
            cell_height_margin = cell_margin_2

            cell_height = cell_height - cell_height_margin
            cell_width = cell_height

        # else:
            # cell_margin_1 = cell_margin_1+cell_margin_1//ROWS
            # cell_margin_2 = cell_margin_2+cell_margin_2//COLUMNS

            cell_width_margin = cell_margin_2
            cell_height_margin = cell_margin_1

            cell_width = cell_width - cell_width_margin
            cell_height = cell_width
    else:
        #Incomplete
        #cell_margin_2 = cell_margin_2+cell_margin_2//ROWS

        cell_width_margin = cell_margin_2
        cell_height_margin = cell_margin_2

        cell_height = cell_height - cell_height_margin
        cell_width = cell_width - cell_width_margin

    cells = []
    for row in range(ROWS):
        for column in range(COLUMNS):
            cell = Cell(row, column, cell_width, cell_height, CELL_COLOR)
            cell.coordinates = (cell_width_margin//2+block_2.coordinates[0]+int((cell_width*column)+(cell_width_margin*column)), cell_height_margin//2+block_2.coordinates[1]+int((cell_height*row)+(cell_height_margin*row)))
            cells.append(cell)
    
    return [block_1, block_2, title_block, player_1_title_block, player_2_title_block, center_title_block, cells]


def refreshDisplay(screen, all_sprites):
    for entity in all_sprites:
        screen.blit(entity.surf, entity.coordinates)
    pygame.display.flip()

    
# Initialize pygame
pygame.init()

# Create the screen object
screen = pygame.display.set_mode((WINDOW_HEIGHT, WINDOW_WIDTH))

# Set the title of the screen
pygame.display.set_caption("Four In A Row Duels")

# Create objects (to hold the grids, title_blocks and cells)
[block_1, block_2, title_block, player_1_title_block, player_2_title_block, center_title_block, cells] = initBoardDisplay()


# Define Fonts to use for display
FONT_SIZE_1 = 20 # Change to depend on one of the sizes
FONT_1 = pygame.font.SysFont('Verdana', FONT_SIZE_1)

# Create the display texts
p1_display = "Player 1: "+init_msg.name1
p2_display = "Player 2: "+init_msg.name2

player_1_text = FONT_1.render(p1_display, True, BLACK)
player_1_text_size = (player_1_text.get_width(), player_1_text.get_height())

player_2_text = FONT_1.render(p2_display, True, BLACK)
player_2_text_size = (player_2_text.get_width(), player_2_text.get_height())

# Place Fonts in the blocks
player_1_title_block.surf.blit(player_1_text, (player_1_title_block.width//2 - player_1_text_size[0]//2, player_1_title_block.height//2 - player_1_text_size[1]//2))

player_2_title_block.surf.blit(player_2_text, (player_2_title_block.width//2 - player_2_text_size[0]//2, player_2_title_block.height//2 - player_2_text_size[1]//2))

# Create sprite groups
title_sprites = pygame.sprite.Group()
title_sprites.add(title_block, player_1_title_block, player_2_title_block)

all_sprites = pygame.sprite.Group()
all_sprites.add(block_1, block_2, title_block, player_1_title_block, player_2_title_block)
for cell in cells:
    all_sprites.add(cell)

tokens = []

game.ready()

while True:
    msg = game.refresh()
    
    screen.fill(BACKGROUND_COLOR)
    refreshDisplay(screen, all_sprites)

    cell_in = [msg.last_played_cell.row, msg.last_played_cell.column, msg.last_played_cell.player]
    # check that the cell_in is not the same as the last cell. i.e. a new cell has been recieved

    tokens.append(Token(cell_in[0], cell_in[1], cell_in[2]))
    for cell in cells:
        for token in tokens:
            if cell.row == token.row and cell.column == token.column:
                cell_index = cells.index(cell)
                pygame.draw.circle(cells[cell_index].surf, token.color, (cells[cell_index].width//2, cells[cell_index].height//2), cells[cell_index].width//2-MARGIN)
    pygame.display.flip()
    
    if game.winner:

        if game.winner == 1 or game.winner == 2:
            center_display = "Winner: "+game.winner_name(init_msg)
        elif game.winner == 3:
            center_display = "Draw"
        center_text = FONT_1.render(center_display, True, BLACK)
        center_text_size = (center_text.get_width(), center_text.get_height())
        center_title_block.surf.blit(center_text, (center_title_block.width//2 - center_text_size[0]//2, center_title_block.height//2 - center_text_size[1]//2))
        title_sprites.add(center_title_block)
        all_sprites.add(center_title_block)

        refreshDisplay(screen, all_sprites)

        time.sleep(5)
        break
    
    # update display from msg fields

# change display after game has eneded

# game.winner_name(init_msg)

# update display from game.winner (1 or 2, 3 for draw or -1 if any bug that got you there)
# if winner is 1 or 2 you can use game.winner_name(init_msg) to get their name
