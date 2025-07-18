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
struct edge {
    int u, v, w;
} e[N << 1];
vector<PII> G[N];
int a[N];
int dep[N], fa[N], son[N], siz[N], tp[N], dfx[N], rk[N], tot;

namespace BT {
    void dfs1(int u, int f) {
        siz[u] = 1;
        dep[u] = dep[f] + 1;
        fa[u] = f;
        for (auto [v, w] : G[u]) {
            if (v == f) continue;
            a[v] = w;
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
}
using namespace BT;

namespace Segtree {
    #define lson (rt << 1)
    #define rson (rt << 1 | 1)
    int t[N << 2];
    void pushup(int rt) { t[rt] = max(t[lson], t[rson]); }
    void build(int rt, int l, int r) {
        if (l == r) return (void)(t[rt] = a[rk[l]]);
        int mid = (l + r) >> 1;
        build(lson, l, mid); build(rson, mid + 1, r);
        pushup(rt);
    }
    void update(int rt, int l, int r, int k, int x) {
        if (l == r) return (void)(t[rt] = x);
        int mid = (l + r) >> 1;
        if (k <= mid) update(lson, l, mid, k, x);
        else update(rson, mid + 1, r, k, x);
        pushup(rt);
    }
    int query(int rt, int l, int r, int L, int R) {
        if (L <= l && r <= R) return t[rt];
        int mid = (l + r) >> 1, res = 0;
        if (L <= mid) res = max(res, query(lson, l, mid, L, R));
        if (R > mid) res = max(res, query(rson, mid + 1, r, L, R));
        return res;
    }
}
using namespace Segtree;

int que(int x, int y) {
    int res = 0;
    while (tp[x] != tp[y]) {
        if (dep[tp[x]] < dep[tp[y]]) swap(x, y);
        res = max(res, query(1, 1, n, dfx[tp[x]], dfx[x]));
        x = fa[tp[x]];
    }
    if (dep[x] < dep[y]) swap(x, y);
    res = max(res, query(1, 1, n, dfx[y] + 1, dfx[x]));
    return res;
}


inline void solve() {
    read(n);
    for (int i = 1; i < n; ++i) {
        read(e[i].u, e[i].v, e[i].w);
        int u = e[i].u, v = e[i].v, w = e[i].w;
        G[u].push_back(mk(v, w));
        G[v].push_back(mk(u, w));
        a[v] = w;
    }
    dfs1(1, 0);
    dfs2(1, 1);
    build(1, 1, n);
    char op[10];
    while (scanf("%s", op), op[0] != 'D') {
        int x, y;
        if (op[0] == 'Q') {
            read(x, y);
            printf("%d\n", que(x, y));
        }
        else {
            read(x, y);
            int u = e[x].u, v = e[x].v;
            if (fa[v] == u) swap(u, v);
            update(1, 1, n , dfx[u], y);;
        }
    }
    memset(G, 0, sizeof(G));
    memset(a, 0, sizeof(a));
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    read(T);
    while (T--) solve();
    return 0;
}