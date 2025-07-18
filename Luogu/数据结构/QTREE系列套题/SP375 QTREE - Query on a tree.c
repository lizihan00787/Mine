#include <stdio.h>
#include <string.h>

#define MAXN 100020
#define MAXE (MAXN << 1)
#define max(a, b) ((a) > (b) ? (a) : (b))

struct Edge {
    int u, v, w;
} e[MAXN << 1];

struct Node {
    int to, weight, next;
} G[MAXE];
int head[MAXN], idx;

void add(int u, int v, int w) {
    G[idx].to = v;
    G[idx].weight = w;
    G[idx].next = head[u];
    head[u] = idx++;
}

int a[MAXN];
int dep[MAXN], fa[MAXN], son[MAXN], siz[MAXN];
int tp[MAXN], dfx[MAXN], rk[MAXN], tot;

int t[MAXN << 2];
int n, T;

int read_int() {
    int x = 0, f = 1; char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}

// ----- Heavy-Light Decomposition -----
void dfs1(int u, int f) {
    siz[u] = 1;
    dep[u] = dep[f] + 1;
    fa[u] = f;
    for (int i = head[u]; i != -1; i = G[i].next) {
        int v = G[i].to;
        if (v == f) continue;
        a[v] = G[i].weight;
        dfs1(v, u);
        siz[u] += siz[v];
        if (siz[v] > siz[son[u]]) son[u] = v;
    }
}

void dfs2(int u, int t) {
    tp[u] = t;
    dfx[u] = ++tot;
    rk[tot] = u;
    if (son[u]) dfs2(son[u], t);
    for (int i = head[u]; i != -1; i = G[i].next) {
        int v = G[i].to;
        if (v == fa[u] || v == son[u]) continue;
        dfs2(v, v);
    }
}

// ----- Segment Tree -----
void pushup(int rt) {
    t[rt] = max(t[rt << 1], t[rt << 1 | 1]);
}

void build(int rt, int l, int r) {
    if (l == r) {
        t[rt] = a[rk[l]];
        return;
    }
    int mid = (l + r) >> 1;
    build(rt << 1, l, mid);
    build(rt << 1 | 1, mid + 1, r);
    pushup(rt);
}

void update(int rt, int l, int r, int k, int x) {
    if (l == r) {
        t[rt] = x;
        return;
    }
    int mid = (l + r) >> 1;
    if (k <= mid) update(rt << 1, l, mid, k, x);
    else update(rt << 1 | 1, mid + 1, r, k, x);
    pushup(rt);
}

int query(int rt, int l, int r, int L, int R) {
    if (L <= l && r <= R) return t[rt];
    int mid = (l + r) >> 1;
    int res = 0;
    if (L <= mid) res = max(res, query(rt << 1, l, mid, L, R));
    if (R > mid) res = max(res, query(rt << 1 | 1, mid + 1, r, L, R));
    return res;
}

// ----- Query -----
int que(int x, int y) {
    int res = 0;
    while (tp[x] != tp[y]) {
        if (dep[tp[x]] < dep[tp[y]]) {
            int tmp = x; x = y; y = tmp;
        }
        res = max(res, query(1, 1, n, dfx[tp[x]], dfx[x]));
        x = fa[tp[x]];
    }
    if (dep[x] < dep[y]) {
        int tmp = x; x = y; y = tmp;
    }
    if (dfx[y] + 1 <= dfx[x])
        res = max(res, query(1, 1, n, dfx[y] + 1, dfx[x]));
    return res;
}

void solve() {
    memset(head, -1, sizeof(head));
    memset(son, 0, sizeof(son));
    memset(t, 0, sizeof(t));
    idx = tot = 0;

    n = read_int();
    for (int i = 1; i < n; ++i) {
        e[i].u = read_int();
        e[i].v = read_int();
        e[i].w = read_int();
        int u = e[i].u, v = e[i].v, w = e[i].w;
        add(u, v, w);
        add(v, u, w);
    }

    dfs1(1, 0);
    dfs2(1, 1);
    build(1, 1, n);

    char op[10];
    while (scanf("%s", op), op[0] != 'D') {
        int x = read_int();
        int y = read_int();
        if (op[0] == 'Q') {
            printf("%d\n", que(x, y));
        } else {
            int u = e[x].u, v = e[x].v;
            if (fa[v] == u) update(1, 1, n, dfx[v], y);
            else update(1, 1, n, dfx[u], y);
        }
    }
}

int main() {
    T = read_int();
    while (T--) solve();
    return 0;
}
