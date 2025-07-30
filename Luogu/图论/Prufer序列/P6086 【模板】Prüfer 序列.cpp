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

const int N = 5e6 + 20;

int n, o;
int p[N], f[N], d[N]; // d为连向儿子的边数（可以类似理解为入度）
ll ans;

void TP() {
    for (int i = 1; i < n; ++i) read(f[i]), ++d[f[i]];
    for (int i = 1, j = 1; i <= n - 2; ++i, ++j) {
        while (d[j]) ++j; p[i] = f[j];
        while (i <= n - 2 && !--d[p[i]] && p[i] <= j) p[i + 1] = f[p[i]], ++i;
    }
    for (int i = 1; i <= n - 2; ++i) ans ^= 1ll * i * p[i];
}
void PT() {
    for (int i = 1; i <= n - 2; ++i) read(p[i]), ++d[p[i]]; p[n - 1] = n;
    for (int i = 1, j = 1; i < n; ++i, ++j) {
        while (d[j]) ++j; f[j] = p[i];
        while (i < n && !--d[p[i]] && p[i] < j) f[p[i]] = p[i + 1], ++i;
    }
    for (int i = 1; i < n; ++i) ans ^= 1ll * i * f[i];
}

inline void solve() {
    read(n, o);
    o == 1 ? TP() : PT();
    printf("%lld\n", ans);
}

signed main() {
    // freopen(".in","r",stdin);w
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0; 
}