# PROTOTIPO ABB - ÁRBOL GENEALÓGICO MITOLÓGICO GRIEGO

## 📋 Descripción General

Implementación de un **Árbol Binario de Búsqueda (ABB)** aplicado a la genealogía de dioses y héroes de la mitología griega. El programa permite gestionar miembros mitológicos mediante operaciones básicas de ABB, con una interfaz de consola intuitiva y visualización ASCII del árbol.

## ✨ Características Principales

### 🔒 Validación de Entradas

- **Validación numérica robusta:** Verifica que año y mes sean valores numéricos válidos
- **Rangos controlados:** Año (0-9999), Mes (1-12)
- **Manejo de errores:** Evita crashes por entradas incorrectas

### 🔑 Sistema de Claves Únicas

- **Clave compuesta:** `anio * 100 + mes`
- **Ejemplo:** Año 10, Mes 6 → Clave 1006
- **Ventaja:** Permite diferenciar seres del mismo año pero distinto mes
- **Prevención de duplicados:** El sistema avisa si ya existe un miembro con esa clave

### 🌳 Operaciones del ABB

- **Insertar:** Agrega nuevos miembros manteniendo el orden del árbol
- **Buscar:** Localiza miembros por año y mes de forma eficiente
- **Eliminar:** Remueve miembros usando el algoritmo del sucesor inorden
- **Recorridos:** Inorden, Preorden y Postorden para diferentes vistas de los datos

### 🎨 Visualización ASCII

- **Vista vertical:** Raíz arriba, hijos abajo (más natural)
- **Caracteres especiales:** `├──`, `└──`, `│` para mostrar conexiones
- **Información completa:** Muestra nombre, [año-mes] y (rol) de cada nodo
- **Actualización automática:** Se muestra después de insertar/eliminar

### 🧪 Datos de Prueba

- **15 miembros precargados:** Desde Ouranos (primigenio) hasta Teseo (héroe)
- **Árbol balanceado:** Zeus como raíz central con ramas equilibradas
- **Diversidad mitológica:** Incluye primigenios, titanes, olímpicos y héroes

## 🏗️ Estructura del Código

