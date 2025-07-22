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

const int N = 5e3 + 20;

int n;
ll box[N], f[N], g[N], depmax;
ll ans;
vector<int> G[N];

void dfs(int u, int fa, int dep) {
    depmax = max(depmax, 1ll * dep);
    box[dep]++;
    for (auto v : G[u]) {
        if (v == fa) continue;
        dfs(v, u, dep + 1);
    }
}

inline void solve() {
    read(n);
    for (int i = 1; i < n; ++i) {
        int x, y;
        read(x), read(y);
        G[x].emplace_back(y);
        G[y].emplace_back(x);
    }
    for (int i = 1; i <= n; ++i) {
        memset(f, 0, sizeof(box));
        memset(g, 0, sizeof(g));
        for (auto j : G[i]) {
            depmax = 0;
            memset(box, 0, sizeof(box));
            dfs(j, i, 1);
            for (int k = 1; k <= depmax; ++k) {
                ans += f[k] * box[k];
                f[k] += g[k] * box[k];
                g[k] += box[k];
            }
        }
    }
    printf("%lld\n", ans);
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}