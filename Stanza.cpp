#include <fstream>
#include <cstdlib>
#include <cstring>
#include <ncurses.h>
#include "Giocatore.cpp"
#include "Stanza.hpp"

using namespace std;

Stanza::Stanza(Giocatore* giocatore,int idLivello,int idStanza,int id_matrix_used[],int num_id) {
srand(time(0));

for(int i=0;i<num_max_nemici;i++)
    nemici[i]=NULL;

    top = NULL;
    bottom = NULL;
    right = NULL;
    left = NULL;

    this->idLivello=idLivello;
    this->idStanza=idStanza;
    
    int x, y;
    char path[] = "stanze/0";


    bool cerca=false;
    int j=0;
    for(j=0;j<num_id && !cerca;j++)
         if(id_matrix_used[j]<0)
          cerca=true; 
  
    if(cerca)
     {
      bool c1=false;
      int new_id;
      do{
         c1=false;
        new_id=rand()%10;
        for(int z=0;z<num_id && !c1;z++)
          if(new_id==id_matrix_used[z])
             c1=true;
        }while(c1);
       
      id_matrix_used[j]=new_id;
      path[7]+=new_id;
     }

    ifstream input;
    input.open(path);
    
    y = 0;
    char riga[STANZA_X+1];
    while(!input.eof() && (y < STANZA_Y)) { // Lettura riga per riga da file
        input.getline(riga, STANZA_X);
        for(int x=0; x < STANZA_X; ++x){ // Scrittura della riga letta nella rispettiva riga della matrice stanza
            stanza[y][x] = riga[x];
        }
        ++y;
    }
    
    input.close();

//*****************************GENERAZIONI DI OGGETTI SULLA MAPPA********************************
    int num_max_oggetti=30*idLivello;
    if(num_max_oggetti>300)
    num_max_oggetti=300;
    this->n_oggetti =(rand() % num_max_oggetti) +10;//, timeOut = STANZA_X*STANZA_Y*2;

    oggetti=(Oggetto_pos**)malloc(n_oggetti*sizeof(Oggetto_pos*));
    for(int i=0;i<n_oggetti;i++){ // Aggiungo oggetti alla stanza 
          do
             {
              x=rand() % STANZA_X;
              y=rand() % STANZA_Y;
             }
          while(stanza[y][x]!=' ');


          
         // if(stanza[y][x] == ' '){
            stanza[y][x] = ((rand()%2) == 0)?('+'):('o');
            oggetti[i]=new Oggetto_pos;
            oggetti[i]->coo.x=x;
            oggetti[i]->coo.y=y;
            //oggetti[i]=new Oggetto_pos;            
          if(stanza[y][x]=='+'){
              oggetti[i]->oggetto.arma=NULL;
              oggetti[i]->oggetto.kit=new KIT;
              if(idLivello>10)
                idLivello=10;
              oggetti[i]->oggetto.kit->vita=idLivello*((rand() % 10) +1);
              oggetti[i]->oggetto.kit->quantita=(rand() % 5) +1;
            }//generazione kit
           else{
                int arma=((rand() % 5) +1);
                bool scelto=false;
                while(!scelto)
                 {
                  if(idLivello==1 && (arma==1 || arma==2))
                    scelto=true;
                  else if(idLivello==2 && ((arma==1 || arma==2 || arma==5)))
                    scelto=true;
                  else if(idLivello==3 && ((arma==1 || arma==2 || arma==5 || arma==4)))
                    scelto=true;
                  else if(idLivello>=4)
                    scelto=true;
                  else 
                    arma=((rand() % 5) +1);
                 }
              
	      oggetti[i]->oggetto.kit=NULL;
              if(arma==1)
oggetti[i]->oggetto.arma=new Arma(GLOCK45,PROIETTILE,GLOCK45_MUNIZIONI_PER_SPARO,GLOCK45_DANNI,GLOCK45_GITTATA,GLOCK45_MUNIZIONI,GLOCK45_ID);
              else if(arma==2)
oggetti[i]->oggetto.arma=new Arma(MAGNUM44,PROIETTILE,MAGNUM44_MUNIZIONI_PER_SPARO,MAGNUM44_DANNI,MAGNUM44_GITTATA,MAGNUM44_MUNIZIONI,MAGNUM44_ID);
              else if(arma==3)
oggetti[i]->oggetto.arma=new Arma(MACHINEGUN,PROIETTILE,MACHINEGUN_MUNIZIONI_PER_SPARO,MACHINEGUN_DANNI,MACHINEGUN_GITTATA,MACHINEGUN_MUNIZIONI,MACHINEGUN_ID);
              else if(arma==4)
oggetti[i]->oggetto.arma=new Arma(AK_47,PROIETTILE,AK_47_MUNIZIONI_PER_SPARO,AK_47_DANNI,AK_47_GITTATA,AK_47_MUNIZIONI,AK_47_ID);
              else if(arma==5)
oggetti[i]->oggetto.arma=new Arma(WARFARE_SNIPER,PROIETTILE,WARFARE_SNIPER_MUNIZIONI_PER_SPARO,WARFARE_SNIPER_DANNI,WARFARE_SNIPER_GITTATA,WARFARE_SNIPER_MUNIZIONI,WARFARE_SNIPER_ID);
/*char nommme[25];
             mvprintw(0,0,"Hai raccolto un'arma");
             oggetti[i]->oggetto.arma->getNome(nommme);
             mvprintw(1,0,"Danni: %s",nommme);
             refresh();
             getch();
refresh();
getch();
*/
            }//generazione arma
           //}//posizione valida per la generazione
    }//fine for
//************************************************************************************************************************************
//**************************************GENERAZIONE NEMICI*******************************************************************************
 this->num_nemici=(rand() % num_max_nemici)+1;
 //nemici=new (Persona*)[15];
 for(int i=0;i<num_max_nemici;i++){
     if(i<num_nemici)
       {
        int app=i;
        char num[3];
        int num_rand=(rand()%3)+1;
        num[1]=(app%10)+'0';
        app/=10;
        num[0]=(app%10)+'0';
        num[2]='\0';
        //nemici[i]=(IA_Persona*)malloc(sizeof(IA_Persona));//nemici[i]=new Persona
        char nome[50]="T-800-";
        int vita=150*(0.25*idLivello*num_rand);
        if(vita>500)
          vita=500;
        strcat(nome,num);
        nemici[i]=new Personaggio(nome,(char*)"Nemico",'T',vita);

        coordinate coo_nemico;
        coo_nemico.x=rand() % STANZA_X;
        coo_nemico.y=rand() % STANZA_Y;
        while(stanza[coo_nemico.y][coo_nemico.x]!=' ')
             {
              coo_nemico.x=rand() % STANZA_X;
              coo_nemico.y=rand() % STANZA_Y;
             } 
        nemici[i]->setCoordinate(coo_nemico);

        
     int id_arma=((rand() % 5) +1);
     bool scelto=false;
     while(!scelto)
       {
        if(idLivello==1 && (id_arma==1 || id_arma==2))
           scelto=true;
        else if(idLivello==2 && ((id_arma==1 || id_arma==2 || id_arma==5)))
           scelto=true;
        else if(idLivello==3 && ((id_arma==1 || id_arma==2 || id_arma==5 || id_arma==4)))
           scelto=true;
        else if(idLivello>=4)
          scelto=true;
        else 
          id_arma=((rand() % 5) +1);
       }

        Oggetto arma;
        arma.kit=NULL;
        if(id_arma==1)
          arma.arma=new Arma(GLOCK45,PROIETTILE,GLOCK45_MUNIZIONI_PER_SPARO,GLOCK45_DANNI,GLOCK45_GITTATA,GLOCK45_MUNIZIONI,GLOCK45_ID);
        else if(id_arma==2)
          arma.arma=new Arma(MAGNUM44,PROIETTILE,MAGNUM44_MUNIZIONI_PER_SPARO,MAGNUM44_DANNI,MAGNUM44_GITTATA,MAGNUM44_MUNIZIONI,MAGNUM44_ID);
        else if(id_arma==3)
          arma.arma=new Arma (MACHINEGUN,PROIETTILE,MACHINEGUN_MUNIZIONI_PER_SPARO,MACHINEGUN_DANNI,MACHINEGUN_GITTATA,MACHINEGUN_MUNIZIONI,MACHINEGUN_ID);
        else if(id_arma==4)
          arma.arma=new Arma(AK_47,PROIETTILE,AK_47_MUNIZIONI_PER_SPARO,AK_47_DANNI,AK_47_GITTATA,AK_47_MUNIZIONI,AK_47_ID);
        else if(id_arma==5)
          arma.arma=new Arma(WARFARE_SNIPER,PROIETTILE,WARFARE_SNIPER_MUNIZIONI_PER_SPARO,WARFARE_SNIPER_DANNI,WARFARE_SNIPER_GITTATA,WARFARE_SNIPER_MUNIZIONI,WARFARE_SNIPER_ID);

        nemici[i]->addOggetto(arma);
        nemici[i]->setArma(arma.arma);  
       }
     else
       nemici[i]=NULL;
    }
}

