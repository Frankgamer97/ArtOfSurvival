/*! \file Animazioni.hpp
    \author Francesco Palmisano
*/
#ifndef Animazioni_HPP_INCLUDED
#define Animazioni_HPP_INCLUDED
#include "Livello.hpp"
#include "Structure.hpp"

/** @struct Arma_i
 *  @brief Questa struct definisce una lista bidirezionale di armi con la rispettiva picture
 */

struct Arma_i{
/*!
\var arma
\brief puntatore ad arma
*/
Arma* arma;
/*!
\var draw
\brief matrice della picture
*/
char draw[25][79];
/*!
\var next
\brief puntatore al nodo succesivo
*/
Arma_i* next;
/*!
\var pre
\brief puntatore al nodo precedente
*/
Arma_i* pre;
};
//! \typedef definisce il puntatore ad Arma_i
typedef Arma_i* Arma_icon;

/** @struct KIT_i
 *  @brief Questa struct definisce una lista bidirezionale di kit medici
 */
struct KIT_i{
/*!
\var kit
\brief kit medico
*/
KIT* kit;
/*!
\var pre
\brief puntatore al nodo precedente
*/
KIT_i* pre;
/*!
\var next
\brief puntatore al nodo succesivo
*/
KIT_i*next;
};
//! \typedef definisce il puntatore ad KIT_i
typedef KIT_i* KIT_icon;


