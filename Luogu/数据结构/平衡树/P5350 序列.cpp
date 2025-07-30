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

const int N = 3e5 + 20, mod = 1e9 + 7, M = 4e6 + 20;

int n, q;
int v[N];
mt19937 rnd(std::chrono::system_clock::now().time_since_epoch().count());
int rd(int l, int r) { return std::uniform_int_distribution<int>(l, r)(rnd); }

template <typename PPP>
void ad(int &a, PPP x) { a = (a + x) % mod; }
template <typename PPP>
void se(int &a, PPP x) { a = (x) % mod; }

namespace FHQ_treap {
    #define lson (t[rt].ls)
    #define rson (t[rt].rs)
    struct node {
        int ls, rs, sum, siz, val;
        int add, cov;
        bool rev;
    } t[M];
    int tot = 0, root = 0;
    inline void clone(int &rt) { t[++tot] = t[rt]; rt = tot; }
    inline int newnode(int val) { return t[++tot] = (node){0, 0, val, 1, val, 0, -1, 0}, tot; }
    inline void pushup(int rt) { se(t[rt].sum, (1ll * t[rt].val + t[lson].sum + t[rson].sum)); t[rt].siz = t[lson].siz + t[rson].siz + 1; }
    inline void add(int rt, int x) { if (rt) ad(t[rt].val, x), ad(t[rt].sum, 1ll * x * t[rt].siz), ad(t[rt].add, x); }
    inline void cov(int rt, int x) { if (rt) se(t[rt].val, x), se(t[rt].sum, 1ll * x * t[rt].siz), se(t[rt].cov, x), t[rt].add = 0; }
    inline void rev(int rt) { if (rt) t[rt].rev ^= 1, swap(lson, rson); }
    inline void pushdown(int rt) {
        if (!t[rt].rev && t[rt].cov == -1 && !t[rt].add) return;
        if (lson) clone(lson); if (rson) clone(rson);
        if (t[rt].rev) rev(lson), rev(rson), t[rt].rev = 0;
        if (t[rt].cov != -1) cov(lson, t[rt].cov), cov(rson, t[rt].cov), t[rt].cov = -1;
        if (t[rt].add) add(lson, t[rt].add), add(rson, t[rt].add), t[rt].add = 0;
    }
    void build(int &rt, int l, int r) {
        if (l > r) return (void)(rt = 0);
        int mid = (l + r) >> 1;
        rt = newnode(v[mid]);
        build(lson, l, mid - 1); build(rson, mid + 1, r);
        pushup(rt);
    }
    void split(int rt, int &l, int &r, int k) {
        if (!rt) return (void)(l = r = 0);
        clone(rt);
        pushdown(rt);
        if (t[lson].siz < k) l = rt, split(rson, rson, r, k-t[lson].siz-1);
        else r = rt, split(lson, l, lson, k);
        pushup(rt);
    }
    int merge(int x, int y) {
        if (!x || !y) return x + y;
        if (rd(0, (t[x].siz + t[y].siz) - 1) < t[x].siz) {
            clone(x), pushdown(x);
            t[x].rs = merge(t[x].rs, y);
            pushup(x); return x;
        } 
        else {
            clone(y), pushdown(y);
            t[y].ls = merge(x, t[y].ls);
            pushup(y); return y;
        }
    }
    int a, b, c, d, e;
    inline void copy() {
        int l1, r1, l2, r2, bk = 1;
        read(l1, r1, l2, r2);
        if (r1 > r2) swap(l1, l2), swap(r1, r2), bk = 0;
        split(root, d, e, r2); split(d, c, d, l2 - 1);
        split(c, b, c, r1); split(b, a, b, l1 -1);
        if (bk) root = merge(a, merge(b, merge(c, merge(b, e))));
        else root = merge(a, merge(d, merge(c, merge(d, e))));
    }
    inline void sp() {
        int l1, r1, l2, r2;
        read(l1, r1, l2, r2);
        if (r1 > r2) swap(l1, l2), swap(r1, r2);
        split(root, d, e, r2); split(d, c, d, l2 - 1);
        split(c, b, c, r1); split(b, a, b, l1 -1);
        root = merge(a, merge(d, merge(c, merge(b, e))));
    }
    inline void push(int rt) {
        if (!rt) return;
        pushdown(rt);
        push(lson), v[++n] = t[rt].val, push(rson);
    }
}
using namespace FHQ_treap;

inline void solve() {
    read(n, q);
    for (int i = 1; i <= n; ++i) read(v[i]);
    build(root, 1, n);
    while (q--) {
        int opt;
        read(opt);
        switch (opt) {
            case 1: {
                int l, r, a, b ,c;
                read(l, r);
                split(root, b, c, r); split(b, a, b, l - 1);
                printf("%d\n",t[b].sum);
                root = merge(a, merge(b, c));
                break;
            }
            case 2: {
                int l, r, k, a, b ,c;
                read(l, r, k);
                split(root, b, c, r); split(b, a, b, l - 1);
                clone(b); cov(b, k);
                root = merge(a, merge(b, c));
                break;
            }
            case 3: {
                int l, r, k, a, b ,c;
                read(l, r, k);
                split(root, b, c, r); split(b, a, b, l - 1);
                clone(b); add(b, k);
                root = merge(a, merge(b, c));
                break;
            }
            case 4: copy(); break;
            case 5: sp(); break;
            case 6: {
                int l, r, a, b ,c;
                read(l, r);
                split(root, b, c, r); split(b, a, b, l - 1);
                clone(b); rev(b);
                root = merge(a, merge(b, c));
                break;
            }
        }
        if (tot > 3600000) n = 0, push(root), root = tot = 0, build(root, 1, n);
    }
    n = 0, push(root);
    for (int i = 1; i <= n; ++i) printf("%d ", v[i]);
}

signed main() {
    // freopen("P5586_1.in","r",stdin);
    // freopen("my.out","w",stdout);
    // read(T);
    solve();
    return 0;
}