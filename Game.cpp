/*
UNICO BUG VISIBILITA DEI PERSONAGGI A TRATTI
*/

#include <cstring>
#include <fstream>
#include <ncurses.h>
#include "Animazioni.cpp"
#include "Game.hpp"
using namespace std;

Game::Game(Giocatore* gamer){
//coordinate inizili del giocatore
total_time_machine_part_catched=0;
coordinate coo;
coo.y=1;
coo.x=44;
gamer->setCoordinate(coo);
this->gamer=gamer;

pre_stanza=NULL;

livello_corrente=new Livello(gamer,NULL,3,1,total_time_machine_part);
stanza=livello_corrente->s;

num_time_machine_part=0;

for(int i=0;i<STANZA_Y;i++)
   for(int j=0;j<STANZA_X;j++)
     if(stanza->stanza[i][j]=='#')
       num_time_machine_part++;

time_machine_part_coo=(Time_Machine**)malloc(num_time_machine_part*sizeof(Time_Machine*));

for(int i=0;i<num_time_machine_part;i++){
   time_machine_part_coo[i]=new Time_Machine;
   time_machine_part_coo[i]->trovato=false;
  }

int contatore=0;
for(int i=0;i<STANZA_Y;i++)
   for(int j=0;j<STANZA_X;j++)
     if(stanza->stanza[i][j]=='#')
       {
        time_machine_part_coo[contatore]->coo.y=i;
        time_machine_part_coo[contatore++]->coo.x=j;
       }
stanza->aggiornaAiutanti(gamer);
stanza_coo.y=7;
stanza_coo.x=35;
//***********impostazione coordinate aiutanti di base*****************
for(int i=0;i<gamer->num_max_aiuti;i++){
               if(gamer->aiuti[i]!=NULL){
               coordinate coo_aiutante;
               coo_aiutante.x=rand() % STANZA_X;
               coo_aiutante.y=rand() % STANZA_Y;
               while(stanza->stanza[coo_aiutante.y][coo_aiutante.x]!=' ')
                 {
                  coo_aiutante.x=rand() % STANZA_X;
                  coo_aiutante.y=rand() % STANZA_Y;
                 }
               gamer->aiuti[i]->setCoordinate(coo_aiutante);
              }//fine aggiornamento vecchi aiutanti nella nuova stanza
             }//fine for

//**********************Impostazioni turni inziali di gioco********************************

turni=(Turno**)malloc((stanza->num_max_nemici+gamer->num_max_aiuti+1)*sizeof(Turno*));
int ii=0,jj=0;

for(int j=0;j<stanza->num_max_nemici+gamer->num_max_aiuti+1;j++)
   turni[j]=NULL;

for(int i=0;i<stanza->num_nemici+gamer->num_aiuti+1 || ii<gamer->num_aiuti && jj<stanza->num_nemici;i++)
   {
    if(i==0)
      {
       turni[i]=new Turno;
       turni[i]->persona=gamer;
       turni[i]->turno=true;
      }
    else if(i>0 && ii<gamer->num_aiuti)
      {  
       if(gamer->aiuti[ii]==NULL)
          {
           if(stanza->nemici[jj]!=NULL){
             turni[i]=new Turno;
             turni[i]->persona=stanza->nemici[jj++];
             turni[i]->turno=false;
            }
           else 
            { 
              i--; 
              jj++; 
              ii++;
            }
          }//si passa subito ai nemici
       else{
            if(gamer->aiuti[ii]!=NULL){
            turni[i]=new Turno;
            turni[i]->persona=gamer->aiuti[ii++];
            turni[i]->turno=false;}
           }
      }
     else if(i>0 && stanza->nemici[jj]!=NULL){
          turni[i]=new Turno;
          turni[i]->persona=stanza->nemici[jj++];
          turni[i]->turno=false;
         }
     else i--;
   }
//*******************************************************

//generazione oggetto per animazioni
animazioni=new Animazioni();
//impostazione comandi standard
controller=new Controller;
controller->up='w';
controller->down='s';
controller->sx='a';
controller->dx='d';
controller->porta=' ';
controller->zaino='2';
controller->sparo=10;
controller->dialoga='3';
controller->raccogli='+';
controller->menu='9';
}

