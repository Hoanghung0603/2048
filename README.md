

# 2048 Game using C++ and SDL2.0

This is a project about the 2048 game using C++ and SDL2.0 (include SDL_image and SDL_mixer). It is a popular puzzle game which is suitable for any age.

![2048](https://user-images.githubusercontent.com/125201219/236513254-18b7c3ab-3d76-4f87-972e-423277db8314.png)

## Game Rules

- When starting the game, the player can choose the size of the grid they want to play. Winning conditions vary based on the chosen grid size. For a 3x3 grid, the player needs to reach the 1024 tile. For a 4x4 or 5x5 grid, player wins by reaching the 2048 tile. To win on a 6x6 grid, the 4096 tile needs to be reached.
- Game starts, player uses the arrow keys to move the number tiles. Two square tiles with the same value will merge into one.
- You win the game if a tile with the value of 2048 appears. Otherwise, the game ends when you cannot move the tiles anymore.

## Features
During gameplay, the following features are available:
- Press the "u" key to undo your last move (you can only undo one move per turn).
- Press the "n" key to start a new game.
- Press the "r" key to view the winnerlist, where you can see the ranking sorted by playtime or score.

## Demo


https://github.com/Hoanghung0603/2048/assets/125201219/15f599da-0b62-4b71-aa19-3593770f5b50


## Installation
To install and run the 2048 game, follow these steps:

1. Install a C++ compiler (such as Visual Studio Code or Codeblocks).
   ([How to download Codeblocks](https://www.wikihow.com/Download,-Install,-and-Use-Code::Blocks#Downloading-Code::Blocks))
3. Install the SDL2.0 library (as well as SDL_image and SDL_mixer) by downloading it from the official SDL2.0 website or using a package manager. ([Here is how to do it](https://lazyfoo.net/tutorials/SDL/01_hello_SDL/index.php))

### Cloning the Repository

1. Open your command line interface (CLI) or terminal.
2. Navigate to the directory where you want to clone the repository using the `cd` command.
3. Run the command `git clone https://github.com/Hoanghung0603/2048.git`.

This will create a local copy of the repository on your machine.

### Building and Running the Game

To build and run the game, follow these steps:

1. Open the project in your C++ IDE.
2. Build the project.
3. Run the project.

## Contact Information

If you have any questions or suggestions, please contact me via email: hoangduyhung021@gmail.com.
