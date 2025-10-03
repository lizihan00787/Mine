#include <bits/stdc++.h>
#define endl '\n'
#define int __int128
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
char ch;
inline int read(char &ch){
    int x = 0;
    ch = getchar();
    while(!isdigit(ch)) ch = getchar();
    while(isdigit(ch)) x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
    return x;
}
template <typename Ty, typename... Args>
inline void read(Ty &x, Args &...args) { read(x); read(args...); }
template <typename P>
inline void write(P x) {
    if (x < 0) putchar('-'), x = -x;
    if (x >= 10) write(x / 10);
    putchar(x % 10 + '0');
}
int T = 1;

const int N = 1e6 + 20;
const int P = 5e4 + 20;
const int mod = 4179340454199820289ll;

int n, m, k;
int a[N], b[N], c[N], d[N], e[N], rev[N];
int lim, len;

bool isnp[N];
int prime[N], tot;

void init() {
    for (int i = 2; i <= P; ++i) {
        if (!isnp[i]) prime[++tot] = i;
        for (int j = 1; j <= tot && i * prime[j] <= P; ++j) {
            isnp[i * prime[j]] = 1;
            if (i % prime[j] == 0) break;
        }
    }
}

namespace Math {
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
    void mul(int n, int m, int *f, int *g) {
        lim = 1, len = 0;
        while (lim <= (n + m)) lim <<= 1, len++;
        for (int i = 0; i <= lim; ++i) rev[i] = (rev[i >> 1] >> 1 | ((i & 1) << (len - 1)));
        NTT(f, 1); NTT(g, 1);
        for (int i = 0; i <= lim; ++i) f[i] = f[i] * g[i] % mod;
        NTT(f, -1);
    }
}
using namespace Math;

inline void solve() {
    init();
    while(read(n, m, k), n || m || k) {
        memset(a, 0, sizeof(a)), memset(b, 0, sizeof(b)), memset(c, 0, sizeof(c)), memset(d, 0, sizeof(d));
        for (int i = 0; i <= m; ++i) a[i] = b[i] = c[i] = d[i] = isnp[i];
        for (int i = 1; i <= k; ++i) {
            int x = read(ch);
            if (ch == 'S') a[x] = 0;
            if (ch == 'H') b[x] = 0;
            if (ch == 'C') c[x] = 0;
            if (ch == 'D') d[x] = 0;
        }
        mul(m, m, a, b), mul(m, m, c, d), mul((m << 1), (m << 1), a, c);
        for (int i = n; i <= m; ++i) write(a[i]), puts("");
        puts("");
    }
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}