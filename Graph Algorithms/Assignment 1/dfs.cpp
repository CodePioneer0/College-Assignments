#include<bits/stdc++.h>
using namespace std;
void dfs(int node, vector<int>& visited, vector<vector<int>>& graph) {
    visited[node] = 1;
    for (auto it : graph[node]) {
        if (!visited[it]) {
            cout<<char(it+'a')<<" -- "<<char(node+'a')<<endl;
            dfs(it, visited, graph);
        }
    }
}
int main(){
    int n, m;
    cout << "Enter the number of nodes and edges: ";
    cin >> n >> m;
    vector<vector<int>> graph(n);
    cout << "Enter the edges (u v) :" << endl;
    for (int i = 0; i < m; i++) {
        char u, v;
        cin >> u >> v;
        graph[u - 'a'].push_back(v - 'a');
        graph[v - 'a'].push_back(u - 'a');
    }
    
    vector<int> visited(n, 0);
    cout << "Edges in the Spanning Tree through DFS :" << endl;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(i, visited, graph);
        }
    }
    return 0;
}