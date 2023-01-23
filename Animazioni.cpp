#include <ncurses.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <string.h>
#include <cstdlib>
#include "Livello.cpp"
#include "Animazioni.hpp"

Arma_icon Animazioni::ListaArma(p_oggetto zaino[]){
Arma_icon r,app; 
r=NULL;
app=NULL;

for(int i=0;i<50;i++)
   {
    if(zaino[i]!=NULL)
      {    
           if(zaino[i]->arma!=NULL)
            {
             if(r==NULL)
               {
                r=new Arma_i;
                r->pre=NULL;
                r->next=NULL;
                app=r;
               }
             else
              {
               app->next=new Arma_i;
               app->next->pre=app;
               app=app->next;
               app->next=NULL;
              }
            app->arma=(zaino[i])->arma;

            char path[14]="armi/weapon_";
            char w[26][79];
            int j=0; 
            ifstream file;
            path[12]=app->arma->getIndex()+48;
            path[13]='\0'; 

            file.open(path,ifstream::in);
            while(file.good() && j<25)
               file.getline(w[j++],79);
            file.close();
 
            for(int z=0;z<25;z++)
               strcpy(app->draw[z],w[z]);
           }
      }//ramo cella non vuota
   }

 if(app==NULL)
   return NULL;

 app->next=r;
 r->pre=app;
 return r;
}

KIT_icon Animazioni::ListaKIT(p_oggetto zaino[]){
KIT_icon r,app;
r=NULL;
app=NULL;

for(int i=0;i<50;i++)
   {
    if(zaino[i]!=NULL)
      {    
           if(zaino[i]->kit!=NULL)
            {
              if(zaino[i]->kit->quantita>0)
                {
                 if(r==NULL)
                   {
                    r=new KIT_i;
                    r->pre=NULL;
                    r->next=NULL;
                    app=r;
                   }
                 else
                   {
                    app->next=new KIT_i;
                    app->next->pre=app;
                    app=app->next;
                    app->next=NULL;
                   }
                 app->kit=(zaino[i])->kit;
                }
               else
                {
                 delete zaino[i]->kit;
                 zaino[i]->kit=NULL;
                }
            }
      }//ramo cella non vuota
   }

 if(app==NULL)
   return NULL;

 app->next=r;
 r->pre=app;
 return r;
}

void Animazioni::stampaArma(int x,int y,char weapon_matrix[][79]){
for(int i=0;i<25;i++)
        mvprintw(y+i,x,weapon_matrix[i]);
 refresh();
}

void Animazioni::stampaKIT(int x,int y,char draw[][50]){
for(int i=0;i<25;i++)
   mvprintw(y+i,x,draw[i]);
refresh();
}

Arma_icon Animazioni::ScorriArma(Arma_icon node_current, int x_max,int x, int y, int direction,long duration){

  if(direction!=4 && direction!=6) 
   return NULL;
 if(direction==4)
   {
     int x_app=x;
     do
       {
        for(int i=0;i<25;i++)
            mvprintw(y+i,x+77," ");
        stampaArma(--x,y,node_current->draw);
        refresh();
        usleep(duration);	
       }
     while(x>0);

     for(int z=1;z<79;z++)
        {
         for(int i=z;i<79;i++)
            {
             for(int j=0;j<25;j++)
                {
                 mvprintw(y+j,i-z,"%c",node_current->draw[j][i]); 
                 mvprintw(y+j,i-z+1," "); 
                }
            } 

	refresh();
        usleep(duration);
        }

     for(int i=0;i<25;i++)
        mvprintw(y+i,0," "); 

     int offset_x=0;
     int offset_y=0;
     for(offset_x=0;offset_x<79;offset_x++)
       {
         for(offset_y=0;offset_y<25;offset_y++)
            mvprintw(y+offset_y,x_max-offset_x,"%c",node_current->next->draw[offset_y][78-offset_x]); 
         refresh();
         usleep(duration);
       }
     x=x_max-offset_x+2;
     y=y+offset_y-25;

     do
       {
        for(int i=0;i<25;i++)
            mvprintw(y+i,x+77," ");
        stampaArma(--x,y,node_current->next->draw);
        refresh();
        usleep(duration);	
       }
     while(x>x_app);
     return node_current->next;
    }
 else
    {
     int x_app=x;
     do
       {
        for(int i=0;i<25;i++)
            mvprintw(y+i,x," ");
        stampaArma(++x,y,node_current->draw);
        refresh();
        usleep(duration);	
       }
     while(x<x_max-77);

     for(int z=1;z<79;z++)
        {
         for(int i=z;i<79;i++)
            {
             for(int j=0;j<25;j++)
                {
                 mvprintw(y+j,x+z,"%c",node_current->draw[j][78-i]); 
                 mvprintw(y+j,x+z-1," "); 
                }
            } 

	refresh();
        usleep(duration);
        }

     for(int i=0;i<25;i++)
        mvprintw(y+i,0," ");

     int offset_x=0;
     int offset_y=0;
     for(offset_x=0;offset_x<79;offset_x++)
       {
         for(offset_y=0;offset_y<25;offset_y++)
            mvprintw(y+offset_y,offset_x,"%c",node_current->pre->draw[offset_y][offset_x]); 
         refresh();
         usleep(duration);
       }
     offset_x=0;

     do
       {
        for(int i=0;i<25;i++)
            mvprintw(y+i,offset_x," ");
        stampaArma(++offset_x,y,node_current->pre->draw);
        refresh();
        usleep(duration);	
       }
     while(offset_x<x_app);

     return node_current->pre;
    }
 return NULL;
}

KIT_icon Animazioni::ScorriKIT(KIT_icon node_current,char draw[][50], int x_max,int x, int y, int direction,long duration){

  if(direction!=4 && direction!=6) 
   return NULL;
 if(direction==4)
   {
     int x_app=x;
     do
       {
        for(int i=0;i<25;i++)
            mvprintw(y+i,x+48," ");
        stampaKIT(--x,y,draw);
        refresh();
        usleep(duration);	
       }
     while(x>0);

     for(int z=1;z<50;z++)
        {
         for(int i=z;i<50;i++)
            {
             for(int j=0;j<25;j++)
                {
                 mvprintw(y+j,i-z,"%c",draw[j][i]); 
                 mvprintw(y+j,i-z+1," "); 
                }
            } 

	refresh();
        usleep(duration);
        }

     for(int i=0;i<25;i++)
        mvprintw(y+i,0," "); 

     int offset_x=0;
     int offset_y=0;
     for(offset_x=0;offset_x<50;offset_x++)
       {
         for(offset_y=0;offset_y<25;offset_y++)
            mvprintw(y+offset_y,x_max-offset_x,"%c",draw[offset_y][48-offset_x]); 
         refresh();
         usleep(duration);
       }
     x=x_max-offset_x+2;
     y=y+offset_y-25;

     do
       {
        for(int i=0;i<25;i++)
            mvprintw(y+i,x+48," ");
        stampaKIT(--x,y,draw);
        refresh();
        usleep(duration);	
       }
     while(x>x_app);
     return node_current->next;
    }
 else
    {
     int x_app=x;
     do
       {
        for(int i=0;i<25;i++)
            mvprintw(y+i,x," ");
        stampaKIT(++x,y,draw);
        refresh();
        usleep(duration);	
       }
     while(x<x_max-50);

     for(int z=1;z<50;z++)
        {
         for(int i=z;i<50;i++)
            {
             for(int j=0;j<25;j++)
                {
                 mvprintw(y+j,x+z,"%c",draw[j][50-i]); 
                 mvprintw(y+j,x+z-1," "); 
                }
            } 

	refresh();
        usleep(duration);
        }

     for(int i=0;i<25;i++)
        mvprintw(y+i,0," ");

     int offset_x=0;
     int offset_y=0;
     for(offset_x=0;offset_x<50;offset_x++)
       {
         for(offset_y=0;offset_y<25;offset_y++)
            mvprintw(y+offset_y,offset_x,"%c",draw[offset_y][offset_x]); 
         refresh();
         usleep(duration);
       }
     offset_x=0;

     do
       {
        for(int i=0;i<25;i++)
            mvprintw(y+i,offset_x," ");
        stampaKIT(++offset_x,y,draw);
        refresh();
        usleep(duration);	
       }
     while(offset_x<x_app);

     return node_current->pre;
    }
 return NULL;
}

