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

const int N = 1e5 + 10;

int n, m, s;

vector<PII> G[N];
int dis[N], vis[N];
struct node {
    int to, dis;
    bool operator < (const node &b) const {
        return b.dis < dis;
    }
};

void dijkstra(int s) {
    for (int i = 1; i <= n; ++i) dis[i] = 0x3f3f3f3f, vis[i] = 0;
    dis[s] = 0;
    priority_queue<node> q;
    q.push({s, 0});
    while (!q.empty()) {
        auto u = q.top().to;
        q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (auto [v, w] : G[u]) {
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                if (!vis[v]) q.push({v, dis[v]});
            }
        }
    }
}

inline void solve() {
    read(n, m, s);
    for (int i = 1; i <= m; ++i) {
        int u, v, w;
        read(u, v, w);
        G[u].emplace_back(v, w);
    }
    dijkstra(s);
    for (int i = 1; i <= n; ++i) printf("%d ", dis[i]);
    puts("");
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}