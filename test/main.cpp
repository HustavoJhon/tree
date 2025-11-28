#include <iostream>
#include <string>
using namespace std;

struct Nodo {
  int anio;
  int mes;
  int clave;     // Clave única = anio*100 + mes
  string nombre; // Nombre del personaje
  string rol;    // Olimpo, Titán, héroe, etc.
  Nodo *izq;     // Subárbol izquierdo
  Nodo *der;     // Subárbol derecho

  // Constructor del nodo
  Nodo(int a, int m, const string &nom, const string &r) {
    anio = a;
    mes = m;
    clave = a * 100 + m;
    nombre = nom;
    rol = r;
    izq = NULL;
    der = NULL;
  }
};

// PROTOTIPOS
Nodo *insertar(Nodo *raiz, int anio, int mes, const string &nombre,
               const string &rol);
Nodo *eliminarMiembro(Nodo *raiz, int anio, int mes);
Nodo *buscarExacto(Nodo *raiz, int anio, int mes);
Nodo *minimo(Nodo *nodo);
void inorden(Nodo *raiz);
void preorden(Nodo *raiz);
void postorden(Nodo *raiz);
void imprimirArbolAscii(Nodo *raiz, string prefix, bool esUltimo);
bool leerIntRango(const string &prompt, int &valor, int minVal, int maxVal);

//  INSERTAR
/*
 Inserta un nuevo miembro en el ABB según la clave anio*100 + mes.
 Si la raíz es NULL, crea un nuevo nodo.
 Si la clave es menor va a la izquierda, si es mayor va a la derecha.
 Si la clave ya existe, muestra un aviso.
*/
Nodo *insertar(Nodo *raiz, int anio, int mes, const string &nombre,
               const string &rol) {
  int clave = anio * 100 + mes;

  // Caso base: insertar en árbol vacío
  if (raiz == NULL) {
    return new Nodo(anio, mes, nombre, rol);
  }

  // Inserción recursiva en izquierda o derecha
  if (clave < raiz->clave) {
    raiz->izq = insertar(raiz->izq, anio, mes, nombre, rol);
  } else if (clave > raiz->clave) {
    raiz->der = insertar(raiz->der, anio, mes, nombre, rol);
  } else {
    cout << "Aviso: ya existe un miembro con ese anio y mes.\n";
  }

  return raiz;
}

//  BUSCAR
/*
 Busca un nodo exacto en el ABB según su clave.
 Retorna un puntero al nodo o NULL si no existe.
*/
Nodo *buscarExacto(Nodo *raiz, int anio, int mes) {
  int clave = anio * 100 + mes;

  if (raiz == NULL)
    return NULL;

  if (clave == raiz->clave)
    return raiz;

  if (clave < raiz->clave)
    return buscarExacto(raiz->izq, anio, mes);

  return buscarExacto(raiz->der, anio, mes);
}

//  MÍNIMO
/*
 Encuentra el nodo con la clave mínima.
 Se usa para encontrar el sucesor al eliminar un nodo.
*/
Nodo *minimo(Nodo *nodo) {
  while (nodo != NULL && nodo->izq != NULL)
    nodo = nodo->izq;
  return nodo;
}

//  ELIMINAR
/*
 Elimina un nodo del ABB respetando las reglas:
 - Caso 1: nodo sin hijos → se elimina directamente.
 - Caso 2: nodo con un hijo → se reemplaza por ese hijo.
 - Caso 3: nodo con dos hijos → se reemplaza con su sucesor inorden.
*/
Nodo *eliminarMiembro(Nodo *raiz, int anio, int mes) {
  if (raiz == NULL)
    return raiz;

  int clave = anio * 100 + mes;

  // Buscar nodo a eliminar
  if (clave < raiz->clave) {
    raiz->izq = eliminarMiembro(raiz->izq, anio, mes);
  } else if (clave > raiz->clave) {
    raiz->der = eliminarMiembro(raiz->der, anio, mes);
  } else {
    // Nodo encontrado: manejar casos de eliminación

    // Caso 1: sin hijo izquierdo
    if (raiz->izq == NULL) {
      Nodo *temp = raiz->der;
      delete raiz;
      return temp;
    }

    // Caso 2: sin hijo derecho
    else if (raiz->der == NULL) {
      Nodo *temp = raiz->izq;
      delete raiz;
      return temp;
    }

    // Caso 3: dos hijos → tomar sucesor
    Nodo *suc = minimo(raiz->der);

    // Copiar datos del sucesor
    raiz->anio = suc->anio;
    raiz->mes = suc->mes;
    raiz->clave = suc->clave;
    raiz->nombre = suc->nombre;
    raiz->rol = suc->rol;

    // Eliminar sucesor
    raiz->der = eliminarMiembro(raiz->der, suc->anio, suc->mes);
  }

  return raiz;
}

//  RECORRIDOS
/*
 Imprime árbol en INORDEN (izq - raíz - der)
 Muestra miembros ordenados por fecha.
*/
void inorden(Nodo *raiz) {
  if (raiz) {
    inorden(raiz->izq);
    cout << raiz->nombre << " (" << raiz->anio << "-" << raiz->mes << ") - "
         << raiz->rol << endl;
    inorden(raiz->der);
  }
}

/*
 PREORDEN (raíz - izq - der)
*/
void preorden(Nodo *raiz) {
  if (raiz) {
    cout << raiz->nombre << " (" << raiz->anio << "-" << raiz->mes << ") - "
         << raiz->rol << endl;
    preorden(raiz->izq);
    preorden(raiz->der);
  }
}

/*
 POSTORDEN (izq - der - raíz)
*/
void postorden(Nodo *raiz) {
  if (raiz) {
    postorden(raiz->izq);
    postorden(raiz->der);
    cout << raiz->nombre << " (" << raiz->anio << "-" << raiz->mes << ") - "
         << raiz->rol << endl;
  }
}

