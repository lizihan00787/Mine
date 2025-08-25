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

int x, y;

inline void solve() {
    read(x);
    y = 4 * x - 1;
    int a, b;
    vector<int> ans;
    for (int i = 1; i * i <= abs(y); ++i) {
        if (y % i != 0) continue;
        if (i * i == y) a = b = i;
        else a = i, b = y / i;
        if ((b - a - 2) % 4 == 0) ans.emplace_back((b - a - 2) / 4);
        if (i * i == y) a = b = -i;
        else a = -i, b = -y / i;
        if ((b - a - 2) % 4 == 0) ans.emplace_back((b - a - 2) / 4);
    }
    sort(ans.begin(), ans.end());
    printf("%lld\n", ans.size());
    for (auto it : ans) printf("%lld ", it);
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}