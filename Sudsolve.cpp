//Anirudh Agarwala
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <cstdlib>
#include <stdlib.h>
#include <cctype>
#include <iomanip>
using namespace std;

bool solver(int **grid, int row, int col, bool *solved);
bool validRow(int **grid, int row, int value);
bool validCol(int **grid, int row, int value);
bool validBlock(int **grid, int row, int col, int value);
bool solnCheckRow(int **grid, bool flag);
bool solnCheckCol(int **grid, bool flag);
bool solnCheckBlock(int **grid, bool flag);

int main()
{
  string input="", temp=""; //sudoku input
  int **grid = new int*[9]; //stores input as grid
  for(int i=0; i<9; ++i)
    grid[i] = new int[9];
  int l=0; //counter for input
  int row=0, col=0;
  bool solved_var = false;
  bool *solved=&solved_var; //checks if there was a sol'n or not  
  int charhex=0, inputlength=0;

  getline(cin, input);

  while(l != 81)
  {
  for(int i=0; i < 9; i++)
    for(int j=0; j < 9; j++) 
    {
      if(input[l]==46)
        grid[i][j] = 0;
      else
        grid[i][j] = input[l]-48;
      l++;
    }
  }
 
  inputlength = input.length(); 

  /* ERRORS */
  for(int i=0; i < inputlength; i++)
  {
    charhex = input[i];
    if(iscntrl(input[i]))
    { 
        cout << "ERROR: expected <value> saw \\x" << hex << setw(2) << setfill('0') << charhex << endl;
        return 0;
    }
  }//checks hex

  if((input.length())<81)
  {
     if(cin.eof())
     {
        cout << "ERROR: expected <value> saw <eof>" << endl;
        exit(0);
     }//if given blank file

    cout<<"ERROR: expected <value> saw \\n" << endl;
    return 0;
  }
  if((input.length())!=81)
  {
    cout<<"ERROR: expected \\n saw "<< input[81] <<endl;
    return 0;
  }//if not 81 characters

  for(int i=0; i < 81; i++)
  {
     if(! ((isdigit(input[i]) && (input[i]!=48)) || input[i]=='.'))
     {
        cout << "ERROR: expected <value> saw " << input[i] << endl;
        return 0;
     }
  }//checks if non-characters 

  while(!cin.eof())
  {
    getline(cin, temp);
  }
  
  *solved = solver(grid, row, col, solved); //solves sudoku
  
  if((*solved)==false)
  {
    cout << "No solutions.\n";
    return 0;
  }//prints error message for no solution

  return 0;
}//main


bool solver(int** grid, int row, int col, bool* solved)
{
  bool flag = false;
  if(row > 8)
  {
    flag = solnCheckRow(grid, flag);
    flag = solnCheckCol(grid, flag);
    flag = solnCheckBlock(grid, flag);
    for(int i=0; i < 9; i++)
    {
      for(int j=0; j < 9; j++)
      {
        if(flag==true)
          cout << grid[i][j];
        else
        {
          *solved=false;
          return *solved;
        }//print No Solutions.
       }//inner for
    }//prints out grid
    cout << endl;
    *solved = true;
    return *solved; //exits if done solving
  }
  else
  {
    while(grid[row][col]!=0)
    {
      if( ++col > 8)
      {
        col = 0;
        row++;
        if (row > 8)
        {
          flag = solnCheckRow(grid, flag);
          flag = solnCheckCol(grid, flag);
          flag = solnCheckBlock(grid, flag);
          for(int i=0; i < 9; i++)
          {
            for(int j=0; j < 9; j++)
            {
              if(flag==true)
                cout << grid[i][j];
              else
              {
                *solved=false;
                return *solved;
              }//print No Solutions.
            }//inner for
          }//prints out grid
          cout << endl;
          *solved = true;
          return *solved; //exits if done solving
        }//if
      }//moves to next row
    }//goes through whole grid
  
  for(int value=1; value < 10; value++)
  {
    if(validRow(grid, row, value) && validCol(grid, col, value) && validBlock(grid, row, col, value))
    {
      grid[row][col] = value; //sets empty cell to next guess
    
      if(col < 8)
        *solved = solver(grid, row, col+1, solved); //goes to next cell in row
      else
        *solved = solver(grid, row+1, 0, solved); //goes to next row      

    }//checks if value is valid option
  }//guesses all the values 
  
  grid[row][col]=0; //resets cell to 0 (will now go up 1 level in recursion and try next value)

  }//else

  return *solved;
}//solver

