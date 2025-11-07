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

int n, m, q;
int root[N];

mt19937 rnd(233);

namespace FHQ_tree {
    #define lson (t[rt].ls)
    #define rson (t[rt].rs)
    struct node {
        int l, r, ls, rs;
        int siz, key;
    } t[N * 20];
    int tot = 0;
    int newnode(int l, int r) {
        t[++tot].l = l, t[tot].r = r;
        t[tot].siz = r - l + 1, t[tot].key = rnd();
        return tot;
    }
    void pushup(int rt) {
        t[rt].siz = t[lson].siz + t[rson].siz + t[rt].r - t[rt].l + 1;
    }
    int merge(int x, int y) {
        if (!x || !y) return x + y;
        if (t[x].key < t[y].key) {
            t[x].rs = merge(t[x].rs, y);
            pushup(x);
            return x;
        }
        else {
            t[y].ls = merge(x, t[y].ls);
            pushup(y);
            return y;
        }
    }
    void split_new(int rt, int k) {
        if (t[rt].r - t[rt].l < k) return;
        int want = t[rt].l + k - 1;
        int nn = newnode(want + 1, t[rt].r);
        t[rt].r = want;
        rson = merge(nn, rson);
        pushup(rt);
    }
    void split(int rt, int siz, int &x, int &y) {
        if (!rt) return (void)(x = y = 0);
        if (t[lson].siz >= siz) {
            y = rt;
            split(lson, siz, x, lson);
        }
        else {
            split_new(rt, siz - t[lson].siz);
            x = rt;
            split(rson, siz - t[lson].siz - (t[rt].r - t[rt].l + 1), rson, y);
        }
        pushup(rt);
    }
}
using namespace FHQ_tree;

inline void solve() {
    read(n, m, q);
    for (int i = 1; i <= n; ++i) root[i] = newnode((i - 1) * m + 1, i * m - 1);
    for (int i = 1; i <= n; ++i) root[n + 1] = merge(root[n + 1], newnode(i * m, i * m));
    while (q--) {
        int a, b, x, y, z, x_, y_, z_;
        read(a, b);
        if (b != m) {
            split(root[a], b, x, y); split(x, b - 1, x, z);
            printf("%lld\n", t[z].l);
            split(root[n + 1], a, x_, y_); split(x_, a - 1, x_, z_);
            root[a] = merge(x, merge(y, z_)); root[n + 1] = merge(x_, merge(y_, z));
        }
        else {
            split(root[n + 1], a, x, y); split(x, a - 1, x, z);
            printf("%lld\n", t[z].l);
            root[n + 1] = merge(x, merge(y, z));
        }
    }
}

signed main() {
    // freopen("P3960_7.in","r",stdin);
    // freopen("my.out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}