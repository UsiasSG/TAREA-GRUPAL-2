#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <map>
#include <algorithm>
//PROGRAMA UMG
using namespace std;
struct Palabra {
    string palabra;
    string traduccion;
    string significado;
};

// Función para crear una nueva palabra y almacenarla en el archivo
void crearPalabra() {
    Palabra nuevaPalabra;

    cout << "Ingrese la palabra: ";
    getline(cin, nuevaPalabra.palabra);

    cout << "Ingrese la traduccion: ";
    getline(cin, nuevaPalabra.traduccion);

    cout << "Ingrese la funcionalidad: ";
    getline(cin, nuevaPalabra.significado);

    // Abre el archivo en modo de escritura al final
    ofstream archivo("datos.txt", ios::app);
    if (!archivo) {
        cerr << "Error al abrir el archivo." << endl;
        return;
    }

    // Escribe la nueva palabra en el archivo
    archivo << nuevaPalabra.palabra << "," << nuevaPalabra.traduccion << "," << nuevaPalabra.significado << endl;
    archivo.close();
}

// Función para leer todas las palabras almacenadas en el archivo
void leerPalabras() {
    // Abre el archivo en modo de lectura
    ifstream archivo("datos.txt");
    if (!archivo) {
        cerr << "Error al abrir el archivo." << endl;
        return;
    }

    // Lee cada palabra del archivo y la muestra en pantalla
    string palabra, traduccion, significado;
    while (getline(archivo, palabra, ',')) {
        getline(archivo, traduccion, ',');
        getline(archivo, significado);
        // Muestra los datos de la palabra en formato de tabla
        cout << "| " << setw(20) << palabra << " | " << setw(20) << traduccion << " | " << setw(20) << significado << endl;
    }

    archivo.close();
}

// Función para eliminar una palabra del archivo
void eliminarPalabra(const string& palabraAEliminar) {
    ifstream archivoEntrada("datos.txt");
    ofstream archivoSalida("temp.txt");

    if (!archivoEntrada || !archivoSalida) {
        cerr << "Error al abrir el archivo." << endl;
        return;

    }

    string palabra, traduccion, significado;
    bool eliminada = false;

    // Lee cada palabra del archivo
    while (getline(archivoEntrada, palabra, ',')) {
        getline(archivoEntrada, traduccion, ',');
        getline(archivoEntrada, significado);

        // Si la palabra es diferente a la que se desea eliminar, se escribe en el archivo de salida
        if (palabra != palabraAEliminar) {
            archivoSalida << palabra << "," << traduccion << "," << significado << endl;
        } else {
            eliminada = true;
        }
    }

    archivoEntrada.close();
    archivoSalida.close();

    // Elimina el archivo original y renombra el archivo temporal
    remove("datos.txt");
    rename("temp.txt", "datos.txt");

    if (eliminada) {
        cout << "Palabra eliminada exitosamente." << endl;
    } else {
        cout << "La palabra no fue encontrada." << endl;
    }
}

// Función para editar una palabra del archivo
void editarPalabra(const string& palabraAEditar) {
    ifstream archivoEntrada("datos.txt");
    ofstream archivoSalida("temp.txt");

    if (!archivoEntrada || !archivoSalida) {
        cerr << "Error al abrir el archivo." << endl;
        return;
    }

    string palabra, traduccion, significado;
    bool editada = false;

    // Lee cada palabra del archivo
    while (getline(archivoEntrada, palabra, ',')) {
        getline(archivoEntrada, traduccion, ',');
        getline(archivoEntrada, significado);

        // Si la palabra coincide con la que se desea editar, se solicitan los nuevos valores y se escriben en el archivo de salida
        if (palabra == palabraAEditar) {
            editada = true;
            cout << "Ingrese la nueva traduccion para '" << palabraAEditar << "': ";
            getline(cin, traduccion);

            cout << "Ingrese la nueva funcionalidad para '" << palabraAEditar << "': ";
            getline(cin, significado);

            archivoSalida << palabraAEditar << "," << traduccion << "," << significado << endl;
        } else {
            archivoSalida << palabra << "," << traduccion << "," << significado << endl;
        }
    }

    archivoEntrada.close();
    archivoSalida.close();

    // Elimina el archivo original y renombra el archivo temporal
    remove("datos.txt");
    rename("temp.txt", "datos.txt");

    if (editada) {
        cout << "Palabra editada exitosamente." << endl;
    } else {
        cout << "La palabra no fue encontrada." << endl;
    }
}

