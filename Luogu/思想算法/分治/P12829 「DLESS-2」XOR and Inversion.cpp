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

#define ull unsigned long long
#define uint unsigned int

const int N = (1<<20), D = 20;

int n, q, *b[D];
ull cnt[D][D][2];
uint p[N];

void calc(int d, int l, int r) {
    if (l == r) return;
    int mid = (l + r) >> 1;
    calc(d - 1, l, mid); calc(d - 1, mid + 1, r);
    for (int i = l; i <= mid; ++i)
        for (int j = 0; j < n; ++j)
            ++b[j][p[i] >> j];
    for (int i = mid + 1; i <= r; ++i)
        for (int j = 0; j < n; ++j)
            cnt[d][j][p[i] >> j & 1 ^ 1] += b[j][p[i] >> j ^ 1];
    for (int i = l; i <= mid; ++i)
        for (int j = 0; j < n; ++j)
            b[j][p[i] >> j] = 0;
}

inline void solve() {
    read(n, q);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cnt[i][j][0] = cnt[i][j][1] = 0;
    for (int i = 0; i < (1 << n); ++i) read(p[i]);
    calc(n - 1, 0, (1 << n) - 1);
    int a = 0, b = 0;
    while (q--) {
        int opt, x;
        ull res = 0;
        read(opt, x);
        if (opt == 1) b ^= x;
        else a ^= x;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                res += cnt[i][j][(a >> i & 1) ^ (b >> j & 1) ^ 1];
        printf("%llu\n", res);
    }
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    read(T);
    for (int i = 0, j = N; i < D; ++i, j >>= 1) b[i] = new int[j](); // 栈空间动态开数组
    while (T--) solve();
    for (int i = 0; i < D; ++i) delete[] b[i];
    return 0;
}