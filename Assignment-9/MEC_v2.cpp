/* 
Min-Edge-Coloring (MEC) File made by Faiq Baig || Matrikel Number : 4767143
This version uses Edge Ordering Heuristic - sorts by decreasing degree sum before coloring, 
typically reducing the number of colors used. Also switches from vector<bool> to vector<char>
(from bit-packed, that is slow to byte-addressed, that is fast.)
*/

#include <cstdio>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Edge {
    int u, v;
    int color;
};

int main() {
    // Read input
    int n, m;
    scanf("%d %d", &n, &m);

    if (m == 0) {
        printf("0\n");
        return 0;
    }

    // Read arcs and compute degrees
    vector<int> deg(n + 1, 0);
    vector<Edge> edges;
    edges.reserve(m);

    for (int i = 0; i < 2 * m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        deg[u]++;
        if (u < v) {
            edges.push_back({u, v, 0});
        }
    }

    // Find max degree
    int D = 0;
    for (int v = 1; v <= n; v++) {
        D = max(D, deg[v]);
    }
    int max_color = 2 * D - 1;

    /*
    Sort edges by degree susm descending: high degree vertices get colored first
    This way it produces more compact colorings (closer to optimal D)
    */
   sort(edges.begin(), edges.end(), [&](const Edge &a, const Edge &b)
{
    return (deg[a.u] + deg[a.v]) > (deg[b.u] + deg[b.v]);
   });

   // Use vector<char> instead of vector<bool> for faster random access
   vector<vector<char>> used(n + 1, vector<char>(max_color + 1, 0));

   // Greedy coloring on reorderd edges
   for (Edge &e : edges) {
    for (int c = 1; c <= max_color; c++) {
        if (!used[e.u][c] && !used[e.v][c]) {
            e.color = c;
            used[e.u][c] = 1;
            used[e.v][c] = 1;
            break;
            }
        }
   }

   // Determine the number of colors used
   int used_colors = 0;
   for (Edge &e : edges) {
    used_colors = max(used_colors, e.color);
   }

   // Output
   printf("%d\n", used_colors);
   for (Edge &e : edges) {
    printf("%d %d %d\n", e.u, e.v, e.color);
   }
   
   return 0;
}