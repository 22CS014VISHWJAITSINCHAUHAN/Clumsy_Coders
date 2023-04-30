//This code is Developed by 22CS008,22CS014,22CS009
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
