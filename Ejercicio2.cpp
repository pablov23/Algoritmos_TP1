#include <iostream>
#include<string.h>

using namespace std;

struct Comercio{
    string nombre;
    int rubro;
    unsigned zona;
};

const int MAX_POR_RUBRO = 10;
const int CANT_ZONAS = 6;
const int CANT_RUBROS = 4;

void informar(int contador[CANT_ZONAS][CANT_RUBROS]);

int main()
{
    int k = 0;
    int contador[CANT_ZONAS][CANT_RUBROS] = {0};
    Comercio comercios[240];

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

    informar(contador);
    return 0;
}

void informar(int contador[CANT_ZONAS][CANT_RUBROS]){
    cout << "--- Informacion sobre cada zona ---" << endl;
    int i, j, hay_de_todos;
    string rubros[4] = {"Pizzerias", "Heladerias", "Bebidas", "Parrillas"};
    for (i = 0; i < CANT_ZONAS; i++){
        cout << "- ZONA " << i+1 << " -" << endl;
        hay_de_todos = 1; // 1 = true; 0 = false
        for (j = 0; j < CANT_RUBROS; j++){
            if (contador[i][j] == 0){
                hay_de_todos = 0;
                cout << "En la zona " << i+1 << " no se incorporaron " << rubros[j] << endl;
            }
        }
        cout << "En la zona " << i+1 << (hay_de_todos == 1 ? "" : " NO") << " hay comercios para todos los rubros." << endl;
    }
}