### Estructura de Datos
```cpp
struct Nodo {
    int anio;           // Año de referencia
    int mes;            // Mes de referencia
    int clave;          // Clave única (anio*100 + mes)
    string nombre;      // Nombre del ser mitológico
    string rol;         // Rol (Primigenio, Titan, Olimpico, Heroe)
    Nodo* izq;          // Puntero al hijo izquierdo
    Nodo* der;          // Puntero al hijo derecho
};

### Funciones Principales

#### `insertar(Nodo* raiz, int anio, int mes, string nombre, string rol)`
- **Propósito:** Inserta un nuevo nodo en el ABB
- **Lógica:** Compara claves y decide si va a izquierda (menor) o derecha (mayor)
- **Retorno:** Nueva raíz del árbol
- **Complejidad:** O(h) donde h es la altura del árbol

#### `buscarExacto(Nodo* raiz, int anio, int mes)`
- **Propósito:** Busca un nodo específico por año y mes
- **Lógica:** Navegación recursiva comparando claves
- **Retorno:** Puntero al nodo encontrado o NULL
- **Complejidad:** O(h)

#### `eliminarMiembro(Nodo* raiz, int anio, int mes)`
- **Propósito:** Elimina un nodo del árbol
- **Casos manejados:**
  - Nodo sin hijos: eliminación directa
  - Nodo con un hijo: reemplaza por su hijo
  - Nodo con dos hijos: reemplaza por sucesor inorden (mínimo del subárbol derecho)
- **Retorno:** Nueva raíz del árbol
- **Complejidad:** O(h)

#### `imprimirArbolAscii(Nodo* raiz, string prefix, bool esUltimo)`
- **Propósito:** Visualiza el árbol en formato ASCII vertical
- **Parámetros:**
  - `prefix`: Prefijo para mantener la estructura visual
  - `esUltimo`: Determina qué caracteres usar (├── o └──)
- **Lógica:** Recorrido recursivo mostrando primero izquierda, luego derecha
- **Salida:** Representación visual del árbol en consola

#### `leerIntRango(string prompt, int &valor, int minVal, int maxVal)`
- **Propósito:** Lee y valida entradas numéricas dentro de un rango
- **Validaciones:**
  - Verifica que todos los caracteres sean dígitos
  - Comprueba que el valor esté dentro del rango permitido
- **Retorno:** true cuando se obtiene un valor válido

#### `cargarMitologia(Nodo* raiz)`
- **Propósito:** Carga 15 miembros mitológicos como datos de prueba
- **Distribución:**
  - Zeus (10-6) como raíz central
  - 8 nodos en rama izquierda (claves menores)
  - 6 nodos en rama derecha (claves mayores)
- **Resultado:** Árbol relativamente balanceado

### Recorridos del Árbol

#### `inorden(Nodo* raiz)`
- **Orden:** Izquierda → Raíz → Derecha
- **Resultado:** Elementos ordenados de menor a mayor por clave
- **Uso:** Ver la secuencia cronológica de los miembros

#### `preorden(Nodo* raiz)`
- **Orden:** Raíz → Izquierda → Derecha
- **Resultado:** Útil para copiar o serializar el árbol
- **Uso:** Ver jerarquía desde la raíz

#### `postorden(Nodo* raiz)`
- **Orden:** Izquierda → Derecha → Raíz
- **Resultado:** Útil para eliminar el árbol completo
- **Uso:** Procesar hojas antes que padres

## 📊 Datos Mitológicos Precargados
struct Nodo {
    int anio;           // Año de referencia
    int mes;            // Mes de referencia
    int clave;          // Clave única (anio*100 + mes)
    string nombre;      // Nombre del ser mitológico
    string rol;         // Rol (Primigenio, Titan, Olimpico, Heroe)
    Nodo* izq;          // Puntero al hijo izquierdo
    Nodo* der;          // Puntero al hijo derecho
};

### Funciones Principales

#### `insertar(Nodo* raiz, int anio, int mes, string nombre, string rol)`
- **Propósito:** Inserta un nuevo nodo en el ABB
- **Lógica:** Compara claves y decide si va a izquierda (menor) o derecha (mayor)
- **Retorno:** Nueva raíz del árbol
- **Complejidad:** O(h) donde h es la altura del árbol

#### `buscarExacto(Nodo* raiz, int anio, int mes)`
- **Propósito:** Busca un nodo específico por año y mes
- **Lógica:** Navegación recursiva comparando claves
- **Retorno:** Puntero al nodo encontrado o NULL
- **Complejidad:** O(h)

#### `eliminarMiembro(Nodo* raiz, int anio, int mes)`
- **Propósito:** Elimina un nodo del árbol
- **Casos manejados:**
  - Nodo sin hijos: eliminación directa
  - Nodo con un hijo: reemplaza por su hijo
  - Nodo con dos hijos: reemplaza por sucesor inorden (mínimo del subárbol derecho)
- **Retorno:** Nueva raíz del árbol
- **Complejidad:** O(h)

#### `imprimirArbolAscii(Nodo* raiz, string prefix, bool esUltimo)`
- **Propósito:** Visualiza el árbol en formato ASCII vertical
- **Parámetros:**
  - `prefix`: Prefijo para mantener la estructura visual
  - `esUltimo`: Determina qué caracteres usar (├── o └──)
- **Lógica:** Recorrido recursivo mostrando primero izquierda, luego derecha
- **Salida:** Representación visual del árbol en consola

#### `leerIntRango(string prompt, int &valor, int minVal, int maxVal)`
- **Propósito:** Lee y valida entradas numéricas dentro de un rango
- **Validaciones:**
  - Verifica que todos los caracteres sean dígitos
  - Comprueba que el valor esté dentro del rango permitido
- **Retorno:** true cuando se obtiene un valor válido

#### `cargarMitologia(Nodo* raiz)`
- **Propósito:** Carga 15 miembros mitológicos como datos de prueba
- **Distribución:**
  - Zeus (10-6) como raíz central
  - 8 nodos en rama izquierda (claves menores)
  - 6 nodos en rama derecha (claves mayores)
- **Resultado:** Árbol relativamente balanceado

### Recorridos del Árbol

#### `inorden(Nodo* raiz)`
- **Orden:** Izquierda → Raíz → Derecha
- **Resultado:** Elementos ordenados de menor a mayor por clave
- **Uso:** Ver la secuencia cronológica de los miembros

#### `preorden(Nodo* raiz)`
- **Orden:** Raíz → Izquierda → Derecha
- **Resultado:** Útil para copiar o serializar el árbol
- **Uso:** Ver jerarquía desde la raíz

#### `postorden(Nodo* raiz)`
- **Orden:** Izquierda → Derecha → Raíz
- **Resultado:** Útil para eliminar el árbol completo
- **Uso:** Procesar hojas antes que padres

## 📊 Datos Mitológicos Precargados
└── Zeus [10-6] (Rey Olimpico)
    ├── Cronos [5-3] (Titan)
    │   ├── Oceano [3-2] (Titan)
    │   │   ├── Ouranos [2-1] (Primigenio)
    │   │   └── Rea [4-5] (Titanide)
    │   └── Hades [7-8] (Olimpico)
    │       ├── Hestia [6-4] (Olimpica)
    │       └── Poseidon [8-9] (Olimpico)
    └── Atenea [15-7] (Olimpica)
        ├── Apolo [13-2] (Olimpico)
        │   ├── Artemisa [12-1] (Olimpica)
        │   └── Hermes [14-5] (Olimpico)
        └── Heracles [18-3] (Heroe)
            ├── Perseo [17-9] (Heroe)
            └── Teseo [20-4] (Heroe)
```

