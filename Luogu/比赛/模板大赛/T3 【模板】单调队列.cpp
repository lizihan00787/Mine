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

const int N = 1e6 + 10;

int n, k;
int a[N];
int q1[N], q2[N];

inline void solve() {
    read(n, k);
    for (int i = 1; i <= n; ++i) read(a[i]);
    int l = 1, r = 0;
    for (int i = 1; i <= n; ++i) {
        while (l <= r && i - q1[l] >= k) l++;
        while (l <= r && a[q1[r]] > a[i]) r--;
        q1[++r] = i;
        if (i >= k) printf("%d ", a[q1[l]]);
    }
    puts("");
    l = 1, r = 0;
    for (int i = 1; i <= n; ++i) {
        while (l <= r && i - q1[l] >= k) l++;
        while (l <= r && a[q1[r]] < a[i]) r--;
        q1[++r] = i;
        if (i >= k) printf("%d ", a[q1[l]]);
    }
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}