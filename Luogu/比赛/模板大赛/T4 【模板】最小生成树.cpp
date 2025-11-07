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

const int N = 5e3 + 10, M = 2e5 + 10;

int n, m;

struct edge {
    int u, v, w;
    bool operator < (const edge &b) const {
        return w < b.w;
    }
} e[M];

int fa[N];
int find(int x) { return (x == fa[x]) ? x : fa[x] = find(fa[x]); }
void unionn(int a, int b) {
    int x = find(a), y = find(b);
    if (fa[y] != x) fa[y] = x;
}

int Kruskal() {
    int tot = 0;
    int w = 0;
    for (int i = 1; i <= m; ++i) {
        if (find(e[i].u) != find(e[i].v)) unionn(e[i].u, e[i].v), ++tot, w += e[i].w;
        if (tot == n - 1) return w;
    }
    if (tot != n - 1) return -1;
}

inline void solve() {
    read(n, m);
    for (int i = 1; i <= n; ++i) fa[i] = i;
    for (int i = 1; i <= m; ++i) read(e[i].u, e[i].v, e[i].w);
    sort(e + 1, e + m + 1);
    int ans = Kruskal();
    if (ans == -1) puts("orz");
    else printf("%d\n", ans);
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}