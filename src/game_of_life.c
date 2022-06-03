#include "game_of_life.h"

void game_cycle_iter(char *p_c, int *p_is_correct, int *p_upd_ms,
                     int **p_field, int *init_state, int *p_n_gen, int *p_pause)
{
    napms(*p_upd_ms);
    if (*p_is_correct)
    {
        clear();
        refresh();
        draw_field(*p_field, *p_upd_ms, *p_n_gen, *p_pause);
        *p_c = getch();
    }
    *p_is_correct = *p_is_correct && update(*p_c, p_upd_ms, p_field,
                                            init_state, p_n_gen, p_pause);
}

void init_env()
{
    initscr();
    noecho();
    timeout(0);
    raw();
}

int initialize_field(int **p_field, int **p_init_field)
{
    *p_field = (int *)malloc(WIDTH * HEIGHT * sizeof(int));
    int is_correct = *p_field != NULL;
    for (int i = 0; is_correct && i < WIDTH * HEIGHT; ++i)
        is_correct = is_correct && scanf("%d", &((*p_field)[i])) == 1;
    if (is_correct)
    {
        char *termid = ctermid(NULL);
        is_correct = is_correct && alloc_and_copy_arr(*p_field, p_init_field);
        is_correct = is_correct && termid != NULL && freopen(termid, "r", stdin) != NULL;
    }
    return is_correct;
}

int update(char c, int *p_upd_ms, int **p_field, int *init_state, int *p_n_gen, int *p_pause)
{
    int is_correct = 1;
    update_speed_ms(c, p_upd_ms, p_pause);
    if (!reset_if_needed(c, p_field, init_state, p_n_gen) && (!*p_pause || c == ' '))
    {
        int *field_prev;
        is_correct = is_correct && alloc_and_copy_arr(*p_field, &field_prev);
        *p_n_gen = *p_n_gen + 1;
        for (int i = 0; is_correct && i < HEIGHT; ++i)
            for (int j = 0; is_correct && j < WIDTH; ++j)
                update_cell(p_field, field_prev, i, j);
        if (is_correct)
            free(field_prev);
    }
    return is_correct;
}

int reset_if_needed(char c, int **p_field, int *init_state, int *p_n_gen)
{
    int had_reset = c == 'r' || c == 'R' || *p_n_gen >= MAX_GENERATION;
    if (had_reset)
    {
        copy_arr(init_state, p_field);
        *p_n_gen = 1;
    }
    return had_reset;
}

void update_speed_ms(char c, int *p_upd_ms, int *p_pause)
{
    if ('1' <= c && c <= '9')
    {
        *p_upd_ms = MIN_DELAY_MS + ONE_LEVEL_DELAY_MS * (10 - (c - '0') - 1);
        *p_pause = 0;
    }
    if (c == '0' || c == ' ')
        *p_pause = 1;
}

void copy_arr(const int *field, int **p_field_copy)
{
    for (int i = 0; i < HEIGHT; ++i)
        for (int j = 0; j < WIDTH; ++j)
            (*p_field_copy)[WIDTH * i + j] = field[WIDTH * i + j];
}

int alloc_and_copy_arr(const int *field, int **p_field_copy)
{
    *p_field_copy = (int *)malloc(WIDTH * HEIGHT * sizeof(int));
    int is_correct = *p_field_copy != NULL;
    for (int i = 0; is_correct && i < HEIGHT; ++i)
        for (int j = 0; is_correct && j < WIDTH; ++j)
            (*p_field_copy)[WIDTH * i + j] = field[WIDTH * i + j];
    return is_correct;
}

void update_cell(int **p_field, int *field_prev, int i, int j)
{
    int n_alive_neighb = count_alive_neighbors(field_prev, i, j);
    if (is_cell_dead(field_prev, i, j) && n_alive_neighb == 3)
        make_cell_alive(p_field, i, j);
    if (is_cell_alive(field_prev, i, j) && (n_alive_neighb < 2 || n_alive_neighb > 3))
        make_cell_dead(p_field, i, j);
}

int count_alive_neighbors(const int *field, int i, int j)
{
    return field[WIDTH * ((i + 1) % HEIGHT) + j] + field[WIDTH * i + ((j + 1) % WIDTH)] +
           field[WIDTH * ((HEIGHT + i - 1) % HEIGHT) + j] +
           field[WIDTH * i + ((WIDTH + j - 1) % WIDTH)] +
           field[WIDTH * ((i + 1) % HEIGHT) + ((j + 1) % WIDTH)] +
           field[WIDTH * ((HEIGHT + i - 1) % HEIGHT) + ((j + 1) % WIDTH)] +
           field[WIDTH * ((i + 1) % HEIGHT) + ((WIDTH + j - 1) % WIDTH)] +
           field[WIDTH * ((HEIGHT + i - 1) % HEIGHT) + ((WIDTH + j - 1) % WIDTH)];
}

void draw_field(int *field, int upd_ms, int n_gen, int pause)
{
    draw_upper_border(upd_ms, n_gen, pause);
    for (int i = 0; i < HEIGHT; ++i)
    {
        printw("|");
        for (int j = 0; j < WIDTH; ++j)
            printw("%c", field[WIDTH * i + j] ? ALIVE_CELL : DEAD_CELL);
        printw("|\n");
    }
    draw_lower_border();
    printw("Keys: Q - quit, R - reset, 1,2,3,4,5,6,7,8,9 - speed, 0 or SPACE - pause,\n");
    printw("(during pause) SPACE - next step.");
}

void draw_upper_border(int upd_ms, int n_gen, int pause)
{
    if (pause)
        printw("o---Upd.delay=INFms---N.generations=%-5.d",
               n_gen);
    else
        printw("o---Upd.delay=%-3.dms---N.generations=%-5.d",
               upd_ms, n_gen);
    for (int i = 40; i < WIDTH; ++i)
        printw("-");
    printw("o\n");
}

void draw_lower_border()
{
    printw("o");
    for (int i = 0; i < WIDTH; ++i)
        printw("-");
    printw("o\n");
}

void make_cell_dead(int **p_field, int i, int j)
{
    (*p_field)[WIDTH * (i % HEIGHT) + (j % WIDTH)] = 0;
}

void make_cell_alive(int **p_field, int i, int j)
{
    (*p_field)[WIDTH * (i % HEIGHT) + (j % WIDTH)] = 1;
}

int is_cell_alive(const int *field, int i, int j)
{
    return field[WIDTH * (i % HEIGHT) + (j % WIDTH)];
}

int is_cell_dead(const int *field, int i, int j)
{
    return 1 - field[WIDTH * (i % HEIGHT) + (j % WIDTH)];
}
