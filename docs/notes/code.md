## struct Nodo

```cpp
struct Nodo {
	int anio;
	int mes;
	int clave;
	string nombre;
	string rol;
	Nodo *izq;
	Nodo *der;
	Nodo(int a, int m, const string &nom, const string &r) {
		anio = a;
		mes = m;
		clave = a * 100 + m;
		nombre = capitalizar(nom); // Capitalizar al crear nodo
		rol = capitalizar(r); // Capitalizar al crear nodo
		izq = NULL;
		der = NULL;
	}
};
```
El bloque define la estructura **Nodo**, que representa la unidad básica del Árbol Binario de Búsqueda (ABB). Cada nodo almacena información del personaje mitológico y, además, mantiene enlaces hacia sus hijos izquierdo y derecho, lo que permite construir la estructura jerárquica del árbol.

Los atributos `anio` y `mes` registran la fecha simbólica del personaje. A partir de ambos se genera la propiedad `clave`, calculada como `anio * 100 + mes`, que permite obtener un identificador numérico único y ordenable. Esta clave es esencial porque determina la posición de cada nodo dentro del ABB, garantizando que todos los registros mantengan un orden estricto y que operaciones como insertar, buscar y eliminar sean eficientes.

Los campos `nombre` y `rol` almacenan los datos textuales del personaje. Ambos se normalizan mediante la función `capitalizar()`, de modo que el registro mantenga un formato uniforme sin importar cómo lo ingrese el usuario. Esto mejora la calidad y legibilidad de los datos almacenados.

Los punteros `izq` y `der` representan las conexiones hacia los subárboles izquierdo y derecho. El subárbol izquierdo contiene nodos con claves menores, y el derecho nodos con claves mayores, manteniendo la propiedad fundamental del ABB. Inicialmente se asignan como `NULL` para indicar que el nodo recién creado no tiene hijos.

El constructor del nodo se encarga de inicializar correctamente todos los campos, calcular la clave, normalizar las cadenas y dejar preparados los punteros. Esto garantiza que cada nodo esté listo para integrarse en el árbol sin inconsistencias ni datos inválidos.

## Prototipos
```cpp
Nodo *insertar(Nodo *raiz, int anio, int mes, const string &nombre,
const string &rol);
Nodo *buscarExacto(Nodo *raiz, int anio, int mes);
Nodo *eliminarMiembro(Nodo *raiz, int anio, int mes);
Nodo *minimo(Nodo *n);
void inorden(Nodo *r);
void preorden(Nodo *r);
void postorden(Nodo *r);
void imprimirArbolAscii(Nodo *r, string pref, bool esUltimo);
bool leerIntRango(const string &msg, int &valor, int minVal, int maxVal);
bool leerAnio(int &anio);
bool leerMes(int &mes, int anio);
bool leerTextoNoVacio(const string &msg, string &texto);
```
Este bloque declara las funciones principales que manipulan y gestionan el Árbol Binario de Búsqueda (ABB). Al ubicarlas como prototipos, el compilador conoce su existencia antes de que aparezcan sus definiciones, permitiendo una organización estructurada del código.

Las funciones `insertar`, `buscarExacto`, `eliminarMiembro` y `minimo` conforman el núcleo lógico del ABB, encargándose de mantener su estructura y propiedades
- **`insertar`** define cómo se incorpora un nuevo nodo comparando la clave generada con las existentes, preservando la organización por fechas.
- **`buscarExacto`** realiza una búsqueda recursiva optimizada gracias al orden del ABB, permitiendo localizar rápidamente un nodo por su año y mes.
- **`eliminarMiembro`** gestiona la eliminación respetando los tres casos fundamentales (hoja, nodo con un hijo, nodo con dos hijos) y reestructura el árbol para mantener su validez.
- **`minimo`** localiza el nodo con la clave más baja en un subárbol, siendo indispensable al aplicar la eliminación con reemplazo por sucesor inorden.

Los métodos `inorden`, `preorden` y `postorden` implementan los recorridos clásicos, esenciales tanto para visualizar el contenido del ABB como para construir funcionalidades de análisis temporal, jerárquico o generacional. Cada uno sigue un orden distinto de visita de nodos, lo que permite observar el árbol desde perspectivas específicas.

La función `imprimirArbolAscii` genera una representación visual del árbol en formato de texto, construyendo un diagrama jerárquico mediante prefijos y símbolos que muestran la estructura real del ABB. Su objetivo es ayudar al usuario a comprender la forma del árbol sin necesidad de herramientas gráficas externas.

Finalmente, las funciones `leerIntRango`, `leerAnio`, `leerMes` y `leerTextoNoVacio` encapsulan la validación de entradas del usuario. Garantizan que los datos ingresados sean numéricos, estén dentro de rangos válidos y que textos como nombres o roles no estén vacíos. Estas funciones protegen al programa contra errores de entrada y aseguran la integridad de los datos almacenados en el árbol.


