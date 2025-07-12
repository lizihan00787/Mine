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

const int N = 1e5 + 20;

int n, m;
int a[N];

namespace Segtree {
    #define lson (rt<<1)
    #define rson (rt<<1|1)
    struct node {
        int sum,tag;
    } t[N << 2];
    void pushup(int rt) {
        t[rt].sum = t[lson].sum + t[rson].sum;
        if(t[lson].tag && t[rson].tag) t[rt].tag = 1;
        else t[rt].tag = 0;
    }
    void build(int rt, int l, int r) {
        if (l == r) {
            t[rt].sum = a[l];
            if (a[l] == 0 || a[l] == 1) t[rt].tag =1;
            else t[rt].tag = 0;
            return;
        }
        int mid = (l + r) >> 1;
        build(lson, l, mid); build(rson, mid + 1, r);
        pushup(rt);
    }
    void update(int rt, int l, int r, int L, int R) {
        if (l == r) {
            t[rt].sum = sqrt(t[rt].sum);
            if (t[rt].sum == 0 || t[rt].sum == 1) t[rt].tag = 1;
            return;
        }
        int mid = (l + r) >> 1;
        if (L <= mid && !t[lson].tag) update(lson, l, mid, L, R);
        if (R > mid && !t[rson].tag) update(rson, mid + 1, r, L, R);
        pushup(rt);
    }
    int query(int rt, int l, int r, int L, int R) {
        if (L <= l && r <= R) return t[rt].sum;
        int mid = (l + r) >> 1, res = 0;
        if (L <= mid) res += query(lson, l, mid, L, R);
        if (R > mid) res += query(rson, mid + 1, r, L, R);
        return res;
    }
}
using namespace Segtree;

inline void solve() {
    int cas = 0;
    while (~scanf("%lld", &n)) {
        cas++;
        memset(t, 0, sizeof(t));
        memset(a, 0, sizeof(a));
        for (int i = 1; i <= n; ++i) read(a[i]);
        build(1, 1, n);
        read(m);
        printf("Case #%lld:\n", cas);
        while (m--) {
            int opt, l, r;
            read(opt, l, r);
            if (l > r) swap(l, r);
            if (opt == 0) update(1, 1, n, l, r);
            else printf("%lld\n", query(1, 1, n, l, r));
        }
        puts("");
    }
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}