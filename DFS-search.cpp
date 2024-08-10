/*
  Q23 Maze Design: Maze solving algorithm using 2D Array
  Assignment:
  Learn how to use a C++ class template.

  Project requirements:

  1. Navigate through the maze provided and identify a route from the starting point "S" to the goal point "G." The symbol "W" represents walls, while empty cells indicate spaces where a path can be established.

  2. The symbol "X" does not appear in either one of the two mazes. When working on the program, you may know what it is for. We will let you figure this out by yourself.

  3. It is presumed that a viable path will always be discoverable.
  3. Once the path is determined, output a maze resembling the following configuration.



  In the output, the "o" symbols indicate the path that connects "S" and "G." It may not be the shortest route and your solution may not be the same as the one above. 

  4. We should choose the best container class from either stack, queue, and deque to implement this program. Points will be deducted if the class is properly chosen.

  5. When testing, we should move 'S' and 'G' to any positions in the maze, and a proper path should still be generated after the program is executed.
  -

  Solution Idea:

  1. Best container: Stack. Appends previously visited coordinates and maintains correct path. 

  2. 
   while( not at goal and NOT out of boundary)
    {
           case 'G':                  
             update the 2D array with the values of O's for each coordinate within the stack.

           case blank: 
             append pair<int,int> to stack, move current coordinate to the blank spot

           case 'W' (wall) or case 'V' (visited): 
             look at adjacent spots within the 2D array for blank coordinates. Ignore other walls (W) and visited spots (V).

           case dead end: 
             backtrack and replace current spots with "V" for visited until we find a spot with adjacent blank spots, meaning it can be visited. Remove dead-end coordinates from the stack during backtracking.
    }

  3. Assuming the pseudocode will work as intended, the implementation should only take a few hours.

  while (goal is not found)
    // North
    if ( within the boundary(i--, j) && the value is empty ) {
      i--;
      curr_pos = {i,j}
      mark "o" on {i,j}
      path.push(curr_pos);
    }
    // West
    else if ( within the boundary(i, j--) && the value is empty ) {
      j--;
      curr_pos = {i,j}
      mark "o" on {i,j}
      path.push(curr_pos);
    }
    // East
    else if ( within the boundary(i, j++) && the value is empty ) {
      j++;
      curr_pos = {i,j}
      mark "o" on {i,j}
      path.push(curr_pos);
    }
    // South
    else if ( within the boundary(i++, j) && the value is empty ) {
      i++;
      curr_pos = {i,j}
      mark "o" on {i,j}
      path.push(curr_pos);
    }
    else { // dead end
      add an X in the array at this current position
      path.pop; // remove from stack
      curr_pos = top element in the stack
    }


*/

#include <iostream>
#include <stack>
#include <vector>

using namespace std;
const int SIZE = 9;

void display( char arr[SIZE][SIZE] )
{
    cout << endl << "= = = = = = = = = = = " << endl;
    for(int i  = 0; i < SIZE; i++)
    {
        cout << "= ";
        for(int j  = 0; j < SIZE; j++)
        {
            cout << arr[i][j] << " ";
        }
        cout <<  "= " << endl;
    }
    cout << "= = = = = = = = = = = " << endl;
    return;
} 

void displayFinal(char arr[SIZE][SIZE] )
{
    cout << endl << "Path:" << endl;
    cout << "= = = = = = = = = = = " ;
    for(int i  = 0; i < SIZE; i++)
    {
        cout << endl << "= ";
        for(int j  = 0; j < SIZE; j++)
        {
            if (arr[i][j] == 'X')
                cout <<  "  ";
            else
                cout << arr[i][j] << " ";
        }
        cout <<  "= ";
    }
    cout << endl << "= = = = = = = = = = = " << endl;
    return;
}

bool withinTheBoundary(int i, int j)
{
  return i >= 0 &&  i < SIZE && j >= 0 && j < SIZE;
}

pair<int, int> findStart(char arr[SIZE][SIZE]) {
  for ( int i = 0; i < SIZE; i++ ) {
    for ( int j = 0; j < SIZE; j++ ) {
      if ( arr[i][j] == 'S')  {
        return std::make_pair(i, j); 
      }
    }
  }
  return std::make_pair(0,0);
}

// Function to find the path through the maze
void findPath(char arr[SIZE][SIZE]) {
    stack<pair<int, int>> mazeStack;

    pair<int, int> currLocation = findStart(arr);

    mazeStack.push(currLocation);

    while (!mazeStack.empty()) {
        // Get current position
        currLocation = mazeStack.top();
        int i = currLocation.first;
        int j = currLocation.second;

      
        if (arr[i][j] != 'S' && arr[i][j] != 'G') {
          arr[i][j] = 'O';
        }

        // Within Goal
        if ( arr[i][j] == 'G' || arr[i+1][j] == 'G' || arr[i-1][j]== 'G' || arr[i][j + 1]== 'G' || arr[i-1][j - 1]== 'G' ) {
            break;
        }

        // Check all four directions
        if (withinTheBoundary(i - 1, j) && arr[i - 1][j] == ' ') { // north
            mazeStack.push({i - 1, j});
        } else if (withinTheBoundary(i + 1, j) && arr[i + 1][j] == ' ') { // south
            mazeStack.push({i + 1, j});
        } else if (withinTheBoundary(i, j + 1) && arr[i][j + 1] == ' ') { // east
            mazeStack.push({i, j + 1});
        } else if (withinTheBoundary(i, j - 1) && arr[i][j - 1] == ' ') { // west
            mazeStack.push({i, j - 1});
        } else { // backtracking
            arr[i][j] = 'X';
            mazeStack.pop();
        }
    }
}


int main()
{
    char maze2D[SIZE][SIZE] =
      { {'S', ' ', ' ', ' ', 'W', ' ', ' ', ' ', ' '},
        {' ', 'W', ' ', ' ', 'W', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', 'W', 'W', ' ', ' ', 'W', ' '},
        {'W', ' ', 'W', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', 'W', ' ', ' ', 'W', ' ', ' ', ' '},
        {' ', 'W', ' ', ' ', ' ', ' ', 'W', ' ', 'W'},
        {' ', 'W', ' ', 'W', ' ', ' ', 'W', ' ', ' '},
        {' ', ' ', ' ', 'W', 'W', 'W', ' ', ' ', 'W'},
        {' ', ' ', ' ', ' ', ' ', 'W', ' ', ' ', 'G'},
                      };

    findPath(maze2D);
    displayFinal(maze2D);

    return 0;
}
