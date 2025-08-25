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

const int MaxN = 8e5 + 20, MaxM = 2e7 + 10, mod = 998244353;

int N, M, S, L;
int fac[MaxM], inv[MaxM], f[MaxN], g[MaxN], rev[MaxN], lim, len;

int qpow(int a, int b) {
    int res = 1ll;
    while(b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
int invv(int a) { return qpow(a, mod - 2); }
int C(int n, int m) { return fac[n] * inv[m] % mod * inv[n - m] % mod; }

void NTT(int *f, int flag) {
    for (int i = 0; i < lim; ++i) if (i < rev[i]) swap(f[i], f[rev[i]]);
    for (int h = 2; h <= lim; h <<= 1) {
        int w = qpow(114514, (mod - 1) / h);
        if (flag == -1) w = invv(w);
        for (int j = 0; j < lim; j += h) {
            int t1, t2, g = 1;
            for (int k = j; k < j + h / 2; k++, g = g * w % mod) {
                t1 = f[k] % mod, t2 = f[k + h / 2] * g % mod;
                f[k] = (t1 + t2) % mod, f[k + h / 2] = (t1 - t2 + mod) % mod;
            }
        }
    }
    if (flag == -1) {
        int invl = invv(lim);
        for (int i = 0; i < lim; ++i) f[i] = f[i] * invl % mod;
    }
}

inline void solve() {
    read(N, M, S, L);
    int up = max(N, L);
    inv[1] = inv[0] = fac[0] = 1;
    for (int i = 1; i <= up; ++i) fac[i] = fac[i - 1] * i % mod;
    inv[up] = invv(fac[up]);
    for (int i = up - 1; ~i; --i) inv[i] = inv[i + 1] * (i + 1) % mod;
    for (int i = 0; i <= L; ++i) {
        f[i] = (i & 1) ? (mod - inv[i]) : inv[i];
        g[i] = qpow(i, L) * inv[i] % mod;
    }
    lim = 1, len = 0;
    while (lim <= (L << 1)) lim <<= 1, len++;
    for (int i = 0; i < lim; ++i) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (len - 1));
    NTT(f, 1), NTT(g, 1);
    for (int i = 0; i < lim; ++i) f[i] = f[i] * g[i] % mod;
    NTT(f, -1);
    while (S--) {
        int n, m, k, ans = 0;
        read(n, m, k);
        for (int i = 0; i <= min(L, min(m, k)); ++i) ans = (ans + f[i] * fac[n - i] % mod * inv[m - i] % mod * inv[k - i] % mod) % mod;
        ans = (ans * fac[k] % mod * fac[m] % mod * inv[n] % mod);
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