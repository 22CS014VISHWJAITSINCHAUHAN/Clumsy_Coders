//This code is Developed by 22CS008,22CS014,22CS033
// This will generate a svg file format or sudoku puzzle. Which you can fetch easily.
// For example you can use it as a online Sudoku website generator.

#include <bits/stdc++.h> // This includes all library in c++.

#define UNASSIGNED 0

using namespace std;
//! Step 1 : Initialize the object first
//! Set up the initial position of the puzzle
class Sudoku {
private:
  int grid[9][9];
  int solnGrid[9][9];
  int guessNum[9];
  int gridPos[81];
  int difficultyLevel;
  bool grid_status;

public:
  Sudoku ();
  Sudoku (string, bool row_major=true);
  void fillEmptyDiagonalBox(int);
  void createSeed();
  void printGrid();
  bool solveGrid();
  string getGrid();
  void countSoln(int &number);
  void genPuzzle();
  bool verifyGridStatus();
  void printSVG(string);
  void calculateDifficulty();
  int  branchDifficultyScore();
};
// START: Get grid as string in row major order
string Sudoku::getGrid()
{
  string s = "";
  for(int row_num=0; row_num<9; ++row_num)
  {
    for(int col_num=0; col_num<9; ++col_num)
    {
      s = s + to_string(grid[row_num][col_num]);
    }
  }

  return s;
}
// END: Get grid as string in row major order
// START: Generate random number
int genRandNum(int maxLimit)
{
  return rand()%maxLimit;
}
// END: Generate random number


// START: Helper functions for solving grid
//! Step 4 : Implement the helper function to solve the Sudoku
bool FindUnassignedLocation(int grid[9][9], int &row, int &col)
{
    for (row = 0; row < 9; row++)
    {
        for (col = 0; col < 9; col++)
        {
            if (grid[row][col] == UNASSIGNED)
                return true;
        }
    }

    return false;
}
//! Step 4 : Use Helper function to check if number is present in row or not
bool UsedInRow(int grid[9][9], int row, int num)
{
    for (int col = 0; col < 9; col++)
    {
        if (grid[row][col] == num)
            return true;
    }

    return false;
}
//! Step 5 : Using helper function to check if number is present in column or not
bool UsedInCol(int grid[9][9], int col, int num)
{
    for (int row = 0; row < 9; row++)
    {
        if (grid[row][col] == num)
            return true;
    }

    return false;
}

//! Step 6 : Use Helper function to check if number is present in a 3 x 3 matrix or not
bool UsedInBox(int grid[9][9], int boxStartRow, int boxStartCol, int num)
{
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            if (grid[row+boxStartRow][col+boxStartCol] == num)
                return true;
        }
    }

    return false;
}
//! Step 7 : Use Helper Function to check if number is Used in Row, Column and Box
bool isSafe(int grid[9][9], int row, int col, int num)
{
    return !UsedInRow(grid, row, num) && !UsedInCol(grid, col, num) && !UsedInBox(grid, row - row%3 , col - col%3, num);
}
// END: Helper functions for solving grid


// START: Create seed grid
//! Step 9 : Create a seed grid to generate a random number
void Sudoku::fillEmptyDiagonalBox(int idx)
{
  int start = idx*3;
  random_shuffle(this->guessNum, (this->guessNum) + 9, genRandNum);
  for (int i = 0; i < 3; ++i)
  {
    for (int j = 0; j < 3; ++j)
    {
      this->grid[start+i][start+j] = guessNum[i*3+j];
    }
  }
}

//! Step 10 : Create a helper function for seed grid
void Sudoku::createSeed()
{
  /* Fill diagonal boxes to form:
      x | . | .
      . | x | .
      . | . | x
  */
  this->fillEmptyDiagonalBox(0);
  this->fillEmptyDiagonalBox(1);
  this->fillEmptyDiagonalBox(2);

  /* Fill the remaining blocks:
      x | x | x
      x | x | x
      x | x | x
  */
  this->solveGrid(); // TODO: not truly random, but still good enough because we generate random diagonals.

  // Saving the solution grid
  for(int i=0;i<9;i++)
  {
    for(int j=0;j<9;j++)
    {
      this->solnGrid[i][j] = this->grid[i][j];
    }
  }
}
// END: Create seed grid
