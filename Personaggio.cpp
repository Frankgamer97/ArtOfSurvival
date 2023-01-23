#include <ncurses.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include "IA_Persona.cpp"
#include "Personaggio.hpp"
using namespace std;


Personaggio::Personaggio(char Nome[50],char Tipo[50],char carattere,int vita):IA_Persona(Nome,Tipo,carattere,vita){
}

void Personaggio::AutoAction(Controller* controller,char stanza[25][91],coordinate coo_stanza,Persona* personaggi[],int num_personaggi,Oggetto_pos** oggetti,int num_oggetti, int* total_time_machine_part_catched,int local_time_machine_part,Time_Machine** time_machine_coo){



char nome_persona[50];
coordinate persona=this->getCoordinate();
this->getNome(nome_persona);
bool controllo=false;


if(persona.y-1>=0 && persona.y-1<=24)
 {
  if((stanza[persona.y-1][persona.x]=='+') || (stanza[persona.y-1][persona.x]=='o'))
    {
     controllo=true;
     this->raccogli(controller,controller->up,stanza,coo_stanza,oggetti,num_oggetti,total_time_machine_part_catched,local_time_machine_part,time_machine_coo);
    }
 }

else if(persona.y+1>=0 && persona.y+1<=24) 
 { 
  if((stanza[persona.y+1][persona.x]=='+') || (stanza[persona.y+1][persona.x]=='o'))
    {
     this->raccogli(controller,controller->down,stanza,coo_stanza,oggetti,num_oggetti,total_time_machine_part_catched,local_time_machine_part,time_machine_coo);
     controllo=true;
    }
 }

else if(persona.x+1<=89 && persona.x+1>=0)
 {
  if((stanza[persona.y][persona.x+1]=='+') || (stanza[persona.y][persona.x+1]=='o'))
    {
     controllo=true;
     this->raccogli(controller,controller->dx,stanza,coo_stanza,oggetti,num_oggetti,total_time_machine_part_catched,local_time_machine_part,time_machine_coo);
    }
 }

else if(persona.x-1>=0 && persona.x-1<=89)
 { 
  if((stanza[persona.y][persona.x-1]=='+') || (stanza[persona.y][persona.x-1]=='o'))
    {
     controllo=true;
     this->raccogli(controller,controller->sx,stanza,coo_stanza,oggetti,num_oggetti,total_time_machine_part_catched,local_time_machine_part,time_machine_coo);
    }
 }

if(!controllo)
  {
   for(int i=0;i<num_personaggi && !controllo;i++){
       if(personaggi[i]!=NULL){
            char nome_c[50],tipo_c[50];
            personaggi[i]->getNome(nome_c);
            this->getTipo(tipo_c);
 if(
               strcmp(nome_c,nome)!=0 &&
               ((strcmp(tipo_c,"Nemico")==0 && personaggi[i]->getCarattere()!='T') || 
                (strcmp(tipo_c,"Aiutante")==0 && personaggi[i]->getCarattere()=='T'))
   )
{
              //possibile persona da puntatare non è se stesso
               int max_danni=0;
               Oggetto* zaino[50];
               Arma* max=NULL;
               this->getZaino(zaino);
               //scelta dell'arma più forte presente nello zaino
               for(int j=0;j<50;j++){
                   if(zaino[j]!=NULL)
                     if(zaino[j]->arma!=NULL)
                       if(zaino[j]->arma->getDanni()>max_danni){
                          max_danni=zaino[j]->arma->getDanni();
                          max=zaino[j]->arma;
                         }
                   }//fine for di scelta dell'arma
               this->setArma(max);
               coordinate app_persona=personaggi[i]->getCoordinate();
               if(persona.x==app_persona.x){
                  
                  int differenza=persona.y-app_persona.y;
                  if(differenza<0)
                    {
                     if(-1*this->getArma()->getGittata()<differenza){//gittata superiore alla distanza dal personaggio da colpire
                        
                        bool c1=true;
                        for(int j=persona.y;j<app_persona.y && c1;j++)
                          if(stanza[j][persona.x]=='*')
                        c1=false;
                        if(c1)
                          { 
                           controllo=false;
                           bool via=false;
                           for(int i=0;i<local_time_machine_part && !via;i++){
                              if(time_machine_coo[i]!=NULL){
                                 int app=this->getCoordinate().y+1;
                                 if(app>24)
                                    app=24;
                                 if(stanza[app][this->getCoordinate().x]!='#')
                                      { via=true; controllo=true;}
                                    }
                             }//fine for()
                           if(via)
                           this->spara(controller,controller->down,stanza,coo_stanza,personaggi,num_personaggi);
                          }
                       }//fine controllo gittata
                    }
                  else
                    {
                     if(this->getArma()->getGittata()>differenza){//gittata superiore alla distanza dal personaggio da colpire
                        bool c1=true;
                        for(int j=persona.y;j>app_persona.y && c1;j--)
                           if(stanza[j][persona.x]=='*')
                       c1=false;
                       if(c1)
                        { 
                          
                          bool via=false;
                           for(int i=0;i<local_time_machine_part && !via;i++){
                              if(time_machine_coo[i]!=NULL){
                                 int app=this->getCoordinate().y-1;
                                 if(app<0)
                                    app=0;
                                 if(stanza[app][this->getCoordinate().x]!='#')
                                      { via=true; controllo=true;}
                                    }
                             }//fine for()
                           if(via)
                         this->spara(controller,controller->up,stanza,coo_stanza,personaggi,num_personaggi);
                        }
                      }//fine controllo gittata
                    }

                  this->getArma()->setMunizioni(this->getArma()->getMunizioni()-this->getArma()->getNumProiettili());
                 }
               else if(persona.y==app_persona.y){
                  controllo=true;
                  int differenza=persona.x-app_persona.x;
                  if(differenza<0)
                    {
                     if(-1*this->getArma()->getGittata()<differenza){//gittata superiore alla distanza dal personaggio da colpire
                        bool c1=true;
                        for(int j=persona.x;j<app_persona.x && c1;j++)
                           if(stanza[persona.y][j]=='*')
                        c1=false;
                        if(c1)
                          {
                           bool via=false;
                           for(int i=0;i<local_time_machine_part && !via;i++){
                              if(time_machine_coo[i]!=NULL){
                                 int app=this->getCoordinate().x+1;
                                 if(app>89)
                                    app=89;
                                 if(stanza[this->getCoordinate().y][app]!='#')
                                      { via=true; controllo=true;}
                                    }
                             }//fine for()
                           if(via)
                            this->spara(controller,controller->dx,stanza,coo_stanza,personaggi,num_personaggi);
                          }
                       }//fine controllo gittata
                    }
                  else
                    {
                     if(this->getArma()->getGittata()>differenza){//gittata superiore alla distanza dal personaggio da colpire
                        bool c1=true;
                        for(int j=persona.x;j>app_persona.x && c1;j--)
                          if(stanza[persona.y][j]=='*')
                        c1=false;
                        if(c1)
                          {
                           bool via=false;
                           for(int i=0;i<local_time_machine_part && !via;i++){
                              if(time_machine_coo[i]!=NULL){
                                 int app=this->getCoordinate().x-1;
                                 if(app<0)
                                    app=0;
                                 if(stanza[this->getCoordinate().y][app]!='#')
                                      { via=true; controllo=true;}
                                    }
                             }//fine for()
                           if(via) 
                           this->spara(controller,controller->sx,stanza,coo_stanza,personaggi,num_personaggi);
                          }
                        }//fine controllo gittata
                    }                
                  this->getArma()->setMunizioni(this->getArma()->getMunizioni()-this->getArma()->getNumProiettili());
                 }

              }//IA nemico e Aiutante
           }//persona esiste      
      }//fine for

   if(!controllo)//se non è riuscito a sparare a nessuno si muove
     {
      int scelta=(rand()%4)+1;
      if(scelta==1)
        this->passo(controller,NULL,controller->up,stanza); 
      else if(scelta==2)
        this->passo(controller,NULL,controller->down,stanza); 
      else if(scelta==3)
        this->passo(controller,NULL,controller->sx,stanza); 
      else if(scelta==4)
        this->passo(controller,NULL,controller->dx,stanza); 
     }//movimento

  }
}




