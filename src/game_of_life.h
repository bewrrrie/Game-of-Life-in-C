#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H

#include <ncurses.h>
#include <stdlib.h>

#define MIN_DELAY_MS 50
#define ONE_LEVEL_DELAY_MS 25
#define DEFAULT_DELAY_MS 150
#define MAX_GENERATION 99999
#define WIDTH 80
#define HEIGHT 25
#define DEAD_CELL ' '
#define ALIVE_CELL 'o'

void game_cycle_iter(char *p_c, int *p_is_correct, int *p_upd_ms,
                     int **p_field, int *init_state, int *p_n_gen,
                     int *p_pause);
void init_env();
int initialize_field(int **field, int **init_field);
int update(char c, int *p_upd_ms, int **field, int *init_state,
           int *p_n_gen, int *p_pause);
int reset_if_needed(char c, int **p_field, int *init_state, int *p_n_gen);
void update_cell(int **p_field, int *field_prev, int i, int j);
void update_speed_ms(char c, int *p_upd_ms, int *p_pause);
void draw_field(int *field, int upd_ms, int n_gen, int pause);
void draw_upper_border(int upd_ms, int n_gen, int pause);
void draw_lower_border();
void make_cell_dead(int **p_field, int i, int j);
void make_cell_alive(int **p_field, int i, int j);
void copy_arr(const int *field, int **p_field_copy);
int alloc_and_copy_arr(const int *field, int **p_field_copy);
int is_cell_alive(const int *field, int i, int j);
int is_cell_dead(const int *field, int i, int j);
int count_alive_neighbors(const int *field, int i, int j);

#endif
