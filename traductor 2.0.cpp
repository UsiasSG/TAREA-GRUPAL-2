#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

struct Palabra {
    string palabra;
    string traduccion;
    string funcionalidad;
};

// Función para agregar una palabra al archivo
void agregarPalabra(ofstream& archivo) {
    Palabra nuevaPalabra;
    cout << "Ingrese Palabra: ";
    cin >> nuevaPalabra.palabra;
    cout << "Ingrese Traduccion: ";
    cin >> nuevaPalabra.traduccion;
    cout << "Ingrese Funcionalidad: ";
    cin.ignore(); // Ignorar el salto de línea anterior
    getline(cin, nuevaPalabra.funcionalidad);

    archivo << nuevaPalabra.palabra << "  >>>  " << nuevaPalabra.traduccion << ":   " << nuevaPalabra.funcionalidad << endl;
    cout << "Palabra agregada correctamente." << endl;
}

// Función para leer todas las palabras del archivo
void leerPalabras(ifstream& archivo) {
    Palabra palabra;
    cout << "Listado de palabras:" << endl;
    while (getline(archivo, palabra.palabra, ',') && getline(archivo, palabra.traduccion, ',') && getline(archivo, palabra.funcionalidad)) {
        cout << "Palabra: " << palabra.palabra << ", Traducción: " << palabra.traduccion << ", Funcionalidad: " << palabra.funcionalidad << endl;
    }
}

// Función para actualizar una palabra en el archivo
// Función para actualizar una palabra en el archivo
void actualizarPalabra(const string& nombreArchivo) {
    string palabraActualizar;
    cout << "Ingrese la palabra a actualizar: ";
    cin >> palabraActualizar;

    fstream archivo(nombreArchivo);

    if (!archivo) {
        cerr << "Error al abrir el archivo." << endl;
        return;
    }

    string linea;
    vector<string> lineasActualizadas;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string palabra, traduccion, funcionalidad;
        getline(ss, palabra, ',');
        getline(ss, traduccion, ',');
        getline(ss, funcionalidad);

        if (palabra == palabraActualizar) {
            string nuevaPalabra, nuevaTraduccion, nuevaFuncionalidad;
            cout << "Ingrese la nueva palabra: ";
            cin >> nuevaPalabra;
            cout << "Ingrese la nueva traducción: ";
            cin >> nuevaTraduccion;
            cout << "Ingrese la nueva funcionalidad: ";
            cin.ignore(); // Ignorar el salto de línea anterior
            getline(cin, nuevaFuncionalidad);
            lineasActualizadas.push_back(nuevaPalabra + "," + nuevaTraduccion + "," + nuevaFuncionalidad);
        } else {
            lineasActualizadas.push_back(linea);
        }
    }

    archivo.close();

    ofstream archivoEscritura(nombreArchivo);
    if (!archivoEscritura) {
        cerr << "Error al abrir el archivo para escritura." << endl;
        return;
    }

    for (const auto& linea : lineasActualizadas) {
        archivoEscritura << linea << endl;
    }

    cout << "Palabra actualizada correctamente." << endl;
}

// Función para borrar una palabra del archivo
void borrarPalabra(const string& nombreArchivo) {
    string palabraBorrar;
    cout << "Ingrese la palabra a borrar: ";
    cin >> palabraBorrar;

    ifstream archivoLectura(nombreArchivo);
    if (!archivoLectura) {
        cerr << "Error al abrir el archivo." << endl;
        return;
    }

    string linea;
    vector<string> lineasNuevas;

    while (getline(archivoLectura, linea)) {
        stringstream ss(linea);
        string palabra, traduccion, funcionalidad;
        getline(ss, palabra, ',');
        getline(ss, traduccion, ',');
        getline(ss, funcionalidad);

        if (palabra != palabraBorrar) {
            lineasNuevas.push_back(linea);
        }
    }

    archivoLectura.close();

    ofstream archivoEscritura(nombreArchivo);
    if (!archivoEscritura) {
        cerr << "Error al abrir el archivo para escritura." << endl;
        return;
    }

    for (const auto& linea : lineasNuevas) {
        archivoEscritura << linea << endl;
    }

    cout << "Palabra borrada correctamente." << endl;
}

// Función principal
int main() {
    string nombreArchivo = "palabras.txt";

    int opcion;
    do {
        cout << "\n1. Agregar Palabra" << endl;
        cout << "2. Leer Palabras" << endl;
        cout << "3. Actualizar Palabra" << endl;
        cout << "4. Borrar Palabra" << endl;
        cout << "5. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                ofstream archivo(nombreArchivo, ios::app); // Abrir en modo append para agregar palabras al final
                if (!archivo) {
                    cerr << "Error al abrir el archivo." << endl;
                    return 1;
                }
                agregarPalabra(archivo);
                archivo.close();
                break;
            }
            case 2: {
                ifstream archivo(nombreArchivo);
                if (!archivo) {
                    cerr << "Error al abrir el archivo." << endl;
                    return 1;
                }
                leerPalabras(archivo);
                archivo.close();
                break;
            }
            case 3:
                actualizarPalabra(nombreArchivo);
                break;
            case 4:
                borrarPalabra(nombreArchivo);
                break;
            case 5:
                cout << "Saliendo del programa." << endl;
                break;
            default:
                cout << "Opción inválida. Por favor, seleccione una opción válida." << endl;
                break;
        }
    } while (opcion != 5);

    return 0;
}