/*! \class Animazioni
    \brief Gestisce le principali animazioni del gioco
    \details Questa classi gestisce tutte le principali animazioni del gioco, di cui:<br>
           -Gestione mappa del livello;<br>
           -Gestione comandi utente;<br>
           -Gestione lista di personaggi;<br>
           -Animazione per ascesa e discesa da ogni livello<br>
           -Animazione di visita dello zaino del giocatore<br>
           -Animazione di fine gioco (causa morte del giocatore e completamento della quest)

*/
class Animazioni{
private:
	/*!
           \fn ListaArma
           \brief crea la lista delle armi per lo scorrimento
           \param zaino zaino del giocatore
           \return lista delle armi
        */
	Arma_icon ListaArma(p_oggetto zaino[]);
	/*!
           \fn ListaKIT
           \brief crea la lista dei kit medici
           \param zaino zaino del giocatore
           \return lista dei kit medici
        */
	KIT_icon ListaKIT(p_oggetto zaino[]);
	/*!
           \fn stampaArma
           \brief stampa sullo schermo la picture dell'arma a partire dalle sue coordinate x e y
           \param x coordinata x della picture dell'arma
           \param y coordinata y della picture dell'arma 
           \param weapon_matrix[][79] matrice di carateeri per la picture dell'arma
        */
	void stampaArma(int x,int y,char weapon_matrix[][79]);
/*!
           \fn stampaKIT
           \brief stampa sullo schermo la picture del kit medico a partire dalle sue coordinate x e y
           \param x coordinata x della picture del kit medico
           \param y coordinata y della picture del kit medico
           \param draw[][79] matrice di caratteri per la picture dell'arma
        */
	void stampaKIT(int x,int y,char draw[][50]);
/*!
           \fn ScorriArma
           \brief scorre la lista delle armi seconda una direzione precisa passata come parametro
           \param node_current oggetto di struttura Arma_icon che rappresenta l'arma che si vuole scorrere
           \param x_max ascissa massima di scorrimento prima di caricare lo scorrimento della picture succesiva/precedente
           \param x ascissa di partenza della picture dell'arma
           \param y ordinata di partenza della picture dell'arma
           \param direction direzione dello scorrimento (4 verso sinistra, 6 verso destra)
           \param duration durata in millisecondi dello scorrimento 
           \return nodo di tipo Arma_icon precedente/succesivo al node_current
        */
	Arma_icon ScorriArma(Arma_icon node_current, int x_max,int x, int y, int direction,long duration);

/*!
           \fn ScorriKIT
           \brief scorre la lista deli kit medici seconda una direzione precisa passata come parametro
           \param node_current oggetto di struttura KIT_icon che rappresenta il kit medico che si vuole scorrere
           \param x_max ascissa massima di scorrimento prima di caricare lo scorrimento della picture succesiva/precedente
           \param x ascissa di partenza della picture del kit medico
           \param y ordinata di partenza della picture del kit medico
           \param direction direzione dello scorrimento (4 verso sinistra, 6 verso destra)
           \param duration durata in millisecondi dello scorrimento 
           \return nodo di tipo KIT_icon precedente/succesivo al node_current
        */
	KIT_icon ScorriKIT(KIT_icon node_current,char draw[][50], int x_max,int x, int y, int direction,long duration);

/*!
           \fn selectControl
           \brief Animazione per la gestione della modifica dei comandi utente
           \param controller puntatore all'istanza di tipo Controller che rappresenta un insieme dei principali comandi del gioco
           \return coordinate del cursore dopo la prima modifica
        */
	coordinate selectControl(Controller* controller);
/*!
           \fn dualController
           \brief controlla se un carattere che rapresenterebbe un comando non sia gia presente nell'insieme dei comandi
           \param controller puntatore all'istanza di tipo Controller che rappresenta un insieme dei principali comandi del gioco
           \param new_controller nuovo comando utente che si vuole modifcare
           \return true se il carattere del nuovo comanda esiste già nell'insieme dei comandi uetnte, false altrimenti
        */
	bool dualController(Controller* controller,char new_controller);
/*!
           \fn changeControl
           \brief gestisce dualController e selectControl per la modifica dei comandi utente
           \param controller puntatore all'istanza di tipo Controller che rappresenta un insieme dei principali comandi del gioco
        */
        void changeControl(Controller* controller);

/*!
           \fn disegnaStanza
           \brief [metodo ricorsivo] controlla se un carattere che rapresenterebbe un comando non sia gia presente nell'insieme dei comandi
           \param s puntatore all'instanza di tipo Stanza che raprrensenta la picture della stanza che si vuole stampare a video
           \param id_usati[] vettore di id_stanza che sono gia stati utilizzati per stampare le rispettive stanze
           \param num_stanze numero delle stanze che si vogliono rappresentare
           \param coo coordinate della stanza che si vuole rappresentare
           \param id_giocatore_stanza id_stanza della stanza in cui è situato il giocatore
           \param idLivello idLivello di tutte le stanze che si vogliono rappresentare per uno stesso Livello
        */
	void disegnaStanza(Stanza* s,int id_usati[],int num_stanze, coordinate coo,int id_giocatore_stanza,int idLivello);
public:
/*!
           \fn nextLevel
           \brief gestisce l'animazione per l'avanzamento di livello
        */
	void nextLevel();
/*!
           \fn preLevel
           \brief gestisce l'animazione per la discesa di livello
        */
	void preLevel();
/*!
           \fn LevelMap
           \brief gestisce la visione della mini-mappa del livello corrente
           \param controller puntatore all'instanza di tipo Controller per l'insieme di tutti i comandi utente
           \param first puntatore all'istanza di tipo stanza della prima stanza del livello corrente
           \param num_stanze numero delle stanze che si vogliono rappresentare
           \param id_stanza_giocatore id_stanza della stanza in cui è situato il giocatore
           \param idLivello idLivello di tutte le stanze che si vogliono rappresentare per uno stesso Livello
        */
	void LevelMap(Controller* controller,Stanza* first,int num_stanze,int id_stanza_giocatore,int idLivello);
/*!
           \fn PersoneDetail
           \brief mostra a video tutti i dettagli dei personaggi (giocatore,aiutanti e nemici) presenti nella stanza corrente
           \param persone[] vettore di tutte le persone che si vogliono descrivere
           \param num numero di persone che si vogliono descrivere
           \param id_stanza rappresenta l'identificatore della stanza
           \param id_livello idLivello di tutte le stanze che si vogliono rappresentare per uno stesso Livello
        */
	void PersoneDetail(Persona* persone[], int num,int id_stanza,int id_livello);
/*!
           \fn gameover
           \brief gestisce l'animazione del gameover (fine del gioco)
        */
	int gameover();
/*!
           \fn win
           \brief gestisce l'animazione della fine del gioco (causa superamento della quest)
        */
	void win();
/*!
           \fn mostraZaino
           \brief Gestisce l'animazione per la visita da parte dell'utente di tutti gli oggetti raccolti nel proprio zaino
           \param persona parametro che indica la persona di cui si vuole mostra lo zaino
        */
	void mostraZaino(Persona* persona);
/*!
           \fn gameMenu
           \brief Gestisce ele principali animazioni implementate in questa classe (visita della minimappa,zaino e gestione dei controlli utente)
           \param controller puntatore all'istanza di tipo Controller che rappresenta l'insieme di tutti i comandi utente
           \param s puntatore all'istanza di tipo Stanza per la visione della minimappa del livello 
           \param id_stanza_giocatore id_stanza della stanza in cui è situato il giocatore
           \param livello idLivello di tutte le stanze che si vogliono rappresentare per uno stesso Livello
           \param num_stanze numero delle stanze che si vogliono rappresentare
           \param persone parametro che indica le persone di cui si vogliono descrivere
           \param num_persone numero di persone che si vogliono descrivere   
        */
	void gameMenu(Controller* controller,Stanza* s,int id_stanza_giocatore,int livello,int num_stanze,Persona* persone[],int num_persone);
};

#endif /*Animazioni_HPP_INCLUDED*/
