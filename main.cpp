//============================================================================
// Name        : Progetto.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <ncurses.h>
#include "Game.cpp"

using namespace std;

//*********************************

int main() {
initscr();
noecho();
curs_set(0);


Giocatore* gamer;
Game* game;
int x,y;
gamer=new Giocatore((char*)"John Connor",(char*)"Eroe",100,(char)'v');

Oggetto o1,o2,o3,o4,o5;
o1.kit=NULL;
o2.kit=NULL;
o3.kit=NULL;
o4.kit=NULL;
o5.kit=NULL;

o1.arma=new Arma(GLOCK45,PROIETTILE,GLOCK45_MUNIZIONI_PER_SPARO,GLOCK45_DANNI,GLOCK45_GITTATA,10,GLOCK45_ID);
o2.arma=new Arma(MAGNUM44,PROIETTILE,MAGNUM44_MUNIZIONI_PER_SPARO,MAGNUM44_DANNI,MAGNUM44_GITTATA,10,MAGNUM44_ID);
o3.arma=new Arma(MACHINEGUN,PROIETTILE,MACHINEGUN_MUNIZIONI_PER_SPARO,MACHINEGUN_DANNI,MACHINEGUN_GITTATA,40,MACHINEGUN_ID);
o4.arma=new Arma(AK_47,PROIETTILE,AK_47_MUNIZIONI_PER_SPARO,AK_47_DANNI,AK_47_GITTATA,15,AK_47_ID);
o5.arma=new Arma(WARFARE_SNIPER,PROIETTILE,WARFARE_SNIPER_MUNIZIONI_PER_SPARO,WARFARE_SNIPER_DANNI,WARFARE_SNIPER_GITTATA,5,WARFARE_SNIPER_ID);

gamer->addOggetto(o1);
gamer->addOggetto(o2);
gamer->addOggetto(o3);
gamer->addOggetto(o4);
gamer->addOggetto(o5);

game=new Game(gamer);

//******************************STORY_LINE*********************************
getmaxyx(stdscr,y,x);

mvprintw((y/2)-6,(x/2)-19,"LA GUERRA... LA GUERRA NON CAMBIA MAI.");
refresh();
usleep(4000000);
refresh();
mvprintw((y/2)-5,(x/2)-57,"NON IMPORTA DI QUALE EPOCA SI PARLI PERCHE' E' UNA LEGGE UNIVERSALE CHE SI IMPARA NELLA PEGGIORE DELLE SITUAZIONI.");
refresh();
usleep(4000000);
refresh();
mvprintw((y/2)-4,(x/2)-56,"MA SOPRATUTTO IL PEGGIOR NEMICO DELL'UMANITA', E' L'UMANITA' STESSA. GRAZIE ALL'UMANITA' NOI POSSIAMO ESISTERE.");
refresh();
usleep(4000000);
refresh();
mvprintw((y/2)-3,(x/2)-41,"GRAZIE ALL'UMANITA E' NATA SKYNET. E' GRAZIE ALL'UMANITA CHE SONO NATI I TERMINATOR"); 
refresh();
usleep(4000000);
refresh();
mvprintw((y/2)-2,(x/2)-33,"ED E' GRAZIE ALL'UMANITA CHE L'UMANITA STESSA SI E' QUASI ESTINTA.");
refresh();
usleep(4000000);
refresh();
mvprintw((y/2)-1,(x/2)-25,"MA L'UMANITA' SIAMO NOI LO SIAMO STATI E LO SAREMO SEMPRE");
refresh();
usleep(4000000);
refresh();
mvprintw((y/2),(x/2)-41,"E OGGI VI DICO CHE ABBIAMO UNA POSSIBILITA', UNA POSSIBILITA' PER CAMBIARE LE COSE.");
refresh();
usleep(4000000);
refresh();
mvprintw((y/2)+1,(x/2)-31,"UNA POSSIBILITA' DI TORNARE NEL PASSATO PER CAMBIARE IL FUTURO!");
refresh();
usleep(4000000);
refresh();
mvprintw((y/2)+2,(x/2)-29,"UNA POSSIBILITA' PER FAR SI CHE SKYNET NON VENGA MAI CREATA!");
refresh();
usleep(4000000);
refresh();
mvprintw((y/2)+3,(x/2)-40,"PERCIO' VI CHIEDO DI AIUTARMI, A TROVARE I COMPONENTI PER UNA MACCHINA DEL TEMPO");
refresh();
usleep(4000000);
refresh();
mvprintw((y/2)+4,(x/2)-38,"CHE SKYNET, UNA VOLTA SAPUTO DELLA SUA ESISTENZA, LA DIVISA IN TANTI PEZZI");
refresh();
usleep(4000000);
refresh();
mvprintw((y/2)+5,(x/2)-21,"VI CHIEDO DI AIUTARMI A SCONFIGGERE SKYNET!");
refresh();
usleep(4000000);
refresh();
mvprintw((y/2)+6,(x/2)-21,"VI CHIEDO DI AIUTARMI A SALVARE L'UMANITA!");
refresh();
usleep(4000000);
refresh();
mvprintw((y/2)+8,(x/2)-37,"[RACCOGLI TUTTI I '#' PEZZI DELLA MACCHINA DEL TEMPO PER SALVARE IL FUTURO]");
refresh();
getch();
clear();

mvprintw((y/2)-1,(x/2)-32,"*****************************************************************");
mvprintw((y/2),(x/2)-32,  "*                          ART OF SURVIVAL                      *");
mvprintw((y/2)+1,(x/2)-32,"*****************************************************************");
refresh();
usleep(2000000);
refresh();
clear();
//*************************************************************************
game->start();


endwin();
return 0;
}

