#include <bits/stdc++.h>
using namespace std;
int id = 0;
vector<int> indexes, lowlink;
stack<int> st;
vector<bool> onStack;
vector<vector<int>> sccs;
void dfs(int node, vector<vector<int>>& adj){
    indexes[node] = lowlink[node] = id++;
    st.push(node);
    onStack[node] = true;
    for(auto it : adj[node]){
        if(indexes[it] == -1){
            dfs(it, adj);
            lowlink[node] = min(lowlink[node], lowlink[it]);
        } else if(onStack[it]){
            lowlink[node] = min(lowlink[node], indexes[it]);
        }
    }
    if(lowlink[node] == indexes[node]){
        vector<int> component;
        while(true){
            int curr = st.top();
            st.pop();
            onStack[curr] = false;
            component.push_back(curr);
            if(curr == node) break;
        }
        sccs.push_back(component);
    }
}
void tarjan(vector<vector<int>>&adj){
    int n = adj.size();
    indexes.resize(n, -1);
    lowlink.resize(n, -1);
    onStack.resize(n, false);
    id = 0;
    while(!st.empty()) st.pop();
    sccs.clear();
    for(int i=0;i<n;i++){
        if(indexes[i] == -1){
            dfs(i, adj);
        }
    }
}
int main(){
    vector<vector<int>> adj = {
        {2,8},
        {0,7,2},
        {},
        {1,4},
        {3},
        {4,6,3},
        {2,3},
        {5,6,8},
        {0,6}
    };
    tarjan(adj);
    cout << "Number of Strongly Connected Components: " << sccs.size() << endl;
    for(int i=0;i<sccs.size();i++){
        cout << "SCC " << i+1 << ": ";
        for(auto it : sccs[i]){
            cout << (char)('a' + it) << " ";
        }
        cout << endl;
    }
    return 0;
}