# Tic-Tac-Toe

This repository contains the implementation of a Tic-Tac-Toe game developed as part of my first-semester coursework at BME. The game features a dynamic board size, customizable settings, and a computer opponent with varying difficulty levels. This project showcases both my programming and problem-solving skills.

## Features

### Gameplay
- **Dynamic Board Size**: The game board can be adjusted to dimensions ranging from 6x6 to 20x20, providing flexibility for different levels of complexity.
- **Winning Condition**: Players must align five of their symbols (X or O) consecutively in any direction (horizontal, vertical, or diagonal) to win the game.
- **Two Difficulty Levels**:
  - **Normal Mode**: The computer uses the Minimax algorithm with limited depth.
  - **Hard Mode**: The computer uses the advanced Minimax algorithm with alpha-beta pruning, with a greater depth, ensuring challenging and strategic gameplay.

### User Interface
- **Graphical Interface**: The game features a clean and intuitive graphical user interface built using SDL2.
- **Menus**:
  - **Main Menu**: Provides options to start a new game, load a saved game, or quit the application.
  - **Setup Menu**: Allows users to customize game settings, including board size, difficulty level, and the starting player.

### Additional Features
- **Save and Load**: Players can save their game progress to a file and resume it at any time.
- **Dynamic Memory Management**: Efficient handling of the game board and other resources ensures smooth operation.
- **Error Handling**: The program validates inputs and provides appropriate feedback for invalid actions.

## File Structure

The project is organized into clearly separated source and header files for better modularity:

- **Source Files (`src/`)**:
  - `check.c`: Validates moves and checks game conditions.
  - `computer.c`: Implements computer decision-making logic for different difficulty levels.
  - `creategraphic.c`: Handles graphical rendering and user interface.
  - `game.c`: Core game logic, including initialization and control flow.
  - `init.c`: Handles game setup and initialization.
  - `main.c`: Entry point of the application.
  - Other supporting files for menus, structures, and utility functions.
- **Header Files (`include/`)**:
  - Corresponding headers for each source file, containing function declarations and shared structures.

## Key Algorithms

### Minimax Algorithm with Alpha-Beta Pruning
The Minimax algorithm is the backbone of the Hard Mode, allowing the computer to make strategic decisions:
- **Purpose**: Evaluates all possible moves to determine the best outcome for the computer while minimizing the opponent's chances of winning.
- **Alpha-Beta Pruning**: Reduces the number of nodes evaluated by skipping branches that cannot influence the final decision.
- **Heuristic Evaluation**: Assigns scores to game states based on factors such as potential winning sequences and blocked opponent moves.

### Move Validation
The game ensures that every move is valid and provides functions to:
- Check if a position is within bounds and unoccupied.
- Detect win conditions by evaluating consecutive symbols in all directions.
- Identify if the board is full, signaling a draw.

### Graphics Rendering
- SDL2 functions dynamically render menus, game boards, and feedback messages based on the current game state.
- Example functions:
  - `createMenu(SDL_Renderer* renderer)`: Renders the main menu.
  - `createGameGraphics(SDL_Renderer* renderer, GameSettings* settings)`: Displays the game board with updated player moves.

### Prerequisites
- **SDL2**
- **GCC**
- **Platform**: The game is tested on Windows 11 with Code::Blocks, but it should run on any platform with SDL2 support.

## Tools and Environment
- **Programming Language**: C
- **Libraries**: SDL2, debugmalloc
- **Compiler**: GCC
- **Development Environment**: Code::Blocks on Windows 11

## Challenges and Solutions

### Implementing the Minimax Algorithm
One of the most complex aspects of the project was implementing the Minimax algorithm with alpha-beta pruning. Challenges included:
- **Exponential Growth of States**: Limited the depth of recursion to ensure the algorithm remained efficient and fast.
- **Heuristic Accuracy**: Designed a heuristic evaluation function to score game states effectively.

### Dynamic Memory Management
Managing the game board as a dynamically allocated 2D array required careful handling to avoid memory leaks. Functions were created to allocate and free memory appropriately.

### Graphical Integration
Integrating SDL2 with game logic involved:
- Designing a responsive graphical interface.
- Ensuring smooth transitions between game states, such as starting a new game or loading progress.

## Learning Highlights
- Gained experience with advanced algorithms like Minimax and alpha-beta pruning.
- Developed a modular design approach with clear separation of logic, rendering, and utility functions.
- Enhanced problem-solving skills by addressing challenges in heuristic evaluation and memory management.
- Built a complete graphical application using SDL2, improving my understanding of event-driven programming.

## Featured Project
- My Tic-Tac-Toe game has been featured on the course website as one of the best projects of the semester.
[Link](https://infoc.eet.bme.hu/nhfgaleria2024/#32)

