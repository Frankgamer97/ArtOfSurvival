/*!
  \file Arma.hpp
  \author Francesco Palmisano
*/
#ifndef ARMA_HPP_INCLUDED
#define ARMA_HPP_INCLUDED
#include <unistd.h>
#include "Structure.hpp"
#include "DefaultArmi.hpp"

using namespace std;
/*!
  \class Arma
  \brief questa classe definisce le specifiche dell'arma dei personaggi
*/
class Arma{
private:
 //! \var Nome
 //! \brief nome dell'arma
 char Nome[25];
 //! \var proiettile
 //! \brief carattere del proiettile
 char proiettile;
 //! \var num_proiettili
 //! \brief numero di proiettili per sparo
 int num_proiettili;
 //! \var danni
 //! \brief quantità di danni (per proiettile)
 int danni;
 //! \var gittata
 //! \brief gittata del proiettile (numero di caratteri prima che il proiettile scompaia)
 int gittata;
 //! \var munizioni
 //! \brief numero di proiettili totali
 int munizioni;
 //! \var index
 //! \brief indentifica della picuture dell'arma
 int index;

public:
/*!
  \fn Arma
  \brief Costruttore
  \param Nome[] nome dell'arma
  \param proiettile carattere del proiettile
  \param num_proiettili numero di proiettili per sparo
  \param danni danni per singolo proiettile
  \param gittata gittata dell'arma
  \param munizioni numero di proiettili totali
  \param index indice della picture dell'arma
*/
 Arma(char Nome[],char proiettile,int num_proiettili,int danni,int gittata,int munizioni,int index);
/*!
  \fn setNome
  \brief Modifica il nome
  \param Nome[] nuovo nome dell'arma
*/
 void setNome(char Nome[]);
/*!
  \fn getNome
  \brief ritorna il nome
  \param Nome[] array dove salvare il nome
*/
 void getNome(char Nome[]);
/*!
  \fn setProiettile
  \brief Modifica il proiettile
*/
 void setProiettile(char proiettile);
/*!
  \fn getProiettile
  \brief ritorna il proiettile
*/
 char getProiettile();
/*!
  \fn setNumProiettili
  \brief modifica il numero dei proiettili per sparo
*/
 void setNumProiettili(int num_proiettili);
/*!
  \fn getNumProiettili
  \brief ritorna il numero di proiettili per sparo
*/
 int getNumProiettili();
/*!
  \fn setDanni
  \brief Modifica i danni del proiettile
  \param danni nuovi danni
*/
 void setDanni(int danni);
/*!
  \fn getDanni
  \brief Ritorna i danni del proiettile
*/
 int getDanni();
/*!
  \fn setGittata
  \brief Modifica la gittata
  \param gittata nuova gittata
*/
 void setGittata(int gittata);
/*!
  \fn getGittata
  \brief Ritorna la gittata
*/
 int getGittata();
/*!
  \fn setMunizioni
  \brief Modifica il numero di munizioni
  \param munizioni nuove munizioni
*/
 void setMunizioni(int munizioni);
/*!
  \fn getMunizioni
  \brief Ritorna le munizioni
*/
 int getMunizioni();
/*!
  \fn getIndex
  \brief Ritorna l'indice della picture dell'arma
*/
 int getIndex();
/*!
  \fn setIndex
  \brief Modifica l'indice della picture dell'arma
  \param index nuovo indice della picture dell'arma
*/
 void setIndex(int index);
};
#endif /* Arma_hpp_  */
