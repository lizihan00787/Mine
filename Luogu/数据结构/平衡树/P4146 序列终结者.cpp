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

const int N = 2e5 + 10;

int n, q;

namespace FHQ_tree {
    mt19937 rnd(233);
    #define lson (t[rt].ls)
    #define rson (t[rt].rs)
    struct node {
        int ls, rs, siz, key;
        int val, maxx;
        int add;
        bool rev;
    } t[N];
    int tot = 0;
    int newnode(int val) {
        t[++tot].siz = 1;
        t[tot].val = val;
        t[tot].key = rnd();
        return tot;
    }
    void pushup(int rt) {
        t[rt].siz = t[lson].siz + t[rson].siz + 1;
        t[rt].maxx = max(t[lson].maxx, max(t[rt].val , t[rson].maxx));
    }
    void pushdown(int rt) {
        if (!t[rt].add && !t[rt].rev) return;
        if (t[rt].rev) t[lson].rev ^= 1, t[rson].rev ^= 1, swap(t[rt].ls, t[rt].rs);
        if (t[rt].add) t[lson].add += t[rt].add, t[rson].add += t[rt].add, t[lson].maxx += t[rt].add, t[rson].maxx += t[rt].add, t[lson].val += t[rt].add, t[rson].val += t[rt].add;
        t[rt].add = t[rt].rev = 0;
    }
    void split(int rt, int siz, int &x, int &y) {
        if (!rt) return (void)(x = y = 0);
        pushdown(rt);
        if (t[lson].siz >= siz) {
            y = rt;
            split(lson, siz, x, lson);
        }
        else {
            x = rt;
            split(rson, siz - t[lson].siz - 1, rson, y);
        }
        pushup(rt);
    }
    int merge(int x, int y) {
        if (!x || !y) return x + y;
        pushdown(x), pushdown(y);
        if (t[x].key < t[y].key) {
            t[y].ls = merge(x, t[y].ls);
            pushup(y);
            return y;
        }
        else {
            t[x].rs = merge(t[x].rs, y);
            pushup(x);
            return x;
        }
    }
}
using namespace FHQ_tree;

inline void solve() {
    read(n, q);
    t[0].val = t[0].add = t[0].maxx= -1e16;
    int root = 0;
    for (int i = 1; i <= n; ++i) root = merge(root, newnode(0));
    while (q--) {
        int op, l, r, v, x, y, z;
        read(op, l, r);
        if (op == 1) {
            read(v);
            split(root, r, x, z);
            split(x, l - 1, x, y);
            t[y].add += v; t[y].maxx += v, t[y].val += v;
            root = merge(x, merge(y, z));
        }
        else if (op == 2) {
            split(root, r, x, z);
            split(x, l - 1, x, y);
            t[y].rev ^= 1;
            root = merge(x, merge(y, z));
        }
        else {
            split(root, r, x, z);
            split(x, l - 1, x, y);
            printf("%lld\n", t[y].maxx);
            root = merge(x, merge(y, z));
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