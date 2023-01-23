/*!
\file Game.hpp
\author Francesco Palmisano
*/

#ifndef Game_HPP_INCLUDED
#define Game_HPP_INCLUDED
#include "Animazioni.hpp"


#ifndef TURNO_STRUCTURE
#define TURNO_STRUCTURE
/** @struct Turno
 *  @brief Questa struct definisce un'oggetto turno essenziale per la gestione a turni del gioco
 */
struct Turno{
//! \var persona
//! \brief persona
Personaggio* persona;
//! \var turno
//! \brief flag se =true è il turno di persona e false altrimenti
bool turno;
};
#endif

#ifndef TIME_MACHINE_STRUCT 
#define TIME_MACHINE_STRUCT
/** @struct Time_Machine
 *  @brief Questa struct definisce le specifiche del carattere della macchina del tempo
 */
struct Time_Machine{
//! \var coo
//! \brief coordinate di #
coordinate coo;
//! \var trovato
//! \brief se =true # è stato trovato e false altrimenti
bool trovato;
};
#endif
/*!
 \class Game
 \brief Classe che gestisce tutte le altre, gestisce i turni di gioco e le principali operazioni di esso
*/
class Game{
private:
/*!
 \var stanza_coo
 \brief coordinate sullo schermo della stanza corrente
*/
	coordinate stanza_coo;//indica le coordinate sullo schermo da cui la stanza corrente del gioco verrà stampata
	//la creazione dei nemici deve essere fatta singolarmente nelle stanze
/*!
 \var livello_corrente
 \brief puntatore al livello corrente del gioco
*/
        Livello* livello_corrente;
/*!
 \var stanza
 \brief puntatore alla stanza corrente del gioco
*/
        Stanza* stanza;//indica la stanza corrente
/*!
 \var pre_stanza
 \brief puntatore alla stanza precedente a quella corrente
*/
        Stanza* pre_stanza;//stanza precedentemente esplorata
/*!
 \var gamer
 \brief puntatore al giocatore (gestito dall'utente)
*/
	Giocatore* gamer;
/*!
 \var turni
 \brief vettore di turni per stabilire nel gioco in ogni istante di chi sia il turno di agire
*/
        Turno** turni;
/*!
 \var total_time_machine_part
 \brief costante statica che indica il numero totale dei pezzi della macchina del tempo da raccogliere
*/
        static const int total_time_machine_part=10;
/*!
 \var total_time_machine_part_catched
 \brief indica il numero totale dei pezzi della macchina del tempo da raccolti
*/
        int total_time_machine_part_catched;
/*!
 \var time_machine_part_coo
 \brief vettore per le indicazioni della posizione di ogni #
*/
        Time_Machine** time_machine_part_coo;//vettore che per le coordinate dei pezzi delle macchine del tempo (per la stanza corrente)
/*!
 \var num_time_machine_part
 \brief lunghezza del vettore delle coordinate  per la stanza corrente
*/
        int num_time_machine_part;//lunghezza del vettore delle coordinate del vettori dei pezzi della macchina del tempo per la stanza corrente
/*!
 \var stanza_cleaned
 \brief buffer per la stanza
*/
        char stanza_cleaned[25][91];
        //static const char oggetto_finale='#';
        
	//comandi (che si possono essere modificate dall utente a piacimento) da fare tutte le set ed i get
/*!
 \var controller
 \brief oggetto che definisce l'insieme dei comandi utente
*/
	Controller* controller;//struct per i comandi d'interazione
/*!
 \var animazioni
 \brief puntatore all'oggetto che utilizza tutte le animazioni del gioco
*/
	Animazioni* animazioni;
/*!
 \fn aggiorna_time_machine_part_coo
 \brief aggiorna il vettore degli oggetti #
*/
	void aggiorna_time_machine_part_coo();
public:
/*!
 \fn Game
 \brief Costruttore che instanzia il primo livello è i comandi default
*/
	Game(Giocatore* gamer);
/*!
 \fn getController
 \brief ritorna il puntatore all'oggetto dei controlli utente
*/
	Controller* getController();
/*!
 \fn getAnimazioni
 \brief ritorna il puntatore all'oggetto delle animazioni
*/
	Animazioni* getAnimazioni();
	//gestione movimento personaggi
	//void draw_room();
/*!
 \fn draw_details
 \brief ricarica il frame dello schermo
*/
	void draw_details();
/*!
 \fn aggiorna_turni
 \brief aggiorna i turni di gioco in caso di cambio di stanza
*/
	void aggiorna_turni();
/*!
 \fn start
 \brief metodo che lancia effettivamente il gioco
*/        
	void start();
	//gestione nemici*********************************************************************************

};

#endif /*Game_HPP_INCLUDED*/
