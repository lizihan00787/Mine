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

const int N = 1e5 + 20;

int n, m;
vector<PII> G[N];
int dep[N], dis[N], fa[N], son[N], siz[N], tp[N], dfx[N], rk[N], tot;

namespace BT {
    void dfs1(int u, int f) {
        siz[u] = 1;
        dep[u] = dep[f] + 1;
        fa[u] = f;
        for (auto [v, w] : G[u]) {
            if (v == f) continue;
            dis[v] = dis[u] + w;
            dfs1(v, u);
            siz[u] += siz[v];
            if (siz[v] > siz[son[u]]) son[u] = v;
        }
    }
    void dfs2(int u, int t) {
        tp[u] = t;
        dfx[u] = ++tot; rk[tot] = u;
        if (son[u]) dfs2(son[u], t);
        for(auto [v, w] : G[u]) {
            if (v == fa[u] || v == son[u]) continue;
            dfs2(v, v);
        }
    }
    int lca(int u, int v) {
        while (tp[u] != tp[v]) {
            if (dep[tp[u]] < dep[tp[v]]) swap(u, v);
            u = fa[tp[u]];
        }
        return dep[u] < dep[v] ? u : v;
    }
}
using namespace BT;

inline void solve() {
    read(n);
    for (int i = 1; i < n; ++i) {
        int u, v, w;
        read(u, v, w);
        G[u].push_back(mk(v, w));
        G[v].push_back(mk(u, w));
    }
    dfs1(1, 0);
    dfs2(1, 1);
    string op;
    while (1) {
        cin >> op;
        int x, y, k;
        if (op == "DONE") break;
        else if (op == "DIST") {
            read(x, y);
            printf("%d\n", dis[x] + dis[y] - 2 * dis[lca(x, y)]);
        }
        else {
            read(x, y, k);
            int lc = lca(x, y);
            if (k > dep[x] - dep[lc] + 1) {
                k = dep[x] - dep[lc] + 1 + dep[y] - dep[lc] + 1 - k;
                swap(x, y);
            }
            while (k > dep[x] - dep[tp[x]] + 1) {
                k -= (dep[x] - dep[tp[x]] + 1);
                x = fa[tp[x]];
            }
            printf("%d\n", rk[dfx[x] - k + 1]);
        }
    }
    for (int i = 1; i <= n; ++i) G[i].clear();
    tot = 0;
    for (int i = 1; i <= n; ++i) fa[i] = dfx[i] = son[i] = siz[i] = dep[i] = dis[i] = tp[i] = rk[i] = 0;
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    read(T);
    while (T--) solve();
    return 0;
}