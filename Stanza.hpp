/*!
   \file Stanza.hpp
   \author Nicola Serra
*/

#ifndef Stanza_hpp
#define Stanza_hpp
#include <iostream>
#include "Giocatore.hpp"
#include "Structure.hpp"
#include "DefaultArmi.hpp"

/** colonne massimo per stanza*/ 
#define STANZA_X 91
/** righe massime per stanza.*/ 
#define STANZA_Y 25

/**Definizione della struttura Oggetto_pos.*/ 
#ifndef OGGETTO_POS
#define OGGETTO_POS

/** @struct Oggetto_pos
 *  @brief Questa struct permette l'associazione Oggetto-coordinate
 */

struct Oggetto_pos{
/*!
  \var oggetto
  \brief oggetto raccoglibile
*/
Oggetto oggetto;
/*!
 \var coo
 \brief coordinate
*/
coordinate coo;
};
#endif
/*!
  \class Stanza
  \brief defisce le specifiche della stanza di ogni livello di gioco
*/
class Stanza {
private:
    /*!
     \var idStanza
     \brief indice nella stanza riferita ad uno specifico livello di gioco
    */
    int idStanza;
    /*!
     \var idLivello
     \brief indice del livello di gioco 
    */
    int idLivello;
    /*!
     \fn creaAiutante
     \brief crea il vettore di aiutanti secondo il giocatore passato come parametro
     \param giocatore indica il giocatore per cui creare i nuovi aiutanti
    */
    void creaAiutante(Giocatore* giocatore);
public:
    /*!
      \var stanza
      \brief matrice di caratteri della stanza corrente
    */
    char stanza[STANZA_Y][STANZA_X];
    /*!
      \var top
      \brief puntatore alla stanza sopra quella corrente
    */
    Stanza* top;
    /*!
      \var bottom
      \brief puntatore alla stanza sotto quella corrente
    */
    Stanza* bottom;
    /*!
      \var right
      \brief puntatore alla stanza destra rispetto quella corrente
    */
    Stanza* right;
    /*!
      \var left
      \brief puntatore alla stanza sinistra rispetto a quella corrente
    */
    Stanza* left;
    /*!
      \var n_oggetti
      \brief numero di oggetti raccoglibili nella stanza
    */
    int n_oggetti;
    /*!
      \var oggetti
      \brief oggetti raccoglibili nella stanza
    */
    Oggetto_pos** oggetti;
    /*!
      \var num_nemici
      \brief numero di nemici attualmente generati
    */
    int num_nemici;
    /*!
      \var num_max_nemici
      \brief numero massimo di nemici generabili per la stanza
    */
    static const int num_max_nemici=10;
    /*!
      \var nemici
      \brief vettore di nemici presenti (e assenti) della stanza
    */
    Personaggio* nemici[num_max_nemici]; 
    
    /*!
      \fn setIndexStanza
      \brief modifica l'indice della stanza
      \param newIndex nuovo indice della stanza
    */
    void setIndexStanza(int newIndex);
    /*!
      \fn getIndexStanza
      \brief Ritorna l'indice della stanza
    */
    int getIndexStanza();
    
    /*!
      \fn setIndexLivello
      \brief modifica l'indice del livello
      \param newIndex nuovo indice del livello della stanza
    */
    void setIndexLivello(int newIndex);
    /*!
      \fn getIndexLivello
      \brief Ritorna l'indice dellivello
    */
    int getIndexLivello();
    
    /*!
      \fn aggiornaAiutanti
      \brief modifica (quando possibile) il numero di aiutanti per il giocatore [chiamato quando si cambia stanza]
      \param giocatore Indica il giocatore a cui aggiornare i propri aiutanti
    */
    void aggiornaAiutanti(Giocatore* giocatore);

    /*!
      \fn Stanza
      \brief Costruttore
      \param giocatore Indica il giocatore (umano) presente nella stanza
      \param idLivello Indice del livello della stanza
      \param idStanza Indice della stanza per uno specifico livello
    */
    Stanza(Giocatore* giocatore,int idLivello,int idStanza,int id_matrix_used[],int num_id);
};
#endif /* Stanza_hpp */
