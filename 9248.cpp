#include <iostream>
#include <utility>
#include <vector>
#define NIL -1
using namespace std;

void countingSort(vector<int> *sa, const vector<int> &rank, int stride) {
    int N = rank.size();
    vector<int> cnt(max(N, 256), 0);
    auto nextRank = [N, &rank](int sa, int stride) {
        return sa + stride < N ? rank[sa + stride] : 0;
    };
    for (int i = 0; i < N; i++) {
        cnt[nextRank(i, stride)]++;
    }
    int sum = 0;
    for (int i = 0; i < cnt.size(); i++) {
        int tmp = sum;
        sum += cnt[i];
        cnt[i] = tmp;
    }
    vector<int> temp_sa(N);
    for (int i = 0; i < N; i++) {
        temp_sa[cnt[nextRank((*sa)[i], stride)]++] = (*sa)[i];
    }
    *sa = std::move(temp_sa);
}

auto findSuffixArray(const string &s) -> vector<int> {
    int N = s.size();
    vector<int> sa(N), rank(N), temp_rank(N);
    for (int i = 0; i < N; i++) {
        sa[i] = i;
        rank[i] = s[i];
    }
    auto isDifferent = [&rank, N](int a, int b, int stride) {
        if (rank[a] == rank[b]) {
            return (a + stride < N && b + stride < N) ? (rank[a+stride] < rank[b+stride]) : (a > b);
        }
        return rank[a] < rank[b];
    };
    for (int k = 1; k <= N; k<<=1) {
        countingSort(&sa, rank, k);
        countingSort(&sa, rank, 0);
        int r = 1;
        temp_rank[sa[0]] = r;
        for (int i = 1; i < N; i++) {
            temp_rank[sa[i]] = isDifferent(sa[i-1], sa[i], k) ? ++r : r;
        }
        rank = temp_rank;
        if (r == N) break;
    }
    return sa;
}

auto findLongestCommonPrefix(const vector<int> &sa, const string &s) {
    int N = s.size();
    vector<int> phi(N);
    phi[sa[0]] = NIL;
    for (int i = 1; i < N; i++) {
        phi[sa[i]] = sa[i-1];
    }
    vector<int> plcp(N);
    int L;
    for (int i = L = 0; i < N; i++) {
        int prev = phi[i];
        if (prev == NIL) {
            plcp[i] = 0;
            continue;
        }
        while (i + L < N && prev + L < N && s[i + L] == s[prev + L]) L++;
        plcp[i] = L;
        L = max(L - 1, 0);
    }
    vector<int> lcp(N);
    for (int i = 0; i < N; i++) {
        lcp[i] = plcp[sa[i]];
    }
    return lcp;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    string s;
    cin>>s;
    auto sa = findSuffixArray(s);
    for (int suffix : sa) {
        cout << suffix + 1 << ' ';
    }
    cout << '\n';
    auto lcp = findLongestCommonPrefix(sa, s);
    cout << "x ";
    for (int i = 1; i < lcp.size(); i++) {
        cout << lcp[i] << ' ';
    }
}