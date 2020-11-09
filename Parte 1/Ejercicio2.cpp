#include <iostream>
#include<string.h>
#include <stdio.h>

using namespace std;

// Comercio: No contiene el rubro, para no incluirlo en los archivos.
struct Comercio{
    char nombre[20];
    unsigned zona;
};

// Constantes
const int MAX_COMERCIOS = 240;
const int MAX_POR_RUBRO = 10;
const int CANT_ZONAS = 6;
const int CANT_RUBROS = 4;
const string nombre_rubros[4] = {"Pizzerias", "Heladerias", "Bebidas", "Parrillas"};

void llenar_comercios(Comercio comercios[MAX_COMERCIOS], int rubros[MAX_COMERCIOS], int contador[CANT_ZONAS][CANT_RUBROS]);
void generar_archivos(Comercio c[MAX_COMERCIOS], int rubros[MAX_COMERCIOS]);
void informar(int contador[CANT_ZONAS][CANT_RUBROS]);
void escribir_archivo(string nombre, Comercio comercios[], int length);
void swap(Comercio *a, Comercio *b);
void ordenar(Comercio comercios[], int length);

int main(){
    // Variables principales
    Comercio comercios[MAX_COMERCIOS];
    int rubros[MAX_COMERCIOS] = {0};
    int contador[CANT_ZONAS][CANT_RUBROS] = {0};
    // Desarrollo del programa
    llenar_comercios(comercios, rubros, contador);
    generar_archivos(comercios, rubros);
    informar(contador);
    return 0;
}

void generar_archivos(Comercio c[MAX_COMERCIOS], int rubros[MAX_COMERCIOS]){
    int lengths[CANT_RUBROS] = {0};
    int j[CANT_RUBROS] = {0};
    // Obtener la cantidad de comercios de cada rubro
    Comercio temp = c[0];
    int i = 0;
    while (strcmp(temp.nombre, "*") != 0){
        lengths[rubros[i] - 1]++;
        i++;
        temp = c[i];
    }
    // Crear vectores de comercios para cada rubro y llenarlos
    Comercio pizzerias[lengths[0]], heladerias[lengths[1]], bebidas[lengths[2]], parrillas[lengths[3]];
    temp = c[0];
    i = 0;
    while (strcmp(temp.nombre, "*") != 0) {
        switch (rubros[i]) {
            case 1: pizzerias[j[0]] = temp; break;
            case 2: heladerias[j[1]] = temp; break;
            case 3: bebidas[j[2]] = temp; break;
            case 4: parrillas[j[3]] = temp; break;
        }
        j[rubros[i] - 1]++;
        i++;
        temp = c[i];
    }
    // Ordenar alfabeticamente los comercios de cada rubro
    ordenar(pizzerias, lengths[0]);
    ordenar(heladerias, lengths[1]);
    ordenar(bebidas, lengths[2]);
    ordenar(parrillas, lengths[3]);
    // Guardar todos los comercios en archivos
    escribir_archivo("Pizzerias.dat", pizzerias, lengths[0]);
    escribir_archivo("Heladerias.dat", heladerias, lengths[1]);
    escribir_archivo("Bebidas.dat", bebidas, lengths[2]);
    escribir_archivo("Parrillas.dat", parrillas, lengths[3]);
}

// Toma un vector de comercios y los escribe en un archivo
void escribir_archivo(string nombre, Comercio comercios[], int length){
    char char_array[nombre.length() + 1];
    strcpy(char_array, nombre.c_str());
    FILE* archivo = fopen(char_array, "ab");
    for (int i = 0; i < length; i++)
        fwrite(&comercios[i], sizeof(Comercio), 1, archivo);
    fclose(archivo);
}

// Cambia los valores de dos variables de tipo Comercio
void swap(Comercio *a, Comercio *b){
    Comercio temp = *a;
    *a = *b;
    *b = temp;
}

// Algoritmo para ordenar alfabeticamente los comercios
void ordenar(Comercio comercios[], int length){
    int i, j, min;
    for (i = 0; i < length - 1; i++){
        min = i;
        for (j = i+1; j < length; j++)
            if (strcmp(comercios[j].nombre, comercios[min].nombre) < 0)
                min = j;
        swap(&comercios[min], &comercios[i]);
    }
}

// Provee al usuario informacion sobre cada zona
void informar(int contador[CANT_ZONAS][CANT_RUBROS]){
    cout << "--- Informacion sobre los comercios ingresados ---" << endl;
    int i, j;
    bool todos;
    // Informacion sobre cada rubro
    for (i = 0; i < CANT_RUBROS; i++) {
        todos = true;
        for (j = 0; j < CANT_ZONAS; j++)
            if (contador[j][i] != 0) todos = false;
        if (todos) cout << "No se incorporaron " << nombre_rubros[i] << "." << endl;
    }
    // Informacion sobre cada zona
    for (i = 0; i < CANT_ZONAS; i++){
        todos = true;
        for (j = 0; j < CANT_RUBROS; j++)
            if (contador[i][j] == 0) todos = false;
        cout << "En la zona " << i+1 << (todos ? "" : " NO") << " hay comercios para todos los rubros." << endl;
    }
}

// Llena un array de comercios mediante el input del usuario
void llenar_comercios(Comercio comercios[MAX_COMERCIOS], int rubros[MAX_COMERCIOS], int contador[CANT_ZONAS][CANT_RUBROS]){
    int k = 0;
    cout << "Ingreso de datos (nombre = \"*\" para finalizar)" << endl;
    cout << "Rubros: 1 para Pizzeria, 2 para Heladeria, 3 para Bebidas y 4 para Parrilla." << endl;
    cout << "-- Nuevo Comercio --" << endl << "Ingrese el nombre: ";
    cin >> comercios[k].nombre;
    while (strcmp(comercios[k].nombre, "*") != 0){
        cout << "Ingrese el rubro: ";
        cin >> rubros[k];
        cout << "Ingrese la zona: ";
        cin >> comercios[k].zona;
        if (contador[comercios[k].zona - 1][rubros[k] - 1] < MAX_POR_RUBRO){
            contador[comercios[k].zona - 1][rubros[k] - 1]++;
            k++;
        }else{
            cout << "El ultimo comercio ingresado desbordo la cantidad permitida para su rubro. Intente de nuevo." << endl;
        }
        cout << "-- Nuevo Comercio --" << endl << "Ingrese el nombre: ";
        cin >> comercios[k].nombre;
    }
}
