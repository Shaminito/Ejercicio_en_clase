#include <iostream>
#include <fstream>

using namespace std;

struct nodo{
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
    nodo *sgt;
    nodo *ant;
};

void cogerDatos(ifstream &fin);
void imprimirDatos();
void alumnoViejo(ofstream &fout);
void expedientePar(ofstream &fout);
void expedienteImpar(ofstream &fout);

void pocentajeActividad(ofstream &fout);

void asistencia(ofstream &fout);

nodo *peek;
nodo *lista;

int main() {

    ifstream fin("../Ejercicio prpogramacion con estructuras lineales - RESPUESTAS PEL.tsv");
    ofstream fout("../Resultado.txt");

    cogerDatos(fin);
    //imprimirDatos();
    alumnoViejo(fout);

    expedientePar(fout);
    expedienteImpar(fout);

    pocentajeActividad(fout);
    asistencia(fout);
}

void asistencia(ofstream &fout) {
    try{
        nodo *aux = lista;

        int presencial = 0;
        int hyflex = 0;

        fout<<"Asistencia: "<<endl;
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
        fout<<"Presencial,"<<presencial<<" EN TOTAL: "<<endl;
        while(aux != NULL){
            if(aux -> asistencia == 0){
                fout<<aux -> nombre<<" "<<aux -> apellido<<endl;
            }
            aux = aux -> sgt;
        }

        fout<<endl;

        aux = lista;
        //Hyflex
        fout<<"Hyflex,"<<hyflex<<" EN TOTAL: "<<endl;
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
        nodo *aux = lista;

        float alumnosTotal = 0;
        float entregados = 0;
        float no_entregados = 0;

        fout<<"Actividad Individual 1:"<<endl;

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
        nodo *aux = lista;

        fout<<"Listado de alumnos con expediente impar:"<<endl;

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
        nodo *aux = lista;

        fout<<"Listado de alumnos con expediente par:"<<endl;

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
        nodo *aux = lista;
        nodo *alumnoViejo;
        int oldYear = 9999;

        while(aux != NULL){
            if(oldYear > aux -> year){
                oldYear = aux -> year;
                alumnoViejo = aux;
            }
            aux = aux -> sgt;
        }
        fout<<"Alumno viejo:"<<endl;
        fout<<alumnoViejo->nombre<<" "<<alumnoViejo->apellido<<" "<<", expediente: "<<alumnoViejo->nExpediente<<", año: "<<alumnoViejo->year<<endl<<endl;
    }
    catch(...){
        fout.close();
    }
}

void imprimirDatos() {
    nodo *aux = lista;
    while (aux != NULL){
        cout<<aux->nExpediente<<endl;
        aux = aux -> sgt;
    }
}

void cogerDatos(ifstream &fin) {
    try{
        while(!fin.eof()){
            if(!lista){
                nodo *alumno = new nodo;
                // Inserta elementos en un nodo alum
                fin >> alumno->fecha >> alumno->hora >> alumno->mail >> alumno->nombre >> alumno->apellido >> alumno->asigRpt >> alumno->nExpediente >> alumno->githubUser >> alumno->programacion >> alumno->exposicion >> alumno->actividad >> alumno->mes >> alumno->year >> alumno->asistencia;
                alumno -> sgt = NULL;
                alumno -> ant = NULL;
                lista = alumno;
                peek = alumno;
            }
            else{
                nodo *alumno = new nodo;
                // Inserta elementos en un nodo alum
                fin >> alumno->fecha >> alumno->hora >> alumno->mail >> alumno->nombre >> alumno->apellido >> alumno->asigRpt >> alumno->nExpediente >> alumno->githubUser >> alumno->programacion >> alumno->exposicion >> alumno->actividad >> alumno->mes >> alumno->year >> alumno->asistencia;
                peek -> sgt = alumno;
                alumno -> sgt = NULL;
                alumno -> ant = peek;
                peek = alumno;
            }
        }
    }
    catch(...){
        fin.close();
    }
}
