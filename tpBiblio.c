// TP GESTION D'UNE BIBLIOTHEQUE
#include "biblio.h"

int menu()
{
	int choix;
	// au programme du TP7 :
	printf("\n\n\n//////////////////////////MENU///////////////////////////");
	printf("\n 1 - ajouter un nouveau livre dans la bibliotheque ");
	printf("\n 2 - afficher tous les livres de la bibliotheque ");
	printf("\n 3 - rechercher un livre (par son titre)"); // il peut y avoir plusieurs livres de même titre. Dans ce cas, indiquez le nombre d'exemplaires disponibles
	printf("\n 4 - rechercher et afficher tous les livres d'un auteur");
	printf("\n 5 - supprimer un livre de la bibliotheque");
	// si les 5 choix ci dessus sont bien codés, modifiez votre structure T_Livre et passez à 5 champs (avec cote,editeur et annee)
	printf("\n 6? - (MANUEL) Sauvegarder la bibliotheque"); ///////////////////////////////////////////////////////////////////////////////////////////MODIF
	printf("\n 7? - (MANUEL) Restaurer la bibliotheque");	///////////////////////////////////////////////////////////////////////////////////////////MODIF

	// au programme du TP8 :
	// ajouter le champ emprunteur à votre structure T_Livre

	printf("\n 8 - emprunter un livre de la bibliotheque");
	printf("\n 9 - restituer/rendre un livre de la bibliotheque");
	printf("\n 10 - trier les livres (par titre)");
	printf("\n 11 - trier les livres (par auteur)");
	printf("\n 12 - trier les livres (par annee)");

	// si les 5 choix (6-10) sont bien codés, changez le type T_Emp et remplacez-le par la structure T_Emp visible dans livre.h

	// vous pourrez alors faire les menus 11,12,etc...
	printf("\n 13 - lister les livres disponibles ");
	printf("\n 14 - lister les emprunts en retard "); // on suppose qu'un emprunt dure 7 jours.

	printf("\n 15 - Temps restant pour emprunt ");
	printf("\n 16 - Vider la bibliotheque ");

	//printf("\n 17 - ... imaginez vous même vos propres fonctionnalités ");

	printf("\n\n 0 - QUITTER");
	printf("\n\n Votre choix : ");

	scanf("%d[^\n]", &choix);
	getchar();
	printf("\n//////////////////FIN_DU_MENU///////////////////////////\n\n");
	return choix;
}

int main()
{
	printf("\nLa sauvegrarde et la restauration sont de base automatique \nmais vous pouveez le faire manuellement également dans le menu.\n\n");
	int reponse, chx;
	T_Bibliotheque B;
	init(&B);
	chargement(&B);
	do
	{
		chx = menu();
		switch (chx)
		{
		case 1:
			reponse = ajouterLivre(&B);
			if (reponse == 1)
				printf(" ajout reussi !!");
			else
				printf("impossible d ajouter (bibliotheque pleine)");
			sauvegarde(&B);
			break;
		case 2:
			reponse = afficherBibliotheque(&B);
			if (reponse == 0)
				printf("La bibliotheque est vide");

			break;
		case 3:
			reponse = recherche(&B);
			if (reponse == 0)
				printf("Ce livre n'est pas disponible");
			else
				printf("Il y a %d exemplaire(s) disponible(s)", reponse); //////////

			break;
		case 4:
			informations(&B);
			break;

		case 5:
			supr(&B);
			sauvegarde(&B);
			break;

		case 6:
			sauvegarde(&B); // placer avant der
			break;
		case 7:
			chargement(&B); // placer der
			break;

		case 8:
			saisirEmp(&B);
			sauvegarde(&B);
			break;

		case 9:
			restituer(&B);
			sauvegarde(&B);
			break;

		case 10:
			tridutitre(&B);
			sauvegarde(&B);
			break;

		case 11:
			triauteur(&B);
			sauvegarde(&B);
			break;

		case 12:
			triannee(&B);
			sauvegarde(&B);
			break;

		case 13:
			listlivdisp(&B);
			break;

		case 14:
			listret(&B);
			/* Pour tester veuillez emprunter un livre puis changer la date de votre PC en l'avançant de 7 jours puis faire 14 sur le menu */
			break;

		case 15:
			tempsrest(&B); // Calcul le nombre de jours restant pour livre si livre pas en retard mais emprunté
			break;

		case 16:
			poubelle(); // Vide nos donnés (pour debug)
			chargement(&B);
			break;
		}

	} while (chx != 0);

	return 0;
}
