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

int n, l, r, ans;

inline void solve() {
    read(n); l = 1, ans = 0;
    while (l <= n) {
        r = n / (n / l);
        int res = 0;
        for (int i = l, j; i <= r; i = j + 1) {
            int tmp = log2(i);
            j = min((1ll << (tmp + 1)) - 1, r);
            res += tmp * (((j - i + 1) >> 1) + (i & 1 && j & 1));
        }
        ans += res * (n / l);
        l = r + 1;
    }
    printf("%lld\n", ans * 2);
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}