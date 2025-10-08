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

const int N = 2335, mod = 2333;

int n, k, C[N + 10][N + 10], f[N + 10][N + 10];

int Lucas(int n, int m) {
    if (!m) return 1;
    if (n == m) return 1;
    if (n < m) return 0;
    return C[n % mod][m % mod] * Lucas(n / mod, m / mod) % mod;
}
int calc(int n, int k) {
    if (k < 0) return 0;
    if (!n || !k) return 1;
    if (n < mod && k < mod) return f[n][k];
    return (f[n % mod][mod - 1] * calc(n / mod, k / mod - 1) % mod + Lucas(n / mod, k / mod) * f[n % mod][k % mod] % mod) % mod;
}

inline void solve() {
    read(n, k);
    printf("%lld\n", calc(n, k));
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    C[0][0] = 1;
    for (int i = 1; i <= N; ++i) C[i][i] = C[i][0] = 1;
    for (int i = 1; i <= N; ++i)
        for (int j = 1; j < i; ++j) C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
    f[0][0] = 1;
    for (int i = 1; i <= N; ++i) f[i][0] = 1;
    for (int i = 0; i <= N; ++i)
        for (int j = 1; j <= N; ++j)
            f[i][j] = (C[i][j] + f[i][j - 1]) % mod;
    read(T);
    while (T--) solve();
    return 0;
}