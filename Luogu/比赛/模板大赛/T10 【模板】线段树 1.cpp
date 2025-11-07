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

const int N = 1e5 + 10;

int n, m;
int a[N];

namespace S_tree {
    #define lson (rt << 1)
    #define rson (rt << 1 | 1)
    #define mid ((l + r) >> 1)
    int t[N << 2], tag[N << 2];
    void pushup(int rt) { t[rt] = t[lson] + t[rson]; }
    void build(int rt, int l, int r) {
        if (l == r) return (void)(t[rt] = a[l], tag[rt] = 0);
        build(lson, l, mid); build(rson, mid + 1, r);
        pushup(rt);
    }
    void pushdown(int rt, int l, int r) {
        if (!tag[rt]) return;
        t[lson] += tag[rt] * (mid - l + 1);
        t[rson] += tag[rt] * (r - mid);
        tag[lson] += tag[rt];
        tag[rson] += tag[rt];
        tag[rt] = 0;
    }
    void update(int rt, int l, int r, int L, int R, int x) {
        if (L <= l && r <= R) return (void)(t[rt] += (r - l + 1) * x, tag[rt] += x);
        pushdown(rt, l, r);
        if (L <= mid) update(lson, l, mid, L, R, x);
        if (R > mid) update(rson, mid + 1, r, L, R, x);
        pushup(rt);
    }
    int query(int rt, int l, int r, int L, int R) {
        if (L <= l && r <= R) return t[rt];
        pushdown(rt, l, r);
        int ans = 0;
        if (L <= mid) ans += query(lson, l, mid, L, R);
        if (R > mid) ans += query(rson, mid + 1, r, L, R);
        return ans;
    }
}
using namespace S_tree;

inline void solve() {
    read(n, m);
    for (int i = 1; i <= n; ++i) read(a[i]);
    build(1, 1, n);
    for (int i = 1; i <= m; ++i) {
        int op, l, r, x;
        read(op);
        if (op == 1) read(l, r, x), update(1, 1, n, l, r, x);
        else read(l, r), printf("%lld\n", query(1, 1, n, l, r));
    }
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}