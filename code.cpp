#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 1000005;

struct Node {
    int max_val;
    int lazy;
} tree[MAXN * 4];

void push_up(int node) {
    tree[node].max_val = max(tree[node * 2].max_val, tree[node * 2 + 1].max_val);
}

void push_down(int node) {
    if (tree[node].lazy != 0) {
        tree[node * 2].max_val += tree[node].lazy;
        tree[node * 2].lazy += tree[node].lazy;
        tree[node * 2 + 1].max_val += tree[node].lazy;
        tree[node * 2 + 1].lazy += tree[node].lazy;
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
    int mid = (start + end) / 2;
    if (l <= mid) update(node * 2, start, mid, l, r, val);
    if (r > mid) update(node * 2 + 1, mid + 1, end, l, r, val);
    push_up(node);
}

int query(int node, int start, int end, int l, int r) {
    if (l <= start && end <= r) {
        return tree[node].max_val;
    }
    push_down(node);
    int mid = (start + end) / 2;
    int res = 0;
    if (l <= mid) res = max(res, query(node * 2, start, mid, l, r));
    if (r > mid) res = max(res, query(node * 2 + 1, mid + 1, end, l, r));
    return res;
}

inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

int main() {
    int x = read();
    int k = read();
    int p = read();

    if (x <= 1) {
        for (int i = 0; i < p; ++i) {
            read(); read(); read();
            printf("T\n");
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
            printf("T\n");
            continue;
        }

        if (query(1, 1, n_segments, l, r) + n <= k) {
            update(1, 1, n_segments, l, r, n);
            printf("T\n");
        } else {
            printf("N\n");
        }
    }

    return 0;
}
