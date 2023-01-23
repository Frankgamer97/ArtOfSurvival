#include <cstring>
#include <iostream>
#include <ncurses.h>
#include "Arma.cpp"
#include "Persona.hpp"
using namespace std;


Persona::Persona(char nome[50],char tipo[50],int vita,char carattere){ //costruttore dell'oggetto persona
this->vita=vita;
this->carattere=carattere;
strcpy(this->nome,nome);
strcpy(this->tipo,tipo);
arma_corrente=NULL;
scudo=false;

for(int i=0;i<50;i++)
   zaino[i]=NULL;
}

void Persona::getNome(char nome[50]){ //ritorna il nome del personaggio

strcpy(nome,this->nome);
}

void Persona::getTipo(char tipo[]){//ritorna il tipo del personaggio
strcpy(tipo,this->tipo);
}

char Persona::getCarattere(){
return carattere;
}

void Persona::setCarattere(char carattere){
this->carattere=carattere;
}

bool Persona::getScudo(){//ritorna lo stato dello scudo
return scudo;
}

void Persona::setScudo(bool scudo){//modifica lo stato dello scudo
this->scudo=scudo;
} 

void Persona::addVita(int vita){ //incrementa la vita
this->vita=this->vita+vita;
if(this->vita>500){     //nel caso l'incremento di vita superi la vita massima
    this->vita=500;
}
}

void Persona::subVita(int vita){ //decrementa la vita
this->vita=this->vita-vita;
if(this->vita<=0){        
    this->vita=0;//controllo nel caso la vita del personaggio scenda a 0,esso perde la partita
    //cout<<"YOU LOSE"<<" ";  
}
}

int Persona::getVita(){ //restituisce quanta vita ha il personaggio attualmente
return this->vita;
}

Arma* Persona::getArma(){//ritorna l'arma corrente della persona
return arma_corrente;
}
void Persona::setArma(Arma* arma_corrente){//modifica l'arma corrente della persona
Oggetto o;
bool controllo=false;
o.kit=NULL;
o.arma=arma_corrente;
for(int i=0;i<50 && !controllo;i++){
  if(this->compareOggetto(o,i))
    controllo=true;
}
if(controllo)
  this->arma_corrente=arma_corrente;
}

bool Persona::addOggetto(Oggetto o){ //aggiunge un oggetto allo zaino
int i=0;

if(o.kit!=NULL && o.arma!=NULL) //controllo nel caso l'oggetto è sia kit che arma
    return false;
else if(o.kit==NULL && o.arma==NULL)// controllo nel caso l'oggetto non è ne arma ne kit
  return false;

while(this->zaino[i]!=NULL && i<50) i++; //raggiunge la prima posizione dello zaino vuota
if(i>=50) return false;
else
 {
    this->zaino[i]=new Oggetto;
    this->zaino[i]->kit=o.kit;
    this->zaino[i]->arma=o.arma;
    return true;
 }
}


bool Persona::compareOggetto(Oggetto o,int i){
if(this->zaino[i]==NULL) return false;  //nel caso la posizione dello zaino sia NULL

if(o.kit!=NULL && this->zaino[i]->kit!=NULL)
   {//nel caso sia un kit
    if(this->zaino[i]->kit->vita==o.kit->vita /*&& this->zaino[i]->kit->quantita==o.kit->quantita*/)
        return true;
    else
        return false;   
   }
else if(o.arma!=NULL && this->zaino[i]->arma!=NULL)
   {   //nel caso sia un arma 
    char arma_zaino[50];
    char arma_corrente[50];
    this->zaino[i]->arma->getNome(arma_zaino);
    o.arma->getNome(arma_corrente);
    if(strcmp(arma_zaino,arma_corrente)==0)
       return true;
    else 
       return false;
   }
else return false;
}

void Persona::removeOggetto(Oggetto o){ //rimuove dallo zaino l'oggetto passatogli come parametro
    /*int i=0;
   while((compareOggetto(o,i))==false && i<50) { //vado a cercare l'oggetto nello zaino
    i++;
   }*/
    int i=0;
    if((i=this->getIndexOggetto(o))>=0){
    delete this->zaino[i];
    this->zaino[i]=NULL;
    }
}


int Persona::getIndexOggetto(Oggetto o){                      //ritorna l'indice dello zaino in cui si trova l'oggetto passatogli come parametro
int i=0;
while((compareOggetto(o,i))==false && i<50){                    //vado a cercare l'oggetto nello zaino
    i++;
}
if(i==50)
  return -1; //indice non trovato
return i;
}


void Persona::getZaino(p_oggetto newZaino[50]){ //copia il contenuto dello zaino attuale del personaggio in un altro zaino
    for(int i=0;i<50;i++){
        newZaino[i]=this->zaino[i];
    }
}

void Persona::setCoordinate(coordinate coo){ //aggiorna le coordinate del personaggio
this->coo.x=coo.x;
this->coo.y=coo.y;
}


coordinate Persona::getCoordinate(){ //ritorna le coordinate del personaggio
return this->coo;
}
