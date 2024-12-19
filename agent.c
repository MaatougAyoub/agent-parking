#include "agent.h"
#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>

void verif_CIN(agent *G)
{
    do
    {
        printf("\nEntrer CIN (8 digits): ");
        scanf("%d", &G->CIN);
    } while (G->CIN < 10000000 || G->CIN > 99999999);
}

void verif_numTEL(agent *G)
{
    do
    {
        printf("\nEntrer Telephone Number (8 digits): ");
        scanf("%d", &G->numTEL);
    } while (G->numTEL < 10000000 || G->numTEL > 99999999);
}

int verif_sexe(agent *G)
{
    do
    {
        printf("\nEntrer le sexe de l'agent (1: Homme / 0: Femme): ");
        scanf("%d", &G->sexe);
    } while (G->sexe != 0 && G->sexe != 1);
    return G->sexe;
}

int verif_horraires(agent *G)
{
    do
    {
        printf("\nEnter es horraires de travail (0: 00h-8h / 1: 8h-16h / 2: 16h-00h): ");
        scanf("%d", &G->horraires_de_travail);
    } while (G->horraires_de_travail < 0 || G->horraires_de_travail > 2);
    return G->horraires_de_travail;
}

int verif_poste(agent *G)
{
    do
    {
        printf("\nEnter position de travail (0, 1, 2, or 3): ");
        scanf("%d", &G->poste_de_travail);
    } while (G->poste_de_travail < 0 || G->poste_de_travail > 3);
    return G->poste_de_travail;
}

void saisir_agent(agent *G)
{
    printf("\nEntrer le nom de l'agent: ");
    scanf("%s", G->nom);
    printf("\nEntrer le prenom de l'agent: ");
    scanf("%s", G->prenom);
    verif_CIN(G);

    printf("\nEntrer la date de naissance de l'agent (day month year): ");
    scanf("%d %d %d", &G->date_naissance.jour, &G->date_naissance.mois, &G->date_naissance.annee);

    verif_sexe(G);

    printf("\nEntrer la ville de l'agent: ");
    scanf("%s", G->ville);

    verif_numTEL(G);

    printf("\nEntrer Email de l'agent: ");
    scanf("%s", G->email);

    printf("\nEntrer la date de recrutement de l'agent (day month year): ");
    scanf("%d %d %d", &G->date_recrutement.jour, &G->date_recrutement.mois, &G->date_recrutement.annee);

    verif_horraires(G);
    verif_poste(G);
}


int ajouter_agent(char *file_agent, agent G)
{
    FILE *f = fopen(file_agent, "a");
    if (f != NULL)
    {
        fprintf(f, "%s %s %d %02d/%02d/%04d %s %d %s %02d/%02d/%04d ",
                G.nom, G.prenom, G.CIN,
                G.date_naissance.jour, G.date_naissance.mois, G.date_naissance.annee,
                G.ville, G.numTEL, G.email,
                G.date_recrutement.jour, G.date_recrutement.mois, G.date_recrutement.annee);

        const char *gender = (G.sexe == 0) ? "Femme" : "Homme";
        fprintf(f, "%s ", gender);

        const char *work_hours = (G.horraires_de_travail == 0) ? "00h-8h" :
                                 (G.horraires_de_travail == 1) ? "8h-16h" : "16h-00h";
        fprintf(f, "%s ", work_hours);

        fprintf(f, "Poste%d\n", G.poste_de_travail);

        fclose(f);
        return 1;
    }
    return 0;
}


