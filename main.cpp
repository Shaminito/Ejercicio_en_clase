#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

time_t now = time(0);
tm *tiempo = localtime(&now);

struct alumno{
    string fecha;
    string hora;
    string mail;
    string nombre;
    string apellido;
    int asigRpt;
    int nExpediente;
    string githubUser;
    int programacion;
    int exposicion;
    int actividad;
    int mes;
    int year;
    int asistencia;
    alumno *sgt;
    alumno *ant;
};

void cogerDatos(ifstream &fin);
void imprimirDatos();
void alumnoViejo(ofstream &fout);
void expedientePar(ofstream &fout);
void expedienteImpar(ofstream &fout);
void pocentajeActividad(ofstream &fout);
void asistencia(ofstream &fout);
void alumnosMes(ofstream &fout);

alumno *peek;
alumno *lista;


int main() {

    ifstream fin("../Ejercicio prpogramacion con estructuras lineales - RESPUESTAS PEL.tsv");
    ofstream fout("../Resultado.txt");
    cogerDatos(fin);
    //imprimirDatos();
    alumnoViejo(fout);
    alumnosMes(fout);
    expedientePar(fout);
    expedienteImpar(fout);
    pocentajeActividad(fout);
    asistencia(fout);
}

void alumnosMes(ofstream &fout) {

    alumno *aux = lista;

    try{
        int mes_actual = tiempo -> tm_mon+1;
        int anio_actual = tiempo ->tm_year+1900;
        fout<<"ALUMNOS QUE CUMPLEN AÑOS ESTE MES:"<<endl;
        while(aux != NULL){
            int edad = anio_actual - aux -> year;
            if(aux -> mes > mes_actual){
                edad--;
            }
            fout<<"Nombre: "<<aux -> nombre<<endl;
            fout<<"Mes de nacimiento: "<<aux -> mes<<endl;
            fout<<"Año de nacimiento: "<<aux -> year<<endl;
            fout<<"Edad: "<<edad<<endl;
            fout<<endl;
            aux = aux -> sgt;
        }
        fout<<endl;
        /*int mes = 1;
        while(mes < 13){
            string alumnos;
            int num_alumnos = 0;
            while(aux != NULL){
                if(aux -> mes == mes){
                    alumnos += aux ->nombre +" "+ aux ->apellido +"\n";
                    num_alumnos++;
                }
                aux = aux -> sgt;
            }
            cout<<"mes: "<<mes<<endl;
            cout<<"alumnos: "<<endl<<alumnos;
            cout<<"Total: "<<num_alumnos<<endl<<endl;
            aux = lista;
            mes++;
        }*/
    }
    catch(...){
        fout.close();
    }
}

void asistencia(ofstream &fout) {
    try{
        alumno *aux = lista;

        int presencial = 0;
        int hyflex = 0;

        fout<<"ASISTENCIA: "<<endl;
        //Números de alumnos quienes asistieron presencialmente y por hyflex
        while(aux != NULL){
            if(aux -> asistencia == 0){
                presencial++;
            }
            else{
                hyflex++;
            }
            aux = aux -> sgt;
        }

        aux = lista;
        //Presencial
        fout<<"PRESENCIAL,"<<presencial<<" EN TOTAL: "<<endl;
        while(aux != NULL){
            if(aux -> asistencia == 0){
                fout<<aux -> nombre<<" "<<aux -> apellido<<endl;
            }
            aux = aux -> sgt;
        }

        fout<<endl;

        aux = lista;
        //Hyflex
        fout<<"HYFLEX,"<<hyflex<<" EN TOTAL: "<<endl;
        while(aux != NULL){
            if(aux -> asistencia == 1){
                fout<<aux -> nombre<<" "<<aux -> apellido<<endl;
            }
            aux = aux -> sgt;
        }
        fout<<endl;
    }
    catch(...){
        fout.close();
    }
}

