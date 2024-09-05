#include <iostream>
#include <chrono>
#include <thread>
#include <ncurses.h>

bool gameOver;
const int height = 10;
const int width = 30;
using namespace std;

int x, y, fruitX, fruitY;
int tailX[100], tailY[100];
int nTail;

int score = 0;
enum eDirection { STOP = 0, UP, DOWN, LEFT, RIGHT };
eDirection dir;


void Setup() {
    gameOver = false;
    x = width /2;
    y = height /2;

    fruitX = 1 + rand() % (width - 2); // makes fruitX stay between 1 and width - 1

    fruitY = 1 + rand() % (height - 2);// makes fruitX stay between 1 and height - 1
    dir = STOP;
    nTail = 0;

}
void Draw() {
    mvprintw(0, 0, "Score: %d \n", score);  // Print score
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {

            if (j == width - 1) {
                printw("#\n");
            }
            else if (i == y && j == x) {
                printw("O");
            }
            else if (i == fruitY && j == fruitX) {
                printw("x");
            }
            else if (i == 0 || i == height - 1 || j == 0) {
                printw("#");
            }
            else {
                if (nTail>0) {
                    bool printed = false;
                    for (int k = 0; k < nTail; k++) {
                        if (i == tailY[k] && j == tailX[k]) {
                            printed = true;
                            printw("o");
                        }
                    }
                    if (!printed) {
                        printw(" ");
                    }
                }
                else {
                    printw(" ");
                }

            }

        }
    }

    refresh();
}
void Input(){
        switch (getch()) {
            case KEY_UP:
                dir = UP;

            break;
            case KEY_DOWN:
                dir = DOWN;
            break;
            case KEY_LEFT:
                dir = LEFT;
            break;
            case KEY_RIGHT:
                dir = RIGHT;
            break;
            case 'x':
                gameOver = true;
            break;
            default:
                break;
        }
}
void Move() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++) {
        int prev2X = tailX[i];
        int prev2Y = tailY[i];
        tailX[i] = prevX; ;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir) {
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case STOP:
            break;
    }
    if (x == 0 || y == 0 || x == width - 1 || y == height - 1) {
        gameOver = true;
    }
}
void Logic() {
    if (x == fruitX && y == fruitY) {
        srand(time(nullptr));
        fruitX = 1 + rand() % (width - 2); // makes fruitX stay between 1 and width - 1
        fruitY = 1 + rand() % (height - 2);
        score++;
        if (score % 2 ==0 && score != 0) {
            nTail++;
        }
    }
}
int main() {

    initscr();               // Start ncurses mode
    keypad(stdscr, TRUE);     // Enable function keys (F1, arrow keys, etc.)
    noecho();                 // Don't echo user input
    cbreak();                 // Disable line buffering (input available immediately)
    nodelay(stdscr, TRUE);

    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Move();
        Logic();
        this_thread::sleep_for(chrono::milliseconds(250));
    }
    endwin();  // End ncurses mode

    return 0;
}
