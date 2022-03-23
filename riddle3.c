/****************************************************************************************************
NUMBER PUZZLE GAME

Danielle Nguyen
104386103

Player picks the size of the game board and the program will generate a new grid with a random 
pattern of numbers and a blank space. Player must slide a tile into the blank space one by one with
the goal of putting all the numbers in the correct order.
*****************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//FUNCTIONS
int getDimension(int dimension);                            //function prototype: get row/column dimensions from user
int makeArray(int size, int array[]);                       //function prototype: make array of size row*column and fill with numbers from 1 to size
int gameGrid(int row, int column, int array[]);             //function prototype: turns 1D array to 2D table and prints on screen
int getSelection(int size);                                 //function prototype: get user input for tile to slide into blank space
int indexFind(int array[], int size, int locateValue);      //function prototype: locate index of interest (blank or user selected)
int tileCheck(int xb, int yb, int xs, int ys);              //function prototype: checks if user selected tile is adjacent to blank tile

//GLOBAL VARIABLES FOUND IN THE PROGRAM
int input;          //validates scanf returns
int selectedN;      //Input: number player wants to move
int swap;           //tracks if numbers in array are in order

int main(void)
{
    //WELCOME PROMPT
    puts("Welcome to the Number Riddle Game!");

    int i;              //general array index
    int blankIndex;     //array index storing blank (0)
    int selectedIndex;  //array index storing user selected input
    
    srand(time(NULL));  //generates a unique random number pattern everytime the program is run

    //GAME LOOP (START = 1 TO ENTER GAME)
    int start = 1;      //variable to enter game loop
    do
    {
        //PROMPT USER FOR GRID SIZE (# OF ROWS AND COLUMNS)
        int row = 0; //User input for number of rows on grid
        puts("How many rows do you want to play with? (Enter 3-8)");
        row = getDimension(row);

        puts("Great!");

        int column = 0; //User input for number of columns on grid 
        puts("How many columns do you want to play with? (Enter 3-8)");       
        column = getDimension(column);
        
        //Test: printf("Rows: %d\n", row);
        //Test: printf("Columns: %d\n", column);

    
        //GENERATE ARRAY OF NUMBERS TO FILL GAME GRID (RANGE FROM 0 (BLANK) TO SIZE OF GRID) 
        int size = row*column;                      //maximum size of grid = maximum size of number array
        int array[size];                            //define array 
        array[size] = makeArray(size, array);       //make array to hold numbers of the game board

        //SHUFFLE NUMBERS IN ARRAY
        for (int i = 0; i < size; i++)
        {
            int a = array[i];
            int newIndex = rand() % size;
            array[i] = array[newIndex];
            array[newIndex] = a;
        }
        
        //OUTPUT LOOP: GENERATE AND PRINT GAME GRID OF SIZE (ROW x COLUMN) AND WITH RANDOM NUMBER ORDER FROM ARRAY
        puts("\nHere's your game board:");
        gameGrid(row, column, array);                   //make and display game grid
            
        //GAME START: LOOP FOR MOVING TILES AND TRACKING # OF MOVES
        int moves = 0; //initialize moves counter
        printf("\nMoves: %d\n\n", moves);
        
        do
        {
            //Prompt user to select tile to slide into blank space
            puts("Which number would you like to slide? [Or enter 0 to exit game]");
            int selectedN = getSelection(size);
            if(selectedN == 0)                                                      //Checks if user wants to exit game (Entered 0)
            {
                start = 0;
                break;
            }

            //Scan array to retrieve index storing blank (value 'size')
            int blankIndex = indexFind(array, size, size);

            //Scan array to retrieve index storing value that matches user selected input (selectedN)
            int selectedIndex = indexFind(array, size, selectedN);

            //Determine x,y coordinate location of blank index
            int xb; //column location of blank index
            int yb; //row location of blank index
            for(int r = 0; r < row; r++)
            {
                for(int c = 0; c < column; c++)
                {
                    if((r * column + c) == blankIndex)
                    {
                        xb = c;
                        yb = r;
                        //Test: printf("xb is %d and yb is %d\n", xb, yb);
                        break;
                    }
                }
            }
           
            //Determine x,y coordinate location of selectedN index
            int xs; //column location of blank index
            int ys; //row location of blank index
            for(int r = 0; r < row; r++)
            {
                for(int c = 0; c < column; c++)
                {
                    if((r * column + c) == selectedIndex)
                    {
                        xs = c;
                        ys = r;
                        //Test: printf("xs is %d and ys is %d\n", xs, ys);
                        break;
                    }
                }
            }

            swap = -1; 

            if(tileCheck(xb, yb, xs, ys) == 1)                          //Check validity of selected tile: Is it adjacent to blank tile?
            {
                int slideToSelected = array[blankIndex];                //If yes, swap them
                int slideToBlank = array[selectedIndex];
                array[blankIndex] = slideToBlank;
                array[selectedIndex] = slideToSelected;
                moves++;

                for(int i = 1 ; i < size ; i++)                         //Then check if numbers are in correct order via bubble sort
                {
                    swap = 0;
                    if(array[i] < array[i-1])
                    {
                        swap++;
                        //Test: printf("Swap: %d\n", swap);
                        break;
                    }
                }
            }
            else                                                        //If no, user did not select a tile adjacent to the blank. Pick another.
            {
                puts("Sorry, invalid move.");
                continue;
            }
        
            //UPDATE GAME GRID AND # OF MOVES
            i = 0;
            gameGrid(row, column, array);                               //Display new game grid
            printf("\nMoves: %d\n\n", moves);                           //Displays how many moves the player has made  

        } while(swap != 0 || input != 1 || selectedN < 1 || selectedN > (size -1));         
        //Conditions to repeat game loop: Repeat if (1) numbers are not in order, or (2) scanf does not receive a valid input, or (3) input is not within valid range                                       

        /*END OF GAME: BREAK OUT OF GAME LOOP
        Upon breaking out of game loop:
        First check if user entered 0 to exit game (ie. Did player quit?):
        If yes, player quit: break out of loop completely*/
        if(selectedN == 0)                                                                  
        {
            start = 0;
            break;
        }
        
        /*Second check if tiles were in correct order to break the loop (ie. Did player win?):
        If yes, player won: Congratulate player and ask to play again*/
        if(swap == 0)
        {
            printf("Congratulations! You've completed the puzzle! You did it in %d moves!\n", moves);
        }

        //INPUT LOOP: PROMPT USER TO PLAY AGAIN
        do
        {
            puts("Would you like to play again?\n(Enter 1 to Play Again, 0 to Exit)");
            input = scanf("%d", &start);
            if(input != 1 || start < 0 || start > 1)              //Validates scanf return value and range check: input can only be 0 or 1
            {
                fflush(stdin);
                puts("Sorry, invalid response");
                continue;
            }

        } while (input != 1 || start < 0 || start > 1);           //Condition to repeat loop: if scanf doesn't receive a valid input
        
    }while(start == 1);
    
    //PLAYER ENTERED 0 TO EXIT GAME (IE. EXIT DO/WHILE GAME LOOP)
    puts("Thank you for playing! Have a great day, good bye!");

    return 0;   
}

