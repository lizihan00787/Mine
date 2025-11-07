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

const int N = 1e6 + 10;

char s1[N], s2[N];
int nxt[N], n, m;

inline void solve() {
    scanf("%s", s1 + 1);
    n = strlen(s1 + 1);
    scanf("%s", s2 + 1);
    m = strlen(s2 + 1);
    int j = 0;
    for (int i = 2; i <= n; ++i) {
        while (j && s2[i] != s2[j + 1]) j = nxt[j];
        if (s2[j + 1] == s2[i]) ++j;
        nxt[i] = j;
    }
    j = 0;
    for (int i = 1; i <= n; ++i) {
        while (j && s1[i] != s2[j + 1]) j = nxt[j];
        if (s2[j + 1] == s1[i]) ++j;
        if (j == m) printf("%d\n", i - m + 1), j = nxt[j];
    }
    for (int i = 1; i <= m; ++i) printf("%d ", nxt[i]);
    puts("");
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}