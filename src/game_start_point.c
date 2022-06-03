#include "game_start_point.h"

int run_game() {
    char c = getch();
    int *field;
    int *init_state;
    int upd_ms = DEFAULT_DELAY_MS;
    int n_generations = 1;
    int is_correct = initialize_field(&field, &init_state);
    int pause = 0;
    if (is_correct)
        init_env();
    while (is_correct && c != 'q' && c != 'Q')
        game_cycle_iter(&c, &is_correct, &upd_ms, &field,
                        init_state, &n_generations, &pause);
    if (is_correct) {
        endwin();
        free(field);
        free(init_state);
    }
    return is_correct;
}
