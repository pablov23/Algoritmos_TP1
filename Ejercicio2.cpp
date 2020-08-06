#include <iostream>
#include <string.h>

using namespace std;

/*Por cada negocio se ingresa: Nombre de comercio, rubro y código de zona en la que se encuentra.
Se admite un máximo de 10 comercios por rubro por cada zona.*/

struct Comercio{
    string nombre;
    int rubro;
    unsigned zona;
};

void Informarubros(int contador[6][4]);
void informazonas(int contador[6][4]);

int main()
{
    unsigned i,j,k=0;
    int contador[6][4];
    //se podia inicializar una matriz de otra forma?
    for(i=0;i<6;i++){
        for(j=0;j<4;j++){
            contador[i][j]=0;
        }
    }
    Comercio comerc[240];
    cout<<"Ingrese nombre del comercio. Ingrese un asterisco (*) para finalizar."<<endl;
    cin>>comerc[k].nombre;
    while(comerc[k].nombre!="*"){

        cout<<"Ingrese rubro del comercio. 1 para Pizzeria, 2 para Heladeria, 3 para Bebidas y 4 para Parrilla "<<endl;
        cin>>comerc[k].rubro;
        cout<<"Ingrese zona del comercio "<<endl;
        cin>>comerc[k].zona;
        if(contador[comerc[k].zona-1][comerc[k].rubro-1]<=9){
            contador[comerc[k].zona-1][comerc[k].rubro-1]+=1;
            k++;
        }
            else{
                    cout<<"El ultimo negocio ingresado desbordo la cantidad permitida para su rubro. Intente de nuevo. "<<endl;
        }
        cout<<"Ingrese nombre del comercio. Ingrese un asterisco (*) para finalizar."<<endl;
        cin>>comerc[k].nombre;
    }
    Informarubros(contador);
    informazonas(contador);
    //testeo para mostrar el array contador
    /*
    for(i=0;i<6;i++){
        for(j=0;j<4;j++){
            cout<<contador[i][j]<<endl;

        }
    }*/
}

void Informarubros(int contador[6][4]){
    int i,j,aux;
    cout<<endl;
    for(i=0;i<4;i++){
        aux=0;
        for(j=0;j<6;j++){
            aux+=contador[j][i];
            }
        switch(i){
            case 0:
                if (aux==0)
                    cout<<"No se incorporaron Pizzerias"<<endl;
                    break;
            case 1:
                if (aux==0)
                    cout<<"No se incorporaron Heladerias"<<endl;
                    break;
            case 2:
                if (aux==0)
                    cout<<"No se incorporaron Bebidas"<<endl;
                    break;
            case 3:
                if (aux==0)
                    cout<<"No se incorporaron Parrillas"<<endl;
                    break;
        }
    }
}

void informazonas(int contador[6][4]){
    int i,j,k;
    cout<<endl;
    for(i=0;i<6;i++){
        k=0;
        for(j=0;j<4;j++){
            if(contador[i][j]>0)
                k++;
        }
        if(k==4)
            cout<<"Hay comercios para todos los rubros en la zona "<<i+1<<endl;
    }

}