## Insertar
```cpp
Nodo *insertar(Nodo *raiz, int anio, int mes, const string &nombre, const string &rol) {
	int clave = anio * 100 + mes;
	if (raiz == NULL) {
		return new Nodo(anio, mes, nombre, rol);
	}
	if (clave < raiz->clave)
		raiz->izq = insertar(raiz->izq, anio, mes, nombre, rol);
	else if (clave > raiz->clave)
		raiz->der = insertar(raiz->der, anio, mes, nombre, rol);
	else {
		cout << "\n*** AVISO: Ya existe un miembro con fecha " << anio << "-" << mes
		<< " ***\n";
		cout << "Miembro existente: " << raiz->nombre << " (" << raiz->rol << ")\n";
	}
	return raiz;
}
```
La función `insertar` implementa la operación fundamental de construcción del Árbol Binario de Búsqueda. Primero genera la clave única combinando año y mes, lo que garantiza orden cronológico en el árbol. Si la raíz es nula, crea un nuevo nodo, actuando como caso base de la recursión. Cuando el nodo actual existe, compara la clave ingresada con la clave almacenada: si es menor, continúa la inserción por el subárbol izquierdo; si es mayor, por el derecho. Esto mantiene la propiedad estructural del ABB, asegurando búsquedas eficientes en futuras operaciones. Si la clave coincide exactamente con la de un nodo existente, se detecta un duplicado y no se inserta nada, preservando la integridad del árbol y evitando ambigüedades. Finalmente, la función retorna la raíz actual para reconstruir correctamente los enlaces a medida que la recursión retrocede.
## Buscar
```cpp
Nodo *buscarExacto(Nodo *raiz, int anio, int mes) {
	int clave = anio * 100 + mes;
	if (raiz == NULL)
		return NULL;
	if (clave == raiz->clave)
		return raiz;
	if (clave < raiz->clave)
		return buscarExacto(raiz->izq, anio, mes);
	else
		return buscarExacto(raiz->der, anio, mes);
}
```
La función `buscarExacto` realiza una búsqueda recursiva dentro del Árbol Binario de Búsqueda empleando como criterio la clave generada por año y mes. Primero calcula la clave buscada y compara: si el nodo actual es nulo, significa que el recorrido llegó al final sin encontrar coincidencias, por lo que devuelve `NULL`. Si la clave coincide exactamente con la del nodo actual, retorna dicho nodo como resultado de la búsqueda. En caso contrario, aplica la propiedad fundamental del ABB: si la clave solicitada es menor, continúa la búsqueda descendiendo por el subárbol izquierdo; si es mayor, por el derecho. Esta toma de decisiones reduce el espacio de búsqueda en cada llamada, garantizando un tiempo de búsqueda proporcional a la altura del árbol y haciendo la operación eficiente incluso con grandes cantidades de datos.
## Eliminar
```cpp
Nodo *eliminarMiembro(Nodo *raiz, int anio, int mes) {
	if (raiz == NULL) {
		cout << "\n*** El miembro no existe en el arbol ***\n";
		return raiz;
	}
	int clave = anio * 100 + mes;
	if (clave < raiz->clave) {
		raiz->izq = eliminarMiembro(raiz->izq, anio, mes);
	} else if (clave > raiz->clave) {
		raiz->der = eliminarMiembro(raiz->der, anio, mes);
	} else {
		// Nodo encontrado
		cout << "\n*** Eliminando: " << raiz->nombre << " ***\n";
	if (raiz->izq == NULL) {
		Nodo *temp = raiz->der;
		delete raiz;
		return temp;
	} else if (raiz->der == NULL) {
		Nodo *temp = raiz->izq;
		delete raiz;
		return temp;
	}
	// Nodo con dos hijos: obtener sucesor inorden
	Nodo *suc = minimo(raiz->der);
	raiz->anio = suc->anio;
	raiz->mes = suc->mes;
	raiz->clave = suc->clave;
	raiz->nombre = suc->nombre;
	raiz->rol = suc->rol;
	raiz->der = eliminarMiembro(raiz->der, suc->anio, suc->mes);
	}
	return raiz;
}
```
La función `eliminarMiembro` implementa la eliminación de nodos en un Árbol Binario de Búsqueda respetando todas sus reglas estructurales. Primero verifica si el árbol está vacío; si lo está, retorna sin cambios. Luego calcula la clave del nodo objetivo y aplica búsqueda recursiva: si la clave es menor o mayor que la del nodo actual, continúa por el subárbol correspondiente para localizarlo. Cuando encuentra el nodo a eliminar, maneja tres escenarios clásicos. Si el nodo no tiene hijo izquierdo, se reemplaza directamente por su subárbol derecho; si no tiene hijo derecho, se reemplaza por el subárbol izquierdo. En el caso más complejo—cuando posee ambos hijos—localiza el sucesor inorden mediante la función `minimo` (el nodo más pequeño del subárbol derecho), copia sus datos en el nodo actual y luego elimina el sucesor mediante una llamada recursiva. Este procedimiento garantiza que la propiedad de orden del ABB se conserve mientras se libera correctamente la memoria del nodo eliminado.
### ¿Qué hace esta parte cuando el nodo tiene dos hijos?
Cuando un nodo tiene **dos hijos**, no se puede eliminar directamente porque rompería el orden del ABB.  
Por eso se usa un truco estándar:
### 👉 PASO 1: Encontrar el sucesor inorden
`Nodo *suc = minimo(raiz->der);`
El **sucesor inorden** es el nodo con el valor más pequeño del subárbol derecho.  
Ese nodo es el siguiente en la secuencia ordenada del ABB, por eso **es perfecto para reemplazar al nodo que queremos eliminar**.