void Stanza::creaAiutante(Giocatore* giocatore){
     Personaggio* new_aiutante=NULL; 
     bool controllo;
     char F[50]="Frank";
     char N[50]="Nick";
     char L[50]="Luke";
     char W[50]="Walter";
     char M[50]="Mr.White";
     char C[50]="Claire";
     char D[50]="Drake";
     char H[50]="Harper";
     char O[50]="Olivia";
     char J[50]="Josephine";
     do{
        controllo=false;
        if(new_aiutante!=NULL)
           delete new_aiutante;
        int scelta=(rand() % 10)+1;
        int num_rand=(rand()%3)+1;
        int vita=150*(0.25*idLivello*num_rand);
        if(vita>500)
          vita=500;

        if(scelta==1)
          new_aiutante=new Personaggio(F,(char*)"Aiutante",'F',vita);
        else if(scelta==2)
          new_aiutante=new Personaggio(N,(char*)"Aiutante",'N',vita);
        else if(scelta==3)
          new_aiutante=new Personaggio(L,(char*)"Aiutante",'L',vita);
        else if(scelta==4)
          new_aiutante=new Personaggio(W,(char*)"Aiutante",'W',vita);
        else if(scelta==5)
          new_aiutante=new Personaggio(M,(char*)"Aiutante",'M',vita);
        else if(scelta==6)
          new_aiutante=new Personaggio(C,(char*)"Aiutante",'C',vita);
        else if(scelta==7)
          new_aiutante=new Personaggio(D,(char*)"Aiutante",'D',vita);
        else if(scelta==8)
          new_aiutante=new Personaggio(H,(char*)"Aiutante",'H',vita);
        else if(scelta==9)
          new_aiutante=new Personaggio(O,(char*)"Aiutante",'O',vita);
        else if(scelta==10)
          new_aiutante=new Personaggio(J,(char*)"Aiutante",'J',vita);

        for(int j=0;j<giocatore->num_max_aiuti && !controllo;j++)
            controllo=giocatore->comparePersona(*new_aiutante,j);
           
     } 
     while(controllo);

     coordinate coo_aiutante;
     coo_aiutante.x=rand() % STANZA_X;
     coo_aiutante.y=rand() % STANZA_Y;
     int max=2000;
     int inizio=0;
     while(stanza[coo_aiutante.y][coo_aiutante.x]!=' ' && inizio<max)
       {
        coo_aiutante.x=rand() % STANZA_X;
        coo_aiutante.y=rand() % STANZA_Y;
        inizio++;
       }
     new_aiutante->setCoordinate(coo_aiutante);
     int index_aiutante=giocatore->addAiutante(*new_aiutante);

     

     int id_arma=((rand() % 5) +1);
     bool scelto=false;
     while(!scelto)
       {
        if(idLivello==1 && (id_arma==1 || id_arma==2))
           scelto=true;
        else if(idLivello==2 && ((id_arma==1 || id_arma==2 || id_arma==5)))
           scelto=true;
        else if(idLivello==3 && ((id_arma==1 || id_arma==2 || id_arma==5 || id_arma==4)))
           scelto=true;
        else if(idLivello>=4)
          scelto=true;
        else 
          id_arma=((rand() % 5) +1);
       }

     Oggetto arma;
     arma.kit=NULL;
     if(id_arma==1)
       arma.arma=new Arma(GLOCK45,PROIETTILE,GLOCK45_MUNIZIONI_PER_SPARO,GLOCK45_DANNI,GLOCK45_GITTATA,GLOCK45_MUNIZIONI,GLOCK45_ID);
     else if(id_arma==2)
       arma.arma=new Arma(MAGNUM44,PROIETTILE,MAGNUM44_MUNIZIONI_PER_SPARO,MAGNUM44_DANNI,MAGNUM44_GITTATA,MAGNUM44_MUNIZIONI,MAGNUM44_ID);
     else if(id_arma==3)
       arma.arma=new Arma (MACHINEGUN,PROIETTILE,MACHINEGUN_MUNIZIONI_PER_SPARO,MACHINEGUN_DANNI,MACHINEGUN_GITTATA,MACHINEGUN_MUNIZIONI,MACHINEGUN_ID);
     else if(id_arma==4)
       arma.arma=new Arma(AK_47,PROIETTILE,AK_47_MUNIZIONI_PER_SPARO,AK_47_DANNI,AK_47_GITTATA,AK_47_MUNIZIONI,AK_47_ID);
     else if(id_arma==5)
       arma.arma=new Arma(WARFARE_SNIPER,PROIETTILE,WARFARE_SNIPER_MUNIZIONI_PER_SPARO,WARFARE_SNIPER_DANNI,WARFARE_SNIPER_GITTATA,WARFARE_SNIPER_MUNIZIONI,WARFARE_SNIPER_ID);

//mvprintw(4,0,"num_ aiuti:%d   index_aiutante:%d",giocatore->num_aiuti,index_aiutante);
  //   refresh();

     giocatore->aiuti[index_aiutante]->addOggetto(arma);
     giocatore->aiuti[index_aiutante]->setArma(arma.arma);
}

