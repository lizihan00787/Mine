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

const int N = 6100, mod = 1e4 + 7;

int n, m;
int dp[110][N];
char s[110];
struct node {
    int ch[27];
    int fail;
    int flag;
} t[N];
int tmp = 0;

void insert(char *s) {
    int u = 0, n = strlen(s + 1);
    for (int i = 1; i <= n; ++i) {
        int p = s[i] - 'A';
        if (!t[u].ch[p]) t[u].ch[p] = ++tmp;
        u = t[u].ch[p];
    }
    t[u].flag = 1;
}

void build() {
    queue<int> q;
    for (int i = 0; i < 26; ++i) if (t[0].ch[i]) q.push(t[0].ch[i]);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = 0; i < 26; ++i) {
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

int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

inline void solve() {
    read(n, m);
    for (int i = 1; i <= n; ++i) scanf("%s", s + 1), insert(s);
    build();
    dp[0][0] = 1;
    for (int i = 0; i < m; ++i) for (int j = 0; j <= tmp; ++j) for (int k = 0; k < 26; ++k) 
        if (!t[t[j].ch[k]].flag) dp[i + 1][t[j].ch[k]] = (dp[i + 1][t[j].ch[k]] + dp[i][j]) % mod;
    int ans = qpow(26, m);
    for (int i = 0; i <= tmp; ++i) ans = (ans - dp[m][i] + mod) % mod;
    printf("%d\n", ans);
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}