---
### 👉 PASO 2: Copiar los datos del sucesor al nodo actual

`raiz->anio = suc->anio; raiz->mes = suc->mes; raiz->clave = suc->clave; raiz->nombre = suc->nombre; raiz->rol = suc->rol;`
En lugar de mover nodos en memoria (lo que complicaría los punteros), simplemente **copiamos la información** del sucesor al nodo que queremos eliminar.
Así, desde fuera, se ve como si el sucesor hubiese “subido” al lugar del nodo eliminado.

---
### 👉 PASO 3: Eliminar el nodo sucesor (que ahora es duplicado)

`raiz->der = eliminarMiembro(raiz->der, suc->anio, suc->mes);`

Una vez copiados los datos:
- el nodo sucesor sigue existiendo más abajo en el árbol,
- ahora se debe eliminar ese nodo duplicado.
Pero ese nodo _siempre_ tendrá **0 o 1 hijo**, así que su eliminación es simple.

## Imprimir Arbol
```cpp
void imprimirArbolAscii(Nodo *r, string pref, bool esUltimo) {
	if (r == NULL)
		return;
		cout << pref;
	if (esUltimo)
		cout << "`-- ";
	else
		cout << "|-- ";
		cout << r->nombre << " [" << r->anio << "-" << r->mes << "] (" << r->rol
		<< ")\n";
		string nuevoPref = pref + (esUltimo ? " " : "| ");
	if (r->izq != NULL && r->der != NULL) {
		imprimirArbolAscii(r->izq, nuevoPref, false);
		imprimirArbolAscii(r->der, nuevoPref, true);
	} else if (r->izq != NULL) {
		imprimirArbolAscii(r->izq, nuevoPref, true);
	} else if (r->der != NULL) {
		imprimirArbolAscii(r->der, nuevoPref, true);
	}
}
```
Este procedimiento imprime el árbol binario en formato **ASCII**, donde la raíz aparece arriba y sus ramas se dibujan hacia abajo usando símbolos como:

- `|--` para nodos intermedios
    
- `` `--` `` para el último nodo de un nivel
    
- Espacios y barras `|` para marcar la estructura vertical
    

El objetivo es permitir visualizar fácilmente cómo están organizados los nodos del árbol sin usar gráficos complejos.

---

## 🟩 ¿Qué hace cada línea de este bloque?

`if (r == NULL)     return;`

✔ Si el nodo es NULL, no hay nada más que imprimir.  
✔ Es el caso base de la recursión.

---

`cout << pref;`

✔ Imprime los espacios y barras necesarios para mantener la alineación del árbol.  
✔ `pref` contiene `"| "` o `" "` dependiendo de si el nodo era el último en su nivel.

---

``if (esUltimo)     cout << "`-- "; else     cout << "|-- ";``

✔ Dibuja el conector del nodo actual.  
✔ `` `-- `` señala que este nodo es el **último** de su nivel.  
✔ `|--` indica que todavía existen más nodos hermanos.

---

`cout << r->nombre << " [" << r->anio << "-" << r->mes << "] (" << r->rol << ")\n";`

✔ Imprime la información del nodo: nombre, fecha y rol.  
✔ Esto es lo que se verá como el valor del nodo en el árbol ASCII.

---

`string nuevoPref = pref + (esUltimo ? "    " : "|   ");`

✔ Construye el prefijo que usarán los hijos de este nodo.  
✔ Si es el último hijo → agrega espacios `" "`  
✔ Si no lo es → agrega una barra `"| "`

Esto conserva la estructura visual del árbol al bajar de nivel.

---

### 🟪 Llamadas recursivas

`if (r->izq != NULL && r->der != NULL) {     imprimirArbolAscii(r->izq, nuevoPref, false);     imprimirArbolAscii(r->der, nuevoPref, true); }`

✔ Si tiene ambos hijos, primero imprime el izquierdo y luego el derecho.  
✔ El derecho siempre se marca como "último".

---

`else if (r->izq != NULL) {     imprimirArbolAscii(r->izq, nuevoPref, true); }`

✔ Solo existe hijo izquierdo → se imprime como último.

---

`else if (r->der != NULL) {     imprimirArbolAscii(r->der, nuevoPref, true); }`

✔ Solo hijo derecho → también es último.