coordinate Animazioni::selectControl(Controller* controller){
int x,y;
getmaxyx(stdscr,y,x);
//clear();
int x_cursor=(x/2)-15;
int y_cursor=(y/2)-7;
char c;

mvprintw((y/2)-11,(x/2)-51,"Selezionare il comando da modificare con w ed s e premere invio per modificarlo digitando quello nuovo");
mvprintw((y/2)-9,(x/2)-13,"Comandi movimento giocatore");

if(controller->up!=' ' && controller->up!=10)
  mvprintw((y/2)-7,(x/2)-15,"* up   ->  %c     ",controller->up);
else if(controller->up==' ')
  mvprintw((y/2)-7,(x/2)-15,"* up   ->  space");
else
  mvprintw((y/2)-7,(x/2)-15,"* up   ->  invio");

if(controller->down!=' ' && controller->down!=10)
  mvprintw((y/2)-5,(x/2)-13,"down   ->  %c     ",controller->down);
else if(controller->down==' ')
  mvprintw((y/2)-5,(x/2)-13,"down   ->  space");
else
  mvprintw((y/2)-5,(x/2)-13,"down   ->  invio");


if(controller->sx!=' ' && controller->sx!=10)
  mvprintw((y/2)-3,(x/2)-13,"sx   ->  %c     ",controller->sx);
else if(controller->sx==' ')
  mvprintw((y/2)-3,(x/2)-13,"sx   ->  space");
else
  mvprintw((y/2)-3,(x/2)-13,"sx   ->  invio");

if(controller->dx!=' ' && controller->dx!=10)
  mvprintw((y/2)-1,(x/2)-13,"dx   ->  %c     ",controller->dx);
else if(controller->dx==' ')
  mvprintw((y/2)-1,(x/2)-13,"dx   ->  space");
else
  mvprintw((y/2)-1,(x/2)-13,"dx   ->  invio");

mvprintw((y/2)+1,(x/2)-13,"Comandi per l'interazione");

if(controller->porta!=' ' && controller->porta!=10)
  mvprintw((y/2)+3,(x/2)-13,"apri/chiudi porta     ->  %c     ",controller->porta);
else if(controller->porta==' ')
  mvprintw((y/2)+3,(x/2)-13,"apri/chiudi porta     ->  space");
else
  mvprintw((y/2)+3,(x/2)-13,"apri/chiudi porta     ->  invio");

if(controller->zaino!=' ' && controller->zaino!=10)
  mvprintw((y/2)+5,(x/2)-13,"apri zaino            ->  %c     ",controller->zaino);
else if(controller->zaino==' ')
  mvprintw((y/2)+5,(x/2)-13,"apri zaino            ->  space");
else
  mvprintw((y/2)+5,(x/2)-13,"apri zaino            ->  invio");

if(controller->sparo!=' ' && controller->sparo!=10)
  mvprintw((y/2)+7,(x/2)-13,"spara/conferma azione ->  %c     ",controller->sparo);
else if(controller->sparo==' ')
  mvprintw((y/2)+7,(x/2)-13,"spara/conferma azione ->  space");
else
  mvprintw((y/2)+7,(x/2)-13,"spara/conferma azione ->  invio");


if(controller->raccogli!=' ' && controller->raccogli!=10)
  mvprintw((y/2)+9,(x/2)-13,"raccogli              ->  %c     ",controller->raccogli);
else if(controller->raccogli==' ')
  mvprintw((y/2)+9,(x/2)-13,"raccogli              ->  space");
else
  mvprintw((y/2)+9,(x/2)-13,"raccogli              ->  invio");

mvprintw((y/2)+11,(x/2)-13,"Conferma");
refresh();


while((c=getch())!=10){
   if(y_cursor==(y/2)-7)
     {
      if(c=='W' || c=='w')
        {
         mvprintw(y_cursor,x_cursor," ");
         y_cursor=(y/2)+11;
         mvprintw(y_cursor,x_cursor,"* ");
        }
      else if(c=='S' || c=='s')
        {
         mvprintw(y_cursor,x_cursor," ");
         y_cursor=(y/2)-5;
         mvprintw(y_cursor,x_cursor,"* ");         
        }
     }
   else if(y_cursor==(y/2)-5)
     {
      if(c=='W' || c=='w')
        {
         mvprintw(y_cursor,x_cursor," ");
         y_cursor=(y/2)-7;
         mvprintw(y_cursor,x_cursor,"* ");
        }
      else if(c=='S' || c=='s')
        {
         mvprintw(y_cursor,x_cursor," ");
         y_cursor=(y/2)-3;
         mvprintw(y_cursor,x_cursor,"* ");         
        }
     }
   else if(y_cursor==(y/2)-3)
     {
      if(c=='W' || c=='w')
        {
         mvprintw(y_cursor,x_cursor," ");
         y_cursor=(y/2)-5;
         mvprintw(y_cursor,x_cursor,"* ");
        }
      else if(c=='S' || c=='s')
        {
         mvprintw(y_cursor,x_cursor," ");
         y_cursor=(y/2)-1;
         mvprintw(y_cursor,x_cursor,"* ");         
        }
     }
   else if(y_cursor==(y/2)-1)
     {
      if(c=='W' || c=='w')
        {
         mvprintw(y_cursor,x_cursor," ");
         y_cursor=(y/2)-3;
         mvprintw(y_cursor,x_cursor,"* ");
        }
      else if(c=='S' || c=='s')
        {
         mvprintw(y_cursor,x_cursor," ");
         y_cursor=(y/2)+3;
         mvprintw(y_cursor,x_cursor,"* ");         
        }
     }
   else if(y_cursor==(y/2)+3)
     {
      if(c=='W' || c=='w')
        {
         mvprintw(y_cursor,x_cursor," ");
         y_cursor=(y/2)-1;
         mvprintw(y_cursor,x_cursor,"* ");
        }
      else if(c=='S' || c=='s')
        {
         mvprintw(y_cursor,x_cursor," ");
         y_cursor=(y/2)+5;
         mvprintw(y_cursor,x_cursor,"* ");         
        }
     }
   else if(y_cursor==(y/2)+5)
     {
      if(c=='W' || c=='w')
        {
         mvprintw(y_cursor,x_cursor," ");
         y_cursor=(y/2)+3;
         mvprintw(y_cursor,x_cursor,"* ");
        }
      else if(c=='S' || c=='s')
        {
         mvprintw(y_cursor,x_cursor," ");
         y_cursor=(y/2)+7;
         mvprintw(y_cursor,x_cursor,"* ");         
        }
     }
   else if(y_cursor==(y/2)+7)
     {
      if(c=='W' || c=='w')
        {
         mvprintw(y_cursor,x_cursor," ");
         y_cursor=(y/2)+5;
         mvprintw(y_cursor,x_cursor,"* ");
        }
      else if(c=='S' || c=='s')
        {
         mvprintw(y_cursor,x_cursor," ");
         y_cursor=(y/2)+9;
         mvprintw(y_cursor,x_cursor,"* ");         
        }
     }
   else if(y_cursor==(y/2)+9)
     {
      if(c=='W' || c=='w')
        {
         mvprintw(y_cursor,x_cursor," ");
         y_cursor=(y/2)+7;
         mvprintw(y_cursor,x_cursor,"* ");
        }
      else if(c=='S' || c=='s')
        {
         mvprintw(y_cursor,x_cursor," ");
         y_cursor=(y/2)+11;
         mvprintw(y_cursor,x_cursor,"* ");         
        }
     }
   else if(y_cursor==(y/2)+11)
     {
      if(c=='W' || c=='w')
        {
         mvprintw(y_cursor,x_cursor," ");
         y_cursor=(y/2)+9;
         mvprintw(y_cursor,x_cursor,"* ");
        }
      else if(c=='S' || c=='s')
        {
         mvprintw(y_cursor,x_cursor," ");
         y_cursor=(y/2)-7;
         mvprintw(y_cursor,x_cursor,"* ");         
        }
     }
   refresh();
  }

coordinate coo;

//clear();
mvprintw(y_cursor,x_cursor," ");
refresh();
coo.x=x_cursor;
coo.y=y_cursor;
return coo;
}

