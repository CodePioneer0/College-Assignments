# include <bits/stdc++.h>
using namespace std;
void dfs(int node,vector<int>&vis,vector<int>adj[],stack<int>&st){
    vis[node] = 1;
    for(auto it : adj[node]){
        if(!vis[it]){
            dfs(it,vis,adj,st);
        }
    }
    st.push(node);
}
void dfsOnTranspose(int node,vector<int>&vis,vector<int> adjT[],vector<char>&components){
    vis[node] = 1;
    components.push_back('a' + node);
    for(auto it : adjT[node]){
        if(!vis[it]){
            dfsOnTranspose(it,vis,adjT,components);
        }
    }
}
int main(){
    // 0 -> a, 1 -> b, 2 -> c, 3 -> d, 4 -> e, 5 -> f
    vector<int>adj[6];
    adj[0] = {1,5};
    adj[1] = {0,2,4};
    adj[2] = {4,3};
    adj[3] = {4};
    adj[4] = {2};
    adj[5] = {4, 0};
    vector<int>vis(6,0);
    stack<int>st;
    //Step 1 : Ordering based on finishing time
    dfs(0,vis,adj,st);
    //Step 2 : Transpose the graph
    vector<int>adjT[6];
    for(int i=0;i<6;i++){
        vis[i] = 0;
        for(auto it : adj[i]){
            adjT[it].push_back(i);
        }
    }
    //Step 3 : Do DFS based on finishing time
    int sccs = 0;
    vector<string> components;
    while(!st.empty()){
        int node = st.top();
        st.pop();
        if(!vis[node]){
            vector<char>components;
            dfsOnTranspose(node,vis,adjT,components);
            sccs++;
            for(auto it : components){
                cout << it << " ";
            }
            cout << endl;
        }
    }
    cout << "Number of Strongly Connected Components: " << sccs << endl;
    return 0;
}