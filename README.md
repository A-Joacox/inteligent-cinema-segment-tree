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
    - Comparativa de rendimiento contra **Linear Search**, **Fenwick Tree** y **AVL Tree**.

## Compilación y Ejecución
El proyecto está escrito en C++ moderno y modularizado.

### Requisitos
- Compilador G++ (soporte C++17 recomendado).

### Instrucciones
Desde la carpeta del proyecto:

```bash
cd IntelligentCinema
g++ main.cpp CinemaRow.cpp CinemaSystem.cpp Benchmark.cpp -o cinema_app
./cinema_app
```

## Resultados del Benchmark
El sistema incluye una herramienta de benchmarking (Opción 5 del menú) que compara 4 estructuras:

**Resultados típicos (N=10,000 asientos):**
- **Consultas (Queries)**: 
    - Segment Tree: **0.015 us** (Extremadamente rápido)
    - Linear Search: 250.11 us (~17,000x más lento)
    - Fenwick Tree: 0.030 us (Muy rápido)
    - AVL Tree: 0.096 us (Rápido)
- **Actualizaciones (Updates)**: 
    - Segment Tree: **149 us** (Eficiente para rangos)
    - AVL Tree: 1270 us (Muy lento por rotaciones)

## Estructura del Código
- `CinemaRow (.h/.cpp)`: Implementación del Segment Tree.
- `FenwickRow.h`: Implementación del Fenwick Tree.
- `AVLRow.h`: Implementación del AVL Tree.
- `CinemaSystem (.h/.cpp)`: Lógica de negocio.
- `Benchmark (.h/.cpp)`: Pruebas de rendimiento.
- `main.cpp`: Punto de entrada.

## Autor
Proyecto realizado para el curso de AED.
