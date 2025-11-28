#include <iostream>
#include <locale.h> // Para caracteres en español
#include <string>
using namespace std;

// =============================================
// Convierte una cadena NUMERICA a entero (sin atoi)
// =============================================
int convertirEntero(const string &txt) {
  int n = 0;
  for (int i = 0; i < (int)txt.length(); i++) {
    n = n * 10 + (txt[i] - '0');
  }
  return n;
}

// =============================================
// Verifica si un texto contiene SOLO digitos
// =============================================
bool esNumero(const string &txt) {
  if (txt.length() == 0)
    return false;
  for (int i = 0; i < (int)txt.length(); i++) {
    if (txt[i] < '0' || txt[i] > '9')
      return false;
  }
  return true;
}

// =============================================
// Convierte un caracter a minuscula (sin tolower)
// =============================================
char aMinuscula(char c) {
  if (c >= 'A' && c <= 'Z')
    return c + 32;
  return c;
}

// =============================================
// Convierte un caracter a mayuscula (sin toupper)
// =============================================
char aMayuscula(char c) {
  if (c >= 'a' && c <= 'z')
    return c - 32;
  return c;
}

// =============================================
// Capitaliza la primera letra de cada palabra
// Ejemplo: "zeus rey" -> "Zeus Rey"
// =============================================
string capitalizar(const string &txt) {
  string resultado = "";
  bool nuevaPalabra = true;

  for (int i = 0; i < (int)txt.length(); i++) {
    if (txt[i] == ' ') {
      resultado += ' ';
      nuevaPalabra = true;
    } else {
      if (nuevaPalabra) {
        resultado += aMayuscula(txt[i]);
        nuevaPalabra = false;
      } else {
        resultado += aMinuscula(txt[i]);
      }
    }
  }

  return resultado;
}

// =============================================
// Elimina espacios al inicio y final de cadena
// =============================================
string trim(const string &txt) {
  if (txt.length() == 0)
    return "";

  int inicio = 0;
  int fin = txt.length() - 1;

  // Buscar primer caracter no espacio
  while (inicio <= fin && txt[inicio] == ' ')
    inicio++;

  // Buscar ultimo caracter no espacio
  while (fin >= inicio && txt[fin] == ' ')
    fin--;

  // Si solo habia espacios
  if (inicio > fin)
    return "";

  return txt.substr(inicio, fin - inicio + 1);
}

// =============================================
// Verifica si una cadena esta vacia o solo espacios
// =============================================
bool esVacia(const string &txt) { return trim(txt).length() == 0; }

// =============================================
// Verifica si el año es bisiesto
// =============================================
bool esBisiesto(int anio) {
  if (anio % 4 != 0)
    return false;
  if (anio % 100 != 0)
    return true;
  if (anio % 400 == 0)
    return true;
  return false;
}

// =============================================
// Valida que el mes tenga dias correctos
// =============================================
bool mesValido(int mes, int anio) {
  if (mes < 1 || mes > 12)
    return false;

  // Dias por mes
  int diasMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  // Ajustar febrero si es bisiesto
  if (esBisiesto(anio))
    diasMes[1] = 29;

  return true; // Ya verificamos el rango 1-12
}

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
    rol = capitalizar(r);      // Capitalizar al crear nodo
    izq = NULL;
    der = NULL;
  }
};

// PROTOTIPOS
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

