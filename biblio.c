#include "biblio.h"

/*******************************************************************************************************/
////////////////////////////////////MANUEL
void sauvegarde(T_Bibliotheque *ptrB)
{
	FILE *fic = NULL; // le type FILE
	int i;
	fic = fopen("baseLivres", "w"); // w = le mode = write avec ECRASEMENT
	// fopen renvoie NULL si probleme (disque plein, disque non accessible ...
	if (fic != NULL)
	{
		for (i = 0; i < ptrB->nbLivres; i++)
		{
			// fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)
			fwrite(&(ptrB->etagere[i]), sizeof(T_livre), 1, fic);
		}
		fclose(fic);
		puts("\n\nSAUVEGARDE REUSSIE ..............");
	}
	else
		puts("\n\nECHEC DE SAUVEGARDE  !!!!!  ");
}

//////////////////////////////////MANUEL

void chargement(T_Bibliotheque *ptrB)
{
	FILE *fic = NULL; // le type FILE
	int i = 0;
	fic = fopen("baseLivres", "r"); // r = le mode read
	// fopen renvoie NULL si probleme (disque plein, disque non accessible ...
	if (fic != NULL)
	{
		do
		{

			fread(&(ptrB->etagere[i]), sizeof(T_livre), 1, fic);
			i++;
		} while (!feof(fic));
		fclose(fic);
		ptrB->nbLivres = i - 1;
		puts("\n\nCHARGEMENT  REUSSI ..............");
	}
	else
		puts("\n\nECHEC DE CHARGEMENT  !!!!!  ");
}
///////////////////////////////////

void init(T_Bibliotheque *ptrB)
{

	ptrB->nbLivres = 0;
	// ou (*ptrB).nbLivres=0;
}

int ajouterLivre(T_Bibliotheque *ptrB)
{
	if (ptrB->nbLivres < CAPACITE_BIBLIO) // reste t il de la place?
	{
		saisirLivre(&(ptrB->etagere[ptrB->nbLivres]));
		ptrB->nbLivres++;
		return 1;
	}

	return 0;
}

int afficherBibliotheque(const T_Bibliotheque *ptrB)
{
	int i;
	if (ptrB->nbLivres == 0)
		return 0;
	else
	{
		for (i = 0; i < ptrB->nbLivres; i++)
		{
			afficherLivre(&(ptrB->etagere[i]));
		}

		return 1;
	}
}

int recherche(T_Bibliotheque *ptrB)
{

	int a = 0;
	int b = 0;
	int c = 0;
	char tit[MAX_TITRE];

	lireChaine("\nQuel est le titre du livre que vous rechercher ?", tit, MAX_TITRE);

	do
	{
		b = strcmp(tit, (ptrB->etagere[a].titre));

		if (b == 0)
		{
			c = c + 1;
		}
		a++;

	} while (a < ptrB->nbLivres);

	return c;
}

void informations(T_Bibliotheque *ptrB)
{ //

	// int comp,i,flag=0;
	int a = 0;
	int b = 0;

	char aut[MAX_TITRE];																		//
	lireChaine("\nQuel est l'auteur dont vous voulez consulter les livres ? ", aut, MAX_TITRE); //

	do
	{
		b = strcmp(aut, (ptrB->etagere[a].auteur));

		if (b == 0)
		{
			printf("\n\n");
			printf("Livre n°%d :\n", a + 1);
			printf("Titre : %s \n", (ptrB->etagere[a].titre));
			printf("Code : %s \n", (ptrB->etagere[a].code));
			printf("Editeur : %s \n", (ptrB->etagere[a].editeur));
			printf("Annee : %d \n", (ptrB->etagere[a].annee));
		}

		a++;
	} while (a < ptrB->nbLivres);
}

void supr(T_Bibliotheque *ptrB)
{

	int a = 0;
	int b = 0;
	int c = 0;
	int d = 0;
	int e = 0;
	char tit[MAX_TITRE];

	lireChaine("\nQuel est le titre du livre que vous supprimer ? ", tit, MAX_TITRE);

	do
	{
		b = strcmp(tit, (ptrB->etagere[a].titre));

		if (b == 0)
		{
			c = c + 1;
			e = a;
		}
		a++;

	} while (a < ptrB->nbLivres);

	if (c != 0)
	{
		for (d = e; d < CAPACITE_BIBLIO - 1; d++)
		{
			strcpy((ptrB->etagere[d].code), (ptrB->etagere[d + 1].code));
			strcpy((ptrB->etagere[d].titre), (ptrB->etagere[d + 1].titre));
			strcpy((ptrB->etagere[d].auteur), (ptrB->etagere[d + 1].auteur));
			strcpy((ptrB->etagere[d].editeur), (ptrB->etagere[d + 1].editeur));
			(ptrB->etagere[d].annee) = (ptrB->etagere[d + 1].annee);
			// strcpy((ptrB->etagere[d].emprunteur.nomemprunteur),(ptrB->etagere[d+1].emprunteur.nomemprunteur));
		}
		printf("\n\"%s\" a bien été supprimé", tit);
		(ptrB->nbLivres) = (ptrB->nbLivres) - 1;
	}

	else
		printf("\nIl n'y a pas de livre se nommant \"%s\" a supprimer.", tit);
}

