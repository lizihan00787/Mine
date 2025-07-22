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
inline void read(Ty &x, Args &...args) {
    read(x);
    read(args...);
}
int T = 1;

const int N = 2e6 + 20;

int n, m, cnt = 0;
int c[N], dfx[N], siz[N], fa[N], dep[N], rt[N];
vector<int> G[N];

namespace Segtree {
    #define lson (t[rt].ls)
    #define rson (t[rt].rs)
    struct node {
        int ls, rs, sum;
    } t[N << 5];
    int tot = 0;
    void pushup(int rt) { t[rt].sum = t[lson].sum + t[rson].sum; }
    void update(int &rt, int l, int r, int k, int x) {
        if (!rt) rt = ++tot;
        if (l == r) return (void)(t[rt].sum += x);
        int mid = (l + r) >> 1;
        if (k <= mid) update(lson, l, mid, k, x);
        else update(rson, mid + 1, r, k, x);
        pushup(rt);
    }
    int query(int rt, int l, int r, int L, int R) {
        if (L <= l && r <= R) return t[rt].sum;
        int mid = (l + r) >> 1, res = 0;
        if (L <= mid) res += query(lson, l, mid, L, R);
        if (R > mid) res += query(rson, mid + 1, r, L, R);
        return res;
    }
    int merge(int p, int q, int l, int r) {
        if (!q || !p) return p + q;
        if (l == r) return t[p].sum += t[q].sum, p;
        int mid = (l + r) >> 1;
        t[p].ls = merge(t[p].ls, t[q].ls, l, mid);
        t[p].rs = merge(t[p].rs, t[q].rs, mid + 1, r);
        pushup(p);
        return p;
    }
}
using namespace Segtree;

void dfs(int u) {
    siz[u] = 1;
    dfx[u] = ++cnt;
    for (auto v : G[u]) {
        dep[v] = dep[u] + 1;
        dfs(v);
        siz[u] += siz[v];
    }
}

inline void solve() {
    read(n);
    for (int i = 2; i <= n; ++i) read(fa[i]), G[fa[i]].push_back(i);
    for (int i = 1; i <= n; ++i) read(c[i]);
    dfs(1);
    read(m);
    for (int i = 1; i <= n; ++i) update(rt[dep[i]], 1, n, dfx[i], c[i]);
    while (m--) {
        int op;
        read(op);
        if (op == 1) {
            int x, y;
            read(x, y);
            rt[y] = merge(rt[y], rt[x], 1, n);
            rt[x] = 0;
        } else if (op == 2) {
            int k, x;
            read(k, x);
            update(rt[dep[k]], 1, n, dfx[k], x);
        } else {
            int k;
            read(k);
            printf("%d\n", query(rt[dep[k]], 1, n, dfx[k], dfx[k] + siz[k] - 1));
        }
    }
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}