// Función para traducir las palabras reservadas de C++ en el código ingresado
void traducirPalabrasReservadas(const string& codigo) {
    ifstream archivoPalabras("datos.txt");
    if (!archivoPalabras) {
        cerr << "Error al abrir el archivo de palabras." << endl;
        return;
    }

    map<string, string> traducciones;
    string palabra, traduccion, significado;

    // Lee cada palabra del archivo de palabras y la agrega al mapa de traducciones
    while (getline(archivoPalabras, palabra, ',')) {
        getline(archivoPalabras, traduccion, ',');
        getline(archivoPalabras, significado);
        traducciones[palabra] = traduccion;
    }

    archivoPalabras.close();

    istringstream stream(codigo);
    string linea;

    bool dentroDeComentario = false;
    bool dentroDeCadena = false;

    // Lee cada línea del código ingresado
    while (getline(stream, linea)) {
        // Comprueba si la línea está dentro de un comentario de una línea
        size_t posComentarioLinea = linea.find("//");
        if (posComentarioLinea != string::npos) {
            cout << linea.substr(0, posComentarioLinea) << endl;
            break; // Termina la traducción después del comentario de una línea
        }

        // Comprueba si la línea está dentro de un comentario de varias líneas
        size_t posComentarioInicio = linea.find("/*");
        if (posComentarioInicio != string::npos) {
            dentroDeComentario = true;
        }

        // Si estamos dentro de un comentario, muestra la línea y continúa con la siguiente
        if (dentroDeComentario) {
            size_t posComentarioFin = linea.find("*/");
            if (posComentarioFin != string::npos) {
                dentroDeComentario = false;
            }
            continue;
        }

        // Comprueba si la línea contiene una cadena
        size_t posComillas = linea.find("\"");
        if (posComillas != string::npos) {
            dentroDeCadena = !dentroDeCadena;
        }

        // Si estamos dentro de una cadena, muestra la línea y continúa con la siguiente
        if (dentroDeCadena) {
            cout << linea << endl;
            continue;
        }

        // Procesa la línea palabra por palabra para mantener los signos de puntuación
        istringstream palabraStream(linea);
        string palabraCodigo;
        while (palabraStream >> palabraCodigo) {
            // Elimina cualquier signo de puntuación que pueda estar presente en la palabra
            string palabraSinPuntuacion = palabraCodigo;
            palabraSinPuntuacion.erase(remove_if(palabraSinPuntuacion.begin(), palabraSinPuntuacion.end(), ::ispunct), palabraSinPuntuacion.end());

            // Si la palabra está presente en el mapa de traducciones, muestra su traducción
            if (traducciones.find(palabraSinPuntuacion) != traducciones.end()) {
                cout << traducciones[palabraSinPuntuacion] << palabraCodigo.substr(palabraSinPuntuacion.length()) << " ";
            } else {
                cout << palabraCodigo << " ";
            }
        }

        // Muestra un salto de línea después de procesar cada línea
        cout << endl;
    }
}





int main() {
    int opcion;
    string palabraAEditar;
    string palabraAEliminar;
    string codigo;

    do {
    	cout << "---------------------------------" << endl;
    	cout << "GESTOR DE DICCIONARIO DE PALABRAS" << endl;
        cout << "---------------------------------" << endl;
		cout << "1. Crear palabra" << endl;
        cout << "2. Leer palabras" << endl;
        cout << "3. Editar palabra" << endl;
        cout << "4. Eliminar palabra" << endl;
        cout << "5. Digitar codigo" << endl;
        cout << "6. Salir" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion;
        cin.ignore();
		system("cls");
        switch(opcion) {
            case 1:
                crearPalabra();
                break;
            case 2:
                leerPalabras();
                break;
            case 3:
                cout << "Ingrese la palabra que desea editar: ";
                getline(cin, palabraAEditar);
                editarPalabra(palabraAEditar);
                break;
            case 4:
                cout << "Ingrese la palabra que desea eliminar: ";
                getline(cin, palabraAEliminar);
                eliminarPalabra(palabraAEliminar);
                break;
            case 5:
                cout << "Ingrese el codigo a traducir (presione Enter dos veces para finalizar):" << endl;
                {
                    stringstream buffer;
                    string linea;
                    while (getline(cin, linea) && !linea.empty()) {
                        buffer << linea << endl;
                    }
                    codigo = buffer.str();
                }
                traducirPalabrasReservadas(codigo);
			    break;
            case 6:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opcion no valida" << endl;
        }
    } while (opcion != 6);

}
