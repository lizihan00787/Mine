#include <bits/stdc++.h>
#define endl '\n'
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

const int N = 1e6 + 20;

int n, m;
int p[N], s[2][N], fail[N], L[N], R[N], pre[N], nxt[N];
vector<int> ans;

inline void solve() {
    read(n, m);
    for (int i = 1; i <= n; ++i) read(p[i]), s[0][p[i]] = i;
    for (int i = 1; i <= m; ++i) read(s[1][i]);
    for (int i = 1; i <= n; ++i) pre[i] = p[s[0][i] - 1], nxt[i] = p[s[0][i] + 1];
    for (int i = n; i >= 1; --i) L[i] = pre[i], R[i] = nxt[i], pre[nxt[i]] = pre[i], nxt[pre[i]] = nxt[i]; // 找到i的前缀中i的前驱和后继的位置（用双向链表）
    auto check = [&](int id, int i, int j) {
        int res = 1, Lm = L[j], Rm = R[j];
        if (Lm) res &= (s[id][i - (j - Lm)] < s[id][i]);
        if (Rm) res &= (s[id][i - (j - Rm)] > s[id][i]);
        return res;
    };
    for (int i = 2, j = 0; i <= n; ++i) {
        while (j && !check(0, i, j + 1)) j = fail[j];
        if (check(0, i, j + 1)) ++j;
        fail[i] = j;
    }
    for (int i = 1, j = 0; i <= m; ++i) {
        while (j && !check(1, i, j + 1)) j = fail[j];
        if (check(1, i, j + 1)) ++j;
        if (j == n) ans.emplace_back(i - n + 1), j = fail[j];
    }
    printf("%d\n", (int)(ans.size()));
    for (auto it : ans) printf("%d ", it);
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    solve();
    return 0;
}