#include <iostream>
#include<string.h>

using namespace std;

/*Por cada negocio se ingresa: Nombre de comercio, rubro y código de zona en la que se encuentra.
Se admite un máximo de 10 comercios por rubro por cada zona.*/

struct Comercio{
    string nombre;
    char rubro[20];
    unsigned zona;
};

Comercio ingresoDatos();
void ordenar(struct Comercio v[],unsigned cantidad);
void mostrar(Comercio v[],int cantidad);
void noIngresos(int contPizzeria,int contHeladeria,int contBebidas,int contParrilla);
void controlZonas(Comercio v[],int cantidad);

int main()
{
    unsigned cant,i;
    unsigned cantmax=9;
    int contPizzeria=0,contHeladeria=0,contBebidas=0,contParrilla=0;
     //“Heladerias.dat”, “Pizzeria.dat”, “Bebidas.dat” y “Parrilla.dat”
    cout<<"Comercios a ingresar: ";
    cin>>cant;
    Comercio comerc[cant];
    for(i=0;i<cant;i++)
        {
            comerc[i]=ingresoDatos();
            if(!strcmpi(comerc[i].rubro,"Pizzeria"))
            contPizzeria++;
            if(!strcmpi(comerc[i].rubro,"Heladeria"))
            contHeladeria++;
            if(!strcmpi(comerc[i].rubro,"Bebidas"))
            contBebidas++;
            if(!strcmpi(comerc[i].rubro,"Parrilla"))
            contParrilla++;
            if(contPizzeria>cantmax||contBebidas>cantmax||contHeladeria>cantmax||contParrilla>cantmax)
                {
                    cout<<"El ultimo negocio ingresado desbordo la cantidad permitida para su rubro"<<endl;
                    i--;
                }

        }

    noIngresos(contPizzeria,contHeladeria,contBebidas,contParrilla);
    ordenar(comerc,cant);
    controlZonas(comerc,cant);
    mostrar(comerc,cant);



       /*

    }

    FILE*heladerias;
    heladerias=fopen("Heladerias.dat","wb");
    if(heladerias==NULL)
        cout<<"Error"<<endl;

    FILE*pizzerias;
    pizzerias=fopen("Pizzeria.dat","wb");
    if(pizzerias==NULL)
        cout<<"Error"<<endl;

    FILE*bebidas;
    bebidas=fopen("Bebidas.dat","wb");
    if(bebidas==NULL)
        cout<<"Error"<<endl;

    FILE*parrilla;
    parrilla=fopen("Parrilla.dat","wb");
    if(parrilla==NULL)
        cout<<"Error"<<endl;


}
*/
}
Comercio ingresoDatos()
{
    Comercio ingresado;
    cout<<"Ingrese nombre comercio "<<endl;
    cin>>ingresado.nombre;
    cout<<"Ingrese rubro comercio "<<endl;
    cin>>ingresado.rubro;
    cout<<"Ingrese zona comercio "<<endl;
    cin>>ingresado.zona;
    return ingresado;
}

void ordenar(struct Comercio v[],unsigned cantidad)
{
    unsigned i=0,j;
    Comercio aux;
    bool cambio;
    do
    {
        cambio=false;
        for(j=0;j<cantidad-1-i;j++)
        {
            if(v[j].nombre>v[j+1].nombre)
            {
                aux=v[j];
                v[j]=v[j+1];
                v[j+1]=aux;
                cambio=true;
            }
        }
        i++;
    }while(i<cantidad && cambio);
}

void mostrar(Comercio v[],int cantidad)
{
    for(int i=0;i<cantidad;i++)
        cout<<v[i].nombre<<v[i].rubro<<v[i].zona<<endl;
}

void noIngresos(int contPizzeria,int contHeladeria,int contBebidas,int contParrilla)
{
    cout<<"Informacion general:"<<endl;
    if(!contPizzeria)
        cout<<"No se ingresaron pizzerías"<<endl;
    if(!contHeladeria)
        cout<<"No se ingresaron heladerias"<<endl;
    if(!contBebidas)
        cout<<"No se ingresaron locales de bebidas"<<endl;
    if(!contParrilla)
        cout<<"No se ingresaron parrillas"<<endl;

    cout<<"\n"<<endl;
}

void controlZonas(Comercio v[],int cantidad)
{
    int zona[6][4]={};
    for(int h=0;h<6;h++)
    {
        for(int d=0;d<4;d++)
        {
            cout<<zona[h][d];
        }
    }
    int aux;
    for(int i=0;i<cantidad;i++)
    {
       if(strcmpi(v[i].rubro,"Pizzeria")==0)
       {
          zona[(v[i].zona)-1][0]++;
       }

       if(strcmpi(v[i].rubro,"Heladeria")==0)
       {
          zona[(v[i].zona)-1][1]++;
       }

       if(strcmpi(v[i].rubro,"Bebidas")==0)
       {
           zona[(v[i].zona)-1][2]++;
       }

       if(strcmpi(v[i].rubro,"Parrilla")==0)
       {
           zona[(v[i].zona)-1][3]++;
       }

    }


    for(int i=0;i<6;i++)
    {
        cout<<"Comercios zona "<<i+1<<endl;
        aux=0;
        if(zona[i][0]==0)
        {
            cout<<"No hay Pizzerias en la zona "<<i+1<<endl;
            aux++;
        }
        if(zona[i][1]==0)
        {
            cout<<"No hay Heladerias en la zona "<<i+1<<endl;
            aux++;
        }
        if(zona[i][2]==0)
        {
            cout<<"No hay locales de bebidas en la zona "<<i+1<<endl;
            aux++;
        }
        if(zona[i][3]==0)
        {
            cout<<"No hay Parrillas en la zona "<<i+1<<"\n"<<endl;
            aux++;
        }

        if(!aux)
        cout<<"Hay comercios para todos los rubros en la zona "<<i+1<<endl;

        }
}