Controller* Game::getController(){return controller;}
Animazioni* Game::getAnimazioni(){return animazioni;}

void Game::draw_details(){
  char nome[50];
  gamer->getNome(nome);
  char scudo[4];
  if(gamer->getScudo())
     strcpy(scudo,"on ");
  else 
     strcpy(scudo,"off");

  //TITOLO

  int x,y;
  getmaxyx(stdscr,y,x);
  mvprintw(1,(x/2)-8,"ART OF SURVIVAL");
  //PARAMETRI
  mvprintw(5,1,"[#] pezzi macchina del tempo %d/%d",total_time_machine_part_catched,total_time_machine_part);
  mvprintw(8,15,"nome: %s",nome);
  mvprintw(11,15,"vita: %d",gamer->getVita());
  mvprintw(14,15,"scudo: %s",scudo);
  mvprintw(17,15,"compagni: %d",gamer->num_aiuti);
  mvprintw(20,15,"nemici: %d",stanza->num_nemici);
  if(gamer->getArma()==NULL)
    mvprintw(23,15,"arma: none");
  else
    {
     if(gamer->getArma()->getMunizioni()<=0)
       {
        gamer->setArma(NULL);
        mvprintw(23,15,"arma: none");
       }
     char nome_arma[50];
     gamer->getArma()->getNome(nome_arma);
     mvprintw(23,15,"arma: %s",nome_arma);
     mvprintw(25,15,"Munizini: %d",gamer->getArma()->getMunizioni());
    }

  mvprintw(27,15,"Stanza: %d",stanza->getIndexStanza()+1);
  mvprintw(29,15,"Livello:%d",stanza->getIndexLivello());
  //COMANDI-LISTA

  if(controller->up==' ')
     mvprintw(33,30,"SPACE: SU");
  else if(controller->up==10)
     mvprintw(33,30,"INVIO: SU");
  else
     mvprintw(33,30,"%c: SU",controller->up);

  if(controller->down==' ')
    mvprintw(35,30,"SPACE: GIU");
  else if(controller->down==10)
    mvprintw(35,30,"INVIO: GIU");
  else
    mvprintw(35,30,"%c: GIU",controller->down);

  if(controller->sx==' ')
    mvprintw(37,30,"SPACE: SX");
  else if(controller->sx==10)
    mvprintw(37,30,"INVIO: SX");
  else
    mvprintw(37,30,"%c= SX",controller->sx);

  if(controller->dx==' ')
    mvprintw(39,30,"SPACE: DX");
  else if(controller->dx==10)
    mvprintw(39,30,"INVIO: DX");
  else
    mvprintw(39,30,"%c: DX",controller->dx);

  if(controller->sparo==' ')
    mvprintw(33,55,"SPACE:\t SPARA");
  else if(controller->sparo==10)
    mvprintw(33,55,"INVIO:\t SPARA");
  else 
    mvprintw(33,55,"%c:\t SPARA",controller->sparo);
  
  
  if(controller->zaino==' ')
    mvprintw(35,55,"SPACE:\t ZAINO");
  else if(controller->zaino==10)
    mvprintw(35,55,"INVIO:\t ZAINO");
  else 
    mvprintw(35,55,"%c:\t ZAINO",controller->zaino);

  if(controller->dialoga==' ')
    mvprintw(37,55,"SPACE=\t DIALOGA");
  else if(controller->dialoga==10)
    mvprintw(37,55,"INVIO:\t DIALOGA");
  else 
    mvprintw(37,55,"%c:\t DIALOGA",controller->dialoga);

  if(controller->raccogli==' ')
   mvprintw(33,90,"\tSPACE:\t RACCOGLI");
  else if(controller->raccogli==10)
   mvprintw(33,90,"\tINVIO:\t RACCOGLI");
  else
   mvprintw(33,90,"\t%c:\tRACCOGLI",controller->raccogli);

  if(controller->porta==' ')
    mvprintw(35,90,"\tSPACE:\t APRI/CHIUDI PORTA");
  else if(controller->porta==10)
    mvprintw(35,90,"\tINVIO:\t APRI/CHIUDI PORTA");
  else
    mvprintw(35,90,"\t%c:\t APRI/CHIUDI PORTA",controller->porta);
  mvprintw(37,90,"\t%c:\tMENU'",controller->menu);

for(int i=0;i<25;i++)
   for(int j=0;j<91;j++)
      {
       if(stanza->stanza[i][j]=='F' || stanza->stanza[i][j]=='N' || stanza->stanza[i][j]=='L' || stanza->stanza[i][j]=='W' ||
          stanza->stanza[i][j]=='M' || stanza->stanza[i][j]=='C' || stanza->stanza[i][j]=='D' || stanza->stanza[i][j]=='O' ||
          stanza->stanza[i][j]=='J' || stanza->stanza[i][j]=='T')
          stanza->stanza[i][j]=' ';
       else if(stanza->stanza[i][j]=='#')
          stanza->stanza[i][j]='#';
      }

  for(int i=1;i<stanza->num_max_nemici+gamer->num_max_aiuti+1;i++)
     {
      if(turni[i]!=NULL)
        if(turni[i]->persona!=NULL){
         /*_cleaned*/stanza->stanza[turni[i]->persona->getCoordinate().y][turni[i]->persona->getCoordinate().x]=turni[i]->persona->getCarattere();
         refresh();
        }
     }

  for(int YY=0;YY<25;YY++)
     mvprintw(stanza_coo.y+YY,stanza_coo.x,"%s",stanza->stanza[YY]);
  refresh();

  mvprintw(stanza_coo.y+(gamer->getCoordinate()).y,stanza_coo.x+(gamer->getCoordinate()).x,"%c",gamer->getCarattere());
  refresh();
 

 for(int i=0;i<num_time_machine_part;i++)
    if(!time_machine_part_coo[i]->trovato){
       mvprintw(stanza_coo.y+time_machine_part_coo[i]->coo.y,stanza_coo.x+time_machine_part_coo[i]->coo.x,"#");
       refresh(); 
      }
}

