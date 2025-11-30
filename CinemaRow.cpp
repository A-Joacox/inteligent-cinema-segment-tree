#include "CinemaRow.h"
#include <cmath>

// Implementación de SeatNode
SeatNode::SeatNode() : total_free(0), max_consecutive(0), 
             prefix_free(0), suffix_free(0), length(0), lazy(0) {}

SeatNode::SeatNode(bool is_free, int len) {
    length = len;
    lazy = 0;
    if (is_free) {
        total_free = prefix_free = suffix_free = max_consecutive = len;
    } else {
        total_free = prefix_free = suffix_free = max_consecutive = 0;
    }
}

// Implementación de CinemaRow
SeatNode CinemaRow::merge(const SeatNode& left, const SeatNode& right) {
    SeatNode result;
    result.length = left.length + right.length;
    result.total_free = left.total_free + right.total_free;
    result.lazy = 0;
    
    result.prefix_free = left.prefix_free;
    if (left.prefix_free == left.length) {
        result.prefix_free += right.prefix_free;
    }
    
    result.suffix_free = right.suffix_free;
    if (right.suffix_free == right.length) {
        result.suffix_free += left.suffix_free;
    }
    
    result.max_consecutive = max({
        left.max_consecutive,
        right.max_consecutive,
        left.suffix_free + right.prefix_free
    });
    
    return result;
}

void CinemaRow::push(int node) {
    if (tree[node].lazy != 0) {
        bool set_free = (tree[node].lazy == 1);
        
        tree[2*node].lazy = tree[node].lazy;
        tree[2*node].total_free = set_free ? tree[2*node].length : 0;
        tree[2*node].max_consecutive = set_free ? tree[2*node].length : 0;
        tree[2*node].prefix_free = set_free ? tree[2*node].length : 0;
        tree[2*node].suffix_free = set_free ? tree[2*node].length : 0;
        
        tree[2*node+1].lazy = tree[node].lazy;
        tree[2*node+1].total_free = set_free ? tree[2*node+1].length : 0;
        tree[2*node+1].max_consecutive = set_free ? tree[2*node+1].length : 0;
        tree[2*node+1].prefix_free = set_free ? tree[2*node+1].length : 0;
        tree[2*node+1].suffix_free = set_free ? tree[2*node+1].length : 0;
        
        tree[node].lazy = 0;
    }
}

void CinemaRow::build(int node, int start, int end) {
    if (start == end) {
        tree[node] = SeatNode(seats[start], 1);
    } else {
        int mid = (start + end) / 2;
        build(2*node, start, mid);
        build(2*node+1, mid+1, end);
        tree[node] = merge(tree[2*node], tree[2*node+1]);
    }
}

void CinemaRow::updateRange(int node, int start, int end, int l, int r, bool set_free) {
    if (l > end || r < start) return;
    
    if (l <= start && end <= r) {
        tree[node].lazy = set_free ? 1 : 2;
        tree[node].total_free = set_free ? tree[node].length : 0;
        tree[node].max_consecutive = set_free ? tree[node].length : 0;
        tree[node].prefix_free = set_free ? tree[node].length : 0;
        tree[node].suffix_free = set_free ? tree[node].length : 0;
        return;
    }
    
    push(node);
    
    int mid = (start + end) / 2;
    updateRange(2*node, start, mid, l, r, set_free);
    updateRange(2*node+1, mid+1, end, l, r, set_free);
    
    tree[node] = merge(tree[2*node], tree[2*node+1]);
}

SeatNode CinemaRow::query(int node, int start, int end, int l, int r) {
    if (r < start || end < l) return SeatNode();
    
    if (l <= start && end <= r) return tree[node];
    
    push(node);
    
    int mid = (start + end) / 2;
    if (r <= mid) return query(2*node, start, mid, l, r);
    if (l > mid) return query(2*node+1, mid+1, end, l, r);
    
    return merge(query(2*node, start, mid, l, r),
                query(2*node+1, mid+1, end, l, r));
}

CinemaRow::CinemaRow(int size) : n(size) {
    seats.assign(n, true);
    quality.resize(n);
    tree.resize(4 * n);
    
    double center = (n - 1) / 2.0;
    for (int i = 0; i < n; i++) {
        double dist = abs(i - center);
        int score = 100 - (int)(dist * (80.0 / center));
        quality[i] = max(10, score);
    }
    
    build(1, 0, n-1);
}

void CinemaRow::reserveRange(int start, int end) {
    if (start > end || start < 0 || end >= n) return;
    for(int i=start; i<=end; ++i) seats[i] = false;
    updateRange(1, 0, n-1, start, end, false);
}

void CinemaRow::cancelRange(int start, int end) {
    if (start > end || start < 0 || end >= n) return;
    for(int i=start; i<=end; ++i) seats[i] = true;
    updateRange(1, 0, n-1, start, end, true);
}

tuple<bool, int, int> CinemaRow::findBestBlock(int k) {
    if (tree[1].max_consecutive < k) {
        return {false, -1, -1};
    }
    
    int bestStart = -1;
    int maxScore = -1;
    int currentFree = 0;
    
    for (int i = 0; i < n; i++) {
        if (seats[i]) {
            currentFree++;
        } else {
            currentFree = 0;
        }
        
        if (currentFree >= k) {
            int start = i - k + 1;
            int score = 0;
            for(int j=0; j<k; j++) score += quality[start+j];
            
            if (score > maxScore) {
                maxScore = score;
                bestStart = start;
            }
        }
    }
    
    if (bestStart != -1) return {true, bestStart, maxScore};
    return {false, -1, -1};
}

int CinemaRow::queryFree(int l, int r) {
    if (l > r || l < 0 || r >= n) return 0;
    return query(1, 0, n-1, l, r).total_free;
}

int CinemaRow::getQuality(int pos) {
    if (pos >= 0 && pos < n) return quality[pos];
    return 0;
}

void CinemaRow::print() {
    for (int i = 0; i < n; i++) {
        if (!seats[i]) cout << RED << "X" << RESET << " ";
        else {
            if (quality[i] >= 90) cout << YELLOW << "*" << RESET << " ";
            else if (quality[i] >= 60) cout << GREEN << "O" << RESET << " ";
            else cout << CYAN << "-" << RESET << " ";
        }
    }
    cout << RESET;
}

bool CinemaRow::isFree(int pos) {
    return pos >= 0 && pos < n && seats[pos];
}