int modifier(char *file_agent, int CIN, agent nouvG)
{
    agent G;
    char gender_str[10], work_hours_str[10], work_poste[10];
    FILE *f = fopen(file_agent, "r");
    if (f == NULL) {
        printf("Error opening the input file: %s\n", file_agent);
        return 0;
    }

    FILE *f2 = fopen("nouv_agent.txt", "w");
    if (f2 == NULL) {
        printf("Error creating the output file: nouv_agent.txt\n");
        fclose(f);  // Close the input file before returning
        return 0;
    }


    while (fscanf(f, "%s %s %d %02d/%02d/%04d %s %d %s %02d/%02d/%04d %s %s %s",
                  G.nom, G.prenom, &G.CIN,
                  &G.date_naissance.jour, &G.date_naissance.mois, &G.date_naissance.annee,
                  G.ville, &G.numTEL, G.email,
                  &G.date_recrutement.jour, &G.date_recrutement.mois, &G.date_recrutement.annee,
                  gender_str, work_hours_str, work_poste) != EOF)
    {
        // Convert gender and work hours and work_poste from strings
        G.sexe = (strcmp(gender_str, "Femme") == 0) ? 0 : 1;
        
	if (strcmp(work_hours_str, "00h-8h") == 0)
            G.horraires_de_travail = 0;
        else if (strcmp(work_hours_str, "8h-16h") == 0)
            G.horraires_de_travail = 1;
        else
            G.horraires_de_travail = 2;

	if (strcmp(work_poste, "poste0") == 0)
            G.poste_de_travail = 0;
        else if (strcmp(work_poste, "poste1") == 0)
            G.poste_de_travail = 1;
        else if (strcmp(work_poste, "poste2") == 0)
            G.poste_de_travail = 2;        
	else
            G.poste_de_travail = 3;

        if (G.CIN == CIN)
        {
            fprintf(f2, "%s %s %d %02d/%02d/%04d %s %d %s %02d/%02d/%04d ",
                    nouvG.nom, nouvG.prenom, nouvG.CIN,
                    nouvG.date_naissance.jour, nouvG.date_naissance.mois, nouvG.date_naissance.annee,
                    nouvG.ville, nouvG.numTEL, nouvG.email,
                    nouvG.date_recrutement.jour, nouvG.date_recrutement.mois, nouvG.date_recrutement.annee);

            const char *gender = (nouvG.sexe == 0) ? "Femme" : "Homme";
            fprintf(f2, "%s ", gender);

            const char *work_hours = (nouvG.horraires_de_travail == 0) ? "00h-8h" :
                                      (nouvG.horraires_de_travail == 1) ? "8h-16h" : "16h-00h";
            fprintf(f2, "%s ", work_hours);

            fprintf(f2, "Poste%d\n", nouvG.poste_de_travail);

        }
        else
        {
            fprintf(f2, "%s %s %d %02d/%02d/%04d %s %d %s %02d/%02d/%04d %s %s Poste%d\n",
                    G.nom, G.prenom, G.CIN,
                    G.date_naissance.jour, G.date_naissance.mois, G.date_naissance.annee,
                    G.ville, G.numTEL, G.email,
                    G.date_recrutement.jour, G.date_recrutement.mois, G.date_recrutement.annee,
                    (G.sexe == 0) ? "Femme" : "Homme",
                    (G.horraires_de_travail == 0) ? "00h-8h" :
                    (G.horraires_de_travail == 1) ? "8h-16h" : "16h-00h",
                    G.poste_de_travail);
        }
    }

    fclose(f);
    fclose(f2);

    remove(file_agent);
    rename("nouv_agent.txt", file_agent);

    return 1;
}



int supprimer(char *file_agent, int CIN)
{
    agent G;
    char gender_str[10], work_hours_str[10], work_poste[10];
    int found = 0; // Pour vérifier si l'agent a été trouvé

    FILE *f = fopen(file_agent, "r");
    if (f == NULL) {
        printf("Erreur lors de l'ouverture du fichier : %s\n", file_agent);
        return 0;
    }

    FILE *f2 = fopen("nouv_agent.txt", "w");
    if (f2 == NULL) {
        printf("Erreur lors de la création du fichier temporaire : nouv_agent.txt\n");
        fclose(f);
        return 0;
    }

    // Lecture et écriture dans le fichier temporaire en excluant l'agent avec le CIN spécifié
    while (fscanf(f, "%s %s %d %02d/%02d/%04d %s %d %s %02d/%02d/%04d %s %s %s",
                  G.nom, G.prenom, &G.CIN,
                  &G.date_naissance.jour, &G.date_naissance.mois, &G.date_naissance.annee,
                  G.ville, &G.numTEL, G.email,
                  &G.date_recrutement.jour, &G.date_recrutement.mois, &G.date_recrutement.annee,
                  gender_str, work_hours_str, work_poste) != EOF)
    {
        // Si le CIN correspond, on marque cet agent comme trouvé et on le saute
        if (G.CIN == CIN) {
            found = 1;
        }
        else {
            fprintf(f2, "%s %s %d %02d/%02d/%04d %s %d %s %02d/%02d/%04d %s %s %s\n",
                    G.nom, G.prenom, G.CIN,
                    G.date_naissance.jour, G.date_naissance.mois, G.date_naissance.annee,
                    G.ville, G.numTEL, G.email,
                    G.date_recrutement.jour, G.date_recrutement.mois, G.date_recrutement.annee,
                    gender_str, work_hours_str, work_poste);

        }
    }

    fclose(f);
    fclose(f2);

    // Si l'agent n'a pas été trouvé, on supprime le fichier temporaire et on retourne 0
    if (found==0) {
        printf("Agent avec le CIN %d non trouvé.\n", CIN);
        remove("nouv_agent.txt");
        return 0;
    }

    // si l'agent est trouvé, on remplace le fichier original par le fichier temporaire et on retourne 1
    remove(file_agent);
    rename("nouv_agent.txt", file_agent);

    printf("Suppression de l'agent avec CIN %d réussie.\n", CIN);
    return 1;
}

