/*!
  \file IA_Persona.hpp
  \author Francesco Palmisano
*/
#ifndef IA_Persona_HPP_INCLUDED
#define IA_Persona_HPP_INCLUDED
#include "Persona.hpp"

#ifndef TIME_MACHINE_STRUCT 
#define TIME_MACHINE_STRUCT
struct Time_Machine{
coordinate coo;
bool trovato;
};
#endif

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
 \class IA_Persona
 \brief Gestisce tutte le azioni che vengono considerate come azioni del turno di gioco
*/
class IA_Persona:public Persona{
public:
        /*!
        \fn IA_Persona
        \brief Costruttore
        \param nome[] nome della persona
        \param tipo[] tipo della persona
        \param carattere carattere della persona
        \param vita vita della persona
       */
	IA_Persona(char nome[50],char tipo[50],char carattere,int vita);
        /*!
        \fn write_object
        \brief stampa sulla matrice della stanza tutti gli oggetti raccoglibili
        \param stanza[][] matrice della stanza
        \param raccogliere vettore di oggetti che si possono raccogliere
        \param num_oggetti numero di oggetti che si possono raccogliere 
       */
	void write_object(char stanza[25][91],Oggetto_pos** raccogliere,int num_oggetti);
	//****************

	/*Ritorna lo stato dello scudo*/
        /*!
        \fn getScudo
        \brief Ritorna lo stato dello scudo
       */
	bool getScudo();
        /*!
        \fn setScudo
        \brief Modifica lo stato dello scudo
        \param scudo nuovo stato dello scudo
       */
        bool setScudo(bool scudo);
        /*!
        \fn passo
        \brief effettua l'avazamento sulla stanza della persona
        \param controller puntatore all'instanza di tipo Controller per l'insieme di tutti i comandi utente
        \param new_coordinate possibilita di avere le coordinate aggiornate [Opzionale]
        \param direction direzione in cui la persona deve andare definito dal controller
        \param stanza[][] matrice della stanza
       */
	bool passo(Controller* controller,coordinate* new_coordinate,char direction,char stanza[25][91]);

        /*!
        \fn raccogli
        \brief effettua l'avazamento sulla stanza della persona
        \param controller puntatore all'instanza di tipo Controller per l'insieme di tutti i comandi utente
        \param direction direzione in cui la persona deve andare definito dal controller
        \param stanza[][] matrice della stanza
        \param coo_stanza coordinate della stanza sullo schermo
        \param raccogliere oggetti raccoglibili della stanza
        \param num_oggetti numero di oggetti raccoglibili
       */
	bool raccogli(Controller* controller,char direction,char stanza[25][91],coordinate coo_stanza,Oggetto_pos** raccogliere,int num_oggetti,int* total_time_machine_part_catched,int local_time_machine_part,Time_Machine** time_machine_coo);
        /*!
        \fn spara
        \brief effettua l'avazamento sulla stanza della persona
        \param controller puntatore all'instanza di tipo Controller per l'insieme di tutti i comandi utente
        \param direction direzione in cui la persona deve andare definito dal controller
        \param stanza[][] matrice della stanza
        \param coo_stanza coordinate della stanza sullo schermo
        \param persone[] vettore di tutte le persone presenti nella stanza
        \param num_persone numero di persone presenti nella stanza
       */
	bool spara(Controller* controller,char direction,char stanza[25][91],coordinate coo_stanza,Persona* persone[],int num_persone);
        /*!
        \fn dialoga
        \brief effettua l'avazamento sulla stanza della persona
        \param giocatore puntatore al giocatore
        \param persone[] tutte le persone presenti nella (fatta eccezione per i nemici) con cui è possibile dialogare
        \param num_persone numero di persone presenti nella (fatta eccezione per i nemici) con cui è possibile dialogare
        \param controller puntatore all'instanza di tipo Controller per l'insieme di tutti i comandi utente
        \param direction direzione in cui la persona deve andare definito dal controller
        \param stanza[][] matrice della stanza
        \param diallogo_coo coordinate della messa a video del dialogo
        \param livello numero del livello durante il dialogo
       */
        void dialoga(Persona* giocatore,Persona* persone[],int num_persone,Controller* controller,char direction,char stanza[25][91],coordinate diallogo_coo,int livello);
};
#endif /*IA_Persona_HPP_INCLUDED*/


