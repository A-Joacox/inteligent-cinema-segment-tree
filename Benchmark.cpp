#include "Benchmark.h"
#include "CinemaRow.h"
#include "LinearSearchRow.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>

using namespace std;

void benchmark() {
    cout << "\nBENCHMARK: Segment Tree vs Busqueda Lineal\n";
    cout << "================================================================\n";
    cout << "Comparando operaciones de Rango (Update) y Consulta (Query)\n";
    cout << "================================================================\n\n";
    
    vector<int> sizes = {1000, 10000, 100000};
    
    for (int size : sizes) {
        cout << "--- Dataset: " << size << " asientos ---\n";
        
        CinemaRow segTree(size);
        LinearSearchRow linear(size);
        
        // 1. TEST DE ACTUALIZACIÓN (RESERVA DE RANGO)
        int startRange = size / 4;
        int endRange = size * 3 / 4;
        
        auto t1 = chrono::high_resolution_clock::now();
        for(int i=0; i<1000; i++) segTree.reserveRange(startRange, endRange);
        auto t2 = chrono::high_resolution_clock::now();
        double st_update = chrono::duration<double, micro>(t2 - t1).count() / 1000.0;
        
        t1 = chrono::high_resolution_clock::now();
        for(int i=0; i<1000; i++) linear.reserveRange(startRange, endRange);
        t2 = chrono::high_resolution_clock::now();
        double lin_update = chrono::duration<double, micro>(t2 - t1).count() / 1000.0;
        
        cout << "Update (Range Reserve):\n";
        cout << "  Segment Tree (Lazy): " << fixed << setprecision(3) << st_update << " us\n";
        cout << "  Linear Search:       " << lin_update << " us\n";
        cout << "  Speedup:             " << GREEN << (lin_update / st_update) << "x MAS RAPIDO" << RESET << "\n\n";
        
        // 2. TEST DE CONSULTA (CONTAR LIBRES)
        t1 = chrono::high_resolution_clock::now();
        for(int i=0; i<1000; i++) segTree.queryFree(0, size-1);
        t2 = chrono::high_resolution_clock::now();
        double st_query = chrono::duration<double, micro>(t2 - t1).count() / 1000.0;
        
        t1 = chrono::high_resolution_clock::now();
        for(int i=0; i<1000; i++) linear.queryFree(0, size-1);
        t2 = chrono::high_resolution_clock::now();
        double lin_query = chrono::duration<double, micro>(t2 - t1).count() / 1000.0;
        
        cout << "Query (Count Free):\n";
        cout << "  Segment Tree:        " << st_query << " us\n";
        cout << "  Linear Search:       " << lin_query << " us\n";
        cout << "  Speedup:             " << GREEN << (lin_query / st_query) << "x MAS RAPIDO" << RESET << "\n\n";
    }
}