int chercher(char *file_agent, int CIN, agent *pG)
{
    char gender_str[10], work_hours_str[10], work_poste[10];
    int found = 0;
    FILE *f = fopen(file_agent, "r");

    if (f == NULL) {
        printf("Error opening the input file: %s\n", file_agent);
        return 0;
    }

    while (fscanf(f, "%s %s %d %02d/%02d/%04d %s %d %s %02d/%02d/%04d %s %s %s",
                  pG->nom, pG->prenom, &pG->CIN,
                  &pG->date_naissance.jour, &pG->date_naissance.mois, &pG->date_naissance.annee,
                  pG->ville, &pG->numTEL, pG->email,
                  &pG->date_recrutement.jour, &pG->date_recrutement.mois, &pG->date_recrutement.annee,
                  gender_str, work_hours_str, work_poste) != EOF)
    {
        if (pG->CIN == CIN) {
            pG->sexe = (strcmp(gender_str, "Femme") == 0) ? 0 : 1;

            if (strcmp(work_hours_str, "00h-8h") == 0)
                pG->horraires_de_travail = 0;
            else if (strcmp(work_hours_str, "8h-16h") == 0)
                pG->horraires_de_travail = 1;
            else
                pG->horraires_de_travail = 2;

            if (strcmp(work_poste, "Poste0") == 0)
                pG->poste_de_travail = 0;
            else if (strcmp(work_poste, "Poste1") == 0)
                pG->poste_de_travail = 1;
            else if (strcmp(work_poste, "Poste2") == 0)
                pG->poste_de_travail = 2;
            else
                pG->poste_de_travail = 3;

            found = 1;
            break;
        }
    }
    fclose(f);
    return found;
}

int afficher_cherche_agent(char *file_agent, int CIN)
{
    agent G;
    int found;
    FILE *f2 = fopen("cherche_agent.txt", "w");
    if (f2 == NULL) {
        printf("Error creating the output file: cherche_agent.txt\n");
        return 0;
    }

    found = chercher(file_agent, CIN, &G);
    if (!found) {
        printf("\nAgent non trouvé\n");
    } else {
        const char *gender = (G.sexe == 0) ? "Femme" : "Homme";
        const char *work_hours = (G.horraires_de_travail == 0) ? "00h-8h" :
                                 (G.horraires_de_travail == 1) ? "8h-16h" : "16h-00h";
        
        fprintf(f2, "%s %s %d %02d/%02d/%04d %s %d %s %02d/%02d/%04d %s %s Poste%d\n",
                G.nom, G.prenom, G.CIN,
                G.date_naissance.jour, G.date_naissance.mois, G.date_naissance.annee,
                G.ville, G.numTEL, G.email,
                G.date_recrutement.jour, G.date_recrutement.mois, G.date_recrutement.annee,
                gender, work_hours, G.poste_de_travail);

        printf("\nAgent trouvé avec succès...vérifier le fichier cherche_agent\n");
    }
    fclose(f2);
    return found;
}

int chercher_reservation(char *file_reservation, int jour,int mois,int annee, reservation *pR)
{
    int found=0;
    FILE *f3 = fopen(file_reservation, "r");

    if (f3 == NULL) {
        printf("Error opening the input file: %s\n", file_reservation);
        return 0;
    }
    while (fscanf(f3,"%s %d %d %d %s %02d/%02d/%04d",
                  pR->nom, &pR->id, &pR->place, &pR->durree, pR->statut, &pR->date_reservation.jour, &pR->date_reservation.mois, &pR->date_reservation.annee ) != EOF)
    {
        if((pR->date_reservation.jour==jour) && (pR->date_reservation.mois==mois) && (pR->date_reservation.annee==annee))
        {
            found=1;
            break;
        }
    }
    fclose(f3);
    return found;
}