void Stanza::aggiornaAiutanti(Giocatore* giocatore){
//************************************************GENERAZIONE AIUTANTI****************************************************************

  int num_aiuti=(rand() % giocatore->num_max_aiuti)+1;

//mvprintw(0,0,"num_aiuti da creare: %d",num_aiuti);
//refresh();

  int range=num_aiuti;
  if(giocatore->num_aiuti>0 && giocatore->num_aiuti<num_aiuti){
     range=num_aiuti-giocatore->num_aiuti;
     //giocatore->num_aiuti=num_aiuti;
     }

  else if(giocatore->num_aiuti>0 && giocatore->num_aiuti>num_aiuti)
     range=-1;
  else if(giocatore->num_aiuti>0 && range==giocatore->num_aiuti)
     range=-1;

  if(range>0)
    for(int i=0;i<range;i++)
       creaAiutante(giocatore);

  if(giocatore->num_aiuti==0)
    for(int i=0;i<num_aiuti;i++)
       creaAiutante(giocatore);
}

void Stanza::setIndexStanza(int id) {
    idStanza = id;
}

int Stanza::getIndexStanza() {
    return idStanza;
}

void Stanza::setIndexLivello(int id) {
    idLivello = id;
}

int Stanza::getIndexLivello(){
    return idLivello;
}
