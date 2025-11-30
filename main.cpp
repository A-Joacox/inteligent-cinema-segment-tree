#include <iostream>
#include <cstdlib>
#include "CinemaSystem.h"
#include "Benchmark.h"

using namespace std;

void menu() {
    CinemaSystem cinema(8, 20);  // 8 filas, 20 asientos cada una
    
    // DATOS INICIALES
    cout << "Cargando reservas existentes...\n\n";
    
    cinema.reserve(0, 0, 3);
    cinema.reserve(0, 8, 2);
    cinema.reserve(1, 5, 5);
    cinema.reserve(2, 0, 2);
    cinema.reserve(2, 4, 1);
    cinema.reserve(2, 7, 3);
    cinema.reserve(2, 15, 4);
    cinema.reserve(3, 6, 8);
    cinema.reserve(4, 2, 1);
    cinema.reserve(4, 5, 2);
    cinema.reserve(4, 10, 3);
    cinema.reserve(4, 16, 2);
    cinema.reserve(5, 0, 7);
    cinema.reserve(5, 12, 8);
    cinema.reserve(6, 14, 6);
    cinema.reserve(7, 10, 2);
    
    cout << "Datos iniciales cargados!\n";
    cout << "El cine tiene varias reservas pre-existentes.\n";
    cout << "Ahora puedes probar el sistema de busqueda...\n\n";
    
    cout << "Presiona Enter para continuar...";
    cin.get();
    
    while (true) {
        cinema.display();
        cinema.stats();
        
        cout << "+----------------------------------------+\n";
        cout << "|         MENU PRINCIPAL                 |\n";
        cout << "+----------------------------------------+\n";
        cout << "| 1. Buscar mejores asientos             |\n";
        cout << "| 2. Reservar asientos                   |\n";
        cout << "| 3. Cancelar reserva                    |\n";
        cout << "| 4. Ver estadisticas                    |\n";
        cout << "| 5. Benchmark                           |\n";
        cout << "| 0. Salir                               |\n";
        cout << "+----------------------------------------+\n";
        cout << "Opcion: ";
        
        int option;
        cin >> option;
        
        if (option == 0) break;
        
        switch (option) {
            case 1: {
                int n;
                cout << "¿Cuántos asientos necesitas? ";
                cin >> n;
                
                auto [row, start, score] = cinema.findBestSeats(n);
                if (row != -1) {
                    cout << "[OK] Encontrado: Fila " << char('A' + row) 
                         << ", asientos " << start << "-" << (start + n - 1) << "\n";
                    cout << "     Puntaje de Calidad: " << score << " puntos\n";
                    
                    cout << "Deseas reservar? (1=Si, 0=No): ";
                    int confirm;
                    cin >> confirm;
                    if (confirm) {
                        cinema.reserve(row, start, n);
                        cout << "[OK] Reserva realizada exitosamente!\n";
                    }
                } else {
                    cout << "[ERROR] No hay " << n << " asientos consecutivos disponibles\n";
                }
                break;
            }
            case 2: {
                int row, start, count;
                cout << "Fila (A=0, B=1, ...): ";
                cin >> row;
                cout << "Asiento inicial: ";
                cin >> start;
                cout << "Cantidad de asientos: ";
                cin >> count;
                
                if (cinema.reserve(row, start, count)) {
                    cout << "[OK] Reserva exitosa!\n";
                } else {
                    cout << "[ERROR] No se pudo reservar (asientos ocupados)\n";
                }
                break;
            }
            case 3: {
                int row, start, count;
                cout << "Fila (A=0, B=1, ...): ";
                cin >> row;
                cout << "Asiento inicial: ";
                cin >> start;
                cout << "Cantidad de asientos: ";
                cin >> count;
                
                cinema.cancel(row, start, count);
                cout << "[OK] Reserva cancelada!\n";
                break;
            }
            case 4:
                break;
            case 5:
                benchmark();
                break;
            default:
                cout << "[ERROR] Opcion invalida\n";
        }
        
        cout << "\nPresiona Enter para continuar...";
        cin.ignore();
        cin.get();
        system("clear");
    }
}

int main() {
    cout << "SISTEMA DE RESERVA DE ASIENTOS - SEGMENT TREE\n";
    cout << "================================================\n\n";
    
    menu();
    
    cout << "\nGracias por usar el sistema!\n";
    return 0;
}
