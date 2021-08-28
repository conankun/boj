#include <iostream>
#include <vector>
#define MAX_PHI ((int)1e5)
using ll = long long;
using namespace std;
ll PHI[MAX_PHI+1];
bool is_comp[MAX_PHI+1];
vector<ll> primes;
void sieve() {
    for (int i = 1; i <= MAX_PHI; i++) {
        PHI[i] = i;
    }
    for (int i = 2; i <= MAX_PHI; i++) {
        if (!is_comp[i]) {
            primes.push_back(i);
            PHI[i] = i-1;
            for (int j = 2; i * j <= MAX_PHI; j++) {
                is_comp[i*j]=true;
                PHI[i*j] -= PHI[i*j]/i;
            }
        }
        if (i&1) i++;
    }
}

ll phi(ll M) {
    ll ret = 1;
    for (ll prime : primes) {
        if (M % prime == 0) {
            while (M % prime == 0) {
                ret *= prime;
                M /= prime;
            }
            ret -= ret / prime;
            if (M <= MAX_PHI) {
                break;
            }
        }
    }
    return M > MAX_PHI ? ret * (M - 1) : ret * PHI[M];
}

ll exp(ll N, ll K, ll M) {
    ll unit = N;
    ll ans = 1LL;
    while (K > 0) {
        if (K&1) {
            ans *= unit;
            ans %= M;
        }
        unit *= unit;
        unit %= M;
        K >>= 1;
    }
    return ans;
}

ll find(ll N, ll M) {
    if (M <= 1) {
        return 0;
    }
    if (N == 1) {
        return 1 % M;
    } else if (N == 2) {
        return 2 % M;
    } else if (N == 3) {
        return 9 % M;
    } else if (N == 4) {
        return exp(4, 9, M);
    }
    ll cp = phi(M);
    return exp(N, find(N-1, cp) + cp, M) % M;
}

ll solve(ll N, ll M) {
    sieve();
    return find(N, M);
}

int main() {
    ll N, M;
    sieve();
    cin>>N>>M;
    cout << solve(N, M);
}