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

## Complejidad Algorítmica

Análisis de complejidad temporal para las operaciones principales de cada estructura de datos:

| Estructura | Construcción | Query (Rango) | Update (Punto) | Update (Rango) | Espacio |
|------------|--------------|---------------|----------------|----------------|---------|
| **Segment Tree** | $O(N)$ | $O(\log N)$ | $O(\log N)$ | $O(\log N)$ con Lazy | $O(4N)$ |
| **AVL Tree** | $O(N \log N)$ | $O(\log N + K)$* | $O(\log N)$ | $O(K \log N)$** | $O(N)$ |
| **Fenwick Tree** | $O(N \log N)$ | $O(\log N)$ | $O(\log N)$ | No soportado | $O(N)$ |
| **Linear Search** | $O(N)$ | $O(N)$ | $O(1)$ | $O(N)$ | $O(N)$ |

**Notas:**
- *K = tamaño del rango consultado
- **Requiere K operaciones individuales de inserción/eliminación con rotaciones

### Detalles por Estructura

#### 1. Segment Tree (con Lazy Propagation)
- **Construcción**: $O(N)$ - Construye el árbol bottom-up
- **Query**: $O(\log N)$ - Divide el rango recursivamente
- **Update Punto**: $O(\log N)$ - Actualiza desde hoja hasta raíz
- **Update Rango**: $O(\log N)$ - Lazy propagation evita actualizar todos los nodos
- **Ventaja**: Excelente para operaciones de rango con actualizaciones frecuentes

#### 2. AVL Tree
- **Construcción**: $O(N \log N)$ - Inserciones balanceadas una por una
- **Query**: $O(\log N + K)$ - Búsqueda del inicio + recorrido in-order
- **Update Punto**: $O(\log N)$ - Búsqueda + rotaciones para mantener balance
- **Update Rango**: $O(K \log N)$ - Requiere K operaciones individuales
- **Ventaja**: Mantiene elementos ordenados, útil para búsquedas por valor

#### 3. Fenwick Tree (Binary Indexed Tree)
- **Construcción**: $O(N \log N)$ - Actualizaciones incrementales
- **Query**: $O(\log N)$ - Suma de prefijos mediante saltos binarios
- **Update Punto**: $O(\log N)$ - Propaga cambios hacia arriba
- **Update Rango**: No soportado directamente (requiere técnicas avanzadas)
- **Ventaja**: Implementación simple y eficiente en memoria

#### 4. Linear Search
- **Construcción**: $O(N)$ - Copia directa del arreglo
- **Query**: $O(N)$ - Recorre todo el rango secuencialmente
- **Update Punto**: $O(1)$ - Acceso directo por índice
- **Update Rango**: $O(N)$ - Actualiza cada elemento del rango
- **Ventaja**: Simplicidad, no requiere estructuras auxiliares

### Conclusión
Para el caso de uso del sistema de cine (consultas y actualizaciones de rango frecuentes), **Segment Tree con Lazy Propagation** ofrece el mejor balance de rendimiento con complejidad $O(\log N)$ para todas las operaciones críticas.

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

## Integrantes
- **Joaquin Mercado**
- **Mathias Castro**

Proyecto realizado para el curso de Algoritmos y Estructuras de Datos (AED).
