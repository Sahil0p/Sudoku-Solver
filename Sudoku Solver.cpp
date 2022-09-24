#include <iostream>

using namespace std;

#define UNASSIGNED 0

#define N 9

bool findEmptyPlace(int sudoku[N][N], int& row, int& column);

bool isValid(int sudoku[N][N], int row, int column, int number);

bool solveSudoku(int sudoku[N][N])
{
    int row, column;
    
    //if there is no unassigned location
    if(!findEmptyPlace(sudoku, row, column))
        //success
        return true;
    
    //considering digits 1 to 9
    for(int number = 1; number <= 9; number++)
    {
        //checks if it looks promising
        if(isValid(sudoku, row, column, number))
        {
            //making tentaive assignment
            sudoku[row][column] = number;
            
            //on success, it returns true
            if(solveSudoku(sudoku))
                return true;
            
            //on failure, it unassigns and we try again
            sudoku[row][column] = UNASSIGNED;
        }
    }
    
    //this triggers backtracking algorithm
    return false;
}

bool findEmptyPlace(int sudoku[N][N], int& row, int& column)
{
    for(row = 0; row < N; row++)
    {
        for(column = 0; column < N; column++)
        {
            if(sudoku[row][column] == UNASSIGNED)
                return true;
        }
    }
    
    return false;
}

bool isPresentInRow(int sudoku[N][N], int row, int number)
{
    for(int column = 0; column < N; column++)
    {
        if(sudoku[row][column] == number)
            return true;
            
    }
    
    return false;
}

bool isPresentInColumn(int sudoku[N][N], int column, int number)
{
    for(int row = 0; row < N; row++)
    {
        if(sudoku[row][column] == number)
            return true;

    }
    
    return false;
}

bool isPresentInBox(int sudoku[N][N], int boxStartRow, int boxStartColumn, int number)
{
    for(int row = 0; row < 3; row++)
    {
        for(int column = 0; column < 3; column++)
        {
            if(sudoku[row + boxStartRow][column + boxStartColumn] == number)
                return true;
                
        }
    }
    
    return false;
}

bool isValid(int sudoku[N][N], int row, int column, int number)
{
    //checks if number is not already placed in current row, column and current 3X3 box
    return (!isPresentInRow(sudoku, row, number) && !isPresentInColumn(sudoku, column, number) && !isPresentInBox(sudoku, row - row % 3, column - column % 3, number) && sudoku[row][column] == UNASSIGNED);
}

void printSudoku(int sudoku[N][N])
{
    cout<<"\nSolved Sudoku is given as:\n";
    for(int row = 0; row < N; row++)
    {
        for(int column = 0; column < N; column++)
        {
            cout<<sudoku[row][column]<<" ";
        }
        cout<<endl;
    }
}

int main()
{
    int sudoku[N][N];
    
    for(int  i = 0; i < N; i++)
    {
        cout<<"Enter space separated elements of row "<<i<<" : ";
        for(int j = 0; j < N; j++)
        {
           cin>>sudoku[i][j];
        }
    }
    
    cout<<"\nEntered sudoku is:\n";
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            cout<<sudoku[i][j]<<" ";
        }
        cout<<endl;
    }
    
    if(solveSudoku(sudoku) == true)
        printSudoku(sudoku);
        
    else
        cout<<"No solution exists.";
        
    return 0;
}
