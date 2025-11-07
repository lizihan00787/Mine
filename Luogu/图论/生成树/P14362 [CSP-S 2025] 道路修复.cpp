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

const int N = 1e4 + 10, M = 1e6 + 10;

int n, m, k;
int w[N], c[11][N], fa[N + 10];
struct edge {
    int u, v, w;
    bool operator < (const edge &b) const {
        return w < b.w;
    }
} e[M * 2];
int tot = 0;
bool vis[N];

int find(int x) { return (fa[x] == x) ? x : fa[x] = find(fa[x]); }
void unionn(int a, int b) { fa[find(a)] = find(b); }

inline void solve() {
    read(n, m, k);
    for (int i = 1; i <= n; ++i) fa[i] = i;
    for (int i = 1; i <= m; ++i) read(e[i].u, e[i].v, e[i].w);
    sort(e + 1, e + m + 1);
    for (int i = 1; i <= m; ++i) {
        int u = e[i].u, v = e[i].v;
        if (find(u) != find(v)) {
            unionn(u, v);
            e[++tot] = e[i];
            if (tot == n - 1) break;
        }
    }
    for (int i = 1; i <= k; ++i) {
        read(w[i]);
        for (int j = 1; j <= n; ++j) {
            read(c[i][j]);
            e[++tot] = {i + n, j, c[i][j]};
        }
    }
    sort(e + 1, e + tot + 1);
    ll ans = 0x3f3f3f3f3f3f3f3f;
    for (int s = 0; s < (1 << k); ++s) {
        ll ww = 0;
        int num = 0;
        for (int i = 1; i <= k; ++i) {
            if ((s >> (i - 1)) & 1) {
                vis[i] = 1;
                num++;
                ww += w[i];
            }
            else vis[i] = 0;
        }
        for (int i = 1; i <= n + k; ++i) fa[i] = i;
        int nd = n + num - 1;
        for (int i = 1; i <= tot; ++i) {
            int u = e[i].u, v = e[i].v;
            if (!vis[u - n] && u > n) continue;
            if (find(u) != find(v)) {
                unionn(u, v);
                ww += e[i].w;
                if ((--nd) == 0) break;
            }
        }
        ans = min(ans, ww);
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