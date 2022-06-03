#include <stdio.h>

#include "game_start_point.h"

int main() {
    int is_correct = run_game();
    if (is_correct) {
        printf("Process finished correctly.");
    } else {
        printf("Process finished. Something went wrong!");
    }
    return 0;
}
