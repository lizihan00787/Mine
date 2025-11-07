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

const int N = 3e6 + 10;

int n, q;
char s[N];
struct node {
    int son[72];
    int tot;
} t[N];
int tmp = 0;

int zhuan(char c) {
    if (c >= 'a' && c <= 'z') return (int)(c - 'a');
    else if (c >= 'A' && c <= 'Z') return (int)(c - 'A' + 26);
    else if (c >= '0' && c <= '9') return (int)(c - '0' + 52);
}

void insert(char *s) {
    int u = 0, n = strlen(s + 1);
    for (int i = 1; i <= n; ++i) {
        int k = zhuan(s[i]);
        if (!t[u].son[k]) t[u].son[k] = ++tmp;
        u = t[u].son[k];
        t[u].tot++;
    }
}
int query(char *s) {
    int u = 0, n = strlen(s + 1);
    for (int i = 1; i <= n; ++i) {
        int k = zhuan(s[i]);
        if (!t[u].son[k]) return 0;
        u = t[u].son[k];
    }
    return t[u].tot;
}

inline void solve() {
    for (int i = 0; i <= tmp; ++i) for (int j = 0; j <= 70; ++j) t[i].son[j] = 0;
    for (int i = 0; i <= tmp; ++i) t[i].tot = 0;
    tmp = 0;
    read(n, q);
    for (int i = 1; i <= n; ++i) {
        scanf("%s", s + 1);
        insert(s);
    }
    for (int i = 1; i <= q; ++i) {
        scanf("%s", s + 1);
        cout << query(s) << endl;
    }
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    read(T);
    while (T--) solve();
    return 0;
}