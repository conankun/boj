#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int> findSuffixArray(const string &s) {
    int N = s.size();
    vector<int> ret(N);
    vector<int> rank(N);
    vector<int> temp_rank(N);
    for (int i = 0; i < N; i++) {
        ret[i] = i;
        rank[i] = s[i];
    }
    for (int sz = 1;; sz<<=1) {
        auto cmp = [&rank, sz, N](int a, int b) {
            if (rank[a] == rank[b]) {
                return (a + sz < N && b + sz < N) ? (rank[a+sz] < rank[b+sz]) : (a > b);
            }
            return rank[a] < rank[b];
        };
        sort(ret.begin(), ret.end(), cmp);
        int r = 0;
        temp_rank[ret[0]] = r;
        for (int i = 1; i < N; i++) {
            if (cmp(ret[i-1], ret[i])) r++;
            temp_rank[ret[i]] = r;
        }
        for (int i = 0; i < N; i++) {
            rank[i] = temp_rank[i];
        }
        if (r == N - 1) break;
    }
    return ret;
}
int main() {
    string s;
    cin>>s;
    auto sa = findSuffixArray(s);
    for (int x : sa) {
        cout << x << '\n';
    }
}