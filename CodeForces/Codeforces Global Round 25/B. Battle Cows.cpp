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

const int N = 1e5 + 10;

int n, k;
int a[N];

inline void solve() {
    read(n, k);
    for (int i = 1; i <= n; ++i) read(a[i]);
    int maxk = 1, ans = 0, sum = 0;
    swap(a[1], a[k]);
    for (int i = 2; i <= n; ++i) {
        if (a[i] < a[1]) sum++; 
        else break;
    }
    swap(a[1], a[k]);
    ans = max(ans, sum);

    a[0] = 0x3f3f3f3f;
    for (int i = 1; i < k; ++i) if (a[k] < a[i]) { maxk = i; break; }
    sum = 0;
    swap(a[maxk], a[k]);
    for (int i = maxk + 1; i <= n; ++i) {
        if (a[i] < a[maxk]) sum++;
        else break;
    }
    if (a[maxk - 1] < a[maxk]) sum++;
    swap(a[maxk], a[k]);
    ans = max(ans, sum);

    printf("%d\n", ans);
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    read(T);
    while (T--) solve();
    return 0;
}