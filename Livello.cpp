#include <ctime>
#include <ncurses.h>
#include "Stanza.cpp"
#include "Livello.hpp"

Livello::Livello(Giocatore* gamer,Livello* pre,int direction_pre_stanza,int livello,int time_machine_part){
srand(time(0));
this->pre=pre;
this->next=NULL;
this->livello=livello;
this->time_machine_part=time_machine_part;

int id_usati[n_stanze];
for(int i=0;i<n_stanze;i++)
  id_usati[i]=-1;

num_stanze=(rand()%n_stanze)+1;
s=new Stanza(gamer,livello,0,id_usati,n_stanze);
//stampa delle scale del livello precedente
 if(direction_pre_stanza==4 && pre!=NULL){
    s->stanza[24][43]='.';
    s->stanza[24][44]='.';
    s->stanza[24][45]='.';
    s->stanza[23][43]='.';
    s->stanza[23][45]='.';
   }
 else if(direction_pre_stanza==2 && pre!=NULL){
    s->stanza[0][43]='.';
    s->stanza[0][44]='.';
    s->stanza[0][45]='.';
    s->stanza[1][43]='.';
    s->stanza[1][45]='.';
   }
 else if(direction_pre_stanza==1 && pre!=NULL){
    s->stanza[11][89]='.';
    s->stanza[12][89]='.';
    s->stanza[13][89]='.';
    s->stanza[11][88]='.';
    s->stanza[13][88]='.';
   }
 else if(direction_pre_stanza==3 && pre!=NULL){
    s->stanza[11][0]='.';
    s->stanza[12][0]='.';
    s->stanza[13][0]='.';
    s->stanza[11][1]='.';
    s->stanza[13][1]='.';
   }

/*
4=SU
2=GIU
1=SX
3=DX
*/
Stanza* new_stanza=s;
if(num_stanze>1){
   

   bool finito=false;
   int direction=-1;
   for(int i=1;i<num_stanze;i++){
     //while per la scelta
       int pre_direction=direction;
     do{
    // finito=true;
     direction=(rand()%4)+1;
     if(i==0 && direction_pre_stanza==4 && direction!=2){
       if(direction==4 && new_stanza->top==NULL)
         { new_stanza->top=new Stanza(NULL,livello,i+1,id_usati,n_stanze); new_stanza->top->bottom=new_stanza; new_stanza=new_stanza->top; finito=true;
           pre_direction=direction_pre_stanza;}
       else if(direction==1 && new_stanza->left==NULL)
         { new_stanza->left=new Stanza(NULL,livello,i+1,id_usati,n_stanze); new_stanza->left->right=new_stanza; new_stanza=new_stanza->left; finito=true;
           pre_direction=direction_pre_stanza;}
       else if(direction==3 && new_stanza->right==NULL)
         { new_stanza->right=new Stanza(NULL,livello,i+1,id_usati,n_stanze); new_stanza->right->left=new_stanza; new_stanza=new_stanza->right; finito=true;
           pre_direction=direction_pre_stanza;}
       }
     else if(i==0 && direction_pre_stanza==2 && direction!=4 && new_stanza->bottom==NULL){
       if(direction==2 && new_stanza->bottom==NULL)
         { new_stanza->bottom=new Stanza(NULL,livello,i+1,id_usati,n_stanze); new_stanza->bottom->top=new_stanza; new_stanza=new_stanza->bottom; finito=true;
           pre_direction=direction_pre_stanza;}
       else if(direction==1 && new_stanza->left==NULL)
         { new_stanza->left=new Stanza(NULL,livello,i+1,id_usati,n_stanze); new_stanza->left->right=new_stanza; new_stanza=new_stanza->left; finito=true;
           pre_direction=direction_pre_stanza;}
       else if(direction==3 && new_stanza->right==NULL)
         { new_stanza->right=new Stanza(NULL,livello,i+1,id_usati,n_stanze); new_stanza->right->left=new_stanza; new_stanza=new_stanza->right; finito=true;
           pre_direction=direction_pre_stanza;}
       }
     else if(i==0 && direction_pre_stanza==1 && direction!=3 && new_stanza->left==NULL){
       if(direction==4 && new_stanza->top==NULL)
         { new_stanza->top=new Stanza(NULL,livello,i+1,id_usati,n_stanze); new_stanza->top->bottom=new_stanza; new_stanza=new_stanza->top; finito=true;
           pre_direction=direction_pre_stanza;}
       else if(direction==1 && new_stanza->left==NULL)
         { new_stanza->left=new Stanza(NULL,livello,i+1,id_usati,n_stanze); new_stanza->left->right=new_stanza; new_stanza=new_stanza->left; finito=true;
           pre_direction=direction_pre_stanza;}
       else if(direction==2 && new_stanza->bottom==NULL)
         { new_stanza->bottom=new Stanza(NULL,livello,i+1,id_usati,n_stanze); new_stanza->bottom->top=new_stanza; new_stanza=new_stanza->bottom; finito=true;
           pre_direction=direction_pre_stanza;}
      }
     else if(i==0 && direction_pre_stanza==3 && direction!=1 && new_stanza->top==NULL){
       if(direction==4 && new_stanza->top==NULL)
         { new_stanza->top=new Stanza(NULL,livello,i+1,id_usati,n_stanze); new_stanza->top->bottom=new_stanza; new_stanza=new_stanza->top; finito=true;
           pre_direction=direction_pre_stanza;}
       else if(direction==2 && new_stanza->bottom==NULL)
         { new_stanza->bottom=new Stanza(NULL,livello,i+1,id_usati,n_stanze); new_stanza->bottom->top=new_stanza; new_stanza=new_stanza->bottom; finito=true;
           pre_direction=direction_pre_stanza;}
       else if(direction==3 && new_stanza->right==NULL)
         { new_stanza->right=new Stanza(NULL,livello,i+1,id_usati,n_stanze); new_stanza->right->left=new_stanza; new_stanza=new_stanza->right; finito=true;
           pre_direction=direction_pre_stanza;}
      }
     else 
      {//SEMPLICEMENTE CONTROLLARE SE I PUNTATORI NON GIA STATI DEFINITI
       /*clear();
       mvprintw(0,0,"direction:%d",direction);
       refresh();
       getch();*/
       bool cc=false;
       if(direction==4 && new_stanza->top==NULL && pre_direction!=4)
         {cc=true; new_stanza->top=new Stanza(NULL,livello,i+1,id_usati,n_stanze); new_stanza->top->bottom=new_stanza; new_stanza=new_stanza->top; finito=true;
          pre_direction=direction_pre_stanza;}
       else if(direction==2 && new_stanza->bottom==NULL && pre_direction!=2)
         {cc=true;new_stanza->bottom=new Stanza(NULL,livello,i+1,id_usati,n_stanze); new_stanza->bottom->top=new_stanza; new_stanza=new_stanza->bottom; finito=true; pre_direction=direction_pre_stanza;}
       else if(direction==1 && new_stanza->left==NULL && pre_direction!=1)
         {cc=true;new_stanza->left=new Stanza(NULL,livello,i+1,id_usati,n_stanze); new_stanza->left->right=new_stanza; new_stanza=new_stanza->left; finito=true;
          pre_direction=direction_pre_stanza;}
       else if(direction==3 && new_stanza->right==NULL && pre_direction!=3)
         {cc=true;new_stanza->right=new Stanza(NULL,livello,i+1,id_usati,n_stanze); new_stanza->right->left=new_stanza; new_stanza=new_stanza->right; finito=true; pre_direction=direction_pre_stanza;}
             
       if(!cc)
         i--;
      }//fine generazione stanze nel caso di stanza non numero 1
    }while(!finito);//fine while per la scelta
  }
 }
//creazione di scala per il successivo livello
 if(new_stanza->top==NULL){
    new_stanza->stanza[0][43]='.';
    new_stanza->stanza[0][44]='.';
    new_stanza->stanza[0][45]='.';
    new_stanza->stanza[1][43]='.';
    new_stanza->stanza[1][45]='.';
   }
 else if(new_stanza->bottom==NULL){
    new_stanza->stanza[24][43]='.';
    new_stanza->stanza[24][44]='.';
    new_stanza->stanza[24][45]='.';
    new_stanza->stanza[23][43]='.';
    new_stanza->stanza[23][45]='.';
   }
 else if(new_stanza->left==NULL){
    new_stanza->stanza[11][0]='.';
    new_stanza->stanza[12][0]='.';
    new_stanza->stanza[13][0]='.';
    new_stanza->stanza[11][1]='.';
    new_stanza->stanza[13][1]='.';
   }
 else if(new_stanza->right=NULL){
    new_stanza->stanza[11][89]='.';
    new_stanza->stanza[12][89]='.';
    new_stanza->stanza[13][89]='.';
    new_stanza->stanza[11][88]='.';
    new_stanza->stanza[13][88]='.';
   }
//stampa degli oggetti speciali***********************************************
draw_time_machine(time_machine_part,s);
}