bool solnCheckRow(int **grid, bool flag)
{
  int c1=0, c2=0, c3=0, c4=0, c5=0, c6=0, c7=0, c8=0, c9=0;
  for(int i=0; i<9; i++)
  {
    for(int j=0; j<9; j++)
    {
        switch(grid[i][j])
        {
          case 1: c1++; break;
          case 2: c2++; break;
          case 3: c3++; break;
          case 4: c4++; break;
          case 5: c5++; break;
          case 6: c6++; break;
          case 7: c7++; break;
          case 8: c8++; break;
          case 9: c9++;
        }//checks if board is correct
        
        if((c1>1) || (c2>1) || (c3>1) || (c4>1) || (c5>1) || (c6>1) || (c7>1) || (c8>1) || (c9>1))
        {
          flag = false; //no solution
          return flag;
        }//set flag to false
        else if((c1==1) && (c2==1) && (c3==1) && (c4==1) && (c5==1) && (c6==1) && (c7==1) && (c8==1) && (c9==1))
        {
          flag = true;
          c1=c2=c3=c4=c5=c6=c7=c8=c9=0;
        }//allows to print
    }//inner for
  }//for
  return flag;
  
}//checks if no solution for row

bool solnCheckCol(int **grid, bool flag)
{
  int c1=0, c2=0, c3=0, c4=0, c5=0, c6=0, c7=0, c8=0, c9=0;
  for(int i=0; i<9; i++)
  {
    for(int j=0; j<9; j++)
    {
        switch(grid[j][i])
        {
          case 1: c1++; break;
          case 2: c2++; break;
          case 3: c3++; break;
          case 4: c4++; break;
          case 5: c5++; break;
          case 6: c6++; break;
          case 7: c7++; break;
          case 8: c8++; break;
          case 9: c9++;
        }//checks if board is correct

        if((c1>1) || (c2>1) || (c3>1) || (c4>1) || (c5>1) || (c6>1) || (c7>1) || (c8>1) || (c9>1))
        {
          flag = false; //no solution
          return flag;
        }//set flag to false
        else if((c1==1) && (c2==1) && (c3==1) && (c4==1) && (c5==1) && (c6==1) && (c7==1) && (c8==1) && (c9==1))
        {
          flag = true;
          c1=c2=c3=c4=c5=c6=c7=c8=c9=0;
        }//allows to print
    }//inner for
  }//for
  return flag;

}//checks if no solution for col

bool solnCheckBlock(int **grid, bool flag)
{
  int c1=0, c2=0, c3=0, c4=0, c5=0, c6=0, c7=0, c8=0, c9=0;
 
  for(int col=0; col<=6; col+=3)
  {
  for(int row=0; row<=6; row+=3)
  {
  for(int i=0; i<3; i++)
  {
    for(int j=0; j<3; j++)
    {
        switch(grid[row+i][col+j])
        {
          case 1: c1++; break;
          case 2: c2++; break;
          case 3: c3++; break;
          case 4: c4++; break;
          case 5: c5++; break;
          case 6: c6++; break;
          case 7: c7++; break;
          case 8: c8++; break;
          case 9: c9++;
        }//checks if board is correct

        if((c1>1) || (c2>1) || (c3>1) || (c4>1) || (c5>1) || (c6>1) || (c7>1) || (c8>1) || (c9>1))
        {
          flag = false; //no solution
          return flag;
        }//set flag to false
        else if((c1==1) && (c2==1) && (c3==1) && (c4==1) && (c5==1) && (c6==1) && (c7==1) && (c8==1) && (c9==1))
        {
          flag = true;
          c1=c2=c3=c4=c5=c6=c7=c8=c9=0;
        }//allows to print
    }//inner for
  }//for
  }//row
  }//col
  return flag;

}//checks if no solution for block

bool validRow(int **grid, int row, int value)
{
  for(int col=0; col<9; col++)
    if(grid[row][col]==value)
      return false;
  return true;
}//checks if valid in row

bool validCol(int **grid,int col, int value)
{
  for(int row=0; row<9; row++)
    if(grid[row][col]==value)
      return false;
  return true;
}//checks if valid in col

bool validBlock(int **grid, int row, int col, int value)
{
  row = (row/3)*3;
  col = (col/3)*3;
  for(int i=0; i<3; i++)
    for(int j=0; j<3; j++)
      if(grid[row+i][col+j]==value)
        return false;
  return true;
}//checks if valid in block