## Ejecucion
```cpp
./main
```

### Menú Interactivo
```
MENU:
1. Insertar       → Agregar nuevo miembro
2. Buscar         → Buscar por año+mes
3. Eliminar       → Eliminar miembro
4. Inorden        → Ver lista ordenada
5. Preorden       → Ver jerarquía
6. Postorden      → Ver hojas primero
7. Ver árbol      → Mostrar visualización ASCII
8. Salir          → Terminar programa
```

### Ejemplo de Uso
```
1. Al iniciar: Se carga automáticamente el árbol con 15 miembros
2. Opción 7: Ver la estructura completa del árbol
3. Opción 1: Insertar "Afrodita" (año: 11, mes: 3, rol: "Olimpica")
4. Opción 2: Buscar a Zeus (año: 10, mes: 6)
5. Opción 4: Ver todos los miembros en orden cronológico
```

## 🔧 Características Técnicas

### Simplicidad Didáctica

- **Sin librerías complejas:** Solo `<iostream>` y `<string>`
- **Punteros básicos:** Uso de NULL en lugar de nullptr
- **Código legible:** Comentarios y nombres descriptivos
- **Estructura clara:** Separación lógica con comentarios de sección

### Limitaciones Conocidas (Intencionales)

- No usa clases u OOP avanzado
- No implementa balanceo automático (AVL/Red-Black)
- Validación básica sin excepciones
- Sin persistencia en archivos
- Manejo de memoria manual (sin smart pointers)

### Posibles Mejoras Futuras

- [ ]  Agregar campo `dia` para más granularidad
- [ ]  Implementar persistencia en archivos
- [ ]  Agregar relaciones padre-hijo explícitas
- [ ]  Balanceo automático del árbol
- [ ]  Interfaz gráfica
- [ ]  Sistema de búsqueda por nombre
- [ ]  Exportar árbol a formato DOT (Graphviz)

## 📚 Conceptos de Estructuras de Datos Aplicados

### Árbol Binario de Búsqueda

- **Propiedad fundamental:** Hijo izquierdo < Padre < Hijo derecho
- **Ventaja:** Búsqueda eficiente O(log n) en árbol balanceado
- **Desventaja:** Puede degradarse a O(n) si está desbalanceado

### Recursión

- Todas las operaciones principales usan recursión
- Caso base: nodo NULL o nodo encontrado
- Caso recursivo: navegar por izquierda o derecha

### Algoritmo del Sucesor Inorden

- Se usa en la eliminación de nodos con dos hijos
- Encuentra el menor valor del subárbol derecho
- Mantiene la propiedad del ABB después de eliminar