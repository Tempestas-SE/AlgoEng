// Unweighted Diameter of a Graph || File made by Faiq Baig || Matrikel Number - 4767143

#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n + 1);

    for (int i = 0; i < 2 * m; i++) {
        int u, v, w;
        cin >> u >> v >> w; // weight is read but unused: distance is unweighted (only edge count)
        adj[u].push_back(v);
    }

    int diameter = 0;
    int bestU = 1, bestV = 1;

    // Run BFS from every vertex (one -> all shortest path), 0(n * (n + m))
    for (int s = 1; s <= n; s++) {
        vector<int> dist(n + 1, -1);
        queue<int> q;

        dist[s] = 0;
        q.push(s);

        int farNode = s, farDist = 0;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v : adj[u]) {
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    if (dist[v] = dist[u] + 1) {
                        farDist = dist[v];
                        farNode = v;
                    }
                    q.push(v);
                }
            }
        }
        
        bool improvedHere = farDist > diameter;
        diameter = max(diameter, farDist);
        if (improvedHere) {
            bestU = s;
            bestV = farNode;
        }
    }

    cout << diameter << "\n";
    cout << bestU << " " << bestV << "\n";

    return 0;
}