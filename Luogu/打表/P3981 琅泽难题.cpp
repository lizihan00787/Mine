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

const int mod = 20171111;

int a, p, d;
int ans, k, l, t;

inline void F(long long n) {
    if (n == 2) k = 1, l = 1; // k:F[n],l:F[n-1]
    else if (n % 2 == 0)
        F(n / 2), t = k * k + 2 * k * l, // 二次项公式
            l = k * k + l * l, k = t;    // 二次项公式
    else if (n % 2 == 1) F(n - 1), t = k + l, l = k, k = t; // 普通公式
    k %= mod, l %= mod;
}

inline void solve() {
    read(a, d, p);
    if (p & 1) {
        if (p == 3) {
            if (d > 3) printf("%lld\n", 1ll * (a == 3) + 1);
            else printf("%lld\n", 1ll * (a == 3));
        }
        else if (p == 5 || p == 7) {
            // 5的计算递推式为 F(n) = F(n - 2) + F(n - 4) + 1 其实可以使用矩阵（有点难构造）
            d -= 4, d /= 2; // 除去开始的4行没出现的和重复数量的一行
            if (p == 7) d --; // 7出现行数比5多两行
            if (d > 0) {
                if (d & 1) F(d + 2), ans += k - 1, ans %= mod;
                else F(d), ans += k, F(d + 1), ans += k - 1, ans %= mod;
            }
            ans += (a == 5 || a == 7);
            if (d <= 0) puts("0");
            else printf("%lld\n", ans);
        }
        else printf("%lld\n", 1ll * (a == p)); // 9木得
    }
    else printf("%lld\n", 1ll * (a == p));
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}