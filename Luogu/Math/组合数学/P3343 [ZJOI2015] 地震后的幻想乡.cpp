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

int n, m;
int a[(1 << 10)], G[(1 << 10)];
double C[51][51], f[(1 << 10)][51], g[(1 << 10)][51];

inline void solve() {
    read(n, m);
    C[0][0] = 1;
    for (int i = 1; i <= m; ++i) {
        C[i][0] = 1;
        for (int j = 1; j <= i; ++j) C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
    }
    for (int i = 1; i <= m; ++i) {
        int u, v;
        read(u, v);
        ++G[(1 << (u - 1)) | 1 << (v - 1)];
    }
    for (int s = 1; s < (1 << n); ++s)
        for (int t = s; t; t = (t - 1) & s)
            a[s] += G[t]; // a表示集合s的点中边的数量
    for (int s = 1; s < (1 << n); ++s) {
        for (int i = 0; i <= a[s]; ++i) {
            for (int t = (s - 1) & s; t; t = (t - 1) & s)
                if (t & (s & -s)) //钦定k在s中
                    for (int j = 0; j <= min(i, a[t]); ++j) f[s][i] += g[t][j] * C[a[s ^ t]][i - j];
            g[s][i] = C[a[s]][i] - f[s][i];
        }
    }
    double ans = 0;
    for (int k = 0; k <= m; ++k) ans += f[(1 << n) - 1][k] / C[m][k];
    ans /= (m + 1.0);
    printf("%.6lf\n", ans);
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}
