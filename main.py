import numpy as np
import pygame
import maze  # Import the custom maze package
from Settings import *
from SnakeGame import *

def main():
    pygame.init()

    # Generate maze using the maze package
    generated_maze = maze.Maze(20, 20, 1)  # Example: 20x20 maze with 1 exit
    generated_maze.generate()
    maze_data = generated_maze.getMazeData()

    # Calculate screen size based on maze dimensions
    maze_height = len(maze_data)
    maze_width = len(maze_data[0])
    screen_width = maze_width * CELL_SIZE + 2 * PADDING
    screen_height = maze_height * CELL_SIZE + 2 * PADDING

    screen = pygame.display.set_mode((screen_width, screen_height))
    pygame.display.set_caption('Snake Game with A*')

    game = SnakeGame(maze_data)

    clock = pygame.time.Clock()
    running = True
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

        game.step()
        game.draw(screen)
        pygame.display.flip()
        clock.tick(FPS)

    pygame.quit()

if __name__ == "__main__":
    main()