void lireDateSysteme(T_Emp *E)
{
	char j[9], m[10], h[9], mer[11]; //CHANGER TAILLE DE VIR OU VIRER VIR
	int d, a;
	printf("\nlecture\n");
	system("date > ladate");
	FILE *fic = NULL;			// pointeur de fichier
	fic = fopen("ladate", "r"); // fileOpen en mode 'r'EAD

	// ici , si fic vaut NULL, alors le fopen a indiquÃ©
	// que le fichier ladate n'est pas accessible
	if (fic != NULL)
	{
		while (!feof(fic))
		{
			fscanf(fic, "%s %d %s %d %s %s", j, &d, m, &a, h, mer);
			if (feof(fic))
				printf("\n-->LU : %s- %d- %s- %d- %s- %s", j, d, m, a, h, mer);
		}
		fclose(fic);

		if (strcmp(j, "lun.") == 0)
			E->lejour = lundi;
		if (strcmp(j, "mar.") == 0)
			E->lejour = mardi;
		if (strcmp(j, "mer.") == 0)
			E->lejour = mercredi;
		if (strcmp(j, "jeu.") == 0)
			E->lejour = jeudi;
		if (strcmp(j, "ven.") == 0)
			E->lejour = vendredi;
		if (strcmp(j, "sam.") == 0)
			E->lejour = samedi;
		if (strcmp(j, "dim.") == 0)
			E->lejour = dimanche;

		E->ledate = d;

		if (strcmp(m, "janvier") == 0)
			E->lemois = janvier;
		if (strcmp(m, "fevrier") == 0)
			E->lemois = fevrier;
		if (strcmp(m, "mars") == 0)
			E->lemois = mars;
		if (strcmp(m, "avril") == 0)
			E->lemois = avril;
		if (strcmp(m, "mai") == 0)
			E->lemois = mai;
		if (strcmp(m, "juin") == 0)
			E->lemois = juin;
		if (strcmp(m, "juillet") == 0)
			E->lemois = juillet;
		if (strcmp(m, "aout") == 0)
			E->lemois = aout;
		if (strcmp(m, "septembre") == 0)
			E->lemois = septembre;
		if (strcmp(m, "octobre") == 0)
			E->lemois = octobre;
		if (strcmp(m, "novembre") == 0)
			E->lemois = novembre;
		if (strcmp(m, "decembre") == 0)
			E->lemois = decembre;

		E->lannee = a;
	}
	else
	{
		printf("n souci avec la date systeme !!");

		// on range une date irrÃ©elle
		E->lejour = dimanche;
		E->ledate = 99;
		E->lemois = decembre;
		E->lannee = -999;
	}
}

void saisirEmp(T_Bibliotheque *ptrB)
{

	int a = 0;
	int b = 0;
	int c = 0;
	int e = 0;
	char tit[MAX_TITRE];

	lireChaine("\nQuel est le titre du livre que vous vous voulez emprunter ?", tit, MAX_TITRE);

	do
	{
		b = strcmp(tit, (ptrB->etagere[a].titre));

		if (b == 0)
		{
			c = c + 1;
			e = a;
		}
		a++;

	} while (a < ptrB->nbLivres);

	if (c == 0 || strcmp(ptrB->etagere[e].emprunteur.nomemprunteur, "") != 0)
	{
		printf("\nImpossible d'emprunter ce livre \" %s \"...\nIl n'est pas disponible dans notre bibliothèque ou est déjà emprunté...", tit);
	}
	else
	{
		printf("\nLivre que vous voulez emprunter : %s ", ptrB->etagere[e].titre);
		lireChaine("\nVotre nom : ", (ptrB->etagere[e].emprunteur.nomemprunteur), MAX);
		lireDateSysteme(&(ptrB->etagere[e].emprunteur));
	}
}

