#include <bits/stdc++.h>
#define endl '\n'
#define ll long long
#define PII pair<int, int>
#define mk(a, b) make_pair(a, b)
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define per(i, a, b) for (int i = (a); i >= (b); --i)
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
inline void read(Ty &x, Args &...args) {read(x); read(args...);}
int T = 1;

const int N = 3e3+20, M=320, inf=0x3f3f3f3f;

int n, m;
int X[N], dp[N][M], w[N][N], d[N][M];

void init() {
    rep (l, 1, n) {
        w[l][l] = 0;
        rep (r, l+1, n) w[l][r] = w[l][r-1] + X[r] - X[(l + r) >> 1];
    }
}

inline void solve() {
    read(n, m);
    rep (i, 1, n) read(X[i]);
    init();
    sort(X + 1, X + n + 1);
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0;
    rep (j, 1, m) {
        d[n + 1][j] = n;
        per (i, n, 1) {
            int minn=inf,mink;
            rep (k, d[i][j - 1], d[i + 1][j]) {
                if (dp[k][j - 1] + w[k + 1][i] < minn) {
                    minn = dp[k][j - 1] + w[k + 1][i];
                    mink = k;
                }
            }
            dp[i][j] = minn;
            d[i][j] = mink;
        }
    }
    cout << dp[n][m] << endl;
}

signed main() {
    // freopen("    .in","r",stdin);
    // freopen("    .out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}