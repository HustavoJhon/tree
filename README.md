<a id="readme-top"></a>

<br />
<div align="center">
  <a href="https://github.com/HustavoJhon/abb-mitologia">
    <img src="./assets/logo.jpg" alt="Logo" width="140" height="140">
  </a>

  <h2 align="center">ABB MITOLÓGICO — Árbol Genealógico de la Mitología Griega</h2>

  <p align="center">
    Proyecto universitario desarrollado en C++ que implementa un Árbol Binario de Búsqueda aplicado a la genealogía de dioses, titanes y héroes griegos.
    <br />
    <a href="#"><strong>📘 Ver Informe Completo »</strong></a>
    <br /><br />
    <a href="#codigo">Ver Código</a>
    ·
    <a href="#instalacion">⚙️ Compilar y Ejecutar</a>
    ·
    <a href="#pruebas">🧪 Pruebas</a>
  </p>

  <div>
    <a href="#"><img src="https://img.shields.io/badge/Proyecto-ABB_Mitológico-purple?style=for-the-badge"></a>
    <a href="#"><img src="https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=cplusplus&logoColor=white"></a>
    <a href="#"><img src="https://img.shields.io/badge/Estructura_de_Datos-ABB-orange?style=for-the-badge"></a>
  </div>
</div>

---

<details>
  <summary><b>📑 Tabla de Contenidos</b></summary>
  <ol>
    <li><a href="#sobre-el-proyecto">📘 Sobre el Proyecto</a></li>
    <li><a href="#caracteristicas">✨ Características</a></li>
    <li><a href="#estructura">🏗️ Estructura del Nodo</a></li>
    <li><a href="#operaciones">🔧 Operaciones Implementadas</a></li>
    <li><a href="#instalacion">⚙️ Instalación</a></li>
    <li><a href="#datos-mitologicos">🏛️ Datos Mitológicos</a></li>
    <li><a href="#integrantes">👥 Integrantes</a></li>
    <li><a href="#licencia">📄 Licencia</a></li>
  </ol>
</details>

---

<h2 id="sobre-el-proyecto">📘 Sobre el Proyecto</h2>

Este proyecto implementa un **Árbol Binario de Búsqueda (ABB)** para modelar la jerarquía de dioses, titanes y héroes de la **mitología griega**. Utiliza una clave compuesta `año*100 + mes` para organizar temporalmente a los personajes mitológicos, permitiendo consultas eficientes y visualización clara de las relaciones genealógicas.

### 🎯 Propósito

El ABB permite:
- Organizar la genealogía en orden temporal coherente
- Realizar búsquedas eficientes en O(log n)
- Recorrer la estructura con Inorden, Preorden y Postorden
- Visualizar las relaciones jerárquicas mediante ASCII
- Gestionar inserciones y eliminaciones manteniendo el orden del árbol

<p align="right">(<a href="#readme-top">Volver arriba ↑</a>)</p>

---

<h2 id="caracteristicas">✨ Características</h2>

### 🔒 Validación de Entradas
- Validación numérica de año (0-9999) y mes (1-12)
- Prevención de caracteres inválidos
- Verificación de campos no vacíos para nombre y rol

### 🔑 Sistema de Claves Únicas
- Clave compuesta: `anio * 100 + mes`
- Ejemplo: Año 10, Mes 6 → Clave 1006
- Prevención automática de duplicados

### 🌳 Operaciones del ABB
- **Insertar:** Mantiene el orden del árbol al agregar miembros
- **Buscar:** Localiza por año y mes de forma eficiente
- **Eliminar:** Usa algoritmo del sucesor inorden para nodos con dos hijos
- **Recorridos:** Inorden (cronológico), Preorden (jerárquico), Postorden (generacional)

### 🎨 Visualización ASCII
- Representación vertical con raíz arriba
- Caracteres especiales: `├──`, `└──`, `│`
- Información completa: nombre, [año-mes] y (rol)

### 🧪 Datos Precargados
- 15 miembros mitológicos desde Ouranos hasta Teseo
- Árbol balanceado con Zeus como raíz central
- Incluye: Primigenios, Titanes, Olímpicos y Héroes

<p align="right">(<a href="#readme-top">Volver arriba ↑</a>)</p>

---

