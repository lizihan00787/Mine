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

const int N = 3e5 + 20;

int n, m, k;
int a[N];

inline void solve() {
    read(n, m, k);
    for (int i = 1; i <= n; ++i) read(a[i]);
    sort(a + 1, a + n + 1);
    ll ans = 0, res = 0;
    for (int i = 1; i <= n; ++i) {
        if (k < m) {
            ans += k * (a[i] + res);
            printf("%lld\n", ans);
            return;
        }
        else k -= m, ans += m * (a[i] + res), res += m;
    }
    printf("%lld\n", ans);
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    read(T);
    while (T--) solve();
    return 0;
}