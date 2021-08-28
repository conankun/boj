#include <iostream>
#include <vector>
#define LEFT (node << 1)
#define RIGHT (LEFT + 1)
using ui = unsigned int;
using namespace std;

class SegTree {
private:
    vector<ui> tree, lazy;
    int N;
    inline bool isLeaf(int ns, int ne) {
        return ns == ne;
    }

    inline int intervalSize(int s, int e) {
        return e - s + 1;
    }

    void propagate(int node, int ns, int ne) {
        if (!lazy[node]) {
            return;
        }
        if (!isLeaf(ns, ne)) {
            lazy[LEFT] ^= lazy[node];
            lazy[RIGHT] ^= lazy[node];
        }
        if (intervalSize(ns, ne) & 1) {
            tree[node] ^= lazy[node];
        }
        lazy[node] = 0;
    }
    void update(int s, int e, int node, int ns, int ne, ui val) {
        if (e < ns || s > ne) {
            return;
        }
        if (s <= ns && ne <= e) {
            lazy[node] ^= val;
            propagate(node, ns, ne);
            return;
        }
        int m = (ns + ne) >> 1;
        update(s, e, LEFT, ns, m, val);
        update(s, e, RIGHT ,m + 1, ne, val);
        tree[node] = tree[LEFT] ^ tree[RIGHT];
    }
    int query(int s, int e, int node, int ns, int ne) {
        propagate(node, ns, ne);
        if (e < ns || s > ne) {
            return 0;
        }
        if (isLeaf(ns, ne)) {
            return tree[node];
        }
        int m = (ns + ne) >> 1;
        return query(s, e, LEFT, ns, m) ^ query(s, e, RIGHT, m + 1, ne);
    }
public:
    void update(int s, int e, ui val) {
        update(s, e, 1, 1, N, val);
    }
    int query(int s, int e) {
        return query(s, e, 1, 1, N);
    }
    SegTree(int size) : tree(size << 2), lazy(size << 2), N(size) {}
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int N;
    cin>>N;
    SegTree seg(N);
    for (int i = 1; i <= N; i++) {
        ui x;
        cin>>x;
        seg.update(i, i, x);
    }
    int Q;
    cin>>Q;
    while (Q--) {
        ui t;
        cin>>t;
        if (t == 1) {
            ui a,b,c;
            cin>>a>>b>>c;
            seg.update(a+1,b+1,c);
        } else {
            int a;
            cin>>a;
            cout << seg.query(a+1, a+1) << '\n';
        }
    }
}