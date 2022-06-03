# Conway's Game of Life.

![](demo/demo.gif)

## Usage
To run the game run the bash script `run.sh`:
```
./run.sh
```
To specify a custom initial state pass a file containing the custom initial state as an argument to this script. E.g.
```
./run.sh samples/gosper_gun.txt
```

### Initial state file format
Initial state file consist of 25 rows and 80 columns. Each row contains characters `0` or `1` separated by space and ends with linebreak except last line. Character `1` defines alive cell and `0` defined dead cell. Try out default initial state files placed in `samples/` !

## References
- [Wikipedia article](en.wikipedia.org/wiki/Conway%27s_Game_of_Life).
