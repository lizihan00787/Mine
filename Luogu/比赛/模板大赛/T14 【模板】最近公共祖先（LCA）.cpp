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

const int N = 5e5 + 10;

int n, m, s;
vector<int> G[N];

int dfx[N], siz[N], son[N], tp[N], dep[N], fa[N], tot = 0;
void dfs1(int u, int f) {
    siz[u] = 1; dep[u] = dep[f] + 1; fa[u] = f;
    for (auto v : G[u]) {
        if (v == f) continue;
        dfs1(v, u);
        siz[u] += siz[v];
        if (siz[v] > siz[son[u]]) son[u] = v;
    }
}
void dfs2(int u, int t) {
    tp[u] = t;
    if (son[u]) dfs2(son[u], t);
    for (auto v : G[u]) {
        if (v == fa[u] || v == son[u]) continue;
        dfs2(v, v);
    }
}
int lca(int x, int y) {
    while (tp[x] != tp[y]) {
        if (dep[tp[x]] < dep[tp[y]]) swap(x, y);
        x = fa[tp[x]];
    }
    if (dep[x] > dep[y]) swap(x, y);
    return x;
}

inline void solve() {
    read(n, m, s);
    for (int i = 1; i < n; ++i) {
        int u, v;
        read(u, v);
        G[u].emplace_back(v);
        G[v].emplace_back(u);
    }
    dfs1(s, 0);
    dfs2(s, s);
    for (int i = 1; i <= m; ++i) {
        int x, y;
        read(x, y);
        cout << lca(x, y) << endl;
    }
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}