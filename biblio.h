#ifndef BIBLIO_H // compilation conditionnelle
#define BIBLIO_H

#include "livre.h"

#define CAPACITE_BIBLIO 400 // nb maximum de livres ds la bibliotheque

typedef T_livre T_tabloDeLivres[CAPACITE_BIBLIO];

typedef struct
{
	T_tabloDeLivres etagere;
	int nbLivres; // nb de livres actuellement ds la bibliotheque

} T_Bibliotheque;

// prototypes
void init(T_Bibliotheque *ptrB);
int ajouterLivre(T_Bibliotheque *ptrB);
int afficherBibliotheque(const T_Bibliotheque *ptrB);
int recherche(T_Bibliotheque *ptrB);
void informations(T_Bibliotheque *ptrB);
void supr(T_Bibliotheque *ptrB);
void emmprunt(T_Bibliotheque *ptrB);
void restituer(T_Bibliotheque *ptrB);
void tridutitre(T_Bibliotheque *ptrB);
void triauteur(T_Bibliotheque *ptrB);
void triannee(T_Bibliotheque *ptrB);
void listlivdisp (T_Bibliotheque *ptrB);
void listret (T_Bibliotheque *ptrB);
void tempsrest (T_Bibliotheque *ptrB);



void poubelle();
void sauvegarde(T_Bibliotheque *ptrB);
void chargement(T_Bibliotheque *ptrB);
void saisirEmp(T_Bibliotheque *ptrB);
void lireDateSysteme(T_Emp *E);

#endif
