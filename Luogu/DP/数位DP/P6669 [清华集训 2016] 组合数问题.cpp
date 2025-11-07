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

const int N = 66;
const ll mod = 1e9 + 7;

ll n, m, f[N][2][2][2][2];
ll k, bn[N], bm[N];

int calc(int x, bool ok, bool dif, bool dii, bool dij) {
    if (!x) return ok;
    ll &res = f[x][ok][dif][dii][dij];
    if (~res) return res;
    res = 0;
    int upn = dii ? k - 1 : bn[x], upm = dij ? k - 1 : bm[x];
    for (int i = 0; i <= upn; ++i)
        for (int j = 0; j <= upm && (j <= i || dif); ++j) (res += calc(x - 1, ok | (i < j), dif | (i != j), dii | (i < upn), dij | (j < upm))) %= mod;
    return res;
}

inline void solve() {
    read(n, m);
    memset(f, -1, sizeof(f));
    ll mx = max(n, m), len = 0;
    while (mx) mx /= k, len++;
    for (int i = 1; i <= len; ++i) bn[i] = n % k, n /= k;
    for (int i = 1; i <= len; ++i) bm[i] = m % k, m /= k;
    printf("%lld\n", calc(len, 0, 0, 0, 0));
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    read(T, k);
    while (T--) solve();
    return 0;
}