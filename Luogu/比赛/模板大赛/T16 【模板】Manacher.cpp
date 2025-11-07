#include <bits/stdc++.h>
#define endl '\n'
#define int long long
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

const int N = 3e7 + 1e6 + 10;

char s[N], a[N];
int d[N], tot = 0;

void manacher(char *ss, int k) {
    d[1] = 1;
    for (int i = 2, l, r = 1; i <= k; ++i) {
        if (i <= r) d[i] = min(d[r - i + l], r - i + 1);
        while (ss[i - d[i]] == ss[i + d[i]]) d[i]++;
        if (i + d[i] - 1 > r) l = i - d[i] + 1, r = i + d[i] - 1;
    }
}

inline void solve() {
    scanf("%s", s + 1);
    int n = strlen(s + 1);
    a[0] = '$';
    a[++tot] = '#';
    for (int i = 1; i <= n; ++i) a[++tot] = s[i], a[++tot] = '#';
    manacher(a, tot);
    int ans = 0;
    for (int i = 1; i <= tot; ++i) ans = max(ans, d[i]);
    cout << ans - 1 << endl;
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}