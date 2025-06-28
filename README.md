# Maze Generation and Navigation with Pursuit

This project implements a maze generation algorithm using a modified Eller's algorithm, combined with a character navigation system and a pursuing enemy. The game uses ncurses for terminal-based display and features multiple levels, lives, and an AI that chases the player.

## Features

- **Dynamic Maze Generation**: Creates unique mazes using probabilistic horizontal and vertical connections
- **Character Navigation**: Move through the maze using arrow keys
- **Pursuit AI**: An enemy that follows the player using BFS (Breadth-First Search)
- **Level System**: Progressively more difficult mazes with increasing levels
- **Life System**: Players have multiple lives, lost when caught by the enemy
- **Visual Display**: Uses ncurses for terminal rendering with color support
- **Trail System**: Option to show visited positions (toggle with 't')
- **Performance Metrics**: Real-time display of level and remaining lives
- **Customizable Parameters**: Adjust maze size and difficulty through preprocessor definitions

## Requirements

- C compiler (GCC recommended)
- Ncurses library (wide character support)
- Linux or Unix-like environment (for ncurses support)

## Compilation and Execution

1. Compile the program:
```bash
gcc main.c -o main -lncursesw -lrt
```

2. Run the executable:
```bash
./main
```

3. Use arrow keys to navigate through the maze

## Controls
- **Arrow Keys**: Move the player
- **R**: Generate a new maze (reset current level)
- **T**: Toggle trail (show visited positions)
- **Z**: Toggle slow motion for enemy movement (for debugging)

## Game Elements

- **Player**: Represented by `o` (yellow)
- **Enemy (Stalker)**: Represented by `x` (red) - appears after 3 seconds
- **Entrance**: Represented by `+` (green)
- **Exit**: Represented by `_` (green) - reach this to advance to next level

## Game Mechanics

- The player starts at the entrance and must reach the exit
- Each level increases the speed of the enemy (difficulty)
- The enemy will chase the player using BFS, ensuring the shortest path
- If the enemy catches the player, one life is lost
- When the player reaches the exit:
  - A new maze is generated (next level)
  - Player gains one life (up to maximum of 10)
  - Enemy speed increases by 8%
- The game ends when the player loses all lives

## Code Structure

### Key Components

1. **Data Structures**:
   ```c
   typedef struct {
       int x;
       int y;
   } Coordinates;
   
   typedef struct {
       int interval, entranceTime, life;
       bool alive;
       Coordinates position;
       struct timespec lastEvent;
   } Character;
   ```

2. **Global Variables**:
   - `maze[HEIGHT][WIDTH]`: Stores the maze structure
   - `visited[HEIGHT][WIDTH]`: Tracks positions visited by the player
   - `actor`: The player character
   - `stalker`: The pursuing enemy
   - `enterDoor`, `leaveDoor`: Entrance and exit coordinates

3. **Core Functions**:
   - `init()`: Initializes ncurses, color pairs, and maze structure
   - `mazeGen()`: Generates maze using modified Eller's algorithm
   - `show()`: Displays maze, player, enemy, and doors with colors
   - `entryProcess()`: Handles keyboard input for movement
   - `Stalker()`: Controls enemy behavior and movement
   - `BFS()`: Implements Breadth-First Search for enemy pathfinding
   - `genNewMaze()`: Generates new maze for next level

### Algorithm Overview

**Maze Generation** (Modified Eller's Algorithm):
1. Initialize matrix with unique set identifiers
2. Create horizontal connections between adjacent cells based on probability
3. Create vertical connections between rows with controlled randomness
4. Ensure connectivity by forcing at least one vertical connection per set
5. Finalize maze by connecting remaining sets in last row

**Enemy AI** (Breadth-First Search):
1. Uses queue-based BFS to find shortest path to player
2. Explores all possible paths in the maze
3. Tracks path taken using `cameFrom` matrix
4. Takes first step of shortest path at each move interval

## Customization

Modify these parameters in the source code:
```c
// Maze dimensions
#define M_HEIGHT 8
#define M_WIDTH 8

// Enemy speed (decreases with level, making enemy faster)
speed -= 0.08; // Inside genNewMaze()

// Initial enemy appearance delay (seconds)
getElapsedTime(&lastMazeGen, 3.0) // In createStalker()
```

## Performance Metrics

The game displays real-time information below the maze:
- Current level number
- Lives remaining (visual health bar)
- Enemy speed increases with each level

## Debug Features

- **Trail Mode**: Toggle with 't' to see visited positions (marked with '.')
- **Slow Motion**: Toggle with 'z' to slow down enemy movement (for observation)
- **Life Display**: Lives are shown as a row of '@' symbols below the maze

## License

This code is provided as-is for educational purposes. Feel free to modify and use it in your projects.