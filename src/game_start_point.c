#include "game_start_point.h"

int run_game() {
    char c = getch();
    int *field;
    int *init_state;
    int upd_ms = DEFAULT_DELAY_MS;
    int n_generations = 1;
    int exit_code = initialize_field(&field, &init_state);
    int pause = 0;
    if (exit_code == 0)
        init_env();
    while (exit_code == 0 && c != 'q' && c != 'Q')
        game_cycle_iter(&c, &exit_code, &upd_ms, &field,
                        init_state, &n_generations, &pause);
    if (exit_code == 0) {
        endwin();
        free(field);
        free(init_state);
    }
    return exit_code;
}
