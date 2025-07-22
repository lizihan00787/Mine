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

const int N = 5e5 + 20;

int n, q, rt;
int dfx[N], D[N], U[N], top[N], f[N][21], son[N], dep[N], h[N], tot = 0;
int Log[N];
vector<int> G[N];

void dfs1(int u) {
    for (int i = 1; i <= 19; ++i) f[u][i] = f[f[u][i - 1]][i - 1];
    for (auto v : G[u]) {
        dep[v] = h[v] = dep[u] + 1;
        dfs1(v);
        h[u] = max(h[v], h[u]);
        if (h[v] > h[son[u]]) son[u] = v;
    }
}
void dfs2(int u, int t, int p) {
    dfx[u] = ++tot; top[u] = t;
    D[tot] = u; U[tot] = p;
    if (son[u]) dfs2(son[u], t, f[p][0]);
    for (auto v : G[u]) {
        if (v == son[u]) continue;
        dfs2(v, v, v);
    }
}
inline int ask(int x, int k) {
    if (!k) return x;
    x = f[x][Log[k]], k -= (1 << Log[k]);
    k -= dep[x] - dep[top[x]]; x = top[x];
    if (k >= 0) return U[dfx[x] + k];
    return D[dfx[x] - k];
}

unsigned int s;
inline unsigned int get() {
	s ^= s << 13;
	s ^= s >> 17;
	s ^= s << 5;
	return s; 
}

inline void solve() {
    read(n, q, s);
    Log[0] = -1;
    for (int i = 1; i <= n; ++i)  Log[i] = Log[i >> 1] + 1;
    rt = 1;
    for (int i = 1; i <= n; ++i) {
        read(f[i][0]);
        if (!f[i][0]) rt = i;
        else G[f[i][0]].push_back(i);
    }
    dep[rt] = 1;
    dfs1(rt);
    dfs2(rt, rt, rt);
    ll ans = 0, las = 0;
    for (int i = 1; i <= q; ++i) {
        int x = (get() ^ las) % n + 1, k = (get() ^ las) % dep[x];
        las = ask(x, k);
        ans ^= (ll)i * las;
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