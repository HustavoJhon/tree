# **1. DESCRIPCIÓN TÉCNICA DETALLADA (EN MARKDOWN, POR SECCIONES)**

## **🔹 Manejo de entradas y validaciones**

- `convertirEntero`: Implementa manualmente la conversión de una cadena de dígitos a entero sin usar `atoi`.
- `esNumero`: Verifica si una cadena contiene únicamente caracteres numéricos.
- `aMinuscula` / `aMayuscula`: Implementaciones manuales para cambiar mayúsculas y minúsculas sin usar `<cctype>`.
- `capitalizar`: Convierte la primera letra de cada palabra a mayúscula y el resto a minúsculas.
- `trim`: Elimina espacios al inicio y final de una cadena.
- `esVacia`: Comprueba si una cadena está vacía o contiene solo espacios.
- `esBisiesto`: Determina si un año es bisiesto según las reglas del calendario gregoriano.
- `mesValido`: Verifica que el mes esté dentro del rango 1–12 ajustando febrero si el año es bisiesto.
- `leerIntRango`, `leerAnio`, `leerMes`, `leerTextoNoVacio`: Implementan validaciones para la entrada del usuario, asegurando que los datos sean válidos antes de insertarlos al árbol.

---

## **🔹 Estructura del nodo y árbol**

- `struct Nodo`: Define la estructura básica del ABB.  
   Contiene año, mes, clave (año\*100+mes), nombre capitalizado, rol capitalizado y punteros izquierdo/derecho.
- Constructor del nodo: Inicializa los valores y aplica capitalización a cadenas.

---

## **🔹 Operaciones fundamentales del Árbol Binario de Búsqueda**

### **Insertar**

`insertar()`:

- Calcula la clave única.
- Inserta ordenadamente en el ABB.
- Evita duplicados mostrando mensaje si ya existe un nodo con la misma fecha.

### **Buscar**

`buscarExacto()`:

- Busca similitud exacta de clave navegando recursivamente.

### **Eliminar**

`eliminarMiembro()`:

- Maneja los 3 casos clásicos:
  1. Nodo sin hijos.
  2. Nodo con un hijo.
  3. Nodo con dos hijos → reemplazo por sucesor inorden.
- Muestra mensajes al eliminar.

### **Mínimo**

`minimo()`:

- Obtiene el nodo más pequeño de un subárbol (el más a la izquierda).

---

## **🔹 Recorridos del árbol**

- `inorden()`: Izquierda – raíz – derecha (orden cronológico).
- `preorden()`: Raíz – izquierda – derecha (estructura jerárquica).
- `postorden()`: Izquierda – derecha – raíz (procesamiento completo).

---

## **🔹 Impresión visual del árbol en ASCII**

`imprimirArbolAscii()`:

- Representa el árbol con líneas ASCII estilo directorio:
  - `|--` para nodos intermedios
  - ``--` para últimos nodos
- Muestra claramente ramas, hojas y jerarquía.

---

## **🔹 Datos pre-cargados**

`cargarMitologia()`:

- Inserta automáticamente 15 personajes míticos (dioses, titanes y héroes).
- Garantiza que el árbol tenga suficiente volumen para pruebas y visualización.

---

## **🔹 Menú principal**

- Muestra opciones del sistema.
- Permite insertar, buscar, eliminar, recorrer y visualizar el árbol completo.
- Cada operación incluye:
  - Lectura validada de datos
  - Misajes descriptivos
  - Visualización actualizada del ABB

