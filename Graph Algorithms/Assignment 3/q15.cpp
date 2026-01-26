#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<int> kahnTopologicalSort(const vector<vector<int>>& adj) {
    int n = adj.size();
    vector<int> indeg(n, 0);
    for (int u = 0; u < n; ++u)
        for (int v : adj[u])
            ++indeg[v];

    queue<int> q;
    for (int i = 0; i < n; ++i)
        if (indeg[i] == 0) q.push(i);

    vector<int> order;
    order.reserve(n);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        order.push_back(u);
        for (int v : adj[u]) {
            if (--indeg[v] == 0) q.push(v);
        }
    }

    if ((int)order.size() != n) return {}; // cycle detected -> no topological order
    return order;
}

int main() {
    int n;
    cout << "Enter number of vertices: ";
    if (!(cin >> n) || n <= 0) return 0;

    vector<vector<int>> graph(n);
    int m;
    cout << "Enter number of edges: ";
    if (!(cin >> m) || m < 0) return 0;

    cout << "Enter edges (u v) using letters starting from 'a':\n";
    for (int i = 0; i < m; ++i) {
        char cu, cv;
        cin >> cu >> cv;
        int u = cu - 'a';
        int v = cv - 'a';
        if (u < 0 || u >= n || v < 0 || v >= n) continue;
        graph[u].push_back(v);
    }

    vector<int> topo = kahnTopologicalSort(graph);
    if (topo.empty()) {
        cout << "No topological ordering (graph has a cycle).\n";
    } else {
        cout << "Topological order (by index): ";
        for (int x : topo) cout << x << ' ';
        cout << "\nTopological order (as letters): ";
        for (int x : topo) cout << char('a' + x) << ' ';
        cout << '\n';
    }
    return 0;
}