bool Animazioni::dualController(Controller* controller,char new_controller){
bool controllo=false;

 if(new_controller==controller->up)
   controllo=true;
 else if(new_controller==controller->down)
   controllo=true;
 else if(new_controller==controller->sx)
   controllo=true;
 else if(new_controller==controller->dx)
   controllo=true;
 else if(new_controller==controller->porta)
   controllo=true;
 else if(new_controller==controller->zaino)
   controllo=true;
 else if(new_controller==controller->sparo)
   controllo=true;
 else if(new_controller==controller->dialoga)
   controllo=true;
 else if(new_controller==controller->raccogli)
   controllo=true;

 return controllo;
}


void Animazioni::changeControl(Controller* controller){
int x,y;
char new_controller;
clear();
getmaxyx(stdscr,y,x);
coordinate coo;
do{
   // clear();
    coo=this->selectControl(controller);
    if(coo.y!=(y/2)+11)
      {

       if(coo.y-(y/2)<0)
          coo.x=(x/2)-4;
       else
          coo.x+=28;

       move(coo.y,coo.x);
       curs_set(1);
       new_controller=getch();
       curs_set(0);
       if(!this->dualController(controller,new_controller))
         {
          if(coo.y==(y/2)-7 && new_controller!='9')
            controller->up=new_controller;
          else if(coo.y==(y/2)-5 && new_controller!='9')
            controller->down=new_controller;
          else if(coo.y==(y/2)-3 && new_controller!='9')
            controller->sx=new_controller;
          else if(coo.y==(y/2)-1 && new_controller!='9')
            controller->dx=new_controller;
          else if(coo.y==(y/2)+3 && new_controller!='9')
            controller->porta=new_controller;
          else if(coo.y==(y/2)+5 && new_controller!='9')
            controller->zaino=new_controller;
          else if(coo.y==(y/2)+7 && new_controller!='9')
            controller->sparo=new_controller;
          else if(coo.y==(y/2)+9 && new_controller!='9')
            controller->scudo=new_controller;
          else if(coo.y==(y/2)+11 && new_controller!='9')
            controller->dialoga=new_controller;
          else if(coo.y==(y/2)+13 && new_controller!='9')
            controller->raccogli=new_controller;
         }//controllo se il nuovo tasto esiste già
       else
         {
          mvprintw((y/2)+17,(x/2)-25,"Questo tasto e' gia in uso. Attendere e riscrivere");
          refresh();
          usleep(1500000);
          mvprintw((y/2)+17,(x/2)-25,"                                                  ");
          refresh();
         }
      }//controllo esistenza modifica di tasti
  }
while(coo.y!=(y/2)+11);
clear();
}

void Animazioni::nextLevel(){
//creazione scala******************************************
int x,y;
getmaxyx(stdscr,y,x);
int h_scala=(y/6)-1;//altezza della scala
int b_scala=x/5;//base della scala
int y_i=y-1;
int x_i=0;

clear();

for(int i=0;i<6;i++)
   {
     for(int j=0;j<b_scala;j++)
        mvprintw(y_i,x_i++,"*");
     refresh();
      
     for(int j=0;j<h_scala-1;j++)
        mvprintw(y_i--,x_i,"*");
     refresh();
   }//fine for primario

 for(int j=0;j<b_scala;j++)
        mvprintw(y_i,x_i++,"*");
     refresh();
//**********************************************************
//********************animazione della salita***************
y_i=y;
x_i=0;
for(int j=0;j<6;j++)
  {
    mvprintw(y_i-21,x_i+8,"   ******");
    mvprintw(y_i-20,x_i+8,"  *     O *");
    mvprintw(y_i-19,x_i+8," *       |*");
    mvprintw(y_i-18,x_i+8," *      _ *");
    mvprintw(y_i-17,x_i+8,"  *     **");
    mvprintw(y_i-16,x_i+8,"  *    *   ");
mvprintw(y_i-15,x_i+4,"********    ********");
mvprintw(y_i-14,x_i+4,"*                  *");
mvprintw(y_i-13,x_i+4,"*  **          **  *");
mvprintw(y_i-12,x_i+4,"*  **          **  *");
mvprintw(y_i-11,x_i+4,"*  **          **  *"); 
mvprintw(y_i-10,x_i+4,"*  **          **  *");
mvprintw(y_i-9,x_i+4, "*--**************--*");
mvprintw(y_i-8,x_i+4, "*||**  *    *  **||*");
    mvprintw(y_i-7,x_i+8, "*  *    *  *");
    mvprintw(y_i-6,x_i+8, "*  *    *  *");
    mvprintw(y_i-5,x_i+8, "*  *    *  *");
    mvprintw(y_i-4,x_i+8, "******* *******");
    mvprintw(y_i-3,x_i+8, "*     * *     *");
    mvprintw(y_i-2,x_i+8, "******* *******");
    
    usleep(750000);
    refresh();
    for(int i=2;i<=21;i++)
       for(int z=0;z<20;z++)
          mvprintw(y_i-i,x_i+4+z," ");
       
    y_i=(y_i-h_scala)+1;
    x_i+=b_scala;
  }
 //clear();
}

void Animazioni::preLevel(){
//creazione scala******************************************
int x,y;
getmaxyx(stdscr,y,x);
int h_scala=(y/6)-1;//altezza della scala
int b_scala=x/5;//base della scala
int y_i=y-1;
int x_i=0;

clear();

for(int i=0;i<5 && x_i<x && y_i>=0;i++)
   {
     for(int j=0;j<b_scala;j++)
        mvprintw(y_i,x_i++,"*");
     refresh();
      
     for(int j=0;j<h_scala-1 && x_i<x;j++)
        mvprintw(y_i--,x_i,"*");
     refresh();
   }//fine for primario

 for(int j=0;j<b_scala && x_i<x;j++)
        mvprintw(y_i,x_i++,"*");
     refresh();
//**********************************************************
//********************animazione della salita***************
x_i=x-1;
//y_i--;
for(int j=0;j<5;j++)
  {
    mvprintw(y_i-20,x_i-20,"       ******");
    mvprintw(y_i-19,x_i-20,"      *O     *");
    mvprintw(y_i-18,x_i-20,"     *|       *");
    mvprintw(y_i-17,x_i-20,"     *_       *");
    mvprintw(y_i-16,x_i-20,"      **     *");
    mvprintw(y_i-15,x_i-20,"       *    *   ");
mvprintw(y_i-14,x_i-20,"********    ********");
mvprintw(y_i-13,x_i-20,"*                  *");
mvprintw(y_i-12,x_i-20,"*  **          **  *");
mvprintw(y_i-11,x_i-20,"*  **          **  *");
mvprintw(y_i-10,x_i-20,"*  **          **  *"); 
mvprintw(y_i-9,x_i-20,"*  **          **  *");
mvprintw(y_i-8,x_i-20, "*--**************--*");
mvprintw(y_i-7,x_i-20, "*||**  *    *  **||*");
    mvprintw(y_i-6,x_i-20, "    *  *    *  *");
    mvprintw(y_i-5,x_i-20, "    *  *    *  *");
    mvprintw(y_i-4,x_i-20, "    *  *    *  *");
    mvprintw(y_i-3,x_i-20, "******** *******");
    mvprintw(y_i-2,x_i-20, "*      * *     *");
    mvprintw(y_i-1,x_i-20, "******** *******");
    refresh();
    usleep(750000);
    refresh();
    for(int i=1;i<=20;i++)
       for(int z=0;z<20;z++)
          mvprintw(y_i-i,x_i-20+z," ");
       
    y_i+=h_scala-1;
    x_i-=b_scala;
  }
// clear();
}


