#ifndef IA_Persona_CPP_INCLIDED
#define IA_Persona_CPP_INCLUDED
#include <ncurses.h>
#include <unistd.h>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include "Persona.cpp"
#include "IA_Persona.hpp"

/*
50x5
10x4
100x1
100x2
*/
using namespace std;

IA_Persona::IA_Persona(char nome[50],char tipo[50],char carattere,int vita):Persona(nome,tipo,vita,carattere){
//scudo=false;
}


void IA_Persona::write_object(char stanza[25][91],Oggetto_pos** raccogliere,int num_oggetti){
for(int i=0;i<num_oggetti;i++){

if(raccogliere[i]!=NULL){
   if(raccogliere[i]->oggetto.kit!=NULL)
     stanza[raccogliere[i]->coo.y][raccogliere[i]->coo.x]='+';
   else if(raccogliere[i]->oggetto.arma!=NULL)
     stanza[raccogliere[i]->coo.y][raccogliere[i]->coo.x]='o';
  }//fine if
 }//fine for
}
//****************


bool IA_Persona::passo(Controller* controller,coordinate* new_coordinate,char direction,char stanza[25][91]){
coordinate coo=this->getCoordinate();
coordinate app=coo;
  if(direction==controller->up)
   {
    stanza[coo.y][coo.x]=' ';//nuovo metodo di stanza
    coo.y--;
    if(stanza[coo.y][coo.x]!='*' && stanza[coo.y][coo.x]!='.' && stanza[coo.y][coo.x]!='|' && stanza[coo.y][coo.x]!='-' && stanza[coo.y][coo.x]!='#')
      {
       stanza[coo.y][coo.x]=this->getCarattere();
       if(new_coordinate==NULL)
         this->setCoordinate(coo); 
      } 
    else 
      coo.y++;
   }
  else if(direction==controller->down)
   {
    stanza[coo.y][coo.x]=' ';
    coo.y++;
    if(stanza[coo.y][coo.x]!='*' && stanza[coo.y][coo.x]!='.' && stanza[coo.y][coo.x]!='|' && stanza[coo.y][coo.x]!='-' && stanza[coo.y][coo.x]!='#')
      { 
       stanza[coo.y][coo.x]=this->getCarattere();
       if(new_coordinate==NULL)
          this->setCoordinate(coo); 
      } 
    else
      coo.y--; 
   }
  else if(direction==controller->sx)
   {
    stanza[coo.y][coo.x]=' ';
    coo.x--;
    if(stanza[coo.y][coo.x]!='*' && stanza[coo.y][coo.x]!='.' && stanza[coo.y][coo.x]!='|' && stanza[coo.y][coo.x]!='-' && stanza[coo.y][coo.x]!='#')
      { 
       stanza[coo.y][coo.x]=this->getCarattere();
       if(new_coordinate==NULL)
          this->setCoordinate(coo); 
      } 
    else
      coo.x++; 
   }
  else if(direction==controller->dx)
   {

    stanza[coo.y][coo.x]=' ';
    coo.x++;
    if(stanza[coo.y][coo.x]!='*' && stanza[coo.y][coo.x]!='.' && stanza[coo.y][coo.x]!='|' && stanza[coo.y][coo.x]!='-' && stanza[coo.y][coo.x]!='#')
      { 
       stanza[coo.y][coo.x]=this->getCarattere();
       if(new_coordinate==NULL)
          this->setCoordinate(coo);
      } 
    else
      coo.x--; 
   }


if(new_coordinate!=NULL)
  *new_coordinate=coo;

 if(coo.y==app.y && coo.x==app.x)
   return false;
 return true;
}

bool IA_Persona::getScudo(){return scudo;}

bool IA_Persona::setScudo(bool scudo){this->scudo=scudo;}