int afficher_reservation(char *file_reservation,int jour,int mois,int annee)
{
    reservation R;
    int x;
    FILE *f2 = fopen("cherche_reservation.txt", "w");
    if (f2 == NULL) {
        printf("Error creating the output file: cherche_reservation.txt\n");
        return 0;
    }
    x=chercher_reservation(file_reservation ,jour, mois ,annee, &R);
    if (!x) {
        printf("\nRéservation non trouvé\n");
    }
    else {
        fprintf(f2,"%s %d %d %d %s %02d/%02d/%04d\n",
                R.nom, R.id, R.place, R.durree, R.statut, R.date_reservation.jour, R.date_reservation.mois, R.date_reservation.annee );
        printf("\nRéservation trouvée avec succès...vérifier le fichier cherche_reservation\n");
    }
    fclose(f2);
    return x;
}

/********************************************************************************************/
#include <gtk/gtk.h>



void afficher_agent(GtkWidget *liste) {
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeIter iter;
    GtkTreeModel *store;
    FILE *f;
    char nom[30];
    char prenom[30];
    int cin;
    char date_naissance[15];
    char ville[30];
    int numtel;
    char email[30];
    char date_recrutement[15];
    char sexe[10];
    char work_hours[10];
    char work_poste[15];

    store = gtk_tree_view_get_model(GTK_TREE_VIEW(liste));
    if (store == NULL) {
        // Création des colonnes si elles n'existent pas encore
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Nom", renderer, "text", NOM, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Prénom", renderer, "text", PRENOM, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("CIN", renderer, "text", CIN, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Date de naissance", renderer, "text", DN, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Ville", renderer, "text", VILLE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Numéro de téléphone", renderer, "text", NUMTEL, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Email", renderer, "text", EMAIL, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Date de recrutement", renderer, "text", DR, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Sexe", renderer, "text", SEXE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Heures de travail", renderer, "text", WH, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Poste", renderer, "text", WP, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
    }

    // Création du modèle
    store = gtk_list_store_new(COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT, G_TYPE_STRING,
                               G_TYPE_STRING, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING,
                               G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

    // Lecture du fichier
    f = fopen("agents.txt", "r");
    if (f == NULL) {
        g_print("Erreur : Impossible d'ouvrir le fichier agents.txt\n");
        return; // On quitte la fonction en cas d'erreur
    }

    while (fscanf(f, "%s %s %d %s %s %d %s %s %s %s %s", nom, prenom, &cin, date_naissance,
                  ville, &numtel, email, date_recrutement, sexe, work_hours, work_poste) != EOF) {
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                           NOM, nom,
                           PRENOM, prenom,
                           CIN, cin,
                           DN, date_naissance,
                           VILLE, ville,
                           NUMTEL, numtel,
                           EMAIL, email,
                           DR, date_recrutement,
                           SEXE, sexe,
                           WH, work_hours,
                           WP, work_poste,
                           -1);
    }

    fclose(f);

    // Associer le modèle à la vue
    gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
    g_object_unref(store);
}

/*********************************************************************************************/



void afficher_liste_reservation(GtkWidget *liste) {
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeIter iter;
    GtkTreeModel *store;
    FILE *f;
    char nom[30];
    int id;
    int place;
    int duree;
    char statue[50];  // Augmenter la taille du tableau pour le statut
    char date_reservation[20];  // Augmenter la taille pour la date

    store = gtk_tree_view_get_model(GTK_TREE_VIEW(liste));
    if (store == NULL) {
        // Création des colonnes si elles n'existent pas encore
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Nom", renderer, "text", NNOM, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("ID", renderer, "text", ID, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Place", renderer, "text", PLACE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Duree", renderer, "text", DUREE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Statue", renderer, "text", STATUE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Date de reservation", renderer, "text", DRES, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
    }

    // Création du modèle avec des types spécifiques
    store = gtk_list_store_new(CCOLUMNS, G_TYPE_STRING, G_TYPE_INT, G_TYPE_INT, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING);

    f = fopen("cherche_reservation.txt", "r");
    if (f == NULL) {
        return; // Si le fichier ne s'ouvre pas, quitter la fonction
    }

    while (fscanf(f, "%s %d %d %d %49s %19s", nom, &id, &place, &duree, statue, date_reservation) != EOF) {
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter, NNOM, nom, ID, id, PLACE, place, DUREE, duree, STATUE, statue, DRES, date_reservation, -1);
    }

    fclose(f); // Assurer la fermeture du fichier après lecture

    // Associer le modèle à la vue
    gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
    g_object_unref(store); // Libérer le modèle
}













