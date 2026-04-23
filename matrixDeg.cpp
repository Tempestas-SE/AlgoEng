#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    //Degree of each vertex
    vector<int> deg(n+1, 0);
    
    //Weighted degree of each vertex
    vector <long long> wdeg(n+1, 0);
    
    //Sum of all arc weights
    long long sumWeights = 0;
    
    //Read all 2m directed arcs
    for (int i = 0; i < 2 * m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        
        //Count Degree and Weighted Degree for the source code
        deg[u]++;
        wdeg[u]+=w;
        
        //Add all the weights
        sumWeights += w;
    }
    
    int maxDeg = deg[1];
    int minDeg = deg[1];
    long long maxWDeg = wdeg[1];
    long long minWDeg = wdeg[1];
    
    //Search for max and min value
    for (int i = 1; i <= n; i++) {
        maxDeg = max(maxDeg, deg[i]);
        minDeg = min(minDeg, deg[i]);
        maxWDeg = max(maxWDeg, wdeg[i]);
        minWDeg = min(minWDeg, wdeg[i]);
    }
    
    //Since each undirected edge is given twice
    cout << maxDeg << '\n';
    cout << minDeg << '\n';
    cout << maxWDeg << '\n';
    cout << minWDeg << '\n';
    cout << sumWeights / 2 << '\n';
    
    return 0;
}