bool IA_Persona::raccogli(Controller* controller,char direction,char stanza[25][91],coordinate coo_stanza,Oggetto_pos** raccogliere,int num_oggetti,int* total_time_machine_part_catched,int local_time_machine_part,Time_Machine** time_machine_coo){
//(*total_time_machine_part_catched)++
coordinate persona_coo=this->getCoordinate();
coordinate app=persona_coo;
 if(controller->up==direction)
   app.y--;
 else if(controller->down==direction)
   app.y++;
 else if(controller->sx==direction)
   app.x--;
 else if(controller->dx==direction)
   app.x++;
 else
   return false;

 if((app.y<0 || app.y>24)&&(app.x<0 || app.x>89))
   return false;

 char raccolto=stanza[app.y][app.x];
 bool f_raccolto=false;
 
 Oggetto* zaino[50];
 this->getZaino(zaino);

if(raccolto=='#')
  {
    char raccoglitore[50],tipo[50];
    this->getNome(raccoglitore);
    this->getTipo(tipo);
    if(strcmp(tipo,"Nemico")!=0){
      (*total_time_machine_part_catched)++;
       mvprintw(3,coo_stanza.x+27,"%s ha raccolto un pezzo della macchina del tempo!",raccoglitore);
       refresh();
       usleep(1000000);
       refresh();
       stanza[app.y][app.x]=' ';
       bool trovato=false;
       for(int i=0;i<local_time_machine_part &!trovato;i++)
          if(time_machine_coo[i]->coo.y==app.y && time_machine_coo[i]->coo.x==app.x)
            {time_machine_coo[i]->trovato=true; trovato=true;}
       return true;
      }
    return false;
  }

     for(int i=0;i<num_oggetti && !f_raccolto ;i++)
        {
         if(raccogliere[i]!=NULL)
           if(app.x==raccogliere[i]->coo.x && app.y==raccogliere[i]->coo.y)
           {
             for(int y=0;y<50 && !f_raccolto;y++)
                {
                 if(zaino[y]!=NULL)
                   {
                    if(raccolto=='+')
                      {
                       if(zaino[y]->kit!=NULL)
                         {
                          if(zaino[y]->kit->vita==(raccogliere[i]->oggetto).kit->vita)
                           {
                            
		            zaino[y]->kit->quantita+=(raccogliere[i]->oggetto).kit->quantita;
		            f_raccolto=true;
                            stanza[app.y][app.x]=' ';
                            char raccoglitore[50];
                            char tipo[50];
                            this->getNome(raccoglitore);
                            this->getTipo(tipo);
                            if(strcmp(tipo,"Eroe")==0){
                               mvprintw(3,coo_stanza.x+27,"%s ha raccolto un kit:",raccoglitore);
                               mvprintw(3,coo_stanza.x+27,"vita:%d",(raccogliere[i]->oggetto).kit->vita);
                               mvprintw(3,coo_stanza.x+27,"scorte:%d",(raccogliere[i]->oggetto).kit->quantita);
                               refresh();
                               usleep(1000000);
                              }//stampa a video
                            

                            delete raccogliere[i];
                            raccogliere[i]=NULL;
                            write_object(stanza,raccogliere,num_oggetti);
                            
                           }//aggiornamento vita
                         }//zaino[y]->kit!=NULL
                       }//raccolto=='+'
		     else if(raccolto=='o')
                      {
                       if(zaino[y]->arma!=NULL)
                         {
                          char nome1[25];
                          char nome2[25];
                          zaino[y]->arma->getNome(nome1);
                          (raccogliere[i]->oggetto).arma->getNome(nome2);
                          if(strcmp(nome1,nome2)==0)
                           {      
                            f_raccolto=true;
             zaino[y]->arma->setMunizioni(zaino[y]->arma->getMunizioni()+raccogliere[i]->oggetto.arma->getMunizioni());
                            stanza[app.y][app.x]=' '; 
                            
                            char raccoglitore[50];
                            char tipo[50];
                            this->getNome(raccoglitore);
                            this->getTipo(tipo);
                            if(strcmp(tipo,"Eroe")==0){
                               mvprintw(3,coo_stanza.x+27,"%s ha raccolto %s:",raccoglitore,nome1);
                               refresh();
                               usleep(1000000);
                              }//stampa a video

                            delete raccogliere[i];
                            raccogliere[i]=NULL;                            
                            write_object(stanza,raccogliere,num_oggetti);
                            //getch();
                           }//confronto nomi
                         }//zaino[y]->arma!=NULL
                       }//raccolto=='o'
                    

                   }//controllo zaino!=NULL
                }//fine for dello zaino
             if(!f_raccolto)
               {
                if(!this->addOggetto(raccogliere[i]->oggetto))
                  return false;

                stanza[app.y][app.x]=' '; 
                //delete raccogliere[i];
                char raccoglitore[50];
                char tipo[50];
                this->getNome(raccoglitore);
                this->getTipo(tipo);
                if(strcmp(tipo,"Eroe")==0){
                   if(raccolto=='+'){
                      mvprintw(3,coo_stanza.x+27,"%s ha raccolto un kit:",raccoglitore);
                      mvprintw(3,coo_stanza.x+27,"vita:%d",(raccogliere[i]->oggetto).kit->vita);
                      mvprintw(3,coo_stanza.x+27,"scorte:%d",(raccogliere[i]->oggetto).kit->quantita);
                     }
                  else{
                      char nome_arma[25];
                      (raccogliere[i]->oggetto).arma->getNome(nome_arma);
                      mvprintw(3,coo_stanza.x+27,"%s ha raccolto %s:",raccoglitore,nome_arma);
                     }       
                   refresh();
                   usleep(1000000);   
                  }//stampa a video

                raccogliere[i]=NULL;
                write_object(stanza,raccogliere,num_oggetti);
                return true;
               }//aggiunta dell'oggetto raccolto nello zaino

           }//selezione oggetto raccolto e
        }
     //*******************
 return true;
}


