#ifndef AGENT_H_INCLUDED
#define AGENT_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

typedef struct
{
    int jour;
    int mois;
    int annee;
} date;

typedef struct
{
    char nom[20];
    int id;
    int place;
    int durree;
    char statut[10];
    date date_reservation;
}reservation;

typedef struct
{
    char nom [20];
    char prenom [20];
    int CIN ;
    date date_naissance;
    int sexe;
    char ville[20];
    int numTEL;
    char email[20];
    date date_recrutement;
    int horraires_de_travail;
    int poste_de_travail;
}agent;

enum {
    NOM,
    PRENOM,
    CIN,
    DN,
    VILLE,
    NUMTEL,
    EMAIL,
    DR,
    SEXE,
    WH,
    WP,
    COLUMNS
};

enum {
    NNOM,
    ID,
    PLACE,
    DUREE,
    STATUE,
    DRES,
    CCOLUMNS
};

void verif_CIN(agent *G);
void verif_numTEL(agent *G);
int verif_sexe(agent *G);
int verif_horraires(agent *G);
int verif_poste(agent *G);
void saisir_agent(agent *G);
int ajouter_agent(char * file_agent , agent G);
int modifier(char *file_agent, int CIN ,agent nouvG);
int supprimer(char *file_agent, int CIN);
int chercher(char *file_agent , int CIN, agent *pG);
int afficher_cherche_agent(char *file_agent, int CIN);
int chercher_reservation(char *file_reservation, int jour,int mois,int annee, reservation *pR);
int afficher_reservation(char *file_reservation,int jour,int mois,int annee);
void afficher_agent(GtkWidget *liste);
void afficher_liste_reservation(GtkWidget *liste);





#endif // AGENT_H_INCLUDED

