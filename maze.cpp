/*
maze.cpp
*/

#include <iostream>
#include "mazeio.h"
#include "queue.h"
// #include "queue.h"

using namespace std;

// Prototype for maze_search, which you will fill in below.
int maze_search(char** maze, int rows, int cols);

// Add other prototypes here for any functions you wish to use

//checks if maze is valid and has only the correct characters and theres only one F and one S
//returns 0 if valid, a 1 if invalid character present, and 2 if there is not only one F and S
int valid_maze(char** maze, int rows, int cols);

//checks if given coordinates is valid location in maze to account for edge cases
bool valid_coord(Location loc, int rows, int cols);


 
// main function to read, solve maze, and print result
int main(int argc, char* argv[]){
  int rows, cols, result;
  char** mymaze=NULL;
  const char* invalid_char_message = "Error, invalid character.";
  const char* invalid_maze_message = "Invalid maze.";
  const char* no_path_message = "No path could be found!";

  if(argc < 2)
  {
    cout << "Please provide a maze input file" << endl;
    return 1;
  }

  //updates rows and cols pointers from read in values and stores mymaze 
  mymaze = read_maze(argv[1],&rows,&cols); // <---TASK: COMPLETE THIS FOR CHECKPOINT 1

  // For checkpoint 2 you should check the validity of the maze
  // You may do so anywhere you please and can abstract that
  // operation with a function or however you like.
  


  //================================
  // When working on Checkpoint 4, you will need to call maze_search
  // and output the appropriate message or, if successful, print
  // the maze.  But for Checkpoint 1, we print the maze, regardless.
  result = maze_search(mymaze,rows,cols);
  
  if (result==1){
    print_maze(mymaze, rows, cols);
  }
  else if (result == -1){
    if (valid_maze(mymaze,rows,cols)==1){
      cout<<invalid_char_message;
    }
    else {
      cout<<invalid_maze_message;
    }
  }
  else{
    cout<<no_path_message;
  }
  

  //================================
  // ADD CODE BELOW 
  // to delete all memory that read_maze allocated: CHECKPOINT 2
  for (int r=0;r<rows;r++){
    delete [] mymaze[r];
  }
  delete [] mymaze;
  return 0;
}

/**************************************************
 * Attempt to find shortest path and return:
 *  1 if successful
 *  0 if no path exists
 *
 * If path is found fill it in with '*' characters
 *  but don't overwrite the 'S' and 'F' cells
 * NOTE: don't forget to deallocate memory in here too!
 *************************************************/
int maze_search(char** maze, int rows, int cols)
{
  // *** You complete **** CHECKPOINT 4

  //making queue of max spaces in disappear
  Queue locq(rows*cols);

  //checks if it is a valid maze and returns -1
  if(valid_maze(maze,rows,cols)){
    return -1;
  }
  Location start,finish;
  
  //dynamically allocated bool and Location arrays and initialized bool array to false, and found start and finish locations
  bool** explored = new bool*[rows];
  Location** predecessor = new Location*[rows];
  for (int r = 0;r<rows;r++){
    explored[r]=new bool[cols];
    predecessor[r]=new Location[cols];
    for (int c= 0;c<cols;c++){
      if (maze[r][c]=='S'){
        start.row=r;
        start.col=c;
      }
      else if(maze[r][c]=='F'){
        finish.row=r;
        finish.col=c;
      }
      explored[r][c]=false;
    }
  }
  //adds in finish to queue and updates explored array
  locq.add_to_back(start);
  explored[start.row][start.col]=true;
  bool finished = false;

  // makes array of NWSE locations and checks each location's coordinates to see if it is in maze
  // adds to queue if it is a '.', and updates explored array and predecessor array accoridngly
  //if finish is found, predecessor array and explored array updated accordingly
  while(!locq.is_empty()){
    Location loc = locq.remove_from_front(); // takes location from front
    Location nloc=loc, sloc = loc, eloc = loc, wloc = loc; // makes 4 new points
    nloc.row--;sloc.row++;eloc.col++;wloc.col--; //updates poitns to reflect locaitons
    Location NWSE[] = {nloc,wloc,sloc,eloc}; // array of locations

    //iterates through NWSE location
    for (int z = 0;z<4;z++){
      Location newloc = NWSE[z];
      if (valid_coord(newloc,rows,cols)&& !explored[newloc.row][newloc.col]){//if coord in bounds and isnt explored
        if (maze[newloc.row][newloc.col]=='.'){//if char is .
          explored[newloc.row][newloc.col]=true;
          //cout<<loc.row<<loc.col<<endl<<newloc.row<<newloc.col<<endl<<endl;
          locq.add_to_back(newloc);
          predecessor[newloc.row][newloc.col]=loc;
        }
        else if (maze[newloc.row][newloc.col]=='F'){ // if finish is found
          finished = true; // can break if finish is found after all
          predecessor[newloc.row][newloc.col]=loc;
          explored[newloc.row][newloc.col]=true;
        }
      }
    }
    //if finish is found then break while loop as shortest path has been found
    if (finished){break;}
  }
  //if finish is found start walking back through maze and changing chars to '*' until start is encountered
  while(finished){
    Location previousloc=predecessor[finish.row][finish.col];
    if(maze[previousloc.row][previousloc.col]=='S'){
        break;
    }
    maze[previousloc.row][previousloc.col]='*';
    finish = previousloc;
  }
  for (int r = 0; r<rows;r++){
    delete [] explored[r];
    delete [] predecessor[r];
  }
  delete [] explored;
  delete[] predecessor;
  
  //if path found return 0 or else returned is 0
  if (finished){
    return 1;
  }
  return 0; // DELETE this stub, it's just for Checkpoint 1 to compile.
}

//iterates through array to check for validity
int valid_maze(char** maze, int rows, int cols){
  int startPresent = 0;
  int finishPresent=0;
  for (int r = 0; r<rows;r++){
    for (int c =0;c<cols;c++){
      char present = maze[r][c];
      if (!(present=='#'|| present=='.'||present =='F'||present=='S')){
        return 1;
      }
      if (present=='S'){
        startPresent++;
        if (startPresent>1){
            return 2;
        }
      }
      if (present=='F'){
        finishPresent++;
        if (finishPresent>1){
            return 2;
        }
      }
    }
  }
  if (startPresent ==0||finishPresent==0){
    return 2;
  }
  return 0;
}

//given point and array dimensions checks if it is a valid point
bool valid_coord(Location loc, int rows, int cols){
  if (loc.row >=0 && loc.row<rows && loc.col>=0 && loc.col <cols){
    return true;
  }
  return false;
}