void Game::aggiorna_turni(){
for(int j=0;j<stanza->num_max_nemici+gamer->num_max_aiuti+1;j++)
   turni[j]=NULL;
int ii=0,jj=0;
for(int i=0;i<stanza->num_nemici+gamer->num_aiuti+1 || ii<gamer->num_aiuti && jj<stanza->num_nemici;i++)
   {
    if(i==0)
      {
       turni[i]=new Turno;
       turni[i]->persona=gamer;
       turni[i]->turno=true;
      }
    else if(i>0 && ii<gamer->num_aiuti)
      {  
       if(gamer->aiuti[ii]==NULL)
          {
           if(stanza->nemici[jj]!=NULL/* && jj<stanza->num_nemici*/){
             turni[i]=new Turno;
             turni[i]->persona=stanza->nemici[jj++];
             turni[i]->turno=false;
            }
           else 
            { 
              i--; 
              jj++; 
              ii++;
            }
          }//si passa subito ai nemici
       else{
            if(gamer->aiuti[ii]!=NULL){
            turni[i]=new Turno;
            turni[i]->persona=gamer->aiuti[ii++];
            turni[i]->turno=false;}
           }
      }
     else if(i>0 && stanza->nemici[jj]!=NULL){
          turni[i]=new Turno;
          turni[i]->persona=stanza->nemici[jj++];
          turni[i]->turno=false;
         }
     else i--;
   }
 
}

void Game::aggiorna_time_machine_part_coo(){


for(int i=0;i<num_time_machine_part;i++)
   {
    mvprintw(stanza_coo.y+time_machine_part_coo[i]->coo.y,stanza_coo.x+time_machine_part_coo[i]->coo.x," ");
    refresh(); 
    delete time_machine_part_coo[i]; 
   }

num_time_machine_part=0;
for(int i=0;i<STANZA_Y;i++)
   for(int j=0;j<STANZA_X;j++)
     if(stanza->stanza[i][j]=='#')
       num_time_machine_part++;

time_machine_part_coo=(Time_Machine**)malloc(num_time_machine_part*sizeof(Time_Machine*));

for(int i=0;i<num_time_machine_part;i++){
   time_machine_part_coo[i]=new Time_Machine;
   time_machine_part_coo[i]->trovato=false;
  }

int contatore=0;
for(int i=0;i<STANZA_Y;i++)
   for(int j=0;j<STANZA_X;j++)
     if(stanza->stanza[i][j]=='#')
       {
        time_machine_part_coo[contatore]->coo.y=i;
        time_machine_part_coo[contatore++]->coo.x=j;
       }


}

