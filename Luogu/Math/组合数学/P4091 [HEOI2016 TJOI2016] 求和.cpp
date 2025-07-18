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

const int N = 5e5 + 20, mod = 998244353;

int n, cnt;
int inv[N], pri[N], isnp[N], pw[N];

int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
void make() {
    inv[1] = 1;
    for (int i = 2; i <= n + 2; ++i) inv[i] = inv[mod % i] * (mod - mod / i) % mod;
    for (int i = 2; i <= n; ++i) {
        if (!isnp[i]) pri[++cnt] = i, pw[i] = qpow(i, n + 1);
        for (int j = 1; j <= cnt && i * pri[j] <= n; ++j) {
            isnp[i * pri[j]] = 1;
            pw[i * pri[j]] = pw[i] * pw[pri[j]] % mod;
            if (i % pri[j] == 0) break;
        }
    }
}

inline void solve() {
    read(n);
    if (n == 0) return (void)(puts("1"));
    make();
    int t1 = -1 * qpow(-2, n + 1) * inv[3] % mod, t2 = -2 * inv[3] % mod;
    int f0 = -inv[3], fn = t1, ans = (fn - f0) % mod, bin = n + 1;
    f0 = t2 * f0 % mod, fn = (t1 * (n + 1) + t2 * fn) % mod;
    ans = (ans - (n + 1) * (fn - f0) % mod + mod) % mod;
    for (int i = 2; i <= n; ++i) {
        bin = bin * (n + 2 - i) % mod * inv[i] % mod;
        f0 = t2 * f0 % mod;
        fn = (t1 * bin % mod + t2 * fn % mod) % mod;
        ans = (ans + ((i & 1) ? -1 : 1) * (inv[i - 1] * (pw[i] - 1) % mod * (fn - f0) % mod) % mod + mod) % mod;
    }
    printf("%lld\n", (ans + mod) % mod);
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}