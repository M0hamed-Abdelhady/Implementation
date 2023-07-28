#include <bits/stdc++.h>

using namespace std;

#define ll long long


const int N = 1e5 + 3;

int logs[N];
int sparse[N][19];

void build(vector<int> &value) {
//  building sparse table (RMQ) for value
    int n = value.size() - 1;
    int lOG = __lg(n + 1) + 1;
    for (int sz = 0; sz < lOG; ++sz) {
        for (int i = 0; i + (1 << sz) - 1 <= n; ++i) {
            if (!sz)sparse[i][sz] = value[i];
            else {
                sparse[i][sz] = max(sparse[i][sz - 1], sparse[i + (1 << (sz - 1))][sz - 1]);
            }
        }
    }
}


int RMQ(int l, int r) {
//   get max in range from l to r
    int log = logs[r - l + 1];
    return max(sparse[l][log], sparse[r - (1 << log) + 1][log]);
}


int main() {
//  preprocessing for log2(sz)
//  efficiently find x satisfy 2^x <= sz ---> x = logs[sz]
    logs[1] = 0;
    for (int i = 2; i < N; ++i) {
        logs[i] = logs[i / 2] + 1;
    }

    vector<int> a = {1, 21, 3, 4, 5};
    build(a);
    cout << RMQ(2, 4) << '\n';
    cout << RMQ(0, 2) << '\n';
//  Range Maximum Query
    return 0;
}