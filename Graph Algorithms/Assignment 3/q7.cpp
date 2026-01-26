#include <iostream>
#include <vector>
#include <numeric>
#include <functional>
using namespace std;

class Net {
private:
    int n;
    vector<vector<int>> adj;

public:
    Net(int n) : n(n), adj(n) {}

    void linkNodes(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    bool edgeExists(int u, int v) const {
        for (int x : adj[u])
            if (x == v) return true;
        return false;
    }

    bool eulerBreaks() const {
        int edges = 0;
        for (int i = 0; i < n; i++) {
            if (adj[i].size() > 5) return true;
            edges += adj[i].size();
        }
        edges /= 2;
        if (n >= 3 && edges > 3 * n - 6) return true;
        return false;
    }

    bool hasK5() const {
        if (n < 5) return false;

        vector<int> nodes(n);
        iota(nodes.begin(), nodes.end(), 0);
        vector<int> pickSet(5);

        function<bool(int,int)> choose = [&](int start, int depth) {
            if (depth == 5) {
                for (int i = 0; i < 5; i++)
                    for (int j = i + 1; j < 5; j++)
                        if (!edgeExists(pickSet[i], pickSet[j]))
                            return false;
                return true;
            }
            for (int i = start; i <= n - (5 - depth); i++) {
                pickSet[depth] = nodes[i];
                if (choose(i + 1, depth + 1)) return true;
            }
            return false;
        };

        return choose(0, 0);
    }

    bool hasK33() const {
        if (n < 6) return false;

        vector<int> nodes(n);
        iota(nodes.begin(), nodes.end(), 0);
        vector<int> pickSet(6);

        function<bool(int,int)> choose = [&](int start, int depth) {
            if (depth == 6) {
                for (int mask = 0; mask < (1 << 6); mask++) {
                    if (__builtin_popcount(mask) != 3) continue;

                    vector<int> A, B;
                    for (int i = 0; i < 6; i++)
                        (mask & (1 << i)) ? A.push_back(pickSet[i]) : B.push_back(pickSet[i]);

                    bool ok = true;
                    for (int a : A)
                        for (int b : B)
                            if (!edgeExists(a, b)) ok = false;

                    if (ok) return true;
                }
                return false;
            }

            for (int i = start; i <= n - (6 - depth); i++) {
                pickSet[depth] = nodes[i];
                if (choose(i + 1, depth + 1)) return true;
            }
            return false;
        };

        return choose(0, 0);
    }

    bool isFlat() const {
        if (eulerBreaks()) return false;
        if (hasK5() || hasK33()) return false;
        return true;
    }
};

int main() {
    Net g1(8);
    g1.linkNodes(0,4);
    g1.linkNodes(0,5);
    g1.linkNodes(0,7);
    g1.linkNodes(1,4);
    g1.linkNodes(1,5);
    g1.linkNodes(1,6);
    g1.linkNodes(2,5);
    g1.linkNodes(2,6);
    g1.linkNodes(2,7);
    g1.linkNodes(3,4);
    g1.linkNodes(3,6);
    g1.linkNodes(3,7);

    cout << "\nGraph 1: " << (g1.isFlat() ? "Planar\n" : "Not Planar\n");

    Net g2(9);
    g2.linkNodes(0,1);
    g2.linkNodes(0,3);
    g2.linkNodes(0,3);
    g2.linkNodes(0,5);
    g2.linkNodes(0,8);
    g2.linkNodes(1,2);
    g2.linkNodes(1,8);
    g2.linkNodes(2,3);
    g2.linkNodes(2,5);
    g2.linkNodes(2,7);
    g2.linkNodes(3,4);
    g2.linkNodes(3,5);
    g2.linkNodes(3,7);
    g2.linkNodes(4,5);
    g2.linkNodes(4,6);
    g2.linkNodes(5,6);
    g2.linkNodes(5,7);
    g2.linkNodes(6,7);
    g2.linkNodes(7,8);

    cout << "Graph 2: " << (g2.isFlat() ? "Planar\n" : "Not Planar\n");

    Net g3(6);
    g3.linkNodes(0,1);
    g3.linkNodes(0,2);
    g3.linkNodes(0,3);
    g3.linkNodes(0,4);
    g3.linkNodes(0,5);
    g3.linkNodes(1,2);
    g3.linkNodes(1,3);
    g3.linkNodes(1,4);
    g3.linkNodes(1,5);
    g3.linkNodes(2,3);
    g3.linkNodes(2,4);
    g3.linkNodes(2,5);
    g3.linkNodes(3,4);
    g3.linkNodes(3,5);
    g3.linkNodes(4,5);

    cout << "Graph 3: " << (g3.isFlat() ? "Planar\n" : "Not Planar\n");
}
