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

int n;

namespace FHQ_treap {
    #define lson (t[rt].ls)
    #define rson (t[rt].rs)
    mt19937 rnd(233);
    struct node {
        int val, siz, key;
        int ls, rs;
    } t[N];
    int tot, root;
    int newnode(int val) {
        t[++tot].val = val;
        t[tot].key = rnd();
        t[tot].siz = 1;
        return tot;
    }
    void pushup(int rt) { t[rt].siz = t[lson].siz + t[rson].siz + 1; }
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
    void split(int rt, int val, int &x, int &y) {
        if (!rt) return (void)(x = y = 0);
        if (t[rt].val <= val) {
            x = rt;
            split(rson, val, rson, y);
        }
        else {
            y = rt;
            split(lson, val, x, lson);
        }
        pushup(rt);
    }
    int x, y, z;
    void insert(int val) {
        split(root, val, x, y);
        root = merge(x, merge(newnode(val), y));
    }
    void del(int val) {
        split(root, val, x, z);
        split(x, val - 1, x, y);
        y = merge(t[y].ls, t[y].rs);
        root = merge(merge(x, y), z);
    }
    int getrnk(int val) {
        split(root, val - 1, x, y);
        int ans = t[x].siz + 1;
        root = merge(x, y);
        return ans;
    }
    int getval(int rnk) {
        int rt = root;
        while (rt) {
            if (t[lson].siz + 1 == rnk) break;
            else if (t[lson].siz >= rnk) rt = lson;
            else rnk -= t[lson].siz + 1, rt = rson;
        }
        return t[rt].val;
    }
    int pre(int val) {
        split(root, val - 1, x, y);
        int rt = x;
        while (rson) rt = rson;
        int res = t[rt].val;
        root = merge(x, y);
        return res;
    }
    int nxt(int val) {
        split(root, val, x, y);
        int rt = y;
        while (lson) rt = lson;
        int res = t[rt].val;
        root = merge(x, y);
        return res;
    }
}
using namespace FHQ_treap;

inline void solve() {
    read(n);
    for (int i = 1; i <= n; ++i) {
        int op;
        int x;
        read(op);
        read(x);
        if (op == 1) insert(x);
        else if (op == 2) del(x);
        else if (op == 3) cout << getrnk(x) << endl;
        else if (op == 4) cout << getval(x) << endl;
        else if (op == 5) cout << pre(x) << endl;
        else cout << nxt(x) << endl;
    }
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}