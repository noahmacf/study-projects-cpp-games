// Snake Game

#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <ncurses.h>
#include <curses.h>
#include <stdio.h>
#include <iomanip>

using namespace std;

// Initializes variables
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;
bool gameOver;
bool inCorner
;

// Declares Functions
    // Sets up game
void Setup();
    // Draws the border, DrawInside() is inside for loop
void DrawBorder();
    // Draws inside of border, snake and fruit, within DrawBorder() for loop
void DrawInside(int i, int j);
    // Allows key input to be read, used in Input()
int khbit(void);
    // Reacts to key presses evaluated in khbit()
void Input();
    // 
void Logic();

// Main function
int main()
{
    Setup();
    using namespace std::this_thread;
    using namespace std::chrono;
    while(!gameOver)
    {
        DrawBorder();
        Input();
        Logic();
        //sleep_for(seconds(2));
    }

    return 0;
}

void Setup()
{
    gameOver = false;
    dir = STOP;
    score = 0;
    // Snake Start Position
    x = width / 2;
    y = height / 2;
    // Fruit start position
    srand(static_cast<unsigned int>(time(0)));
    fruitX = rand() % (width - 3);
    fruitY = rand() % (height - 3);
    
    // Welcomes player
    string input = "";
    while(input != "continue" && input != "quit")
    {
        cout << "Welcome to the snake game!\n";
        cout << "Please enter continue to start playing or quit to exit: ";
        cin >> input;
        cout << "\n";
        if (input == "quit")
        {
            gameOver = true;
        }
    }
}
void DrawBorder()
{
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

    // Print the top border
    for (int i = 0; i < width; i++)
    {
        cout << "#";
    }
    cout << "\n";

    // Print the side border, snake, and fruit
    for (int i = 0; i < (height - 2); i++)
    {
        cout << "#";
        for (int j = 0; j < (width - 2); j++)
        {
            DrawInside(i, j);
        }
        cout << "#\n";
    }

    // Print the bottom border
    for (int i = 0; i < width; i++)
    {
        cout << "#";
    }
    cout << "\n" << left << "#" << "Score: " << setw(11) << score << "#\n";
    for (int i = 0; i < width; i++)
    {
        cout << "#";
    }
    cout << "\n";
}
void DrawInside(int i, int j)
{
    if (i == y && j == x)
    {
        cout << "O";
    }
    else if (i == fruitY && j == fruitX)
    {
        cout << "F";
    }
    else
    {
        bool print = false;
        for (int k = 0; k < nTail; k++)
        {
            if(tailX[k] == j && tailY[k] == i)
            {
                if (!inCorner)
                {
                    cout << "o";
                    print = true;
                }
                else
                {
                    cout << " ";
                }
            }
        }
        if (!print && !inCorner)
        {
            cout << " ";
        }
        inCorner = false;
    }
    
}
int kbhit(void)
{
    int ch = getchar();

    if (ch != ERR) {
        //ungetch(ch);
        return 1;
    } else {
        return 0;
    }
}
void Input()
{
    if (kbhit())
    {
        switch(getchar())
        {
            case 'w':
            {
                dir = UP;
                break;
            }
            case 'a':
            {
                dir = LEFT;
                break;
            }
            case 's':
            {
                dir = DOWN;
                break;
            }
            case 'd':
            {
                dir = RIGHT;
                break;
            }
            case 'x':
            {
                gameOver = true;
                break;
            }
        }
    }
}
void Logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch(dir)
    {
        case UP:
        {
            y--;
            break;
        }
        case LEFT:
        {
            x--;
            break;
        }
        case DOWN:
        {
            y++;
            break;
        }
        case RIGHT:
        {
            x++;
            break;
        }
        default:
        {
            break;
        }
    }
    // Checks if snake goes outside border
    if (x > (width - 1) || x < 0 || y > (height - 1) || y < 0)
    {
        gameOver = true;
    }
    if (x >= (width - 2)) x = 0; else if (x <= 0) x = width - 3;
    if (y >= (height - 2)) y = 0; else if (y <= 0) y = height - 3;
    // Kills snake if it eats its own tail
    for (int i = 0; i < nTail; i++)
    {
        if (tailX[i] == x && tailY[i] == y)
        {
            gameOver = true;
        }
    }
    // Checks if snake has eaten the fruit, it increases the tail
    if (x == fruitX && y == fruitY)
    {
        score += 10;
        fruitX = rand() % (width - 3);
        fruitY = rand() % (height - 3);
        nTail++;
        inCorner = true;
    }
}