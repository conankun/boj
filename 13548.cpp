#include <iostream>
#include <vector>
#define BUCKET_SIZE 320
#define MAX_NUM 100100
using namespace std;
inline int bucket(int idx) {
    return idx / BUCKET_SIZE;
}
struct Query {
    int s,e, idx;
    bool operator<(const Query &q) const {
        return (bucket(s) == bucket(q.s)) ? (e < q.e) : (bucket(s) < bucket(q.s));
    }
};

vector<int> cnt;
vector<int> freq;
int ans = 1;

void increment(int v) {
    cnt[v]++;
    freq[cnt[v]-1]--;
    freq[cnt[v]]++;
    if (freq[cnt[v]] && cnt[v] > ans) {
        ans = cnt[v];
    }
}

void decrement(int v) {
    cnt[v]--;
    freq[cnt[v]+1]--;
    freq[cnt[v]]++;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int N;
    cin>>N;
    vector<int> seq(N);
    cnt.assign(MAX_NUM, 0);
    freq.assign(N, 0);
    for (int i = 0; i < N; i++) {
        cin>>seq[i];
    }
    int Q;
    cin>>Q;
    vector<Query> queries(Q);
    for (int i = 0; i < Q; i++) {
        cin>>queries[i].s>>queries[i].e;
        queries[i].s--, queries[i].e--;
        queries[i].idx = i;
    }
    sort(queries.begin(), queries.end());
    int s = 0, e = 0;
    cnt[seq[0]]=1;
    freq[1]=1;
    vector<int> qans(Q);
    for (const auto [qs,qe,idx]: queries) {
        while (s < qs) decrement(seq[s++]);
        while (s > qs) increment(seq[--s]);
        while (e < qe) increment(seq[++e]);
        while (e > qe) decrement(seq[e--]);
        while (!freq[ans]) ans--;
        qans[idx] = ans;
    }
    for (int answer : qans) {
        cout << answer << '\n';
    }
}