/*
return 0=ricomincia partita;
return 1=abbandona partita
*/
int Animazioni::gameover(){
int x,y;
int direzione=1;
int x_i=0;
int y_i=0;
getmaxyx(stdscr,y,x);

refresh();
for(int i=0;i<6;i++)
  {
  // refresh();
      //clear();
   mvprintw ((y/2)-4,5,"* * * * * * * *");
   mvprintw ((y/2)-3,5,"* * * * * * * *");
   mvprintw ((y/2)-2,5,"* *");
   mvprintw ((y/2)-1,5,"* *");
   mvprintw ((y/2),5,  "* *   * * * * *");
   mvprintw ((y/2)+1,5,"* *   * * * * *");
   mvprintw ((y/2)+2,5,"* *         * *");
   mvprintw ((y/2)+3,5,"* * * * * * * *");
   mvprintw ((y/2)+4,5,"* * * * * * * *");

   mvprintw ((y/2)-4,22,"* * * * * * * *");
   mvprintw ((y/2)-3,22,"* * * * * * * *");
   mvprintw ((y/2)-2,22,"* *         * *");
   mvprintw ((y/2)-1,22,"* *         * *");
   mvprintw ((y/2),22,  "* * * * * * * *");
   mvprintw ((y/2)+1,22,"* * * * * * * *");
   mvprintw ((y/2)+2,22,"* *         * *");
   mvprintw ((y/2)+3,22,"* *         * *");
   mvprintw ((y/2)+4,22,"* *         * *");
   //refresh();
   mvprintw ((y/2)-4,40,"* * * * * * * *");
   mvprintw ((y/2)-3,40,"* * * * * * * *");
   mvprintw ((y/2)-2,40,"* *   * *   * *");
   mvprintw ((y/2)-1,40,"* *   * *   * *");
   mvprintw ((y/2),40,  "* *   * *   * *");
   mvprintw ((y/2)+1,40,"* *   * *   * *");
   mvprintw ((y/2)+2,40,"* *   * *   * *");
   mvprintw ((y/2)+3,40,"* *   * *   * *");
   mvprintw ((y/2)+4,40,"* *   * *   * *");
   //refresh();
   mvprintw ((y/2)-4,58,"* * * * * * * *");
   mvprintw ((y/2)-3,58,"* * * * * * * *");
   mvprintw ((y/2)-2,58,"* *");
   mvprintw ((y/2)-1,58,"* *");
   mvprintw ((y/2),58,  "* * * * * * * *");
   mvprintw ((y/2)+1,58,"* * * * * * * *");
   mvprintw ((y/2)+2,58,"* *");
   mvprintw ((y/2)+3,58,"* * * * * * * *");
   mvprintw ((y/2)+4,58,"* * * * * * * *");
   //refresh();
   mvprintw ((y/2)-4,78,"* * * * * * * *");
   mvprintw ((y/2)-3,78,"* * * * * * * *");
   mvprintw ((y/2)-2,78,"* *         * *");
   mvprintw ((y/2)-1,78,"* *         * *");
   mvprintw ((y/2),78,  "* *         * *");
   mvprintw ((y/2)+1,78,"* *         * *");
   mvprintw ((y/2)+2,78,"* *         * *");
   mvprintw ((y/2)+3,78,"* * * * * * * *");
   mvprintw ((y/2)+4,78,"* * * * * * * *");
   //refresh();
   mvprintw ((y/2)-4,95,"* *         * *");
   mvprintw ((y/2)-3,95,"* *         * *");
   mvprintw ((y/2)-2,95,"* *         * *");
   mvprintw ((y/2)-1,95,"* *         * *");
   mvprintw ((y/2),95,  "* *         * *");
   mvprintw ((y/2)+1,95," * *       * * ");
   mvprintw ((y/2)+2,95,"  * * *   * *  ");
   mvprintw ((y/2)+3,95,"    * * * *    ");
   mvprintw ((y/2)+4,95,"      * *      ");
   //refresh();
   mvprintw ((y/2)-4,112,"* * * * * * * *");
   mvprintw ((y/2)-3,112,"* * * * * * * *");
   mvprintw ((y/2)-2,112,"* *");
   mvprintw ((y/2)-1,112,"* *");
   mvprintw ((y/2),112,  "* * * * * * * *");
   mvprintw ((y/2)+1,112,"* * * * * * * *");
   mvprintw ((y/2)+2,112,"* *");
   mvprintw ((y/2)+3,112,"* * * * * * * *");
   mvprintw ((y/2)+4,112,"* * * * * * * *");
   refresh();
   mvprintw ((y/2)-4,129,"* * * * * * * *");
   mvprintw ((y/2)-3,129,"* * * * * * * *");
   mvprintw ((y/2)-2,129,"* *         * *");
   mvprintw ((y/2)-1,129,"* * * * * * * *");
   mvprintw ((y/2),129,  "* * * * * * * *");
   mvprintw ((y/2)+1,129,"* * * *");
   mvprintw ((y/2)+2,129,"* *   * * ");
   mvprintw ((y/2)+3,129,"* *     * *");
   mvprintw ((y/2)+4,129,"* *       * *");
   refresh();
   usleep(500000);
   refresh();
   if(i==5) break; 
   for(int i=(y/2)-4;i<=(y/2)+4;i++)
      for(int j=5;j<=143;j++)
       mvprintw(i,j," ");
   refresh();
   usleep(500000);
   //refresh();
  }

clear();
/*  for(int i=0;i<7;i++)
     for(int j=0;j<18;j++)
        mvprintw((y/2)+6+i,(x/2)-13+j," ");*/
  refresh(); 

  int scelta=0;
  /*char c;
  mvprintw((y/2)+7,(x/2)-13,"Cosa vuoi fare?");
  mvprintw((y/2)+9,(x/2)-13,"*Ricomincia");
  mvprintw((y/2)+11,(x/2)-13," Abbandona");

  
    while((c=getch())!=10){
     if(scelta==0 && (c=='w' || c=='W') || (c=='s' || c=='S'))
       {
        scelta=1;
        mvprintw((y/2)+9,(x/2)-13," ");
        mvprintw((y/2)+11,(x/2)-13,"*");
       }
     else if(scelta==1 && (c=='w' || c=='W') || (c=='s' || c=='S'))
       {
        scelta=0;
        mvprintw((y/2)+9,(x/2)-13,"*");
        mvprintw((y/2)+11,(x/2)-13," ");
       }
     refresh();
    }*/
  //clear();
  return scelta;
}

