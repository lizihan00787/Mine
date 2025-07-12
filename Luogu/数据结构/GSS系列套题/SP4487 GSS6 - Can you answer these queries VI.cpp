#include <bits/stdc++.h>
#define endl '\n'
#define ll long long
#define PII pair<int, int>
#define mk(a, b) make_pair(a, b)
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define per(i, a, b) for (int i = (a); i >= (b); --i)
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
inline void read(Ty &x, Args &...args) {read(x); read(args...);}
int T = 1;

const int N = 2e5+20;
std::mt19937 rnd(233);

int n, m, rt, a[N];

namespace FHQ_Treap {
    #define lson (t[rt].l)
    #define rson (t[rt].r)
    struct node {
        int l, r, siz, val, key;
        int lsum, rsum, sum, mx;
    } t[N];
    int cnt=0;
    void pushup(int rt) {
        t[rt].siz = t[lson].siz + t[rson].siz + 1;
        t[rt].sum = t[lson].sum + t[rson].sum + t[rt].val;
        t[rt].mx = max(max(t[lson].mx, t[rson].mx), t[rt].val + t[lson].rsum + t[rson].lsum);
        t[rt].lsum = max(t[lson].lsum, t[lson].sum + t[rt].val + t[rson].lsum);
        t[rt].rsum = max(t[rson].rsum, t[rson].sum + t[rt].val + t[lson].rsum);
    }
    int newnode(int val) {
        t[++cnt].siz = 1;
        t[cnt].key = rnd();
        t[cnt].val = t[cnt].mx = t[cnt].sum = val;
        t[cnt].lsum = t[cnt].rsum = max(val, 0);
        return cnt;
    }
    void split(int rt, int &l, int &r, int k) {
        if (!rt) 
            return (void)(l = r = 0);
        if (t[lson].siz < k) {
            l = rt;
            split(rson, rson, r, k - t[lson].siz - 1);
        }
        else {
            r = rt;
            split(lson, l, lson, k);
        }
        pushup(rt);
    }
    int merge(int x, int y) {
        if (!x || !y) return x + y;
        if (t[x].key < t[y].key) {
            t[x].r = merge(t[x].r, y);
            return pushup(x), x;
        }
        else {
            t[y].l = merge(x, t[y].l);
            return pushup(y), y;
        }
    }
}
using namespace FHQ_Treap;

inline void solve() {
    read(n);
    rep (i, 1, n) {
        read(a[i]);
        rt = merge(rt, newnode(a[i]));
    }
    t[0].mx=-0x3f3f3f3f;
    read(m);
    while (m--) {
        int x, y, z, a, b;
        char op[2];
        scanf("%s", op);
        if (op[0] == 'I') {
            read(a, b);
            split(rt, x, y, a - 1);
            rt  = merge(x, merge(newnode(b), y));
        }
        else if (op[0] == 'D') {
            read(a);
            split(rt, x, y, a - 1); split(y, y, z, 1);
            rt = merge(x, z);
        }
        else if (op[0] == 'R') {
            read(a, b);
            split(rt, x, y, a - 1); split(y, y, z, 1);
            t[y].val = b; pushup(y);
            rt = merge(x, merge(y, z));
        }
        else {
            read(a, b);
            split(rt, x, y, b); split(x, x, z, a - 1);
            cout << t[z].mx << endl;
            rt = merge(merge(x, z), y);
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