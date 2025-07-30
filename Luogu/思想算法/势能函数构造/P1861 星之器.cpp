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

int n, m;
ll ans = 0;

inline void solve() {
    read(n, m);
    for (int i = 1; i <= n; ++i) for (int j = 1, x; j <= m; ++j) read(x), ans += 1ll * x * ((i + 1) * i / 2 + (j + 1) * j / 2);
    for (int i = 1; i <= n; ++i) for (int j = 1, x; j <= m; ++j) read(x), ans -= 1ll * x * ((i + 1) * i / 2 + (j + 1) * j / 2);
    printf("%lld\n", ans);
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}