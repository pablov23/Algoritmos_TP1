#include <iostream>
#include<string.h>
#include <stdio.h>

using namespace std;

struct Comercio{
    string nombre;
    int rubro;
    unsigned zona;
};

const int MAX_COMERCIOS = 240;
const int MAX_POR_RUBRO = 10;
const int CANT_ZONAS = 6;
const int CANT_RUBROS = 4;
const string nombre_rubros[4] = {"Pizzerias", "Heladerias", "Bebidas", "Parrillas"};

void llenar_comercios(Comercio comercios[MAX_COMERCIOS], int contador[CANT_ZONAS][CANT_RUBROS]);
void informar(int contador[CANT_ZONAS][CANT_RUBROS]);
void generar_archivos(Comercio comercios[MAX_COMERCIOS]);
void escribir_archivo(string nombre, Comercio comercios[], int length);
void swap(Comercio *a, Comercio *b);
void ordenar(Comercio comercios[], int length);

int main(){
    Comercio comercios[MAX_COMERCIOS];
    int contador[CANT_ZONAS][CANT_RUBROS] = {0};
    llenar_comercios(comercios, contador);
    generar_archivos(comercios);
    informar(contador);
    return 0;
}

void generar_archivos(Comercio c[MAX_COMERCIOS]){
    int lengths[CANT_RUBROS] = {0};
    int j[CANT_RUBROS] = {0};
    Comercio temp = c[0];
    int i = 0;
    while (temp.nombre != "*"){
        lengths[temp.rubro - 1]++;
        i++;
        temp = c[i];
    }
    Comercio pizzerias[lengths[0]], heladerias[lengths[1]], bebidas[lengths[2]], parrillas[lengths[3]];
    temp = c[0];
    i = 0;
    while (temp.nombre != "*") {
        switch (temp.rubro) {
            case 1: pizzerias[j[0]] = temp; break;
            case 2: heladerias[j[1]] = temp; break;
            case 3: bebidas[j[2]] = temp; break;
            case 4: parrillas[j[3]] = temp; break;
        }
        j[temp.rubro - 1]++;
        i++;
        temp = c[i];
    }
    ordenar(pizzerias, lengths[0]);
    ordenar(heladerias, lengths[1]);
    ordenar(bebidas, lengths[2]);
    ordenar(parrillas, lengths[3]);
    escribir_archivo("Pizzerias.dat", pizzerias, lengths[0]);
    escribir_archivo("Heladerias.dat", heladerias, lengths[1]);
    escribir_archivo("Bebidas.dat", bebidas, lengths[2]);
    escribir_archivo("Parrillas.dat", parrillas, lengths[3]);
}

void escribir_archivo(string nombre, Comercio comercios[], int length){
    char char_array[nombre.length() + 1];
    strcpy(char_array, nombre.c_str());
    FILE* archivo = fopen(char_array, "w");
    for (int i = 0; i < length; i++)
        fwrite(&comercios[i], sizeof(Comercio), 1, archivo);
    fclose(archivo);
}

void swap(Comercio *a, Comercio *b){
    Comercio temp = *a;
    *a = *b;
    *b = temp;
}

void ordenar(Comercio comercios[], int length){
    int i, j, min;
    // One by one move boundary of unsorted subarray
    for (i = 0; i < length - 1; i++){
        // Find the minimum element in unsorted array
        min = i;
        for (j = i+1; j < length; j++)
            if (comercios[j].nombre < comercios[min].nombre)
                min = j;
        // Swap the found minimum element with the first element
        swap(&comercios[min], &comercios[i]);
    }
}

void informar(int contador[CANT_ZONAS][CANT_RUBROS]){
    cout << "--- Informacion sobre cada zona ---" << endl;
    int i, j, hay_de_todos;

    for (i = 0; i < CANT_ZONAS; i++){
        cout << "- ZONA " << i+1 << " -" << endl;
        hay_de_todos = 1; // 1 = true; 0 = false
        for (j = 0; j < CANT_RUBROS; j++){
            if (contador[i][j] == 0){
                hay_de_todos = 0;
                cout << "En la zona " << i+1 << " no se incorporaron " << nombre_rubros[j] << endl;
            }
        }
        cout << "En la zona " << i+1 << (hay_de_todos == 1 ? "" : " NO") << " hay comercios para todos los rubros." << endl;
    }
}

void llenar_comercios(Comercio comercios[MAX_COMERCIOS], int contador[CANT_ZONAS][CANT_RUBROS]){
    int k = 0;

    cout << "Ingreso de datos (nombre = \"*\" para finalizar)" << endl;
    cout << "Rubros: 1 para Pizzeria, 2 para Heladeria, 3 para Bebidas y 4 para Parrilla." << endl;

    cout << "-- Nuevo Comercio --" << endl << "Ingrese el nombre: ";
    cin >> comercios[k].nombre;
    while (comercios[k].nombre != "*"){
        cout << "Ingrese el rubro: ";
        cin >> comercios[k].rubro;
        cout << "Ingrese la zona: ";
        cin >> comercios[k].zona;
        if (contador[comercios[k].zona - 1][comercios[k].rubro - 1] < MAX_POR_RUBRO){
            contador[comercios[k].zona - 1][comercios[k].rubro - 1]++;
            k++;
        }else{
            cout << "El ultimo comercio ingresado desbordo la cantidad permitida para su rubro. Intente de nuevo." << endl;
        }
        cout << "-- Nuevo Comercio --" << endl << "Ingrese el nombre: ";
        cin >> comercios[k].nombre;
    }
}
