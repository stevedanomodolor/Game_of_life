# GAME OF LIFE

# Table of Contents
* [General Info](#General-info)
* [Code specification](#Code-specification)
* [Dependencies](#Dependencies)
* [Build](#Build)
* [Usage](#Usage)


## General Info
The code contains a c implementation of the game of life by conway.
## Code specification
The code consists of the following parts
- conway_functions: where all the functions for the initialization/display/update of each cell in the the game of life. It is worth mentioning that each the cellmap only stores the live cell to improve code speed.
- visualization_tools- This part contains necessary functions to allows display information to the user using the ncurses library.
- common_variable_type- It contains variable type commonly shared between all the other parts of the code.
- global_variables/main this included the definition and declarations of all the necessary variables to execute the game. It also include a state machine to better handle the flow of the game.
## Dependencies
This game requires was implemented  and tested on a linux system/ unexpected behavior might occur if executed in a other system.
The ncurses library is used for the display, if you do not have it install, use the following command to install
```
sudo apt-get install libncurses5-dev libncurses5
```
## Build
To build the game go to the folder that where the Makefile is and execute the following command
```
make clean
make - to compile the code
./main - to execute the game
```

## Usage
After executing the game, it should take you directly to the main menu-

 **IMPORTANT**
 - Use touch pad to interact with the menu, mouse click might not work well(external mouse does work but might require double click)
 - Remember to play p to start the simulation in both manual or automatic mode
 - Instructions in included in the Helpbox
 - **Have fun !!!:)))))))**

 This initial structure are available
- R_pentomino
- Diehard
- Acorn
- Glider
- LightWeigth_spaceship
- Pulsar
