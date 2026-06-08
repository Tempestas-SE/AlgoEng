// Topology Sort with a DAG File made by Faiq Baig || Matrikel Number: 4767143
// In this code, I use Kahn's algorithm: this repeatedly removes node with in-degree 0

#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>

using namespace std;

int main() {
    // Read number of vertices [n] and arcs [m]
    int n, m;
    scanf("%d %d", &n, &m);

    // Building the adjacency list and compute in-degrees
    // adj[i] stores all neighbours of node i (nodes are 1-indexed)
    vector<vector<int>> adj(n + 1);
    // inDeg[i] = number of incoming arcs to node i
    vector<int> inDeg(n + 1, 0);

    for (int i = 0; i < m; i++) {
      int u, v, w;
      scanf("%d %d %d", &u, &v, &w);
      // Adding directed edge u -> v (weight w is not needed for ordering)
      adj[u].push_back(v);
      // One more incoming edge to v
      inDeg[v]++;
    }

    /*
    Kahn's Algorithm - start with all nodes that have no
    incoming edges (in-degree = 0)
    */
   vector<int> zeroDeg; // This acts a queue of zero-degree nodes

   for (int i = 1; i <= n; i++) {
    if (inDeg[i] == 0) {
      zeroDeg.push_back(i);
    }
   }

   // Processing the nodes in topological order
   vector<int> topoOrder; // Will store the final topological order

   while (!zeroDeg.empty()) {
    // Take one node from the back (queue behaviour - 0(1))
    int u = zeroDeg.back();
    zeroDeg.pop_back();
    topoOrder.push_back(u);
   }
}
