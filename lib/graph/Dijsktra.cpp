#define _CRT_SBCURE_NO_DEPRECATE
// #include<bits/stdc++.h>
#include <set>
#include <cmath>
#include <queue>
#include <stack>
#include <vector>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <functional>
#include <climits>
using namespace std;
const int maxn = 110;
const int INF = 0x3f3f3f3f;

int main() {
    int e_count = 0, n_count = 0;
    cin >> e_count >> n_count;
    int start = 1, target = n_count;
    vector<vector<int>> graph(n_count+1, vector<int>(n_count+1, -1));
    for(int i=1; i<=n_count; i++) {
        graph[i][i] = 0;
    }
    for(int i=0; i<e_count; i++) {
        int n1, n2, val;
        cin >> n1 >> n2 >> val;
        graph[n1][n2] = val;
        graph[n2][n1] = val;
    }
    for(int i=1; i<=n_count; i++) {
        for(int j=1; j<=n_count; j++) {
            cout << graph[i][j] << " ";
        }
        cout << endl;
    }
    vector<bool> visited(n_count+1, false);
    vector<int> dists(n_count+1, INT_MAX);
    dists[start] = 0;
    int cur_node = start;
    while(true) {
        visited[cur_node] = true;
        int _min_dist = INT_MAX;
        int next_node = -1;
        for(int i=1; i<=n_count; i++) {
            if(visited[i] == false) {
                if(graph[cur_node][i] < 0) continue;
                dists[i] = min(dists[i], dists[cur_node] + graph[cur_node][i]);
                if(dists[i] < _min_dist) {
                    _min_dist = dists[i];
                    next_node = i;
                }
            }
        }
        if(next_node == -1) break;
        cur_node = next_node;
    }
    for(int i=1; i<=n_count; i++) {
        cout << dists[i] << " ";
    }
    cout << endl;
    cout << dists[target] << endl;
}