void restituer(T_Bibliotheque *ptrB)
{

	int a = 0;
	int b = 0;
	int c = 0;
	int e = 0;
	int f = 0;
	char tit[MAX_TITRE];
	char cde[K_MaxCode];
	char nom[K_MaxCode];

	lireChaine("\nQuel est le titre du livre que vous vous voulez restituer ?", tit, MAX_TITRE);
	lireChaine("\nQuel est le code du livre que vous vous voulez restituer ?", cde, K_MaxCode);

	do
	{
		b = strcmp(tit, (ptrB->etagere[a].titre));

		if (b == 0)
		{
			c = c + 1;
			e = a;
		}
		a++;

	} while (a < ptrB->nbLivres);

	a = 0;

	if (c != 0)
	{
		do
		{
			b = strcmp(cde, (ptrB->etagere[a].code));

			if (b == 0)
			{
				f = f + 1;
				e = a;
			}
			a++;

		} while (a < ptrB->nbLivres);
	}

	if (c == 0 || f == 0 || strcmp(ptrB->etagere[e].emprunteur.nomemprunteur, "") == 0)
	{

		printf("\nImpossible de restituer ce livre \" %s \"...\nNous n'avions pas ce modèle", tit);
	}
	else
	{
		printf("\nLivre que vous voulez restituer : %s ", ptrB->etagere[e].titre);
		lireChaine("\nNom de l'emprunteur : ", nom, MAX); // SECURITE
		if (strcmp(nom, ptrB->etagere[e].emprunteur.nomemprunteur) == 0)
		{
			strcpy((ptrB->etagere[e].emprunteur.nomemprunteur), "\0");
			(ptrB->etagere[e].emprunteur.lejour) = dimanche;
			(ptrB->etagere[e].emprunteur.ledate) = 99;
			(ptrB->etagere[e].emprunteur.lemois) = decembre;
			(ptrB->etagere[e].emprunteur.lannee) = -999;
			printf("\nMerci, livre rendu !");
		}
		else
			printf("Imposteur !, Ce n'est pas votre livre !\nVeuillez indiquez le nom de l'emprunteur la prochaine fois");
	}
}

void tridutitre(T_Bibliotheque *ptrB)
{
	int a = 0;
	int b = 0;
	T_livre tmp;
	for (a = 0; a < (ptrB->nbLivres); a++)
	{
		for (b = 0; b < (ptrB->nbLivres) - 1; b++)
		{
			if (strcmp((ptrB->etagere[b].titre), (ptrB->etagere[b + 1].titre)) > 0)
			{
				tmp = ptrB->etagere[b];
				ptrB->etagere[b] = ptrB->etagere[b + 1];
				ptrB->etagere[b + 1] = tmp;
			}
		}
	}
}

void triauteur(T_Bibliotheque *ptrB)
{
	int a = 0;
	int b = 0;
	T_livre tmp;
	for (a = 0; a < (ptrB->nbLivres); a++)
	{
		for (b = 0; b < (ptrB->nbLivres) - 1; b++)
		{
			if (strcmp((ptrB->etagere[b].auteur), (ptrB->etagere[b + 1].auteur)) > 0)
			{
				tmp = ptrB->etagere[b];
				ptrB->etagere[b] = ptrB->etagere[b + 1];
				ptrB->etagere[b + 1] = tmp;
			}
		}
	}
}

void triannee(T_Bibliotheque *ptrB)
{
	int a = 0;
	int b = 0;
	T_livre tmp;
	for (a = 0; a < (ptrB->nbLivres); a++)
	{
		for (b = 0; b < (ptrB->nbLivres) - 1; b++)
		{
			if ((ptrB->etagere[b].annee) > (ptrB->etagere[b + 1].annee))
			{
				tmp = ptrB->etagere[b];
				ptrB->etagere[b] = ptrB->etagere[b + 1];
				ptrB->etagere[b + 1] = tmp;
			}
		}
	}
}

void listlivdisp(T_Bibliotheque *ptrB)
{
	int a;

	printf("\n Liste des livres disponibles à l'emprunt et leurs codes :\n");

	for (a = 0; a < (ptrB->nbLivres); a++)
	{
		if (strcmp(ptrB->etagere[a].emprunteur.nomemprunteur, "\0") == 0)
			afficherLivre(&(ptrB->etagere[a]));
	}
}

