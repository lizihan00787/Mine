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
inline void read(Ty &x, Args &...args) {
    read(x);
    read(args...);
}
int T = 1;

const int N = 4e6 + 20, mod = 998244353;
const double pi = acos(-1);

int n, l, limit, p, invv, invn;
int a[N], b[N], g[N];
int rev[N];
char s[N];

int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
int inv(int a) { return qpow(a, mod - 2); }

void NTT(int *f, int flag) {
    for (int i = 0; i < limit; ++i)
        if (i < rev[i]) swap(f[i], f[rev[i]]);
    for (int h = 2; h <= limit; h <<= 1) {
        int gn = qpow(flag ? 3 : invv, (mod - 1) / h);
        for (int j = 0; j < limit; j += h) {
            int t1, t2, g = 1;
            for (int k = j; k < j + h / 2; ++k, g = g * gn % mod) {
                t1 = f[k] % mod, t2 = g * f[h / 2 + k] % mod;
                f[k] = (t1 + t2) % mod, f[h / 2 + k] = (t1 - t2 + mod) % mod;
            }
        }
    }
}

void change(int x) {
    for (int i = 0; i < limit; ++i) b[i] = g[i];
    b[0] += x;
    NTT(a, 1), NTT(b, 1);
    for (int i = 0; i < limit; ++i) a[i] = a[i] * b[i] % mod, b[i] = 0;
    NTT(a, 0);
    for (int i = 0; i < limit; ++i) a[i] = a[i] * invn % mod;
    for (int i = 0; i < limit; ++i) a[i + 1] = (a[i + 1] + a[i] / 10) % mod, a[i] %= 10;
}

inline void solve() {
    scanf("%s", s);
    n = strlen(s);
    limit = 1;
    bool flag = 0;
    for (int i = 0; i < n; ++i) g[i] = s[n - i - 1] - '0';
    while (limit <= n * 5) limit <<= 1, l++;
    invn = inv(limit), invv = inv(3);
    for (int i = 0; i < limit; ++i) rev[i] = rev[i >> 1] >> 1 | (i & 1) << l - 1;
    a[0] = 1;
    for (int i = 0; i < limit; ++i) a[i] += g[i];
    change(2), change(3), change(4);
    for (int i = 0; i < limit; ++i) a[i + 1] = (a[i + 1] + a[i] / 10) % mod, a[i] %= 10;
    for (int i = limit - 1; i >= 0; --i) a[i - 1] += (a[i] % 24) * 10, a[i] /= 24;
    for (int i = limit - 1; i >= 0; --i)
        if (flag || a[i]) flag = 1, printf("%lld", a[i]);
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}