/*
Contracting Cluster file made by Faiq Baig | Matrikel Number: 4767143
This verison uses an unordered map with a packed key (faster, O(1) avg)
*/

#include <algorithm>
#include <iostream>
#include <cmath>
#include <cstdio>
#include <vector>
#include <unordered_map>

using namespace std;

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);

    // Read all 2m directed arcs
    int totalArcs = 2 * m;
    vector<int> arcU(totalArcs), arcV(totalArcs), arcW(totalArcs);
    for (int i = 0; i < totalArcs; i++) {
        scanf("%d %d %d", &arcU[i], &arcV[i], &arcW[i]);
    }

    // Cluster key node
    vector<int> key(n + 1);
    for (int i = 1; i <= n; i++) scanf("%d", &key[i]);

    // Big node weight = Count of nodes mapped into each cluster
    vector<long long> nodeWeight(k,0);
    for (int i = 1; i <= n; i++) nodeWeight[key[i]]++;

    // Pack (a, b) into a single 64-bit key as a * k + b
    // Allows use of unordered_map<long long, ...> instead of hasing pair
    // Avoids overhead of custom pair-has and gvie 0(1) average lookups
    unordered_map<long long, long long> edgeWeight;
    edgeWeight.reserve(totalArcs * 2);
    for (int i = 0; i < totalArcs; i++) {
        int a = key[arcU[i]];
        int b = key[arcV[i]];
        if (a != b) {
            long long packed = (long long)a * k + b;
            edgeWeight[packed] += arcW[i];
        }
    }

    // Unpack and count unordered pairs once (a < b)
    int M = 0;
    for (auto &e : edgeWeight) {
        int a = (int)(e.first / k);
        int b = (int)(e.first % k);
        if (a < b) M++;
    }

    printf("%d %d\n", k, M);

    for (auto &e : edgeWeight) {
        int a = (int)(e.first / k);
        int b = (int)(e.first % k);
        if (a < b) {
            long long w1 = e.second;
            long long w2 = edgeWeight[(long long)b * k + a]; // the reverse direction

            printf("%d %d %lld\n", a, b, w1);
            printf("%d %d %lld\n", b, a, w2);
        }
    }

    for (int c = 0; c < k; c++) printf("%lld\n", nodeWeight[c]);

    return 0 ;
}