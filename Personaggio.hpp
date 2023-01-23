/*!
\file Personaggio.hpp
\author Luca Tabanelli
*/
#ifndef PERSONAGGIO_HPP_INCLUDED
#define PERSONAGGIO_HPP_INCLUDED
#include "IA_Persona.hpp"

#ifndef TIME_MACHINE_STRUCT 
#define TIME_MACHINE_STRUCT
/** @struct Time_Machine
 *  @brief Questa struct definisce la posizione di uno dei pezzi della macchina del tempo ed indica se è stato trovato o meno
 */
struct Time_Machine{
/*!
  \var coo
  \brief coordinate del pezzo della macchina del tempo
*/
coordinate coo;
/*!
  \var trovato
  \brief flag che indica se il pezzo è stato trovato o meno
*/
bool trovato;
};
#endif

/*!
 \class Personaggio
 \brief Filgia di IA_Persona, definisce un metodo per la gestione automatica di aiutanti e nemici
*/
class Personaggio:public IA_Persona{
public:
        /*! \fn Personaggio
            \brief Costruttore 
            \param Nome nome della persona
            \param Tipo tipo della persona
            \param carattere carattere stampato a video della persona 
            \param vita unità di vita della persona
        */
	Personaggio(char Nome[50],char Tipo[50],char carattere,int vita);
        /*!
          \fn AutoAction
          \brief permette la gestione automatica del personaggio in questione
          \param controller struttura dati che rappresenta l'insieme dei comandi utente
          \param stanza matrice della stanza in cui è presente il giocatore
          \param coo_stanza coordinate della stanza in questione sullo schermo
          \param personaggi vettore di tutte le persone (giocatore, aiutanti e nemici) nella stanza in questione
          \param num_personaggi lunghezza del vettore personaggi
          \param oggetti vettore di tutti gli oggetti raccoglibili nella stanza in questione
          \param num_oggetti lunghezza del vettore oggetti
          \param total_time_machine_part_catched numero di pezzi della macchina del tempo attualmente raccolti
          \param local_time_machine_part numero di pezzi della macchina del tempo presenti nella stanza corrente
          \param time_machine_coo vettore di Time_Machine
        */
	void AutoAction(Controller* controller,char stanza[25][91],coordinate coo_stanza,Persona* personaggi[],int num_personaggi,Oggetto_pos** oggetti,int num_oggetti,int* total_time_machine_part_catched,int local_time_machine_part,Time_Machine** time_machine_coo);
};

#endif /*PERSONAGGIO_HPP_INCLUDED*/
