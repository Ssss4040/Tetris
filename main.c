#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>

#define WIDTH 18
#define LENGTH 20
#define TOP 0
#define LEFT 0
#define SPEED_UPDATE_FIELD 150000

void start_field(int *field);
int sample_figures(int *field, int *list_figures);
void figures_field(int *field, int *list_figures, int *speed_update);
void output_field(int *field);
void pausedelay(int *milli_seconds);
void turn_figutes(int *field);
void move_left(int *field);
void move_right(int *field);
void move_down(int *field);
int check_down_figure(int *field);
void check_fill_width(int *field);
int check_move_figure(int *field, int move);
int figure_O(int *field);
int figure_J(int *field);
int figure_Z(int *field);
int figure_T(int *field);
int figure_S(int *field);
int figure_L(int *field);
int figure_I(int *field);

int main() {
    // initscr();
    // savetty();
    // nonl();
    // cbreak();
    // noecho();
    // timeout(0);
    // leaveok(stdscr, TRUE);
    // curs_set(0);
    int speed_update = SPEED_UPDATE_FIELD;
    int field[LENGTH][WIDTH];
    int list_figures = 0;

    start_field(&field[0][0]);

        figures_field(&field[0][0], &list_figures, &speed_update);
        //output_field(&field[0][0]);
        //pausedelay(150000);
    
    // pausedelay(1000000);
    // curs_set(1);
    // clear();
    // refresh();
    // resetty();
    // endwin();
    // exit(0);
    return 0;
}

void start_field(int *field) {
    
    for (int i = 0; i < LENGTH; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == TOP || j == LEFT 
            || j == (WIDTH-1)  || i == (LENGTH-1))
                field[i*WIDTH+j] = 1;
            else field[i*WIDTH+j] = 0;
        }
    }
}

 int sample_figures(int *field, int *list_figures) {
    int flag = 0;
    switch (0) {
        case 0: {
            flag = figure_O(field);
            (*list_figures)++;
            } break;
        case 1: {
            flag = figure_J(field);
            (*list_figures)++;
        }break;
        case 2: {
            flag = figure_Z(field);
            (*list_figures)++;
        }break;
        case 3: {
            flag = figure_T(field);
            (*list_figures)++;
        }break;
        case 4: {
            flag = figure_S(field);
            (*list_figures)++;
        }break;
        case 5: {
            flag = figure_L(field);
            (*list_figures)++;
        }break;
        case 6: {
            flag = figure_I(field);
            *list_figures = 0;
        }break;
        default: break;
    }
    return flag;
 }

void figures_field(int *field, int *list_figures, int *speed_update) {
    *speed_update = SPEED_UPDATE_FIELD;

    while (sample_figures(field, list_figures) == 0) {
        char vvv;
        while (check_down_figure(field) == 0) {
            pausedelay(speed_update);
            scanf("%c", &vvv);
            switch (vvv) {
                case 'a': {
                    move_left(field);
                } break;
                case 'd': {
                    move_right(field);
                } break;
                case 's': {
                    (*speed_update) /= 2;
                    move_down(field);
                } break;
                case '\n': {
                    move_down(field);
                }
                default: {
                } break;
            }
            output_field(field);
        }
        turn_figutes(field);
        check_fill_width(field);
    }
}

int check_down_figure(int *field) {
    int stop_figure = 0;
    for (int i = LENGTH-1; i >= 0; i--) { // 0 .. 49
            for (int j = WIDTH-1; j >= 0; j--) {// 0 .. 79
                if (field[i*WIDTH+j] == 2) {
                    if ((field[(i+1)*WIDTH+j] == 1) 
                    || (field[(i+1)*WIDTH+j] == 3)) {
                        stop_figure = 1;
                    }
                }
            }
        }
    return stop_figure;
}

void check_fill_width(int *field) {
    int count = 0;
    for (int i = TOP+1; i < LENGTH; i++) { // 20
        count = 0;
        for (int j = WIDTH-1; j >= LEFT+1; j--) { // 18
            if (field[i*WIDTH+j] == 3) {
                count++;
            }
        }
        if (count == ((WIDTH-1)-(TOP+1))) {
            for (int tmp = i; tmp > 2; tmp--) {
                for (int j = WIDTH-2; j >= LEFT+1; j--) {
                    if(field[(tmp)*WIDTH+(j)] != 1) {
                        field[(tmp)*WIDTH+(j)] = field[(tmp-1)*WIDTH+j];
                    }
                    field[(tmp-1)*WIDTH+(j)] = 0;
                }
            }
        }
    }
}

