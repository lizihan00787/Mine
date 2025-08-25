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

const int N = 1e7 + 10, mod = 998244353;

int n, m, k;
int invfac[N], id[N], S[N];
int p[N], tp;

ll qpow(ll a, ll b) {
    ll res = 1ll; a %= mod;
    while(b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

inline void solve() {
    read(n, m, k);
    if (m == 1) { printf("%lld\n", qpow(n, k)); return; }
    invfac[1] = id[1] = 1;
    for (int i = 2; i <= k; ++i) {
        if (!id[i]) id[i] = qpow(p[++tp] = i, k), invfac[i] = qpow(i, mod - 2);
        for (int j = 2, t; j <= tp && (t = i * p[j]) <= k; ++j) {
            id[t] = 1ll * id[i] * id[p[j]] % mod;
            invfac[t] = 1ll * invfac[i] * invfac[p[j]] % mod;
            if (i % p[j] == 0) break;
        }
    }
    if (n > k) {
        int p = qpow(m, mod - 2);
        ll C = 1, x = 1; S[k] = 1;
        for (int i = k - 1; i; --i) {
            C = C * (n - i - 1) % mod * invfac[k - i] % mod; // 递推算下降幂和阶乘之比就是组合数
            x = x * (mod - p) % mod; // -p 的 k - i次方
            S[i] = (1ll * S[i + 1] * (mod + 1 - p) + C * x) % mod;
        }
        C = x = 1; ll ans = 0;
        for (int i = 1; i <= k; ++i) {
            x = x * p % mod;
            C = C * (n - i + 1) % mod * invfac[i] % mod;
            ans = (ans + x * C % mod * id[i] % mod * S[i] % mod) % mod;
        }
        printf("%lld\n", ans);
    }
    else {
        int p = qpow(m, mod - 2), q = mod + 1 - p;
        ll x1 = 1, x2 = qpow(q, n), C = 1, ans = 0;
        q = qpow(q, mod - 2);
        for (int i = 1; i <= k; ++i) {
            x1 = x1 * p % mod;
            x2 = x2 * q % mod;
            C = C * (n - i + 1) % mod * invfac[i] % mod;
            ans = (ans + x1 * x2 % mod * C % mod * id[i]) % mod;
        }
        printf("%lld\n", ans);
    }
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}