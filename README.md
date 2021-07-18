# SnakeXenzia
Snake Game build in C using Linked List.

Features:
- It creates a grid of 20 X 20 as the roaming space for the snake.
- If the snake crosses the boundary then it will come up from the opposite boundary.
- Movement of snake is done using w-a-s-d keys:
  - w -> forward
  - s -> backward
  - d -> right
  - a -> left
- Load saved game functionality is there.
- Real time increase in length of the snake as it eats the food.
- Snake dies if it bites itself.

Functionality:
- 20 X 20 grid is created by printing # at the boundaries.
- 20 X 20 size matrix is created for tracking movement of snake.
- Food is created using random function inside the 20 X 20 grid.
- As the snake, head->x, head->y matches with the fhead->x, fhead->y then a new linked list node is added at the tail of the snake.
- With each movement of snake we check whether the head->x, head->y matches with any linked list node->x and node->y, 
  if yes then it means snake has bitten itself and game will be over.
- For loading a saved game press 'L' at start of the game, the snake location and score will be loaded from the file Snake.txt.
- For quitting the game press 'X', at the time of quitting current progress and snake location will be saved in Snake.txt file.
