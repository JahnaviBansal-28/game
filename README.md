Lane-Dodging Game – My Analysis & Modifications

This project is a small C-based console game where you move a player left/right to avoid a falling obstacle. The whole thing runs inside the Windows console, so it mainly relies on clearing and redrawing the screen very quickly to create the illusion of movement.

1. Main Idea of the Game

The game has three lanes (left, middle, right).
An obstacle appears at the top in one of these lanes and keeps moving downward every frame.
The player sits at the bottom and can shift between the three lanes using the left and right arrow keys.

If the obstacle reaches the bottom and both share the same lane → the game ends.

The loop keeps running until this collision happens.

2. Libraries Used & Platform

The program includes:

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>


conio.h and windows.h make it work only on Windows (because of getch(), _kbhit(), Sleep, and system("cls")).

3. Important Variables in the Game
int x = 1;              // Player lane (0,1,2)
int step = 0;           // Which row the obstacle is on
int obstaclePos = rand() % 3;   // Lane of the obstacle


x → where the player is currently standing

step → how far the obstacle has travelled vertically

obstaclePos → randomly chosen lane for the upcoming obstacle

The entire game is basically these three values changing inside an infinite loop.

4. How the Main Game Loop Works

The gameplay loop does four things repeatedly:

Reads player input

Draws the screen

Checks collision

Moves the obstacle and updates variables

4.1 Input Handling
if (_kbhit()) {
    char ch = getch();
    if (ch == 75 && x > 0) x--;   // left arrow
    if (ch == 77 && x < 2) x++;   // right arrow
}


_kbhit() only checks if a key was pressed (non-blocking).

getch() reads the key immediately.

Using ASCII codes:

75 → left arrow

77 → right arrow

This keeps the player inside lanes 0–2.

4.2 Drawing Everything on the Screen

First the console is cleared:

system("cls");


Then a small border is printed, followed by 10 rows representing the path.

When i == step, we print the obstacle in its current lane:

if (i == step) {
    // print obstacle in the correct lane
}
else {
    // print empty row
}


After these 10 rows, the player is drawn on the bottom lane depending on x.

So the screen layout each frame is:

Top border

10 falling rows (one of them may contain the obstacle)

Bottom row with the player

4.3 Collision Check
if (step == 10 && x == obstaclePos) {
    printf("GAME OVER!");
    break;
}


Once the obstacle reaches row 10 (the player row), if both the player and obstacle are in the same lane → game ends.

4.4 Moving the Obstacle
Sleep(120);
step++;


Each frame:

The game pauses for ~120 ms

The obstacle moves one row downward

After it goes off-screen:

if (step > 10) {
    step = 0;
    obstaclePos = rand() % 3;
}


This creates an endless cycle of new obstacles.

5. Quick Summary of the Game Flow

Every frame:

Check for left/right input

Clear console

Draw border, obstacle row, empty rows, and player

Print score

Detect collision

Move obstacle downward

Reset obstacle when needed

6. Modifications I Implemented

For the assignment, I picked two enhancements:

✔️ 1. Score System

I added a score variable that increases every time an obstacle reaches the bottom without hitting the player.

The score is displayed on screen during gameplay:

printf("Score: %d    High Score: %d\n", score, highScore);


This makes the game more engaging because you can track how long you’ve survived.

✔️ 2. High Score Saving (File Handling)

I introduced a highScore variable that is stored permanently in a file called highscore.txt.

Reading the high score at the start:
FILE *f = fopen("highscore.txt", "r");
if (f != NULL) {
    fscanf(f, "%d", &highScore);
    fclose(f);
}

Updating it when the game ends:
if (score > highScore) {
    f = fopen("highscore.txt", "w");
    fprintf(f, "%d", score);
    fclose(f);
}


This lets the game remember the best score even if the program is closed and reopened.

7. Why These Features Improve the Game

Score adds a sense of progression

High score gives long-term motivation

Combining these makes the game feel more complete without making the code too complicated