#include <iostream>


using namespace std;

void mostrarDatos(struct Repartidor repart[],int cantidad);
Repartidor ingresoDatos();

struct Repartidor
{
    int dni;
    char nombre[20];
    char apellido[20];
    unsigned zona;

};
int main()
{
    int cant,i;
    FILE*repartidores;
    repartidores=fopen("Repartidores.dat","wb");
    if(repartidores==NULL)
        cout<<"Error"<<endl;
    else
    {
        cout<<"Repartidores a ingresar: ";
        cin>>cant;
        Repartidor repart[cant];
        for(i=0;i<cant;i++)
        {
            cout<<"Repartidor N "<<i+1<<endl;
            repart[i]=ingresoDatos();
            fwrite(&repart[i],sizeof(Repartidor),1,repartidores);
        }
        fclose(repartidores);
        mostrarDatos(&repart[0],cant);
    }
    return 0;
}

Repartidor ingresoDatos()
{
    Repartidor auxiliar;
    cout<<"Ingrese DNI repartidor "<<endl;
    cin>>auxiliar.dni;
    cout<<"Ingrese nombre repartidor "<<endl;
    cin>>auxiliar.nombre;
    cout<<"Ingrese apellido repartidor "<<endl;
    cin>>auxiliar.apellido;
    cout<<"Ingrese zona repartidor "<<endl;
    cin>>auxiliar.zona;
    return auxiliar;
}

void mostrarDatos(struct Repartidor repart[],int cantidad)
{
    int j;
    int zona[]={0,0,0,0,0,0};
            for(j=0;j<cantidad;j++){


                switch(repart[j].zona)
                {
                case 1:
                    zona[0]++;
                    break;
                case 2:
                    zona[1]++;
                    break;
                case 3:
                    zona[2]++;
                    break;
                case 4:
                    zona[3]++;
                    break;
                case 5:
                    zona[4]++;
                    break;
                case 6:
                    zona[5]++;
                    break;
                default:
                    cout<<"Error";

         }

}
    cout<<"Cantidad de repartidores por zona:"<<endl;
     for(j=0;j<6;j++){
            cout<<"Zona: "<<j+1<<endl;
            if(zona[j]==0)
                cout<<" No hay repartidores en la zona "<<endl;
            else
                cout<<" Cantidad de repartidores: "<<zona[j]<<endl;

     }
}