//QUA INCOMINCIERA IL GIOCO
void Game::start(){
Stanza* first=stanza;
//Appena terminata la IA_persona per quanto mi è possibile al momento testare realmente incremento e decremento dello zaino
//con inserimeni fatti dalla stanza corrente (anche se ancora fittizzia)

 bool uscita=false;
 char comando;
 char last_direction='\0';
 int token_turno=0;
 int total_edited_time_machine_part=num_time_machine_part;

 do{
    clear();
    draw_details();
    for(int i=0;i<1+gamer->num_max_aiuti+stanza->num_max_nemici;i++)
       {
         if(turni[i]!=NULL)
            if(turni[i]->persona!=NULL){
             if(i==0 && turni[0]->persona->getVita()<=0){
               clear();
               animazioni->gameover();
               return;
               }
              if(i>0 && turni[i]->persona->getVita()<=0)
               {
                char tipo[50];
                turni[i]->persona->getTipo(tipo);
                if(strcmp(tipo,"Aiutante")==0){
                    mvprintw(stanza_coo.y+turni[i]->persona->getCoordinate().y,stanza_coo.x+turni[i]->persona->getCoordinate().x," ");
                    refresh();
                    gamer->removeAiutante(*turni[i]->persona);
                    turni[i]->persona=NULL;
                    turni[i]->turno=false;
                   }
                else if(strcmp(tipo,"Nemico")==0){
                bool finito=false;
                for(int j=0;j<stanza->num_max_nemici && !finito;j++)
                   {
                     if(stanza->nemici[j]!=NULL){

                        char nome1[50];
                        char tipo1[50];
                        char nome2[50];
                        char tipo2[50];

                        stanza->nemici[j]->getNome(nome1);
                        turni[i]->persona->getNome(nome2);
                        stanza->nemici[j]->getTipo(tipo1);
                        turni[i]->persona->getTipo(tipo2);              
          
                        if(strcmp(nome1,nome2)==0 &&  strcmp(tipo1,tipo2)==0 &&
                           stanza->nemici[j]->getVita()==turni[i]->persona->getVita())
                          {
                          mvprintw(stanza_coo.y+turni[i]->persona->getCoordinate().y,stanza_coo.x+turni[i]->persona->getCoordinate().x," ");
                           refresh();
                           stanza->nemici[j]=NULL; 
                           turni[i]->persona=NULL; 
                           turni[i]->turno=false; 
                           finito=true;
                          }
                       }//(fine if(stanza->nemici[j]!=NULL))ricerca del nemico da eliminaren e settare tutti i suoi puntatori a NULL
                   }//for di ricerca del nemico da eliminare e settare tutti i suoi puntatori a NULL
                 if(finito) stanza->num_nemici--;
                }//codice per eliminazione del nemico e settare tutti i suoi puntatori a NULL
                draw_details();
               }
        }//persona esistente nei turni
       }//eliminazione di persone con vita <=0

    gamer->write_object(stanza->stanza,stanza->oggetti,stanza->n_oggetti);

  //getch();
    int num1=(rand() % 100)+40;
    int num2=(rand() % 50)+1;
    if(num1==num2 && !gamer->getScudo()){
       gamer->setScudo(true);
       mvprintw(3,stanza_coo.x,"Difesa di rigenerata. Se vieni sparato non subirai danni");
       refresh();
       //mvprintw(5,stanza_coo.x,"[Premi un tasto per continuare]");
       refresh();
       //usleep(1000000);
       refresh();
    }

    if(turni[0]->turno)
      {
       draw_details();
       turni[0]->turno=false;
       token_turno=1;
       bool controllo=false;
       for(int i=token_turno;i<1+gamer->num_max_aiuti+stanza->num_max_nemici && !controllo;i++)
         if(turni[i]!=NULL){
            controllo=true;
            turni[i]->turno=true;
            token_turno=i;
           }
       comando=getch();
       if(comando==27) 
         uscita=true;
       else if(comando==controller->up)
         {
          
          gamer->setCarattere('^');
          gamer->passo(controller,NULL,controller->up,stanza->stanza);
          draw_details();
          last_direction=controller->up;
         }
       else if(comando==controller->down)
         {
          gamer->setCarattere('v');
          gamer->passo(controller,NULL,controller->down,stanza->stanza);
          draw_details();
          last_direction=controller->down;
         }
       else if(comando==controller->sx)
         {
          gamer->setCarattere('<');
          gamer->passo(controller,NULL,controller->sx,stanza->stanza);
          draw_details();
          last_direction=controller->sx;
         }
       else if(comando==controller->dx)
         {
          gamer->setCarattere('>');
          gamer->passo(controller,NULL,controller->dx,stanza->stanza);
          draw_details();
          last_direction=controller->dx;
         }

       else if(comando==controller->porta)
         {
         // Stanza* pre;
          pre_stanza=stanza;
          bool controllo=false;
          if(gamer->getCoordinate().y==12 && gamer->getCoordinate().x==1 /*&& stanza->left==NULL*/){ 
              
              if(/*stanza->getIndexStanza()>=(livello_corrente->getNumStanze()-1) && */stanza->stanza[12][0]=='.' && stanza->left==NULL)
                { 
                 animazioni->nextLevel();
                 controllo=true;
                 int app;
                 if(total_time_machine_part-total_edited_time_machine_part<=0)
                   app=0;
                 else
                   app=(rand()%(total_time_machine_part-total_edited_time_machine_part))+1;
                 Livello* new_livello=new Livello(gamer,livello_corrente,4,stanza->getIndexLivello()+1,app);
                 total_edited_time_machine_part+=app;
                 stanza->left=new_livello->s;
                 new_livello->s->right=stanza;
                 stanza=stanza->left;
                 livello_corrente->next=new_livello;
                 livello_corrente->next->pre=livello_corrente;
                 livello_corrente=livello_corrente->next;
                 pre_stanza->stanza[gamer->getCoordinate().y][gamer->getCoordinate().x]=' ';
                 coordinate new_coo; 
                 new_coo.y=12;
                 new_coo.x=88;
                 gamer->setCoordinate(new_coo);
                }
              else if(stanza->left!=NULL)
               {
                if(stanza->left->getIndexLivello()<stanza->getIndexLivello())
                  { animazioni->preLevel(); livello_corrente=livello_corrente->pre;}
                if(stanza->left->getIndexLivello()>stanza->getIndexLivello())
                  { animazioni->nextLevel(); livello_corrente=livello_corrente->next;}
                controllo=true;
                stanza=stanza->left; 
                pre_stanza->stanza[gamer->getCoordinate().y][gamer->getCoordinate().x]=' ';
                coordinate new_coo; 
                new_coo.y=12;
                new_coo.x=88;
                gamer->setCoordinate(new_coo);
               }
             
             }
            else if(gamer->getCoordinate().y==12 && gamer->getCoordinate().x==88){ 
              if(/*stanza->getIndexStanza()==(livello_corrente->getNumStanze()-1) &&*/ stanza->stanza[13][89]=='.' && stanza->right==NULL)
                { 
                 animazioni->nextLevel();
                 controllo=true;
                 int app;
                 if(total_time_machine_part-total_edited_time_machine_part<=0)
                   app=0;
                 else
                   app=(rand()%(total_time_machine_part-total_edited_time_machine_part))+1;
                 Livello* new_livello=new Livello(gamer,livello_corrente,4,stanza->getIndexLivello()+1,app);
                 total_edited_time_machine_part+=app;
                 stanza->right=new_livello->s;
                 new_livello->s->left=stanza;
                 stanza=stanza->right;
                 livello_corrente->next=new_livello;
                 livello_corrente->next->pre=livello_corrente;
                 livello_corrente=livello_corrente->next;
                 pre_stanza->stanza[gamer->getCoordinate().y][gamer->getCoordinate().x]=' ';
                 coordinate new_coo; 
                 new_coo.y=12;
                 new_coo.x=1;
                 gamer->setCoordinate(new_coo);
                }
              else if(stanza->right!=NULL)
               {
                if(stanza->right->getIndexLivello()<stanza->getIndexLivello())
                  { livello_corrente=livello_corrente->pre; animazioni->preLevel();}
                if(stanza->right->getIndexLivello()>stanza->getIndexLivello())
                  {animazioni->nextLevel(); livello_corrente=livello_corrente->next;}
                controllo=true;
                stanza=stanza->right; 
                pre_stanza->stanza[gamer->getCoordinate().y][gamer->getCoordinate().x]=' ';
                coordinate new_coo; 
                new_coo.y=12;
                new_coo.x=1;
                gamer->setCoordinate(new_coo);
               }
             
            }
          else if(gamer->getCoordinate().y==1 && (gamer->getCoordinate().x==43 || gamer->getCoordinate().x==44)){ 
              if(/*stanza->getIndexStanza()==(livello_corrente->getNumStanze()-1) &&*/ stanza->stanza[0][43]=='.'  && stanza->top==NULL)
                { 
                 animazioni->nextLevel();
                 controllo=true;
                 int app;
                 if(total_time_machine_part-total_edited_time_machine_part<=0)
                   app=0;
                 else
                   app=(rand()%(total_time_machine_part-total_edited_time_machine_part))+1;
                 Livello* new_livello=new Livello(gamer,livello_corrente,4,stanza->getIndexLivello()+1,app);
                 total_edited_time_machine_part+=app;
                 stanza->top=new_livello->s;
                 new_livello->s->bottom=stanza;
                 stanza=stanza->top;
                 livello_corrente->next=new_livello;
                 livello_corrente->next->pre=livello_corrente;
                 livello_corrente=livello_corrente->next;
                 pre_stanza->stanza[gamer->getCoordinate().y][gamer->getCoordinate().x]=' ';
                 coordinate new_coo; 
                 new_coo.y=23;
                 new_coo.x=43;
                 gamer->setCoordinate(new_coo);
                }
              else if(stanza->top!=NULL)
               {
                if(stanza->top->getIndexLivello()<stanza->getIndexLivello())
                  { livello_corrente=livello_corrente->pre; animazioni->preLevel();}
                if(stanza->top->getIndexLivello()>stanza->getIndexLivello())
                  {animazioni->nextLevel(); livello_corrente=livello_corrente->next;}
                controllo=true;
                stanza=stanza->top; 
                pre_stanza->stanza[gamer->getCoordinate().y][gamer->getCoordinate().x]=' ';
                coordinate new_coo; 
                new_coo.y=23;
                new_coo.x=43;
                gamer->setCoordinate(new_coo);
               }
             }
          else if(gamer->getCoordinate().y==23 && (gamer->getCoordinate().x==43 || gamer->getCoordinate().x==44) ){ 

              if(/*stanza->getIndexStanza()==(livello_corrente->getNumStanze()-1) &&*/ stanza->stanza[24][43]=='.' && stanza->bottom==NULL)
                { 
                 animazioni->nextLevel();
                 controllo=true;
                 int app;
                 if(total_time_machine_part-total_edited_time_machine_part<=0)
                   app=0;
                 else
                   app=(rand()%(total_time_machine_part-total_edited_time_machine_part))+1;
                 Livello* new_livello=new Livello(gamer,livello_corrente,4,stanza->getIndexLivello()+1,app);
                 total_edited_time_machine_part+=app;
                 stanza->bottom=new_livello->s;
                 new_livello->s->top=stanza;
                 stanza=stanza->bottom;
                 livello_corrente->next=new_livello;
                 livello_corrente->next->pre=livello_corrente;
                 livello_corrente=livello_corrente->next;
                 pre_stanza->stanza[gamer->getCoordinate().y][gamer->getCoordinate().x]=' ';
                 coordinate new_coo; 
                 new_coo.y=1;
                 new_coo.x=43;
                 gamer->setCoordinate(new_coo);
                }
              else if(stanza->bottom!=NULL)
               {
                mvprintw(0,95,"QUIQUI");
                refresh();
                getch();
                if(stanza->bottom->getIndexLivello()<stanza->getIndexLivello())
                  { livello_corrente=livello_corrente->pre; animazioni->preLevel();}
                if(stanza->bottom->getIndexLivello()>stanza->getIndexLivello())
                  { animazioni->nextLevel(); livello_corrente=livello_corrente->next;}
                controllo=true;
                stanza=stanza->bottom; 
                pre_stanza->stanza[gamer->getCoordinate().y][gamer->getCoordinate().x]=' ';
                coordinate new_coo; 
                new_coo.y=1;
                new_coo.x=43;
                gamer->setCoordinate(new_coo);
               }
             
             }
          else 
             controllo=false;
        
          for(int i=0;i<STANZA_Y;i++)
             for(int j=0;j<STANZA_X;j++)
               stanza_cleaned[i][j]=stanza->stanza[i][j];
          if(controllo){ 
            
            stanza->aggiornaAiutanti(gamer);
            
            for(int i=0;i<gamer->num_max_aiuti;i++){
               if(gamer->aiuti[i]!=NULL){ 
               coordinate coo_aiutante;
               coo_aiutante.x=rand() % STANZA_X;
               coo_aiutante.y=rand() % STANZA_Y;
               int max=2000;
               int inizio=0;
               while(stanza->stanza[coo_aiutante.y][coo_aiutante.x]!=' ' && inizio<max)
                 {
                  coo_aiutante.x=rand() % STANZA_X;
                  coo_aiutante.y=rand() % STANZA_Y;
                  inizio++;
                 }
               if(inizio<max)
                 gamer->aiuti[i]->setCoordinate(coo_aiutante);
              }//fine aggiornamento vecchi aiutanti nella nuova stanza
             }//fine for
            
            this->aggiorna_turni();
            this->aggiorna_time_machine_part_coo();
            turni[0]->turno=true;
            token_turno=0;

           }//cambio stanza valido
          clear();
          draw_details();
         }
       else if(comando==controller->zaino)
         { 
          turni[0]->turno=true; 
          token_turno=0;
          animazioni->mostraZaino(gamer);
         } 
       else if(comando==controller->sparo)
         {
          Persona* persone[1+gamer->num_max_aiuti+stanza->num_max_nemici];
          persone[0]=gamer;
          for(int i=1;i<1+gamer->num_max_aiuti+stanza->num_max_nemici;i++){
              if(turni[i]!=NULL)
               {
                if(turni[i]->persona!=NULL)
                   {
                    char tt[50];
                    turni[i]->persona->getTipo(tt);
                   } 
                persone[i]=turni[i]->persona;
                }
              else 
               persone[i]=NULL; 
             }
           if(gamer->getArma()!=NULL)
            if(gamer->getArma()->getMunizioni()>0)
             {
              bool via=false;
              for(int i=0;i<num_time_machine_part && !via;i++){
                 if(time_machine_part_coo[i]!=NULL){
                    if(controller->up==last_direction && stanza->stanza[gamer->getCoordinate().y-1][gamer->getCoordinate().x]!='#')
                      via=true;
                    else if(controller->down==last_direction && stanza->stanza[gamer->getCoordinate().y+1][gamer->getCoordinate().x]!='#')
                      via=true;
                    else if(controller->sx==last_direction && stanza->stanza[gamer->getCoordinate().y][gamer->getCoordinate().x-1]!='#')
                      via=true;
                    else if(controller->dx==last_direction && stanza->stanza[gamer->getCoordinate().y][gamer->getCoordinate().x+1]!='#')
                      via=true;
                   }
                 }//fine for()
              if(via){
                 gamer->spara(controller,last_direction,stanza->stanza,stanza_coo,persone,1+gamer->num_max_aiuti+stanza->num_max_nemici);
                 gamer->getArma()->setMunizioni(gamer->getArma()->getMunizioni()-gamer->getArma()->getNumProiettili());
                     }
              
             }
           //turni[0]->turno=true;
         }
       else if(comando==controller->dialoga)
         {
          Persona* persone[1+gamer->num_max_aiuti+stanza->num_max_nemici];
          persone[0]=gamer;
          for(int i=1;i<1+gamer->num_max_aiuti+stanza->num_max_nemici;i++){
              if(turni[i]!=NULL)
               {
                if(turni[i]->persona!=NULL)
                   {
                    char tt[50];
                    turni[i]->persona->getTipo(tt);
                   } 
                persone[i]=turni[i]->persona;
                }
              else 
               persone[i]=NULL; 
             }
           coordinate dialogo;
           dialogo.y=2;
           dialogo.x=stanza_coo.x;
           gamer->dialoga(gamer,persone,1+gamer->num_max_aiuti+stanza->num_max_nemici,controller,last_direction,stanza->stanza,dialogo,1/*livello*/);
         }
       else if(comando==controller->raccogli)
         {
          gamer->raccogli(controller,last_direction,stanza->stanza,stanza_coo,stanza->oggetti,stanza->n_oggetti,&total_time_machine_part_catched,num_time_machine_part,time_machine_part_coo);
          draw_details();
          if(total_time_machine_part_catched>=total_time_machine_part){
             clear();
             animazioni->win();
             return;
            }
         }
       else if(comando=='9')
        {
         turni[0]->turno=true; 
         token_turno=0;
         Persona* persone[1+gamer->num_max_aiuti+stanza->num_max_nemici];
          persone[0]=gamer;
          for(int i=1;i<1+gamer->num_max_aiuti+stanza->num_max_nemici;i++){
              if(turni[i]!=NULL)
               {
                if(turni[i]->persona!=NULL)
                   {
                    char tt[50];
                    turni[i]->persona->getTipo(tt);
                   } 
                persone[i]=turni[i]->persona;
                }
              else 
               persone[i]=NULL; 
             }
        //1=LIVELLO
        //7=N_STANZE
          
         animazioni->gameMenu(controller,livello_corrente->s,stanza->getIndexStanza(),stanza->getIndexLivello(),livello_corrente->num_stanze,persone,1+gamer->num_max_aiuti+stanza->num_max_nemici);
        }
       else
        {
         token_turno=0;
         turni[0]->turno=true;
        }
      }//fine turno giocatore
    else{
             this->draw_details();
         if(token_turno>=1+gamer->num_max_aiuti+stanza->num_max_nemici){
              token_turno=0;
              turni[0]->turno=true;
           }
         else if(turni[token_turno]!=NULL){//azione personaggio
          turni[token_turno]->turno=false;
          Persona* persone[1+gamer->num_max_aiuti+stanza->num_max_nemici];
          persone[0]=gamer;
          for(int i=1;i<1+gamer->num_max_aiuti+stanza->num_max_nemici;i++){
              if(turni[i]!=NULL){
                if(turni[i]->persona!=NULL) 
                   persone[i]=turni[i]->persona;
                else  
                   persone[i]=NULL;
               }          
              else 
               persone[i]=NULL; 
             }//fine for
        // if(turni[token_turno]!=NULL)
           if(turni[token_turno]->persona!=NULL)
             turni[token_turno]->persona->AutoAction(controller,stanza->stanza,stanza_coo,persone,1+gamer->num_max_aiuti+stanza->num_max_nemici,stanza->oggetti,stanza->n_oggetti,&total_time_machine_part_catched,num_time_machine_part,time_machine_part_coo);
           } 
        token_turno++;
        draw_details();
        bool c1=false;
        if(turni[token_turno]!=NULL){
          if(turni[token_turno]->persona!=NULL)
            {c1=true; turni[token_turno]->turno=true;}
        }
       if(!c1){//il prossimo non ha turni
           for(int i=(++token_turno);i<1+gamer->num_max_aiuti+stanza->num_max_nemici && !c1;i++)
              if(turni[i]!=NULL){
                if(turni[i]->persona!=NULL)
                   {c1=true; turni[i]->turno=true;}
               }
              }
       if(!c1){//nesun altro ha il permesso
         turni[0]->turno=true;
         token_turno=0; 
        }
     }//fine azioni altri personaggi
   }//fine while
 while(!uscita);
}