void move_left(int *field) {
    int move = 0;
    move--;
    if ((check_move_figure(field, move) == 0))
    for (int i = LENGTH-1; i >= 0; i--) { // 0 .. 49
        
        for (int j = 0; j < WIDTH; j++) { // 0 .. 79
            if ((field[(i)*WIDTH+j] == 2)) {
                field[i*WIDTH+j] = 0;
                field[(i+1)*WIDTH+(j+move)] = 2;
            }
        }
    }
}

void move_right(int *field) {
    int move = 0;
    move++;
    if (check_move_figure(field, move) == 0)
    for (int i = LENGTH-1; i >= 0; i--) { // 0 .. 49
     
        for (int j = WIDTH-1; j >= 0; j--) { // 0 .. 79
            if ((field[(i)*WIDTH+j] == 2)) {
                field[i*WIDTH+j] = 0;
                field[(i+1)*WIDTH+(j+move)] = 2;
            }
        }
    }
}

int check_move_figure(int *field, int move) {
    int flag = 0;
    for (int i = LENGTH-1; i >= 0; i--) { // 0 .. 49
        for (int j = 0; j < WIDTH; j++) { // 0 .. 79
            if ((field[(i)*WIDTH+j] == 2) 
            && (field[(i+1)*WIDTH+(j+move)] != 2) 
            && (field[(i+1)*WIDTH+(j+move)] != 0)) {
                if (field[(i+1)*WIDTH+(j+move)] != 0)
                    flag = 1;
            }
        }          
    }
    return flag;
}

void move_down(int *field) {
    int move = 0;
    for (int i = LENGTH-1; i >= 0; i--) { // 0 .. 49
        for (int j = 0; j < WIDTH; j++) { // 0 .. 79
            if ((field[(i)*WIDTH+j] == 2)) {
                field[i*WIDTH+j] = 0;
                field[(i+1)*WIDTH+(j+move)] = 2;
            }
        }          
    }
}


void turn_figutes (int *field) {
    for (int i = LENGTH-1; i >= 0; i--) { // 0 .. 49
            for (int j = WIDTH-1; j >= 0; j--) {
                if ((field[i*WIDTH+j] == 2)) {
                    field[i*WIDTH+j] = 3;
                }
            }
    }
}

void output_field(int *field) {
    for (int i = 0; i < LENGTH; i++) {
        for (int j = 0; j < WIDTH; j++) {
            switch (field[i*WIDTH+j]) {
                // case 1: printw("."); break;
                // case 2: printw("2"); break;
                // case 3: printw("3"); break;
                // case 0: printw("."); break;
                case 1: printf("1"); break;
                case 2: printf("2"); break;
                case 3: printf("3"); break;
                case 0: printf("."); break;
                
                default:break;
            }
        }
        // printw("\n");
        printf("\n");
    }
}

int figure_O(int *field) {
    int flag = 0;
    if ((field[1*WIDTH+(WIDTH/2)] == 0) &&
        (field[1*WIDTH+(WIDTH/2-1)] == 0) &&
        (field[2*WIDTH+(WIDTH/2)] == 0) && 
        (field[2*WIDTH+(WIDTH/2-1)] == 0)) {
            field[1*WIDTH+(WIDTH/2)] = 2; // ##
            field[1*WIDTH+(WIDTH/2-1)] = 2; // ##
            field[2*WIDTH+(WIDTH/2)] = 2;
            field[2*WIDTH+(WIDTH/2-1)] = 2; 
        } else {
            flag = 1;
        }
    return flag;
}

