#include <bits/stdc++.h>
using namespace std;

void eraseEdge(vector<vector<int>>& adj, int u, int v) {
    adj[u].erase(find(adj[u].begin(), adj[u].end(), v));
    adj[v].erase(find(adj[v].begin(), adj[v].end(), u));
}

vector<int> buildCycle(vector<vector<int>>& adj, int start) {
    vector<int> cycle;
    stack<int> st;
    st.push(start);

    while (!st.empty()) {
        int u = st.top();
        if (!adj[u].empty()) {
            int v = adj[u].back();
            eraseEdge(adj, u, v);
            st.push(v);
        } else {
            cycle.push_back(u);
            st.pop();
        }
    }
    return cycle;
}

vector<int> getEulerianCircuit(vector<vector<int>>& adj) {
    for (int i = 0; i < adj.size(); i++) {
        if (adj[i].size() % 2 != 0) {
            return {};
        }
    }

    int start = -1;
    for (int i = 0; i < adj.size(); i++) {
        if (!adj[i].empty()) {
            start = i;
            break;
        }
    }
    if (start == -1) return {};

    vector<int> circuit = buildCycle(adj, start);

    bool moreEdges = true;
    while (moreEdges) {
        moreEdges = false;
        for (int i = 0; i < circuit.size(); i++) {
            int u = circuit[i];
            if (!adj[u].empty()) {
                vector<int> extraCycle = buildCycle(adj, u);
                circuit.insert(circuit.begin() + i + 1, extraCycle.begin(), extraCycle.end() - 1);
                moreEdges = true;
                break;
            }
        }
    }
    return circuit;
}

int main() {
    vector<vector<int>> adj = {
        {1,3,4,5},
        {0,2,3,5},
        {1,3,4},
        {0,1,2,4},
        {0,5,3,2},
        {0,1,4}
    };

    vector<int> circuit = getEulerianCircuit(adj);

    if (circuit.empty()) {
        cout << "No Eulerian circuit exists." << endl;
    } else {
        cout << "Eulerian circuit: ";
        for (int v : circuit) {
            cout << v << " ";
        }
        cout << endl;
    }
    return 0;
}
