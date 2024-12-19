#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <string.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "agent.h"



void on_ajouter_clicked(GtkButton *objet_graphique, gpointer user_data) {
	GtkWidget *input_nom;
	GtkWidget *input_prenom;
	GtkWidget *input_CIN;
	GtkWidget *input_ville;
	GtkWidget *input_numTEL;
	GtkWidget *input_email;
	GtkWidget *dn_jour;
	GtkWidget *dn_mois;
	GtkWidget *dn_annee;
	GtkWidget *dr_jour;
	GtkWidget *dr_mois;
	GtkWidget *dr_annee;
	GtkWidget *Combobox1;
	GtkWidget *Combobox2;
	GtkWidget *toggle_button_h;
	GtkWidget *toggle_button_f;
	GtkWidget *output;
	int n;


	agent new_agent;  

    // Récupérer les widgets
	input_nom = lookup_widget(GTK_WIDGET(objet_graphique), "nom");
	input_prenom = lookup_widget(GTK_WIDGET(objet_graphique), "prenom");
	input_CIN = lookup_widget(GTK_WIDGET(objet_graphique), "CIN");
	input_ville = lookup_widget(GTK_WIDGET(objet_graphique), "ville");
	input_numTEL = lookup_widget(GTK_WIDGET(objet_graphique), "numTEL");
	input_email = lookup_widget(GTK_WIDGET(objet_graphique), "email");
	output = lookup_widget(GTK_WIDGET(objet_graphique), "output");
	dn_jour = lookup_widget(GTK_WIDGET(objet_graphique), "datedenaissancejour");
	dn_mois = lookup_widget(GTK_WIDGET(objet_graphique), "datedenaissancemois");
	dn_annee = lookup_widget(GTK_WIDGET(objet_graphique), "datedenaissanceannee");
	dr_jour = lookup_widget(GTK_WIDGET(objet_graphique), "datederecrutementjour");
	dr_mois = lookup_widget(GTK_WIDGET(objet_graphique), "datederecrutementmois");
	dr_annee = lookup_widget(GTK_WIDGET(objet_graphique), "datederecrutementannee");
	Combobox1 = lookup_widget(GTK_WIDGET(objet_graphique), "horraires_de_travail");
	Combobox2 = lookup_widget(GTK_WIDGET(objet_graphique), "poste_de_travail");
	toggle_button_h = lookup_widget(GTK_WIDGET(objet_graphique), "homme");
	toggle_button_f = lookup_widget(GTK_WIDGET(objet_graphique), "femme");

	/* Récupérer les valeurs des boutons radio en utilisant la fonction gtk_toggle_button_set_active */
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggle_button_h))) {
		new_agent.sexe=1;
	}
	else
		if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggle_button_f))) {
			new_agent.sexe=0;
		}


	/* Récupérer les valeurs des spins buttons en utulisant la fonction gtk_spin_button_get_value_as_int qui retourne l'entier choisi par l'utilisateur */    
	new_agent.date_naissance.jour=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(dn_jour));
	new_agent.date_naissance.mois=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(dn_mois));
	new_agent.date_naissance.annee=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(dn_annee));
	new_agent.date_recrutement.jour=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(dr_jour));
	new_agent.date_recrutement.mois=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(dr_mois));
	new_agent.date_recrutement.annee=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(dr_annee));


    // Récupérer les textes entrés par l'utilisateur
	strcpy(new_agent.nom, gtk_entry_get_text(GTK_ENTRY(input_nom)));
	strcpy(new_agent.prenom, gtk_entry_get_text(GTK_ENTRY(input_prenom)));
	strcpy(new_agent.ville, gtk_entry_get_text(GTK_ENTRY(input_ville)));
	strcpy(new_agent.email, gtk_entry_get_text(GTK_ENTRY(input_email)));

    // Conversion de CIN et numTEL en entier
	new_agent.CIN = atoi(gtk_entry_get_text(GTK_ENTRY(input_CIN)));
	new_agent.numTEL = atoi(gtk_entry_get_text(GTK_ENTRY(input_numTEL)));

