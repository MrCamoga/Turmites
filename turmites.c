#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Rule {
    int color;
    int direction;
    int state;
};

int main(int argc, int *argv[]) {

    const int n_states = 2; //colors
    const int ant_states = 3;

    const int dir_x[] = {0,1,0,-1};
    const int dir_y[] = {-1,0,1,0};

    // struct Rule rules[3][2] = {{{1,1,1},{1,-1,0}},{{1,3,1},{0,1,2}},{{1,3,2},{1,3,0}}};

    struct Rule rules[5][2] = {{{1,0,1},{1,-1,0}},{{1,2,2},{0,3,3}},{{0,1,4},{0,1,3}},{{1,3,0},{0,3,1}},{{0,0,0},{0,0,1}}};

    int x = 512;
    int y = 512;
    int antstate = 0;

    unsigned char *level = calloc(1024*1024,sizeof(unsigned char));

    int it;
    clock_t start = clock();
    for(it = 0; 1; it++) {
        unsigned char *state = &level[x|(y<<10)];
        struct Rule *rule = &rules[antstate][*state];
        if(rule->direction == -1) break;
        x+=dir_x[rule->direction];
        y+=dir_y[rule->direction];
        antstate = rule->state;
        *state = rule->color;
    }
    clock_t end = clock();
    double seconds = (double)(end-start)/CLOCKS_PER_SEC;
    printf("%d\n", it);
    printf("%fs,%f it/s\n",seconds, it/seconds);


    // for(int i = 0; i < ant_states; i++) {
    //     for(int j = 0; j < n_states; j++) {
    //         struct Rule *rule = &rules[i][j];
    //         printf("%d,%d,%d\n",rule->color,rule->direction,rule->state);
    //     }
    // }

    return 0;
}