/*
Bug se si spara da troppo vicino ad oggetti,nemici,aiutanti, si richia di cancellare parte della stanza
*/
bool IA_Persona::spara(Controller* controller,char direction,char stanza[25][91],coordinate coo_stanza,Persona* persone[],int num_persone){
//***********************

 Arma* arma=this->getArma();
 bool controllo=true;
 collisione colpito;

 coordinate sparo=this->getCoordinate();
 colpito.coo.y=-1;
 colpito.coo.x=-1;
 colpito.danno=-1;
 colpito.volte=-1;
 colpito.chi='\0';

 if(arma==NULL)
   return false;

 for(int i=0;i<arma->getNumProiettili() && controllo;i++){
     if(controller->up==direction)
        sparo.y--;
     else if(controller->down==direction)
        sparo.y++;
     else if(controller->sx==direction)
        sparo.x--;
     else if(controller->dx==direction)
        sparo.x++;

     if(stanza[sparo.y][sparo.x]=='*' || stanza[sparo.y][sparo.x]=='|'|| stanza[sparo.y][sparo.x]=='-' || stanza[sparo.y][sparo.x]=='.' ||
        stanza[sparo.y][sparo.x]=='T' || stanza[sparo.y][sparo.x]=='N'|| stanza[sparo.y][sparo.x]=='L'|| stanza[sparo.y][sparo.x]=='W'||  
        stanza[sparo.y][sparo.x]=='M'|| stanza[sparo.y][sparo.x]=='C'|| stanza[sparo.y][sparo.x]=='D'|| stanza[sparo.y][sparo.x]=='H'||
        stanza[sparo.y][sparo.x]=='Q'|| stanza[sparo.y][sparo.x]=='J'
       )
       {
        int start=0;
        int fine=0;
        int spazio=0;
        if(controller->up==direction)
          {
           start=this->getCoordinate().y-1;
           fine=sparo.y;
          }
        else if(controller->down==direction)
          {
           start=this->getCoordinate().y+1;
           fine=sparo.y;
          }
        else if(controller->sx==direction)
          {
           start=this->getCoordinate().x-1;
           fine=sparo.x;
          }
        else if(controller->dx==direction)
          {
           start=this->getCoordinate().x+1;
           fine=sparo.x;
          }
        if(fine-start<0)
           spazio=start-fine;
        else
           spazio=fine-start;
        //if(stanza[sparo.y][sparo.x]!='T')
        for(int i=0;i<spazio;i++)
           {
            if(controller->up==direction && stanza[this->getCoordinate().y-1-i][sparo.x]!=this->getCarattere() && 
               stanza[this->getCoordinate().y-1-i][sparo.x]!='#')
              stanza[this->getCoordinate().y-1-i][sparo.x]=' ';   
            else if(controller->down==direction && stanza[this->getCoordinate().y+1+i][sparo.x]!=this->getCarattere() &&
                   stanza[this->getCoordinate().y+1+i][sparo.x]!='#')
              stanza[this->getCoordinate().y+1+i][sparo.x]=' ';
            else if(controller->sx==direction && stanza[sparo.y][this->getCoordinate().x-1-i]!=this->getCarattere() &&
                    stanza[sparo.y][this->getCoordinate().x-1-i]!='#') 
              stanza[sparo.y][this->getCoordinate().x-1-i]=' '; 
            else if(controller->dx==direction && stanza[sparo.y][this->getCoordinate().x+1+i]!=this->getCarattere() &&
                stanza[sparo.y][this->getCoordinate().x+1+i]!='#')
              stanza[sparo.y][this->getCoordinate().x+1+i]=' ';          

            for(int j=0;j<25;j++)
               mvprintw(coo_stanza.y+j,coo_stanza.x,"%s",stanza[j]);
            //mvprintw(coo_stanza.y+(this->getCoordinate()).y,coo_stanza.x+(this->getCoordinate()).x,"%c",this->getCarattere()); 
            for(int z=0;z<num_persone;z++)
               if(persone[z]!=NULL)
                 mvprintw(coo_stanza.y+persone[z]->getCoordinate().y,coo_stanza.x+persone[z]->getCoordinate().x,"%c",persone[z]->getCarattere()); 
            refresh();
            usleep(25000);
            refresh();
           }
        if(stanza[sparo.y][sparo.x]=='T' || stanza[sparo.y][sparo.x]=='N'|| stanza[sparo.y][sparo.x]=='L'|| stanza[sparo.y][sparo.x]=='W'||  
           stanza[sparo.y][sparo.x]=='M' || stanza[sparo.y][sparo.x]=='C'|| stanza[sparo.y][sparo.x]=='D'|| stanza[sparo.y][sparo.x]=='H'||
           stanza[sparo.y][sparo.x]=='Q' || stanza[sparo.y][sparo.x]=='J'
          )
         {
           
          for(int j=0;j<num_persone;j++){
              if(persone[j]!=NULL){
                if(sparo.y==persone[j]->getCoordinate().y && sparo.x==persone[j]->getCoordinate().x)
                  {
                   char pistolero[50];
                   char tipo_vittima[50];
                   char vittima[50];
                   this->getNome(pistolero);
                   persone[j]->getTipo(tipo_vittima);
                   persone[j]->getNome(vittima);
                  
                   stanza[sparo.y][sparo.x]=' ';
                   
                   if(strcmp(tipo_vittima,"Eroe")!=0 || !persone[j]->getScudo())
                     persone[j]->subVita(arma->getDanni()*arma->getNumProiettili());
                   persone[j]->setScudo(false);  
                 /*
                   mvprintw(3,coo_stanza.x+15,"%s ha colpito %s",pistolero,vittima);
                   //mvprintw(5,coo_stanza.x+15,"[PREMERE UN TASTO PER CONTINUARE]");
                   //getch(); 
                   refresh();
                   usleep(1000000);
                   refresh(); */            
               }
             }
            }

          return true;
             
         }
        return false;
       }
       
     else if((sparo.y<0 || sparo.y>24)&&(sparo.x<0 || sparo.x>89))
       controllo=false;
     else{
       if(stanza[sparo.y][sparo.x]==' ')
          stanza[sparo.y][sparo.x]=arma->getProiettile();

       else if(stanza[sparo.y][sparo.x]!='*' && stanza[sparo.y][sparo.x]!='|'&& stanza[sparo.y][sparo.x]!='.' && 
              stanza[sparo.y][sparo.x]!='-' && stanza[sparo.y][sparo.x]!='+' && stanza[sparo.y][sparo.x]!='o' && stanza[sparo.y][sparo.x]!='#')
         {
          
          for(int j=0;j<num_persone;j++){
              if(persone[j]!=NULL)
                if(sparo.y==persone[j]->getCoordinate().y && sparo.x==persone[j]->getCoordinate().x)
                  {
                   
                   char pistolero[50];
                   char vittima[50];
                   char tipo_vittima[50];
                   persone[j]->getTipo(tipo_vittima);
                   persone[j]->getNome(vittima);
                   stanza[sparo.y][sparo.x]=' ';
                   if(strcmp(tipo_vittima,"Eroe")!=0 || !persone[j]->getScudo())
                     persone[j]->subVita(arma->getDanni()*arma->getNumProiettili());
                   persone[j]->setScudo(false); 
/*
                   this->getNome(pistolero);
                   mvprintw(3,coo_stanza.x+15,"%s ha colpito %s",pistolero,vittima);
                   refresh();
                   usleep(1000000);
                   refresh();  */
 //mvprintw(25,0,"persona: %d vita new:%d",j,persone[j]->getVita());
               // refresh();
               // getch();               
              }
             }
         }
       else
         controllo=false;

       for(int j=0;j<25;j++)
         mvprintw(coo_stanza.y+j,coo_stanza.x,"%s",stanza[j]);
       //mvprintw(coo_stanza.y+(this->getCoordinate()).y,coo_stanza.x+(this->getCoordinate()).x,"%c",this->getCarattere()); 
       for(int z=0;z<num_persone;z++)
          if(persone[z]!=NULL)
            mvprintw(coo_stanza.y+persone[z]->getCoordinate().y,coo_stanza.x+persone[z]->getCoordinate().x,"%c",persone[z]->getCarattere());
  
       refresh();
       usleep(25000);
       refresh();
       }//ramo coordinate valide per la stanza
    }//fine primo for
//*************************************************************************************
 if(colpito.chi=='\0')
    {
      int gittata_sparo=0;
      if(controller->up==direction){
       //if(arma->getGittata()-arma->getNumProiettili()<sparo.y-2)
        // gittata_sparo=arma->getGittata()-arma->getNumProiettili();
      // else
         gittata_sparo=sparo.y-1;

       controllo=true;
       for(int i=0;i<gittata_sparo && controllo;i++)
          {
            if(stanza[sparo.y-1][sparo.x]==' ' || stanza[sparo.y-1][sparo.x]=='+' || stanza[sparo.y-1][sparo.x]=='o')
              {
               if(stanza[sparo.y+arma->getNumProiettili()-1][sparo.x]!=this->getCarattere())
                 stanza[sparo.y+arma->getNumProiettili()-1][sparo.x]=' ';
               stanza[--sparo.y][sparo.x]=arma->getProiettile();

               for(int j=0;j<25;j++)
                  mvprintw(coo_stanza.y+j,coo_stanza.x,"%s",stanza[j]);
               //mvprintw(coo_stanza.y+(this->getCoordinate()).y,coo_stanza.x+(this->getCoordinate()).x,"%c",this->getCarattere()); 
               for(int z=0;z<num_persone;z++)
                if(persone[z]!=NULL)
                 mvprintw(coo_stanza.y+persone[z]->getCoordinate().y,coo_stanza.x+persone[z]->getCoordinate().x,"%c",persone[z]->getCarattere()); 
               refresh();
               usleep(25000);
               refresh();
              }
            else if(stanza[sparo.y-1][sparo.x]!='*' && stanza[sparo.y-1][sparo.x]!='|'&& stanza[sparo.y-1][sparo.x]!='-' && 
            stanza[sparo.y-1][sparo.x]!='+' && stanza[sparo.y-1][sparo.x]!='o' && stanza[sparo.y-1][sparo.x]!='.' && stanza[sparo.y-1][sparo.x]!='#')
              {
               //for da controllare[Possibile bug-impossibilie da controllare senza Stanza]
               for(int i=(--sparo.y)+arma->getNumProiettili();i>sparo.y;i--)
                  {
                    if(stanza[i][sparo.x]!=this->getCarattere())
                      stanza[i][sparo.x]=' ';
                    for(int j=0;j<25;j++)
                       mvprintw(coo_stanza.y+j,coo_stanza.x,"%s",stanza[j]);
                      //mvprintw(coo_stanza.y+(this->getCoordinate()).y,coo_stanza.x+(this->getCoordinate()).x,"%c",this->getCarattere()); 
                    for(int z=0;z<num_persone;z++)
                     if(persone[z]!=NULL)
                       mvprintw(coo_stanza.y+persone[z]->getCoordinate().y,coo_stanza.x+persone[z]->getCoordinate().x,"%c",persone[z]->getCarattere());
                    refresh();
                    usleep(25000);
                    refresh();
                  }
              for(int j=0;j<num_persone;j++){
                if(persone[j]!=NULL)
                 if(sparo.y==persone[j]->getCoordinate().y && sparo.x==persone[j]->getCoordinate().x)
                    {
                     char pistolero[50];
                     char vittima[50];
                     char tipo_vittima[50];
                     persone[j]->getTipo(tipo_vittima);
                     persone[j]->getNome(vittima);
                   
                     if(strcmp(tipo_vittima,"Eroe")!=0 || !persone[j]->getScudo())
                       persone[j]->subVita(arma->getDanni()*arma->getNumProiettili());
                     stanza[sparo.y][sparo.x]=' ';
                     persone[j]->setScudo(false); 
                     this->getNome(pistolero);
                    // persone[j]->getNome(vittima);
                     /*mvprintw(3,coo_stanza.x+15,"%s ha colpito %s",pistolero,vittima);
                     refresh();
                     usleep(1000000);
                     refresh();  */
                    }
                   }
              return true;
              }//collisione avvenuta
          }//fine for

       if(colpito.chi=='\0')
         {
          for(int i=sparo.y+arma->getNumProiettili();i>=sparo.y;i--)
                  {
                    stanza[i][sparo.x]=' ';
                    for(int j=0;j<25;j++)
                       mvprintw(coo_stanza.y+j,coo_stanza.x,"%s",stanza[j]);
                    //mvprintw(coo_stanza.y+(this->getCoordinate()).y,coo_stanza.x+(this->getCoordinate()).x,"%c",this->getCarattere()); 
                    for(int z=0;z<num_persone;z++)
                     if(persone[z]!=NULL)
                      mvprintw(coo_stanza.y+persone[z]->getCoordinate().y,coo_stanza.x+persone[z]->getCoordinate().x,"%c",persone[z]->getCarattere()); 
                    refresh();
                    usleep(25000);
                    refresh();
                  }
         }
      }
      else if(controller->down==direction){

       gittata_sparo=arma->getGittata()-arma->getNumProiettili();
       controllo=true;

       for(int i=0;i<gittata_sparo && controllo;i++)
          {
           if(stanza[sparo.y+1][sparo.x]==' ' || stanza[sparo.y+1][sparo.x]=='+' || stanza[sparo.y+1][sparo.x]=='o')
              {
               stanza[sparo.y-arma->getNumProiettili()+1][sparo.x]=' ';
               stanza[++sparo.y][sparo.x]=arma->getProiettile();

               for(int j=0;j<25;j++)
                  mvprintw(coo_stanza.y+j,coo_stanza.x,"%s",stanza[j]);
               //mvprintw(coo_stanza.y+(this->getCoordinate()).y,coo_stanza.x+(this->getCoordinate()).x,"%c",this->getCarattere()); 
               for(int z=0;z<num_persone;z++)
                 if(persone[z]!=NULL)
                  mvprintw(coo_stanza.y+persone[z]->getCoordinate().y,coo_stanza.x+persone[z]->getCoordinate().x,"%c",persone[z]->getCarattere()); 
               refresh();
               usleep(25000);
               refresh();
              }
            else if(stanza[sparo.y+1][sparo.x]!='*' && stanza[sparo.y+1][sparo.x]!='|'&& stanza[sparo.y+1][sparo.x]!='-' && 
            stanza[sparo.y+1][sparo.x]!='+' && stanza[sparo.y+1][sparo.x]!='o' && stanza[sparo.y+1][sparo.x]!='.' && stanza[sparo.y+1][sparo.x]!='#')
              {
               
               //for da controllare[Possibile bug-impossibilie da controllare senza Stanza] srà la falsa riga del successivo

               for(int i=(++sparo.y)-arma->getNumProiettili();i<=sparo.y;i++)
                  {
                    stanza[i][sparo.x]=' ';
                    for(int j=0;j<25;j++)
                       mvprintw(coo_stanza.y+j,coo_stanza.x,"%s",stanza[j]);
                    //mvprintw(coo_stanza.y+(this->getCoordinate()).y,coo_stanza.x+(this->getCoordinate()).x,"%c",this->getCarattere()); 
                    for(int z=0;z<num_persone;z++)
                     if(persone[z]!=NULL)
                      mvprintw(coo_stanza.y+persone[z]->getCoordinate().y,coo_stanza.x+persone[z]->getCoordinate().x,"%c",persone[z]->getCarattere()); 
                    refresh();
                    usleep(25000);
                    refresh();
                  }

               for(int j=0;j<num_persone;j++){
                 if(persone[j]!=NULL)
                  if(sparo.y==persone[j]->getCoordinate().y && sparo.x==persone[j]->getCoordinate().x)
                    {
                     char pistolero[50];
                     char vittima[50];
                     char tipo_vittima[50];
                     persone[j]->getTipo(tipo_vittima);
                     persone[j]->getNome(vittima);
                     stanza[sparo.y][sparo.x]=' ';
                     if(strcmp(tipo_vittima,"Eroe")!=0 || !persone[j]->getScudo())
                       persone[j]->subVita(arma->getDanni()*arma->getNumProiettili());
                     persone[j]->setScudo(false); 
                     this->getNome(pistolero);
                     //persone[j]->getNome(vittima);
                     /*mvprintw(3,coo_stanza.x+15,"%s ha colpito %s",pistolero,vittima);
                     refresh();
                     usleep(1000000);
                     refresh();*/   
                    }
                  }

               return true;
              }//collisione avvenuta
          }//fine for

       if(colpito.chi=='\0')
         {
          for(int i=sparo.y-arma->getNumProiettili();i<=sparo.y;i++)
                  {
                    stanza[i][sparo.x]=' ';
                    for(int j=0;j<25;j++)
                       mvprintw(coo_stanza.y+j,coo_stanza.x,"%s",stanza[j]);
                    //mvprintw(coo_stanza.y+(this->getCoordinate()).y,coo_stanza.x+(this->getCoordinate()).x,"%c",this->getCarattere()); 
                    for(int z=0;z<num_persone;z++)
                     if(persone[z]!=NULL)
                      mvprintw(coo_stanza.y+persone[z]->getCoordinate().y,coo_stanza.x+persone[z]->getCoordinate().x,"%c",persone[z]->getCarattere()); 
                    refresh();
                    usleep(25000);
                    refresh();
                  }
         }
      }
      else if(controller->sx==direction){
       //if(arma->getGittata()-arma->getNumProiettili()<sparo.y-2)
        // gittata_sparo=arma->getGittata()-arma->getNumProiettili();
      // else
         gittata_sparo=sparo.x-1;

       controllo=true;
       for(int i=0;i<arma->getGittata() && controllo;i++)
          {
            if(stanza[sparo.y][sparo.x-1]==' ' || stanza[sparo.y][sparo.x-1]=='+' || stanza[sparo.y][sparo.x-1]=='o')
              {
               if( stanza[sparo.y][sparo.x+arma->getNumProiettili()-1]!=this->getCarattere())
                 stanza[sparo.y][sparo.x+arma->getNumProiettili()-1]=' ';
               stanza[sparo.y][--sparo.x]=arma->getProiettile();

               for(int j=0;j<25;j++)
                  mvprintw(coo_stanza.y+j,coo_stanza.x,"%s",stanza[j]);
               //mvprintw(coo_stanza.y+(this->getCoordinate()).y,coo_stanza.x+(this->getCoordinate()).x,"%c",this->getCarattere()); 
               for(int z=0;z<num_persone;z++)
                 if(persone[z]!=NULL)
                   mvprintw(coo_stanza.y+persone[z]->getCoordinate().y,coo_stanza.x+persone[z]->getCoordinate().x,"%c",persone[z]->getCarattere()); 
               refresh();
               usleep(25000);
               refresh();
              }
            else if(stanza[sparo.y][sparo.x-1]!='*' && stanza[sparo.y][sparo.x-1]!='|'&& stanza[sparo.y][sparo.x-1]!='-' && 
            stanza[sparo.y][sparo.x-1]!='+' && stanza[sparo.y][sparo.x-1]!='o' && stanza[sparo.y][sparo.x-1]!='.' && stanza[sparo.y][sparo.x-1]!='#')
              {
               //for da controllare[Possibile bug-impossibilie da controllare senza Stanza]
               for(int i=(--sparo.x)+arma->getNumProiettili();i>sparo.x;i--)
                  {
                    stanza[sparo.y][i]=' ';
                    for(int j=0;j<25;j++)
                    //mvprintw(coo_stanza.y+(this->getCoordinate()).y,coo_stanza.x+(this->getCoordinate()).x,"%c",this->getCarattere()); 
                    for(int z=0;z<num_persone;z++)
                     if(persone[z]!=NULL)
                      mvprintw(coo_stanza.y+persone[z]->getCoordinate().y,coo_stanza.x+persone[z]->getCoordinate().x,"%c",persone[z]->getCarattere());
                    refresh();
                    usleep(25000);
                    refresh();
                  }

              for(int j=0;j<num_persone;j++){
                if(persone[j]!=NULL)
                 if(sparo.y==persone[j]->getCoordinate().y && sparo.x==persone[j]->getCoordinate().x)
                   {
                    char pistolero[50];
                    char vittima[50];
                    char tipo_vittima[50];
                     persone[j]->getTipo(tipo_vittima);
                     persone[j]->getNome(vittima);
                     stanza[sparo.y][sparo.x]=' ';
                     if(strcmp(tipo_vittima,"Eroe")!=0 || !persone[j]->getScudo())
                       persone[j]->subVita(arma->getDanni()*arma->getNumProiettili());
                     persone[j]->setScudo(false); 
                    this->getNome(pistolero);
                    //persone[j]->getNome(vittima);
                    /*mvprintw(3,coo_stanza.x+15,"%s ha colpito %s",pistolero,vittima);
                    refresh();
                    usleep(1000000);
                    refresh();*/  
                   }
                  }

              return true;
              }//collisione avvenuta
          }//fine for

       if(colpito.chi=='\0')
         {
          for(int i=sparo.x+arma->getNumProiettili();i>=sparo.x;i--)
                  {
                    stanza[sparo.y][i]=' ';
                    for(int j=0;j<25;j++)
                       mvprintw(coo_stanza.y+j,coo_stanza.x,"%s",stanza[j]);
                    //mvprintw(coo_stanza.y+(this->getCoordinate()).y,coo_stanza.x+(this->getCoordinate()).x,"%c",this->getCarattere()); 
                    for(int z=0;z<num_persone;z++)
                     if(persone[z]!=NULL)
                      mvprintw(coo_stanza.y+persone[z]->getCoordinate().y,coo_stanza.x+persone[z]->getCoordinate().x,"%c",persone[z]->getCarattere());
                    refresh();
                    usleep(25000);
                    refresh();
                  }
         }
      }
      if(controller->dx==direction){
      // if(arma->getGittata()-arma->getNumProiettili()<sparo.y-2)
         gittata_sparo=arma->getGittata()-arma->getNumProiettili();

       controllo=true;

       for(int i=0;i<gittata_sparo && controllo;i++)
          {
            if(stanza[sparo.y][sparo.x+1]==' ' || stanza[sparo.y][sparo.x+1]=='+' || stanza[sparo.y][sparo.x+1]=='o')
              {//getch();
               stanza[sparo.y][sparo.x-arma->getNumProiettili()+1]=' ';
               stanza[sparo.y][++sparo.x]=arma->getProiettile();

               for(int j=0;j<25;j++)
                  mvprintw(coo_stanza.y+j,coo_stanza.x,"%s",stanza[j]);
               //mvprintw(coo_stanza.y+(this->getCoordinate()).y,coo_stanza.x+(this->getCoordinate()).x,"%c",this->getCarattere()); 
               for(int z=0;z<num_persone;z++)
                if(persone[z]!=NULL)
                  mvprintw(coo_stanza.y+persone[z]->getCoordinate().y,coo_stanza.x+persone[z]->getCoordinate().x,"%c",persone[z]->getCarattere());  
               refresh();
               usleep(25000);
               refresh();
              }
            else if(stanza[sparo.y][sparo.x+1]!='*' && stanza[sparo.y][sparo.x+1]!='|'&& stanza[sparo.y][sparo.x+1]!='-' && 
            stanza[sparo.y][sparo.x+1]!='+' && stanza[sparo.y][sparo.x+1]!='o' && stanza[sparo.y][sparo.x+1]!='.' && stanza[sparo.y][sparo.x+1]!='#')
              {
               //for da controllare[Possibile bug-impossibilie da controllare senza Stanza] srà la falsa riga del successivo

               for(int i=(++sparo.x)-arma->getNumProiettili();i<=sparo.x;i++)
                  {
                    stanza[sparo.y][i]=' ';
                    for(int j=0;j<25;j++)
                       mvprintw(coo_stanza.y+j,coo_stanza.x,"%s",stanza[j]);
                    //mvprintw(coo_stanza.y+(this->getCoordinate()).y,coo_stanza.x+(this->getCoordinate()).x,"%c",this->getCarattere()); 
                    for(int z=0;z<num_persone;z++)
                     if(persone[z]!=NULL)
                      mvprintw(coo_stanza.y+persone[z]->getCoordinate().y,coo_stanza.x+persone[z]->getCoordinate().x,"%c",persone[z]->getCarattere());
                    refresh();
                    usleep(25000);
                    refresh();
                  }

               for(int j=0;j<num_persone;j++){
                 if(persone[j]!=NULL)
                  if(sparo.y==persone[j]->getCoordinate().y && sparo.x==persone[j]->getCoordinate().x)
                    {
                     char pistolero[50];
                     char vittima[50];
                     char tipo_vittima[50];
                     persone[j]->getTipo(tipo_vittima);
                     persone[j]->getNome(vittima);
                     stanza[sparo.y][sparo.x]=' ';
                     if(strcmp(tipo_vittima,"Eroe")!=0 || !persone[j]->getScudo())
                       persone[j]->subVita(arma->getDanni()*arma->getNumProiettili());
                     persone[j]->setScudo(false); 
                     this->getNome(pistolero);
                     //persone[j]->getNome(vittima);
                     /*mvprintw(3,coo_stanza.x+15,"%s ha colpito %s",pistolero,vittima);
                     refresh();
                     usleep(1000000);
                     refresh();*/  
                    }
                   }
                  

               return true;
              }//collisione avvenuta
          }//fine for

       if(colpito.chi=='\0')
         {
          for(int i=sparo.x-arma->getNumProiettili();i<=sparo.x;i++)
                  {
                    stanza[sparo.y][i]=' ';
                    for(int j=0;j<25;j++)
                       mvprintw(coo_stanza.y+j,coo_stanza.x,"%s",stanza[j]);
                    //mvprintw(coo_stanza.y+(this->getCoordinate()).y,coo_stanza.x+(this->getCoordinate()).x,"%c",this->getCarattere()); 
                    for(int z=0;z<num_persone;z++)
                     if(persone[z]!=NULL)
                      mvprintw(coo_stanza.y+persone[z]->getCoordinate().y,coo_stanza.x+persone[z]->getCoordinate().x,"%c",persone[z]->getCarattere());
                    refresh();
                    usleep(25000);
                    refresh();
                  }
         }
      }

      for(int j=0;j<25;j++)
         mvprintw(coo_stanza.y+j,coo_stanza.x,"%s",stanza[j]);

      //mvprintw(coo_stanza.y+(this->getCoordinate()).y,coo_stanza.x+(this->getCoordinate()).x,"%c",this->getCarattere()); 
      for(int z=0;z<num_persone;z++)
       if(persone[z]!=NULL)
        mvprintw(coo_stanza.y+persone[z]->getCoordinate().y,coo_stanza.x+persone[z]->getCoordinate().x,"%c",persone[z]->getCarattere());;
   
      refresh();
      usleep(25000);
      refresh();
    }
 return false;
}