/* Récupérer les valeurs des combobox en utilisant la fonction gtk_combo_box_get_active_text qui retourne la chaine de caractère choisis par l'utilisateur */
	if (strcmp("00h==>8h",gtk_combo_box_get_active_text(GTK_COMBO_BOX(Combobox1)))==0) {
		new_agent.horraires_de_travail=0;	
	}
	else
		if (strcmp("8h==>16h",gtk_combo_box_get_active_text(GTK_COMBO_BOX(Combobox1)))==0) {
			new_agent.horraires_de_travail=1;
		}
		else {
			new_agent.horraires_de_travail=2;
		}

	
	
	if (strcmp("poste0",gtk_combo_box_get_active_text(GTK_COMBO_BOX(Combobox2)))==0) {
		new_agent.poste_de_travail=0;	
	}
	else
		if (strcmp("poste1",gtk_combo_box_get_active_text(GTK_COMBO_BOX(Combobox2)))==0) {
			new_agent.poste_de_travail=1;
		}
		else
			if (strcmp("poste2",gtk_combo_box_get_active_text(GTK_COMBO_BOX(Combobox2)))==0) {
				new_agent.poste_de_travail=2;
			}
			else {
				new_agent.poste_de_travail=3;
			}


	


    // Vérification des champs
	if (strlen(new_agent.nom) == 0 || strlen(new_agent.prenom) == 0 || new_agent.CIN == 0 ||
		strlen(new_agent.ville) == 0 || new_agent.numTEL == 0 || strlen(new_agent.email) == 0) {
		gtk_label_set_text(GTK_LABEL(output), "Tous les champs doivent être remplis !");
	} 
	else {
        // Si les champs sont valides, ajoutez l'agent
		n=ajouter_agent("agents.txt", new_agent);
		if (n != 0) {
			gtk_label_set_text(GTK_LABEL(output), "Agent ajouté avec succès !");
		} 
		else {
			gtk_label_set_text(GTK_LABEL(output), "Erreur lors de l'ajout de l'agent.");
        	}
    	}
}


/******************************************************************************************************/

void on_continuer_clicked(GtkButton *objet_graphique, gpointer user_data) {
	GtkWidget *output;
	GtkWidget *input_CIN;
	int CIN;
	int n;
	input_CIN = lookup_widget(GTK_WIDGET(objet_graphique), "CIN");
	output = lookup_widget(GTK_WIDGET(objet_graphique), "output");
	CIN = atoi(gtk_entry_get_text(GTK_ENTRY(input_CIN)));
	n=supprimer("agents.txt",CIN);
	if (!n) {
		gtk_label_set_text(GTK_LABEL(output), "Agent non trouvé(e) !");
	}
	else {
		gtk_label_set_text(GTK_LABEL(output), "Agent supprimé(e) avec succès !"); 
	}

}

