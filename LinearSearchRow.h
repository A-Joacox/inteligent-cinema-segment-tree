#ifndef LINEAR_SEARCH_ROW_H
#define LINEAR_SEARCH_ROW_H

#include <vector>
using namespace std;

class LinearSearchRow {
    vector<bool> seats;
    int n;
public:
    LinearSearchRow(int size) : n(size) {
        seats.assign(n, true);
    }
    
    void reserveRange(int start, int end) {
        for(int i=start; i<=end && i<n; ++i) seats[i] = false;
    }
    
    int queryFree(int l, int r) {
        int count = 0;
        for(int i=l; i<=r && i<n; ++i) {
            if(seats[i]) count++;
        }
        return count;
    }
};

#endif
