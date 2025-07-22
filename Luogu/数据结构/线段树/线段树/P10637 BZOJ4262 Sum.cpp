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

const int N = 1e5 + 20;

int n = 1e5, q;
ll a[N];
struct node {
    int l, r, k, id;
};

namespace Segtree {
    #define lson (rt << 1)
    #define rson (rt << 1 | 1)
    #define mid ((l + r) >> 1)
    ll t[N << 2], tag[N << 2];
    inline void pushup(int rt) { t[rt] = t[lson] + t[rson]; }
    inline void pushtag(int rt, int l, int r, ll x) { t[rt] += (r - l + 1) * x, tag[rt] += x; }
    inline void pushdown(int rt, int l, int r) { if(!tag[rt]) return; pushtag(lson, l, mid, tag[rt]), pushtag(rson, mid + 1, r, tag[rt]); tag[rt] = 0; }
    void update(int rt, int l, int r, int L, int R, ll x) {
        if (L <= l && r <= R) return (void)(pushtag(rt, l, r, x));
        pushdown(rt, l, r);
        if (L <= mid) update(lson, l, mid, L, R, x);
        if (R > mid) update(rson, mid + 1, r, L, R, x);
        pushup(rt);
    }
    ll query(int rt, int l, int r, int L, int R) {
        if (L <= l && r <= R) return t[rt];
        pushdown(rt, l, r);
        ll res = 0;
        if (L <= mid) res += query(lson, l, mid, L, R);
        if (R > mid) res += query(rson, mid + 1, r, L, R);
        return res;
    }
}
using namespace Segtree;

namespace DataMaker {
    const int mod = 1e9;
    ll fst = 1023, sec = 1025;
    void solve() {
        for (int i = 1; i <= n; ++i) {
            a[i] = fst ^ sec;
            fst = fst * 1023 % mod;
            sec = sec * 1025 % mod;
        }
    }
}

vector<node> v[N];
ll ans[N];
int st[N], tp;

void work() {
    memset(t, 0, sizeof(t)), memset(tag, 0, sizeof(tag)), tp = 0;
    for (int i = 1; i <= n; ++i) {
        while (tp && a[st[tp]] <= a[i]) {
            update(1, 1, n, st[tp - 1] + 1, st[tp], 1ll * (i - st[tp]) * a[st[tp]]);
            tp--;
        }
        st[++tp] = i;
        for (auto [l, r, k, id] : v[i]) {
            ll res = query(1, 1, n, l, r);
            for (int j = 1; j <= tp; ++j) {
                int len = min(st[j], r) - max(st[j - 1], l - 1);
                if (len <= 0) continue;
                res += 1ll * len * (i - st[j] + 1) * a[st[j]];
            }
            ans[id] += (res * k);
        }
    }
}

inline void solve() {
    read(q);
    DataMaker::solve();
    for (int i = 1; i <= q; ++i) {
        int l1, l2, r1, r2;
        read(l1, r1, l2, r2);
        v[r2].emplace_back((node){l1, r1, 1, i});
        v[l2 - 1].emplace_back((node){l1, r1, -1, i}); // 将询问差分后的新询问。
    }
    work();
    for (int i = 1; i <= n; ++i) a[i] *= -1;
    work();
    for (int i = 1; i <= q; ++i) printf("%lld\n", ans[i]);
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}