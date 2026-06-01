// Matriculation Number: 4767143 || Maximum Flow with Minimum Cut file made by Faiq Baig

#include <algorithm>
#include <climits>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
// Edge in the residual graph
struct Edge {
    int to;       // destination vertex
    int rev;      // index of reverse edge in g[to]
    long long cap; // remaining capacity
};
// Dinic's max flow implementation
class Dinic {
    vector<vector<Edge>> g; // adjacency list
    vector<int> level;      // BFS level graph
    vector<int> it;         // current edge pointer for DFS
    // BFS: builds level graph from source
    void bfs(int s) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (auto &e : g[v]) {
                if (e.cap > 0 && level[e.to] < 0) {
                    level[e.to] = level[v] + 1;
                    q.push(e.to);
                }
            }
        }
    }
    // DFS: sends flow along level graph
    long long dfs(int v, int t, long long f) {
        if (v == t) return f;
        for (int &i = it[v]; i < (int)g[v].size(); i++) {
            Edge &e = g[v][i];
            if (e.cap > 0 && level[v] < level[e.to]) {
                long long d = dfs(e.to, t, min(f, e.cap));
                if (d > 0) {
                    e.cap -= d;
                    g[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }
public:
    Dinic(int n) : g(n), level(n), it(n) {}
    // Adds directed edge with reverse edge (cap 0)
    void add_edge(int from, int to, long long cap) {
        g[from].push_back({to, (int)g[to].size(), cap});
        g[to].push_back({from, (int)g[from].size() - 1, 0});
    }
    // Computes max flow from s to t
    long long max_flow(int s, int t) {
        long long flow = 0;
        while (true) {
            bfs(s);
            if (level[t] < 0) break;          // no more augmenting paths
            fill(it.begin(), it.end(), 0);
            long long f;
            while ((f = dfs(s, t, LLONG_MAX)) > 0) {
                flow += f;
            }
        }
        return flow;
    }
    // BFS from s in residual graph; reachable nodes = s-side of min cut
    vector<bool> min_cut(int s) {
        vector<bool> vis(g.size(), false);
        queue<int> q;
        vis[s] = true;
        q.push(s);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (auto &e : g[v]) {
                if (e.cap > 0 && !vis[e.to]) {
                    vis[e.to] = true;
                    q.push(e.to);
                }
            }
        }
        return vis;
    }
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    Dinic dinic(n);
    // Read 2m directed arcs (two per undirected edge, same cap, opposite dir)
    for (int i = 0; i < 2 * m; i++) {
        int u, v;
        long long cap;
        cin >> u >> v >> cap;
        u--; v--;                           // convert to 0-indexed
        dinic.add_edge(u, v, cap);
    }
    int s, t;
    cin >> s >> t;
    s--; t--;
    // Compute max flow = min cut capacity
    long long flow = dinic.max_flow(s, t);
    cout << flow << "\n";
    // Find and output the s-side of the min cut
    auto cut = dinic.min_cut(s);
    for (int i = 0; i < n; i++) {
        if (cut[i]) {
            cout << i + 1 << " ";           // back to 1-indexed
        }
    }
    cout << "\n";
    return 0;
}