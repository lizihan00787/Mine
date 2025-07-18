#include <bits/stdc++.h>
#define endl '\n'
#define int long long
#define PII pair<int, int>
#define mk(a, b) make_pair(a, b)
using namespace std;

const int mod = 1e9 + 7;

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
        res %= (mod - 1);
        ch = getchar();
    }
    x = res * f;
}
template <typename Ty, typename... Args>
inline void read(Ty &x, Args &...args) { read(x); read(args...); }
int T = 1;


int n;

struct martix {
    int mat[2][2];
    martix() { memset(mat, 0, sizeof(mat)); }
    martix operator * (const martix &b) const {
        martix c;
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 2; ++j)
                for(int k = 0; k < 2; ++k)
                    c.mat[i][j] = (c.mat[i][j] + mat[i][k] * b.mat[k][j]) %mod;
        return c;
    }
} p1,p2;

martix qpow(martix a, martix one, int b) {
    martix res = one;
    while (b) {
        if (b & 1) res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}

inline void solve() {
    read(n);
    int a[2][2] = {{1, 0}, {0, 1}};
    memcpy(p1.mat, a, sizeof(a));
    int b[2][2] = {{2, 1}, {1, 0}};
    memcpy(p2.mat, b, sizeof(b));
    printf("%lld\n", qpow(p2, p1, n - 1).mat[0][0]);
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}