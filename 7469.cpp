#include <algorithm>
#include <iostream>
#include <vector>
#define LEFT (node << 1)
#define RIGHT (LEFT + 1)
using namespace std;
struct MergeSortTree {
private:
    vector<vector<int>> tree;
    int N;
    int query(int s, int e, int node, int ns, int ne, int K) const {
        if (ns > e || ne < s) {
            return 0;
        }
        if (s <= ns && ne <= e) {
            return std::lower_bound(tree[node].begin(), tree[node].end(), K) - tree[node].begin();
        }
        int m = (ns + ne) >> 1;
        return query(s, e, LEFT, ns, m, K) + query(s, e, RIGHT, m + 1, ne, K);
    }
    void merge(int node, int s, int e) {
        if (s >= e) {
            return;
        }
        int m = (s + e) >> 1;
        merge(LEFT, s, m);
        merge(RIGHT, m + 1, e);
        tree[node].resize(tree[LEFT].size() + tree[RIGHT].size());
        std::merge(
                tree[LEFT].begin(),
                tree[LEFT].end(),
                tree[RIGHT].begin(),
                tree[RIGHT].end(),
                tree[node].begin());
    }
    void insert(int node, int s, int e, int idx, int value) {
        if (s == e && s == idx) {
            tree[node].push_back(value);
            return;
        }
        int m = (s + e) >> 1;
        if (idx <= m) {
            insert(LEFT, s, m, idx, value);
        } else {
            insert(RIGHT, m + 1, e, idx, value);
        }
    }
public:
    void insert(int idx, int value) {
        insert(1, 1, N, idx, value);
    }
    int query(int s, int e, int K) const {
        return query(s, e, 1, 1, N, K);
    }
    void merge() {
        merge(1, 1, N);
    }
    MergeSortTree(int size) : tree(4*size), N(size) {}
};

int find(int i, int j, int k, const MergeSortTree &mst) {
    int low = -1e9 - 10;
    int high = 1e9 + 10;
    int ans = low;
    while (low <= high) {
        int mid = (low + high) >> 1;
        if (mst.query(i, j, mid) <= k - 1) {
            ans = max(ans, mid);
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int N, M;
    cin>>N>>M;
    MergeSortTree mst(N);
    for (int i = 0; i < N; i++) {
        int x;
        cin>>x;
        mst.insert(i + 1, x);
    }
    mst.merge();
    while(M--) {
        int i, j, k;
        cin>>i>>j>>k;
        cout << find(i, j, k, mst) << '\n';
    }
}