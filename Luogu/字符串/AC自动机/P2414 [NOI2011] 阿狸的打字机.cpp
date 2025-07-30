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

const int N = 1e5 + 20;

int m;
int ans[N]; 

namespace AC_Auto {
    int tmp = 1, wordid = 0;
    struct node {
        int son[27], cson[27], fa;
        int fail;
    } tr[N];
    int wordpos[N];
    void insert(char *s) {
        int p = 1, len = strlen(s + 1);
        for (int i = 1; i <= len; ++i) {
            if(s[i] >= 'a' && s[i] <= 'z') {
                if(!tr[p].son[s[i] - 'a']) tr[p].son[s[i] - 'a'] = tr[p].cson[s[i] - 'a'] = ++tmp, tr[tmp].fa = p;
                p = tr[p].son[s[i] - 'a'];
            }
            else if(s[i] == 'P') wordpos[++wordid] = p; // 标记第 i 个字符串结束位置在哪
            else p = tr[p].fa;
        }
    }
    void Getfail() {
        queue<int> q;
        tr[1].fail = 1;
        for (int i = 0; i < 26; ++i) {
            if (tr[1].son[i]) q.push(tr[1].son[i]), tr[tr[1].son[i]].fail = 1;
            else tr[1].son[i] = 1;
        }
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i = 0; i < 26; ++i) {
                if (tr[u].son[i]) q.push(tr[u].son[i]), tr[tr[u].son[i]].fail = tr[tr[u].fail].son[i];
                else tr[u].son[i] = tr[tr[u].fail].son[i];
            }
        }
    }
}
using namespace AC_Auto;

namespace BIT {
    int t[N];
    #define low(x) (x & (-x))
    void add(int x, int val) { for (; x <= tmp; x += low(x)) t[x] += val; }
    int que(int x) { int res = 0; for(; x; x -=low(x)) res += t[x]; return res; }
    int query(int l, int r) { return que(r) - que(l - 1); }
}
using namespace BIT;

int dfn[N], low[N], tot = 0;

struct que {
    int model, context;
}q[N];
vector<int> ask[N], G[N];
char str[N];

void dfs(int u) {
    dfn[u] = ++tot;
    for (auto v : G[u]) dfs(v);
    low[u] = tot;
}

void work(int u) {
    add(dfn[u], 1);
    for (auto id : ask[u]) ans[id] = query(dfn[wordpos[q[id].model]], low[wordpos[q[id].model]]);
    for (int i = 0; i < 26; ++i) if (tr[u].cson[i]) work(tr[u].cson[i]);
    add(dfn[u], -1);
}

inline void solve() {
    scanf("%s", str + 1); read(m);
    insert(str);
    Getfail();
    for (int i = 2; i <= tmp; ++i) G[tr[i].fail].emplace_back(i);
    dfs(1);
    for (int i = 1; i <= m; ++i) {
        read(q[i].model, q[i].context);
        ask[wordpos[q[i].context]].emplace_back(i); // 存储每个文本串在trie上的同一结束位置有哪些询问
    }
    // for (int i = 0; i <= tmp; ++i) printf("%d ", tr[i].fail);
    work(1);
    for (int i = 1; i <= m; ++i) printf("%d\n", ans[i]);
}

signed main() {
    // freopen("P2414_1.in","r",stdin);
    // freopen("my.out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}