#include <bits/stdc++.h>
#define endl '\n'
#define int long long
#define PII pair<int, int>
#define mk(a, b) make_pair(a, b)
using namespace std;

const int N = 1e5 + 20, mod = 1004535809;

template <typename P>
inline void read(P &x) {
    P res = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        res = ((res << 3) + (res << 1) + (ch ^ 48)) % mod;
        ch = getchar();
    }
    x = res * f;
}
template <typename Ty, typename... Args>
inline void read(Ty &x, Args &...args) { read(x); read(args...); }
int T = 1;

int n, k, t;
int a[N << 4], b[N << 4], rev[N << 4], lim, len;

int qpow(int a, int b) {
    int res = 1ll;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
int invv(int a) { return qpow(a, mod - 2); }

void NTT(int *f, int flag) {
    for (int i = 0; i < lim; ++i) if (i < rev[i]) swap(f[i], f[rev[i]]);
    for (int h = 2; h <= lim; h <<= 1) {
        int w = qpow(3, (mod - 1) / h);
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
    read(n, k, t);
    for (int i = 0; i < n; ++i) read(a[i]);
    b[0] = 1;
    if (t == 0) for (int i = 1; i <= n; ++i) b[i] = b[i - 1] * (k + i - 1 + mod) % mod * qpow(i ,mod - 2) % mod;
    else for (int i = 1; i <= n; ++i) b[i] = (mod - b[i - 1] * (k - i + 1 + mod) % mod * qpow(i, mod - 2)) % mod;
    lim = 1, len = 0;
    while (lim <= (n << 1)) lim <<= 1, len++;
    for (int i = 0; i < lim; ++i) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (len - 1));
    NTT(a, 1), NTT(b, 1);
    for (int i = 0; i < lim; ++i) a[i] = a[i] * b[i] % mod;
    NTT(a, -1);
    for (int i = 0; i < n; ++i) printf("%lld ", a[i]);
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}