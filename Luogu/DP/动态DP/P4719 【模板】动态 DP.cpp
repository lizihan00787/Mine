#include <bits/stdc++.h>
#define endl '\n'
#define ll long long
#define ull unsigned long long
#define PII pair<int, int>
#define mk(a, b) make_pair(a, b)
using namespace std;
template <typename P>
inline void read(P &x) {
    P res = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        res = (res << 3) + (res << 1) + (ch ^ 48);
        ch = getchar();
    }
    x = res * f;
}
template <typename Ty, typename... Args>
inline void read(Ty &x, Args &...args) {
    read(x);
    read(args...);
}
int T = 1;

const int N = 1e5 + 20;

int n, m;
int a[N];
vector<int> G[N];
int fa[N], siz[N], son[N], dfx[N], tot = 0, rk[N], tp[N], dep[N], en[N];
ll f[N][2];

struct martix {
    ll g[2][2];
    martix() {
        memset(g, -0x3f, sizeof(g));
    }
    martix operator * (const martix &b) const {
        martix c;
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 2; ++j)
                for (int k = 0; k < 2; ++k)
                    c.g[i][j] = max(c.g[i][j], g[i][k] + b.g[k][j]);
        return c;
    }
} val[N];

namespace Segtree {
    #define lson (rt << 1)
    #define rson (rt << 1 | 1)
    martix t[N << 2];
    void pushup(int rt) { t[rt] = t[lson] * t[rson]; }
    void build(int rt, int l, int r) {
        if (l == r)
            return (void)(t[rt] = val[rk[l]]);
        int mid = (l + r) >> 1;
        build(lson, l, mid); build(rson, mid + 1, r);
        pushup(rt);
    }
    void update(int rt, int l, int r, int k) {
        if (l == r)
            return (void)(t[rt] = val[rk[k]]);
        int mid = (l + r) >> 1;
        if (k <= mid) update(lson, l, mid, k);
        else update(rson, mid + 1, r, k);
        pushup(rt);
    }
    martix query(int rt, int l, int r, int L, int R) {
        if (L <= l && r <= R)
            return t[rt];
        int mid = (l + r) >> 1;
        if (L > mid) return query(rson, mid + 1, r, L, R);
        else if (R <= mid) return query(lson, l, mid, L, R);
        else return query(lson, l, mid, L, R) * query(rson, mid + 1, r, L, R);
    }
}
using namespace Segtree;
namespace TD {
    void dfs1(int u) {
        siz[u] = 1;
        for (auto v : G[u]) {
            if (v == fa[u]) continue;
            fa[v] = u; dep[v] = dep[u] + 1;
            dfs1(v);
            siz[u] += siz[v];
            if (siz[v] > siz[son[u]]) son[u] = v;
        }
    }
    void dfs2(int u, int t) {
        tot++;
        tp[u] = t, dfx[u] = tot, rk[tot] = u, en[t] = max(en[t], tot);
        f[u][0] = 0, f[u][1] = a[u];
        val[u].g[0][0] = val[u].g[0][1] = 0, val[u].g[1][0] = a[u];
        if (son[u]) {
            dfs2(son[u], t);
            f[u][0] += max(f[son[u]][0], f[son[u]][1]);
            f[u][1] += f[son[u]][0];
        }
        for (auto v : G[u]) {
            if (v == fa[u] || v == son[u]) continue;
            dfs2(v, v);
            f[u][0] += max(f[v][0], f[v][1]);
            f[u][1] += f[v][0];
            val[u].g[0][0] += max(f[v][0], f[v][1]);
            val[u].g[0][1] = val[u].g[0][0];
            val[u].g[1][0] += f[v][0];
        }
    }
}
using namespace TD;

void updpath(int u, int w) {
    val[u].g[1][0] += w - a[u];
    a[u] = w;
    martix bef, aft;
    while (u != 0) {
        bef = query(1, 1, n, dfx[tp[u]], en[tp[u]]);
        update(1, 1, n, dfx[u]);
        aft = query(1, 1, n, dfx[tp[u]], en[tp[u]]);
        u = fa[tp[u]];
        val[u].g[0][0] += max(aft.g[0][0], aft.g[1][0]) - max(bef.g[0][0], bef.g[1][0]);
        val[u].g[0][1] = val[u].g[0][0];
        val[u].g[1][0] += aft.g[0][0]-bef.g[0][0];
    }
}

inline void solve() {
    read(n, m);
    for (int i = 1; i <= n; ++i) read(a[i]);
    for (int i = 1; i < n; ++i) {
        int u, v;
        read(u, v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs1(1), dfs2(1, 1);
    build(1, 1, n);
    while (m--) {
        int u, w;
        read(u, w);
        updpath(u, w);
        martix res = query(1, 1, n, dfx[1], en[1]);
        cout << max(res.g[0][0], res.g[1][0]) << endl;
    }
}

signed main() {
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    // read(T);
    while (T--) solve();
    return 0;
}