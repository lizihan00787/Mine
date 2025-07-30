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

const int N = 1e5 + 20, M = 2e6 + 20;

int n, q;
vector<int> G[M];
int dfx[M], siz[M], dep[M], son[M], tp[M], fa[M], tot = 0;

namespace AC_Auto{
    int tmp = 1;
    struct trie {
        int son[27];
        int fail;
    } tr[M];
    int End[N];
    void insert(char *s, int id) {
        int p = 1, len = strlen(s + 1);
        for (int i = 1; i <= len; ++i) {
            int v = s[i] - 'a';
            if (!tr[p].son[v]) tr[p].son[v] = ++tmp;
            p = tr[p].son[v];
        }
        End[id] = p;
    }
    void Getfail() {
        queue<int> q;
        for (int i = 0; i < 26; ++i) tr[0].son[i] = 1;
        q.push(1); tr[1].fail = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i = 0; i < 26; ++i) {
                if (tr[u].son[i]) tr[tr[u].son[i]].fail = tr[tr[u].fail].son[i], q.push(tr[u].son[i]);
                else tr[u].son[i] = tr[tr[u].fail].son[i];
            }
        }
    }
}
using namespace AC_Auto;

namespace BT{
    void dfs1(int u, int f) {
        siz[u] = 1; dep[u] = dep[f] + 1; fa[u] = f;
        for (auto v : G[u]) {
            if (v == f) continue;
            dfs1(v, u);
            siz[u] += siz[v];
            if (siz[v] > siz[son[u]]) son[u] = v;
        }
    }
    void dfs2(int u, int t) {
        tp[u] = t; dfx[u] = ++tot;
        if (son[u]) dfs2(son[u], t);
        for (auto v : G[u]) {
            if (v == fa[u] || v == son[u]) continue;
            dfs2(v, v);
        }
    }
    int lca(int x, int y) {
        while (tp[x] != tp[y]) {
            if (dep[tp[x]] < dep[tp[y]]) swap(x, y);
            x = fa[tp[x]];
        }
        return dep[x] < dep[y] ? x : y;
    }
}
using namespace BT;

namespace BIT{
    #define low(x) (x & (-x))
    int t[M];
    void add(int k, int x) { for(; k <= tmp; k += low(k)) t[k] += x; }
    int que(int x) { int res = 0; for(; x; x -= low(x)) res += t[x]; return res; }
}
using namespace BIT;

bool cmp(int x, int y) { return dfx[x] < dfx[y]; }

char s[M];
int seq[M];

inline void solve() {
    read(n);
    for (int i = 1; i <= n; ++i) scanf("%s", s + 1), insert(s, i);
    Getfail();
    for (int i = 2; i <= tmp; ++i) G[tr[i].fail].emplace_back(i);
    dfs1(1, 0); dfs2(1, 1);
    read(q);
    while (q--) {
        int opt;
        read(opt);
        if (opt == 1) {
            scanf("%s", s + 1);
            int p = 1, len = strlen(s + 1);
            for (int i = 1; i <= len; ++i) {
                int v = s[i] - 'a';
                p = tr[p].son[v];
                seq[i] = p;
            }
            sort(seq + 1, seq + len + 1, cmp);
            for (int i = 1; i <= len; ++i) add(dfx[seq[i]], 1);
            for (int i = 1; i < len; ++i) add(dfx[lca(seq[i], seq[i + 1])], -1);
        }
        else {
            int x;
            read(x);
            int p = End[x];
            printf("%d\n", que(dfx[p] + siz[p] - 1) - que(dfx[p] - 1));
        }
    }
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}