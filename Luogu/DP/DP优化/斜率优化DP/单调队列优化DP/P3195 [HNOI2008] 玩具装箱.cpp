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

const int N = 5e4 + 20;

int n, L;
double sum[N], f[N];
int head, tail, q[N];

inline void solve() {
    read(n, L);
    for (int i = 1; i <= n; ++i) scanf("%lf", &sum[i]), sum[i] += sum[i - 1];
    q[head = tail = 1] = 0;
    auto a = [&](int x) { return sum[x] + x; };
    auto b = [&](int x) { return a(x) + L + 1; };
    auto X = [&](int x) { return b(x); };
    auto Y = [&](int x) { return f[x] + b(x) * b(x); };
    auto Fk = [&](int i, int j) { return (Y(j) - Y(i)) / (X(j) - X(i)); };
    for (int i = 1; i <= n; ++i) {
        while (head < tail && Fk(q[head], q[head + 1]) < 2 * a(i)) head++;
        f[i] = f[q[head]] + (a(i) - b(q[head])) * (a(i) - b(q[head]));
        while (head < tail && Fk(i, q[tail]) < Fk(q[tail], q[tail - 1])) tail--;
        q[++tail] = i;
    }
    printf("%lld\n", (ll)f[n]);
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}