void Livello::draw_time_machine(int rest_time_machine_part,Stanza* box){

if(rest_time_machine_part<=0 || box==NULL)
  return;
int app;
if(rest_time_machine_part>10)
  app=(rand()%10)+1;
else
  app=(rand()%rest_time_machine_part)+1;
/*
clear();
mvprintw(0,0,"stanza %d # da stampare:%d",box->getIndexStanza(),app);
refresh();
getch();*/
//rest_time_machine_part-=app;
 int i=0;
 do{
    
    coordinate print;
    print.x=rand()%STANZA_X;
    print.y=rand()%STANZA_Y;
    
    if(box->stanza[print.y][print.x]==' ')  
      {
       i++;
       box->stanza[print.y][print.x]='#';
      } 
   }while(i<app);

 int next_stanza;
 bool finito;
 do{
    next_stanza=(rand()%4)+1;
    if(
       (next_stanza==4 && box->top!=NULL) ||
       (next_stanza==2 && box->bottom!=NULL) ||
       (next_stanza==1 && box->left!=NULL) ||
       (next_stanza==3 && box->right!=NULL) ||
       (box->top==NULL&& box->bottom==NULL && box->left==NULL && box->right==NULL)
      )
      finito=true;
   }while(!finito);

 if(next_stanza==4 && box->top!=NULL) 
   draw_time_machine(rest_time_machine_part-app,box->top);
 else  if(next_stanza==2 && box->bottom!=NULL)
   draw_time_machine(rest_time_machine_part-app,box->bottom);
 else  if(next_stanza==1 && box->left!=NULL)
   draw_time_machine(rest_time_machine_part-app,box->left);
 else if(next_stanza==3 && box->right!=NULL)
   draw_time_machine(rest_time_machine_part-app,box->right);
  else{
    if(rest_time_machine_part-app>0)
       {

        if(box->top!=NULL) 
          draw_time_machine(rest_time_machine_part-app,box->top);
        else  if(box->bottom!=NULL)
          draw_time_machine(rest_time_machine_part-app,box->bottom);
        else  if(box->left!=NULL)
          draw_time_machine(rest_time_machine_part-app,box->left);
        else if(box->right!=NULL)
          draw_time_machine(rest_time_machine_part-app,box->right);
        else{
             i=0;
             do{
    
                coordinate print;
                print.x=rand()%STANZA_X;
                print.y=rand()%STANZA_Y; 
                if(box->stanza[print.y][print.x]==' ')  
                 {
                  i++;
                  box->stanza[print.y][print.x]='#';
                 } 
               }while(i<rest_time_machine_part-app);
            }
       }
/*clear();

if(box->top==NULL)
  mvprintw(1,0,"TOP NULL");
if(box->bottom==NULL)
  mvprintw(2,0,"BOTTOM NULL");
if(box->left==NULL)
  mvprintw(3,0,"LEFT NULL");
if(box->right==NULL)
  mvprintw(4,0,"RIGHT NULL");

mvprintw(0,0,"stanza %d TUTTI NULL", box->getIndexStanza());
refresh();
getch();*/
    }
}

int Livello::getNLivello(){
 return livello;
}
void Livello::setLivello(int livello){
 this->livello=livello;
}

int Livello::getNumStanze(){return n_stanze;}