<h2 id="estructura">🏗️ Estructura del Nodo</h2>
```cpp
struct Nodo {
    int anio;           // Año simbólico
    int mes;            // Mes simbólico
    int clave;          // anio*100 + mes
    string nombre;      // Nombre mitológico
    string rol;         // Primigenio, Titan, Olimpico, Heroe
    Nodo* izq;          // Subárbol izquierdo (menores)
    Nodo* der;          // Subárbol derecho (mayores)
};
```

<p align="right">(<a href="#readme-top">Volver arriba ↑</a>)</p>

---

<h2 id="operaciones">🔧 Operaciones Implementadas</h2>

| Operación | Descripción | Complejidad |
|-----------|-------------|-------------|
| **Insertar** | Agrega un nodo en la posición correcta según su clave | O(h) |
| **Buscar** | Localiza un nodo por año y mes | O(h) |
| **Eliminar** | Remueve un nodo manteniendo el orden del ABB | O(h) |
| **Inorden** | Recorrido cronológico ascendente | O(n) |
| **Preorden** | Recorrido jerárquico desde la raíz | O(n) |
| **Postorden** | Recorrido generacional desde hojas | O(n) |
| **Visualizar** | Representación ASCII del árbol | O(n) |

*h = altura del árbol, n = número de nodos*

<p align="right">(<a href="#readme-top">Volver arriba ↑</a>)</p>

---

<h2 id="instalacion">⚙️ Instalación</h2>

### Compilar y ejecutar

1. Clona el repositorio:
```bash
git clone https://github.com/HustavoJhon/abb-mitologia.git
cd abb-mitologia
```

2. Compila el programa:
```bash
g++ prototipo.cpp -o main
# o
c++ prototipo.cpp -o main
```

3. Ejecuta:
```bash
./main
```

### Menú Interactivo
```
MENU:
1. Insertar       → Agregar nuevo miembro
2. Buscar         → Buscar por año+mes
3. Eliminar       → Eliminar miembro
4. Inorden        → Ver lista cronológica
5. Preorden       → Ver jerarquía
6. Postorden      → Ver generaciones
7. Ver árbol      → Visualización ASCII
0. Salir          → Terminar programa
```

<p align="right">(<a href="#readme-top">Volver arriba ↑</a>)</p>

---

<h2 id="datos-mitologicos">🏛️ Datos Mitológicos Precargados</h2>
```
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

### Jerarquía Mitológica

- **Primigenios:** Ouranos (Padre Cielo) - Los seres más antiguos
- **Titanes:** Cronos, Oceano, Rea - Segunda generación divina
- **Olímpicos:** Zeus, Hera, Atenea, Apolo - Dioses del Olimpo
- **Héroes:** Heracles, Perseo, Teseo - Semidioses mortales

<p align="right">(<a href="#readme-top">Volver arriba ↑</a>)</p>

---

<h2 id="integrantes">👥 Integrantes</h2>

| Nombre | Rol | GitHub |
|--------|------|--------|
| **Jhon Gustavo Ccarita Velasquez** | Líder de Proyecto, Desarrollo Backend | <a href="https://github.com/HustavoJhon"><img src="https://img.shields.io/badge/GitHub-181717?style=flat&logo=github&logoColor=white"></a> |
| **Rodrigo Sevillanos Tinco** | Implementación de Operaciones ABB | <a href="https://github.com/C3b1taz"><img src="https://img.shields.io/badge/GitHub-181717?style=flat&logo=github&logoColor=white"></a> |
| **Andre Sebastian Espinosa Zea** | Documentación y Diagramas | <a href="https://github.com/BLUESKY211206"><img src="https://img.shields.io/badge/GitHub-181717?style=flat&logo=github&logoColor=white"></a> |

### 📚 Información del Curso

- **Curso:** Estructura de Datos
- **Docente:** Yesenia Concha Ramos
- **NRC:** 59008
- **Periodo:** 2025-02
- **Universidad:** Universidad Continental - Cusco, Perú

<p align="right">(<a href="#readme-top">Volver arriba ↑</a>)</p>

---

<h2 id="licencia">📄 Licencia</h2>

Distribuido bajo la licencia **MIT**.  
Consulta el archivo <a href="LICENSE">LICENSE</a> para más información.

<p align="center">
  <br>
  <img src="./assets/logos/Ucontinental-logotipo.png" alt="footer" width="120"><br>
  <sub>© 2025 ABB Mitológico - Proyecto Universitario de Estructura de Datos</sub>
</p>

<p align="right">(<a href="#readme-top">Volver arriba ↑</a>)</p>