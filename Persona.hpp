/*!
 \file Persona.hpp
 \author Luca Tabanelli
*/

#ifndef PERSONA_HPP_INCLUDED
#define PERSONA_HPP_INCLUDED
#define OGGETTO_INCLUDED
#include "Arma.hpp"

/** @struct Time_Machine
 *  @brief Questa struct definisce un oggetto raccoglibile (kit medico o arma). Può essere definito solo uno dei due puntatori
 */

struct Oggetto{
/*!
  \var kit 
  \brief puntatore al kit medico
*/
KIT *kit;
/*!
  \var arma
  \brief puntatore all'arma
*/
Arma *arma;
};
typedef Oggetto* p_oggetto;

/*!
 \class Persona
 \brief definisce le caratterische di una persona (che è la classe padre radice di tutte le sue derivate)
*/
class Persona{
protected:
  /*!
    \var nome
    \brief nome della persona
  */
  char nome[50];
  /*!
    \var tipo
    \brief tipo della persona (Eroe,Aiutante,Nemico)
  */
  char tipo[50];//tipo di personaggio
  /*!
    \var vita
    \brief unita di vita della persona
  */
  int vita;//punti vita
  /*!
    \var carattere
    \brief carattere della personache viene stampato a video
  */
  char carattere;//carattere del personaggio
  /*!
    \var scudo
    \brief flag che indica se lo scudo della persona è atttivo o meno
  */
  bool scudo;//scudo attivo/disattivo

private:
  /*!
    \var arma_corrente
    \brief puntatore all'arma che la persona attualmente utilizza
  */
Arma* arma_corrente;
  /*!
    \var zaino
    \brief vettore di oggetti raccolti dalla persona
  */
p_oggetto zaino[50]; //array di puntatori ad oggetti
  /*!
    \var coo
    \brief coordinate sulla stanza della persona
  */
coordinate coo;
public:
/*!
  \fn Persona
  \brief Costruttore
  \param nome nome della persona
  \param tipo tipo della persona
  \param vita unità di vita della persona
  \param carattere carattere stampato a video della persona
*/
  Persona(char nome[50],char tipo[50],int vita,char carattere);
  /*!
  \fn getNome
  \brief ritorna il nome della persona
  \param nome vettore che conterrà il nome
*/
  void getNome(char nome[]);
  /*!
  \fn getTipo
  \brief ritorna il tipo della persona
  \param tipo vettore che conterrà il tipo
*/
  void getTipo(char tipo[]);
  /*!
  \fn getCarattere
  \brief ritorna il carattere della persona
*/
  char getCarattere();
  /*!
  \fn setCarattere
  \brief Modifica il carattere della persona
  \param carattere nuovo carattere dell apersona
*/
  void setCarattere(char carattere);//modifica il carattere del personaggio
  /*!
  \fn getScudo
  \brief ritorna lo stato dello scudo
*/
  bool getScudo();//ritorna lo stato dello scudo
  /*!
  \fn setScudo
  \brief Modifica lo stato dello scudo
  \param scudo nuovo stato dello scudo
*/
  void setScudo(bool scudo);//modifica lo stato dello scudo 
  /*!
  \fn addVita
  \brief Aggiunge unità di vita al persona
  \param vita quantità da aggiungere
*/
  void addVita(int vita);//incrementa la vita (si tratta solo di un semplice assegnamento);
  /*!
  \fn subVita
  \brief Toglie unità di vita al persona
  \param vita quantità da togliere
*/
  void subVita(int vita);//decrementa vita (si tratta solo di un semplice assegnamento);
  /*!
  \fn getVita
  \brief Ritorna le unità di vita della persona
*/
  int getVita();//restituisce la vita
  /*!
  \fn getArma
  \brief ritona il puntatore all'arma corrente della persona
*/
  Arma* getArma();//ritorna l'arma corrente della persona
  /*!
  \fn setArma
  \brief Modifica l'arma corrente del personaggio
  \param arma_corrente puntatore all'nuova arma corrente
*/
  void setArma(Arma* arma_corrente);//modifica l'arma corrente della persona
  /*!
  \fn addOggetto
  \brief Aggiunge un'oggetto allo zaino
  \param o nuovo oggetto da aggiungere. Ritorna true se ha aggiunto o, false altrimenti
*/
  bool addOggetto(Oggetto o);// aggiunge oggetto allo zaino;
  /*!
  \fn compareOggetto
  \brief Confronta l'oggetto o con quello presente alla posizione i-esima dello zaino
  \param o oggetto da confrontare
  \param i indice del confronto
*/
  bool compareOggetto(Oggetto o,int i);// compara un oggetto passatogli come parametro con una posizione nello zaino
  /*!
  \fn removeOggetto
  \brief Rivuove (se è possibile) l'oggetto o dallo zaino
  \param o oggetto da rimuovere
*/
  void removeOggetto(Oggetto o);//toglie l'oggetto dallo zaino (l'oggetto passato come paramentro é proprio l'oggetto da togliere)
                                //lo devi trovare nell'array ed eliminarlo
  /*!
  \fn getIndexOggetto
  \brief ritorna l'indice del vettore a cui corrisponde l'oggetto o (<0 altrimenti)
  \param o oggetto per cui si vuole conoscere l'indice
*/
  int getIndexOggetto(Oggetto o);//ritorna l'indice del vettore che indica la posizione dell'oggetto o
  /*!
  \fn getZaino
  \brief ritorna l'intero zaino della persona
  \param newZaino vettore dello zaino ritornato per indirizzo
*/
  void getZaino(p_oggetto newZaino[50]);//copia lo zaino in un altro zaino;
  /*!
  \fn setCoordinate
  \brief modifca le coordinate della persona riferite alla stanza
  \param coo nuove coordinate della persona
*/
  void setCoordinate(coordinate coo);//aggiorna le coordinate del personaggio;
  /*!
  \fn getCoordinate
  \brief Ritorna le coordinate della persona riferite alla stanza
*/
  coordinate getCoordinate();//ritorna le coordinate della persona
};

#endif /*PERSONA_HPP_INCLUDED*/
