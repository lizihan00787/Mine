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

const int N = 5e5 + 10;

int n, m;

namespace BIT {
    #define lowbit(x) (x & (-x))
    int t[N];
    void add(int k, int x) { for(; k <= n; k += lowbit(k)) t[k] += x; }
    int get(int k) { int res = 0; for(; k; k -= lowbit(k)) res += t[k]; return res; }
    int getl(int l, int r) { return get(r) - get(l - 1); }
}
using namespace BIT;

inline void solve() {
    read(n, m);
    for (int i = 1, x; i <= n; ++i) read(x), add(i, x);
    for (int i = 1; i <= m; ++i) {
        int op, l, r, x, k;
        read(op);
        if (op == 1) read(k, x), add(k, x);
        else read(l, r), printf("%d\n", getl(l, r));
    }
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}