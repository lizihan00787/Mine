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

const int N = 2e5 + 20;

int n, m, subn;
ll ans;
vector<int> G[N], E[N];

int dfn[N], low[N], st[N], tp = 0, dfc = 0, w[N], tot, siz[N];

void tanjan(int u) {
    w[st[++tp] = u] = -1;
    dfn[u] = low[u] = ++dfc;
    ++subn;
    for (auto v : G[u]) {
        if (!dfn[v]) {
            tanjan(v);
            low[u] = min(low[v], low[u]);
            if (low[v] >= dfn[u]) {
                E[++tot].emplace_back(u); E[u].emplace_back(tot);
                w[tot]++;
                do E[tot].emplace_back(st[tp]), w[tot]++;
                while(st[tp--] != v);
            }
        }
        else low[u] = min(low[u], dfn[v]);
    }
}


void dfs(int u, int fa) {
    siz[u] = u <= n;
    for (auto v : E[u]) {
        if (v == fa) continue;
        dfs(v, u);
        ans += 2ll * siz[v] * siz[u] * w[u];
        siz[u] += siz[v];
    }
    ans += 2ll * siz[u] * (subn - siz[u]) * w[u];
}

inline void solve() {
    read(n, m);
    tot = n;
    for (int i = 1; i <= m; ++i) {
        int x, y;
        read(x, y);
        G[x].emplace_back(y);
        G[y].emplace_back(x);
    }
    for (int i = 1; i <= n; ++i) {
        if (!dfn[i]) {
            subn = 0;
            tanjan(i);
            dfs(i, 0);
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