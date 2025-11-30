#ifndef FENWICK_ROW_H
#define FENWICK_ROW_H

#include <vector>
using namespace std;

class FenwickRow {
private:
    int n;
    vector<int> bit;
    vector<bool> seats;

    void update(int idx, int val) {
        idx++; // 1-based indexing
        while (idx <= n) {
            bit[idx] += val;
            idx += idx & -idx;
        }
    }

    int query(int idx) {
        idx++; // 1-based indexing
        int sum = 0;
        while (idx > 0) {
            sum += bit[idx];
            idx -= idx & -idx;
        }
        return sum;
    }

public:
    FenwickRow(int size) : n(size) {
        seats.assign(n, true);
        bit.assign(n + 1, 0);
        // Initialize with all 1s (all seats free)
        for (int i = 0; i < n; i++) {
            update(i, 1);
        }
    }

    // Range update: O(K * log N) where K is range size
    // BIT doesn't support efficient range updates for this specific problem easily
    void reserveRange(int start, int end) {
        for (int i = start; i <= end && i < n; i++) {
            if (seats[i]) {
                seats[i] = false;
                update(i, -1); // Decrease count of free seats
            }
        }
    }

    // Range query: O(log N)
    int queryFree(int l, int r) {
        if (l > r) return 0;
        return query(r) - query(l - 1);
    }
};

#endif
