# Console Lane-Dodging Game – Code Analysis

This repository contains a simple console-based lane-dodging game written in C for Windows.  
The player controls a character at the bottom of the screen and must avoid incoming obstacles falling from the top in one of three lanes.

---

## 1. Overall Game Idea

- The game has **3 horizontal lanes**: left, middle, right.
- A single **obstacle** spawns at the top in a random lane and moves **down one row each frame**.
- The **player** stays at the bottom and can move left or right using the **arrow keys**.
- If the obstacle reaches the bottom **in the same lane** as the player, the game ends with **"GAME OVER!"**.

The game runs in an infinite loop until a collision happens.

---

## 2. Dependencies and Platform

The program uses:

```c
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

Important Variables
int x = 1;              // Player position: 0 = left, 1 = middle, 2 = right
int step = 0;           // Obstacle's vertical position (row index)
int obstaclePos = rand() % 3;   // Lane of the obstacle: 0, 1, or 2


x: represents which lane the player is currently in.

step: represents how far down the obstacle has moved (from top to bottom).

obstaclePos: represents in which lane (0, 1, or 2) the obstacle is spawned.

All game logic is controlled using these three variables inside a while(1) game loop.

4. Game Loop Structure

The main game loop repeatedly performs these steps:

Input Handling

Drawing the Scene

Collision Detection

Updating Obstacle Position

4.1 Input Handling
if (_kbhit()) {
    char ch = getch();

    if (ch == 75 && x > 0)        // LEFT arrow
        x--;

    if (ch == 77 && x < 2)        // RIGHT arrow
        x++;
}


_kbhit() checks if a key has been pressed without stopping the program.

getch() reads the pressed key.

Key code 75: left arrow → move player one lane to the left (if not already at lane 0).

Key code 77: right arrow → move player one lane to the right (if not already at lane 2).

This ensures the player stays within the valid lane range [0, 2].

4.2 Drawing the Scene

First, the console is cleared and a top border is printed:

system("cls");
printf("|--- --- ---|\n");


Then, 10 rows of the "road" are printed:

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


If i == step, the obstacle is drawn in its lane using the %c placeholder with character 1.

Otherwise, an empty lane row is printed.

Finally, the player is drawn in the bottom row:

if (x == 0)
    printf("| %c        |\n", 6);
else if (x == 1)
    printf("|     %c    |\n", 6);
else if (x == 2)
    printf("|        %c |\n", 6);


The player is displayed in the lane indicated by x using the %c placeholder with character 6.

In total, the display shows:

Top border

10 rows of road with (possibly) the falling obstacle

1 bottom row with the player

4.3 Collision Detection
if (step == 10 && x == obstaclePos) {
    printf("\nGAME OVER!\n");
    break;
}


When step == 10, the obstacle has reached the player's row.

If at that moment x == obstaclePos, both are in the same lane → collision.

The game prints "GAME OVER!" and exits the loop.

4.4 Obstacle Movement and Reset
Sleep(120);
step++;

if (step > 10) {
    step = 0;
    obstaclePos = rand() % 3; // new lane
}


Sleep(120) slows the loop to make the game playable.

step++ moves the obstacle one row down.

When the obstacle goes beyond the bottom row (step > 10) and no collision occurred:

step is reset to 0 (top row).

A new random lane is chosen for obstaclePos.

This creates the repeating cycle of new obstacles falling toward the player.

5. Flow Summary

High-level logic per frame:

Check if player pressed left/right → update x.

Clear the screen and redraw:

Border

Obstacle at its current row (step) and lane (obstaclePos)

Player at bottom lane (x)

If obstacle is at the player's row and lane → Game Over.

Wait 120 ms.

Move obstacle down one row (step++).

If obstacle goes past bottom without collision → reset it at top with a new random lane.

6. Observations and Possible Improvements

The game currently:

Has no scoring system.

Does not increase difficulty over time.

Exits immediately after the first collision.

It is platform-dependent:

Uses conio.h, windows.h, Sleep, and system("cls").

Possible improvements:

Add a score based on how many obstacles were dodged.

Gradually decrease Sleep() duration to make it faster.

Add a restart option instead of exiting on Game Over.

Replace system("cls") with a more efficient rendering method to reduce screen flicker.

---

## 7. Implemented Modifications

For Objective 2, the following features were added to the game:

### 7.1 Score System

- A new integer variable `score` was introduced to track how many obstacles the player successfully dodges.
- Every time an obstacle travels from the top of the screen to the bottom **without colliding** with the player, the score is increased by 1.
- The current score is displayed on the screen during gameplay:

```c
int score = 0;
printf("Score: %d    High Score: %d\n", score, highScore);

This gives the player immediate feedback on their performance and rewards surviving longer.

7.2 High Score Storage Using File Handling

A highScore variable was added to track the best score across multiple runs of the game.

The high score is stored in a simple text file named highscore.txt.

Loading the High Score

At the start of the program, the game tries to read a previously saved high score:

int highScore = 0;
FILE *f = fopen("highscore.txt", "r");
if (f != NULL) {
    fscanf(f, "%d", &highScore);
    fclose(f);
}


If the file exists, the value is read and used as the initial highScore.

If the file does not exist, the highScore is initialized to 0.

Updating and Saving the High Score

When the game ends, the final score is compared to the stored high score:

if (score > highScore) {
    highScore = score;
    f = fopen("highscore.txt", "w");
    if (f != NULL) {
        fprintf(f, "%d", highScore);
        fclose(f);
    }
}


If the current score is greater than highScore, it is treated as a new high score.

The new high score is written back into highscore.txt using file handling.

A message is displayed to inform the player that they achieved a new high score.

Displaying Score and High Score

During gameplay, both the current score and the high score are displayed:

printf("Score: %d    High Score: %d\n", score, highScore);


This makes the game more engaging by:

Showing immediate progress (score),

Encouraging players to beat their previous best (high score),
Persisting progress across multiple game sessions using file handling.