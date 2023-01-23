/*!
\file DefaultArmi.hpp
\author Francesco Palmisano
*/
#ifndef DEFAULTARMI_HPP_INCLUDED
#define DEFAULTARMI_HPP_INCLUDED
//! \var PROIETTILE
//! \brief carattere comune per tuti i proiettili delle armi
char PROIETTILE='-';

//! \var GLOCK45
//! \brief nome dell'arma
char GLOCK45[]="glock-45";
#define GLOCK45_MUNIZIONI 40
#define GLOCK45_MUNIZIONI_PER_SPARO 1
#define GLOCK45_DANNI 15
#define GLOCK45_GITTATA 10
#define GLOCK45_ID 1

//! \var MAGNUM44
//! \brief nome dell'arma
char MAGNUM44[]="44-magnum";
#define MAGNUM44_MUNIZIONI 30
#define MAGNUM44_MUNIZIONI_PER_SPARO 1
#define MAGNUM44_DANNI 10
#define MAGNUM44_GITTATA 15
#define MAGNUM44_ID 2

//! \var MACHINEGUN
//! \brief nome dell'arma
char MACHINEGUN[]="machine-gun";
#define MACHINEGUN_MUNIZIONI 100
#define MACHINEGUN_MUNIZIONI_PER_SPARO 20
#define MACHINEGUN_DANNI 5
#define MACHINEGUN_GITTATA 20
#define MACHINEGUN_ID 3

//! \var AK_47
//! \brief nome dell'arma
char AK_47[]="ak-47";
#define AK_47_MUNIZIONI 60
#define AK_47_MUNIZIONI_PER_SPARO 5
#define AK_47_DANNI 10
#define AK_47_GITTATA 23
#define AK_47_ID 4

//! \var WARFARE_SNIPER
//! \brief nome dell'arma
char WARFARE_SNIPER[]="warfare sniper";
#define WARFARE_SNIPER_MUNIZIONI 30
#define WARFARE_SNIPER_MUNIZIONI_PER_SPARO 1
#define WARFARE_SNIPER_DANNI 30
#define WARFARE_SNIPER_GITTATA 23
#define WARFARE_SNIPER_ID 5

#endif /*DEFAULTARMI_HPP_INCLUDED*/
