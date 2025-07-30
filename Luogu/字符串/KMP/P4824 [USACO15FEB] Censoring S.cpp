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

const int N = 1e6 + 20;

char s[N], t[N];
int n, m;
int nxt[N], f[N], st[N], tp = 0;

inline void solve() {
    scanf("%s", s + 1);
    scanf("%s", t + 1);
    n = strlen(s + 1);
    m = strlen(t + 1);
    for (int i = 2, j = 0; i <= m; ++i) {
        while (j && t[i] != t[j + 1]) j = nxt[j];
        if (t[i] == t[j + 1]) j++;
        nxt[i] = j;
    }
    for (int i = 1, j = 0; i <= n; ++i) {
        while (j && s[i] != t[j + 1]) j = nxt[j];
        if (s[i] == t[j + 1]) j++;
        f[i] = j;
        st[++tp] = i;
        if (j == m) {
            tp -= m;
            j = f[st[tp]];
        }
    }
    for (int i = 1; i <= tp; ++i) printf("%c", s[st[i]]);
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}