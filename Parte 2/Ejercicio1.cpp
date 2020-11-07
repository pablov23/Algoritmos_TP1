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
    NodoPedido* sig;
};
struct ColaPedidos{
    NodoPedido* pri;
    NodoPedido* ult;
};
struct Repartidor
{
    int dni;
    char nombre[20];
    char apellido[20];
    unsigned zona;
};
struct NodoRepartidor
{
    Repartidor dato;
    NodoRepartidor *sigRep;
    NodoPedido *listaPedido;
};

const unsigned CANT_ZONAS = 6;

// Parte 1
void recibirPedido(FILE* archivos[4], ColaPedidos* colas[CANT_ZONAS]);
void encolarPedido(ColaPedidos*&cola, Pedido pedido);
int getZonaComercio(FILE* archivo, string nombre);
Pedido ingresarDatosPedido();
// Parte 2
void asignarPedidos(NodoRepartidor*&lista, ColaPedidos* colas[CANT_ZONAS]);
int getRepartidor(string nombreRep, Repartidor &repartidor);
NodoRepartidor* buscarInsertarRepartidor(NodoRepartidor* &lista, Repartidor rep);
void insertarPedidoPorImporte(NodoPedido*&lista, Pedido pedido);
void desencolarPedido(ColaPedidos*&cola, Pedido &pedido);
void transferirPedidos(NodoPedido*&listaPedido, ColaPedidos*&pedidos, int cantPedidos);
// Partes 3 y 4
void mostrar(NodoRepartidor* listaRep);
void salir();

int main(){
    // Abro los archivos y verifico
    FILE* archivos[4] = {fopen("Pizzerias.dat", "rb"), fopen("Heladerias.dat", "rb"), fopen("Bebidas.dat", "rb"), fopen("Parrillas.dat", "rb")};
    if (archivos[0]==NULL || archivos[1]==NULL || archivos[2]==NULL || archivos[3]==NULL) return 1;
    // Creo un vector con colas (una para cada zona), y lo inicializo
    ColaPedidos* colas[CANT_ZONAS];
    for (unsigned i = 0; i<CANT_ZONAS; i++) colas[i] = new ColaPedidos;
    // Lista de repartidores
    NodoRepartidor* listaRep = NULL;
    // Le muestro un menu de opciones al usuario
    unsigned opcion = 1;
    while (opcion >= 1 && opcion <=3){
        cout<<"- Menu ----------------------------------------------------------"<<endl;
        cout<<"1: Recibir un pedido / 2: Asignar pedidos / 3: Mostrar / 4: Salir"<<endl;
        cout<<"Ingrese un numero del 1 al 4: ";
        cin>>opcion;
        switch (opcion){
            case 1: recibirPedido(archivos, colas); break;
            case 2: asignarPedidos(listaRep, colas); break;
            case 3: mostrar(listaRep); break;
            case 4: salir(); break;
            default: break;
        }
    }
    // Cierro todos los archivos
    fclose(archivos[0]); fclose(archivos[1]); fclose(archivos[2]); fclose(archivos[3]);
    return 0;
}

// Ingresa un nuevo pedido
void recibirPedido(FILE* archivos[4], ColaPedidos* colas[CANT_ZONAS]){
    Pedido p = ingresarDatosPedido();
    int zona = getZonaComercio(archivos[p.rubro-1], p.comercio);
    cout<<"-----------------------------------------------------------------"<<endl;
    if (zona == -1) {
        cout<<"Error: el comercio no esta inscripto. Ingrese nuevamente los datos."<<endl;
    } else {
        encolarPedido(colas[zona-1], p);
        cout<<"Pedido recibido!"<<endl;
    }
}

// Inserta un pedido en una cola
void encolarPedido(ColaPedidos*&cola, Pedido pedido){
    NodoPedido* p;
    p = new NodoPedido;
    p->dato = pedido;
    p->sig = NULL;
    if (cola->pri == NULL) cola->pri = p;
    else cola->ult->sig = p;
    cola->ult = p;
}

