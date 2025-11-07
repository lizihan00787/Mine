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

const int N = 3e5 + 10;

int n, m, tot;
int d[N];
ll f[N], g[N];
vector<int> G[N];

void dfs(int u, int fa, int mid) {
    f[u] = -0x3f3f3f3f, g[u] = 0x3f3f3f3f;
    for (auto v : G[u]) {
        if (v == fa) continue;
        dfs(v, u, mid);
        f[u] = max(f[v] + 1, f[u]);
        g[u] = min(g[v] + 1, g[u]);
    }
    if (f[u] + g[u] <= mid) f[u] = -0x3f3f3f3f;
    if (g[u] > mid && d[u]) f[u] = max(f[u], 0ll);
    if (f[u] == mid) f[u] = -0x3f3f3f3f, g[u] = 0, ++tot;
}

int check(int x) {
    tot = 0;
    dfs(1, 0, x);
    if (f[1] >= 0) ++tot;
    return tot <= m;
}

inline void solve() {
    read(n, m);
    for (int i = 1; i <= n; ++i) read(d[i]);
    for (int i = 1; i < n; ++i) {
        int u, v;
        read(u, v);
        G[u].emplace_back(v);
        G[v].emplace_back(u);
    }
    int l = 0, r = n, ans = 0;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (check(mid)) r = mid - 1, ans = mid;
        else l = mid + 1;
    }
    printf("%d\n", ans);
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}