#include <bits/stdc++.h>
using namespace std;

class DisjointSet{
    vector<int>rank,parent,size;
public:
    DisjointSet(int n){
        rank.resize(n+1,0);
        parent.resize(n+1);
        size.resize(n+1);
        for(int i=0;i<=n;i++){
            parent[i] = i;
            size[i] = 1;
        }
    }
    int findUPar(int node){
        if(node == parent[node]){
            return node;
        }
        return parent[node] = findUPar(parent[node]);
    }
    void UnionByRank(int u,int v){
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if(ulp_u==ulp_v) return;
        if(rank[ulp_u]<rank[ulp_v]){
            parent[ulp_u] = ulp_v;
        }
        else if(rank[ulp_u]>rank[ulp_v]){
            parent[ulp_v] = ulp_u;
        }
        else{
            parent[ulp_v] = ulp_u;
            rank[ulp_u]++;
        }
    }   
    void UnionBySize(int u,int v){
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if(ulp_u==ulp_v) return;
        if(size[ulp_u]<size[ulp_v]){
            parent[ulp_u] = ulp_v;
            size[ulp_v]+=size[ulp_u];
        }
        else{
            parent[ulp_v] = ulp_u;
            size[ulp_u]+=size[ulp_v];
        }
    }    
};
int spanningTree(int V, vector<vector<int>> adj[],vector<pair<int, int>> &tree) {
    vector<pair<int,pair<int,int>>>edges;
    for(int i=0;i<V;i++){
        for(auto it : adj[i]){
            int adjNode = it[0];
            int wt = it[1];
            edges.push_back({wt,{i,adjNode}});
        }
    }
    sort(edges.begin(),edges.end());
    DisjointSet ds(V);
    int wtMst = 0;
    for(auto it : edges){
        int wt = it.first;
        int u = it.second.first;
        int v = it.second.second;
        if(ds.findUPar(u)!=ds.findUPar(v)){
            wtMst+=wt;
            ds.UnionBySize(u,v);
            tree.push_back({u,v});
        }
    }
    return wtMst;
    
}
int main() {
    int V, E;
    cin >> V >> E;
    vector<vector<int>> adj[V];
    int i = 0;
    while (i++ < E) {
        int u, v, w;
        cin >> u >> v >> w;
        vector<int> t1, t2;
        t1.push_back(v);
        t1.push_back(w);
        adj[u].push_back(t1);
        t2.push_back(u);
        t2.push_back(w);
        adj[v].push_back(t2);
    }
    vector<pair<int, int>> tree;
    cout<<"Minimum Spanning Tree size : "<<spanningTree(V, adj,tree) << "\n";
    cout<<"Edges of Minimum Spanning Tree : \n";
    for(auto it : tree){
        cout<<it.first<<" "<<it.second<<"\n";
    }
    return 0;
}