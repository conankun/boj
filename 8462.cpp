#pragma GCC optimize("Ofast")
#include <algorithm>
#include <iostream>
#define BUCKET_SIZE 450
#define MAXN 100100
#define MAX_VAL 1000100
using ll = long long;
using namespace std;
int N, Q, arr[MAXN], cnt[MAX_VAL];
ll ans[MAXN], sum = 0;
inline int bucket(int idx) {
    return idx / BUCKET_SIZE;
}
struct Query {
    int s, e, idx;
    bool operator<(const Query &q) const {
        if (bucket(s) == bucket(q.s)) {
            return e < q.e;
        }
        return bucket(s) < bucket(q.s);
    }
} queries[MAXN];

inline void increment(int idx) {
    int &ks = cnt[arr[idx]];
    sum -= (ll)ks*ks*arr[idx];
    ks++;
    sum += (ll)ks*ks*arr[idx];
}

inline void decrement(int idx) {
    int &ks = cnt[arr[idx]];
    sum -= (ll)ks*ks*arr[idx];
    ks--;
    sum += (ll)ks*ks*arr[idx];
}

void solve() {
    int s = 0, e = 0;
    increment(0);
    for (int i = 0; i < Q; i++) {
        const auto [qs, qe, idx] = queries[i];
        while (s < qs) decrement(s++);
        while (s > qs) increment(--s);
        while (e < qe) increment(++e);
        while (qe < e) decrement(e--);
        ans[idx] = sum;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>N>>Q;
    for (int i = 0; i < N; i++) {
        cin>>arr[i];
    }
    for (int i = 0; i < Q; i++) {
        cin>>queries[i].s>>queries[i].e;
        queries[i].s--;
        queries[i].e--;
        queries[i].idx = i;
    }
    sort(queries, queries+Q);
    solve();
    for (int i = 0; i < Q; i++) {
        cout << ans[i] << '\n';
    }
}