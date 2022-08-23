#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>

#define WIDTH 80
#define LENGTH 50
#define TOP 0
#define BOTTOM 49
#define LEFT 0
#define RIGHT 79

void start_field(int *field);
void figures(int *field);
int check_update_filed(int *field, int *last_field);
void output_field(int *field);
void pausedelay(int milli_seconds);

int main() {
    int field[LENGTH][WIDTH];
    int x = 0;
    start_field(&field[0][0]);
    while (x != 100) {
        figures(&field[0][0]);
        output_field(&field[0][0]);
    }   
    return 0;
}

void start_field(int *field) {
    
    for (int i = 0; i < LENGTH; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == TOP || j == LEFT || i == BOTTOM  || j ==RIGHT)
                field[i*WIDTH+j] = 1;
            else field[i*WIDTH+j] = 0;
        }
    }
}

void figures(int *field) {
    int last_filed[LENGTH][WIDTH];
    for (int i = LENGTH-1; i >= 0; i--) { // 0 .. 49
        for (int j = WIDTH-1; j >= 0; j--) {
            last_filed[i][j] == field[i*WIDTH+j];
        }
    }
    field[1*WIDTH+13] = 2;
    field[1*WIDTH+14] = 2;
    field[2*WIDTH+13] = 2;
    field[2*WIDTH+14] = 2;
    
    output_field(field);
    while (check_update_filed(field, &last_filed[0][0]) != 0) {
        int move = 0, from = 0, before = 0, changes = 0;
        switch (getchar()) {
            case 'a': {
                move++;
                from = 0;
                before = WIDTH-1;
                changes = 1;

            } break;
            case 'd': {
                move--;
                from = 0;
                before = WIDTH-1;
                changes = -1;
            } break;
            default: break;
        }
        for (int i = LENGTH-1; i >= 0; i--) { // 0 .. 49
            for (int j = from; j != before; j-=changes) { // 0 .. 79
                if ((field[i*WIDTH+j] == 2) && (((field[(i+1)*WIDTH+j]) != 1) && ((field[(i+1)*WIDTH+j]) != 2))) {
                    field[i*WIDTH+j] = 0;
                    field[(i+1)*WIDTH+(j+move)] = 2;
                    output_field(field);
                    pausedelay(150000);
                }
            }
        }
    }
}


int check_update_filed(int *field, int *last_field) {
    int flag = 0;
    for (int i = LENGTH-1; i >= 0; i--) { // 0 .. 49
        for (int j = WIDTH-1; j >= 0; j--) {
            if (last_field[i*WIDTH+j] != field[i*WIDTH+j]) {
                flag++;
            }
        }
    }
    return flag;
}

void output_field(int *field) {
    for (int i = 0; i < LENGTH; i++) {
        for (int j = 0; j < WIDTH; j++) {
            switch (field[i*WIDTH+j]) {
                case 1: printf("."); break;
                case 2: printf("#"); break;
                case 0: printf(" "); break;
                default:break;
            }
        }
        printf("\n");
    }
}

void pausedelay(int milli_seconds) {
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds) {}
}
