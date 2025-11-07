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

const int N = 11;

const int dx[4] = {0, -1, 0, 1};
const int dy[4] = {-1, 0, 1, 0};

int n, m, d, maxm, ans = -0x3f3f3f3f;
int v[N], val[(1 << N)];
int f[N][N][(1 << N)];
char s[N][N];
int ax[12], ay[12];
int vis[12][12][(1 << 12)];

struct node {
    int x, y, s;
    node (int _x = 0, int _y = 0, int _s = 0) { x = _x, y = _y, s = _s; }
};

inline int solve(int mx, int my, int nx, int ny, int ms) {
    int ns = ms;
    for (int i = 1; i <= d; ++i) 
        if (((mx == ax[i] && nx < ax[i]) || (mx < ax[i] && nx == ax[i])) && ny > ay[i]) ns ^= (1 << (i - 1));
    return ns;
}

void SPFA(int sx, int sy) {
    queue<node> q;
    q.push(node(sx, sy, 0));
    memset(f, 0x3f, sizeof(f));
    f[sx][sy][0] = 0;
    while (!q.empty()) {
        auto tmp = q.front();
        q.pop();
        int X = tmp.x, Y = tmp.y, S = tmp.s;
        vis[X][Y][S] = 0;
        for (int i = 0; i < 4; ++i) {
            int nx = X + dx[i], ny = Y + dy[i], ns = S;
            if (nx < 1 || nx > n || ny < 1 || ny > m || s[nx][ny] == '#' || (s[nx][ny] >= '1' && s[nx][ny] <= '9')) continue;
            if (i & 1) ns = solve(X, Y, nx, ny, S);
            if (f[X][Y][S] < f[nx][ny][ns]) {
                f[nx][ny][ns] = f[X][Y][S] + 1;
                if (!vis[nx][ny][ns]) q.push(node(nx, ny, ns)), vis[nx][ny][ns] = 1;
            }
        }
    }
    for (int i = 0; i < maxm; ++i) ans = max(ans, val[i] - f[sx][sy][i]);
}

inline void solve() {
    read(n, m, d);
    maxm = 1 << d;
    for (int i = 1; i <= d; ++i) read(v[i]);
    for (int i = 0; i < maxm; ++i)
        for (int j = 1; j <= d; ++j) if (i & (1 << (j - 1))) val[i] += v[j];
    for (int i = 1; i <= n; ++i) scanf("%s", s[i] + 1);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (s[i][j] >= '1' && s[i][j] <= '9') {
                int u = s[i][j] - '0';
                ax[u] = i, ay[u] = j;
            }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) if (s[i][j] == '0') SPFA(i, j);
    printf("%d\n", ans);
}

signed main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // read(T);
    while (T--) solve();
    return 0;
}