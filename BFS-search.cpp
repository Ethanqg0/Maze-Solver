#include <iostream>
#include <queue>
#include <vector>

using namespace std;
const int SIZE = 9;

void displayFinal(char arr[SIZE][SIZE])
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
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (arr[i][j] == 'S') {
                return std::make_pair(i, j);
            }
        }
    }
    return std::make_pair(0, 0);
}

void findPathBFS(char arr[SIZE][SIZE]) {
    queue<pair<int, int>> mazeQueue;
    pair<int, int> start = findStart(arr);
    mazeQueue.push(start);

    while (!mazeQueue.empty()) {
        pair<int, int> curr = mazeQueue.front();
        mazeQueue.pop();

        int i = curr.first;
        int j = curr.second;

        // If we've found the goal, stop
        if (arr[i][j] == 'G') {
            break;
        }

        // Mark the current position as part of the path
        if (arr[i][j] != 'S') {
            arr[i][j] = 'O';
        }

        // Check all four directions and enqueue valid moves
        if (withinTheBoundary(i - 1, j) && (arr[i - 1][j] == ' ' || arr[i - 1][j] == 'G')) { // north
            mazeQueue.push({i - 1, j});
            if (arr[i - 1][j] != 'G') arr[i - 1][j] = 'V'; // Mark as visited to prevent re-enqueueing
        }
        if (withinTheBoundary(i + 1, j) && (arr[i + 1][j] == ' ' || arr[i + 1][j] == 'G')) { // south
            mazeQueue.push({i + 1, j});
            if (arr[i + 1][j] != 'G') arr[i + 1][j] = 'V'; // Mark as visited
        }
        if (withinTheBoundary(i, j - 1) && (arr[i, j - 1] == ' ' || arr[i, j - 1] == 'G')) { // west
            mazeQueue.push({i, j - 1});
            if (arr[i, j - 1] != 'G') arr[i, j - 1] = 'V'; // Mark as visited
        }
        if (withinTheBoundary(i, j + 1) && (arr[i, j + 1] == ' ' || arr[i, j + 1] == 'G')) { // east
            mazeQueue.push({i, j + 1});
            if (arr[i, j + 1] != 'G') arr[i, j + 1] = 'V'; // Mark as visited
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

    findPathBFS(maze2D);
    displayFinal(maze2D);

    return 0;
}
