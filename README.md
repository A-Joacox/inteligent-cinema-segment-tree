# Intelligent Cinema - Segment Tree Application

## Descripción
Proyecto para el curso de Algoritmos y Estructuras de Datos (AED). Implementación de un sistema de reserva de cine "inteligente" utilizando **Segment Trees** con **Lazy Propagation**.

El objetivo es demostrar la utilidad práctica de las estructuras de datos avanzadas para resolver problemas de optimización en tiempo real.

## Características Principales
1.  **Segment Tree con Lazy Propagation**: 
    - Permite actualizaciones de rango (reservas de grupos completos) en tiempo $O(\log N)$.
    - Optimización crítica para sistemas de alta concurrencia.
2.  **Sistema de Calidad de Asientos**: 
    - Asignación automática de puntajes a los asientos basada en una distribución normal (Centro > Bordes).
    - Visualización gráfica de categorías: Premium (`*`), Standard (`O`), Low Cost (`-`).
3.  **Búsqueda Inteligente (Heurística)**: 
    - Algoritmo `findBestSeats` que encuentra automáticamente los *mejores* asientos disponibles, maximizando el puntaje de calidad acumulado.
4.  **Benchmark Científico**: 
    - Comparativa de rendimiento en tiempo real contra una Búsqueda Lineal ($O(N)$).

## Compilación y Ejecución
El proyecto está escrito en C++ moderno y modularizado.

### Requisitos
- Compilador G++ (soporte C++17 recomendado).

### Instrucciones
Desde la carpeta del proyecto:

```bash
g++ main.cpp CinemaRow.cpp CinemaSystem.cpp Benchmark.cpp -o cinema_app
./cinema_app
```

## Resultados del Benchmark
El sistema incluye una herramienta de benchmarking (Opción 5 del menú) que compara el Segment Tree contra una implementación ingenua (Linear Search). (De ahí añado comparación con Fenwick Tree y AVL)

**Resultados típicos (N=10,000 asientos):**
- **Consultas (Queries)**: El Segment Tree es **~17,000x más rápido**.
- **Actualizaciones (Updates)**: Rendimiento comparable, pero con mejor escalabilidad asintótica.

## Estructura del Código
- `CinemaRow (.h/.cpp)`: Implementación del Segment Tree, Nodos y Lazy Propagation.
- `CinemaSystem (.h/.cpp)`: Lógica de negocio, gestión de filas y estadísticas.
- `Benchmark (.h/.cpp)`: Pruebas de rendimiento y métricas.
- `LinearSearchRow.h`: Clase base para comparación en el benchmark.
- `main.cpp`: Punto de entrada e interfaz de usuario (CLI).
