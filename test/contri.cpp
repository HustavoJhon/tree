#include <iostream>
#include <string>
using namespace std;

// =============================================
// Convierte una cadena NUMÉRICA a entero (sin atoi)
// =============================================
int convertirEntero(const string &txt) {
    int n = 0;
    for (int i = 0; i < (int)txt.length(); i++) {
        n = n * 10 + (txt[i] - '0');
    }
    return n;
}

// =============================================
// Verifica si un texto contiene SOLO dígitos
// =============================================
bool esNumero(const string &txt) {
    if (txt.length() == 0) return false;
    for (int i = 0; i < (int)txt.length(); i++) {
        if (txt[i] < '0' || txt[i] > '9')
            return false;
    }
    return true;
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
        nombre = nom;
        rol = r;
        izq = NULL;
        der = NULL;
    }
};

// PROTOTIPOS
Nodo *insertar(Nodo *raiz, int anio, int mes, const string &nombre, const string &rol);
Nodo *buscarExacto(Nodo *raiz, int anio, int mes);
Nodo *eliminarMiembro(Nodo *raiz, int anio, int mes);
Nodo *minimo(Nodo *n);
void inorden(Nodo *r);
void preorden(Nodo *r);
void postorden(Nodo *r);
void imprimirArbolAscii(Nodo *r, string pref, bool esUltimo);
bool leerIntRango(const string &msg, int &valor, int minVal, int maxVal);

// =============================================
// INSERTAR
// =============================================
Nodo *insertar(Nodo *raiz, int anio, int mes, const string &nombre, const string &rol) {
    int clave = anio * 100 + mes;

    if (raiz == NULL) {
        return new Nodo(anio, mes, nombre, rol);
    }

    if (clave < raiz->clave)
        raiz->izq = insertar(raiz->izq, anio, mes, nombre, rol);
    else if (clave > raiz->clave)
        raiz->der = insertar(raiz->der, anio, mes, nombre, rol);
    else
        cout << "Aviso: ya existe un miembro con esa clave.\n";

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
// MÍNIMO
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
    if (raiz == NULL)
        return raiz;

    int clave = anio * 100 + mes;

    if (clave < raiz->clave) {
        raiz->izq = eliminarMiembro(raiz->izq, anio, mes);
    }
    else if (clave > raiz->clave) {
        raiz->der = eliminarMiembro(raiz->der, anio, mes);
    }
    else {
        if (raiz->izq == NULL) {
            Nodo *temp = raiz->der;
            delete raiz;
            return temp;
        }
        else if (raiz->der == NULL) {
            Nodo *temp = raiz->izq;
            delete raiz;
            return temp;
        }

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
        cout << r->nombre << " (" << r->anio << "-" << r->mes << ") - " << r->rol << endl;
        inorden(r->der);
    }
}

void preorden(Nodo *r) {
    if (r) {
        cout << r->nombre << " (" << r->anio << "-" << r->mes << ") - " << r->rol << endl;
        preorden(r->izq);
        preorden(r->der);
    }
}

void postorden(Nodo *r) {
    if (r) {
        postorden(r->izq);
        postorden(r->der);
        cout << r->nombre << " (" << r->anio << "-" << r->mes << ") - " << r->rol << endl;
    }
}

// =============================================
// ASCII TREE (sin Unicode)
// =============================================
void imprimirArbolAscii(Nodo *r, string pref, bool esUltimo) {
    if (r == NULL) return;

    cout << pref;
    if (esUltimo)
        cout << "`-- ";
    else
        cout << "|-- ";

    cout << r->nombre << " [" << r->anio << "-" << r->mes << "] (" << r->rol << ")\n";

    string nuevoPref = pref + (esUltimo ? "    " : "|   ");

    if (r->izq != NULL && r->der != NULL) {
        imprimirArbolAscii(r->izq, nuevoPref, false);
        imprimirArbolAscii(r->der, nuevoPref, true);
    }
    else if (r->izq != NULL) {
        imprimirArbolAscii(r->izq, nuevoPref, true);
    }
    else if (r->der != NULL) {
        imprimirArbolAscii(r->der, nuevoPref, true);
    }
}

// =============================================
// LECTURA VALIDADA (sin atoi, sin isdigit)
// =============================================
bool leerIntRango(const string &msg, int &valor, int minVal, int maxVal) {
    string cadena;

    while (true) {
        cout << msg;
        cin >> cadena;

        if (!esNumero(cadena)) {
            cout << "Solo numeros.\n";
            continue;
        }

        valor = convertirEntero(cadena);

        if (valor < minVal || valor > maxVal) {
            cout << "Fuera de rango.\n";
            continue;
        }

        return true;
    }
}

// =============================================
// CARGAR MITOLOGÍA
// =============================================
Nodo *cargarMitologia(Nodo *r) {
    r = insertar(r, 10, 6, "Zeus", "Rey Olimpico");

    r = insertar(r, 5, 3, "Cronos", "Titan");
    r = insertar(r, 3, 2, "Oceano", "Titan");
    r = insertar(r, 2, 1, "Ouranos", "Primigenio");
    r = insertar(r, 4, 5, "Rea", "Titanide");
    r = insertar(r, 7, 8, "Hades", "Olimpico");
    r = insertar(r, 6, 4, "Hestia", "Olimpica");
    r = insertar(r, 8, 9, "Poseidon", "Olimpico");

    r = insertar(r, 15, 7, "Atenea", "Olimpica");
    r = insertar(r, 13, 2, "Apolo", "Olimpico");
    r = insertar(r, 12, 1, "Artemisa", "Olimpica");
    r = insertar(r, 14, 5, "Hermes", "Olimpico");
    r = insertar(r, 18, 3, "Heracles", "Heroe");
    r = insertar(r, 17, 9, "Perseo", "Heroe");
    r = insertar(r, 20, 4, "Teseo", "Heroe");

    return r;
}

// =============================================
// PROGRAMA PRINCIPAL
// =============================================
int main() {
    Nodo *raiz = NULL;

    raiz = cargarMitologia(raiz);

    cout << "\n=== Arbol mitologico cargado ===\n\n";
    imprimirArbolAscii(raiz, "", true);

    int opcion;

    do {
        cout << "\nMENU:\n";
        cout << "1. Insertar\n";
        cout << "2. Buscar\n";
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
            imprimirArbolAscii(raiz, "", true);
        }

        else if (opcion == 2) {
            int a, m;
            leerIntRango("Anio: ", a, 0, 9999);
            leerIntRango("Mes: ", m, 1, 12);

            Nodo *res = buscarExacto(raiz, a, m);
            if (res != NULL)
                cout << "Encontrado: " << res->nombre << endl;
            else
                cout << "No existe.\n";
        }

        else if (opcion == 3) {
            int a, m;
            leerIntRango("Anio: ", a, 0, 9999);
            leerIntRango("Mes: ", m, 1, 12);

            raiz = eliminarMiembro(raiz, a, m);
            imprimirArbolAscii(raiz, "", true);
        }

        else if (opcion == 4)
            inorden(raiz);
        else if (opcion == 5)
            preorden(raiz);
        else if (opcion == 6)
            postorden(raiz);
        else if (opcion == 7)
            imprimirArbolAscii(raiz, "", true);

    } while (opcion != 0);

    return 0;
}
