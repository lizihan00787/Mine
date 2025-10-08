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

const int N = 5e5 + 10;

int n;
char s1[N], s2[N];
int a[N], b[N], cnt1, cnt2;

inline void solve() {
    read(n);
    scanf("%s", s1 + 1);
    scanf("%s", s2 + 1);
    for (int i = 1; i <= n; ++i) {
        if (s1[i] == '1') a[++cnt1] = i;
        if (s2[i] == '1') b[++cnt2] = i;
    }
    a[++cnt1] = b[++cnt2] = n + 1;
    int i = 1, j = 1;
    ll ans = 0;
    while (i <= cnt1 && j <= cnt2) {
        while (a[i] < b[j] && i < cnt1) i += 2, ans += abs(a[i - 1] - a[i - 2]);
        if ((i >= cnt1 || j >= cnt2) && (a[i] != b[j])) { puts("-1"); return; }
        ans += abs(a[i] - b[j]);
        j++; i++;
    }
    printf("%lld\n", ans);
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}