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

const int N = 1e5 + 10;

int n, q;
char s[N];

namespace FHQ_treap {
    mt19937 rnd(233);
    #define lson (t[rt].ls)
    #define rson (t[rt].rs)
    struct node{
        int siz, key, rs, ls, val;
        int sum, premax, sufmax, premin, sufmin;
        bool rev, opp;
        int cov; 
    } t[N];
    int tot, root;
    int newnode(int val) {
        ++tot;
        t[tot].val = t[tot].sum = val;
        t[tot].key = rnd();
        if (val == 1) t[tot].premax = t[tot].sufmax = 1;
        else t[tot].premin = t[tot].sufmin = -1;
        t[tot].siz = 1;
        return tot;
    }
    void pushup(int rt) {
        t[rt].siz = t[lson].siz + t[rson].siz + 1;
        t[rt].sum = t[lson].sum + t[rson].sum + t[rt].val;
        t[rt].premax = max(t[lson].premax, t[lson].sum + t[rt].val + t[rson].premax);
        t[rt].premin = min(t[lson].premin, t[lson].sum + t[rt].val + t[rson].premin);
        t[rt].sufmax = max(t[rson].sufmax, t[rson].sum + t[rt].val + t[lson].sufmax);
        t[rt].sufmin = min(t[rson].sufmin, t[rson].sum + t[rt].val + t[lson].sufmin);
    }
    void pushtag(int rt, bool rev, bool opp, int cov) {
        if (opp) {
            t[rt].sum = -t[rt].sum; t[rt].val = -t[rt].val;
            int a = t[rt].premax, b = t[rt].premin;
            t[rt].premin = -a, t[rt].premax = -b;
            a = t[rt].sufmax, b = t[rt].sufmin;
            t[rt].sufmin = -a, t[rt].sufmax = -b;
            t[rt].cov = -t[rt].cov;
            t[rt].opp ^= 1;
        }
        if (cov) {
            t[rt].val = t[rt].cov = cov;
            t[rt].sum = t[rt].siz * cov;
            if (cov == 1) t[rt].premax = t[rt].sufmax = t[rt].sum, t[rt].premin = t[rt].sufmin = 0;
            else t[rt].premax = t[rt].sufmax = 0, t[rt].premin = t[rt].sufmin = t[rt].sum;
        }
        if (rev) {
            swap(t[rt].ls, t[rt].rs);
            swap(t[rt].premax, t[rt].sufmax);
            swap(t[rt].premin, t[rt].sufmin);
            t[rt].rev ^= 1;
        }
    }
    void pushdown(int rt) {
        if (!t[rt].cov && !t[rt].rev && !t[rt].opp) return;
        if (lson) pushtag(lson, t[rt].rev, t[rt].opp, t[rt].cov);
        if (rson) pushtag(rson, t[rt].rev, t[rt].opp, t[rt].cov);
        t[rt].cov = t[rt].rev = t[rt].opp = 0;
    }
    int merge(int x, int y) {
        if (!x || !y) return x + y;
        pushdown(x); pushdown(y);
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
    int query(int l, int r) {
        int x, y, z, tmp1, tmp2, res = 0;
        split(root, r, x, z);
        split(x, l - 1, x, y);
        tmp1 = t[y].premax, tmp2 = abs(t[y].sufmin);
        res = (tmp1 + 1) / 2 + (tmp2 + 1) / 2;
		root = merge(merge(x, y),z);
        return res;
    }
    void replace(int l, int r, int k) {
        int x, y, z;
        split(root, r, x, z);
        split(x, l - 1, x, y);
        pushtag(y, 0, 0, k);
		root = merge(merge(x, y),z);
    }
    void reverse(int l, int r) {
        int x, y, z;
        split(root, r, x, z);
        split(x, l - 1, x, y);
        pushtag(y, 1, 0, 0);
		root = merge(merge(x, y),z);
    }
    void invert(int l, int r) {
        int x, y, z;
        split(root, r, x, z);
        split(x, l - 1, x, y);
        pushtag(y, 0, 1, 0);
		root = merge(merge(x, y),z);
    }
}
using namespace FHQ_treap;

inline void solve() {
    read(n, q);
    scanf("%s", s + 1);
    for (int i = 1; i <= n; ++i) root = merge(root, newnode((s[i] == ')') ? 1 : -1));
    while (q--) {
        char op[10];
        scanf("%s", op + 1);
        int l, r;
        read(l, r);
        if (op[1] == 'R') {
            char x;
            x = getchar();
            replace(l, r, (x == ')') ? 1 : -1);
        }
        else if (op[1] == 'S') reverse(l, r);
        else if (op[1] == 'I') invert(l, r);
        else printf("%d\n", query(l, r));
    }
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}