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

const int N = 1e5 + 10, mod = 1e5 + 3;

int n, k, cnt;
int a[N];
ll f[N];
ll qpow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

inline void solve() {
    read(n, k);
    for (int i = 1; i <= n; ++i) read(a[i]);
    for (int i = n; i; --i)
        if (a[i]) {
            cnt++;
            for (int j = 1; j * j <= i; ++j) 
                if (i % j == 0) {
                    a[j] ^= 1;
                    if (j * j != i) a[i / j] ^= 1;
                }
        }
    f[n + 1] = 0;
    for (int i = n; i; --i) {
        ll tmp = 1ll * (n - i) * f[i + 1] % mod;
        tmp = (tmp + 1ll * n) % mod;
        tmp = tmp * qpow(i, mod - 2) % mod;
        f[i] = tmp;
    }
    ll tmp = 0;
    if (cnt <= k) tmp = cnt;
    else {
        for (int i = cnt; i > k; --i) tmp = (tmp + f[i]) % mod;
        tmp = (tmp + k) % mod;
    }
    for (int i = 1; i <= n; ++i) tmp = (tmp * 1ll * i) % mod;
    printf("%lld\n", tmp);
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}