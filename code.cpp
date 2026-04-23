#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

const int MAXN = 1000005;

struct Node {
    int max_val;
    int lazy;
} tree[MAXN * 4];

inline void push_up(int node) {
    tree[node].max_val = max(tree[node << 1].max_val, tree[node << 1 | 1].max_val);
}

inline void push_down(int node) {
    if (tree[node].lazy != 0) {
        int lz = tree[node].lazy;
        tree[node << 1].max_val += lz;
        tree[node << 1].lazy += lz;
        tree[node << 1 | 1].max_val += lz;
        tree[node << 1 | 1].lazy += lz;
        tree[node].lazy = 0;
    }
}

void update(int node, int start, int end, int l, int r, int val) {
    if (l <= start && end <= r) {
        tree[node].max_val += val;
        tree[node].lazy += val;
        return;
    }
    push_down(node);
    int mid = (start + end) >> 1;
    if (l <= mid) update(node << 1, start, mid, l, r, val);
    if (r > mid) update(node << 1 | 1, mid + 1, end, l, r, val);
    push_up(node);
}

int query(int node, int start, int end, int l, int r) {
    if (l <= start && end <= r) {
        return tree[node].max_val;
    }
    push_down(node);
    int mid = (start + end) >> 1;
    int res = 0;
    if (l <= mid) res = max(res, query(node << 1, start, mid, l, r));
    if (r > mid) res = max(res, query(node << 1 | 1, mid + 1, end, l, r));
    return res;
}

char buf[1 << 20], *p1 = buf, *p2 = buf;
#define get_char() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2) ? EOF : *p1++)

inline int read() {
    int x = 0, f = 1;
    char ch = get_char();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        if (ch == EOF) return -1;
        ch = get_char();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = get_char();
    }
    return x * f;
}

inline void write_char(char c) {
    putchar(c);
}

int main() {
    int x = read();
    int k = read();
    int p = read();

    if (x == -1) return 0;

    if (x <= 1) {
        for (int i = 0; i < p; ++i) {
            read(); read(); read();
            write_char('T'); write_char('\n');
        }
        return 0;
    }

    int n_segments = x - 1;

    for (int i = 0; i < p; ++i) {
        int u = read();
        int v = read();
        int n = read();

        if (u > v) swap(u, v);

        // Segments are from u to v-1
        int l = u;
        int r = v - 1;

        if (l > r) {
            write_char('T'); write_char('\n');
            continue;
        }

        if (query(1, 1, n_segments, l, r) + n <= k) {
            update(1, 1, n_segments, l, r, n);
            write_char('T'); write_char('\n');
        } else {
            write_char('N'); write_char('\n');
        }
    }

    return 0;
}