int figure_J(int *field) {
    int flag = 0;
    if ((field[1*WIDTH+(WIDTH/2-1)] == 0) &&
    (field[2*WIDTH+(WIDTH/2-1)] == 0) &&
    (field[3*WIDTH+(WIDTH/2-1)] == 0) &&
    (field[3*WIDTH+(WIDTH/2-2)] == 0)) {
        field[1*WIDTH+(WIDTH/2-1)] = 2; //  #
        field[2*WIDTH+(WIDTH/2-1)] = 2; //  #
        field[3*WIDTH+(WIDTH/2-1)] = 2; // ##
        field[3*WIDTH+(WIDTH/2-2)] = 2;
    } else {
        flag = 1;
    }
    return flag;
}

int figure_Z(int *field) {
    int flag = 0;
    if ((field[1*WIDTH+(WIDTH/2-1)] == 0) &&
    (field[1*WIDTH+(WIDTH/2)] == 0) &&
    (field[2*WIDTH+(WIDTH/2)] == 0) &&
    (field[2*WIDTH+(WIDTH/2+1)] == 0)) {
        field[1*WIDTH+(WIDTH/2-1)] = 2; // ##
        field[1*WIDTH+(WIDTH/2)] = 2;   //  ##
        field[2*WIDTH+(WIDTH/2)] = 2;
        field[2*WIDTH+(WIDTH/2+1)] = 2;
    } else {
        flag = 1;
    }
    return flag;
}

int figure_T(int *field) {
    int flag = 0;
    if ((field[1*WIDTH+(WIDTH/2)] == 0) &&
    (field[2*WIDTH+(WIDTH/2-1)] == 0) &&
    (field[2*WIDTH+(WIDTH/2)] == 0) &&
    (field[2*WIDTH+(WIDTH/2+1)] == 0)) {
        field[1*WIDTH+(WIDTH/2)] = 2;   //  #
        field[2*WIDTH+(WIDTH/2-1)] = 2; // ###
        field[2*WIDTH+(WIDTH/2)] = 2;
        field[2*WIDTH+(WIDTH/2+1)] = 2;
    } else {
        flag = 1;
    }
    return flag;
}

int figure_S(int *field) {
    int flag = 0;
    if ((field[1*WIDTH+(WIDTH/2)] == 0) &&
    (field[1*WIDTH+(WIDTH/2+1)] == 0) &&
    (field[2*WIDTH+(WIDTH/2)] == 0) &&
    (field[2*WIDTH+(WIDTH/2-1)] == 0)) {
        field[1*WIDTH+(WIDTH/2)] = 2;   //  ##
        field[1*WIDTH+(WIDTH/2+1)] = 2; // ##
        field[2*WIDTH+(WIDTH/2)] = 2;
        field[2*WIDTH+(WIDTH/2-1)] = 2;
    } else {
        flag = 1;
    }
    return flag;
}

int figure_L(int *field) {
    int flag = 0;
    if ((field[1*WIDTH+(WIDTH/2)] == 0) && 
    (field[2*WIDTH+(WIDTH/2)] == 0) &&
    (field[3*WIDTH+(WIDTH/2)] == 0) &&
    (field[3*WIDTH+(WIDTH/2+1)] == 0)) {
        field[1*WIDTH+(WIDTH/2)] = 2;   // # 
        field[2*WIDTH+(WIDTH/2)] = 2;   // #
        field[3*WIDTH+(WIDTH/2)] = 2;   // ##
        field[3*WIDTH+(WIDTH/2+1)] = 2;
    } else {
        flag = 1;
    }
    return flag;
}

int figure_I(int *field) {
    int flag = 0;
    if ((field[1*WIDTH+(WIDTH/2)] == 0) && 
    (field[2*WIDTH+(WIDTH/2)] == 0) &&
    (field[3*WIDTH+(WIDTH/2)] == 0) &&
    (field[4*WIDTH+(WIDTH/2)] == 0)) {
        field[1*WIDTH+(WIDTH/2)] = 2;   // # 
        field[2*WIDTH+(WIDTH/2)] = 2;   // #
        field[3*WIDTH+(WIDTH/2)] = 2;   // #
        field[4*WIDTH+(WIDTH/2)] = 2;   // #
    } else {
        flag = 1;
    }
    return flag;
}

void pausedelay(int *milli_seconds) {
    clock_t start_time = clock();
    while (clock() < start_time + *milli_seconds) {}
}
