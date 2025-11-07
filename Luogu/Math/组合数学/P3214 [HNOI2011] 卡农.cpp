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

const int N = 1e6 + 10;
const ll mod = 1e8 + 7;

int n, m;
ll a[N], f[N];
ll qpow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
ll fac(int a) {
    ll res = 1;
    while (a) res = res * a % mod, a--;
    return res;
}

inline void solve() {
    read(n, m);
    ll tot = qpow(2, n) - 1;
    a[0] = 1;
    for (int i = 1; i <= m; ++i) a[i] = a[i - 1] * (tot - i + 1 + mod) % mod;
    f[0] = 1;
    for (int i = 2; i <= m; ++i) {
        f[i] = a[i - 1];
        f[i] = (f[i] - f[i - 1] + mod) % mod;
        f[i] = (f[i] - f[i - 2] * (i - 1) % mod * (tot - (i - 2)) % mod + mod) % mod;
    }
    printf("%lld\n", f[m] * qpow(fac(m), mod - 2) % mod);
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}