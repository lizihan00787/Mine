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

const int N = 2e5 + 10;

int n, m, blk, tmp, a[N], b[N], col[N], used[N], ans[N];
vector<int> G[N];
int fa[N], siz[N], son[N], dep[N], tp[N], st[N], ed[N], e[N], cnt = 0;

struct node {
    int l, r, lca, id, lb, rb;
} q[N];

void dfs1(int u, int f) {
    siz[u] = 1; dep[u] = dep[f] + 1; fa[u] = f;
    e[++cnt] = u; st[u] = cnt;
    for (auto v : G[u]) {
        if (v == f) continue;
        dfs1(v, u);
        siz[u] += siz[v];
        if (siz[v] > siz[son[u]]) son[u] = v;
    }
    e[++cnt] = u; ed[u] = cnt;
}
void dfs2(int u, int t) {
    tp[u] = t;
    if (son[u]) dfs2(son[u], t);
    for (auto v : G[u]) {
        if (v == fa[u] || v == son[u]) continue;
        dfs2(v, v);
    }
}
int lca(int u, int v) {
    while (tp[u]!= tp[v]) {
        if (dep[tp[u]] < dep[tp[v]]) swap(u, v);
        u = fa[tp[u]];
    }
    if (dep[u] > dep[v]) swap(u, v);
    return u;
}
void add(int x) { tmp += (++col[a[x]] == 1); }
void del(int x) { tmp -= (--col[a[x]] == 0); }
void calc(int x) { (!used[x]) ? add(x) : del(x); used[x] ^= 1; }
bool cmp(node x, node y) { return (x.lb == y.lb) ? (x.lb % 2 == 1? x.r < y.r : x.r > y.r) : x.l < y.l; }


inline void solve() {
    read(n, m);
    blk = n * 2 / sqrt(m * 2 / 3);
    for (int i = 1; i <= n; ++i) read(a[i]), b[i] = a[i];
    sort(b + 1, b + n + 1);
    for (int i = 1; i <= n; ++i) a[i] = lower_bound(b + 1, b + n + 1, a[i]) - b;
    for (int i = 1; i < n; ++i) {
        int u, v;
        read(u, v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs1(1, 0);
    dfs2(1, 1);
    for (int i = 1; i <= m; ++i) {
        int x, y;
        read(x, y);
        if (st[x] > st[y]) swap(x, y);
        q[i].id = i;
        q[i].lca = lca(x, y);
        if (q[i].lca == x) q[i].l = st[x], q[i].r = st[y], q[i].lb = st[x] / blk, q[i].rb = st[y] / blk, q[i].lca = 0;
        else q[i].l = ed[x], q[i].r = st[y], q[i].lb = ed[x] / blk, q[i].rb = st[y] / blk;
    }
    sort(q + 1, q + m + 1, cmp);
    int l = 1, r = 0;
    for (int i = 1; i <= m; ++i) {
        while (l > q[i].l) calc(e[--l]);
        while (r < q[i].r) calc(e[++r]);
        while (l < q[i].l) calc(e[l++]);
        while (r > q[i].r) calc(e[r--]);
        if (q[i].lca) calc(q[i].lca);
        ans[q[i].id] = tmp;
        if (q[i].lca) calc(q[i].lca);
    }
    for (int i = 1; i <= m; i++) printf("%d\n", ans[i]);
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}