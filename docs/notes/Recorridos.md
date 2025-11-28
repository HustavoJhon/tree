## INORDEN
```cpp
void inorden(Nodo *r) {
	if (r) {
		inorden(r->izq);
		cout << r->nombre << " (" << r->anio << "-" << r->mes << ") - " << r->rol
		<< endl;
	inorden(r->der);
	}
}
```
El recorrido **inorden** es una función recursiva que visita los nodos de un **Árbol Binario de Búsqueda (ABB)** en el orden:
### 👉 Izquierda → Raíz → Derecha

Este orden **garantiza que los datos se impriman ordenados de menor a mayor**, según la clave del ABB.

### 🟩 ¿Qué hace cada parte del código?

`void inorden(Nodo *r) {   if (r) {`
- Si el nodo actual (`r`) no es nulo, continúa.
- Si es nulo, no hace nada (caso base de la recursión).

    `inorden(r->izq);`
### 📌 Paso 1: Recorrer el subárbol izquierdo

Se llama a sí misma sobre el hijo izquierdo.  
En un ABB, **los nodos menores están a la izquierda**, así que se visitan primero.

    `cout << r->nombre << " (" << r->anio << "-" << r->mes << ") - " << r->rol          << endl;`

### 📌 Paso 2: Procesar la raíz
Una vez completado todo el subárbol izquierdo, se imprime el nodo actual (nombre, año, mes y rol).

    `inorden(r->der);`
### 📌 Paso 3: Recorrer el subárbol derecho
Finalmente visita el lado derecho del nodo actual, donde están los valores mayores.


## PREORDEN 
```cpp
void preorden(Nodo *r) {
	if (r) {
		cout << r->nombre << " (" << r->anio << "-" << r->mes << ") - " << r->rol
		<< endl;
		preorden(r->izq);
		preorden(r->der);
	}
}
```
El recorrido **preorden** visita los nodos del árbol en este orden:

### 👉 Raíz → Izquierda → Derecha

Este recorrido es útil para **mostrar la estructura jerárquica del árbol**, empezando siempre por el nodo actual antes que sus hijos.
### 🟩 ¿Qué hace cada parte del código?

`void preorden(Nodo *r) {   if (r) {`
- Verifica que el nodo no sea nulo.
- Si es nulo, no hace nada (caso base de recursión).

    `cout << r->nombre << " (" << r->anio << "-" << r->mes << ") - " << r->rol          << endl;`

### 📌 Paso 1: Procesar la raíz

Se imprime **primero** el contenido del nodo actual (nombre, fecha y rol).  
Esto define la característica principal del recorrido preorden.

    `preorden(r->izq);`
### 📌 Paso 2: Recorrer subárbol izquierdo

Luego llama recursivamente al hijo izquierdo.  
Se visita toda la rama izquierda antes de pasar a la derecha.

    `preorden(r->der);`
### 📌 Paso 3: Recorrer subárbol derecho

Finalmente recorre todos los nodos del lado derecho.
## POSTORDEN

```cpp
void postorden(Nodo *r) {
	if (r) {
		postorden(r->izq);
		postorden(r->der);
		cout << r->nombre << " (" << r->anio << "-" << r->mes << ") - " << r->rol
		<< endl;
	}
}
```
El recorrido **postorden** visita los nodos en este orden:
### 👉 Izquierda → Derecha → Raíz

Es un recorrido donde **los hijos se procesan primero** y el nodo padre al final.  
Es muy útil para eliminar árboles o analizar descendencias completas.
### 🟩 ¿Qué hace cada parte del código?

`void postorden(Nodo *r) {   if (r) {`
### 📌 Verificación inicial
Si el puntero del nodo es NULL, ya no hay nada que procesar.  
Esto marca el **caso base** de la recursión.
    `postorden(r->izq);`
### 📌 Paso 1: Recorrer subárbol izquierdo
Primero se procesa **toda la rama izquierda**, hasta llegar a los nodos más profundos.
    
    `postorden(r->der);`
### 📌 Paso 2: Recorrer subárbol derecho
Después se recorre completamente el subárbol derecho.

---

    `cout << r->nombre << " (" << r->anio << "-" << r->mes << ") - " << r->rol          << endl;`

### 📌 Paso 3: Procesar la raíz (al final)

El nodo actual se imprime **después** de que sus dos hijos ya fueron procesados.

Este comportamiento lo distingue de inorden y preorden.