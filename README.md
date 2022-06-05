# Conway's Game of Life
![](demo/demo.gif)
Simple console application that runs [Conway's Game of Life](en.wikipedia.org/wiki/Conway%27s_Game_of_Life) implemented in C. In this implementation game the field is a [torus](https://en.wikipedia.org/wiki/Torus) which means that the top is glued to the bottom, and the right border is glued to the left border.

## Requirements
Tested on Ubuntu 20.04.5 LTS.
```
sudo apt install libncurses5-dev
```

## Usage
To run the game run the shell script `run.sh`:
```
./run.sh
```
To specify a custom initial state, pass a file containing the custom initial state as an argument to this script:
```
./run.sh samples/gosper_gun.txt
```

### Initial state file format
Initial state file consists of 25 rows and 80 columns. Each row contains characters `0` or `1` separated by spaces. Each row except the last one ends with a linebreak. Character `1` defines an alive cell and `0` defined a dead cell. For a demo, try out default initial state files placed in `samples/`.

## References
- [Conway's Game of Life (wiki)](en.wikipedia.org/wiki/Conway%27s_Game_of_Life);
- [torus (wiki)](https://en.wikipedia.org/wiki/Torus).
