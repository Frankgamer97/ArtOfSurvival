/*
Appunti gestire la collisione multipla di più proiettili
magari facendo partire la collisione dall'ultimo proiettile
tanti il metodo spara ritorna la struct colpito con cui si
sa da cosa è si è colpiti e anche quante volte ma soprattutto
si può sapere chi è stato colpito (tramite coordinate e carattere)

Crearsi un vettore globale con cui avere un elenco di caratteri con cui non collidere
*/


#include <cstring>
#include <iostream>
#include "Arma.hpp"
//#include "Persona.hpp"
/*using namespace std;

#include <iostream>
//#include <ncurses.h>
#include "Arma.hpp"
#include "Stanza.cpp"
#include "WhiteList.cpp"

*/using namespace std;

Arma::Arma(char Nome[],char proiettile,int num_proiettili,int danni,int gittata,int munizioni,int index){
for(int i=0;i<25;i++)
   this->Nome[i]=Nome[i];
this->proiettile=proiettile;
this->num_proiettili=num_proiettili;
this->danni=danni;
this->gittata=gittata;
this->munizioni=munizioni;
this->index=index;
}

void Arma::setNumProiettili(int num_proiettili){this->num_proiettili=num_proiettili;}
int Arma::getNumProiettili(){return num_proiettili;}
void Arma::setNome(char Nome[]){
 for(int i=0;i<25;i++)
    this->Nome[i]=Nome[i];
}

void  Arma::getNome(char Nome[]){
 for(int i=0;i<25;i++)
   Nome[i]=this->Nome[i];
}
void Arma::setProiettile(char proiettile){this->proiettile=proiettile;}
char Arma::getProiettile(){return proiettile;}
void Arma::setDanni(int danni){this->danni=danni;}
int  Arma::getDanni(){return danni;}
void Arma::setGittata(int gittata){this->gittata=gittata;}
int  Arma::getGittata(){return gittata;}
void Arma::setMunizioni(int munizioni){this->munizioni=munizioni;}
int  Arma::getMunizioni(){return munizioni;}
int  Arma::getIndex(){return index;}
void Arma::setIndex(int index){this->index=index;}
/*
il metodo spara aggiorna le cordinate del carattere del proiettile che
rispecchia il movimento del proiettile stesso finche non incontra un
muro (fatto con lo stesse coordinate dei bordi),scale o porte.
Se incontra un nemico o un aiutante inserisce le coordinate della 
collisione in colpito e delega alla IA capire quale nemico o quale
aiutante è stato colpito. Per la collisione con armi e kit è da decidersi

P.S. questo e lo sparo di un solo proiettile alla volta
     per le mitragliatrici in teoria è necessario un vettore di char o
     di un qualosa di equivalente

*/

/*
0=giu
1=su
2=sx
3=dx
APPUNTO: [getEntity]
se le coordinate vanno al di fuori della stanza ritornare \0
Appunti [PositionProiettile]
se old_coo ha x<0 e y<0 procedere direttamente con la messa a video
il proiettile avanza solo se c'è lo spazio e ritorna true <=> ha colpito una persona

char Stanza::getEntity(coordinate coo){return carattere;}
bool Stanza::PositionProiettile(char proiettile,coordinate old_coo, coordinate new_coo){return true;}

collisione Arma::spara(WhiteList* whitelist, Stanza s,coordinate start,int direzione)
{
 collisione colpito;
 int orizzontale=1;
 int verticale=1;
 if(direzione==0) 
   {
    
    verticale=-1;
    start.y--;
   }
 else if(direzione==1)
   start.y++;
 else if(direzione=2)
   {
    orizzontale=-1;
    start.x--;
   }
 else 
   start.x++;

 WhiteList* base_room_ch;
 base_room_ch=new WhiteList();
 base_room_ch->Add('*');//carattere muro
 base_room_ch->Add('|');//carattere porta
 base_room_ch->Add('.');//carattere scala

 restore_ch restores[num_proiettili];

 bool avanzamento=false;
 bool finito=false;

 coordinate app=start;

 do{
    for(int i=0;i<num_proiettili && !base_room_ch->Search(s.getEntity(app));i++)
      {
       restores[i].coo=app;
       restores[i].ch=s.getEntity(app);
      }

    for(int i=0;i<num_proiettili && !base_room_ch->Search(s.getEntity(app));i++)
      {
        if(avanzamento)
          {
           //ripristino del carattere ch alle coordinate coo del carattere restores[i]
          }
        //**********************************************************
        //fase di scrittura dei proiettili
        int j=0;
        for(j=0;j<num_proiettili && !base_room_ch->Search(s.getEntity(app));j++)
          {    
           if(direzione==0 || direzione==1)
             {
              //scrivi carattere cancellato a coordinate app.x,app.y-1 ed indice
              app.y+=verticale;
             }
       
           else
             app.x=orizzontale;
           // avanzamento=true;
           usleep(5000);//sleep 0.5sec
          }
        if(j<num_proiettili)
          {
           //c'è stata collistione con coordinate in start
           collisione colpito;
           colpito.coo=app;
           colpito.chi=s.getEntity(app);
           colpito.volte=num_proiettili;
           colpito.danno=this->danni;
           for(int z=j;z>=1;z--)
             {
              if(direzione==0 || direzione==1)
               app.y-=z;
              else
               app.x-=z;

              riscrivi carattere sovrapposto(indice vettore num_proiettili-j)
              usleep(5000);
             }
          }
      }
     //**********************************************************
     
     avanzamento=true;
    }
   while(!base_room_ch->Search(s.getEntity(app)));   


  colpito.coo.x=-1;
  colpito.coo.y=-1;
  colpito.chi='\0';
  colpito.volte=0;
  colpito.danno=0; 
  return colpito; 
}
*/
