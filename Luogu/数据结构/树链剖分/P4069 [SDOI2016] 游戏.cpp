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

const int N = 1e5 + 5, inf = 123456789123456789;

int n, m;
vector<PII> G[N];
int siz[N], fa[N], tp[N], tot = 0, dfx[N], rk[N], dep[N], dis[N], son[N];

namespace LCT {
    #define lson (rt << 1)
    #define rson (rt << 1 | 1)
    #define mid ((l + r) >> 1)
    struct Line {
        int k, b;
    } line[N << 1];
    int cnt = 0;
    int calc(int id, int pos) { return line[id].k * dis[rk[pos]] + line[id].b; }
    bool Cmp(int id1, int id2, int pos) { return calc(id1, pos) < calc(id2, pos); }

    int t[N << 2], minn[N << 2];
    void build() { for (int i = 1; i <= n * 4; ++i) minn[i] = inf; }
    void pushup(int rt) { minn[rt] = min(minn[rt], min(minn[lson], minn[rson])); }
    void add(int rt, int l, int r, int id) {
        minn[rt] = min(minn[rt], min(calc(id, l), calc(id, r)));
        if (l == r) { if (Cmp(id, t[rt], l)) t[rt] = id; return;}
        if (Cmp(id, t[rt], mid)) swap(t[rt], id);
        if (Cmp(id, t[rt], l)) add(lson, l, mid, id);
        if (Cmp(id, t[rt], r)) add(rson, mid + 1, r ,id);
        pushup(rt);
    }
    void update(int rt, int l, int r, int L, int R, int id) {
        if (L <= l && r <= R) return (void)(add(rt, l, r, id));
        if (L <= mid) update(lson, l, mid, L, R, id);
        if (R > mid) update(rson, mid + 1, r, L, R, id);
        pushup(rt);
    }
    int query(int rt, int l, int r, int L, int R) {
        if (L <= l && r <= R) return minn[rt];
        int res = min(calc(t[rt], max(l, L)), calc(t[rt], min(r, R)));
        if (L <= mid) res = min(res, query(lson, l, mid, L, R));
        if (R > mid) res = min(res, query(rson, mid + 1, r, L, R));
        return res;
    }
}
using namespace LCT;

namespace KT {
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
        tp[u] = t, dfx[u] = ++tot, rk[tot] = u;
        if (son[u]) dfs2(son[u], t);
        for (auto [v, w] : G[u]) {
            if (v == fa[u] || v == son[u]) continue;
            dfs2(v, v);
        }
    }
    inline int lca(int u, int v) {
        while (tp[u] != tp[v]) {
            if (dep[tp[u]] < dep[tp[v]]) swap(u, v);
            u = fa[tp[u]];
        }
        if (dep[u] > dep[v]) swap(u, v);
        return u;
    }
    inline void upd(int u, int v) {
        while (tp[u] != tp[v]) update(1, 1, n, dfx[tp[u]], dfx[u], cnt), u = fa[tp[u]];
        update(1, 1, n, dfx[v], dfx[u], cnt);
    }
    inline int que(int u, int v) {
        int ans = inf;
        while (tp[u] != tp[v]) {
            if (dep[tp[u]] < dep[tp[v]]) swap(u, v);
            ans = min(ans, query(1, 1, n, dfx[tp[u]], dfx[u]));
            u = fa[tp[u]];
        }
        if (dep[u] > dep[v]) swap(u, v);
        ans = min(ans, query(1, 1, n, dfx[u], dfx[v]));
        return ans;
    }
}
using namespace KT;

inline void solve() {
    read(n, m);
    for (int i = 1; i < n; ++i) {
        int u, v, w;
        read(u, v, w);
        G[u].emplace_back(mk(v, w));
        G[v].emplace_back(mk(u, w));
    }
    dfs1(1, 0);
    dfs2(1, 1);
    build();
    line[0] = Line{0, inf};
    while (m--) {
        int op;
        int a, b, s, t;
        read(op, s, t);
        if (op == 1) {
            read(a, b);
            int lc = lca(s, t);
            line[++cnt] = Line{-a, a * dis[s] + b};
            upd(s, lc);
            line[++cnt] = Line{a, a * (dis[s] - dis[lc] * 2) + b};
            upd(t, lc);
        }
        else printf("%lld\n", que(s, t));
    }
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}