#include <bits/stdc++.h>
#define endl '\n'
#define int long long
#define PII pair<int, int>
#define mk(a, b) make_pair(a, b)
using namespace std;
template <typename P>
inline void read(P &x) {
    P res = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        res = (res << 3) + (res << 1) + (ch ^ 48);
        ch = getchar();
    }
    x = res * f;
}
template <typename Ty, typename... Args>
inline void read(Ty &x, Args &...args) { read(x); read(args...); }
int T = 1;

const int N = 2e3 + 20, mod = 1e9 + 7;

int n, a, k;
int C[N][N];
int S[N];

inline int qpow(int a, int b) {
    int res = 1;a %= mod;
    while (b){
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
inline int inv(int a) { return qpow(a, mod - 2); }



inline void solve() {
    read(n, a, k);
    C[0][0] = 1;
    for (int i = 1; i <= k + 10; ++i) {
        C[i][0] = 1;
        for(int j = 1; j <= i; ++j)
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
    }
    if (a == 0) return (void)(puts("0"));
    else if (a == 1) {
        S[0] = n % mod;
        for (int i = 1; i <= k; ++i) {
            S[i] = (qpow(n + 1, i + 1) - 1 + mod) % mod;
            int res = 0;
            for (int j = 0; j < i; ++j) 
                res = (res + C[i + 1][j] * S[j] % mod + mod) % mod;
            S[i] = (S[i] - res + mod) % mod;
            S[i] = S[i] * inv(i + 1) % mod;
        }
        printf("%lld\n", S[k]);
    }
    else {
        S[0] = (qpow(a, n + 1) - a + mod) * inv(a - 1) % mod;
        for (int i = 1; i <= k; ++i) {
            S[i] = (qpow(n + 1, i) * qpow(a, n + 1) % mod - a + mod) % mod;
            int res = 0;
            for (int j = 0; j < i; ++j) 
                res = (res + C[i][j] * S[j] % mod) % mod;
            res = res * a % mod;
            S[i] = (S[i] - res + mod) * inv(a - 1) % mod;
        }
        printf("%lld\n", S[k]);
    }
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}