void Animazioni::win(){
int x,y;
getmaxyx(stdscr,y,x);

for(int i=0;i<9;i++)
   for(int j=0;j<(x/2)+60;j++)
      mvprintw((y/2)-4+i,(x/2)-25+j," ");

refresh();

for(int i=0;i<6;i++)
  {
   mvprintw((y/2)-4,(x/2)-25,"* *        * * *         * *");
   mvprintw((y/2)-3,(x/2)-25,"* *        * * *         * *");
   mvprintw((y/2)-2,(x/2)-25," * *      * * * *       * * ");
   mvprintw((y/2)-1,(x/2)-25," * *      * * * *       * * ");
   mvprintw((y/2),(x/2)-25,"  * *    * *   * *     * *  ");
   mvprintw((y/2)+1,(x/2)-25,"  * *    * *   * *     * *  ");
   mvprintw((y/2)+2,(x/2)-25,"   * *  * *     * *  * *    ");
   mvprintw((y/2)+3,(x/2)-25,"     * * *        * * *     ");
   mvprintw((y/2)+4,(x/2)-25,"     * * *        * * *     ");

   mvprintw((y/2)-4,(x/2)+5,"* *");
   mvprintw((y/2)-3,(x/2)+5,"* *");
   mvprintw((y/2)-2,(x/2)+5,"* *");
   mvprintw((y/2)-1,(x/2)+5,"* *");
   mvprintw((y/2),(x/2)+5,"* *");
   mvprintw((y/2)+1,(x/2)+5,"* *");
   mvprintw((y/2)+2,(x/2)+5,"* *");
   mvprintw((y/2)+3,(x/2)+5,"* *");
   mvprintw((y/2)+4,(x/2)+5,"* *");

   mvprintw ((y/2)-4,(x/2)+11,"* * * *    * *");
   mvprintw ((y/2)-3,(x/2)+11,"* * * *    * *"); 
   mvprintw ((y/2)-2,(x/2)+11,"* *  * *   * *"); 
   mvprintw ((y/2)-1,(x/2)+11,"* *  * *   * *");
   mvprintw ((y/2),(x/2)+11,"* *   * *  * *");   
   mvprintw ((y/2)+1,(x/2)+11,"* *   * *  * *");
   mvprintw ((y/2)+2,(x/2)+11,"* *    * * * *");
   mvprintw ((y/2)+3,(x/2)+11,"* *    * * * *");
   mvprintw ((y/2)+4,(x/2)+11,"* *     * * *");                                 
   refresh();                                                                   
   usleep(500000);
   refresh();
   if(i==5) break; 
   for(int i=(y/2)-4;i<=(y/2)+4;i++)
      for(int j=5;j<=143;j++)
       mvprintw(i,j," ");
   refresh();
   usleep(500000);
  }

 for(int i=0;i<3;i++)
    {
     mvprintw((y/2)+4,(x/2)-54,"           *");
     mvprintw((y/2)+4,(x/2)+30,"           *");
     refresh();
     usleep(250000);
     refresh(); 
     mvprintw((y/2)+3,(x/2)-54,"          * *");
     mvprintw((y/2)+3,(x/2)+30,"          * *");
     refresh();
     usleep(250000);
     refresh();
     mvprintw((y/2)+2,(x/2)-54,"         * * *");
     mvprintw((y/2)+2,(x/2)+30,"         * * *");
     refresh();
     usleep(250000);
     refresh();
     mvprintw((y/2)+1,(x/2)-54,"        *  *  *");
     mvprintw((y/2)+1,(x/2)+30,"        *  *  *");
     refresh();
     usleep(250000);
     refresh();
     mvprintw((y/2),(x/2)-54,"      *    *    *");
     mvprintw((y/2),(x/2)+30,"      *    *    *");
     refresh();
     usleep(250000);
     refresh();
     mvprintw((y/2)-1,(x/2)-54,"    *     * *     *");
     mvprintw((y/2)-1,(x/2)+30,"    *     * *     *");
     refresh();
     usleep(250000);
     refresh();
     mvprintw((y/2)-2,(x/2)-54,"  *     *     *      *");
     mvprintw((y/2)-2,(x/2)+30,"  *     *     *      *");
     refresh();
     usleep(250000);
     refresh();
     mvprintw((y/2)-3,(x/2)-54,"*    *            *     *");
     mvprintw((y/2)-3,(x/2)+30,"*    *            *     *");
     refresh();
     usleep(250000);
     refresh();

     mvprintw((y/2)-3,(x/2)-54,"                         ");
     mvprintw((y/2)-2,(x/2)-54,"                         ");
     mvprintw((y/2)-1,(x/2)-54,"                         ");
     mvprintw((y/2),(x/2)-54,"                         ");
     mvprintw((y/2)+1,(x/2)-54,"                         ");
     mvprintw((y/2)+2,(x/2)-54,"                         ");
     mvprintw((y/2)+3,(x/2)-54,"                         ");
     mvprintw((y/2)+4,(x/2)-54,"                         ");

     mvprintw((y/2)-3,(x/2)+30,"                         ");
     mvprintw((y/2)-2,(x/2)+30,"                         ");
     mvprintw((y/2)-1,(x/2)+30,"                         ");
     mvprintw((y/2),(x/2)+30,"                         ");
     mvprintw((y/2)+1,(x/2)+30,"                         ");
     mvprintw((y/2)+2,(x/2)+30,"                         ");
     mvprintw((y/2)+3,(x/2)+30,"                         ");
     mvprintw((y/2)+4,(x/2)+30,"                         ");
     refresh();
     usleep(250000);
     refresh();
    }
clear();
}

