#include <iostream>
#include <stdio.h>

using namespace std;

struct Repartidor
{
    int dni;
    char nombre[20];
    char apellido[20];
    unsigned zona;
};

void mostrarDatos(int v[], int ce);
void ingresoDatos(int v[], int ce, FILE* arch);

const int CANT_ZONAS = 6;

int main() {
    int zonas[CANT_ZONAS] = {0};
    FILE* archivo = fopen("Repartidores.dat", "w");
    if (archivo == NULL){
        cout << "Error" << endl;
        return 0;
    }
    ingresoDatos(zonas, CANT_ZONAS, archivo);
    fclose(archivo);
    mostrarDatos(zonas, CANT_ZONAS);
    return 0;
}

void ingresoDatos(int zonas[], int cant_zonas, FILE* arch)
{
    Repartidor aux;
    cout << "Ingreso de repartidores (DNI = 0 para finalizar)" << endl;
    cout << "--- Nuevo Repartidor ---" << endl << "Ingrese el DNI: ";
    cin >> aux.dni;

    while (aux.dni != 0) {

        // Ingreso de datos
        cout << "Ingrese el nombre: ";
        cin >> aux.nombre;
        cout << "Ingrese el apellido: ";
        cin >> aux.apellido;
        cout << "Ingrese la zona (del 1 al " << cant_zonas << "): ";
        cin >> aux.zona;

        // Verificar la zona (si es valida, agregarlo al archivo)
        if (aux.zona < 1 || aux.zona > cant_zonas){
            cout << "Error: zona invalida" << endl;
        } else {
            zonas[aux.zona - 1]++;
            fwrite(&aux, sizeof(Repartidor), 1, arch);
        }

        // Ingreso del DNI
        cout << "--- Nuevo Repartidor ---" << endl << "Ingrese el DNI: ";
        cin >> aux.dni;

    }
}

void mostrarDatos(int zonas[], int cant_zonas)
{
    cout << "-- Cantidad de repartidores por zona: --" << endl;
    for(int i = 0; i < cant_zonas; i++){
        if(zonas[i] == 0)
            cout << "No hay repartidores en la zona " << i+1 << endl;
        else
            cout << "En la zona "<< i+1 << " hay " << zonas[i] << " repartidores." << endl;
    }
}