/*****************************************************************************************************/
void on_modifier_clicked(GtkButton *objet_graphique, gpointer user_data)
{
    GtkWidget *output;
    GtkWidget *input_nom, *input_prenom, *input_CIN, *input_ville, *input_numTEL, *input_email;
    GtkWidget *Combobox1, *Combobox2;
    agent new_agent;
    int cin, n;

    // Initialisation des widgets
    output = lookup_widget((GtkWidget *)objet_graphique, "output");
    input_nom = lookup_widget((GtkWidget *)objet_graphique, "nom");
    input_prenom = lookup_widget((GtkWidget *)objet_graphique, "prenom");
    input_CIN = lookup_widget((GtkWidget *)objet_graphique, "CIN");
    input_ville = lookup_widget((GtkWidget *)objet_graphique, "ville");
    input_numTEL = lookup_widget((GtkWidget *)objet_graphique, "numTEL");
    input_email = lookup_widget((GtkWidget *)objet_graphique, "email");
    Combobox1 = lookup_widget((GtkWidget *)objet_graphique, "horraires");
    Combobox2 = lookup_widget((GtkWidget *)objet_graphique, "poste");

    // Vérification des champs
    if (strlen(gtk_entry_get_text(GTK_ENTRY(input_nom))) == 0 ||
        strlen(gtk_entry_get_text(GTK_ENTRY(input_prenom))) == 0 ||
        strlen(gtk_entry_get_text(GTK_ENTRY(input_CIN))) == 0 ||
        strlen(gtk_entry_get_text(GTK_ENTRY(input_ville))) == 0 ||
        strlen(gtk_entry_get_text(GTK_ENTRY(input_email))) == 0) {
        gtk_label_set_text(GTK_LABEL(output), "Tous les champs doivent être remplis !");
        return;
    }

    // Récupération des valeurs
    strcpy(new_agent.nom, gtk_entry_get_text(GTK_ENTRY(input_nom)));
    strcpy(new_agent.prenom, gtk_entry_get_text(GTK_ENTRY(input_prenom)));
    strcpy(new_agent.ville, gtk_entry_get_text(GTK_ENTRY(input_ville)));
    strcpy(new_agent.email, gtk_entry_get_text(GTK_ENTRY(input_email)));

    // Conversion des champs numériques
    new_agent.CIN = atoi(gtk_entry_get_text(GTK_ENTRY(input_CIN)));
    new_agent.numTEL = atoi(gtk_entry_get_text(GTK_ENTRY(input_numTEL)));

    // Récupération des combobox
    if (strcmp("00h==>8h", gtk_combo_box_get_active_text(GTK_COMBO_BOX(Combobox1))) == 0) {
        new_agent.horraires_de_travail = 0;
    } else if (strcmp("8h==>16h", gtk_combo_box_get_active_text(GTK_COMBO_BOX(Combobox1))) == 0) {
        new_agent.horraires_de_travail = 1;
    } else {
        new_agent.horraires_de_travail = 2;
    }

    // Appeler la fonction `on_ccontinuer_clicked` pour obtenir le CIN
    cin = on_ccontinuer_clicked(objet_graphique, user_data);
    n=modifier("agents.txt", cin, new_agent);
    if (!cin) {
        gtk_label_set_text(GTK_LABEL(output), "Erreur : CIN invalide !");
        return;
    }

    // Modifier l'agent
    if (!n) {
        gtk_label_set_text(GTK_LABEL(output), "Erreur lors de la modification de l'agent !");
    } else {
	n=modifier("agents.txt", cin, new_agent);
        gtk_label_set_text(GTK_LABEL(output), "Modification réussie !");
    }
}
 

/**********************************************************************************************************************************/
int on_ccontinuer_clicked(GtkButton *objet_graphique, gpointer user_data)
{
    GtkWidget *output;
    GtkWidget *input_CIN;
    int n, CIN;
    char msg[100];
    agent G;
    GtkWidget *fenetre_chercher;
    GtkWidget *fenetre_modifier;

    // Cast objet_graphique to GtkWidget*
    fenetre_chercher = lookup_widget((GtkWidget *)objet_graphique, "demande modifier cin agent");
    fenetre_modifier = lookup_widget((GtkWidget *)objet_graphique, "mis à jour compte agent");
    input_CIN = lookup_widget((GtkWidget *)objet_graphique, "CIN");
    output = lookup_widget((GtkWidget *)objet_graphique, "output");

    // Get input from the entry field
    strcpy(msg, gtk_entry_get_text(GTK_ENTRY(input_CIN)));

    // Check if input is empty
    if (strlen(msg) == 0) {
        gtk_label_set_text(GTK_LABEL(output), "Le champ doit être complis");
        return 0; // Exit function if input is empty
    }

    // Convert input to integer and search for the agent
    CIN = atoi(msg);
    n = chercher("agents.txt", CIN, &G);

    // Handle search results
    if (!n) {
        gtk_label_set_text(GTK_LABEL(output), "Agent non trouvé(e) !");
    } else {
        gtk_widget_destroy(fenetre_chercher);
        
        // Ensure create_mis____jour_compte_agent is implemented or corrected
        fenetre_modifier = create_mis____jour_compte_agent(); 
        gtk_widget_show(fenetre_modifier);
    }
    return CIN;
}






