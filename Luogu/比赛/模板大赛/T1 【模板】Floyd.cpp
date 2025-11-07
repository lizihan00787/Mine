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

const int N = 120;

int n, m;
int g[N][N];
int f[N][N];

inline void solve() {
    read(n, m);
    memset(f, 0x3f, sizeof(f));
    for (int i = 1; i <= n; ++i) f[i][i] = 0;
    for (int i = 1; i <= m; ++i) {
        int u, v, w;
        read(u, v, w);
        f[u][v] = min(f[u][v], w);
        f[v][u] = min(f[v][u], w);
    }
    for (int k = 1; k <= n; ++k)
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            printf("%d ", f[i][j]);
        }
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