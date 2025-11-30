#include "CinemaSystem.h"

CinemaSystem::CinemaSystem(int rows, int seatsPerRow) 
    : numRows(rows), seatsPerRow(seatsPerRow) {
    for (int i = 0; i < numRows; i++) {
        this->rows.push_back(new CinemaRow(seatsPerRow));
    }
}

CinemaSystem::~CinemaSystem() {
    for (auto row : rows) {
        delete row;
    }
}

tuple<int, int, int> CinemaSystem::findBestSeats(int n) {
    int bestRow = -1;
    int bestStart = -1;
    int maxScore = -1;
    
    for (int row = 0; row < numRows; row++) {
        auto [found, start, score] = rows[row]->findBestBlock(n);
        if (found) {
            if (score > maxScore) {
                maxScore = score;
                bestRow = row;
                bestStart = start;
            }
        }
    }
    
    if (bestRow != -1) return {bestRow, bestStart, maxScore};
    return {-1, -1, -1};
}

bool CinemaSystem::reserve(int row, int start, int count) {
    if (row < 0 || row >= numRows) return false;
    
    for (int i = 0; i < count; i++) {
        if (!rows[row]->isFree(start + i)) {
            return false;
        }
    }
    
    rows[row]->reserveRange(start, start + count - 1);
    return true;
}

void CinemaSystem::cancel(int row, int start, int count) {
    if (row >= 0 && row < numRows) {
        rows[row]->cancelRange(start, start + count - 1);
    }
}

void CinemaSystem::display() {
    cout << "\n";
    cout << "+----------------------------------------------------+\n";
    cout << "|         CINE UTEC - SALA 1                         |\n";
    cout << "+----------------------------------------------------+\n";
    cout << "|                  [PANTALLA]                        |\n";
    cout << "|            ===================                     |\n";
    cout << "+----------------------------------------------------+\n";
    
    for (int i = 0; i < numRows; i++) {
        cout << "|  Fila " << char('A' + i) << ":  ";
        rows[i]->print();
        
        int printed = seatsPerRow * 2;
        for (int j = printed; j < 40; j++) cout << " ";
        cout << "|\n";
    }
    
    cout << "+----------------------------------------------------+\n";
    cout << "|  " << GREEN << "O" << RESET << " = Standard  " 
            << YELLOW << "*" << RESET << " = Premium  " 
            << CYAN << "-" << RESET << " = Low Cost  " 
            << RED << "X" << RESET << " = Ocupado |\n";
    cout << "+----------------------------------------------------+\n";
}

void CinemaSystem::stats() {
    int totalFree = 0;
    int totalSeats = numRows * seatsPerRow;
    
    for (int i = 0; i < numRows; i++) {
        totalFree += rows[i]->queryFree(0, seatsPerRow - 1);
    }
    
    cout << "\n[ESTADISTICAS]\n";
    cout << "   Total de asientos: " << totalSeats << "\n";
    cout << "   Asientos libres: " << totalFree << "\n";
    cout << "   Asientos ocupados: " << (totalSeats - totalFree) << "\n";
    cout << "   Ocupacion: " << fixed << setprecision(1) 
            << (100.0 * (totalSeats - totalFree) / totalSeats) << "%\n\n";
}