// =============================================
// INSERTAR (con validacion de duplicados)
// =============================================
Nodo *insertar(Nodo *raiz, int anio, int mes, const string &nombre,
               const string &rol) {
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

// =============================================
// BUSCAR
// =============================================
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

// =============================================
// MINIMO
// =============================================
Nodo *minimo(Nodo *n) {
  while (n != NULL && n->izq != NULL)
    n = n->izq;
  return n;
}

// =============================================
// ELIMINAR
// =============================================
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

// =============================================
// RECORRIDOS
// =============================================
void inorden(Nodo *r) {
  if (r) {
    inorden(r->izq);
    cout << r->nombre << " (" << r->anio << "-" << r->mes << ") - " << r->rol
         << endl;
    inorden(r->der);
  }
}

void preorden(Nodo *r) {
  if (r) {
    cout << r->nombre << " (" << r->anio << "-" << r->mes << ") - " << r->rol
         << endl;
    preorden(r->izq);
    preorden(r->der);
  }
}

void postorden(Nodo *r) {
  if (r) {
    postorden(r->izq);
    postorden(r->der);
    cout << r->nombre << " (" << r->anio << "-" << r->mes << ") - " << r->rol
         << endl;
  }
}

// =============================================
// ASCII TREE (sin Unicode)
// =============================================
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

  string nuevoPref = pref + (esUltimo ? "    " : "|   ");

  if (r->izq != NULL && r->der != NULL) {
    imprimirArbolAscii(r->izq, nuevoPref, false);
    imprimirArbolAscii(r->der, nuevoPref, true);
  } else if (r->izq != NULL) {
    imprimirArbolAscii(r->izq, nuevoPref, true);
  } else if (r->der != NULL) {
    imprimirArbolAscii(r->der, nuevoPref, true);
  }
}

// =============================================
// LECTURA VALIDADA DE ENTEROS CON RANGO
// =============================================
bool leerIntRango(const string &msg, int &valor, int minVal, int maxVal) {
  string cadena;

  while (true) {
    cout << msg;
    cin >> cadena;

    if (!esNumero(cadena)) {
      cout << "*** Error: Solo se permiten numeros ***\n";
      continue;
    }

    valor = convertirEntero(cadena);

    if (valor < minVal || valor > maxVal) {
      cout << "*** Error: Valor fuera de rango [" << minVal << "-" << maxVal
           << "] ***\n";
      continue;
    }

    return true;
  }
}

// =============================================
// LECTURA VALIDADA DE AÑO
// =============================================
bool leerAnio(int &anio) {
  string cadena;

  while (true) {
    cout << "Año (0-9999): ";
    cin >> cadena;

    if (!esNumero(cadena)) {
      cout << "*** Error: Solo se permiten numeros ***\n";
      continue;
    }

    anio = convertirEntero(cadena);

    if (anio < 0 || anio > 9999) {
      cout << "*** Error: Año fuera de rango [0-9999] ***\n";
      continue;
    }

    return true;
  }
}

// =============================================
// LECTURA VALIDADA DE MES
// =============================================
bool leerMes(int &mes, int anio) {
  string cadena;

  while (true) {
    cout << "Mes (1-12): ";
    cin >> cadena;

    if (!esNumero(cadena)) {
      cout << "*** Error: Solo se permiten numeros ***\n";
      continue;
    }

    mes = convertirEntero(cadena);

    if (!mesValido(mes, anio)) {
      cout << "*** Error: Mes invalido [1-12] ***\n";
      continue;
    }

    return true;
  }
}

// =============================================
// LECTURA VALIDADA DE TEXTO NO VACIO
// =============================================
bool leerTextoNoVacio(const string &msg, string &texto) {
  while (true) {
    cout << msg;
    getline(cin, texto);

    texto = trim(texto); // Eliminar espacios extras

    if (esVacia(texto)) {
      cout << "*** Error: El texto no puede estar vacio ***\n";
      continue;
    }

    return true;
  }
}

// =============================================
// CARGAR MITOLOGIA
// =============================================
Nodo *cargarMitologia(Nodo *r) {
  r = insertar(r, 10, 6, "zeus", "rey olimpico");

  r = insertar(r, 5, 3, "cronos", "titan");
  r = insertar(r, 3, 2, "oceano", "titan");
  r = insertar(r, 2, 1, "ouranos", "primigenio");
  r = insertar(r, 4, 5, "rea", "titanide");
  r = insertar(r, 7, 8, "hades", "olimpico");
  r = insertar(r, 6, 4, "hestia", "olimpica");
  r = insertar(r, 8, 9, "poseidon", "olimpico");

  r = insertar(r, 15, 7, "atenea", "olimpica");
  r = insertar(r, 13, 2, "apolo", "olimpico");
  r = insertar(r, 12, 1, "artemisa", "olimpica");
  r = insertar(r, 14, 5, "hermes", "olimpico");
  r = insertar(r, 18, 3, "heracles", "heroe");
  r = insertar(r, 17, 9, "perseo", "heroe");
  r = insertar(r, 20, 4, "teseo", "heroe");

  return r;
}

