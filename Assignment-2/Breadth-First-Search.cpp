#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

struct Edge {
  int to, weight;
};

int main() {
  int n, m;
  scanf("%d %d", &n, &m);

  vector<vector<Edge>> adj(n + 1);

  // Read 2m directed arcs (each undirected edge is given twice)
  for (int i = 0; i < 2 * m; i++) {
    int u, v, w;
    scanf("%d %d %d", &u, &v, &w);
    adj[u].push_back({v, w});
  }

  int s, t;
  scanf("%d %d", &s, &t);

  // dist[i] = accumalated weight along BFS path to node i 
  vector<int> dist(n + 1, -1);
  vector<int> parent(n + 1, -1);

  queue<int> q;
  q.push(s);
  dist[s] = 0;

  while (!q.empty()) {
    int cur = q.front(); q.pop();

    for (const Edge& e : adj[cur]) {
      if (dist[e.to] == -1) {
        dist[e.to] = dist[cur] + e.weight;
        parent[e.to] = cur;
        q.push(e.to);
      }
    }
  }

  // Trace back path from t to s using parent array
  vector<int> path;
  for (int cur = t; cur != -1; cur = parent[cur])
    path.push_back(cur);
  reverse(path.begin(), path.end());

  int edges = (int)path.size() -1;
  printf("%d\n%d\n", edges, dist[t]);
  for (int i = 0; i < (int)path.size(); i++) {
    if (i) printf(" ");
    printf("%d", path[i]);
  }

  printf("\n");

  return 0;
}
