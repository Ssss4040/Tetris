#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>

#define WIDTH 40
#define LENGTH 40
#define TOP 0
#define LEFT 0

void start_field(int *field);
void sample_figures(int *field, int *list_figures);
void figures_field(int *field, int *list_figures);
int check_update_filed(int *field, int *last_field);
void output_field(int *field);
void pausedelay(int milli_seconds);
void turn_figutes (int *field);

int main() {
    initscr();
    savetty();
    nonl();
    cbreak();
    noecho();
    timeout(0);
    leaveok(stdscr, TRUE);
    curs_set(0);
    int field[LENGTH][WIDTH];
    int x = 0, list_figures = 0;
    start_field(&field[0][0]);
    while (x != 100) {
        figures_field(&field[0][0], &list_figures);
        output_field(&field[0][0]);
        pausedelay(150000);
    }
    pausedelay(1000000);
    curs_set(1);
    clear();
    refresh();
    resetty();
    endwin();
    exit(0);
    return 0;
}

void start_field(int *field) {
    
    for (int i = 0; i < LENGTH; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == TOP || j == LEFT || i == (WIDTH-1)  || j == (LENGTH-1))
                field[i*WIDTH+j] = 1;
            else field[i*WIDTH+j] = 0;
        }
    }
}

 void sample_figures(int *field, int *list_figures) {
    switch (*list_figures) {
        case 0: {
            field[1*WIDTH+(WIDTH/2-1)] = 2; // ##
            field[1*WIDTH+(WIDTH/2-2)] = 2; // ##
            field[2*WIDTH+(WIDTH/2-1)] = 2;
            field[2*WIDTH+(WIDTH/2-2)] = 2;
            (*list_figures)++;
            } break;
        case 1: {
            field[1*WIDTH+(WIDTH/2-1)] = 2; //  #
            field[2*WIDTH+(WIDTH/2-1)] = 2; //  #
            field[3*WIDTH+(WIDTH/2-1)] = 2; // ##
            field[3*WIDTH+(WIDTH/2-2)] = 2;
            (*list_figures)++;
        }break;
        case 2: {
            field[1*WIDTH+(WIDTH/2-1)] = 2; // ##
            field[1*WIDTH+(WIDTH/2)] = 2;   //  ##
            field[2*WIDTH+(WIDTH/2)] = 2;
            field[2*WIDTH+(WIDTH/2+1)] = 2;
            (*list_figures)++;
        }break;
        case 3: {
            field[1*WIDTH+(WIDTH/2)] = 2;   //  #
            field[2*WIDTH+(WIDTH/2-1)] = 2; // ###
            field[2*WIDTH+(WIDTH/2)] = 2;
            field[2*WIDTH+(WIDTH/2+1)] = 2;
            (*list_figures)++;
        }break;
        case 4: {
            field[1*WIDTH+(WIDTH/2)] = 2;   //  ##
            field[1*WIDTH+(WIDTH/2+1)] = 2; // ##
            field[2*WIDTH+(WIDTH/2)] = 2;
            field[2*WIDTH+(WIDTH/2-1)] = 2;
            (*list_figures)++;
        }break;
        case 5: {
            field[1*WIDTH+(WIDTH/2)] = 2;   // # 
            field[2*WIDTH+(WIDTH/2)] = 2;   // #
            field[3*WIDTH+(WIDTH/2)] = 2;   // ##
            field[3*WIDTH+(WIDTH/2+1)] = 2;
            (*list_figures)++;
        }break;
        case 6: {
            field[1*WIDTH+(WIDTH/2)] = 2;   // # 
            field[2*WIDTH+(WIDTH/2)] = 2;   // #
            field[3*WIDTH+(WIDTH/2)] = 2;   // #
            field[4*WIDTH+(WIDTH/2)] = 2;   // #
            *list_figures = 0;
        }break;
        default: break;
    }
 }

void figures_field(int *field, int *list_figures) {
    turn_figutes (field);
    int last_filed[LENGTH][WIDTH];
    int flag = 0;
    sample_figures(field, list_figures);
    
    while (check_update_filed(field, &last_filed[0][0]) != 0) {
        flag = 0;
        pausedelay(150000);
        int move = 0, from = 0, before = 0, changes = 0;
        for (int i = LENGTH-1; i >= 0; i--) { // 0 .. 49
            for (int j = WIDTH-1; j >= 0; j--) {// 0 .. 79
                last_filed[i][j] = field[i*WIDTH+j];
            }
        }
        switch (getch()) {
            case 'a': {
                move--;
                for (int i = LENGTH-1; i >= 0; i--) { // 0 .. 49
                    for (int j = 0; j < WIDTH; j++) { // 0 .. 79
                        if ((field[i*WIDTH+j] == 2) && (((field[(i+1)*WIDTH+j]) != 1) && ((field[(i+1)*WIDTH+j]) != 2))) {
                            field[i*WIDTH+j] = 0;
                            field[(i+1)*WIDTH+(j+move)] = 2;
                            clear();
                            output_field(field);
                            printw("\n%d\n", j);
                        }
                    }
                }
            } break;
            case 'd': {
                move++;
                for (int i = LENGTH-1; i >= 0; i--) { // 0 .. 49
                     for (int j = WIDTH-1; j >= 0; j--) { // 0 .. 79
                        if ((field[i*WIDTH+j] == 2) && (((field[(i+1)*WIDTH+j]) != 1) && ((field[(i+1)*WIDTH+j]) != 2))) {
                            field[i*WIDTH+j] = 0;
                            field[(i+1)*WIDTH+(j+move)] = 2;
                            clear();
                            output_field(field);
                            printw("\n%d\n", j);
                        }
                    }
                }
            } break;
            default: {
                move = 0;
                for (int i = LENGTH-1; i >= 0; i--) { // 0 .. 49
                    for (int j = 0; j < WIDTH; j++) { // 0 .. 79
                        if ((field[(i+1)*WIDTH+j] == 2)) {
                                turn_figutes(field);
                                flag++;
                            } else {
                            if ((field[i*WIDTH+j] == 2) && (((field[(i+1)*WIDTH+j]) != 1) 
                                && ((field[(i+1)*WIDTH+j]) != 2)) && (field[(i+1)*WIDTH+j]) != 3) {
                                field[i*WIDTH+j] = 0;
                                field[(i+1)*WIDTH+(j+move)] = 2;
                                clear();
                                output_field(field);
                                printw("\n%d\n", j);
                            }
                        }
                    }
                }
            } break;
        }
        
    }
}

void turn_figutes (int *field) {
    for (int i = LENGTH-1; i >= 0; i--) { // 0 .. 49
            for (int j = WIDTH-1; j >= 0; j--) {
                if (field[i*WIDTH+j] == 2) {
                    field[i*WIDTH+j] = 3;
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
                case 1: printw("."); break;
                case 2: printw("2"); break;
                case 3: printw("3"); break;
                case 0: printw(" "); break;
                default:break;
            }
        }
        printw("\n");
    }
}

void pausedelay(int milli_seconds) {
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds) {}
}
