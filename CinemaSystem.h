#ifndef CINEMA_SYSTEM_H
#define CINEMA_SYSTEM_H

#include "CinemaRow.h"
#include <vector>
#include <iomanip>

class CinemaSystem {
private:
    vector<CinemaRow*> rows;
    int numRows;
    int seatsPerRow;
    
public:
    CinemaSystem(int rows, int seatsPerRow);
    ~CinemaSystem();
    
    tuple<int, int, int> findBestSeats(int n);
    bool reserve(int row, int start, int count);
    void cancel(int row, int start, int count);
    void display();
    void stats();
};

#endif
