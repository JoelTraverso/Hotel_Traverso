#ifndef MENUHABITACIONES_H_INCLUDED
//#include "menuClientes.h"
//#include "misFunciones.h"
#include<cstdlib>
#include<iostream>
#include<stdio.h>
#include<time.h>
#define MENUHABITACIONES_H_INCLUDED




using namespace std;
int menuHabitaciones();

/*class Archivos
{
private:
    FILE *p;
    string arch_usar;
    char tipo[4];
public:
    abrir_archivo(string a,string b)
    {
     p=fopen(a,b);
     if(p==NULL)
        {
            cout<<"Error al abrir el archivo";
            return 0;
        }
     }
};*/
class FechaSistema
{
private:
    int anio,mes,dia,hora,minuto;
    time_t tiempo;
    char cad[80];
    struct tm *tmPtr;
public:
    FechaSistema(int a,int b,int c,int d,int e)
    {
        anio=a;
        mes=b;
        dia=c;
        hora=d;
        minuto=e;
    }
    FechaSistema()
    {
        tiempo = time(NULL);
        tmPtr = localtime(&tiempo);

        anio=tmPtr->tm_year+1900;
        mes=tmPtr->tm_mon+1;
        dia=tmPtr->tm_mday;
        hora=tmPtr->tm_hour;
        minuto=tmPtr->tm_min;
        /*printf("FECHA ACTUAL \n%d/%d/%d %d:%d:%d", tmPtr->tm_mday, tmPtr->tm_mon+1, 1900+tmPtr->tm_year, tmPtr->tm_hour, tmPtr->tm_min, tmPtr->tm_sec);
        strftime(cad, 80, "%A %d de %B de %Y", tmPtr);
        printf("\n\n%s", cad);*/
    }
    int mostar_anio()
    {
        return anio;
    }
    int mostar_mes()
    {
        return mes;
    }
    int mostar_dia()
    {
        return dia;
    }
    int mostar_hora()
    {
        return hora;
    }
    int mostar_minuto()
    {
        return minuto;
    }
};
class Gasto
{
private:
    int id;
    char habitacion[4],tipo;
    float importe;
    char descripcion[240];
    FechaSistema fec;
public:
    void consulta_habitacion(); ///Muestra los gastos correspondientes al ultimo cambio de estado
    void consulta_habitacion_fecha(); ///Muestra los gastos dentro de 2 fechas
    void consulta_habitacion_tipo(); ///Muestra todos los gastos de la habitacion y tipo seleccionado
    void consulta_tipo(); ///Muestra todos los gastos correspondientes al tipo seleccionado
    float get_importe();///Devuelve el importe del gasto
    float get_total(); ///Devuelve el total del ultimo cambio de estado
    void cargar();///carga nuevo gasto
    void anular(); ///anula ultimo gasto
    void modificar(); ///modifica ultimo gasto
};
class Habitacion
{
protected:
    char habitacion[4],estado;
    int id;
};
class Habitacion_ocupada:public Habitacion
{
private:
    char nom_cliente[50],ape_cliente[50];
    char tarj_cliente[17],cod_tarjeta[5],venc_tarjeta[5],dni_cliente[9],serv_contratado[6],hora_limpieza[5],medio_pago;
    bool reserva;
    int tel_cliente;
    float cuenta,pago_adelantado;
    FechaSistema fec_salida,fec_ingreso;
    // Archivos arc;
public:
    void ocupar(); ///Ocupa una habitacion y carga los datos
    void desocupar(); ///Libera una habitacion
    void consultar(); ///Consulta los datos de la habitacion seleccionada
    void consulta_fecha(); ///Consulta los datos de la habitacion entre 2 fechas
};
class Habitacion_mantenimiento:public Habitacion
{
private:
    char descripcion[240];
    float gasto_total;
    int dias_estimado;
public:
    void enviar_mantenimiento(); ///Carga una habitacion al sistema de mantenimiento
    void consultar(); ///Consulta estado de mantenimiento de una habitacion
    void consultar_general(); ///consulta todas las habitaciones en mantenimiento
    void alta();///Da de alta una habitacion y la deja desocupada
};
class Habitacion_reserva:public Habitacion
{
private:
    float pago_adelantado;
    FechaSistema fec_ingreso,fec_salida;
public:
    void consulta(); ///Consulta todas las habitaciones reservadas
    void cancelar(); ///Cancela una reserva
    void cargar  (); ///Carga una nueva reserva
};

void Gasto::cargar()
{
    FILE *g;
    g=fopen("gastos.dat","ab");
    if(g==NULL)
    {
        cout<<"Fallo al abrir el archivo";
        return;
    }
    fseek(g,0,2);
    id=((ftell(g)/sizeof(*this))+1);
    cout<<id;
    cout<<"Ingrese la habitacion que realizo el gasto: ";
    cin>>habitacion;
    cout<<"Ingrese el tipo de gasto: ";
    cin>>tipo;
    cout<<"Ingrese el importe del gasto: $";
    cin>>importe;
    cout<<"Ingrese la descripcion del importe: ";
    cin.ignore();
    cin.getline(descripcion,240);
    fwrite(this,sizeof(*this),1,g);

    fclose(g);

}

void Gasto::consulta_habitacion()
{
    FILE *g;
    g=fopen("gastos.dat","rb");
    if(g==NULL)
    {
        cout<<"Fallo al abrir el archivo";
        return;
    }
    while(fread(this,sizeof(*this),1,g)==1)
    {
        cout<<id<<endl;
        cout<<habitacion<<endl;
        cout<<tipo<<endl;
        cout<<importe<<endl;
        cout<<descripcion<<endl<<endl;
        cout<<"-------------------------------"<<endl;
    }
    fclose(g);
}

#endif // MENUHABITACIONES_H_INCLUDED

