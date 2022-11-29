/*
mazeio.cpp
*/

#include <iostream>
#include <fstream>
#include "mazeio.h"

using namespace std;

/*************************************************
 * read_maze:
 * Read the maze from the given filename into a
 *  2D dynamically  allocated array.
 *
 * Return the pointer to that array.
 * Return NULL (a special address) if there is a problem,
 * opening the file or reading in the integer sizes.
 *
 * The first argument is the filename of the maze input.
 *  You should use an ifstream to open and read from this
 *  file.
 *
 * We also pass in two pointers to integers. These are
 * output parameters (i.e. declared by the caller and
 * passed-by-reference for this function to fill in).
 * Fill the integers pointed to by these arguments
 * with the number of rows and columns
 * read (the first two input values).
 *
 *************************************************/
char** read_maze(char* filename, int* rows, int* cols)
{

    // *** You complete **** CHECKPOINT 1

  ifstream ifile(filename);
  if (ifile.fail()){
    //cout << "HOOOOOOOOOOOOO";
    return NULL;
  }
  ifile >> *rows >> *cols;
  if (ifile.fail()){
    //cout << "FIALELLE";
    return NULL;
  }
  //cout << *rows << " "<<*cols<<endl;
  char buffer[*cols+1];
  
  char** maze = new char*[*rows];

  for (int r = 0; r<*rows; r++){
    maze[r] = new char[*cols];
    ifile>>buffer;
    //cout<<buffer<<endl;
    for (int c =0;c<*cols;c++){
      maze[r][c]=buffer[c];
    }
    //cout << maze[r]<<endl;
    
  }
  
  return maze;
}

/*************************************************
 * Print the maze contents to the screen in the
 * same format as the input (rows and columns, then
 * the maze character grid).
 *************************************************/
void print_maze(char** maze, int rows, int cols)
{
  cout << rows << " " << cols << endl;
  for (int r = 0; r < rows; r++){
    for (int c = 0; c<cols;c++){
      cout << maze[r][c];
    }
    if(r<rows-1){
      cout<<endl;
    }
  }
}

    // *** You complete **** CHECKPOINT 1










