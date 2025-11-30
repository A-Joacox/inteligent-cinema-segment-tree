#ifndef CINEMA_ROW_H
#define CINEMA_ROW_H

#include <vector>
#include <algorithm>
#include <iostream>
#include <tuple>

// Colores para visualización
#define GREEN "\033[32m"   // Asiento libre (Standard)
#define RED "\033[31m"     // Asiento ocupado
#define YELLOW "\033[33m"  // Asiento Premium
#define CYAN "\033[36m"    // Asiento Low Cost
#define RESET "\033[0m"

using namespace std;

// Estructura del Nodo
struct SeatNode {
    int total_free;        // Total de asientos libres en el rango
    int max_consecutive;   // Máximo de asientos libres consecutivos en el rango
    int prefix_free;       // Asientos libres DESDE EL INICIO del rango
    int suffix_free;       // Asientos libres HASTA EL FINAL del rango
    int length;            // Longitud del rango
    int lazy;              // Lazy propagation para updates
    
    SeatNode();
    SeatNode(bool is_free, int len = 1);
};

// Clase Segment Tree
class CinemaRow {
private:
    int n;
    vector<SeatNode> tree;
    vector<bool> seats;
    vector<int> quality;
    
    SeatNode merge(const SeatNode& left, const SeatNode& right);
    void push(int node);
    void build(int node, int start, int end);
    void updateRange(int node, int start, int end, int l, int r, bool set_free);
    SeatNode query(int node, int start, int end, int l, int r);

public:
    CinemaRow(int size);
    void reserveRange(int start, int end);
    void cancelRange(int start, int end);
    tuple<bool, int, int> findBestBlock(int k);
    int queryFree(int l, int r);
    int getQuality(int pos);
    void print();
    bool isFree(int pos);
};

#endif
