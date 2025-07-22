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

const int N = 1e5 + 20, inf = 0x3f3f3f3f3f3f3f3f;

int n, Q, p[N];

namespace KTT {
    struct Func {
        int k, b;
        inline Func operator + (const Func &x) const {
            return (Func){k + x.k, b + x.b};
        }
        inline void add(int v) { b += k * v; }
        inline void set() { k = 0; } //pushup的时候没有最小值的一侧要清空
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
        inline node clear() {
            node a = *this;
            a.lmax.set(), a.rmax.set(), a.maxx.set(), a.sum.set();
            return a;
        }
    };
    #define lson (rt << 1)
    #define rson (rt << 1 | 1)
    node t[N << 2];
    int tag[N << 2], minn[N << 2], semi[N << 2];
    inline void pushup(int rt) { //吉司机线段树
        if (minn[lson] == minn[rson]) {
            minn[rt] = minn[lson];
            semi[rt] = min(semi[lson], semi[rson]);
            t[rt] = t[lson] + t[rson];
        }
        if (minn[lson] < minn[rson]) {
            minn[rt] = minn[lson];
            semi[rt] = min(semi[lson], minn[rson]);
            t[rt] = t[lson] + t[rson].clear();
        }
        if (minn[lson] > minn[rson]) {
            minn[rt] = minn[rson];
            semi[rt] = min(minn[lson], semi[rson]);
            t[rt] = t[lson].clear() + t[rson];
        }
    }
    inline void pushtag(int rt, int v) {
        if (v <= minn[rt]) return;
        int k = v - minn[rt];
        minn[rt] = v;
        tag[rt] = std::max(tag[rt], v);
        t[rt].x -= k; //加上求max的差值
        t[rt].lmax.add(k);
        t[rt].rmax.add(k);
        t[rt].maxx.add(k);
        t[rt].sum.add(k);
    }
    inline void pushdown(int rt) {
        if (tag[rt] == -inf) return;
        int bas = tag[rt];
        tag[rt] = -inf;
        pushtag(lson, bas);
        pushtag(rson, bas);
    }
    inline void build(int rt, int l, int r) {
        tag[rt] = -inf;
        if (l == r) {
            Func q = {1, p[l]};
            t[rt] = {q, q, q, q, inf};
            minn[rt] = p[l], semi[rt] = inf;
            return;
        }
        int mid = (l + r) >> 1;
        build(lson, l, mid);
        build(rson, mid + 1, r);
        pushup(rt);
    }
    inline void upd(int rt, int l, int r, int v) {
        tag[rt] = std::max(tag[rt], v);
        if (v - minn[rt] > t[rt].x) {
            int mid = (l + r) >> 1;
            upd(lson, l, mid, v);
            upd(rson, mid + 1, r, v);
            pushup(rt);
        }
        else pushtag(rt, v);
    }
    inline void update(int rt, int l, int r, int L, int R, int v) {
        if (minn[rt] >= v) return;
        if (L <= l && r <= R && v < semi[rt]) return (void)(upd(rt, l, r, v)); //需要注意这里必须判断修改值大于次大值
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
        if (opt == 0) {
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