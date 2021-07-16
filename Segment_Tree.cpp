#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pii> vpii;
typedef vector<vi> vvi;
typedef complex<double> cd;
typedef vector<cd> vcd;
#define endl '\n'
#define rp(x, i, j) for (int x = (i); x < (j); ++x)
#define rpr(x, i, j) for (int x = (j) - 1; x >= i; --x)
#define rpe(e, arr) for (auto& e : arr)
#define all(x) begin(x), end(x)
#define FASTIO cin.tie(nullptr)->sync_with_stdio(false)
int INF = 1e9;
ll LINF = 1e18;
int dy[]{0, -1, 0, 1};
int dx[]{-1, 0, 1, 0};

struct Seg {
    vector<int> t;
    int n;
    Seg(int n) : n(n) {
        t.resize(n << 1);
    }
    void build() {
        rpr(i, 1, n)
            t[i] = t[i << 1] + t[i << 1 | 1];
    }
    void modify(int p, int value) {
        for (t[p += n] = value, p >>= 1; p > 0; p >>= 1)
            t[p] = t[p << 1] + t[p << 1 | 1];
    }
    int query(int l, int r) {
        int ans = 0;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) ans += t[l++];
            if (r & 1) ans += t[--r];
        }
        return ans;
    }
};

struct SegLazy {
    vector<int> t, d;
    int n, h;
    Seg(int n) : n(n) {
        h = 0;
        while (1 << h < n)
            ++h;
        t.resize(n << 1);
        d.resize(n);
    }
    void build() {
        rpr(i, 1, n)
            t[i] = t[i << 1] + t[i << 1 | 1];
    }
    void apply(int p, int value, int k) {
        t[p] += value * k;
        if (p < n) d[p] += value;
    }
    void build(int p) {
        for (p += n, p >>= 1; p > 0; p >>= 1)
            if (d[p] == 0)
                t[p] = t[p << 1] + t[p << 1 | 1];
    }
    void push(int p) {
        int s = h, k = 1 << (h - 1);
        for (p += n; s > 0; --s, k >>= 1) {
            int i = p >> s;
            if (d[i] != 0) {
                apply(i << 1, d[i], k);
                apply(i << 1 | 1, d[i], k);
                d[i] = 0;
            }
        }
    }
    void modify(int l, int r, int value) {
        if (value == 0) return;
        push(l);
        push(r - 1);
        int l0 = l, r0 = r, k = 1;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1, k <<= 1) {
            if (l & 1) apply(l++, value, k);
            if (r & 1) apply(--r, value, k);
        }
        build(l0);
        build(r0 - 1);
    }
    int query(int l, int r) {
        int res = 0;
        push(l);
        push(r - 1);
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res += t[l++];
            if (r & 1) res += t[--r];
        }
        return res;
    }
};
