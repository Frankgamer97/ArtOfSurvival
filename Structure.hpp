#ifndef Structure_hpp_
#define Structure_hpp_

/** @struct coordinate
 *  @brief Questa struct definisce le coordinate riferite localmente all stanza
 */

struct coordinate{
//! \var x
//! \brief ascissa
//! \var y
//! \brief ordinata
int x;
int y;
};

/** @struct collisione
 *  @brief Questa struct definisce una collisione tra un'entità ed un proiettile
 */

struct collisione{
/*!
\var coo
\brief coordinate dell'entita collisa
*/
coordinate coo;
/*!
\var chi
\brief carattere dell'entita collisa
*/
char chi;
/*!
\var volte
\brief quante volta l'entità è stata colpita
*/
int volte;
/*!
\var danni
\brief Unità di vita perse per l'entità
*/
int danno;
};

/** @struct KIT
 *  @brief Questa struct definisce le caratteristiche di un kit medico
 */
struct KIT{
/*!
\var vita
\brief unita di vite ripristinabili
*/
int vita;
/*!
\var quantita
\brief scorte kit
*/
int quantita;
};

/** @struct restore_ch
 *  @brief Questa struct definisce i caratteri da ripristinare
 */
struct restore_ch{
/*!
\var ch
\brief carattere da ripristinare
*/
char ch;
/*!
\var coo
\brief coordinate del carattere da ripristinare
*/
coordinate coo;
};

/** @struct controller
 *  @brief Questa struct definisce i comandi che l'untente può impartire al gioco
 */
struct Controller{
//comandi (che si possono essere modificate dall utente a piacimento) da fare tutte le set ed i get
//movimento personaggio	

/*!
\var up
\brief passo in avanti
*/
char up;
/*!
\var down
\brief passo all'indietro
*/
char down;
/*!
\var sx
\brief passo verso sinistra
*/
char sx;
/*!
\var dx
\brief passo verso destra
*/
char dx;

//comandi d'interazione
/*!
\var porta
\brief comando attivazione porta
*/
char porta;//apri e/o chiudi porta
/*!
\var zaino
\brief comando apertura zaino
*/
char zaino;//apri zaino
/*!
\var sparo
\brief comando sparo
*/
char sparo;//spara ed attacca
/*!
\var dialoga
\brief comando per dialogare
*/
char dialoga;//dialoga
/*!
\var raccogli
\brief comando per raccogliere
*/
char raccogli;//raccogli oggetto
/*!
\var menu
\brief comando per aprire il menu
*/
char menu;//apri menu del gioco

char scudo;
};


#endif /*Structure_hpp_*/
