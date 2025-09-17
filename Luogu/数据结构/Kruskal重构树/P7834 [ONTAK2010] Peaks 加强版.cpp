#include <bits/stdc++.h>
#define endl '\n'
#define int long long
#define mk(a, b) make_pair(a, b)
#define PII pair<int, int>
#define fi first
#define se second
using namespace std;
template <typename P>
void read(P &x) {
    P res = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch)) {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (isdigit(ch)) {
        res = (res << 3) + (res << 1) + (ch ^ 48);
        ch = getchar();
    }
    x = res * f;
}
template <typename PP, typename... Arc>
void read(PP &x, Arc &...y) { read(x), read(y...); }
template <class P>
void write(P x) {
    if (x > 9) write(x / 10);
    putchar(x % 10 + 48);
}

int T = 1;

const int N = 2e5 + 10, M = N * 16, K = 5e5 + 20;

struct node {
    int u, v, w;
    node() {}
    node(int u, int v, int w) : u(u), v(v), w(w) {}
    inline bool operator<(const node &b) const { return w < b.w; }
} e[K];
vector<int> g[N];
int n, m, q, dftot;
int fa[N], f[N][22], sum[M], L[N], R[N], bin[30], cnt;
int h[N], lim, b[N], val[N];

int ls[N], rs[N], root[N], num;

void mis(int u) {
    for (int i = 1; bin[i] <= n; ++i) f[u][i] = f[f[u][i - 1]][i - 1];
}
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void update(int last, int &now, int l, int r, int x) {
    sum[now = ++cnt] = sum[last] + 1;
    if (l == r) return;
    int mid = (l + r) >> 1;
    if (x <= mid)
        R[now] = R[last], update(L[last], L[now], l, mid, x);
    else
        L[now] = L[last], update(R[last], R[now], mid + 1, r, x);
}
int query(int a, int x, int k) {
    int l = 1, r = lim;
    for (int j = 18; ~j; --j)
        if (f[a][j] && val[f[a][j]] <= x && f[a][j]) a = f[a][j];
    int v = root[rs[a]], u = root[ls[a] - 1];
    if (sum[v] - sum[u] < k) return -1;
    while (l < r) {
        int tmp = sum[R[v]] - sum[R[u]], mid = (l + r) >> 1;
        if (tmp >= k)
            v = R[v], u = R[u], l = mid + 1;
        else
            v = L[v], u = L[u], r = mid, k -= tmp;
    }
    return b[r];
}
void dfs(int u) {
    mis(u), ls[u] = ++num;
    if (u <= n)
        update(root[num - 1], root[num], 1, lim, h[u]);
    else
        root[num] = root[num - 1];
    for (auto to : g[u]) dfs(to);
    rs[u] = num;
}

void solve() {
    read(n, m, q);
    bin[0] = 1;
    for (int i = 1; i <= 22; ++i) bin[i] = bin[i - 1] << 1;
    for (int i = 1; i <= 2 * n; ++i) fa[i] = i;
    for (int i = 1; i <= n; ++i) read(h[i]), b[i] = h[i];
    for (int i = 1, u, v, w; i <= m; ++i)
        read(u, v, w), e[i] = node(u, v, w);
    sort(b + 1, b + 1 + n);
    lim = unique(b + 1, b + 1 + n) - b - 1;
    for (int i = 1; i <= n; ++i) h[i] = lower_bound(b + 1, b + 1 + lim, h[i]) - b;
    sort(e + 1, e + 1 + m);
    dftot = n;
    int las = 0;
    for (int i = 1; i <= m; ++i) {
        int u = find(e[i].u), v = find(e[i].v);
        if (u != v) {
            val[++dftot] = e[i].w, fa[u] = fa[v] = dftot;
            g[dftot].push_back(u);  
            g[dftot].push_back(v);
            f[u][0] = f[v][0] = dftot;
            if (dftot - n == n - 1) break;
        }
    }
    for (int i = 1; i <= dftot; ++i)
        if (!ls[i] && find(i) == i) dfs(find(i));
    while (q--) {
        int u, x, k;
        read(u, x, k);
        u = (u ^ las) % n + 1, k = (k ^ las) % n + 1, x = x ^ las;
        cout << query(u, x, k) << endl;
    }
    return;
}

signed main() {
    // freopen("test.in","r",stdin);
    // freopen("mine.out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}
