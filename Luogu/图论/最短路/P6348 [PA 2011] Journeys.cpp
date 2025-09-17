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

const int N = 5e5 + 10, M = 4e6 + 2e5 + 10;

int n, m, p;
vector<PII> G[M];
int num[N], dis[M];
void dijkstra(int s) {
    memset(dis, 0x3f, sizeof(dis));
    deque<int> q;
    dis[s] = 0;
    q.emplace_back(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop_front();
        for (auto [v, w] : G[u]) {
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                if (w) q.emplace_back(v);
                else q.emplace_front(v);
            }
        }
    }
    for (int i = 1; i <= n; ++i) printf("%d\n", dis[i]);
}

int tot = 0;
#define mid ((l + r) >> 1)
struct node {
    int ls, rs;
} t[M];
void build(int &rt1, int &rt2, int l, int r) {
    if (l == r) return (void)(rt1 = l, rt2 = l);
    if (!rt1) rt1 = ++tot;
    if (!rt2) rt2 = ++tot;
    build(t[rt1].ls, t[rt2].ls, l, mid); G[t[rt1].ls].emplace_back(mk(rt1, 0)), G[rt2].emplace_back(mk(t[rt2].ls, 0));
    build(t[rt1].rs, t[rt2].rs, mid + 1, r); G[t[rt1].rs].emplace_back(mk(rt1, 0)), G[rt2].emplace_back(mk(t[rt2].rs, 0));
}
void connect(int rt, int l, int r, int L, int R, int x, int flag) {
    if (L <= l && r <= R) {
        if (flag) G[x].emplace_back(mk(rt, 0));
        else G[rt].emplace_back(mk(x, 0));
        return;
    }
    if (L <= mid) connect(t[rt].ls, l, mid, L, R, x, flag);
    if (R > mid) connect(t[rt].rs, mid + 1, r, L, R, x, flag);
}

inline void solve() {
    read(n, m, p);
    tot = n;
    int root1 = 0, root2 = 0;
    build(root1, root2, 1, n);
    for (int i = 1; i <= m; ++i) {
        int a, b, c, d, x = ++tot, y = ++tot;
        read(a, b, c, d);
        G[x].emplace_back(mk(y, 1));
        connect(root1, 1, n, a, b, x, 0);
        connect(root2, 1, n, c, d, y, 1);
        x = ++tot, y = ++tot;
        G[x].emplace_back(mk(y, 1));
        connect(root1, 1, n, c, d, x, 0);
        connect(root2, 1, n, a, b, y, 1);
    }
    dijkstra(p);
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}