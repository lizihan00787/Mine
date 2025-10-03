#include <bits/stdc++.h>
#define int long long
#define re register
#define PII pair<int, int>
#define fi first
#define se second
#define MOD 998244353
#define io() ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL)
#define mk(a, b) make_pair(a, b)
#define pqd priority_queue<int, vector<int>, less<int>>
#define pqx priority_queue<int, vector<int>, greater<int>>
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
        res = res * 10 + ch - '0';
        ch = getchar();
    }
    x = res * f;
}
int T = 1;
const int N = 5e5 + 10;
const int mod = 998244353;
int n, limit;
int F[N], G[N], c[N];
int rev[N];
const double pi = acos(-1);
int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = a * res % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
int inv(int a) {
    return qpow(a, mod - 2);
}
void NTT(int *f, int flag) {
    for (int i = 0; i < limit; ++i)
        if (i < rev[i]) swap(f[i], f[rev[i]]);
    for (int h = 2; h <= limit; h <<= 1) {
        int gn = qpow(114514, (mod - 1) / h);
        if (flag == -1) gn = inv(gn);
        for (int j = 0; j < limit; j += h) {
            int t1, t2, g = 1;
            for (int k = j; k < j + h / 2; ++k, g = g * gn % mod) {
                t1 = f[k] % mod, t2 = g * f[h / 2 + k] % mod;
                f[k] = (t1 + t2) % mod, f[h / 2 + k] = (t1 - t2 + mod) % mod;
            }
        }
    }
    if (flag == -1) {
        int invv = inv(limit);
        for (int i = 0; i < limit; ++i) f[i] = f[i] * invv % mod;
    }
}
void work(int *f, int *g, int n) {
    if (n == 1) {
        g[0] = inv(f[0]);
        return;
    }
    work(f, g, (n + 1) / 2);
    limit = 1;
    int k = 0;
    while (limit < (n << 1)) limit <<= 1, k++;
    for (int i = 1; i < limit; ++i) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
    for (int i = 0; i < n; ++i) c[i] = f[i];
    for (int i = n; i < limit; ++i) c[i] = 0;
    NTT(g, 1), NTT(c, 1);
    for (int i = 0; i < limit; ++i) g[i] = g[i] * (2 - c[i] * g[i] % mod + mod) % mod;
    NTT(g, -1);
    for (int i = n; i < limit; ++i) g[i] = 0;
}
signed main() {
    auto solve = [&]() {
        read(n);
        for (int i = 0; i < n; ++i) read(F[i]);
        limit = 1;
        work(F, G, n);
        for (int i = 0; i < n; ++i) cout << G[i] << ' ';
        cout << endl;
    };
    // io();
    // read(T);
    while (T--) solve();
    return 0;
}