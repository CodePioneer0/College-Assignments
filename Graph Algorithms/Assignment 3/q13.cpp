#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

int numVertices, numColors;
vector<vector<int>> adjMatrix;
vector<int> colors;

void tryNextColor(int v) {
    while (true) {
        colors[v] = (colors[v] + 1) % (numColors + 1);
        if (colors[v] == 0) return;
        int j;
        for (j = 0; j < numVertices; ++j)
            if (adjMatrix[v][j] == 1 && colors[v] == colors[j])
                break;
        if (j == numVertices) return;
    }
}

bool colorBacktrack(int v) {
    while (true) {
        tryNextColor(v);
        if (colors[v] == 0) return false;
        if (v == numVertices - 1) return true;
        if (colorBacktrack(v + 1)) return true;
    }
}

void runMColoring() {
    colors.assign(numVertices, 0);
    if (colorBacktrack(0)) {
        cout << "Solution exists. Color assignment:\n";
        for (int i = 0; i < numVertices; ++i)
            cout << "Vertex " << i << ": Color " << colors[i] << '\n';
    } else {
        cout << "No solution exists with " << numColors << " colors.\n";
    }
}

int main() {
    cout << "Enter number of vertices: ";
    if (!(cin >> numVertices) || numVertices <= 0) return 0;

    adjMatrix.assign(numVertices, vector<int>(numVertices, 0));
    cout << "Enter adjacency matrix:\n";
    for (int i = 0; i < numVertices; ++i)
        for (int j = 0; j < numVertices; ++j)
            cin >> adjMatrix[i][j];

    cout << "Enter number of colors: ";
    if (!(cin >> numColors) || numColors < 1) return 0;

    auto start = high_resolution_clock::now();
    runMColoring();
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(end - start).count();
    cout << "Time taken: " << duration << " microseconds.\n";
    return 0;
}