//  ASCII TREE
/*
 Imprime el árbol de forma visual tipo diagrama.
 prefix → conforma el "nivel" visual
 esUltimo → decide entre └── o ├──
*/
void imprimirArbolAscii(Nodo *raiz, string prefix, bool esUltimo) {
  if (raiz == NULL)
    return;

  cout << prefix;
  cout << (esUltimo ? "└── " : "├── ");
  cout << raiz->nombre << " [" << raiz->anio << "-" << raiz->mes << "] ("
       << raiz->rol << ")\n";

  string nuevoPrefix = prefix + (esUltimo ? "    " : "│   ");

  if (raiz->izq != NULL && raiz->der != NULL) {
    imprimirArbolAscii(raiz->izq, nuevoPrefix, false);
    imprimirArbolAscii(raiz->der, nuevoPrefix, true);
  } else if (raiz->izq != NULL) {
    imprimirArbolAscii(raiz->izq, nuevoPrefix, true);
  } else if (raiz->der != NULL) {
    imprimirArbolAscii(raiz->der, nuevoPrefix, true);
  }
}

//  VALIDACIÓN
/*
 Lee un entero validado dentro de un rango específico.
 Solo acepta dígitos.
*/
bool leerIntRango(const string &prompt, int &valor, int minVal, int maxVal) {
  string linea;
  while (true) {
    cout << prompt;
    cin >> linea;

    // Validar solo números
    bool ok = true;
    for (char c : linea)
      if (!isdigit(c))
        ok = false;

    if (!ok) {
      cout << "Entrada invalida. Solo digitos.\n";
      continue;
    }

    valor = stoi(linea);

    if (valor < minVal || valor > maxVal) {
      cout << "Fuera de rango.\n";
      continue;
    }

    return true;
  }
}

//  CARGAR MITOLOGÍA
/*
 Inserta 15 dioses/héroes/titanes predefinidos para comenzar con un árbol
 grande.
*/
Nodo *cargarMitologia(Nodo *raiz) {
  raiz = insertar(raiz, 10, 6, "Zeus", "Rey Olimpico"); // raíz inicial

  // Subárbol izquierdo
  raiz = insertar(raiz, 5, 3, "Cronos", "Titan");
  raiz = insertar(raiz, 3, 2, "Oceano", "Titan");
  raiz = insertar(raiz, 2, 1, "Ouranos", "Primigenio");
  raiz = insertar(raiz, 4, 5, "Rea", "Titanide");
  raiz = insertar(raiz, 7, 8, "Hades", "Olimpico");
  raiz = insertar(raiz, 6, 4, "Hestia", "Olimpica");
  raiz = insertar(raiz, 8, 9, "Poseidon", "Olimpico");

  // Subárbol derecho
  raiz = insertar(raiz, 15, 7, "Atenea", "Olimpica");
  raiz = insertar(raiz, 13, 2, "Apolo", "Olimpico");
  raiz = insertar(raiz, 12, 1, "Artemisa", "Olimpica");
  raiz = insertar(raiz, 14, 5, "Hermes", "Olimpico");
  raiz = insertar(raiz, 18, 3, "Heracles", "Heroe");
  raiz = insertar(raiz, 17, 9, "Perseo", "Heroe");
  raiz = insertar(raiz, 20, 4, "Teseo", "Heroe");

  return raiz;
}

//  PROGRAMA PRINCIPAL
int main() {
  Nodo *raiz = NULL;

  // Carga inicial de 15 personajes
  raiz = cargarMitologia(raiz);

  cout << "\n=== Arbol genealógico mitológico cargado (15 miembros) ===\n\n";
  imprimirArbolAscii(raiz, "", true);

  int opcion;

  // Menú principal
  do {
    cout << "\nMENU:\n";
    cout << "1. Insertar\n";
    cout << "2. Buscar (anio+mes)\n";
    cout << "3. Eliminar\n";
    cout << "4. Inorden\n";
    cout << "5. Preorden\n";
    cout << "6. Postorden\n";
    cout << "7. Ver arbol\n";
    cout << "0. Salir\n";
    cout << "Opcion: ";
    cin >> opcion;

    if (opcion == 1) {
      int a, m;
      string nombre, rol;

      leerIntRango("Anio: ", a, 0, 9999);
      leerIntRango("Mes (1-12): ", m, 1, 12);

      cin.ignore();
      cout << "Nombre: ";
      getline(cin, nombre);
      cout << "Rol: ";
      getline(cin, rol);

      raiz = insertar(raiz, a, m, nombre, rol);

      cout << "\n";
      imprimirArbolAscii(raiz, "", true);
    }

    else if (opcion == 2) {
      int a, m;
      leerIntRango("Anio: ", a, 0, 9999);
      leerIntRango("Mes: ", m, 1, 12);

      Nodo *r = buscarExacto(raiz, a, m);
      if (r)
        cout << "Encontrado: " << r->nombre << "\n";
      else
        cout << "No existe.\n";
    }

    else if (opcion == 3) {
      int a, m;
      leerIntRango("Anio: ", a, 0, 9999);
      leerIntRango("Mes: ", m, 1, 12);

      raiz = eliminarMiembro(raiz, a, m);

      cout << "\n";
      imprimirArbolAscii(raiz, "", true);
    }

    else if (opcion == 4)
      inorden(raiz);

    else if (opcion == 5)
      preorden(raiz);

    else if (opcion == 6)
      postorden(raiz);

    else if (opcion == 7) {
      cout << "\n";
      imprimirArbolAscii(raiz, "", true);
    }

  } while (opcion != 0);

  return 0;
}
