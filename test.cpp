#include "mazeio.h"
int main(){
  int rows, cols;
  char* filename = "maze2.in";
  char** maze = read_maze(filename,&rows, &cols);
  print_maze(maze,rows,cols);
  return 0;
}