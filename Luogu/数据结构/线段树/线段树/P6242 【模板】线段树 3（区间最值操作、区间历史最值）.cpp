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

const int N = 5e5 + 20;

int n, m;
int a[N];

namespace Segtree {
    #define lson (rt << 1)
    #define rson (rt << 1 | 1)
    struct node {
        int sum, maxa, maxb, semi, cnt;
        int add1, add2, add3, add4;
    } t[N << 2];
    void pushup(int rt) {
        t[rt].sum = t[lson].sum + t[rson].sum;
        t[rt].maxa = max(t[lson].maxa, t[rson].maxa);
        t[rt].maxb = max(t[lson].maxb, t[rson].maxb);
        if (t[lson].maxa == t[rson].maxa) {
            t[rt].cnt = t[lson].cnt + t[rson].cnt;
            t[rt].semi = max(t[lson].semi, t[rson].semi);
        }
        else if (t[lson].maxa > t[rson].maxa) {
            t[rt].cnt = t[lson].cnt;
            t[rt].semi = max(t[lson].semi, t[rson].maxa);
        }
        else {
            t[rt].cnt = t[rson].cnt;
            t[rt].semi = max(t[lson].maxa, t[rson].semi);
        }
    }
    void pushtag(int rt, int l, int r, int k1, int k2, int k3, int k4, bool flag) {
        t[rt].sum += t[rt].cnt * k1 + (r - l + 1 - t[rt].cnt) * k2;
        if(flag) t[rt].maxa += k1;
        t[rt].maxb = max(t[rt].maxb, t[rt].maxa + k3);
        if(!flag) t[rt].maxa += k1;
        if (t[rt].semi != -0x3f3f3f3f3f3f3f3f) t[rt].semi += k2;
        if(flag) t[rt].add1 += k1, t[rt].add2 += k2;
        t[rt].add3 = max(t[rt].add3, t[rt].add1 + k3);
        t[rt].add4 = max(t[rt].add4, t[rt].add2 + k4);
        if(!flag) t[rt].add1 += k1, t[rt].add2 += k2;
    }
    void pushdown(int rt, int l, int r) {
        int maxx = max(t[lson].maxa, t[rson].maxa), mid = (l + r) >> 1;
        int &k1 = t[rt].add1, &k2 = t[rt].add2, &k3 = t[rt].add3, &k4 = t[rt].add4;
        if (t[lson].maxa == maxx) pushtag(lson, l, mid, k1, k2, k3, k4, 0);
        else pushtag(lson, l, mid, k2, k2, k4, k4, 0);
        if (t[rson].maxa == maxx) pushtag(rson, mid + 1, r, k1, k2, k3, k4, 0);
        else pushtag(rson, mid + 1, r, k2, k2, k4, k4, 0);
        k1 = k2 = k3 = k4 = 0;
    }
    void build(int rt, int l, int r) {
        if (l == r) {
            t[rt].sum = t[rt].maxa = t[rt].maxb = a[l];
            t[rt].semi = -0x3f3f3f3f3f3f3f3f;
            t[rt].cnt = 1;
            return;
        }
        int mid = (l + r) >> 1;
        build(lson, l, mid);build(rson, mid + 1, r);
        pushup(rt);
    }
    void update(int rt, int l, int r, int L, int R, int x) {
        if (L <= l && r <= R) return (void)(pushtag(rt, l, r, x, x, 0, 0, 1));
        pushdown(rt, l, r);
        int mid = (l + r) >> 1;
        if (L <= mid) update(lson, l, mid, L, R, x);
        if (R > mid) update(rson, mid + 1, r, L, R, x);
        pushup(rt);
    }
    void updatemin(int rt, int l, int r, int L, int R, int x) {
        if (x >= t[rt].maxa) return;
        if (L <= l && r <= R && x > t[rt].semi) {
            int k = t[rt].maxa - x;
            t[rt].sum -= k * t[rt].cnt;
            t[rt].maxa = x, t[rt].add1 -= k;
            return;
        }
        pushdown(rt, l, r);
        int mid = (l + r) >> 1;
        if (L <= mid) updatemin(lson, l, mid, L, R, x);
        if (R > mid) updatemin(rson, mid + 1, r, L, R, x);
        pushup(rt);
    }
    int querysum(int rt, int l, int r, int L, int R) {
        if (L <= l && r <= R) return t[rt].sum;
        pushdown(rt, l, r);
        int mid = (l + r) >> 1, res = 0;
        if (L <= mid) res += querysum(lson, l, mid, L, R);
        if (R > mid) res += querysum(rson, mid + 1, r, L, R);
        return res;
    }
    int querymax(int rt, int l, int r, int L, int R, int k) {
        if (L <= l && r <= R) {
            if (k == 0) return t[rt].maxa;
            else return t[rt].maxb;
        }
        pushdown(rt, l, r);
        int mid = (l + r) >> 1, res = -0x3f3f3f3f3f3f3f3f;
        if (L <= mid) res = max(res, querymax(lson, l, mid, L, R, k));
        if (R > mid) res = max(res, querymax(rson, mid + 1, r, L, R, k));
        return res;
    }
}
using namespace Segtree;

inline void solve() {
    read(n, m);
    for (int i = 1; i <= n; ++i) read(a[i]);
    build(1, 1, n);
    while (m--) {
        int op, l, r, k;
        read(op, l, r);
        if (op == 1) read(k), update(1, 1, n, l, r, k);
        else if (op == 2) read(k), updatemin(1, 1, n, l, r, k);
        else if (op == 3) printf("%lld\n", querysum(1, 1, n, l, r));
        else if (op == 4) printf("%lld\n", querymax(1, 1, n, l, r, 0));
        else printf("%lld\n", querymax(1, 1, n, l, r, 1));
    }
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}