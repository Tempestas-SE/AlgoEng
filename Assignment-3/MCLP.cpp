// MCLP File made by Faiq Baig || Matrikel Nummer - 4767143

#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>
#include <iostream>
#include <random> // Just an extra header

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  // Adjacency list 
  // adj[u] stores the pair (Neighbor, Weight)
  vector<vector<pair<int, int>>> adj(n + 1);

  // The input gives 2m directed arcs for undirected graphs
  // We store each arc exactly it appears
  for (int i = 0; i < 2 * m; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    adj[u].push_back(make_pair(v, w));
  }

  // inS[u] = 1 means node u is in set S 
  // inS[u] = 0 means node u is in V \ S 
  vector<char> inS(n + 1, 0);

  // Initial cut 
  // Put one node in S so both side are non-empty
  inS[1] = 1;

  // Compute the cut weight 
  //  Each unadirected edge appears twice in the adjacency, so divide by 2
  auto count_cut = [&]() -> long long {
    long long cut = 0;
    for (int u = 1; u <= n; u++) {
      for (size_t i = 0; i < adj[u].size(); i++) {
        int v = adj[u][i].first;
        int w = adj[u][i].second;

        // If the endpoints are in different blocks
        // Edge contributes to the cut
        if (inS[u] != inS[v]) {
          cut += w;
        }
      }
    }
    return cut / 2;
  };

  // Gain flipping of the node u 
  // Positive gain means moving u to the other side increases the cut
  auto gain = [&](int u) -> long long {
    long long delta = 0;
    for (size_t i = 0; i < adj[u].size(); i++) {
      int v = adj[u][i].first;
      int w = adj[u][i].second;

      // If u and v are currently on same side,
      // flipping u will add this edge to the same cut
      if (inS[u] == inS[v]) {
        delta += w;
      } else {
        // Otherwise the edge leaves the cut
        delta -= w;
      }
    }
    return delta;
  };

  // Random gen for shuffling node order each round
  // Fixed seeds keep the run deterministic and reproducible
  mt19937 rng(12345);

  // Node order used in each propagation round
  vector<int> order(n);
  for (int i = 0; i < n; i++) {
    order[i] = i + 1;
    }

  bool changed;
  do {
    changed = false;

  // Label propagation loop
  // Keep flipping vertices while some flip improves the cut
  shuffle(order.begin(), order.end(), rng);

  for (int i = 0; i < n; i++) {
            int u = order[i];

            // Flip only if it improves the cut
            if (gain(u) > 0) {
                inS[u] = !inS[u];
                changed = true;
            }
        }
    } while (changed);

  // Output of the cut weight and one block (S)
  cout << count_cut() << '\n';

  for (int u = 1; u <= n; u++) {
    if (inS[u]) {
      cout << u << ' ';
    }
  }
  cout << '\n';

  return 0;
} 