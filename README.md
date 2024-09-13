# MiniLibX Game

This is a simple game built using the MiniLibX library. Follow the instructions below to set up and run the game.

## Prerequisites

- Ensure you have `make` installed on your system.
- Ensure you have the necessary libraries and dependencies for MiniLibX.

## Setup

1. Extract the MiniLibX library:
    ```sh
    tar -xvzf 'minilibx-linux(1).tgz'
    ```

2. Build the project using `make`:
    ```sh
    make
    ```

## Running the Game

To run the game, use the following command:  ./so_long ""map/ one of the maps inside the map directory"
```sh
./so_long map/valid1.ber
```

## Issues

When creating the map, at the end of each single line, when pressing "Enter", it prints a "\n" new_line. For this reason i was
getting problems with reading and with the map_checker.

## To do list

1. Block the player after reaching the door without the objects. It continues moving to the direction.
2. Add sprites