// =============================================
// PROGRAMA PRINCIPAL
// =============================================
int main() {
  // Habilitar caracteres en español (ñ, á, é, etc.)
  setlocale(LC_ALL, "spanish");

  Nodo *raiz = NULL;

  raiz = cargarMitologia(raiz);

  cout << "\n======================================\n";
  cout << "  ARBOL MITOLOGICO CARGADO\n";
  cout << "======================================\n\n";
  imprimirArbolAscii(raiz, "", true);

  int opcion;

  do {
    cout << "\n======================================\n";
    cout << "             MENU PRINCIPAL\n";
    cout << "======================================\n";
    cout << "1. Insertar nuevo miembro\n";
    cout << "2. Buscar miembro\n";
    cout << "3. Eliminar miembro\n";
    cout << "4. Recorrido Inorden\n";
    cout << "5. Recorrido Preorden\n";
    cout << "6. Recorrido Postorden\n";
    cout << "7. Ver arbol completo\n";
    cout << "0. Salir del programa\n";
    cout << "======================================\n";
    cout << "Seleccione una opcion: ";
    cin >> opcion;

    if (opcion == 1) {
      int a, m;
      string nombre, rol;

      cout << "\n--- INSERTAR NUEVO MIEMBRO ---\n";

      // Leer año con validacion
      leerAnio(a);

      // Leer mes con validacion
      leerMes(m, a);

      cin.ignore(); // Limpiar buffer

      // Leer nombre con validacion
      leerTextoNoVacio("Nombre: ", nombre);

      // Leer rol con validacion
      leerTextoNoVacio("Rol: ", rol);

      raiz = insertar(raiz, a, m, nombre, rol);

      cout << "\n--- ARBOL ACTUALIZADO ---\n";
      imprimirArbolAscii(raiz, "", true);
    }

    else if (opcion == 2) {
      int a, m;

      cout << "\n--- BUSCAR MIEMBRO ---\n";
      leerAnio(a);
      leerMes(m, a);

      Nodo *res = buscarExacto(raiz, a, m);
      if (res != NULL) {
        cout << "\n*** MIEMBRO ENCONTRADO ***\n";
        cout << "Nombre: " << res->nombre << endl;
        cout << "Rol: " << res->rol << endl;
        cout << "Fecha: " << res->anio << "-" << res->mes << endl;
      } else {
        cout << "\n*** No existe miembro con esa fecha ***\n";
      }
    }

    else if (opcion == 3) {
      int a, m;

      cout << "\n--- ELIMINAR MIEMBRO ---\n";
      leerAnio(a);
      leerMes(m, a);

      raiz = eliminarMiembro(raiz, a, m);

      cout << "\n--- ARBOL ACTUALIZADO ---\n";
      imprimirArbolAscii(raiz, "", true);
    }

    else if (opcion == 4) {
      cout << "\n--- RECORRIDO INORDEN ---\n";
      if (raiz == NULL)
        cout << "Arbol vacio\n";
      else
        inorden(raiz);
    }

    else if (opcion == 5) {
      cout << "\n--- RECORRIDO PREORDEN ---\n";
      if (raiz == NULL)
        cout << "Arbol vacio\n";
      else
        preorden(raiz);
    }

    else if (opcion == 6) {
      cout << "\n--- RECORRIDO POSTORDEN ---\n";
      if (raiz == NULL)
        cout << "Arbol vacio\n";
      else
        postorden(raiz);
    }

    else if (opcion == 7) {
      cout << "\n--- ARBOL COMPLETO ---\n";
      if (raiz == NULL)
        cout << "Arbol vacio\n";
      else
        imprimirArbolAscii(raiz, "", true);
    }

    else if (opcion != 0) {
      cout << "\n*** Opcion invalida ***\n";
    }

  } while (opcion != 0);

  cout << "\n======================================\n";
  cout << "   Gracias por usar el programa\n";
  cout << "======================================\n";

  return 0;
}