void listret(T_Bibliotheque *ptrB)
{
	int datret, i, mn = 0; // datret = d+m+a + 7 (retard)

	char j[9], m[10], h[9], mer[11], vir[2];
	int d, a, datauj = 0;

	system("date > ladateretard");
	FILE *fic = NULL;				  // pointeur de fichier
	fic = fopen("ladateretard", "r"); // fileOpen en mode 'r'EAD

	// ici , si fic vaut NULL, alors le fopen a indiquÃ©
	// que le fichier ladate n'est pas accessible
	if (fic != NULL)
	{
		while (!feof(fic))
		{
			fscanf(fic, "%s %d %s %d %s %s %s", j, &d, m, &a, vir, h, mer);

			if (strcmp(m, "janvier") == 0)
				mn = 0;
			if (strcmp(m, "fevrier") == 0)
				mn = 1;
			if (strcmp(m, "mars") == 0)
				mn = 2;
			if (strcmp(m, "avril") == 0)
				mn = 3;
			if (strcmp(m, "mai") == 0)
				mn = 4;
			if (strcmp(m, "juin") == 0)
				mn = 5;
			if (strcmp(m, "juillet") == 0)
				mn = 6;
			if (strcmp(m, "aout") == 0)
				mn = 7;
			if (strcmp(m, "septembre") == 0)
				mn = 8;
			if (strcmp(m, "octobre") == 0)
				mn = 9;
			if (strcmp(m, "novembre") == 0)
				mn = 10;
			if (strcmp(m, "decembre") == 0)
				mn = 11;
		}
		fclose(fic);
	}

	for (i = 0; i < (ptrB->nbLivres); i++)
	{

		datret = (ptrB->etagere[i].emprunteur.ledate) + ptrB->etagere[i].emprunteur.lemois + ptrB->etagere[i].emprunteur.lannee + 7;
		datauj = d + mn + a;

		if (datauj > datret && strcmp(ptrB->etagere[i].emprunteur.nomemprunteur, "") != 0)
			printf("\n\n **Le livre %s ayant le code %s, emprunté par %s est en retard de %d jours !", ptrB->etagere[i].titre, ptrB->etagere[i].code, ptrB->etagere[i].emprunteur.nomemprunteur, (datauj - datret));
	}

	int drapo = 0;
	for (i = 0; i < (ptrB->nbLivres); i++)
	{
		datret = (ptrB->etagere[i].emprunteur.ledate) + ptrB->etagere[i].emprunteur.lemois + ptrB->etagere[i].emprunteur.lannee + 7;

		if (datauj < datret || strcmp(ptrB->etagere[i].emprunteur.nomemprunteur, "") == 0)
			drapo++;
	}

	if (drapo == ptrB->nbLivres)
		printf("\nAucun retard à signaler !");
}

void tempsrest(T_Bibliotheque *ptrB)
{
	int datret, i, mn = 0; // datret = d+m+a + 7 (retard)

	char j[9], m[10], h[9], mer[11], vir[2];
	int d, a, datauj = 0;

	system("date > ladateretard");
	FILE *fic = NULL;				  // pointeur de fichier
	fic = fopen("ladateretard", "r"); // fileOpen en mode 'r'EAD

	// ici , si fic vaut NULL, alors le fopen a indiquÃ©
	// que le fichier ladate n'est pas accessible
	if (fic != NULL)
	{
		while (!feof(fic))
		{
			fscanf(fic, "%s %d %s %d %s %s %s", j, &d, m, &a, vir, h, mer);

			if (strcmp(m, "janvier") == 0)
				mn = 0;
			if (strcmp(m, "fevrier") == 0)
				mn = 1;
			if (strcmp(m, "mars") == 0)
				mn = 2;
			if (strcmp(m, "avril") == 0)
				mn = 3;
			if (strcmp(m, "mai") == 0)
				mn = 4;
			if (strcmp(m, "juin") == 0)
				mn = 5;
			if (strcmp(m, "juillet") == 0)
				mn = 6;
			if (strcmp(m, "aout") == 0)
				mn = 7;
			if (strcmp(m, "septembre") == 0)
				mn = 8;
			if (strcmp(m, "octobre") == 0)
				mn = 9;
			if (strcmp(m, "novembre") == 0)
				mn = 10;
			if (strcmp(m, "decembre") == 0)
				mn = 11;
		}
		fclose(fic);
	}

	for (i = 0; i < (ptrB->nbLivres); i++)
	{

		datret = (ptrB->etagere[i].emprunteur.ledate) + ptrB->etagere[i].emprunteur.lemois + ptrB->etagere[i].emprunteur.lannee + 7;
		datauj = d + mn + a;

		if (datauj < datret && strcmp(ptrB->etagere[i].emprunteur.nomemprunteur, "") != 0)
			printf("\n\n **Le livre %s ayant le code %s, emprunté par %s doit rendu au plus tard dans %d jours !", ptrB->etagere[i].titre, ptrB->etagere[i].code, ptrB->etagere[i].emprunteur.nomemprunteur, (datret - datauj));
	}

	int drapo = 0;
	for (i = 0; i < (ptrB->nbLivres); i++)
	{
		if (strcmp(ptrB->etagere[i].emprunteur.nomemprunteur, "") == 0)
			drapo++;
	}

	if (drapo == ptrB->nbLivres)
		printf("\nAucun livre à rendre !");
}

void poubelle()
{
	FILE *fic = NULL; // le type FILE
	fic = fopen("baseLivres", "w"); // w = le mode = write avec ECRASEMENT
	// fopen renvoie NULL si probleme (disque plein, disque non accessible ...
	if (fic != NULL)
	{
		fclose(fic);
		puts("\n\nMISE A LA POUBELLE DES DONNEES REUSSIE ..............");
	}
	else
		puts("\n\nECHEC DE MISE A LA POUBELLE DES DONNEES  !!!!!  ");
}

