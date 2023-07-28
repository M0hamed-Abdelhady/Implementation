#include <bits/stdc++.h>

using namespace std;

#define ll long long


class SegmentTree {
    vector<ll> tree, lazy;
    int n, opposite = INT_MIN;

    ll left(int node) { return (node << 1); }

    ll right(int node) { return (node << 1 | 1); }

    ll cmp(ll a, ll b) {
        if (!~a)return b;
        if (!~b)return a;
        return max(a, b);
    }

    void propagate(int L, int R, int node) {
        if (~lazy[node]) {
            tree[node] = lazy[node];
            if (L != R)
                lazy[left(node)] = lazy[right(node)] = lazy[node];
            lazy[node] = -1;
        }
    }

    void build(vector<ll> &x) {
        n = x.size();
        if (n & (n - 1))n = 1 << (__lg(n) + 1);
        tree.assign(n << 1, opposite), lazy.assign(n << 1, -1);
        for (int i = 0; i < x.size(); ++i) tree[n + i] = x[i];
        for (int i = n - 1; i; --i) tree[i] = cmp(tree[left(i)], tree[right(i)]);
    }

    void update(int L, int R, int node, int Lq, int Rq, int value) {
        propagate(L, R, node);
        if (Lq > R || Rq < L)return;
        if (L == Lq && R == Rq) {
            lazy[node] = value;
            propagate(L, R, node);
            return;
        }
        int mid = L + R >> 1;
        update(L, mid, left(node), Lq, min(mid, Rq), value);
        update(mid + 1, R, right(node), max(Lq, mid + 1), Rq, value);
        if (L != R) {
            tree[node] = cmp(tree[left(node)], tree[right(node)]);
        }
    }

    ll RMQ(int L, int R, int node, int Lq, int Rq) {
        propagate(L, R, node);
        if (L == Lq && R == Rq) return tree[node];
        if (Lq > R || Rq < L)return opposite;
        int mid = L + R >> 1;
        return cmp(RMQ(L, mid, left(node), Lq, min(mid, Rq)),
                   RMQ(mid + 1, R, right(node), max(Lq, mid + 1), Rq));
    }

public:
    SegmentTree();

    SegmentTree(vector<ll> &b) { build(b); }

    void update(int L, int R, int value) { update(0, n - 1, 1, L, R, value); }

    void update(int i, int value) { update(0, n - 1, 1, i, i, value); }

    ll RMQ(int L, int R) { return RMQ(0, n - 1, 1, L, R); }
};


int main() {
    vector<ll> a = {1, 2, 3, 4, 5};
    SegmentTree tree(a);
    tree.update(0, 2, 120);
//  update range from L to R
    tree.update(4, 150);
//  update index i
    cout << tree.RMQ(2, 3) << '\n';
    cout << tree.RMQ(2, 4) << '\n';
//  Range Maximum Query
    return 0;
}
