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

const int N = 2e3 + 20, mod = 998244353;

int n;
int inv[N], mi[N], jc[N], invjc[N], h[N];

inline void solve() {
    read(n);
    for (int k = 0; k <= n; ++k) printf("%lld\n", jc[n] * jc[n] % mod * mi[k] % mod * invjc[k] % mod * h[n - k] % mod);
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    inv[1] = mi[0] = jc[0] = jc[1] = invjc[0] = invjc[1] = 1, mi[1] = 2;
    for (int i = 2; i <= 2000; ++i) jc[i] = (jc[i - 1] * i) % mod, inv[i] = inv[mod % i] * (mod - mod / i) % mod, invjc[i] = invjc[i - 1] * inv[i] % mod, mi[i] = (mi[i - 1] << 1) % mod;
    for (int i = 0; i <= 1000; ++i) 
        for (int j = 0; j <= i; ++j)
            (h[i] += ((j & 1) ? mod - 1 : 1) * invjc[j] % mod * mi[j] % mod * jc[i - j << 1] % mod * invjc[i - j] % mod * invjc[i - j] % mod) %= mod;
    read(T);
    while (T--) solve();
    return 0;
}