void pocentajeActividad(ofstream &fout) {
    try{
        alumno *aux = lista;

        float alumnosTotal = 0;
        float entregados = 0;
        float no_entregados = 0;

        fout<<"ACTIVIDAD INDIVIDUAL 1:"<<endl;

        while(aux != NULL){
            if(aux -> actividad == 0){
                entregados++;
            }
            else{
                no_entregados++;
            }
            alumnosTotal++;
            aux = aux -> sgt;
        }
        fout<<"Porcentaje de los que entregaron la actividad: "<<(entregados/alumnosTotal)*100<<"%"<<endl;
        fout<<"Porcentaje de los que entregaron la actividad: "<<(no_entregados/alumnosTotal)*100<<"%"<<endl;
        fout<<endl;
    }
    catch(...){
        fout.close();
    }
}

void expedienteImpar(ofstream &fout){
    try{
        alumno *aux = lista;

        fout<<"LISTADO DE ALUMNOS CON EXPEDIENTE IMPAR:"<<endl;

        while(aux != NULL){
            if(aux -> nExpediente % 2 != 0){
                fout<<aux->nombre<<" "<<aux->apellido<<" "<<", expediente: "<<aux->nExpediente<<endl;
            }
            aux = aux -> sgt;
        }
        fout<<endl;
        //fout<<alumnoViejo->nombre<<" "<<alumnoViejo->apellido<<" "<<", expediente: "<<alumnoViejo->nExpediente<<", año: "<<alumnoViejo->year<<endl;
    }
    catch(...){
        fout.close();
    }
}

void expedientePar(ofstream &fout){
    try{
        alumno *aux = lista;

        fout<<"LISTADO DE ALUMNOS CON EXPEDIENTE PAR:"<<endl;

        while(aux != NULL){
            if(aux -> nExpediente % 2 == 0){
                fout<<aux->nombre<<" "<<aux->apellido<<" "<<", expediente: "<<aux->nExpediente<<endl;
            }
            aux = aux -> sgt;
        }
        fout<<endl;
        //fout<<alumnoViejo->nombre<<" "<<alumnoViejo->apellido<<" "<<", expediente: "<<alumnoViejo->nExpediente<<", año: "<<alumnoViejo->year<<endl;
    }
    catch(...){
        fout.close();
    }
}

void alumnoViejo(ofstream &fout) {
    try{
        alumno *aux = lista;
        alumno *alumnoViejo;
        int oldYear = tiempo ->tm_year+1900;

        while(aux != NULL){
            if(oldYear > aux -> year){
                oldYear = aux -> year;
                alumnoViejo = aux;
            }
            aux = aux -> sgt;
        }
        fout<<"ALUMNO CON MAYOR EDAD:"<<endl;
        fout<<alumnoViejo->nombre<<" "<<alumnoViejo->apellido<<" "<<", expediente: "<<alumnoViejo->nExpediente<<", año: "<<alumnoViejo->year<<endl<<endl;
    }
    catch(...){
        fout.close();
    }
}

void imprimirDatos() {
    alumno *aux = lista;
    while (aux != NULL){
        cout<<aux->nExpediente<<endl;
        aux = aux -> sgt;
    }
}

void cogerDatos(ifstream &fin) {
    try{
        while(!fin.eof()){
            if(!lista){
                alumno *alumn = new alumno;
                // Inserta elementos en un nodo alum
                fin >> alumn->fecha >> alumn->hora >> alumn->mail >> alumn->nombre >> alumn->apellido >> alumn->asigRpt >> alumn->nExpediente >> alumn->githubUser >> alumn->programacion >> alumn->exposicion >> alumn->actividad >> alumn->mes >> alumn->year >> alumn->asistencia;
                alumn -> sgt = NULL;
                alumn -> ant = NULL;
                lista = alumn;
                peek = alumn;
            }
            else{
                alumno *alumn = new alumno;
                // Inserta elementos en un nodo alum
                fin >> alumn->fecha >> alumn->hora >> alumn->mail >> alumn->nombre >> alumn->apellido >> alumn->asigRpt >> alumn->nExpediente >> alumn->githubUser >> alumn->programacion >> alumn->exposicion >> alumn->actividad >> alumn->mes >> alumn->year >> alumn->asistencia;
                peek -> sgt = alumn;
                alumn -> sgt = NULL;
                alumn -> ant = peek;
                peek = alumn;
            }
        }
    }
    catch(...){
        fin.close();
    }
}