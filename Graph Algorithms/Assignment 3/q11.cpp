#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> orderByDegree(const vector<vector<int>>& adj) {
    int n = adj.size();
    vector<pair<int,int>> degIdx;
    degIdx.reserve(n);
    for (int i = 0; i < n; ++i) degIdx.emplace_back((int)adj[i].size(), i);
    sort(degIdx.rbegin(), degIdx.rend());
    vector<int> order;
    order.reserve(n);
    for (const auto& p : degIdx) order.push_back(p.second);
    return order;
}

vector<int> greedyColoring(const vector<vector<int>>& adj) {
    int n = adj.size();
    vector<int> order = orderByDegree(adj);
    vector<int> color(n, -1);
    int currentColor = 0;
    for (int i = 0; i < n; ++i) {
        int v = order[i];
        if (color[v] != -1) continue;
        color[v] = currentColor;
        for (int j = i + 1; j < n; ++j) {
            int u = order[j];
            if (color[u] != -1) continue;
            bool conflict = false;
            for (int nb : adj[u]) {
                if (color[nb] == currentColor) { conflict = true; break; }
            }
            if (!conflict) color[u] = currentColor;
        }
        ++currentColor;
    }
    return color;
}

int main() {
    int n;
    cout << "Enter number of vertices: ";
    if (!(cin >> n) || n <= 0) return 0;

    vector<vector<int>> graph(n);
    int m;
    cout << "Enter number of edges: ";
    if (!(cin >> m) || m < 0) return 0;

    cout << "Enter edges (u v) using letters from 'a':" << endl;
    for (int i = 0; i < m; ++i) {
        char cu, cv;
        cin >> cu >> cv;
        int u = cu - 'a';
        int v = cv - 'a';
        if (u < 0 || u >= n || v < 0 || v >= n) continue;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    vector<int> colors = greedyColoring(graph);
    cout << "Vertex colors:" << endl;
    for (int i = 0; i < n; ++i) {
        char name = 'a' + i;
        cout << name << ": Color " << (colors[i] + 1) << '\n';
    }

    return 0;
}
