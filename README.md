# Typing Speed Game

## Overview
The **Typing Speed Game** is a fun and interactive C++ project designed to improve users' typing speed and accuracy. The game challenges players to type words correctly within a time limit to progress through levels and achieve high scores.

## Gameplay
1. The player starts at **point A** and needs to reach **point B** by typing words correctly.
2. Each correctly typed word moves the player closer to the endpoint.
3. The game tracks the player's typing speed and scores.
4. The player must complete all levels before the time runs out to win.

## Features
- **Visually Appealing Interface**: Includes animations and graphics for an engaging experience.
- **Typing Speed Tracking**: Displays the player's typing speed during the game.
- **Progressive Difficulty**: Five levels with increasing complexity.
- **Leaderboard**: Tracks and displays top scores (planned feature).
- **Time-Limited Challenge**: Each level must be completed within the specified time.

## Controls
- **Keyboard**: Type the displayed words accurately to progress.
- **Enter Key**: Start the game and advance through levels.
- **Escape Key**: Exit the game.

## Dependencies
- **SFML Library**: For rendering graphics and handling events.
- **C++ Standard Libraries**: Used for basic programming constructs.

## How to Play
1. Launch the game.
2. Read the instructions on the start screen and press `Enter` to begin.
3. Type the displayed text accurately to move the character towards the endpoint.
4. Complete all five levels before the time runs out to win.
5. Check your progress and time on the HUD.

## Code Highlights
### Key Functions
- **`displayString`**: Displays text on the screen.
- **`showStartPage`**: Displays the game's start screen with instructions.
- **`showEndPage`**: Displays the end screen with a win or lose message.
- **`typingGame`**: Main gameplay function that handles the typing logic, timer, and player movement.

### Game Loop
- The game uses a loop to progress through levels. 
- Each level requires typing a predefined sentence accurately.
- The game ends when the player either completes all levels or runs out of time.

## Setup Instructions
1. Install the [SFML Library](https://www.sfml-dev.org/).
2. Clone or download the project repository.
3. Compile the code using a C++ compiler with SFML linked.
   Example compilation command (on Windows using g++):
   ```sh
   g++ -o TypingSpeedGame main.cpp -lsfml-graphics -lsfml-window -lsfml-system

