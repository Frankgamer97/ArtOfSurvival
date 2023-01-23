#include <iostream>
#include <string.h>
#include "Personaggio.cpp"
#include "Giocatore.hpp"
using namespace std;

Giocatore::Giocatore(char nome[],char tipo[],int vita,char carattere):Personaggio(nome,tipo,carattere,vita){
int i=0;
this->num_aiuti=0;
while(i<num_max_aiuti){            //inizializzo il vettore degli aiuti a NULL
    this->aiuti[i]=NULL;
    i++;
    }
}

int Giocatore::addAiutante(Personaggio nuovo){
if(num_aiuti>=num_max_aiuti)
    return -1;

int i=0;
bool controllo=false;
for(i=0;i<num_aiuti && !controllo;i++)
   if(this->aiuti[i]==NULL)
     controllo=true;
/*
while(this->aiuti[i]!=NULL && i<num_aiuti)
    i++;
*/

char nome[50];
char tipo[50];

nuovo.getNome(nome);
nuovo.getTipo(tipo);

if(strlen(nome)==0)//controlli nel caso l'aiutante non abbia un nome
    return -11;

else if(strlen(tipo)==0 || strcmp(tipo,(char*)"Eroe")==0 || strcmp(tipo,(char*)"Nemico")==0)//controllo del tipo dell'aiutante
    return -22;
 
else if(nuovo.getVita()<=0)           //controllo della vita dell'aiutante
    return -33;

else{
    this->aiuti[i]=new Personaggio(nome,tipo,nuovo.getCarattere(),nuovo.getVita());
    this->num_aiuti++;
    return i;
  }
}

bool Giocatore::comparePersona(Personaggio p,int i){
if(i>=num_max_aiuti) return false;  //nel caso la posizione  sia NULL
if(this->aiuti[i]==NULL)
  return false;

char p_nome[50];
char p_tipo[50];

char aiuto_nome[50];
char aiuto_tipo[50];

p.getNome(p_nome);
p.getTipo(p_tipo);
this->aiuti[i]->getNome(aiuto_nome);
this->aiuti[i]->getTipo(aiuto_tipo);
//mvprintw(5,0,"%s-%s",this->aiuti[i]->nome,p.nome);
//getch();
if(strcmp(aiuto_nome,p_nome)==0 && strcmp(aiuto_tipo,p_tipo)==0)
    return true; // nel caso vita,nome e tipo corrispondano
return false;
}

bool Giocatore::removeAiutante(Personaggio aiuto){
int i=0;
bool controllo=false;
for(i=0;i<num_max_aiuti && !controllo;i++)
    controllo=this->comparePersona(aiuto,i);

if(i>=num_max_aiuti || !controllo){  //nel caso siamo arrivati in cima al vettore senza trovarlo
        cout<<"L'aiutante non è stato trovato nel vettore";
        return false;
  }
else{
     delete this->aiuti[i];  //altrimenti vuol dire che l'aiutante è nel vettore e ti sei fermato prima quindi lo elimino
     this->aiuti[i]=NULL;  
     this->num_aiuti--;
     return true;}
}

int Giocatore::getIndexAiutante(Personaggio aiuto){
int i=0;
bool controllo=false;
for(i=0;i<num_max_aiuti && ! controllo;i++)
 controllo=this->comparePersona(aiuto,i);
/*
while(this->comparePersona(aiuto,i)==false && i<10)
{   mvprintw(4,0,"%d",i); refresh() i++; clear();}*/

if(i>=num_max_aiuti)//nel caso sia arrivato in cima al vettore
    return -1;//indice non trovato

return i;
}

bool Giocatore::replaceAiutante(Personaggio old,Personaggio nuovo){
int i=this->getIndexAiutante(old);                      // ottengo l'indice dell'aiutante da rimuovere tramite la funzione getIndexAiutante

char nuovo_nome[50];
char nuovo_tipo[50];

nuovo.getNome(nuovo_nome);
nuovo.getTipo(nuovo_tipo);

if(i==-1){
    cout<<"L'aiutante da sostituire non è presente nella rosa";
    return false;
}else{                                    //cancello cio che puntava la cella dell'array[i] e la vuoto
    if(strlen(nuovo_nome)==0){           //controlli nel caso l'aiutante non abbia un nome
    cout<<"Nessuna sostituzione l'aiutante non ha nome";
    return false;
}else if(strlen(nuovo_tipo)==0 || strcmp(nuovo_tipo,"Giocatore")==0 || strcmp(nuovo_tipo,"Nemico")==0){   //controllo del tipo dell'aiutante
    cout<<"Nessuna sostituzione tipo non valido";
    return false;
}else if(nuovo.getVita()<=0){           //controllo della vita dell'aiutante
    cout<<"Nessuna sostituzione L'aiutante non ha vita";
    return false;
}else{
    delete this->aiuti[i];
    this->aiuti[i]=new Personaggio(nuovo_nome,nuovo_tipo,nuovo.getCarattere(),nuovo.getVita());
    return true;
}
}
}

int Giocatore::getNumAiutanti(){
return this->num_aiuti;
}
