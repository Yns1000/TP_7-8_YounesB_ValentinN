#include "livre.h"

void saisirLivre(T_livre *ptrL)
{

    char year[MAX];
    char test[MAX] = "ok";

    lireChaine("TITRE :", (ptrL->titre), MAX_TITRE);
    lireChaine("AUTEUR :", (ptrL->auteur), MAX);
    lireChaine("CODE :", (ptrL->code), MAX_CODE);
    lireChaine("EDITEUR :", (ptrL->editeur), MAX);
    lireChaine("ANNEE :", year, MAX);
    ptrL->annee = atoi(year);
    do
    {
        if (ptrL->annee == 0)
        {
            printf("\n Vous avez peut-être inseré une année incorrecte !!!\n Si vous voulez utiliser l'an \"0\", entrez \"ok\"");
            lireChaine("\n\nANNEE :", year, MAX);
            ptrL->annee = atoi(year);
        }
    } while (ptrL->annee == 0 && strcmp(year, test) != 0);
    strcpy((ptrL->emprunteur.nomemprunteur), "\0");
    (ptrL->emprunteur.lejour) = dimanche;
    (ptrL->emprunteur.ledate) = 99;
    (ptrL->emprunteur.lemois) = decembre;
    (ptrL->emprunteur.lannee) = -999;
}

//////////////////////

void afficherLivre(const T_livre *ptrL)
{
    char jour[13], mois[13];

    printf("\n\n************************************************************");
    afficherChaine("\nTITRE :", (ptrL->titre));
    printf(" - ");
    afficherChaine("AUTEUR :", (ptrL->auteur));
    printf(" - ");
    afficherChaine("CODE :", (ptrL->code));
    printf(" - ");
    afficherChaine("EDITEUR :", (ptrL->editeur));
    printf(" - ");
    afficherint("ANNEE :", (ptrL->annee)); //BIZARE APRES 2022 NON ?
    printf("\n");

    if (strcmp(ptrL->emprunteur.nomemprunteur, "") == 0)
    {
        printf("\n**Ce livre est libre, vous pouvez l'emprunter !");
    }
    else
    {
        printf("\n **Emprunteur du livre : %s", ptrL->emprunteur.nomemprunteur);
        printf("\n **Emprunt realise le : ");
        switch (ptrL->emprunteur.lejour)
        {
        case 0:
            strcpy(jour, "lundi");
            break;
        case 1:
            strcpy(jour, "mardi");
            break;
        case 2:
            strcpy(jour, "mercredi");
            break;
        case 3:
            strcpy(jour, "jeudi");
            break;
        case 4:
            strcpy(jour, "vendredi");
            break;
        case 5:
            strcpy(jour, "samedi");
            break;
        case 6:
            strcpy(jour, "dimanche");
            break;

        default:
            strcpy(jour, "jour inconnu");
            break;
        }
        printf("%s ", jour);

        printf("%d ", ptrL->emprunteur.ledate);

        switch (ptrL->emprunteur.lemois)
        {
        case 0:
            strcpy(mois, "janvier");
            break;
        case 1:
            strcpy(mois, "fevrier");
            break;
        case 2:
            strcpy(mois, "mars");
            break;
        case 3:
            strcpy(mois, "avril");
            break;
        case 4:
            strcpy(mois, "mai");
            break;
        case 5:
            strcpy(mois, "juin");
            break;
        case 6:
            strcpy(mois, "juillet");
            break;
        case 7:
            strcpy(mois, "aout");
            break;
        case 8:
            strcpy(mois, "septembre");
            break;
        case 9:
            strcpy(mois, "octobre");
            break;
        case 10:
            strcpy(mois, "novembre");
            break;
        case 11:
            strcpy(mois, "decembre");
            break;

        default:
            strcpy(jour, "mois inconnu");
            break;
        }
        printf("%s ", mois);

        printf("%d ", ptrL->emprunteur.lannee);
    }
}
