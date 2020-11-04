#include<iostream>
#include<string.h>

using namespace std;

struct Pedido {
    string domicilio;
    unsigned zona;
    string comercio;
    unsigned rubro;
    unsigned importe;
};

struct Comercio{
    string nombre;
    unsigned zona;
};

struct NodoPedido{
    Pedido dato;
    NodoPedido *sig;
};

const unsigned CANT_ZONAS = 6;
const string nombre_archivos[4] = {"Pizzerias.dat", "Heladerias.dat", "Bebidas.dat", "Parrillas.dat"};

void recibirPedido(NodoPedido* pilas[CANT_ZONAS]);
int getZona(string nombre, unsigned rubro);
void apilarPedido(NodoPedido *&pila, Pedido pedido);
Pedido ingresarDatosPedido();
void asignarPedidos();
void mostrar();
void salir();

int main(){
    NodoPedido* pilas[CANT_ZONAS]; // Pilas de pedidos (una por cada zona)
    unsigned numero = 1; // Opcion del menu
    while (numero >= 1 && numero <=3)
    {
        cout<<"- Menu ----------------------------------------------------------"<<endl;
        cout<<"1: Recibir un pedido / 2: Asignar pedidos / 3: Mostrar / 4: Salir"<<endl;
        cout<<"Ingrese un numero del 1 al 4: ";
        cin>>numero;
        switch (numero){
            case 1: recibirPedido(pilas); break;
            case 2: asignarPedidos(); break;
            case 3: mostrar(); break;
            case 4: salir(); break;
            default: break;
        }
    }
    return 0;
}

void recibirPedido(NodoPedido* pilas[CANT_ZONAS]){
    Pedido p = ingresarDatosPedido();
    int zona = getZona(p.comercio, p.rubro);
    if (zona == p.zona) {
        apilarPedido(pilas[zona-1], p);
        cout<<"Pedido recibido!"<<endl;
    } else {
        cout<<"Error: el comercio no esta inscripto. Ingrese nuevamente los datos."<<endl;
    }
}

// Ingreso de datos para un nuevo pedido
Pedido ingresarDatosPedido(){
    Pedido p;
    cout<<"Ingrese los siguientes datos:"<<endl<<"Domicilio: ";
    cin>>p.domicilio;
    cout<<"Zona: ";
    cin>>p.zona;
    cout<<"Comercio: ";
    cin>>p.comercio;
    cout<<"Rubro (1=Pizzeria 2=Heladeria 3=Bebidas 4=Parrilla): ";
    cin>>p.rubro;
    cout<<"Importe: ";
    cin>>p.importe; 
    return p;
}

// Inserta un pedido en una pila
void apilarPedido(NodoPedido *&pila, Pedido pedido){
    NodoPedido *p;
    p = new NodoPedido;
    p->dato = pedido;
    p->sig = pila;
    pila = p;
}

// Busca un comercio en los archivos y devuelve su zona
int getZona(string nombre, unsigned rubro){
    string nombreArchivo = nombre_archivos[rubro-1];
    char char_array[nombreArchivo.length() + 1];
    strcpy(char_array, nombreArchivo.c_str());
    FILE* archivo = fopen(char_array, "rb");
    if (archivo == NULL) return -1;
    Comercio c;
    fread(&c, sizeof(Comercio), 1, archivo);
    while (!feof(archivo)) {
        if (c.nombre == nombre) {
            fclose(archivo);
            return c.zona;
        }
        fread(&c, sizeof(Comercio), 1, archivo);
    }
    fclose(archivo);
    return -1;
}

void asignarPedidos(){

}

void mostrar(){

}

void salir(){
    
}