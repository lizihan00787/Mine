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

const int N = 1510, mod = 1e9 + 7;

struct node {
    int ch[10];
    int fail;
    int flag;
} t[N];
int tmp = 0;
int m;
char S[N], s[N];
int f[N][N], a[N];

void insert(char *s) {
    int u = 0, n = strlen(s + 1);
    for (int i = 1; i <= n; ++i) {
        int p = s[i] - '0';
        if (!t[u].ch[p]) t[u].ch[p] = ++tmp;
        u = t[u].ch[p];
    }
    t[u].flag = 1;
}

void build() {
    queue<int> q;
    for (int i = 0; i < 10; ++i) if (t[0].ch[i]) q.push(t[0].ch[i]);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = 0; i < 10; ++i) {
            int p = t[u].ch[i];
            if (!p) t[u].ch[i] = t[t[u].fail].ch[i];
            else {
                t[p].fail = t[t[u].fail].ch[i];
                t[p].flag |= t[t[p].fail].flag;
                q.push(p);
            }
        }
    }
}

int dfs(int pos, int p, bool op0, bool lim) {
    if (t[p].flag) return 0;
    if (!pos) return !op0;
    if (!lim && !op0 && ~f[pos][p]) return f[pos][p];
    int upp = lim ? a[pos] : 9;
    int res = 0;
    for (int i = 0; i <= upp; ++i) res = (res + dfs(pos - 1, (op0 && !i) ? 0 : t[p].ch[i], op0 && !i, lim && i == upp)) % mod;
    if (!lim && !op0) f[pos][p] = res;
    return res;
}

int calc() {
    memset(f, -1, sizeof(f));
    int len = strlen(S + 1);
    for (int i = 1; i <= len; ++i) a[len - i + 1] = S[i] - '0';
    return dfs(len, 0, 1, 1);
}

inline void solve() {
    scanf("%s", S + 1);
    read(m);
    while (m--) scanf("%s", s + 1), insert(s);
    build();
    printf("%d\n", calc());
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}