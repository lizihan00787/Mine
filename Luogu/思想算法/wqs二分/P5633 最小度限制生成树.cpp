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

const int N = 5e5 + 20, M = 5e5 + 20;

int n, m, s, k, cntcol;
struct edge {
    int u, v, w;
    int col;
    bool operator < (const edge &b) const {
        if (w != b.w) return w < b.w;
        return col > b.col;
    }
} cur[M];
vector<edge> st[2];

int fa[N];
int find(int x) {
    if (fa[x] == x) return x;
    return fa[x] = find(fa[x]);
}
void unionn(int u, int v) {
    int a = find(u), b = find(v);
    if (a != b) fa[a] = b;
}

ll Kruskal(void) {
    for (int i = 1; i <= n; ++i) fa[i] = i;
    int x = 0, y = 0, cnte = 0;
    for (; x < st[0].size() && y < st[1].size(); ) {
        if (st[0][x] < st[1][y]) cur[++cnte] = st[0][x++];
        else cur[++cnte] = st[1][y++];
    }
    for (; x < st[0].size(); x++) cur[++cnte] = st[0][x];
    for (; y < st[1].size(); y++) cur[++cnte] = st[1][y];
    int cnt = 0; 
    ll ans = 0;
    cntcol = 0;
    for (int i = 1; i <= m; ++i) {
        if (find(cur[i].u) == find(cur[i].v)) continue;
        unionn(cur[i].u, cur[i].v);
        ans += cur[i].w; cntcol += cur[i].col; cnt++;
        if (cnt == n - 1) return ans;
    }
} 

inline void solve() {
    read(n, m, s, k);
    for (int i = 1; i <= m; ++i) {
        int u, v, w;
        read(u, v, w);  
        edge tmp = {u, v, w};
        if (u == s || v == s) tmp.col = 1, st[0].emplace_back(tmp);
        else st[1].emplace_back(tmp);
    }
    sort(st[0].begin(), st[0].end()); sort(st[1].begin(), st[1].end());
    int l = -1e9, r = 1e9;
    auto Search = [&](int x) {
        for (auto &it : st[0]) it.w += x;
        Kruskal();
        for (auto &it : st[0]) it.w -= x;
    };
    Search(l);
    if (cntcol < k) puts("Impossible"), exit(0);
    Search(r);
    if (cntcol > k) puts("Impossible"), exit(0);
    while (l < r) {
        int mid = (l + r + 1) >> 1;
        Search(mid);
        if (cntcol >= k)  l = mid;
        else r = mid - 1;
    }
    for (auto &it : st[0]) it.w += r;
    printf("%lld\n", Kruskal() - r * k);
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}