//FUNCTIONS:
//Function to get grid dimensions
int getDimension(int dimension)
{
    int input;
    while(dimension < 3 || dimension > 8 || input != 1)
        {
            input = scanf("%d", &dimension);
            if(input != 1)                                                              //Validates scanf return value
            {
                fflush(stdin);
                puts("Invalid input. Please enter a value between 3-8");
                continue;
            }
            else if(dimension < 3)                                                      //Range check: input must be between 3-8
            {
                puts("Error, grid size too small: Please enter a value between 3-8");
            }
            else if(dimension > 8)
            {
                puts("Error, grid size too large: Please etner a value between 3-8");
            }
        }
}

//Function to generate array of game grid numbers
int makeArray(int size, int array[])
{
    int i;
    for(i = 0; i < size; i++)
        {
            array[i] = i + 1;
            //Test: printf("%d ", array[i]);
        }
}

//Function to print game grid
int gameGrid(int row, int column, int array[])
{
    int size = row * column;
    
    int i = 0;
    for( int r = 1 ; r <= row ; r++ )
        {
            printf("\n");

            for( int c = 1 ; c <= column ; c++ )
            {
                if(array[i] == size)                                    //if index contains the value = size of grid (max size), print a blank instead
                {
                    printf("|\t%s \t", " ");
                }
                else
                printf("|\t%d \t", array[i]);
                i++;
            }
            printf("|");
        }
}

//Function to get user number selection
int getSelection(int size)
{   
    do
    {
        input = scanf("%d", &selectedN);
            if(input != 1)                                          //Validates scanf return value
            {
                fflush(stdin);
                puts("Sorry, invalid input.");
                puts("Which number would you like to slide?");
                continue;
            }

            if(selectedN < 0 || selectedN > size - 1)               //Range check: selected number can only range between 1 to (grid size - 1)
            {
                fflush(stdin);
                puts("The number you have selected is not on this board.");
                puts("Which number would you like to slide?");
                continue;
            }
    } while (input != 1 || selectedN < 0 || selectedN > (size -1));

    return selectedN;  
}

//Function to locate array index of interest
int indexFind(int array[], int size, int locateValue)
{
    int i; 
    for(i = 0; i < size; i++)
    {
        if(array[i] == locateValue)
        {
            return i;
            //Test: printf("Index with blank is %d\n", blankIndex);
        }
    }
}

//Function to check if valid tile is selected
int tileCheck(int xb, int yb, int xs, int ys)
{    
    /*Check if valid move: selectedN is adjacent to blank index
    If the move is valid, swap the values and increase moves counter by 1.*/
    if(ys == yb && ((xs == xb + 1) || (xs == xb - 1)))                      //if selected tile is in the same row, and one tile to left/right of blank = valid
    {
        return 1;
    }
    else if(xs == xb && ((ys == yb + 1) || (ys == yb - 1)))                 //if selected tile is in the same column, and one tile above/below blank = valid
    {
        return 1;
    }
    else                                                                    //if selected tile does not satisfy the above conditions, 
    {                                                                       //user has selected a tile that is not adjacent to blank tile
        return 0;
    }
}