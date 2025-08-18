#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

class GraphIsomorphism {
public:
    static bool areIsomorphic(const vector<vector<int>>& g1, const vector<vector<int>>& g2) {
        int n1 = g1.size();
        int n2 = g2.size();

        if (n1 != n2) {
            return false;
        }
        
        int e1 = countEdges(g1);
        int e2 = countEdges(g2);
        if (e1 != e2) {
            return false;
        }
        
        vector<int> deg1 = getDegreeSequence(g1);
        vector<int> deg2 = getDegreeSequence(g2);
        sort(deg1.begin(), deg1.end());
        sort(deg2.begin(), deg2.end());
        if (deg1 != deg2) {
            return false;
        }

        map<int, vector<int>> degreeGroups1 = groupByDegree(g1);
        map<int, vector<int>> degreeGroups2 = groupByDegree(g2);

        map<int, int> mapping;
        set<int> used;
        return checkMapping(g1, g2, degreeGroups1, degreeGroups2, mapping, used);
    }

private:
    static int countEdges(const vector<vector<int>>& graph) {
        int sum = 0;
        for (const auto& adj : graph) {
            sum += adj.size();
        }
        return sum / 2; // each edge counted twice
    }

    static vector<int> getDegreeSequence(const vector<vector<int>>& graph) {
        vector<int> deg(graph.size());
        for (int i = 0; i < graph.size(); i++) {
            deg[i] = graph[i].size();
        }
        return deg;
    }

    static map<int, vector<int>> groupByDegree(const vector<vector<int>>& graph) {
        map<int, vector<int>> degreeMap;
        for (int i = 0; i < graph.size(); i++) {
            int degree = graph[i].size();
            degreeMap[degree].push_back(i);
        }
        return degreeMap;
    }

    static bool checkMapping(const vector<vector<int>>& g1, const vector<vector<int>>& g2,
            const map<int, vector<int>>& degGroups1, const map<int, vector<int>>& degGroups2,
            map<int, int>& mapping, set<int>& used) {
        if (mapping.size() == g1.size()) {
            return checkAdjacency(g1, g2, mapping);
        }

        for (const auto& pair : degGroups1) {
            int degree = pair.first;
            const vector<int>& vertices1 = pair.second;
            const vector<int>& vertices2 = degGroups2.at(degree);

            for (int v1 : vertices1) {
                if (mapping.find(v1) != mapping.end()) continue;
                
                for (int v2 : vertices2) {
                    if (used.find(v2) != used.end()) continue;

                    mapping[v1] = v2;
                    used.insert(v2);

                    if (checkMapping(g1, g2, degGroups1, degGroups2, mapping, used)) {
                        return true;
                    }
                    
                    mapping.erase(v1);
                    used.erase(v2);
                }
                return false;
            }
        }
        return false;
    }

    static bool checkAdjacency(const vector<vector<int>>& g1,
            const vector<vector<int>>& g2, const map<int, int>& mapping) {
        for (int u1 = 0; u1 < g1.size(); u1++) {
            int u2 = mapping.at(u1);
            for (int v1 : g1[u1]) {
                int v2 = mapping.at(v1);
                // Check if v2 is in the adjacency list of u2
                if (find(g2[u2].begin(), g2[u2].end(), v2) == g2[u2].end()) {
                    return false;
                }
            }
        }
        return true;
    }
};

int main() {
    // First graph
    cout << "Enter number of vertices in Graph 1: ";
    int V1;
    cin >> V1;
    cout << "Enter number of edges in Graph 1: ";
    int E1;
    cin >> E1;

    vector<vector<int>> g1(V1);

    cout << "Enter edges (u v) for Graph 1:" << endl;
    for (int i = 0; i < E1; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--; 
        g1[u].push_back(v);
        g1[v].push_back(u);
    }

    // Second graph
    cout << "Enter number of vertices in Graph 2: ";
    int V2;
    cin >> V2;
    cout << "Enter number of edges in Graph 2: ";
    int E2;
    cin >> E2;

    vector<vector<int>> g2(V2);

    cout << "Enter edges (u v) for Graph 2:" << endl;
    for (int i = 0; i < E2; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--; 
        g2[u].push_back(v);
        g2[v].push_back(u);
    }

    bool result = GraphIsomorphism::areIsomorphic(g1, g2);
    if (result) {
        cout << "Graphs are isomorphic." << endl;
    } else {
        cout << "Graphs are not isomorphic." << endl;
    }

    return 0;
}