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

const int N = 3e5 + 10;

int n, q;
int a[N], b[N], c[N];
int x[N], y[N], z[N];

inline void solve() {
    read(n, q);
    for (int i = 1; i <= n; ++i) read(b[i]), a[i] = b[i];
    for (int i = 1; i <= q; ++i) read(x[i], y[i], z[i]);
    for (int i = q; i >= 1; --i) {
        a[x[i]] = max(a[x[i]], a[z[i]]);
        a[y[i]] = max(a[y[i]], a[z[i]]);
        if (y[i] != z[i] && x[i] != z[i]) a[z[i]] = 0;
    }
    memcpy(c, a, sizeof(a));
    for (int i = 1; i <= q; ++i) a[z[i]] = min(a[x[i]], a[y[i]]);
    bool fg = 1;
    for (int i = 1; i <= n; ++i) if (a[i] != b[i]) { fg = 0; break; }
    if (!fg) printf("-1");
    else for (int i = 1; i <= n; ++i) printf("%d ", c[i]);
    puts("");
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    read(T);
    while (T--) solve();
    return 0;
}