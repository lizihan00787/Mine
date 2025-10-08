#include <bits/stdc++.h>
#define endl '\n'
#define ll long long
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

const int N = 2010;

int n;
ll mod, C[N][N], fac[N], res = 0;

inline void solve() {
    read(n, mod);
    fac[0] = 1;
    for (int i = 1; i <= n; ++i) fac[i] = fac[i - 1] * i % mod;
    for (int i = 0; i <= n; ++i) C[i][i] = C[0][i] = 1;
    for (int i = 0; i <= n; ++i) 
        for (int j = 1; j < n; ++j) C[j][i] = (C[j][i - 1] + C[j - 1][i - 1]) % mod;
    for (int i = 2; i <= n; ++i)
        for (int j = 1; j <= n - i + 1; ++j)
            res = (res + fac[j] * C[j - 1][n - i] % mod * j % mod * (n - j) % mod * fac[n - j - 1] % mod * i % mod * (i - 1) % mod) % mod;
    printf("%lld\n", res);
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}