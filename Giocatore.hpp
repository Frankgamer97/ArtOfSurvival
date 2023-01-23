/*!
\file Giocatore.hpp
\author Luca Tabanelli
*/

#ifndef GIOCATORE_HPP_INCLUDED
#define GIOCATORE_HPP_INCLUDED
#include "Personaggio.hpp"
using namespace std;

/*!
 \class Giocatore
 \brief Figlia di Persona definisce le specifiche aggiuntive del giocatore utente
*/
class Giocatore:public Personaggio{
public:
 /*!
  \var num_max_aiuti
  \brief costante che indica il numero massimo di aiutanti che si possono avere
 */
 static const int num_max_aiuti=5;//numero massimo di aiutanti
 /*!
  \var aiuti
  \brief vettore degli aiutanti
 */
 Personaggio* aiuti[num_max_aiuti];//vettore di puntatori ad aiutanti
 /*!
  \var num_aiuti
  \brief numero di aiutanti attualmente presenti nel vettore aiuti 
 */
 int num_aiuti;//numero corrente di aiutanti 

 /*!
  \fn Giocatore
  \brief Costruttore
  \param nome nome della persona
  \param tipo tipo della persona
  \param vita unità di vita della persona
  \param carattere carattere stampato a video della persona
 */
 Giocatore(char nome[],char tipo[],int vita,char carattere);
 /*!
  \fn addAiutante
  \brief aggiunge un nuovo aiutante nel vettore aiuti (=0 se ha aggiunto nuovo, !=0 altrimenti)
  \param nuovo nuovo aiutante da inserire
 */
 int addAiutante(Personaggio nuovo);//aggiunge un aiutante al vettore aiuti
 /*!
  \fn removeAiutante
  \brief rimuove aiutante aiuto dal vettore aiuti (true se ha eliminato aiuto, false altrimenti)
  \param aiuto aiutante da rimuovere
 */
 bool removeAiutante(Personaggio aiuto);//rimuove l'aiutante aiuto dal vettore aiuti
 /*!
  \fn replaceAiutante
  \brief sostituisce l'aiutante old con quello buovo nel vettore aiuti (true se ha sostituito, false altrimenti)
  \param old aiutante da sostituire
  \param nuovo nuovo aiutante
 */
 bool replaceAiutante(Personaggio old,Personaggio nuovo);//sostituisci nel vettore aiuti l'aiutante old con l'aiutante new
 /*!
  \fn getIndexAiutante
  \brief ritorna l'indice dl vettore riferito ad aiuto
  \param aiuto aiutante che si vuole conoscere il suo indice
 */
 int getIndexAiutante(Personaggio aiuto);//ritorna l'indice del vettore dov'è contenuto l'aiutante aiuto
  /*!
  \fn getNumAiutanti
  \brief ritorna il numero di aiutanti attualmente presenti nel vettore di aiuti
 */
 int getNumAiutanti();//ritorna il numero di aiutanti attualmente presenti

 /*!
  \fn comparePersona
  \brief confronta l'aiutante p con quello presente nella posizione i-esima del vettore di aiuti
  \param p aiutante da confrontare
  \param i indice del secondo aiutante da confrontare
 */
 bool comparePersona(Personaggio p,int i);//compara i campi della persona
};
#endif // GIOCATORE_HPP_INCLUDED


