#include <iostream>
#include <vector>
#define NIL -1
using namespace std;
int N;
string s;

void countingSort(vector<int> &sa, const vector<int> &rank, int stride) {
    vector<int> cnt(max(256, N));
    auto nextRank = [&rank](int idx, int stride) {
        return idx + stride < N ? rank[idx + stride] : 0;
    };
    for (int i = 0; i < N; i++) {
        cnt[nextRank(i, stride)]++;
    }
    int sum = 0;
    for (int i = 0; i < cnt.size(); i++) {
        int tmp = cnt[i];
        cnt[i] = sum;
        sum += tmp;
    }
    vector<int> temp_sa(N);
    for (int i = 0; i < N; i++) {
        temp_sa[cnt[nextRank(sa[i], stride)]++] = sa[i];
    }
    sa = std::move(temp_sa);
}

auto findSuffixArray() -> vector<int> {
    vector<int> sa(N), rank(N), temp_rank(N);
    for (int i = 0; i < N; i++) {
        sa[i] = i;
        rank[i] = s[i];
    }
    auto isDifferent = [&rank](int a, int b, int stride) {
        if (rank[a] == rank[b]) {
            return (a + stride < N && b + stride < N) ? (rank[a+stride] < rank[b+stride]) : (a > b);
        }
        return rank[a] < rank[b];
    };
    for (int stride = 1; stride <= N; stride <<= 1) {
        countingSort(sa, rank, stride);
        countingSort(sa, rank, 0);
        int r;
        temp_rank[sa[0]] = r = 1;
        for (int i = 1; i < N; i++) {
            temp_rank[sa[i]] = isDifferent(sa[i-1], sa[i], stride) ? ++r : r;
        }
        rank = temp_rank;
        if (r == N) break;
    }
    return sa;
}

auto findLcp(const vector<int> &sa) -> int {
    vector<int> phi(N);
    phi[sa[0]] = NIL;
    for (int i = 1; i < N; i++) {
        phi[sa[i]] = sa[i-1];
    }
    int L = 0;
    int ans = 0;
    for (int i = 0; i < N; i++) {
        int prev = phi[i];
        if (prev == NIL) {
            continue;
        }
        while (i + L < N && prev + L < N && s[i + L] == s[prev + L]) L++;
        ans = max(L, ans);
        L = max(L-1, 0);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>N;
    cin>>s;
    auto sa = findSuffixArray();
    cout << findLcp(sa);
}