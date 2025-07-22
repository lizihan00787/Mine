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

const int N = 2e5 + 20;

int n, q;
int a[N];

namespace Segtree {
    #define lson (rt << 1)
    #define rson (rt << 1 | 1)
    #define mid ((l + r) >> 1)
    struct node {
        int xsum, cnt[30];
        int minn, semi, mcnt, tag;
    } t[N << 2];
    inline void pushup(int rt) {
        t[rt].xsum = t[lson].xsum ^ t[rson].xsum;
        for (int i = 0; i < 30; ++i) t[rt].cnt[i] = t[lson].cnt[i] + t[rson].cnt[i];
        if (t[lson].minn == t[rson].minn) {
            t[rt].minn  =t[lson].minn;
            t[rt].semi = min(t[lson].semi, t[rson].semi);
            t[rt].mcnt = t[lson].mcnt + t[rson].mcnt;
        }
        else if (t[lson].minn > t[rson].minn) {
            t[rt].minn = t[rson].minn;
            t[rt].semi = min(t[lson].minn, t[rson].semi);
            t[rt].mcnt = t[rson].mcnt;
        }
        else if (t[lson].minn < t[rson].minn) {
            t[rt].minn = t[lson].minn;
            t[rt].semi = min(t[lson].semi, t[rson].minn);
            t[rt].mcnt = t[lson].mcnt;
        }
    }
    inline void pushtag(int rt, int x) {
        if (t[rt].minn >= x) return;
        t[rt].xsum ^= ((t[rt].mcnt & 1) * (t[rt].minn ^ x));
        for (int i = 0; i < 30; ++i) t[rt].cnt[i] +=((x >> i & 1) - (t[rt].minn >> i & 1)) * t[rt].mcnt;
        t[rt].minn = t[rt].tag = x;
    }
    inline void pushdown(int rt) {
        if (t[rt].tag == -1) return;
        pushtag(lson, t[rt].tag), pushtag(rson, t[rt].tag);
        t[rt].tag = -1;
    }
    void build(int rt, int l, int r) {
        t[rt].tag = -1;
        if (l == r) {
            t[rt].minn = t[rt].xsum = a[l];
            t[rt].semi = INT_MAX; t[rt].mcnt = 1;
            for (int i = 0; i < 30; ++i) t[rt].cnt[i] = (a[l] >> i & 1);
            return;
        }
        build(lson, l, mid); build(rson, mid + 1, r);
        pushup(rt);
    }
    void update(int rt, int l, int r, int L, int R, int x) {
        if (t[rt].minn >= x) return;
        if (L <= l && r <= R && t[rt].semi > x) return (void)(pushtag(rt, x));
        pushdown(rt);
        if (L <= mid) update(lson, l, mid, L, R, x);
        if (R > mid) update(rson, mid + 1, r, L, R, x);
        pushup(rt);
    }
    int queryx(int rt, int l, int r, int L, int R) {
        if (L <= l && r <= R) return t[rt].xsum;
        pushdown(rt);
        int res = 0;
        if (L <= mid) res ^= queryx(lson, l, mid, L, R);
        if (R > mid) res ^= queryx(rson, mid + 1, r, L, R);
        return res;
    }
    int queryc(int rt, int l, int r, int L, int R, int k) {
        if (L <= l && r <= R) return t[rt].cnt[k];
        pushdown(rt);
        int res = 0;
        if (L <= mid) res += queryc(lson, l, mid, L, R, k);
        if (R > mid) res += queryc(rson, mid + 1, r, L, R, k);
        return res;
    }
}
using namespace Segtree;

inline void solve() {
    read(n, q);
    for (int i = 1; i <= n; ++i) read(a[i]);
    build(1, 1, n);
    while (q--) {
        int op, l, r, x;
        read(op, l, r, x);
        if (op == 1) update(1, 1, n, l, r, x);
        else {
            int xsum = queryx(1, 1, n, l, r) ^ x, fl = -1;
            for (int i = 0; i < 30; ++i) if (xsum >> i & 1) fl = i;
            if (fl == -1) { puts("0"); continue; }
            int ans = queryc(1, 1, n, l, r, fl) + (x >> fl & 1);
            printf("%d\n", ans);
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