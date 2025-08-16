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

const int N = 1e5 + 20, M = 1e6 + 20, inf = 1e18;

int n;
int h[N], w[N], s[N];
struct line {
    int k, b;
} line[N];
int dp[N];

int calc(int id, int pos) { return line[id].k * pos + line[id].b; }
bool Cmp(int id1, int id2, int pos) { return calc(id1, pos) < calc(id2, pos); }

namespace LCT {
    #define lson (rt << 1)
    #define rson (rt << 1 | 1)
    #define mid ((l + r) >> 1)
    int t[M << 2];
    void insert(int rt, int l, int r, int id) {
        if (l == r) { if (Cmp(id, t[rt], l)) t[rt] = id; return;}
        if (Cmp(id, t[rt], mid)) swap(id, t[rt]);
        if (Cmp(id, t[rt], l)) insert(lson, l, mid, id);
        if (Cmp(id, t[rt], r)) insert(rson, mid + 1, r, id);
    }
    int query(int rt, int l, int r, int pos) {
        int res = calc(t[rt], pos);
        if (l == r) return res;
        if (pos <= mid) res = min(res, query(lson, l, mid, pos));
        else res = min(res, query(rson, mid + 1, r, pos));
        return res;
    }
}
using namespace LCT;

inline void solve() {
    read(n);
    for (int i = 1; i <= n; ++i) read(h[i]);
    for (int i = 1; i <= n; ++i) read(w[i]);
    for (int i = 1; i <= n; ++i) s[i] = s[i - 1] + w[i];
    line[0] = {0, inf};
    line[1] = {-2 * h[1], h[1] * h[1] - s[1]};
    insert(1, 0, M, 1);
    for (int i = 2; i <= n; ++i) {
        dp[i] = h[i] * h[i] + s[i - 1] + query(1, 0, M, h[i]);
        line[i] = {-2 * h[i], h[i] * h[i] - s[i] + dp[i]};
        insert(1, 0, M, i);
    }
    printf("%lld\n", dp[n]);
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}