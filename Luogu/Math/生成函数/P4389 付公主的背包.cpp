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

const int mod = 998244353;
const int N = 2e5 + 7e4 + 7e3 + 7e2 + 1;

int n, m;
int X[N], Y[N], k, TT[N];

namespace Poly {
    int rev[N], lim, len, invv[N];
    int qpow(int a, int b) {
        int res = 1ll;
        while (b) {
            if (b & 1) res = res * a % mod;
            a = a * a % mod;
            b >>= 1;
        }
        return res;
    }
    int inv(int a) { return qpow(a, mod - 2); }
    void NTT(int *f, int flag) {
        for (int i = 0; i < lim; ++i) if (i < rev[i]) swap(f[i], f[rev[i]]);
        for (int h = 2; h <= lim; h <<= 1) {
            int w = qpow(3, (mod - 1) / h);
            if (flag == -1) w = inv(w);
            for (int j = 0; j < lim; j += h) {
                int t1, t2, g = 1;
                for (int k = j; k < j + h / 2; k++, g = g * w % mod) {
                    t1 = f[k] % mod, t2 = f[k + h / 2] * g % mod;
                    f[k] = (t1 + t2) % mod, f[k + h / 2] = (t1 - t2 + mod) % mod;
                }
            }
        }
        if (flag == -1) {
            int invl = inv(lim);
            for (int i = 0; i < lim; ++i) f[i] = f[i] * invl % mod;
        }
    }
    void initL(int L) {
        lim = 1, len = 0;
        while (lim < L) lim <<= 1, len++;
        for (int i = 1; i < lim; ++i) rev[i] = (rev[i >> 1] >> 1 | ((i & 1) << (len - 1)));
    }
    void init(int L) {
        invv[0] = invv[1] = 1;
        for (int i = 2; i <= L; ++i) invv[i] = invv[mod % i] * (mod - mod / i) % mod;
    }
    int A[N], B[N], C[N], D[N], E[N], tmp[N];
    void Inv(int *f, int *g, int L) {
        if (L == 1) {
            g[0] = inv(f[0]);
            return;
        }
        Inv(f, g, (L + 1) >> 1);
        initL(L << 1);
        for (int i = 0; i < L; ++i) A[i] = f[i];
        for (int i = L; i < lim; ++i) A[i] = 0;
        NTT(g, 1), NTT(A, 1);
        for (int i = 0; i < lim; ++i) g[i] = g[i] * (2 - A[i] * g[i] % mod + mod) % mod;
        NTT(g, -1);
        for (int i = L; i < lim; ++i) g[i] = 0;
    }
    void Dao(int *f, int *g, int L) {
        for (int i = 1; i < L; ++i) g[i - 1] = i * f[i] % mod;
        g[L] = g[L - 1] = 0;
    }
    void Jifen(int *f, int *g, int L) {
        for (int i = 1; i < L; ++i) g[i] = f[i - 1] * invv[i] % mod;
        g[0] = 0;
    }
    void getln(int *f, int *g, int L) {
        memset(tmp, 0, sizeof(A)), memset(B, 0, sizeof(B));
        Dao(f, tmp, L); Inv(f, B, L);
        initL(L << 1);
        NTT(tmp, 1), NTT(B, 1);
        for (int i = 0; i < (L << 1); ++i) tmp[i] = tmp[i] * B[i] % mod;
        NTT(tmp, -1);
        Jifen(tmp, g, L);
        for (int i = 0; i < (L << 1); ++i) tmp[i] = B[i] = 0;
    }
    void exp(int *f, int *g, int L) {
        if (L == 1) { g[0] = 1; return; }
        exp(f, g, L >> 1);
        for (int i = 0; i < L; ++i) D[i] = g[i];
        getln(g, E, L); 
        for (int i = 0; i < L; ++i) E[i] = (mod - E[i] + f[i]) % mod;
        E[0] = (E[0] + 1) % mod;
        initL(L << 1); NTT(E, 1), NTT(D, 1);
        for (int i = 0; i < (L << 1); ++i) D[i] = D[i] * E[i] % mod;
        NTT(D, -1);
        for (int i = 0; i < L; ++i) g[i] = D[i];
        for (int i = 0; i < (L << 1); ++i) E[i] = D[i] = 0;
    }
    void fastpow(int *f, int *g, int k, int L) {
        memset(E, 0, sizeof(E));
        getln(f, E, L);
        for (int i = 0; i < L; ++i) E[i] = E[i] * k % mod;
        exp(E, g, L);
    }
}
using namespace Poly;

inline void solve() {
    read(n, m);
    for (int i = 1, x; i <= n; ++i) read(x), TT[x]++;
    int p = 1;
    while (p <= m) p <<= 1;
    init(p);
    for (int i = 1; i <= m; ++i) 
        if (TT[i])
            for (int j = i; j < p; j += i) 
                X[j] = (X[j] + TT[i] * (mod - invv[j / i])) % mod;
    exp(X, Y, p); memset(X, 0, sizeof(X)); Inv(Y, X, p);
    for (int i = 1; i <= m; ++i) printf("%lld\n", X[i]);
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}