void Animazioni::mostraZaino(Persona* persona){
/*
0=menu armi;
1=menu kit
*/
   int x,y;
   int scelta=0;
   char c;

   clear();
   getmaxyx(stdscr,y,x);
   mvprintw((y/2)-9,(x/2)-24,"    *    ");
   mvprintw((y/2)-8,(x/2)-24,"  *   *  ");
   mvprintw((y/2)-7,(x/2)-24,"*   *   *");
   mvprintw((y/2)-6,(x/2)-24,"  *   *  ");
   mvprintw((y/2)-5,(x/2)-24,"    *    ");


   mvprintw((y/2)-17,(x/2)-17,"Selezionare la tipologia di oggetti");
   mvprintw((y/2)-16,(x/2)-25,"Premere w ed s per selezionare e invio per confermare");
   mvprintw((y/2)-14,(x/2)-13, "* * * * * * * * * * * * * *");
   mvprintw((y/2)-13,(x/2)-13, "*                         *");
   mvprintw((y/2)-12,(x/2)-13, "*                         *");
   mvprintw((y/2)-11,(x/2)-13, "*                         *");
   mvprintw((y/2)-10,(x/2)-13, "*   _  _______________,   *");
   mvprintw((y/2)-9,(x/2)-13, "*    //@([__]__________)  *");
   mvprintw((y/2)-8,(x/2)-13, "*    /||--[__]            *");
   mvprintw((y/2)-7,(x/2)-13, "*   /    /(( )            *");
   mvprintw((y/2)-6,(x/2)-13, "*  /    |'---'            *");
   mvprintw((y/2)-5,(x/2)-13, "*  |____/                 *");
   mvprintw((y/2)-4,(x/2)-13,"*                         *");
   mvprintw((y/2)-3,(x/2)-13,"*                         *");
   mvprintw((y/2)-2,(x/2)-13,"*                         *");
   mvprintw((y/2)-1,(x/2)-13,"* * * * * * * * * * * * * *");

   mvprintw((y/2)+1,(x/2)-13, "* * * * * * * * * * * * * *");
   mvprintw((y/2)+2,(x/2)-13, "*         *     *         *");
   mvprintw((y/2)+3,(x/2)-13, "*         *     *         *");
   mvprintw((y/2)+4,(x/2)-13, "*         *     *         *");
   mvprintw((y/2)+5,(x/2)-13, "*         *     *         *");
   mvprintw((y/2)+6,(x/2)-13, "* * * * * *     * * * * * *");
   mvprintw((y/2)+7,(x/2)-13, "*                         *");
   mvprintw((y/2)+8,(x/2)-13, "*                         *");
   mvprintw((y/2)+9,(x/2)-13, "* * * * * *     * * * * * *");
   mvprintw((y/2)+10,(x/2)-13, "*         *     *         *");
   mvprintw((y/2)+11,(x/2)-13,"*         *     *         * ");
   mvprintw((y/2)+12,(x/2)-13,"*         *     *         * ");
   mvprintw((y/2)+13,(x/2)-13,"*         *     *         * ");
   mvprintw((y/2)+14,(x/2)-13,"* * * * * * * * * * * * * *");
   refresh();

   while((c=getch())!=10){
    if(scelta==0 && (c=='w' || c=='W') || (c=='s' || c=='S'))
      {
       scelta=1;
       mvprintw((y/2)-9,(x/2)-24,"         ");
       mvprintw((y/2)-8,(x/2)-24,"         ");
       mvprintw((y/2)-7,(x/2)-24,"         ");
       mvprintw((y/2)-6,(x/2)-24,"         ");
       mvprintw((y/2)-5,(x/2)-24,"         ");
       
       mvprintw((y/2)+9,(x/2)-24,"    *    ");
       mvprintw((y/2)+8,(x/2)-24,"  *   *  ");
       mvprintw((y/2)+7,(x/2)-24,"*   *   *");
       mvprintw((y/2)+6,(x/2)-24,"  *   *  ");
       mvprintw((y/2)+5,(x/2)-24,"    *    ");
      }
    else if(scelta==1 && (c=='w' || c=='W') || (c=='s' || c=='S'))
      {
       scelta=0;
       mvprintw((y/2)-9,(x/2)-24,"    *    ");
       mvprintw((y/2)-8,(x/2)-24,"  *   *  ");
       mvprintw((y/2)-7,(x/2)-24,"*   *   *");
       mvprintw((y/2)-6,(x/2)-24,"  *   *  ");
       mvprintw((y/2)-5,(x/2)-24,"    *    ");

       mvprintw((y/2)+9,(x/2)-24,"         ");
       mvprintw((y/2)+8,(x/2)-24,"         ");
       mvprintw((y/2)+7,(x/2)-24,"         ");
       mvprintw((y/2)+6,(x/2)-24,"         ");
       mvprintw((y/2)+5,(x/2)-24,"         ");
      }
    refresh();
   }
   
   clear();

   p_oggetto zaino[50];
   persona->getZaino(zaino);

   if(scelta==0){
      int x_app,y_app;
      char nome_arma[50];
      x_app=(x/2)-38;
      y_app=(y/2)-12;
      Arma_icon r=ListaArma(zaino);
      if(r==NULL)
        {
         mvprintw((y/2),(x/2)-10,"NESSUNA ARMA PRESENTE");
         mvprintw((y/2)+1,(x/2)-24,"PREMERE UN TASTO PER TORNARE AL MENU' PRECEDENTE");
         refresh();
	 getch();
	 return;
        }
      else
        {
         clear();
         Arma_icon app=r;
         stampaArma(x_app,y_app,app->draw);
         //refresh();
      
         app->arma->getNome(nome_arma);
         mvprintw((y/2)-17,(x/2)-11,"Invio => seleziona arma");
         mvprintw((y/2)-16,(x/2)-11,"    4 => scorri verso sinistra");
         mvprintw((y/2)-15,(x/2)-11,"    6 => scorri verso destra");
         mvprintw((y/2)-14,(x/2)-11,"SPACE => elimina arma");
         mvprintw(y_app+25,(x/2)-14,"Nome: \t\t\t%s",nome_arma);
         mvprintw(y_app+26,(x/2)-14,"Munizioni: \t\t%d",app->arma->getMunizioni());
         mvprintw(y_app+27,(x/2)-14,"Munizioni per sparo: \t%d",app->arma->getNumProiettili());
         mvprintw(y_app+28,(x/2)-14,"Danni: \t\t\t%d",app->arma->getDanni());
         mvprintw(y_app+29,(x/2)-14,"Gittata (per carattere): \t%d",app->arma->getGittata());

         while((c=getch())!=10)
           {
            if(c==52 || c==54 || c==' ')
              {
                for(int i=25;i<=29;i++)
                   for(int j=(x/2)-14;j<x;j++)
                      mvprintw(y_app+i,j," ");

                refresh();
              }         

            if(c==52)  
              app=ScorriArma(app,x-1,x_app,y_app,4,10000);
            else if(c==54 || c==' ')  
              {
               app=ScorriArma(app,x-1,x_app,y_app,6,10000);
               if(c==' ')
                 {
                  Oggetto del;
                  int index_arma;
                  del.kit=NULL;
                  del.arma=app->next->arma;

                  if(persona->getArma()==app->next->arma)
                    persona->setArma(NULL);

                  persona->removeOggetto(del);
                  Arma_icon previous=app;
                  Arma_icon cor=app->next;
                  Arma_icon prox=app->next->next;
                  
                  if(previous==prox && previous==cor)
                    {
                     clear();
                     mvprintw((y/2),(x/2)-10,"NESSUN'ARMA PRESENTE");
                     mvprintw((y/2)+1,(x/2)-18,"PREMERE UN TASTO PER TORNARE AL GIOCO");
                     refresh();
                     getch();
	             return; 
                    }
                  previous->next=prox;
                  prox->pre=previous;
                  cor->pre=NULL;
                  cor->next=NULL;
                  delete cor;
                 }
              }

            app->arma->getNome(nome_arma);
            mvprintw(y_app+25,(x/2)-14,"Nome: \t\t\t%s",nome_arma);
            mvprintw(y_app+26,(x/2)-14,"Munizioni: \t\t%d",app->arma->getMunizioni());
            mvprintw(y_app+27,(x/2)-14,"Munizioni per sparo: \t%d",app->arma->getNumProiettili());
            mvprintw(y_app+28,(x/2)-14,"Danni: \t\t\t%d",app->arma->getDanni());
            mvprintw(y_app+29,(x/2)-14,"Gittata (per carattere): \t%d",app->arma->getGittata()); 
            refresh();
           }

           persona->setArma(app->arma);
        }//fine r!=NULL
     }//fine ramo scelta di arma
   else{
        int x_app,y_app;
        x_app=(x/2)-26;
        y_app=(y/2)-12;

        //caricamento della picture dei kit
        char path[9]="armi/kit";
        char draw[25][50];
        int j=0; 
        ifstream file;
        path[8]='\0'; 

        file.open(path,ifstream::in);
        while(file.good() && j<25)
             file.getline(draw[j++],50);
        file.close();
        //*********************************
        KIT_icon r=ListaKIT(zaino);
        if(r==NULL)
          {
           mvprintw((y/2),(x/2)-10,"NESSUN KIT PRESENTE");
           mvprintw((y/2)+1,(x/2)-18,"PREMERE UN TASTO PER TORNARE AL GIOCO");
           refresh();
	   getch();
	   return;
          }
        else{
             KIT_icon app=r;
             clear();
             stampaKIT(x_app,y_app,draw);
      
             mvprintw((y/2)-17,(x/2)-15,"Invio => seleziona kit medico");
             mvprintw((y/2)-16,(x/2)-15,"    4 => scorri verso sinistra");
             mvprintw((y/2)-15,(x/2)-15,"    6 => scorri verso destra");
             mvprintw((y/2)-14,(x/2)-15,"SPACE => elimina kit dallo zaino");
             mvprintw(y_app+27,(x/2)-15,"Vita:   %d",app->kit->vita);
             if(app->kit->quantita>0)
               mvprintw(y_app+28,(x/2)-15,"Scorte: %d",app->kit->quantita);
             else
               mvprintw(y_app+28,(x/2)-15,"Scorte: Esaurite");

             while((c=getch())!=10)
               {
                if(c==52 || c==54 || c==' ')
                  {
                    for(int i=25;i<=26;i++)
                       for(int j=(x/2)-14;j<x;j++)
                          mvprintw(y_app+i,j," ");

                    refresh();
                  }         

                if(c==52)  
                  app=ScorriKIT(app,draw,x-1,x_app,y_app,4,10000);
                else if(c==54 || c==' ')  
                       {
                        app=ScorriKIT(app,draw,x-1,x_app,y_app,6,10000);
                        if(c==' ')
                          {
                           Oggetto del;
                           del.arma=NULL;
                           del.kit=app->next->kit;
                           persona->removeOggetto(del);
                           KIT_icon previous=app;
                           KIT_icon cor=app->next;
                           KIT_icon prox=app->next->next;
                           
                           if(previous==prox && previous==cor)
                             {
                             clear();
                             mvprintw((y/2),(x/2)-10,"NESSUN KIT PRESENTE");
                             mvprintw((y/2)+1,(x/2)-24,"PREMERE UN TASTO PER TORNARE AL MENU' PRECEDENTE");
                             refresh();
                             getch();
	                     return; 
                             }
                           else
                            {
                             previous->next=prox;
                             prox->pre=previous;
                             cor->pre=NULL;
                             cor->next=NULL;
                             delete cor;
                            }
                          }
                       }
                  


                mvprintw(y_app+27,(x/2)-15,"Vita:   %d",app->kit->vita);
                if(app->kit->quantita>0)
                  mvprintw(y_app+28,(x/2)-15,"Scorte: %d",app->kit->quantita);
                else
                  mvprintw(y_app+28,(x/2)-15,"Scorte: Esaurite");
                refresh();
               }

               if(app->kit->quantita<=0){
                  mvprintw((y/2)-30,(x/2)-6,"KIT ESAURITO");
                  refresh();
                  usleep(1500000);
                  refresh();
                  clear();
                  this->mostraZaino(persona);//da vedere
                  return;
                 }
               else{
                 persona->addVita(app->kit->vita);
                 app->kit->quantita--;
                 }
         }//fine ramo con r!=NULL

       }
clear();
return;
}


