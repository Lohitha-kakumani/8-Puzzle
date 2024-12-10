#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <cmath>
#include <algorithm>

using namespace std;

const int N = 3; // Size of the puzzle (3x3)

// A structure to represent a state of the puzzle
struct PuzzleState {
    vector<vector<int>> puzzle;
    int x, y; // Position of the blank tile (0)
    int cost; // Cost to reach this state
    int heuristic; // Estimated cost to the goal
    int depth; // Depth in the search tree

    // Overloading the < operator for priority queue
    bool operator<(const PuzzleState& other) const {
        return (cost + heuristic) > (other.cost + other.heuristic);
    }
};

// Function to calculate Manhattan distance heuristic
int calculateHeuristic(const vector<vector<int>>& puzzle) {
    int distance = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (puzzle[i][j] != 0) {
                int targetX = (puzzle[i][j] - 1) / N;
                int targetY = (puzzle[i][j] - 1) % N;
                distance += abs(i - targetX) + abs(j - targetY);
            }
        }
    }
    return distance;
}

// Function to check if the goal state is reached
bool isGoal(const vector<vector<int>>& puzzle) {
    int num = 1;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (i == N - 1 && j == N - 1) return puzzle[i][j] == 0;
            if (puzzle[i][j] != num++) return false;
        }
    }
    return true;
}

// Function to print the puzzle
void printPuzzle(const vector<vector<int>>& puzzle) {
    for (const auto& row : puzzle) {
        for (int val : row) {
            if (val == 0) cout << "  ";
            else cout << val << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

// Function to solve the 8-puzzle problem
void solve8Puzzle(const vector<vector<int>>& start) {
    priority_queue<PuzzleState> pq;
    map<vector<vector<int>>, bool> visited;

    // Find the blank tile position in the initial state
    int blankX, blankY;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (start[i][j] == 0) {
                blankX = i;
                blankY = j;
            }
        }
    }

    // Initial state
    PuzzleState initialState = {start, blankX, blankY, 0, calculateHeuristic(start), 0};
    pq.push(initialState);

    // Moves: up, down, left, right
    vector<int> dx = {-1, 1, 0, 0};
    vector<int> dy = {0, 0, -1, 1};

    while (!pq.empty()) {
        PuzzleState current = pq.top();
        pq.pop();

        // If the goal state is reached
        if (isGoal(current.puzzle)) {
            cout << "Solved the 8-puzzle problem in " << current.depth << " steps:\n";
            printPuzzle(current.puzzle);
            return;
        }

        if (visited[current.puzzle]) continue;
        visited[current.puzzle] = true;

        // Explore all possible moves
        for (int i = 0; i < 4; ++i) {
            int newX = current.x + dx[i];
            int newY = current.y + dy[i];

            if (newX >= 0 && newX < N && newY >= 0 && newY < N) {
                vector<vector<int>> newPuzzle = current.puzzle;
                swap(newPuzzle[current.x][current.y], newPuzzle[newX][newY]);

                if (!visited[newPuzzle]) {
                    PuzzleState newState = {newPuzzle, newX, newY, current.depth + 1, calculateHeuristic(newPuzzle), current.depth + 1};
                    pq.push(newState);
                }
            }
        }
    }

    cout << "No solution found.\n";
}

int main() {
    vector<vector<int>> start = {
        {1, 2, 3},
        {4, 0, 5},
        {7, 8, 6}
    };

    cout << "Initial puzzle state:\n";
    printPuzzle(start);

    solve8Puzzle(start);

    return 0;
}