/**********************************************************************************************/

void
on_treeview1_row_activated             (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{

}

/**************************************************************************************************/
void on_supprimerlabprincipale_clicked(GtkButton *objet_graphique, gpointer user_data)
{
    GtkWidget *fenetre_principale;
    GtkWidget *fenetre_supprimer;
    fenetre_principale = lookup_widget((GtkWidget *)objet_graphique, "labelprincipale");
    fenetre_supprimer = lookup_widget((GtkWidget *)objet_graphique, "supprimer un agent");
    fenetre_supprimer = create_Supprimer_un_agent ();
    gtk_widget_show (fenetre_supprimer);
    
}

void on_modifierlabprincipale_clicked(GtkButton *objet_graphique, gpointer user_data)
{
    GtkWidget *fenetre_principale;
    GtkWidget *fenetre_modifier;
    fenetre_principale = lookup_widget((GtkWidget *)objet_graphique, "labelprincipale");
    fenetre_modifier = lookup_widget((GtkWidget *)objet_graphique, "demande modifier cin agent");
    fenetre_modifier = create_demande_modifier_cin_agent ();
    gtk_widget_show (fenetre_modifier);

}


void on_ajouterlabprincipale_clicked(GtkButton *objet_graphique, gpointer user_data)
{
    GtkWidget *fenetre_principale;
    GtkWidget *fenetre_ajouter;
    fenetre_principale = lookup_widget((GtkWidget *)objet_graphique, "labelprincipale");
    fenetre_ajouter = lookup_widget((GtkWidget *)objet_graphique, "Ajouter un agent");
    fenetre_ajouter = create_Ajouter_un_agent ();
    gtk_widget_show (fenetre_ajouter);
}

void on_listereservation_clicked(GtkButton *objet_graphique, gpointer user_data)
{
    GtkWidget *fenetre_date_reservation;
    fenetre_date_reservation = create_date_de_r__servation ();
    gtk_widget_show (fenetre_date_reservation);


}


void on_okreservation_clicked(GtkButton *objet_graphique, gpointer user_data)
{
    GtkWidget *dres_jour;
    GtkWidget *dres_mois;
    GtkWidget *dres_annee;
    GtkWidget *output;
    GtkWidget *fenetre_liste_reservation;
    GtkWidget *treeview2;
    char buffer[50];
    reservation R;
    int n, x;

    dres_jour = lookup_widget(GTK_WIDGET(objet_graphique), "datedereservationjour");
    dres_mois = lookup_widget(GTK_WIDGET(objet_graphique), "datedereservationmois");
    dres_annee = lookup_widget(GTK_WIDGET(objet_graphique), "datedereservationannee");
    output = lookup_widget(GTK_WIDGET(objet_graphique), "output");

    R.date_reservation.jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(dres_jour));
    R.date_reservation.mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(dres_mois));
    R.date_reservation.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(dres_annee));

    n = chercher_reservation("re.txt", R.date_reservation.jour, R.date_reservation.mois, R.date_reservation.annee, &R);

    if (!n) {
        gtk_label_set_text(GTK_LABEL(output), "Réservation non trouvée !");
    } else {
        // Construire le message avec la date de réservation
        sprintf(buffer, "%d / %d / %d", R.date_reservation.jour, R.date_reservation.mois, R.date_reservation.annee);
        gtk_label_set_text(GTK_LABEL(output), buffer);

        x = afficher_reservation("re.txt", R.date_reservation.jour, R.date_reservation.mois, R.date_reservation.annee);
        fenetre_liste_reservation = create_liste_des_r__servations();
        gtk_widget_show(fenetre_liste_reservation);
        treeview2 = lookup_widget(fenetre_liste_reservation, "treeview2");
        afficher_liste_reservation(treeview2);
    }
}


