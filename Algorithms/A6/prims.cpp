#include<bits/stdc++.h>
using namespace std;


pair<int, vector<pair<int, int>>> spanningTree(int V, vector<vector<int>> adj[]) {
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>pq;
    vector<int>vis(V,0);
    vector<int>parent(V, -1); 
    pq.push({0,0});
    int sum = 0;
    vector<pair<int, int>> mstEdges;
    
    while(!pq.empty()){
        auto it = pq.top();
        pq.pop();
        int node = it.second;
        int wt = it.first;
        if(vis[node]) continue;
        vis[node] = 1;
        sum += wt;
        

        if(parent[node] != -1) {
            mstEdges.push_back({parent[node], node});
        }
        
        for(auto it : adj[node]){
            int adjNode = it[0];
            int edW = it[1];
            if(!vis[adjNode]){
                pq.push({edW, adjNode});
                parent[adjNode] = node; 
            }
        }
    }
    return {sum, mstEdges};
}

int main(){
    int V, E;
    cin >> V >> E;
    vector<vector<int>>adj[V];
    for(int i=0; i<E; i++){
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    
    auto result = spanningTree(V, adj);
    int minWeight = result.first;
    vector<pair<int, int>> mstEdges = result.second;
    
    cout << "Minimum Spanning Tree Weight: " << minWeight << endl;
    cout << "MST Edges:" << endl;
    for(auto edge : mstEdges) {
        cout << edge.first << " - " << edge.second << endl;
    }
    
    return 0;
}