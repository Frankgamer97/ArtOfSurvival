/*!
\file Livello.hpp
\author Nicola Serra
*/

#ifndef LIVELLO_HPP_INCLUDED
#define LIVELLO_HPP_INCLUDED
#include "Stanza.hpp"

/*!
 \class Livello
 \brief Definisce le specifiche che deve avere un livello di gioco
*/
class Livello{
private:
/*!
 \var livello
 \brief indice del livello
*/
int livello;
/*!
 \var n_stanze
 \brief costante che indica il numero massimo della stanze generabili per uno stesso livello
*/
static const int n_stanze=5;//numero delle stanze massime
/*!
 \var time_machine_part
 \brief numero di pezzi della machhina del tempo presenti nell'intero livello e sparsi per le stanze
*/
int time_machine_part;//numero di pezzi nell'intero livello

/*!
 \fn draw_time_machine
 \brief disegna sul tutte le stanze del livello collegate tutti i pezzi della macchina del tempo
 \param rest_time_machine_part numero di pezzi della macchina del tempo ancora da generare
 \param box stanza su cui stampara i perzzi della macchina del tempo
*/
void draw_time_machine(int rest_time_machine_part,Stanza* box);
public:
/*!
 \var s
 \brief prima stanza del livello
*/
Stanza* s;//stanza primaria (da intendersi la prima stanza che si entra nel nuovo livello)
/*!
 \var next
 \brief puntatore al livello successivo
*/
Livello* next;//livello successivo
/*!
 \var pre
 \brief puntatore al livello precedente
*/
Livello* pre;//livello precedente
/*!
 \var num_stanze
 \brief numero di stanze generate nel livello (<=n_stanze)
*/
int num_stanze;//numero di stanze attualmente presenti


/*!
 \fn Livello
 \brief Costruttore che crea le stanze del livello e genera i pezzi della macchina del tempo
 \param gamer Giocatore utente
 \param pre Livello precedente (=NULL se è il primo livello, !=NULL altrimenti)
 \param direction_pre_stanza direzione delle scale dell'ultima stanza del livello precedente (4=su,2=giu,1=sx,3,dx)
 \param livello indice del livello
 \param num_time_machine_part numero di pezzi della macchina del tempo da generare nel livello
*/
Livello(Giocatore* gamer,Livello* pre,int direction_pre_stanza,int livello,int num_time_machine_part);

/*!
 \fn getNLivello
 \brief ritorna l'indice del livello
*/
int getNLivello();//ritorna l'indice del livello
/*!
 \fn setLivello
 \brief modifica l'indice del livello
 \param livello nuovo livello
*/
void setLivello(int livello);//modifica l'indice del livello
/*!
 \fn getNumStanze
 \brief ritorna il numero delle stanze generati per il livello
*/
int getNumStanze();
};

#endif /*LIVELLO_HPP_INCLUDED*/