void Animazioni::gameMenu(Controller* controller,Stanza* s,int id_stanza_giocatore,int livello,int num_stanze,Persona* persone[],int num_persone){

   int x,y;
   int scelta=0;
   char c;

   clear();
   getmaxyx(stdscr,y,x);
   mvprintw((y/2)+1,(x/2)-42,"    *    ");
   mvprintw((y/2)+2,(x/2)-42,"  *   *  ");
   mvprintw((y/2)+3,(x/2)-42,"*   *   *");
   mvprintw((y/2)+4,(x/2)-42,"  *   *  ");
   mvprintw((y/2)+5,(x/2)-42,"    *    ");


   mvprintw((y/2)-17,(x/2)-17,"Selezionare la tipologia di oggetti");
   mvprintw((y/2)-16,(x/2)-25,"Premere w ed s per selezionare e invio per confermare");
   mvprintw((y/2)-14,(x/2)-50, "* * * * * * * * * * * * * *");
   mvprintw((y/2)-13,(x/2)-50, "*   ***    ***    ***     *");
   mvprintw((y/2)-12,(x/2)-50, "*   * ****** ****** *     *");
   mvprintw((y/2)-11,(x/2)-50, "*   ***    ***    ***     *");
   mvprintw((y/2)-10,(x/2)-50, "*    *      *      *      *");
   mvprintw((y/2)-9,(x/2)-50,  "*    *      *      *      *");
   mvprintw((y/2)-8,(x/2)-50,  "*   ***    ***    ***     *");
   mvprintw((y/2)-7,(x/2)-50,  "*   * *    * ****** *     *");
   mvprintw((y/2)-6,(x/2)-50,  "*   ***    ***    ***     *");
   mvprintw((y/2)-5,(x/2)-50,  "*                         *");
   mvprintw((y/2)-4,(x/2)-50,  "*                         *");
   mvprintw((y/2)-3,(x/2)-50,  "*    MAPPA LIVELLO        *");
   mvprintw((y/2)-2,(x/2)-50,  "*                         *");
   mvprintw((y/2)-1,(x/2)-50,  "* * * * * * * * * * * * * *");

   mvprintw((y/2)-14,(x/2)-13,"* * * * * * * * * * * * * *");
   mvprintw((y/2)-13,(x/2)-13,"*                         *");
   mvprintw((y/2)-12,(x/2)-13,"*             __          *");
   mvprintw((y/2)-11,(x/2)-13,"*            |            *");
   mvprintw((y/2)-10,(x/2)-13,"*            |            *");
   mvprintw((y/2)-9,(x/2)-13, "*   ******** | *********  *");
   mvprintw((y/2)-8,(x/2)-13, "*   *       *****  U   *  *");
   mvprintw((y/2)-7,(x/2)-13, "*   *<- | ->* - * A  O *  *");
   mvprintw((y/2)-6,(x/2)-13, "*   *   V   *****  X   *  *");
   mvprintw((y/2)-5,(x/2)-13, "*   ********   *********  *");
   mvprintw((y/2)-4,(x/2)-13, "*                         *");
   mvprintw((y/2)-3,(x/2)-13, "*   MODIFICA COMANDI      *");
   mvprintw((y/2)-2,(x/2)-13, "*                         *");
   mvprintw((y/2)-1,(x/2)-13, "* * * * * * * * * * * * * *");

   mvprintw((y/2)-14,(x/2)+24,"* * * * * * * * * * * * * *");
   mvprintw((y/2)-13,(x/2)+24,"*   ____________________  *");
   mvprintw((y/2)-12,(x/2)+24,"*   |                  |  *");
   mvprintw((y/2)-11,(x/2)+24,"*   |  |||||    |||||  |  *");
   mvprintw((y/2)-10,(x/2)+24,"*   |   ...      ...   |  *");
   mvprintw((y/2)-9,(x/2)+24, "*   |   ...   .  ...   |  *");
   mvprintw((y/2)-8,(x/2)+24, "*   |         .        |  *");
   mvprintw((y/2)-7,(x/2)+24, "*   |    -----------   |  *");
   mvprintw((y/2)-6,(x/2)+24, "*   |    -----------   |  *");
   mvprintw((y/2)-5,(x/2)+24, "*   |__________________|  *");
   mvprintw((y/2)-4,(x/2)+24, "*                         *");
   mvprintw((y/2)-3,(x/2)+24, "*   ELENCO PERSONAGGI     *");
   mvprintw((y/2)-2,(x/2)+24, "*                         *");
   mvprintw((y/2)-1,(x/2)+24, "* * * * * * * * * * * * * *");
   refresh();

   refresh();
//***********************iniziale***********************
scelta=0;
       mvprintw((y/2)+1,(x/2)-42,"    *    ");
       mvprintw((y/2)+2,(x/2)-42,"  *   *  ");
       mvprintw((y/2)+3,(x/2)-42,"*   *   *");
       mvprintw((y/2)+4,(x/2)-42,"  *   *  ");
       mvprintw((y/2)+5,(x/2)-42,"    *    ");
//******************************************************

   while((c=getch())!=10){
    if((scelta==1 && (c=='a' || c=='A'))||(scelta==2 && (c=='d' || c=='D')))
      {
       scelta=0;

       mvprintw((y/2)+1,(x/2)-42,"    *    ");
       mvprintw((y/2)+2,(x/2)-42,"  *   *  ");
       mvprintw((y/2)+3,(x/2)-42,"*   *   *");
       mvprintw((y/2)+4,(x/2)-42,"  *   *  ");
       mvprintw((y/2)+5,(x/2)-42,"    *    ");

       mvprintw((y/2)+1,(x/2)-3,"         ");
       mvprintw((y/2)+2,(x/2)-3,"         ");
       mvprintw((y/2)+3,(x/2)-3,"         ");
       mvprintw((y/2)+4,(x/2)-3,"         ");
       mvprintw((y/2)+5,(x/2)-3,"         ");
       
       mvprintw((y/2)+1,(x/2)+34,"         ");
       mvprintw((y/2)+2,(x/2)+34,"         ");
       mvprintw((y/2)+3,(x/2)+34,"         ");
       mvprintw((y/2)+4,(x/2)+34,"         ");
       mvprintw((y/2)+5,(x/2)+34,"         ");
      }
    else if((scelta==0 && (c=='d' || c=='D'))||(scelta==2 && (c=='a' || c=='A')))
      {
       scelta=1;

       mvprintw((y/2)+1,(x/2)-42,"         ");
       mvprintw((y/2)+2,(x/2)-42,"         ");
       mvprintw((y/2)+3,(x/2)-42,"         ");
       mvprintw((y/2)+4,(x/2)-42,"         ");
       mvprintw((y/2)+5,(x/2)-42,"         ");

       mvprintw((y/2)+1,(x/2)-3,"    *    ");
       mvprintw((y/2)+2,(x/2)-3,"  *   *  ");
       mvprintw((y/2)+3,(x/2)-3,"*   *   *");
       mvprintw((y/2)+4,(x/2)-3,"  *   *  ");
       mvprintw((y/2)+5,(x/2)-3,"    *    ");

       mvprintw((y/2)+1,(x/2)+34,"         ");
       mvprintw((y/2)+2,(x/2)+34,"         ");
       mvprintw((y/2)+3,(x/2)+34,"         ");
       mvprintw((y/2)+4,(x/2)+34,"         ");
       mvprintw((y/2)+5,(x/2)+34,"         ");


      }
    else if((scelta==0 && (c=='a' || c=='A'))||(scelta==1 && (c=='d' || c=='D')))
      {
       scelta=2;

       mvprintw((y/2)+1,(x/2)-42,"         ");
       mvprintw((y/2)+2,(x/2)-42,"         ");
       mvprintw((y/2)+3,(x/2)-42,"         ");
       mvprintw((y/2)+4,(x/2)-42,"         ");
       mvprintw((y/2)+5,(x/2)-42,"         ");

       mvprintw((y/2)+1,(x/2)-3,"         ");
       mvprintw((y/2)+2,(x/2)-3,"         ");
       mvprintw((y/2)+3,(x/2)-3,"         ");
       mvprintw((y/2)+4,(x/2)-3,"         ");
       mvprintw((y/2)+5,(x/2)-3,"         ");

       mvprintw((y/2)+1,(x/2)+34,"    *    ");
       mvprintw((y/2)+2,(x/2)+34,"  *   *  ");
       mvprintw((y/2)+3,(x/2)+34,"*   *   *");
       mvprintw((y/2)+4,(x/2)+34,"  *   *  ");
       mvprintw((y/2)+5,(x/2)+34,"    *    ");

      }
    refresh();
   }

  if(scelta==2)
     PersoneDetail(persone,num_persone,s->getIndexStanza(),s->getIndexLivello());
  else if(scelta==1)
     changeControl(controller);
  else if(scelta==0)
     LevelMap(controller,s,num_stanze,id_stanza_giocatore,livello);
  return;

}

