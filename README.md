
# Tic Tac Toe Game using SDL2 and TTF

This project is a simple Tic Tac Toe game created using SDL2 and SDL_ttf libraries for rendering text. The game supports two players, displays the current player’s turn, and detects win conditions and ties. A restart button allows the game to be reset after a win, loss, or tie.

## Features
- Tic Tac Toe gameplay for two players
- Player turns displayed on the screen
- Detection of wins (horizontal, vertical, and diagonal) and ties
- A restart button to start a new game
- Rendered with SDL2 graphics and text rendering using SDL_ttf

## Prerequisites

### Linux
Make sure you have the following packages installed:
- `SDL2`
- `SDL2_ttf`

On Debian-based systems, you can install them using:
```bash
sudo apt-get install libsdl2-dev libsdl2-ttf-dev
```

On Arch Linux:
```bash
sudo pacman -S sdl2 sdl2_ttf
```

### Windows
On Windows, you can download the following:
- [SDL2 Development Library](https://libsdl.org/download-2.0.php)
- [SDL2_ttf Development Library](https://www.libsdl.org/projects/SDL_ttf/)

Extract both SDL2 and SDL2_ttf, then set the appropriate include and library directories in your compiler settings (such as MinGW or Visual Studio).

## Compiling and Running

### Linux
1. **Clone the repository**:
   ```bash
   git clone https://github.com/yourusername/tic-tac-toe-sdl2.git
   cd tic-tac-toe-sdl2
   ```

2. **Compile the program**:
   ```bash
   gcc -o tic-tac-toe main.c -lSDL2 -lSDL2_ttf
   ```

3. **Run the program**:
   ```bash
   ./tic-tac-toe
   ```

### Windows (using MinGW)
1. **Download and set up MinGW** if you haven't already. Ensure that the SDL2 and SDL2_ttf libraries are properly placed in your MinGW installation (`include` and `lib` directories).

2. **Compile the program**:
   ```bash
   gcc -o tic-tac-toe.exe main.c -IC:\path\to\SDL2\include -LC:\path\to\SDL2\lib -lSDL2 -IC:\path\to\SDL2_ttf\include -LC:\path\to\SDL2_ttf\lib -lSDL2_ttf
   ```

   Adjust the paths (`C:\path\to\...`) to where you've extracted the SDL2 and SDL_ttf libraries.

3. **Run the program**:
   Simply double-click `tic-tac-toe.exe` in your Windows File Explorer, or run it from the terminal:
   ```bash
   ./tic-tac-toe.exe
   ```

## Controls
- **Left-click** on the squares to place an 'X' or 'O'.
- **Restart Button**: When the game ends in a win, loss, or tie, click the "Restart" button to start a new game.

## Dependencies
- **SDL2**: For rendering the game window and handling input.
- **SDL2_ttf**: For rendering text in the game (e.g., player turn, game over messages).
