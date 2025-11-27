#include <iostream>
#include <string>
using namespace std;

/*
  Estructura de un nodo del Árbol Binario de Búsqueda (ABB).
  Cada nodo representa un ser de la mitología griega,
  almacenado de acuerdo a su año simbólico de nacimiento.
*/
struct Nodo {
  int nacimiento; // Clave del nodo: año simbólico
  string nombre;  // Nombre del ser mitológico
  string rol;     // Rol dentro de la mitología

  Nodo *izq; // Hijo izquierdo
  Nodo *der; // Hijo derecho

  // Constructor que inicializa un nodo
  Nodo(int n, string nom, string r) {
    nacimiento = n;
    nombre = nom;
    rol = r;
    izq = NULL;
    der = NULL;
  }
};

/*
  Función insertar:
  Inserta un nuevo nodo en el ABB respetando el orden.
  Si el valor ya existe, no se inserta.
*/
Nodo *insertar(Nodo *raiz, int nacimiento, string nombre, string rol) {
  if (raiz == NULL) {
    return new Nodo(nacimiento, nombre, rol);
  }

  // Inserción recursiva siguiendo la regla del ABB
  if (nacimiento < raiz->nacimiento) {
    raiz->izq = insertar(raiz->izq, nacimiento, nombre, rol);
  } else if (nacimiento > raiz->nacimiento) {
    raiz->der = insertar(raiz->der, nacimiento, nombre, rol);
  } else {
    // Valor duplicado: no se debe insertar
    cout << "Ya existe un miembro con ese año.\n";
  }

  return raiz;
}

/*
  Función buscar:
  Retorna el nodo cuya clave coincide con "nacimiento".
  Si no existe, retorna NULL.
*/
Nodo *buscar(Nodo *raiz, int nacimiento) {
  if (raiz == NULL || raiz->nacimiento == nacimiento)
    return raiz;

  if (nacimiento < raiz->nacimiento)
    return buscar(raiz->izq, nacimiento);
  else
    return buscar(raiz->der, nacimiento);
}

/*
  Recorrido Inorden:
  Muestra los nodos en orden ascendente según año simbólico.
*/
void inorden(Nodo *raiz) {
  if (raiz != NULL) {
    inorden(raiz->izq);
    cout << raiz->nombre << " (" << raiz->nacimiento << ") - " << raiz->rol
         << endl;
    inorden(raiz->der);
  }
}

/*
  Recorrido Preorden:
  Muestra primero la raíz y luego los hijos.
  Útil para observar jerarquías.
*/
void preorden(Nodo *raiz) {
  if (raiz != NULL) {
    cout << raiz->nombre << " (" << raiz->nacimiento << ") - " << raiz->rol
         << endl;
    preorden(raiz->izq);
    preorden(raiz->der);
  }
}

/*
  Recorrido Postorden:
  Muestra primero los hijos y al final la raíz.
  Útil para analizar descendencia completa.
*/
void postorden(Nodo *raiz) {
  if (raiz != NULL) {
    postorden(raiz->izq);
    postorden(raiz->der);
    cout << raiz->nombre << " (" << raiz->nacimiento << ") - " << raiz->rol
         << endl;
  }
}

/*
  Función minimo:
  Encuentra el nodo más pequeño dentro de un subárbol.
  Se usa para eliminar nodos con dos hijos.
*/
Nodo *minimo(Nodo *nodo) {
  while (nodo != NULL && nodo->izq != NULL)
    nodo = nodo->izq;
  return nodo;
}

/*
  Función eliminarMiembro:
  Elimina un nodo del ABB manteniendo la estructura.
  Considera los tres casos: sin hijos, con un hijo y con dos hijos.
*/
Nodo *eliminarMiembro(Nodo *raiz, int nacimiento) {
  if (raiz == NULL)
    return raiz;

  if (nacimiento < raiz->nacimiento) {
    raiz->izq = eliminarMiembro(raiz->izq, nacimiento);
  } else if (nacimiento > raiz->nacimiento) {
    raiz->der = eliminarMiembro(raiz->der, nacimiento);
  } else {
    // Caso 1: No tiene hijo izquierdo
    if (raiz->izq == NULL) {
      Nodo *temp = raiz->der;
      delete raiz;
      return temp;
    }
    // Caso 2: No tiene hijo derecho
    else if (raiz->der == NULL) {
      Nodo *temp = raiz->izq;
      delete raiz;
      return temp;
    }

    // Caso 3: Tiene dos hijos
    Nodo *sucesor = minimo(raiz->der);

    // Copiar datos del sucesor
    raiz->nacimiento = sucesor->nacimiento;
    raiz->nombre = sucesor->nombre;
    raiz->rol = sucesor->rol;

    // Eliminar sucesor
    raiz->der = eliminarMiembro(raiz->der, sucesor->nacimiento);
  }

  return raiz;
}

/*
  Menú principal:
  Permite al usuario interactuar con las operaciones del ABB.
*/
int main() {
  Nodo *raiz = NULL;
  int opcion, nacimiento;
  string nombre, rol;

  do {
    cout << "\n========== ARBOL GENEALOGICO - MITOLOGIA GRIEGA ==========\n";
    cout << "1. Insertar miembro\n";
    cout << "2. Buscar miembro\n";
    cout << "3. Eliminar miembro\n";
    cout << "4. Mostrar Inorden\n";
    cout << "5. Mostrar Preorden\n";
    cout << "6. Mostrar Postorden\n";
    cout << "0. Salir\n";
    cout << "Seleccione una opcion: ";
    cin >> opcion;

    switch (opcion) {
    case 1:
      cout << "Año simbolico de nacimiento: ";
      cin >> nacimiento;
      cin.ignore();

      cout << "Nombre del ser: ";
      getline(cin, nombre);

      cout << "Rol mitologico: ";
      getline(cin, rol);

      raiz = insertar(raiz, nacimiento, nombre, rol);
      break;

    case 2:
      cout << "Año a buscar: ";
      cin >> nacimiento;

      if (buscar(raiz, nacimiento))
        cout << "Encontrado: " << buscar(raiz, nacimiento)->nombre << endl;
      else
        cout << "No existe en el arbol.\n";
      break;

    case 3:
      cout << "Año a eliminar: ";
      cin >> nacimiento;

      raiz = eliminarMiembro(raiz, nacimiento);
      cout << "Proceso completado.\n";
      break;

    case 4:
      cout << "\n--- INORDEN ---\n";
      inorden(raiz);
      break;

    case 5:
      cout << "\n--- PREORDEN ---\n";
      preorden(raiz);
      break;

    case 6:
      cout << "\n--- POSTORDEN ---\n";
      postorden(raiz);
      break;

    case 0:
      cout << "Saliendo...\n";
      break;

    default:
      cout << "Opcion invalida.\n";
    }

  } while (opcion != 0);

  return 0;
}
