#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

#define HIGHSCORE_FILE "highscore.txt"

int main() {
    srand(time(0));

    int x = 1;                    // player position (0 to 2)
    int step = 0;                 // obstacle vertical movement (row index)
    int obstaclePos = rand() % 3; // 0,1,2 lane

    int score = 0;                // current score
    int highScore = 0;            // best score stored in file
    FILE *f = NULL;

    // load highscore from file
    f = fopen(HIGHSCORE_FILE, "r");
    if (f != NULL) {
        fscanf(f, "%d", &highScore);
        fclose(f);
    } else {
        highScore = 0;
    }

    while (1) {

        // ---- INPUT ----
        if (_kbhit()) {
            char ch = getch();

            if (ch == 75 && x > 0)        // LEFT arrow
                x--;

            if (ch == 77 && x < 2)        // RIGHT arrow
                x++;
        }

        // ---- DRAW ----
        system("cls");
        printf("|--- --- ---|\n");

        for (int i = 0; i < 10; i++) {
            if (i == step) {

                if (obstaclePos == 0)
                    printf("| %c        |\n", 1);

                else if (obstaclePos == 1)
                    printf("|     %c    |\n", 1);

                else if (obstaclePos == 2)
                    printf("|        %c |\n", 1);

            } else {
                printf("|           |\n");
            }
        }

        // ---- PLAYER ----
        if (x == 0)
            printf("| %c        |\n", 6);
        else if (x == 1)
            printf("|     %c    |\n", 6);
        else if (x == 2)
            printf("|        %c |\n", 6);

        // ---- SCORE DISPLAY ----
        printf("Score: %d    High Score: %d\n", score, highScore);

        // ---- COLLISION ----
        if (step == 10 && x == obstaclePos) {
            printf("\nGAME OVER!\n");
            printf("Your Score: %d\n", score);

            // update highschore if needed
            if (score > highScore) {
                highScore = score;
                printf("New High Score!\n");

                f = fopen(HIGHSCORE_FILE, "w");
                if (f != NULL) {
                    fprintf(f, "%d", highScore);
                    fclose(f);
                }
            } else {
                printf("High Score: %d\n", highScore);
            }

            break;
        }

        Sleep(120);

        // Move obstacle down
        step++;

        // Reset when reaches bottom (no collision) → increase score
        if (step > 10) {
            step = 0;
            obstaclePos = rand() % 3; // new lane
            score++;                  // successfully dodged one obstacle
        }
    }

    return 0;
}