// Ingreso de datos para un nuevo pedido
Pedido ingresarDatosPedido(){
    Pedido p;
    cout<<"Domicilio: ";
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

// Busca un comercio en un archivo (con busqueda binaria) y devuelve su zona
int getZonaComercio(FILE* archivo, string nombre){
    Comercio c;
    unsigned desde = 0, hasta, medio;
    fseek(archivo,0,SEEK_END);
    hasta = ftell(archivo)/sizeof(Comercio);
    while(desde <= hasta){
        medio = (desde + hasta) / 2;
        fseek(archivo, medio*sizeof(Comercio), SEEK_SET);
        fread(&c, sizeof(Comercio), 1, archivo);
        // La funcion .compare devuelve -1, 0, ó 1 dependiento el orden alfabetico
        if (nombre.compare(c.nombre) == 0) return c.zona;
        else if (nombre.compare(c.nombre) < 0) hasta=medio-1;
        else desde=medio+1;
    }
    return -1;
}

// Asigna pedidos a un repartidor
void asignarPedidos(NodoRepartidor* &lista, ColaPedidos* colas[CANT_ZONAS]){
    string nombreRep;
    int cantPedidos;
    cout<<"Ingrese nombre del repartidor: ";
    cin>> nombreRep;
    cout<<"Ingrese cantidad de Pedidos: ";
    cin>> cantPedidos;
    cout<<"-----------------------------------------------------------------"<<endl;
    Repartidor r;
    int existe = getRepartidor(nombreRep, r);
    if (existe == -1) {
        cout<<"Error: el repartidor no esta inscripto."<<endl;
        return;
    }
    NodoRepartidor* nodo = buscarInsertarRepartidor(lista, r);
    transferirPedidos(nodo->listaPedido, colas[r.zona-1], cantPedidos);
    cout<<"Pedidos asignados correctamente."<<endl;
}

// Busca un repartidor en el archivo (si no lo encuentra devuelve -1)
int getRepartidor(string nombreRep, Repartidor &repartidor){
    Repartidor r;
    FILE* archivo = fopen("Repartidores.dat", "rb");
    if (archivo == NULL) return -1;
    fread(&r, sizeof(Repartidor), 1, archivo);
    while (!feof(archivo)) {
        if (r.nombre == nombreRep) {
            repartidor = r;
            fclose(archivo);
            return 1;
        }
        fread(&r, sizeof(Repartidor), 1, archivo);
    }
    fclose(archivo);
    return -1;
}

// Busca un repartidor en la lista, y si no esta lo agrega en orden alfabetico
NodoRepartidor* buscarInsertarRepartidor(NodoRepartidor* &lista, Repartidor rep){
    NodoRepartidor *ant, *repLista = lista;
    while(repLista != NULL && strcmp(repLista->dato.nombre, rep.nombre) < 0){
        ant = repLista;
        repLista = repLista->sigRep;
    }
    if(repLista == NULL || strcmp(repLista->dato.nombre, rep.nombre) > 0){
        NodoRepartidor* n = new NodoRepartidor;
        n->dato = rep;
        n->sigRep = repLista;
        if(repLista != lista)
            ant->sigRep = n;
        else
            lista = n;
        return n;
    }
    else
        return repLista;
}

// Inserta un pedido ordenado por su importe
void insertarPedidoPorImporte(NodoPedido*&lista, Pedido pedido){
    NodoPedido *n, *p, *ant;
    n = new NodoPedido;
    n->dato = pedido;
    p = lista;
    while(p != NULL && p->dato.importe < pedido.importe){
        ant = p;
        p = p->sig;
    }
    n->sig = p;
    if(p != lista) ant->sig = n;
    else lista = n;
}

// Saca un pedido de una cola
void desencolarPedido(ColaPedidos*&cola, Pedido &pedido){
    NodoPedido *p = cola->pri;
    pedido = p->dato;
    cola->pri = p->sig;
    delete p;
    if(cola->pri == NULL) cola->ult = NULL;
}

// Transfiere pedidos de una cola a la sublista de un repartidor
void transferirPedidos(NodoPedido*&listaPedido, ColaPedidos*&pedidos, int cantPedidos){
    int contador = 1;
    Pedido p;
    while (pedidos->pri != NULL && contador <= cantPedidos){
        desencolarPedido(pedidos, p);
        insertarPedidoPorImporte(listaPedido, p);
        contador++;
    }
}

// Muestra todos los repartidores y sus pedidos
void mostrar(NodoRepartidor* listaRep){
    cout<<"- Repartidores: -------------------------------------------------"<<endl;
    NodoRepartidor* nr;
    nr = listaRep;
    while(nr != NULL){
        cout<<"Repartidor: "<<nr->dato.nombre<<" "<<nr->dato.apellido<<" (DNI: "<<nr->dato.dni<<", Zona: "<<nr->dato.zona<<")"<<endl;
        cout<<"Pedidos:"<<endl;
        NodoPedido* l = nr->listaPedido;
        while (l != NULL){
            cout<<"- Importe: "<<l->dato.importe<<", Comercio: "<<l->dato.comercio<<", Domicilio: "<<l->dato.domicilio;
            cout<<", Rubro: "<<l->dato.rubro<<", Zona: "<<l->dato.zona<<endl;
            l = l->sig;
        }
        if (nr->sigRep != NULL) cout<<"-----------------------------------------------------------------"<<endl;
        nr = nr->sigRep;
    }
}

void salir(){

}
