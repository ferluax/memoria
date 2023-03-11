/*Codigo del algoritmo fcfs con la hora de llegada
calcula el cpu que se este utilizando, el tiempo de respuesta, espera y el rendimiento*/

#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;

struct procesos 
{
    int pid;
    int hora_llegada; //arrival time
    int tiempo_servicio; // burst time
    int hora_inicio; // start time
    int tiempo_finalizacion; // completion time
    int tiempo_retorno; // turnaround time
    int tiempo_espera; // wainting time
    int tiempo_respuesta; //response time
};

// Primero los procesos se compararan para saber cual es el que debe de comenzar primero 
bool compararLlegada(procesos p1, procesos p2)
{
    return p1.hora_llegada < p2.hora_llegada;
}

bool compararID(procesos p1, procesos p2)
{
    return p1.pid < p2.pid;
}


int main(){

    int n;
    struct procesos p[100];
    float tiempo_retorno_prom;
    float tiempo_espera_prom;
    float tiempo_respuesta_prom;
    float cpu_utilizado; 
    int tiempo_retorno_total =0;
    int tiempo_espera_total =0;
    int tiempo_respuesta_total =0;    
    int tiempo_idle_total =0;    
    float rendimiento;  

    cout<<setprecision(2)<<fixed;

    cout<< "Ingresa el numero de procesos: ";
    cin>>n;

    //Le pedimos al usuario que nos indique cuando fue que llego el proceso y cuanto tiempo estara en el cpu
    for (int i = 0; i < n; i++)
    {
        cout<< "Ingresa la hora de llegada del proceso P"<<i+1<<" : ";
        cin>>p[i].hora_llegada;

        cout<< "Ingresa el tiempo de servicio del proceso P"<<i+1<<" : ";
        cin>>p[i].tiempo_servicio;
        cout<<endl;
    }

    sort(p,p+n,compararLlegada); // Con los tiempos dados estos se compararan para saber cual de los procesos debe de comenzar primero

    
    //con los tiempos de llegada y servicio de los procesos empezaran a entrar y se podra calcular los demas tiempos de finalizacion, retorno, espera y respuesta.
    for (int i = 0; i < n; i++)
    {
        p[i].hora_inicio = (i==0)?            
        p[i].hora_llegada:max(p[i-1].tiempo_finalizacion, p[i].hora_llegada);      
        p[i].tiempo_finalizacion = p[i].hora_inicio + p[i].tiempo_servicio;        
        p[i].tiempo_retorno = p[i].tiempo_finalizacion - p[i].hora_llegada;        
        p[i].tiempo_espera = p[i].tiempo_retorno - p[i].tiempo_servicio;       
        p[i].tiempo_respuesta = p[i].hora_inicio - p[i].hora_llegada;

        tiempo_retorno_total += p[i].tiempo_retorno;
        tiempo_espera_total += p[i].tiempo_espera;
        tiempo_respuesta_total += p[i].tiempo_respuesta;
        tiempo_idle_total +=(i==0)?(p[i].hora_llegada):(p[i].hora_inicio - p[i-1].  tiempo_finalizacion);           
    }

    //Se calcula los tiempo promedio de todos los procesos
    tiempo_retorno_prom = (float)tiempo_retorno_total/n;
    tiempo_espera_prom = (float)tiempo_espera_total/n;
    tiempo_respuesta_prom = (float)tiempo_respuesta_total/n;
    cpu_utilizado = ((p[n-1].tiempo_finalizacion - tiempo_idle_total)/(float)p[n-1].tiempo_finalizacion)*100;
    rendimiento = float(n)/(p[n-1].tiempo_finalizacion - p[0].hora_llegada);

    sort(p,p+n,compararID);
    cout<<endl;


    //Se imprimira los resultados de los procesos
    cout<<"HL\t"<<"TS\t"<<"HI\t"<<"TF\t"<<"TR\t"<<"TE\t"<<"TR\t"<<endl;
    for (int i = 0; i < n; i++)
    {
        cout<<p[i].hora_llegada<<"\t"<<p[i].tiempo_servicio<<"\t"<<p[i].hora_inicio<<"\t"<<p[i].tiempo_finalizacion<<"\t"<<p[i].tiempo_retorno<<"\t"<<p[i].tiempo_espera<<"\t"<<p[i].tiempo_respuesta<<"\n"<<endl;
    }
        cout<<"Tiempo retorno promedio: "<<tiempo_retorno_prom<<endl;
        cout<<"Tiempo espera promedio: "<<tiempo_espera_prom<<endl;
        cout<<"Tiempo respuesta promedio: "<<tiempo_respuesta_prom<<endl;
        cout<<"CPU utilizado: "<<cpu_utilizado<<"%"<<endl;
        cout<<"Rendimiento: "<<rendimiento<<" proceso/unidad de tiempo"<<endl;
    
    return 0;
}