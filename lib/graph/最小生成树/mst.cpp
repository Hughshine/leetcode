//  Prim: 从一个点开始，不断将MST此时向外连接的最短边加入树。
#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> PII;

int arr[1024][1024];

struct Edge {
    int in;
    int out;
    int weight;
} edges[2000];

void kruskal();
void prim();



int main() {
    // kruskal();
    prim();
}

void prim() {
    int m;
    cin >> m;
    for(int i=0; i<m; i++) {
        for(int j=0; j<m; j++) {
            cin >> arr[i][j];
        }
    }
    vector<bool> inMST(m, false);
    vector<int> keys(m, INT_MAX);
    vector<int> pre(m, -1);

    auto cmp = [](PII p1, PII p2) {
        return p1.first > p2.first;
    };

    // Using lamda with decltype is a good choice. 
    // But 是最大堆还是最小堆，和sort的规律似乎不一样。 
    // priority_queue<PII, std::vector<PII>, std::greater<PII>> pq;
    priority_queue<PII, std::vector<PII>, decltype(cmp)> pq(cmp);

    int weight = 0;
    pq.push(PII(0, 0));
    keys[0] = 0;
    while(!pq.empty()) {
        PII pair = pq.top();
        pq.pop();
        int u = pair.second;
        if(inMST[u] == true) continue;  // 正确性没有影响，认为有性能的提速
        inMST[u] = true;
        for(int v=0; v<m; v++) { 
            // 无需在意重复进入队列，先进去的不够小的，后面加入，会提升到前面。
            if(!inMST[v] && keys[v] > arr[u][v]) {
                keys[v] = arr[u][v];
                pq.push(PII(keys[v], v));
                pre[v] = u;
            }
        }
    }
    for(int i=0; i<m; i++) {
        cout << pre[i] << " - " << i << ": " << keys[i] << endl;
        weight += keys[i];
    }
    cout << weight;
}


void kruskal() {
    int m;
    cin >> m;
    for(int i=0; i<m; i++) {
        for(int j=0; j<m; j++) {
            cin >> arr[i][j];
        }
    }
    int ecount = 0;
    for(int i=0; i<m; i++) {
        for(int j=i+1; j<m; j++) {
            if(arr[i][j] < 0) 
                continue;
            edges[ecount].in = i;
            edges[ecount].out = j;
            edges[ecount].weight = arr[i][j];
            ecount++;
        }
    }
    sort(edges, edges+ecount, [](Edge e1, Edge e2) {
        return e1.weight < e2.weight;
    });
    set<int> nodes;
    int weight = 0;
    for(int i=0; i<ecount; i++) {
        if(nodes.count(edges[i].in) && nodes.count(edges[i].out)) {
            continue;
        }
        nodes.insert(edges[i].in);
        nodes.insert(edges[i].out);
        weight += edges[i].weight;
        if(nodes.size() == m) {
            cout << weight;
        }
    }
}