/*

POSSIBILI DIALOGHI
[Aiutante (terminator buono)] Vieni con me se vuoi vivere! 

[Aiutante (terminator buono)]Ho attraversato il tempo per te 

[Aiutante (terminator buono)]Nessuno torna... Nessuno ritorna a casa. E nessun altro verrà qui. Siamo solo lui e me.

[Aiutante (terminator buono)]
Quei Terminator sono là fuori. Non si può patteggiare con loro, non si può ragionare con88 loro. Non sentono né pietà, né rimorso, né paura. Niente li fermerà prima di averti84 eliminato. Capito? Non si fermeranno mai.42
24


88
88+84
88+84+42
[Aiutante (terminator buono)]Scappa... corri!

[Aiutante (terminator buono)]La sua missione è una sola: distruggere, uccidere

*/

void IA_Persona::dialoga(Persona* giocatore,Persona* persone[],int num_persone,Controller* controller,char direction,char stanza[25][91],coordinate dialogo_coo,int livello){
 
 int index_persona=-1;
 
 if(direction==controller->up){
    for(int i=0;i<num_persone && index_persona<0;i++){
       if(persone[i]!=NULL){
          char tipo[50];
          persone[i]->getTipo(tipo);
          if(giocatore->getCoordinate().y-1==persone[i]->getCoordinate().y && giocatore->getCoordinate().x==persone[i]->getCoordinate().x &&
             strcmp(tipo,(char*)"Aiutante")==0)
             index_persona=i;
         }
         
      }//fine for
   }
 else if(direction==controller->down){
       for(int i=0;i<num_persone && index_persona<0;i++){
       if(persone[i]!=NULL){
          char tipo[50];
          persone[i]->getTipo(tipo);
          if(giocatore->getCoordinate().y+1==persone[i]->getCoordinate().y && giocatore->getCoordinate().x==persone[i]->getCoordinate().x &&
             strcmp(tipo,(char*)"Aiutante")==0)
             index_persona=i;
         }
         
      }//fine for
   }
 else if(direction==controller->sx){
       for(int i=0;i<num_persone && index_persona<0;i++){
       if(persone[i]!=NULL){
          char tipo[50];
          persone[i]->getTipo(tipo);
          if(giocatore->getCoordinate().y==persone[i]->getCoordinate().y && giocatore->getCoordinate().x-1==persone[i]->getCoordinate().x &&
             strcmp(tipo,(char*)"Aiutante")==0)
             index_persona=i;
         }
         
      }//fine for
   }
 else if(controller->dx){
        for(int i=0;i<num_persone && index_persona<0;i++){
       if(persone[i]!=NULL){
          char tipo[50];
          persone[i]->getTipo(tipo);
          if(giocatore->getCoordinate().y==persone[i]->getCoordinate().y && giocatore->getCoordinate().x+1==persone[i]->getCoordinate().x &&
             strcmp(tipo,(char*)"Aiutante")==0)
             index_persona=i;
         }
         
      }//fine for
   }

 if(index_persona>=0){
    
    if((rand()%2)+1==1){
       int dialogo=(rand() % 6)+1;
       if(dialogo==1)
             mvprintw(dialogo_coo.y,dialogo_coo.x,"Vieni con me se vuoi vivere!");
       else if(dialogo==2)
          mvprintw(dialogo_coo.y,dialogo_coo.x,"Ho attraversato il tempo per te");
       else if(dialogo==3)
          mvprintw(dialogo_coo.y,dialogo_coo.x,"Nessuno torna... Nessuno ritorna a casa. E nessun altro verrà qui. Siamo solo io,te e loro");
       else if(dialogo==4)
          mvprintw(dialogo_coo.y,dialogo_coo.x,"Scappa...corri!");
       else if(dialogo==5)
          mvprintw(dialogo_coo.y,dialogo_coo.x,"Loro dicono sempre: La mia missione è una sola: distruggere, uccidere");
       else if(dialogo==6){
             mvprintw(dialogo_coo.y,dialogo_coo.x,"Quei Terminator sono là fuori. Non si può patteggiare con loro, non si può ragionare");
             mvprintw(dialogo_coo.y+1,dialogo_coo.x,"con loro. Non sentono né pietà, né rimorso, né paura. Niente li fermerà prima di"); 
             mvprintw(dialogo_coo.y+2,dialogo_coo.x,"averti eliminato. Capito? Non si fermeranno mai.");
         }
       
       refresh();
       mvprintw(dialogo_coo.y+3,dialogo_coo.x,"[Premere un tasto per continuare]");
       refresh();
       getch();
       
      }
    else{
       int scelta=(rand()%2)+1;
       if(scelta==1)/*da kit*/{
          Oggetto o;
          o.kit=new KIT;
          o.arma=NULL;
          if(livello>10)
            livello=10;
          o.kit->vita=livello*((rand() % 10) +1);
          o.kit->quantita=(rand() % 5) +1;

          if(giocatore->addOggetto(o)){
               mvprintw(dialogo_coo.y+1,dialogo_coo.x,"Hai raccoloto un kit");
               mvprintw(dialogo_coo.y+2,dialogo_coo.x,"vita: %d scorte:%d",o.kit->vita,o.kit->quantita);
              }
          else
              mvprintw(dialogo_coo.y+1,dialogo_coo.x,"Zaino pieno");
          refresh();
          mvprintw(dialogo_coo.y+3,dialogo_coo.x,"[Premere un tasto per continuare]");
          refresh();
          getch();
         }
       else /*da arma*/{
         Oggetto o;
         o.kit=NULL;
         bool scelto=false;
         int scelta;
         do{
            scelta=(rand() %4)+1;
            if((scelta==3 && livello<5) || scelta!=3)
              scelto=true;
           }
         while(!scelto);
         
         if(scelto==1)
           o.arma=new Arma(GLOCK45,PROIETTILE,GLOCK45_MUNIZIONI_PER_SPARO,GLOCK45_DANNI,GLOCK45_GITTATA,GLOCK45_MUNIZIONI,GLOCK45_ID);
         else if(scelto==2)
           o.arma=new Arma(MAGNUM44,PROIETTILE,MAGNUM44_MUNIZIONI_PER_SPARO,MAGNUM44_DANNI,MAGNUM44_GITTATA,MAGNUM44_MUNIZIONI,MAGNUM44_ID);
         else if(scelto==3)
           o.arma=new Arma(MACHINEGUN,PROIETTILE,MACHINEGUN_MUNIZIONI_PER_SPARO,MACHINEGUN_DANNI,MACHINEGUN_GITTATA,MACHINEGUN_MUNIZIONI,MACHINEGUN_ID);
         else if(scelto==4)
           o.arma=new Arma(AK_47,PROIETTILE,AK_47_MUNIZIONI_PER_SPARO,AK_47_DANNI,AK_47_GITTATA,AK_47_MUNIZIONI,AK_47_ID);
         bool controllo=false;
         int j=0;
         
         Oggetto* zaino[50];
         giocatore->getZaino(zaino);
         for(j=0;j<50 && !controllo;j++)
           if(!giocatore->compareOggetto(o,j))
             controllo=true; 

         if(controllo){//arma nuova si tenta di inserirla nello zaino
           if(giocatore->addOggetto(o))
              {
               char nome[25];
               o.arma->getNome(nome);
               mvprintw(dialogo_coo.y+1,dialogo_coo.x,"Hai raccoloto un'arma");
               mvprintw(dialogo_coo.y+2,dialogo_coo.x,"Nome: %s",nome);
              }
            else
              mvprintw(dialogo_coo.y+1,dialogo_coo.x,"Zaino pieno");
          }//arma nuova si tenta di inserirla nello zaino
         else
          {//arma gia esistente si aggiornano le munizioni
           zaino[j]->arma->setMunizioni(zaino[j]->arma->getMunizioni()+o.arma->getMunizioni());
           char nome[25];
           o.arma->getNome(nome);
           mvprintw(dialogo_coo.y+1,dialogo_coo.x,"Hai raccoloto un'arma già presente nel tuo zaino. Munizioni aggiunte");
           mvprintw(dialogo_coo.y+2,dialogo_coo.x,"Nome: %s",nome); 
          }//fine aggiornamento munizioni

          refresh();
          mvprintw(dialogo_coo.y+3,dialogo_coo.x,"[Premere un tasto per continuare]");
          refresh();
          getch();
         }//fine da arma
     }//fine scelta di dare qualcosa al giocatore
   }//fine aiutante presente
 else {
    mvprintw(dialogo_coo.y+3,dialogo_coo.x,"Nessun aiutante nelle vicinanze. Premere un tasto per continuare.");
    refresh();
    getch();
   }
}
#endif /*IA_Persona_CPP_INCLUDED*/