void Animazioni::disegnaStanza(Stanza* s,int id_usati[],int num_stanze, coordinate coo,int id_giocatore_stanza,int idLivello){
   bool controllo=false;

   if(s->getIndexLivello()!=idLivello)
     return;
   
   for(int i=0;i<num_stanze;i++)
      if(s->getIndexStanza()==id_usati[i])
         return;

   for(int j=0;j<num_stanze && ! controllo;j++)
      if(id_usati[j]<0)
         { controllo=true; id_usati[j]=s->getIndexStanza();}

   if(!controllo) 
     return;

   mvprintw(coo.y-1,coo.x,"* * *");
   if(s->getIndexStanza()==id_giocatore_stanza)
     mvprintw(coo.y,coo.x,"* O *");
   else   
     mvprintw(coo.y,coo.x,"*   *");
   mvprintw(coo.y+1,coo.x,"* * *");
   refresh();

  if(s->top!=NULL){
      controllo=false;
      for(int i=0;i<num_stanze && !controllo;i++)
          if(s->top->getIndexStanza()==id_usati[i])
            controllo=true;

      if(!controllo){
        // app=app->top; 
         mvprintw(coo.y-2,coo.x+2,"|");
         refresh();
         coo.y-=4;
         disegnaStanza(s->top,id_usati,num_stanze,coo,id_giocatore_stanza,idLivello);
         coo.y+=4;
         //id_stanze[i_stanza++]=app->getIndexStanza();
         }
      /*else{
        mvprintw(coo.y-1,coo.x,"2");
        refresh(); 
       }*/
     }

  if(s->right!=NULL){
      controllo=false;
      for(int i=0;i<num_stanze && !controllo;i++)
          if(s->right->getIndexStanza()==id_usati[i])
            controllo=true;

      if(!controllo){
        //app=app->right;
        mvprintw(coo.y,coo.x+5," - ");
        refresh();
        coo.x+=8; 
        disegnaStanza(s->right,id_usati,num_stanze,coo,id_giocatore_stanza,idLivello);
        coo.x-=8;
        //id_stanze[i_stanza++]=app->getIndexStanza();
       }
      /*else{
        mvprintw(coo.y,coo.x+2,"4");
        refresh(); 
       }*/
    }

  if(s->bottom!=NULL){
      controllo=false;
      for(int i=0;i<num_stanze && !controllo;i++)
          if(s->bottom->getIndexStanza()==id_usati[i])
            controllo=true;

      if(!controllo){
        //app=app->right;
        mvprintw(coo.y+2,coo.x+2,"|");
        refresh();
        coo.y+=4; 
        disegnaStanza(s->bottom,id_usati,num_stanze,coo,id_giocatore_stanza,idLivello);
        coo.y-=4;
        //id_stanze[i_stanza++]=app->getIndexStanza();
       }
      /*else{
        mvprintw(coo.y+3,coo.x,"6");
        refresh(); 
       }*/
    }

  if(s->left!=NULL){
      controllo=false;
      for(int i=0;i<num_stanze && !controllo;i++)
          if(s->left->getIndexStanza()==id_usati[i])
            controllo=true;

      if(!controllo){
        //app=app->right;
        mvprintw(coo.y,coo.x-3," - ");
        refresh();
        coo.x-=8;
        
        refresh(); 
        disegnaStanza(s->left,id_usati,num_stanze,coo,id_giocatore_stanza,idLivello);
        coo.x+=8;
        //id_stanze[i_stanza++]=app->getIndexStanza();
       }
      /*else{
        mvprintw(coo.y,coo.x-1,"*");
        refresh(); 
       }*/
    }
}

void Animazioni::LevelMap(Controller* controller,Stanza* first,int num_stanze,int id_stanza_giocatore,int idLivello){

clear();
int id_stanze[num_stanze];
coordinate coo;
//char minimap[3][3]={"* * *","*   *","* * *"};
Stanza* app;

app=first;
getmaxyx(stdscr,coo.y,coo.x);

mvprintw(1,(coo.x/2)-7,"O : TU SEI QUI");
mvprintw(3,(coo.x/2)-16,"[PREMERE UN TASTO PER CONTINUARE]");
mvprintw(5,(coo.x/2)-10,"MAPPA PER LIVELLO %d",idLivello);

for(int i=0;i<num_stanze;i++)
  id_stanze[i]=-1;

coo.y/=2;
coo.x=coo.x/2;

int i_stanza=0;
int id_stanza=-1;
bool controllo=false;
//mvprintw(0,0,"stanze:%d",num_stanze);

   disegnaStanza(first,id_stanze,num_stanze,coo,id_stanza_giocatore,idLivello);
   getch();
}

void Animazioni::PersoneDetail(Persona* persone[], int num,int id_stanza,int id_livello){
clear();
int x,y;
getmaxyx(stdscr,y,x);

mvprintw(3,(x/2)-27,"Dettagli dei personaggi nella stanza %d del livello %d",id_stanza,id_livello);
mvprintw(5,(x/2)-20,"[PREMERE UN TASTO PER TORNARE AL GIOCO]");

refresh();
int inizio_stampa_nemici=0;
int inizio_stampa_aiutanti=0;
for(int i=0;i<num;i++){

   if(persone[i]!=NULL){
      char nome[50];
      char tipo[50];
      char arma[25];
      int offset_x=0;
      persone[i]->getNome(nome);
      persone[i]->getTipo(tipo);

      if(strcmp(tipo,"Nemico")==0){
         
         if(persone[i]->getArma()!=NULL){
           persone[i]->getArma()->getNome(arma);
           mvprintw(10+(inizio_stampa_nemici++),(x/2)+20,"%d:%s [%s] => %s",persone[i]->getVita(),nome,tipo,arma);
          }//stampa arma
         else
          mvprintw(10+(inizio_stampa_nemici++),(x/2)+20,"%d:%s [%s] => None",persone[i]->getVita(),nome,tipo);
         inizio_stampa_nemici++;
        }//stampa nemici

     else{
         
         if(persone[i]->getArma()!=NULL){
           persone[i]->getArma()->getNome(arma);
           mvprintw(10+(inizio_stampa_aiutanti++),(x/2)-50,"%d:%s [%s] => %s",persone[i]->getVita(),nome,tipo,arma);
          }//stampa arma
         else
          mvprintw(10+(inizio_stampa_aiutanti++),(x/2)-50,"%d:%s [%s] => None",persone[i]->getVita(),nome,tipo);
         inizio_stampa_aiutanti++;
        }//stampa aiutanti
      refresh();
     }//persona esistente
}//fine for()

getch();
}
