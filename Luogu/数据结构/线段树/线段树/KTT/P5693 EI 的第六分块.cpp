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

const int N = 4e5 + 20, inf = 0x3f3f3f3f3f3f3f3f;

int n, Q, p[N];

namespace KTT {
    struct Func {
        int k, b;
        inline Func operator + (const Func &x) const {
            return (Func){k + x.k, b + x.b};
        }
        inline void add(int v) {b += k * v;}
    };
    inline pair<Func, int> max(Func a, Func b) { //求之后的函数为哪个和变更的阈值
        if (a.k < b.k || (a.k == b.k && a.b < b.b)) swap(a, b);
        if (a.b >= b.b) return mk(a, inf);
        return mk(b, (b.b - a.b) / (a.k - b.k));
    }
    struct node {
        Func lmax, rmax, maxx, sum;
        int x;
        inline node operator + (const node &b) const {
            node t;
            pair<Func, int> tmp;
            t.x = min(x, b.x);
            tmp = max(lmax, b.lmax + sum); //（计算lmax的改变后的函数和改变的阈值）
            t.lmax = tmp.first, t.x = min(t.x, tmp.second); // 阈值要取最小的，这样访问就直接更新
            tmp = max(b.rmax, rmax + b.sum);
            t.rmax = tmp.first, t.x = min(t.x, tmp.second);
            tmp = max(maxx, b.maxx);
            t.x = min(t.x, tmp.second);
            tmp = max(tmp.first, rmax + b.lmax);
            t.maxx = tmp.first, t.x = min(t.x, tmp.second);
            t.sum = sum + b.sum;
            return t;
        }
    };
    #define lson (rt << 1)
    #define rson (rt << 1 | 1)
    node t[N << 2];
    int tag[N << 2];
    inline void pushup(int rt) { t[rt] = t[lson] + t[rson]; }
    inline void pushtag(int rt, int v) {
        tag[rt] += v;
        t[rt].x -= v;
        t[rt].lmax.add(v);
        t[rt].rmax.add(v);
        t[rt].maxx.add(v);
        t[rt].sum.add(v);
    }
    inline void pushdown(int rt) {
        if(!tag[rt]) return;
        pushtag(lson, tag[rt]);
        pushtag(rson, tag[rt]);
        tag[rt] = 0;
    }
    inline void build(int rt, int l, int r) {
        if (l == r) {
            Func q = {1, p[l]};
            t[rt] = {q, q, q, q, inf};
            return;
        }
        int mid = (l + r) >> 1;
        build(lson, l, mid);
        build(rson, mid + 1, r);
        pushup(rt);
    }
    inline void upd(int rt, int l, int r, int v) {
        if (v > t[rt].x) {
            int mid = (l + r) >> 1;
            upd(lson, l, mid, tag[rt] + v);
            upd(rson, mid + 1, r, tag[rt] + v);
            tag[rt] = 0;
            pushup(rt);
        }
        else pushtag(rt, v);
    }
    inline void update(int rt, int l, int r, int L, int R, int v) {
        if (L <= l && r <= R) return (void)(upd(rt, l, r, v));
        pushdown(rt);
        int mid = (l + r) >> 1;
        if (L <= mid) update(lson, l, mid, L, R, v);
        if (R > mid) update(rson, mid + 1, r, L, R, v);
        pushup(rt);
    }
    inline node query(int rt, int l, int r, int L, int R) {
        if (L <= l && r <= R) return t[rt];
        pushdown(rt);
        int mid = (l + r) >> 1;
        if (R <= mid) return query(lson, l, mid, L, R);
        if (L > mid) return query(rson, mid + 1, r, L, R);
        return query(lson, l, mid, L, R) + query(rson, mid + 1, r, L, R);
    }
}
using namespace KTT;

inline void solve() {
    read(n, Q);
    for (int i = 1; i <= n; ++i) read(p[i]);
    build(1, 1, n);
    while (Q--) {
        int opt, l, r, x;
        read(opt, l, r);
        if (opt == 1) {
            read(x);
            update(1, 1, n, l, r, x);
        }
        else {
            printf("%lld\n", max(0ll, query(1, 1, n, l, r).maxx.b));
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