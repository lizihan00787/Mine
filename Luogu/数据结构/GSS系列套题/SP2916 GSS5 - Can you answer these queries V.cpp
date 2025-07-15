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

const int N = 1e4+20;

int n, m, a[N];

namespace Segtree{
    #define lson (rt<<1)
    #define rson (rt<<1|1)
    struct node {
        int pre, suf, sum, maxx;
        node operator + (const node &b) const {
            node c;
            c.sum = sum + b.sum;
            c.maxx = max(max(maxx, b.maxx), suf + b.pre);
            c.pre = max(pre, sum + b.pre);
            c.suf = max(b.suf, b.sum + suf);
            return c;
        }
    } t[N << 2];
    void build(int rt, int l, int r) {
        if (l == r) return (void)(t[rt].sum = t[rt].maxx = t[rt].pre = t[rt].suf = a[l]);
        int mid = (l + r) >> 1;
        build(lson, l, mid); build(rson, mid + 1, r);
        t[rt] = t[lson] + t[rson];
    }
    node query(int rt, int l, int r, int L, int R) {
        if (L > R) return node{0, 0, 0, 0};
        if (L <= l && r <= R) return t[rt];
        int mid = (l + r) >> 1;
        if (L > mid) return query(rson, mid + 1, r, L, R);
        else if (R <= mid) return query(lson, l, mid, L, R);
        else return query(lson, l, mid, L, R) + query(rson, mid + 1, r, L, R);
    }
}
using namespace Segtree;

int que(int l1, int r1, int l2, int r2) {
    if (r1 < l2){
        int tmp = query(1, 1, n, r1 + 1, l2 - 1).sum;
        tmp += query(1, 1, n, l1, r1).suf;
        tmp += query(1, 1, n, l2, r2).pre;
        return tmp;
    }
    int ans = query(1, 1, n, l2, r1).maxx;
    if (l1 < l2) ans = max(ans, query(1, 1, n, l1, l2).suf + query(1, 1, n, l2, r2).pre - a[l2]);
    if (r2 > r1) ans = max(ans, query(1, 1, n, l1, r1).suf + query(1, 1, n, r1, r2).pre - a[r1]);
    return ans;
}

inline void solve() {
    read(n);
    for (int i = 1; i <= n; ++i) read(a[i]);
    build(1, 1, n);
    read(m);
    while (m--) {
        int l1, r1, l2, r2;
        read(l1, r1, l2, r2);
        printf("%d\n", que(l1, r1, l2, r2));
    }
    memset(t, 0, sizeof(t));
    memset(a, 0, sizeof(a));
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    read(T);
    while (T--) solve();
    return 0;
}