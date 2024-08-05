import random
from AStar import AStar
import pygame
from Settings import *

class SnakeGame:
    def __init__(self, maze):
        self.maze = maze
        self.width = len(maze[0])
        self.height = len(maze)
        self.snake = [(1, 1)]
        self.direction = (1, 0)
        self.food = self.place_food()
        self.astar = AStar(maze)
        self.path = self.astar.find_path(self.snake[0], self.food)

    def place_food(self):
        while True:
            x = random.randint(0, self.width - 1)
            y = random.randint(0, self.height - 1)
            if self.maze[y][x] == 0 and (x, y) not in self.snake:
                return (x, y)

    def reset(self):
        self.snake = [(1, 1)]
        self.direction = (1, 0)
        self.food = self.place_food()
        self.path = self.astar.find_path(self.snake[0], self.food)

    def step(self):
        if self.path:
            next_pos = self.path.pop(0)
            self.snake.insert(0, next_pos)
            if self.snake[0] == self.food:
                self.food = self.place_food()
                self.path = self.astar.find_path(self.snake[0], self.food)
            else:
                self.snake.pop()

    def draw(self, screen):
        screen.fill(BACKGROUND_COLOR)

        # Draw grid lines
        for y in range(self.height):
            for x in range(self.width):
                pygame.draw.rect(screen, GRID_COLOR, pygame.Rect(x*CELL_SIZE + PADDING, y*CELL_SIZE + PADDING, CELL_SIZE, CELL_SIZE), 1)

        # Draw the maze
        for y in range(self.height):
            for x in range(self.width):
                if self.maze[y][x] == 1:
                    pygame.draw.rect(screen, WALL_COLOR, pygame.Rect(x*CELL_SIZE + PADDING, y*CELL_SIZE + PADDING, CELL_SIZE, CELL_SIZE))

        # Draw the snake
        for pos in self.snake:
            pygame.draw.rect(screen, SNAKE_COLOR, pygame.Rect(pos[0]*CELL_SIZE + PADDING, pos[1]*CELL_SIZE + PADDING, CELL_SIZE, CELL_SIZE))

        # Draw the food
        pygame.draw.rect(screen, FOOD_COLOR, pygame.Rect(self.food[0]*CELL_SIZE + PADDING, self.food[1]*CELL_SIZE + PADDING, CELL_SIZE, CELL_SIZE))
